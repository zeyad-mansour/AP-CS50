import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT ticker, sum(shares) shares FROM purchase WHERE id = :sid GROUP BY ticker",
                           sid=session["user_id"])
    userDetails = db.execute("SELECT * FROM users WHERE id = :sid", sid=session["user_id"])
    value = 0.00
    cash = usd(userDetails[0]["cash"])

    # Iterating through users portfolio and cleaning up values for display
    for row in portfolio:
        details = lookup(row["ticker"])
        row["name"] = details['name']
        row["price"] = usd(details['price'])
        row["value"] = usd(details['price'] * row['shares'])
        value += details['price'] * row['shares']

    value = usd(value + userDetails[0]["cash"])
    return render_template("index.html", portfolio=portfolio, cash=cash, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    #Make sure user arrives via post
    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))

        if stock == None:
            return apology("invalid ticker symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must be a number")

        #Make sure number of shres is positive
        if shares < 0:
            return apology("input positive number")

        rows = db.execute("SELECT cash FROM users WHERE id = :user_id",
                            user_id=session["user_id"])

        available_cash = rows[0]["cash"]

        price = stock["price"]

        total_price = shares * price

        if available_cash < total_price:
            return apology("insufficient funds")

        db.execute("UPDATE users SET cash = cash - :total_price WHERE id = :user_id", total_price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO 'transactions' (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=request.form.get("symbol"), shares=shares, price=price)

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get("username")

    # Checks server for if the username exists
    result = db.execute("SELECT * FROM users WHERE EXISTS (SELECT * FROM users WHERE username = :username)", username=username)

    # Returns via JSON whether name is available or not
    if not result and len(username) > 0:
        return jsonify(True)
    else:
        return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must haz username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Successfully Logged In')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        #Get stock information
        stock = lookup(request.form.get("symbol"))

        #Validate ticker symbol
        if stock == None:
            return apology("invalid ticker symbol")

        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    #User reached route via POST
    if request.method == "POST":

        #User entered username
        if not request.form.get("username"):
            return apology("must provide username")

        #User entered password
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password")

        #Confirm password matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password must match")

        #Hash the password
        hash = generate_password_hash(request.form.get("password"))

        #Insert user into database
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=request.form.get("username"), hash=hash)

        if not result:
            return apology("username already exists")
        else:
            return apology("registration complete", 200)

        #Remember user
        session["user_id"] = result

        return redirect("/")

    #User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))

        if stock == None:
            return apology("invalid ticker symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must be a number")

        if shares < 0:
            return apology("input positive number")

        available_shares = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id and symbol = :symbol GROUP BY symbol",
                                        user_id=session["user_id"], symbol=request.form.get("symbol"))

        if available_shares[0]["total_shares"] < 1 or shares > available_shares[0]["total_shares"]:
            return apology("not enough shares")

        price = stock["price"]

        total_price = shares * price

        db.execute("UPDATE users SET cash = cash + :total_price WHERE id = :user_id", user_id=session["user_id"], total_price=total_price)
        db.execute("INSERT INTO 'transactions' (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=request.form.get("symbol"), shares=-shares, price=price)

        return redirect("/")

    else:
        available_stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
        return render_template("sell.html", available_stocks=available_stocks)

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change Password"""

    # If user submitted form
    if request.method == "POST":

        # Checks if Old Password was provided
        if not request.form.get("oldPassword"):
            return apology("Old Password is Needed", 403)

        # Checks if New Password was provided
        if not request.form.get("newPassword"):
            return apology("Need a New Password", 403)

        # Checks if New Password was typed in correctly the second time
        if not request.form.get("newPassword") == request.form.get("confirmation"):
            return apology("New Passwords Don't Match", 403)

        details = db.execute("SELECT * FROM users WHERE id = :sid", sid=session["user_id"])

        # Checks if old password matches and if it does, updates to new password
        if check_password_hash(details[0]["hash"], request.form.get("oldPassword")):
            hsp = generate_password_hash(request.form.get("newPassword"), method='pbkdf2:sha256', salt_length=8)
            db.execute("UPDATE users SET hash = :hash WHERE id = :sid", hash=hsp, sid=session["user_id"])
            flash("Password Updated")
            return redirect("/")
    else:
        return render_template("password.html")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Deposit More Money!"""

    # If user arrived via POST, prepare to add more money
    if request.method == "POST":

        cash = int(request.form.get("deposit"))

        # Checks if deposit amount is positive
        if cash < 0:
            return apology("Must be a Positive Integer")

        # Checks current balance and then adds the deposit amount and resaves the value
        details = db.execute("SELECT * FROM users WHERE id = :sid", sid=session["user_id"])
        newTotal = cash + details[0]["cash"]
        db.execute("UPDATE users SET cash = :cash WHERE id = :sid", cash=newTotal, sid=session["user_id"])

        # Return to home, confirming deposit to user
        flash("Money Deposited, Baller!")
        return redirect("/")
    else:
        return render_template("deposit.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
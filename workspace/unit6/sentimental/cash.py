from cs50 import get_float

total_coins = 0
quarter = 25
nickel = 5
dime = 10
penny = 1

while True:
    change = get_float("How much change do I owe you? ")
    if change > 0:
        break

change = int(change * 100)

while change > 0:
    while change >= quarter:
        total_coins += 1
        change -= quarter
    while change >= nickel:
        total_coins += 1
        change -= nickel
    while change >= dime:
        total_coins += 1
        change -= dime
    while change >= penny:
        change -= penny
        total_coins += 1

print(total_coins)
import cs50
def main():
    while True:
        print("height: ", end = "")
        height = cs50.get_int()
        if height >= 0 and height <= 23:
            break

    for i in range(height):
        for x in range(height - i - 1):
            print(" ", end = "")
        for j in range(i+2):
            print("#", end = "")
        print("")

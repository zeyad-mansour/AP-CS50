import sys
import cs50

def main():

    if len(sys.argv) != 2:
        sys.exit(1)

    if int(sys.argv[1]) < 26:
        key = int(sys.argv[1])
    else:
        key = int(sys.argv[1]) % 26

    print("Plaintext: ")
    plaintext = input()
    print("ciphertext: ", end="") # end parameter ends the output with a <space>

    for char in plaintext:
        if char.isalpha() and char.isupper():
            j = ((ord(char) - 65 + key) % 26) + 65
            print(chr(j), end="")
        elif char.isalpha() and char.islower():
            j = ((ord(char) - 97 + key) % 26) + 97
            print(chr(j), end="")
        else:
            print(char, end="")
    print("\n")

if __name__ == "__main__":
    main()

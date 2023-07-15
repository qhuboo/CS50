from cs50 import get_int


while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(1, height+1, 1):
    # Prints out the spaces
    for j in range(0, height - i, 1):
        print(" ", end="")
    # Prints out the hashes
    for k in range(0, i, 1):
        print("#", end="")
    # Prints out a 2 space gap
    # Prints out the right side
    print("  ", end="")
    for l in range(0, i, 1):
        print("#", end="")
    print()

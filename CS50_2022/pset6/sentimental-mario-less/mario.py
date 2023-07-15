from cs50 import get_int


# Gets the height from the user
# and ensures the input is between 0 and 9 exclusively
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
    print()

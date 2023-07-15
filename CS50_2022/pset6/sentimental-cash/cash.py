from cs50 import get_float


# Prompts the user for the change owed
# and ensures it is non-negative
while True:
    cents = get_float("Change owed: ")
    if cents > 0:
        break
# Convert to cents to avoid floating point imprecision
cents = cents * 100
# Calculates the number of quarters
quarters = cents // 25
cents = cents - (quarters * 25)
# Calculates the number of dimes
dimes = cents // 10
cents = cents - (dimes * 10)
# Calculates the number of nickels
nickels = cents // 5
cents = cents - (nickels * 5)
# Calculates the number of pennies
pennies = cents
# Coins is the sum of all the coin values
coins = quarters + dimes + nickels + pennies
# Prints the number of coins
print(int(coins))

# TODO

from cs50 import get_float

# originally had an indentation error here; rmb that the rest of the code should not be indented into while true loop
while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        break
amount = dollars * 100

# originally had an error here: rmb that cannot put return within the while loop, else if the return runs, we will break out of the function, ending the code
quarters = 0
while amount >= 25:
    amount = amount - 25
    quarters += 1

dimes = 0
while amount >= 10:
    amount = amount - 10
    dimes += 1

nickels = 0
while amount >= 5:
    amount = amount - 5
    nickels += 1

pennies = 0
while amount >= 1:
    amount = amount - 1
    pennies += 1
print(f"help")

# add the number of each coin together to find total coins required
coins = round(quarters + dimes + nickels + pennies)
print(f"{coins}")

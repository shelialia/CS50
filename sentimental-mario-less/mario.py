# TODO

from cs50 import get_int
# ask user for height input


def main():
    # for each row
    height = get_height()
    for row in range(height):
        # introduces space to the left
        for space in range(height - 1 - row):
            print(f" ", end="")
        # introduces hashes to the right
        for column in range(row + 1):
            print(f"#", end="")
        # move on to the next row
        print(f"\n", end="")

def get_height():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            return height


main()

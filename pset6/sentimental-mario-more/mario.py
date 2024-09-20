from cs50 import get_int


# Get height input from user until an integer between 1 & 8 is received
height = get_int("Height: ")

while height < 1 or height > 8:
    print("Please pick an integer between 1 and 8.")
    height = get_int("Height: ")

# Loop through a height amount of rows
for h in range(height):
    # Create base for range of blocks printed
    r = h + 1

    # Print correct amount of empty spaces
    print(" " * (height - r), end="")

    # Print correct amount of #
    print("#" * r, end="")

    # Print two blank spaces
    print("  ", end="")

    # Print rest of blocks
    print("#" * r)

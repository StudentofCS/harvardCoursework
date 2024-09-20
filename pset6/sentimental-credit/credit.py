from cs50 import get_int
from csv import DictReader
import re


# Main function asking for cc number
def main():
    # Get cc number input and turn it into a str
    cc = str(get_int("Number: "))

    # While the string is empty, continue asking for cc number
    while not cc:
        cc = str(get_int("Number: "))

    if luhn(cc):
        print(valid(cc))

    else:
        print("INVALID")


# Function to run Luhn's algorithm
def luhn(string):
    # Set variables needed for the algorithm
    penultimate = len(string) - 2
    sum = 0

    # Multiply every other digit by 2 then add each digit,
    # starting from second last digit
    for i in range(penultimate, -1, -2):
        temp = str(int(string[i]) * 2)
        if len(temp) > 1:
            sum += int(temp[0]) + int(temp[1])
        else:
            sum += int(temp)
        # print(f"multiply: {sum}")

    # Add the sum to the sum of the other digits
    for j in range(penultimate + 1, -1, -2):
        sum += int(string[j])
    #     print(f"add: {sum}")

    # print(sum)

    if sum % 10 == 0:
        return True
    else:
        return False

# # Function to check if number belongs to a valid cc company
# def valid(string):
#     corps = []

#     # Create a dict using the csv file
#     with open('cc.csv', 'r') as file:
#         reader = DictReader(file)

#         for row in reader:
#             corps.append(row)

#     # Cycle through each code seeing if it matches input
#     for corp in corps:
#         pattern = re.compile(corp["code"])
#         result = re.match(pattern, string)

#         # If a match is found, print the name of cc company
#         if result:
#             return corp["cc"].upper()
#             # print(f"{company}")
#             # break
#     else:
#         # If no match was found, print invalid
#         return "INVALID"
#         # print("INVALID")


# Function to check if number belongs to a valid cc company
def valid(string):
    # Create a dict of all the corps and their codes
    corps = {"34": "amex", "37": "amex", "51": "mastercard",
             "52": "mastercard", "53": "mastercard", "54": "mastercard",
             "55": "mastercard", "4": "visa"}

    # Cycle through each code seeing if it matches input
    for code, corp in corps.items():
        pattern = re.compile(code)
        result = re.match(pattern, string)

        # If a match is found, print the name of cc company
        if result:
            if corp == "amex" and len(string) == 15:
                return corp.upper()
            if corp == "mastercard" and len(string) == 16:
                return corp.upper()
            if corp == "visa" and len(string) == 13 or len(string) == 16:
                return corp.upper()
    else:
        # If no matches, return invalid
        return "INVALID"


main()

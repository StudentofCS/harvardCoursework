from cs50 import get_string
import re


# Main function that outputs the grade level of a text
def main():
    text = get_string("Text: ")

    # Find total number of letters
    letters = find(r"[a-zA-Z]", text)

    # Find total number of words
    words = find(r"[\s]", text) + 1

    # Find total number of sentences
    sentences = find(r"[.!?]", text)

    # Find the avg number of letters and sentences per 100 words
    l = (letters / words) * 100
    s = (sentences / words) * 100

    # Find the coleman-liau score
    grade = round(clindex(l, s))

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# Function to find the pattern
def find(string, text):
    results = re.findall(string, text)
    return len(results)


# Function that calculates the coleman-liau index
def clindex(l, s):
    return 0.0588 * l - 0.296 * s - 15.8


main()

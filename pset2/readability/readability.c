#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function that takes input and counts the letters
int count_letters(char *text);

// Function that counts the words in a text
int count_words(char *text);

// Function that counts the sentences in a text
int count_sentences(char *text);

int main(void)
{
    // Get string input from user
    char *text = get_string("Text: ");

    // Print what the user just input
    printf("\n%s\n", text);

    // Check number of letters in text
    int num_of_letters = count_letters(text);

    // Check number of words in a text
    float num_of_words = count_words(text);

    // check number of sentences
    int num_of_sentences = count_sentences(text);

    // Average number of letters / words and sentences / words * 100
    float avg_l = (num_of_letters / num_of_words) * 100;
    float avg_s = (num_of_sentences / num_of_words) * 100;

    int index = round(0.0588 * avg_l - 0.296 * avg_s - 15.8);

    // Print the results of the reading level
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index > 15)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
}

int count_letters(char *text)
{
    // Variable for letters counted
    int counter = 0;

    int text_length = strlen(text);

    // Loop through entire array of text
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
            counter++;
    }
    return counter;
}

int count_words(char *text)
{
    // Variable for words counted
    int counter = 1;

    int text_length = strlen(text);

    // If string is empty, return 0
    if (text_length == 0)
        return 0;

    // Loop through entire array of text
    for (int i = 0; i < text_length; i++)
    {
        if (isspace(text[i]))
            counter++;
    }
    return counter;
}

int count_sentences(char *text)
{
    // Variable for letters counted
    int counter = 0;

    int text_length = strlen(text);

    // Loop through entire array of text
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            counter++;
    }
    return counter;
}
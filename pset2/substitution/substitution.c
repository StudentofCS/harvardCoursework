#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validate_key(char argv[]);
string ciphertext(string plaintext, char argv[]);
int ALPHABET[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    // Check if there are 2 inputs in argv
    if (argc != 2)
    {
        printf("Please enter a single command-line argument that will be used as your cipher key.\n");
        return 1;
    }

    // Validate the key has exactly 26 unique alphabetical chars
    if (validate_key(argv[1]) == false)
    {
        printf("Please make sure your key has only 26 unique alphabetical characters.\n");
        return 1;
    }

    // Request plaintext input from user
    string plaintext = get_string("plaintext: ");

    // Output ciphertext
    printf("ciphertext: %s\n", ciphertext(plaintext, argv[1]));

    return 0;
}

// Function that will validate if the key has 26 unique chars
bool validate_key(char argv[])
{
    string key = argv;
    int key_length = strlen(key);

    // Check if key has 26 chars
    if (key_length != 26)
    {
        return false;
    }
    // Check if key has every letter in alphabet and no non-alphabeticals
    else
    {
        for (int i = 0, j = key_length; i < j; i++)
        {
            // If key element is in ALPHABET, continue loop to next key element. Return false if not.
            for (int k = 0; k <= j; k++)
            {
                if (k == j)
                {
                    return false;
                }
                else
                {
                    if (ALPHABET[i] == key[k] || (ALPHABET[i] - 32) == key[k])
                    {
                        break;
                    }
                }
            }
        }
    }

    return true;
}

string ciphertext(string plaintext, char argv[])
{
    string key = argv;
    string cipher = plaintext;
    int cipher_length = strlen(cipher);

    // Use for loop to encrypt the plaintext alphabeticals
    for (int i = 0, j = cipher_length; i < j; i++)
    {
        if (islower(cipher[i]))
        {
            cipher[i] = key[cipher[i] - 97];
            cipher[i] = tolower(cipher[i]);
        }
        else if (isupper(cipher[i]))
        {
            cipher[i] = key[cipher[i] - 65];
            cipher[i] = toupper(cipher[i]);
        }
    }
    return cipher;
}

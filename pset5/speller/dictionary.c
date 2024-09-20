// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Inputs word into a hash table
void hashtable(unsigned int index, const char *word);
// Converts a string to all upper case
char *allupper(const char *word);
// Free memory of nodes
void freenode(node *ptr);

// TODO: Choose number of buckets in hash table
const unsigned int N = 25001;

// Hash table
node *table[N];

// Global variable keeping track of dictionary word count
int WORDCOUNT = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Prepare to check table for word where it would index
    int index = hash(word);

    // If node was initiated, compare strings
    if (table[index] != NULL)
    {
        char *temp1 = allupper(word);
        char *temp2 = allupper(table[index]->word);

        // If strings are identical return true
        if (strcmp(temp1, temp2) == 0)
        {
            free(temp1);
            free(temp2);
            return true;
        }
        // If strings are not identical and there's a linked node, check next words
        else if (table[index]->next != NULL)
        {
            node *ptr = table[index]->next;
            free(temp2);
            while (ptr != NULL)
            {
                temp2 = allupper(ptr->word);
                if (strcmp(temp1, temp2) == 0)
                {
                    free(temp1);
                    free(temp2);
                    return true;
                }
                else if (ptr->next != NULL)
                {
                    ptr = ptr->next;
                    free(temp2);
                }
                else
                    ptr = ptr->next;
            }
        }
        // Free temp variables
        free(temp1);
        free(temp2);
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Prepare to find the ASCII for the hash
    int index = 0;
    int length = strlen(word);
    int letters_hashed = 5;

    // Loop until we've reached the last letter or the letters_hashed amount
    for (int i = 0; i < length && i < letters_hashed; i++)
    {
        // Add the ascii values of a letter then to the index value square it
        index += (toupper(word[i]) - 'A');
        index *= index;
    }

    // If the index is greater than the table size, use mod of index
    if (index >= N)
        index = index % N;
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open file and check if opened properly
    FILE *inpt = fopen(dictionary, "r");
    if (inpt == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Prepare to read the dictionary file
    char c;
    char word[LENGTH + 1];
    int num = 0;

    // Initialize the hash table
    for (int i = 0; i < N; i++)
        table[i] = NULL;

    // Loop through each char in the file
    while (fread(&c, sizeof(char), 1, inpt) != 0)
    {
        // If the file goes to next line, close the word string and place in hashtable
        if (num > 0 && isspace(c))
        {
            word[num] = '\0';
            hashtable(hash(word), word);
            num = 0;
            WORDCOUNT++;
        }
        // If the char is a letter or apostrophe, add it to the current word
        else if (num < LENGTH && (isalpha(c) || c == '\''))
        {
            word[num] = c;
            num++;
        }
        // If the word is longer than LENGTH or has a non-letter, complete and don't hash
        else if (num >= LENGTH || !isalpha(c))
        {
            while (fread(&c, sizeof(char), 1, inpt) != 0 && !isspace(c))
                // Reset num to zero after reaching the end of the alphanumeric or oversized word
                num = 0;
        }
    }
    // Close file
    fclose(inpt);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Check if dictionary is loaded
    return WORDCOUNT;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Loop through the table checking every index
    for (int i = 0; i < N; i++)
    {
        // If node not null check if there are linked nodes
        if (table[i] != NULL)
        {
            freenode(table[i]);
            table[i] = NULL;
        }
    }
    return true;
}

// Inputs the indexed word into the hash table
void hashtable(unsigned int index, const char *word)
{
    // Create a new node to add the word to the hash table
    node *newword = malloc(sizeof(node));
    if (newword == NULL)
        printf("Could not malloc %s for hash table.\n", word);

    newword->next = NULL;

    // Check if hash table index is empty, if so then add the word
    if (table[index] == NULL)
    {
        table[index] = newword;
        strcpy(table[index]->word, word);
    }
    // If table index is not empty, find the next empty node in the linked list
    else
    {
        node *temp = table[index];
        while (temp->next != NULL)
            temp = temp->next;

        // Add the new node to the next empty node in the linked list
        temp->next = newword;
        strcpy(newword->word, word);
    }
}

// Converts strings into all upper case
char *allupper(const char *word)
{
    // Prepare to make all upper case word
    char *temp = malloc((LENGTH + 1) * sizeof(char));
    if (temp == NULL)
    {
        printf("Could not malloc temp in allupper function.\n");
        return NULL;
    }
    int i = 0;

    // Loop through to the end of the string while it's shorter than LENGTH or strlen
    int l = strlen(word);
    while (word[i] != '\0' && i < LENGTH && i < l)
    {
        temp[i] = toupper(word[i]);
        i++;
    }

    // Add the null character to the end of the temp string
    temp[i] = '\0';
    return temp;
}

// Frees the memory of nodes
void freenode(node *ptr)
{
    // Set base case for reiteration loop
    if (ptr->next == NULL)
        free(ptr);

    // Call freenode on the next node
    else
    {
        freenode(ptr->next);
        free(ptr);
    }
}

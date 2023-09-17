// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

unsigned int hashValue;
unsigned int countWord;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hashValue = hash(word);
    node *cursor = table[hashValue];

    while(cursor != 0)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *DictionaryFile = fopen(dictionary, "read");

    if (DictionaryFile == NULL)
    {
        printf("Could not open\n");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(DictionaryFile, "%s", word) != EOF)
    {
        node *temp = malloc(sizeof(node));

        if (temp == NULL)
        {
            return false;
        }

        strcpy(temp->word, word);

        hashValue = hash(word);
        temp->next = table[hashValue];
        table[hashValue] = temp;

        countWord++;
    }

    fclose(DictionaryFile);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (countWord > 0)
    {
        return countWord;
    }
    return 0;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <strings.h>
#include <cs50.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash the word to obtain an index value
    int index = hash(word);

    // create a temporary curser node, don't need to allocate memory to it.
    // because curser points at the first node of the linked list. which has already been allocated space to
    // cursor is not pointing to another node that has not been allocated space to yet.
    // urser's pointer point at whatever the linked list start is pointing at; that is the first word at that dictionary index
    node *curser = table[index];

    // if that array of LL does not exist in dictionary, we return false as word is not found
    if (table[index] == NULL)
    {
        return false;
    }

    // while the curser temporary node is pointing at a word (ie. the LL has not ended and does not show null terminator \0)
    while (curser != NULL)
    {
        // we compare the word we have at our hand now, and the word that temporary curser node is pointing at in the dictionary.
        // strcasecmp compares 2 strings case insensitively
        if (strcasecmp(word, curser -> word) == 0)
        {
            // if the words are the same, we return T, successful as word was found. once we return true, we will break out of the function
            return true;
        }
        // otherwise if word is not found yet, we continue on to the next word
        else
        {
            // set the curser temporary node to point at whatever the word node in dictionary is pointing at
            // this means the while loop continues on for the next word
            curser = curser -> next;
        }
    }
    // else if we alr hit the terminator value, we return false as no words were matched
    // we must put return false outside the while loop. only if the while condition is not fulfilled, will we run return false outside the while loop
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // the variable sum will accumulate the ASCII values of each character in the word
    long sum = 0;
    // iterate through each char in the word, until the end of the word
    for (int i = 0; i < strlen(word); i++)
    {
        // word[i] helps to convert each char to its ASCII value
        // the "tolower" function helps to convert each ASCII value to its lower case ASCII value, to ensure the function is case insensitive
        // sum += helps to add all of these up
        sum += tolower(word[i]);
    }
    // modulus of N, which is the size of the hash table, helps to ensure we keep the resulting hash value falls within the hash table
    return sum % N;
}

// we are counting the number of words in file, hence we initialise words in file to be zero first
int file_size = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    // if file contains nothing
    if (file == NULL)
    {
        // unsucessful loading, break out of the function
        fclose(file);
        return false;
    }

    // declare word as a variable again
    char word[LENGTH + 1];
    // while we are reading word by word (line by line, one word per line) and have not reached the end of the file,
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate memory for one node - for each word. this node is not pointing at any linked list yet. it is just a node by itself
        node *n = malloc(sizeof(node));
        // if no more memory space
        if (n == NULL)
        {
            // we close the file opened
            fclose(file);
            //return unsucessful
            return false;
        }
        // we copy over the word (a string) read into the word section of the node that is alone now
        strcpy(n -> word, word);
        // get rid of garbage values at the pointer section of node
        n -> next = NULL;
        // we hash the words. take the word as input, and give an index as output
        int index = hash(word);
        // if the index of word has no existing linked list,
        if (table[index] == NULL)
        {
            // we make the index node point at new word
            table[index] = n;
        }
        // else if the index of word contains an existing linked list,
        else
        {
            // we let the new word's node pointer point at whatever the table index node is pointing at
            n -> next = table[index];
            // we let the table index node pointer point at the new word's node
            table[index] = n;
        }
        // since we already added a word to the linked list in the respective index, we increase the size of file by one
        file_size++;
    }
    // we close the dictionary file
    fclose(file);
    // since we were sucessful in loading dictionary to memory, we return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return file_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 100000; i++)
    {
        // don't need to call malloc to allocate memory for the cursor node, will lead to memory loss instead
        // this is because we already have existing node cursor
        node *cursor = table[i];
        // same for tmp
        node *tmp;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
    return true;
}

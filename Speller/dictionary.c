// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 4000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *temp;
    node *head;
    int WordInputHash = hash(word);
    head = table[WordInputHash];
    while(head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        else
        {
            head = head->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //Credits: http://www.cse.yorku.ca/~oz/hash.html
{
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }
    if (hash > N)
    {
        return hash % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    char WordL[LENGTH + 1];
    node *nodeSto;
    FILE *Dictionary = fopen(dictionary, "r");
    if (Dictionary == NULL)
    {
        return false;
    }
    while (fscanf(Dictionary, "%s", WordL) != EOF)
    {
        nodeSto = malloc(sizeof(node));
        if (nodeSto == NULL)
        {
            unload();
            return false;
        }
        strcpy(nodeSto->word, WordL);
        int index = hash(nodeSto->word);
        if (table[index] == NULL)
        {
            nodeSto->next = NULL;
        }
        else
        {
            nodeSto->next = table[index];
        }
        table[index] = nodeSto;
    }
    fclose(Dictionary);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    node *temp;
    int counter = 0;
    for (int IndexNumberElements = 0; IndexNumberElements < N ; IndexNumberElements++)
    {
        temp = table[IndexNumberElements];
        while (temp != NULL)
        {
            temp = temp->next;
            counter++;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *temp;
    for (int index = 0; index < N; index++)
    {
        while (table[index] != NULL)
        {
            temp = table[index]->next;
            free(table[index]);
            table[index] = temp;
        }
    }
    free(temp);
    if (temp == NULL)
    {
        return true;
    }
    return false;
}
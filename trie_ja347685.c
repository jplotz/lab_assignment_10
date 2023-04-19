/*
 * Jacob Plotz
 * ja347685
 * CS1 Torosdagli Lab Assignment 10
 * 19 Apr. 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHA_LEN 26

struct Trie {
    // are we at the end of a word?
    bool isWord;
    // number of occurences of this word
    int count;
    struct Trie *next[ALPHA_LEN];
};

void insert(struct Trie **ppTrie, char *word);
int numberOfOccurences(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
// set *t to point to a new Trie data structure
void initTrie(struct Trie **t);


int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numWords = 5;

    struct Trie *trie = NULL;
    initTrie(&trie);

    for (int i = 0; i < numWords; i++)
        insert(&trie, pWords[i]);

    for (int i = 0; i < numWords; i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}

int getAlpha(char c)
{
    int x = c-'a';
    if (x >= 0 && x < ALPHA_LEN)
        return x;
    return -1;
}

void initTrie(struct Trie **t)
{
    (*t) = malloc(sizeof(struct Trie));
    if ((*t) == NULL)
        return; // malloc error
    (*t)->isWord = false;
    (*t)->count = 0;
    for (int i = 0; i < ALPHA_LEN; i++)
    {
        (*t)->next[i] = NULL;
    }
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < ALPHA_LEN; i++)
    {
        if (pTrie->next[i] != NULL)
        {
            deallocateTrie(pTrie->next[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Pre-condition: word is null terminated with '\0' and *ppTrie is already initialized
void insert(struct Trie **ppTrie, char *word)
{
    char *c = word;
    int pos;
    struct Trie *temp1 = *ppTrie;
    struct Trie *temp2;
    while (*c)
    {
        pos = getAlpha(*c);
        if (pos >= 0) // is valid position?
        {
            if (temp1->next[pos] == NULL)
            {
                initTrie(&temp2);
                temp1->next[pos] = temp2;
            }
            temp1 = temp1->next[pos];
        }
        c++;
    }
    temp1->isWord = true;
    temp1->count++;
}

int numberOfOccurences(struct Trie *pTrie, char *word)
{
    char *c = word;
    int pos;
    struct Trie *temp = pTrie;
    if (temp == NULL)
            return 0; // empty

    while (*c)
    {
        pos = getAlpha(*c);
        if (pos >= 0) // valid position
        temp = temp->next[pos];
        c++;
    }
    return temp->count;
}

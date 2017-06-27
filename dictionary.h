/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//definitions for hash function
#define HASH_SIZE  65535 //4294967296
#define FNV_PRIME 16777619
#define FNV_OFFSET_BASE 2166136261

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//type definition of dict_node
typedef struct dict_node {
    char dict_word[LENGTH + 1]; 
    struct dict_node *next;
}
dict_node;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned long int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Hashes words and returns a long int to enter words in dictionary array and to look up in the dictionary array.
 */
unsigned long int hash(char key[]);


/**
 * Delete a tree of nodes to free up memory. will only be called when at least one node is available.
 */
bool del_node_tree(dict_node *node);

/**
 * Recursively go through a tree to find the word to check.
 */
bool find_word(dict_node *node, const char* word);

#endif // DICTIONARY_H


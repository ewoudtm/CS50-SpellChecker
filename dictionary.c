/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include "dictionary.h"

unsigned long int word_counter = 0;
dict_node *hash_arr[HASH_SIZE+1] = {NULL};
dict_node *head = NULL;
dict_node *crawler = NULL;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //change word to lowercase
    char low_word[LENGTH+1];
    strcpy(low_word,word);
    for(int i = 0, j = strlen(low_word); i<j; i++){
        low_word[i] = tolower(low_word[i]);    
    }
    
    unsigned long int w = hash(low_word);
    
    crawler = hash_arr[w];
    
    while (crawler != NULL){
        if(strcmp(crawler->dict_word, low_word) == 0)
            return true;
        else
            crawler = crawler->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file 
    FILE* inptr = fopen(dictionary, "r");
    if (inptr == NULL){
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // creating hash array
    
    char tmp_word[LENGTH+1] = {0};
    
    // reading dictionary file per word and storing it into array according to hash function
    while(fscanf(inptr, "%s", tmp_word) != EOF){
        long int hash_index = hash(tmp_word);
        head = hash_arr[hash_index];
        
        // fit new node between head and null pointer (new_node = malloc, new_node ->next = head & head -> new_node, strcpy(new_node_> dict_word, tmp_word) )
        dict_node *new_node = (dict_node*)malloc(sizeof(dict_node));
        if (new_node == NULL){
            printf("failed to enter %s in dictionary", tmp_word);
            return false;
        } 
        new_node->next = head;
        head = new_node;
        strcpy(new_node->dict_word, tmp_word);
        hash_arr[hash_index] = head;
        head = NULL;
        word_counter++;
    }

    fclose(inptr);
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned long int size(void)
{
    return word_counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool unload(void)
{
    for (unsigned long int i = 0; i < HASH_SIZE+1; i++){
        if(hash_arr[i] != NULL)
            if(!del_node_tree(hash_arr[i]))
                return false;
    }
    
    return true;
}


/**
 * Hashes words and returns a long int to enter words in dictionary array and to look up in the dictionary array.
 * FNV-1a hash with lazy mod mapping method - http://www.isthe.com/chongo/tech/comp/fnv/index.html
 */
unsigned long int hash(char key[])
{
    unsigned long int hash = FNV_OFFSET_BASE;
    for (int i = 0, j = strlen(key); i<j; i++){  // for each octet_of_data to be hashed
        hash = hash ^ key[i]; // each octet of data
        hash = hash * FNV_PRIME;
    }
    hash %= HASH_SIZE;
    return hash;
}

/**
 * Delete a tree of nodes to free up memory. will only be called when at least one node is available.
 */
bool del_node_tree(dict_node *node)
{
    dict_node *del = NULL;
    head = node;
    while(head != NULL){
        del = head;
        head = head->next;
        free(del);
        del = NULL;
    }
    if (head == NULL)
        return true;
    return false;
}

/**
 * Recursively go through a tree to find the word to check.
 */
bool find_word(dict_node *node, const char* word)
{
    if(strcmp(node->dict_word, word) == 1)
        return true;
    else if(node->next == NULL)
        return false;
    else
        find_word(node->next, word);
    return false;
}

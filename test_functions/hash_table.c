#include <hash_table.h>

/**
 * create_table - Creates a hash table with a specified size.
 * 
 * @param size: The size of the hash table to be created.
 * Returns: A pointer to the newly created hash table, or NULL if memory allocation fails.
 */

HashTable* create_table(int size) {
    HashTable* ht = calloc(1, sizeof(HashTable));

    if (!ht) {
        return NULL; // Memory allocation failed
    }

    ht->size = size;
    ht->table = calloc(size, sizeof(Node*));
    if (!ht->table) {
        free(ht); // Free the hash table if table allocation fails
        return NULL; // Memory allocation failed
    }

    return ht;
}



/**
 * djb_hash - A simple hash function that computes a hash value for a given key.
 * It uses a basic algorithm that multiplies the current hash by 31 and adds the ASCII
 * 
 * @key: The input string for which the hash is to be computed.
 * @size: The size of the hash table to ensure the hash value fits within the table
 * 
 * Returns: An unsigned integer representing the hash value, which is the computed hash 
 */

 unsigned int djb_hash(const char *key, int size)
 {
    unsigned long hash = 0;
    int c;
    while ((c = *key++))
        hash = hash * 31 + c;
    return hash % size;
}

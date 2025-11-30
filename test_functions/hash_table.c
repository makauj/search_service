#include "hash_table.h"

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

 uint32_t djb_hash(const char *key, int size)
 {
    unsigned long hash = 0;
    int c;
    while ((c = *key++))
        hash = hash * 31 + c;
    return hash % size;
}

/**
 * free_table - Frees the memory allocated for the hash table.
 * 
 * @param ht: A pointer to the hash table to be freed.
 */
void free_table(HashTable* ht) {
    if (!ht) {
        return; // Nothing to free
    }
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp); // Free each node in the linked list
        }
    }
    free(ht->table); // Free the table array
    free(ht); // Free the hash table struct
}

/**
 * search - Searches for a key in the hash table.
 * 
 * @param ht: A pointer to the hash table.
 * @param key: The key to search for.
 * @param hash_func: A pointer to the hash function to use.
 * 
 * Returns: The value associated with the key if found, otherwise -1.
 */
int search(HashTable* ht, const char* key, HashFunction hash_func) {
    if (!ht || !hash_func) {
        return -1; // Invalid hash table or hash function
    }
    uint32_t hash = hash_func(key) % ht->size;
    Node* current = ht->table[hash];

    while (current) {
        if (current->data.key == key) {
            return current->data.value; // Key found, return value
        }
        current = current->next; //
        // Continue searching in the linked list
    }
    return -1; // Key not found
}

/**
 * insert - Inserts a key-value pair into the hash table.
 * 
 * @param ht: A pointer to the hash table.
 * @param key: The key to insert.
 * @param value: The value associated with the key.
 * @param hash_func: A pointer to the hash function to use.
 * 
 * Returns: 0 on success, -1 on failure.
 */
int insert(HashTable* ht, const char* key, int value, HashFunction hash_func) {
    if (!ht || !hash_func) {
        return -1; // Invalid hash table or hash function
    }
    uint32_t hash = hash_func(key) % ht->size;
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return -1; // Memory allocation failed
    }
    new_node->data.key = key;
    new_node->data.value = value;
    new_node->next = ht->table[hash]; // Insert at the beginning of the linked list
    ht->table[hash] = new_node; // Update the head of the bucket
    return 0; // Insertion successful
}

/**
 * delete - Deletes a key from the hash table.
 * 
 * @param ht: A pointer to the hash table.
 * @param key: The key to delete.
 * @param hash_func: A pointer to the hash function to use.
 * 
 * Returns: 0 on success, -1 if the key was not found.
 */
int delete(HashTable* ht, const char* key, HashFunction hash_func) {
    if (!ht || !hash_func) {
        return -1; // Invalid hash table or hash function
    }
    uint32_t hash = hash_func(key) % ht->size;
    Node* current = ht->table[hash];
    Node* prev = NULL;
    while (current) {
        if (current->data.key == key) {
            if (prev) {
                prev->next = current->next; // Bypass the current node
            } else {
                ht->table[hash] = current->next; // Update head if first node
            }
            free(current); // Free the deleted node
            return 0; // Deletion successful
        }
        prev = current;
        current = current->next; // Continue searching in the linked list
    }
    return -1; // Key not found
}

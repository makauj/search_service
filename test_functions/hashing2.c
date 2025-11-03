#include "hash_table.h"
#include <stdint.h>
#include <string.h>

/**
 * hash - hashing function using MurmurHash algorithm
 * @str: input string to be hashed
 * 
 * Return: computed hash value as uint32_t
 */

uint32_t murmur_hash(const char *str)
{
    uint32_t hash = 5381;
    int c;

    if (str == NULL)
        return 0; // Handle null pointer

    while ((c = *str++))
    {
        hash ^= c; // XOR the current hash with the current character
        // XOR operation helps in mixing the bits
        hash *= 0x5bd1e995; // 0x5bd1e995 is a prime number
        // Multiplying by a prime number helps in spreading out the hash values
        hash ^= hash >> 15; // Mix the bits by shifting right by 15 bits
        // This helps in further reducing collisions
        // This is a common technique in hash functions to reduce collisions
    }
    return hash;
}

/**
 * create_table - create a hash table
 * @size: size of the hash table
 * 
 * Return: pointer to the created hash table
 */

HashTable* create_table(int size)
{
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht == NULL)
        return NULL; // Handle memory allocation failure
    ht->size = size; // Set the size of the hash table
    ht->table = (Node**)malloc(sizeof(Node*) * size);
    if (ht->table == NULL)
    {
        free(ht);
        return NULL; // Handle memory allocation failure
    }
    for (int i = 0; i < size; i++)
        ht->table[i] = NULL; // Initialize all buckets to NULL
    return ht;
}

/**
 * insert - insert a key-value pair into the hash table
 * @ht: pointer to the hash table
 * @key: key string
 * @value: value to be associated with the key
 * @hash_func: pointer to the hash function
 * 
 * Return: 0 on success, -1 on failure
 */
int insert(HashTable* ht, const char* key, int value, HashFunction hash_func)
{
    if (ht == NULL || key == NULL || hash_func == NULL)
        return -1; // Handle invalid parameters

    uint32_t hash = hash_func(key) % ht->size;
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
        return -1; // Handle memory allocation failure

    new_node->data.key = key;
    new_node->data.value = value;
    new_node->next = ht->table[hash]; // Insert at the beginning of the linked list
    ht->table[hash] = new_node; // Update the head of the bucket
    return 0; // Insertion successful
}

/**
 * search - search for a key in the hash table
 * @ht: pointer to the hash table
 * @key: key string to search for
 * @hash_func: pointer to the hash function
 * 
 * Return: value associated with the key, or -1 if not found
 */

int search(HashTable* ht, const char* key, HashFunction hash_func)
{
    if (ht == NULL || key == NULL || hash_func == NULL)
        return -1;

    uint32_t hash = hash_func(key) % ht->size; // Compute the hash index
    Node* current = ht->table[hash]; // Get the head of the bucket
    while (current != NULL)
    {
        if (current->data.key == key)
            return current->data.value; // Key found, return the value
        current = current->next; // Move to the next node in the linked list
        // Continue searching in the linked list
    }
    return -1; // Key not found
}

/**
 * delete - free memory allocated for hash table
 * @ht: pointer to the hash table
 * @key: key string to delete
 * @hash_func: pointer to the hash function
 * 
 * Return: 0 on success, -1 on failure
 */
int delete(HashTable* ht, int key, HashFunction hash_func)
{
    if (ht == NULL || hash_func == NULL)
        return -1;

    uint32_t hash = hash_func(key) % ht->size;
    Node* current = ht->table[hash];
    Node* prev = NULL;

    while (current != NULL)
    {
        if (current->data.key == key)
        {
            if (prev == NULL)
                ht->table[hash] = current->next;
            else
                prev->next = current->next;

            free(current);
            return 0; // Key found and deleted
        }
        prev = current;
        current = current->next;
    }
    return -1; // Key not found
}

/**
 * free_table - free memory allocated for hash table
 * @ht: pointer to the hash table
 */
void free_table(HashTable* ht)
{
    if (ht == NULL)
        return;
    for (int i = 0; i < ht->size; i++)
    {
        Node* current = ht->table[i];
        while (current != NULL)
        {
            Node* temp = current;
            current = current->next;
            free(temp); // Free the node
        }
    }
    free(ht->table); // Free the table array
    free(ht); // Free the hash table struct
}

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>

/**
 * This is a simple struct in C
 * It contains: a value key pair
 */
typedef struct KeyValue {
    int key;
    int value;
} KeyValue;

/**
 * this is a struct node
 * It contains: a pointer to the next node and a KeyValue struct
 */
typedef struct Node {
    KeyValue data;
    struct Node* next;
} Node;

/**
 * this is a struct hash table
 * It contains: an array of Node pointers and the size of the table
 */
typedef struct HashTable {
    Node** table;
    int size;
} HashTable;

/**
 * This is a typedef for uint32_t
 * It contains: an unsigned int value
 */
typedef struct uint32_t {
    unsigned int value;
} uint32_t;


typedef unsigned int (*HashFunction)(const char* str);
unsigned int simple_hash(const char* str);
unsigned int djb_hash(const char* str);
unsigned int sdbm_hash(const char* str);
unsigned int murmur_hash(const char* str);
HashTable* create_table(int size);
void free_table(HashTable* ht);
int insert(HashTable* ht, const char* key, int value, HashFunction hash_func);
int search(HashTable* ht, const char* key, HashFunction hash_func);
int delete(HashTable* ht, const char* key, HashFunction hash_func);

#endif // HASH_TABLE_H
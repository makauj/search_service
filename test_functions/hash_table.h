#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

typedef uint32_t (*HashFunction)(int key);

uint32_t simple_hash(const char* str);
uint32_t djb_hash(const char* str);
uint32_t sdbm_hash(const char* str);
uint32_t murmur_hash(const char* str);
HashTable* create_table(int size);
void free_table(HashTable* ht);
int insert(HashTable* ht, const char* key, int value, HashFunction hash_func);
int search(HashTable* ht, const char* key, HashFunction hash_func);
int delete(HashTable* ht, HashFunction hash_func);

#endif // HASH_TABLE_H
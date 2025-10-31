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

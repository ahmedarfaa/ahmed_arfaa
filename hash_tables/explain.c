#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Define a struct to represent a node in the linked list
typedef struct {
    char *key;
    char *value;
    struct node_s *next;
} node_t;

// Define a struct to represent the hash table
typedef struct {
    int size;
    node_t **array;
} hash_table_t;

// Hash function to map a key to an index in the hash table
int hash(char *key) {
    int sum = 0;
    for (int i = 0; i < strlen(key); i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Create a new node with the given key-value pair
node_t *create_node(char *key, char *value) {
    node_t *node = malloc(sizeof(node_t));
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

// Create a new hash table with the given size
hash_table_t *create_hash_table(int size) {
    hash_table_t *table = malloc(sizeof(hash_table_t));
    table->size = size;
    table->array = malloc(size * sizeof(node_t *));
    for (int i = 0; i < size; i++) {
        table->array[i] = NULL;
    }
    return table;
}

// Add a key-value pair to the hash table
void hash_table_set(hash_table_t *table, char *key, char *value) {
    int index = hash(key);
    node_t *node = create_node(key, value);
    if (table->array[index] == NULL) {
        table->array[index] = node;
    } else {
        node->next = table->array[index];
        table->array[index] = node;
    }
}

// Get the value associated with the given key from the hash table
char *hash_table_get(hash_table_t *table, char *key) {
    int index = hash(key);
    node_t *node = table->array[index];
    while (node!= NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

int main() {
    hash_table_t *table = create_hash_table(TABLE_SIZE);

    // Add some key-value pairs to the hash table
    hash_table_set(table, "apple", "red");
    hash_table_set(table, "banana", "yellow");
    hash_table_set(table, "cherry", "red");

    // Retrieve the values associated with some keys from the hash table
    char *value1 = hash_table_get(table, "apple");
    char *value2 = hash_table_get(table, "banana");
    char *value3 = hash_table_get(table, "cherry");

    printf("Value for key 'apple': %s\n", value1);
    printf("Value for key 'banana': %s\n", value2);
    printf("Value for key 'cherry': %s\n", value3);

    // Free the memory used by the hash table and its nodes
    for (int i = 0; i < TABLE_SIZE; i++) {
        node_t *node = table->array[i];
        while (node!= NULL) {
            node_t *next = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = next;
        }
    }
    free(table->array);
    free(table);

    return 0;
}
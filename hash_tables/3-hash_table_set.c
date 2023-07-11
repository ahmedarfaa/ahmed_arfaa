#include "hash_tables.h"

hash_node_t *create_node(const char *key, const char *value) {
    hash_node_t *node = malloc(sizeof(hash_node_t));
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
    int idx = key_index((const unsigned char *)key, ht->size);
    hash_node_t *node = create_node(key, value);

     if (ht->array[idx] == NULL) {
        ht->array[idx] = node;
    } else {
        node->next = ht->array[idx];
        ht->array[idx] = node;
    }
    return node->value;

}
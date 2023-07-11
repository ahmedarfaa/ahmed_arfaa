#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10;

typedef struct node_s
{
    const char *key;
    const char *value;
    struct node_s *next;
} node_t;

typedef struct table_s
{
    unsigned long int size;
    node_t **array;
} table_t;
table_t *create_table(unsigned long int size);

int set_node(table_t *tab, const char *key, const char *value);

int hash(const char *key);
node_t *create_node(const char *key, const char *value);

void get_print(table_t *tab);
void get_value(table_t *tab, const char *value);

void get_value(table_t *tab, const char *key)
{
    int idx = hash(key);
    node_t *node = tab->array[idx];
    while(node !=NULL)
    {
    if (strcmp(node->key, key) ==0)
    {
    printf("%s :%s\n",node->key, node->value);
    return;
    }
    node = node->next;
    idx++;
    }
    printf("not found\n");
}
void get_print(table_t *tab)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        node_t *node = tab->array[i];
        while (node!=NULL)
        {
        printf("%d :%s: %s\n", i, node->key, node->value);
        node = node->next;
        }
    }
}

node_t *create_node(const char *key, const char *value)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    return new_node;
}

int hash(const char *key)
{
    unsigned int i, sum = 0;

    for (i = 0; key[i] != '\0'; i++)
    {
        sum += key[i];
    }

    return sum % TABLE_SIZE;
}

int set_node(table_t *tab, const char *key, const char *value)
{
    int idx = hash(key);
    
    node_t *node = create_node(key, value);

    if (tab->array[idx] == NULL)
        tab->array[idx] = node;
    else
    {
        node->next = tab->array[idx];
        tab->array[idx] = node;
    }

    return 0;
}

table_t *create_table(unsigned long int size)
{
    table_t *tab = malloc(sizeof(table_t));
    unsigned long int i;
    tab->size = size;
    tab->array = malloc(sizeof(node_t *) * size);

    for (i = 0; i < size; i++)
    {
        tab->array[i] = NULL;
    }
    for (i = 0; i < size; i++)
    {
        if (tab->array[i] == NULL)
            printf("%lu: --\n", i);
    }

    return tab;
}

int main(void)
{
    unsigned long int size = 10;
    table_t *tb = create_table(size);

    set_node(tb, "mostafa", "29");
    set_node(tb, "ali", "55");
    set_node(tb, "arfaa", "77");
    set_node(tb, "ahmed", "27");
    set_node(tb, "roaa", "2");
    set_node(tb, "walaa", "20");
    set_node(tb, "walaa", "10");
    get_print(tb);

    printf("---------------\n");
    get_value(tb,"walaa");
    get_value(tb,"arfaa");
    get_value(tb,"mostafa");
    get_value(tb,"ali");
    get_value(tb, "kdj");
    return 0;
}
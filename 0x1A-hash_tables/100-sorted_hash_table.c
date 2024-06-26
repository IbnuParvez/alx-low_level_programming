#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tables.h"

/* djb2 hash function */
unsigned long int hash_djb2(const unsigned char *str)
{
    unsigned long int hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

/* Get the index of a key */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
    return hash_djb2(key) % size;
}

/* Create a sorted hash table */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *ht;
    unsigned long int i;

    ht = malloc(sizeof(shash_table_t));
    if (ht == NULL)
        return NULL;

    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    if (ht->array == NULL)
    {
        free(ht);
        return NULL;
    }
    for (i = 0; i < size; i++)
        ht->array[i] = NULL;

    ht->shead = NULL;
    ht->stail = NULL;

    return ht;
}

/* Insert a key/value pair into the sorted hash table */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    unsigned long int index;
    shash_node_t *new_node, *temp, *prev;

    if (ht == NULL || key == NULL || value == NULL)
        return 0;

    index = key_index((const unsigned char *)key, ht->size);
    temp = ht->array[index];

    /* Check if the key already exists */
    while (temp != NULL)
    {
        if (strcmp(temp->key, key) == 0)
        {
            free(temp->value);
            temp->value = strdup(value);
            return 1;
        }
        temp = temp->next;
    }

    /* Create a new node */
    new_node = malloc(sizeof(shash_node_t));
    if (new_node == NULL)
        return 0;
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    if (new_node->key == NULL || new_node->value == NULL)
    {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return 0;
    }
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    /* Insert into the sorted linked list */
    if (ht->shead == NULL)
    {
        new_node->sprev = NULL;
        new_node->snext = NULL;
        ht->shead = new_node;
        ht->stail = new_node;
    }
    else
    {
        temp = ht->shead;
        prev = NULL;
        while (temp != NULL && strcmp(temp->key, key) < 0)
        {
            prev = temp;
            temp = temp->snext;
        }
        new_node->snext = temp;
        new_node->sprev = prev;
        if (temp != NULL)
            temp->sprev = new_node;
        if (prev != NULL)
            prev->snext = new_node;
        if (ht->shead == temp)
            ht->shead = new_node;
        if (ht->stail == prev)
            ht->stail = new_node;
    }

    return 1;
}

/* Retrieve a value by key */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
    unsigned long int index;
    shash_node_t *node;

    if (ht == NULL || key == NULL)
        return NULL;

    index = key_index((const unsigned char *)key, ht->size);
    node = ht->array[index];
    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

/* Print the hash table in sorted order */
void shash_table_print(const shash_table_t *ht)
{
    shash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");
    node = ht->shead;
    while (node != NULL)
    {
        if (!first)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        first = 0;
        node = node->snext;
    }
    printf("}\n");
}

/* Print the hash table in reverse sorted order */
void shash_table_print_rev(const shash_table_t *ht)
{
    shash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");
    node = ht->stail;
    while (node != NULL)
    {
        if (!first)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        first = 0;
        node = node->sprev;
    }
    printf("}\n");
}

/* Delete the hash table */
void shash_table_delete(shash_table_t *ht)
{
    shash_node_t *node, *temp;

    if (ht == NULL)
        return;

    for (unsigned long int i = 0; i < ht->size; i++)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            temp = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = temp;
        }
    }
    free(ht->array);
    free(ht);
}


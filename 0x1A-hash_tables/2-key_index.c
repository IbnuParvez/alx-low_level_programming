#include "hash_tables.h"

/* Get the index of a key */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
    return hash_djb2(key) % size;
}

#include "get_next_line.h"

static void free_buf_node(t_buf_node *node)
{
    if (!node)
        return;
    free(node);
}

void cleanup_gnl_resources(t_hashtable *hashtable)
{
    int i;
    t_buf_node *curr;
    t_buf_node *next_node;

    if (!hashtable || !hashtable->initialized)
        return;

    i = 0;
    while (i < HASH_SIZE)
    {
        curr = hashtable->table[i].next;
        while (curr != NULL)
        {
            next_node = curr->next;
            free_buf_node(curr);
            curr = next_node;
        }
        hashtable->table[i].fd = -1;
        hashtable->table[i].next = NULL;
        i++;
    }
    hashtable->initialized = 0;
}
#include "lhset.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>

struct lhset *lhset_create()
{
    struct lhset *hs = (struct lhset *)malloc(sizeof(struct lhset));
    assert(hs != NULL);
	hs->ele_num=0;

    for(int i = 0; i < MAX_HASH_SLOT_NUM; i++)
    {
        TAILQ_INIT(&(hs->slots[i]));
    }
    return hs;
}


void lhset_destroy(struct lhset *hs)
{
	struct hnode *tmp = NULL;
    if(hs == NULL)
        return;
    
    for(int i = 0; i < MAX_HASH_SLOT_NUM; i++)
    {
        while((tmp = TAILQ_FIRST(&hs->slots[i])) != NULL)
        {
            TAILQ_REMOVE(&hs->slots[i], tmp, link);
            free(tmp);
        }
        assert(TAILQ_EMPTY(&hs->slots[i]));
    }
    free(hs);
}


static bool __search(struct lhset* hs, uint32_t key)
{
    assert(hs != NULL);
    int slot_index = key % MAX_HASH_SLOT_NUM;
    
    struct hnode *tmp = NULL;
    TAILQ_FOREACH(tmp, &hs->slots[slot_index], link)
    {
        if(tmp->key == key)
        {
            return true;
        }
    }
    return false;
}


bool lhset_search(struct lhset* hs, uint32_t key)
{
    return __search(hs, key);
}


int lhset_insert(struct lhset* hs, uint32_t key)
{
    assert(hs != NULL);
    if(__search(hs, key))
    {
        return -1;
    }

    struct hnode *node = (struct hnode *)malloc(sizeof(struct hnode));
    node->key = key;
    int slot_index = key % MAX_HASH_SLOT_NUM;
    TAILQ_INSERT_TAIL(&hs->slots[slot_index], node, link);
	hs->ele_num++;
    return 0;
}


int lhset_remove(struct lhset* hs, uint32_t key)
{
    assert(hs != NULL);
    int slot_index = key % MAX_HASH_SLOT_NUM;
    struct hnode *tmp = NULL;
    TAILQ_FOREACH(tmp, &hs->slots[slot_index], link)
    {
        if (tmp->key == key)
        {
            TAILQ_REMOVE(&hs->slots[slot_index], tmp, link);
			hs->ele_num--;
            free(tmp);
            return 0;
        }
    }
    return -1;
}

void lhset_traverse(struct lhset* hs, void(* traverse_cb)(uint32_t key, void* usr_arg), void* usr_arg)
{
    assert(hs != NULL);
    for(int i = 0; i < MAX_HASH_SLOT_NUM; i++)
    {
        if(TAILQ_EMPTY(&hs->slots[i]))
        {
            continue;
        }
        struct hnode *tmp = NULL;
        TAILQ_FOREACH(tmp, &hs->slots[i], link)
        {
            traverse_cb(tmp->key, usr_arg);
        }
    }
}

void lhset_to_array(struct lhset* hs, uint32_t* array, uint32_t size)
{
    assert(hs != NULL);
	assert(size >= hs->ele_num);
	int j = 0;
    for(int i = 0; i < MAX_HASH_SLOT_NUM; i++)
    {
        if(TAILQ_EMPTY(&hs->slots[i]))
        {
            continue;
        }
        struct hnode *tmp = NULL;
        TAILQ_FOREACH(tmp, &hs->slots[i], link)
        {
			array[j] = tmp->key;
			j++;
        }
    }
	assert(j <= size);
}

void lhset_print(struct lhset* hs)
{
    if(hs == NULL)
    {
        printf("NULL\n");
        return;
    }

    printf("[ ");
    for (int i = 0; i < MAX_HASH_SLOT_NUM; i++)
    {
        if (TAILQ_EMPTY(&hs->slots[i]))
        {
            continue;
        }
        struct hnode *tmp = NULL;
        TAILQ_FOREACH(tmp, &hs->slots[i], link)
        {
            printf("%"PRIu32" ", tmp->key);
        }
    }
    printf(" ]\n");
}

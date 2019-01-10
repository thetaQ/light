#ifndef __LIGHT_HSET_H__
#define __LIGHT_HSET_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <sys/queue.h>
#include <stdbool.h>

#define MAX_HASH_SLOT_NUM (4*1024*1024)

struct hnode
{
    uint32_t            key;
    TAILQ_ENTRY(hnode)  link;
};

struct lhset
{
    TAILQ_HEAD(, hnode) slots[MAX_HASH_SLOT_NUM];
	int ele_num;
};


/* API */
struct lhset *lhset_create();
void lhset_destroy(struct lhset *hs);
bool lhset_search(struct lhset *hs, uint32_t key);
int lhset_insert(struct lhset *hs, uint32_t key);
int lhset_remove(struct lhset *hs, uint32_t key);
void lhset_traverse(struct lhset *hs, void (*traverse_cb)(uint32_t key, void *usr_arg), void *usr_arg);
void lhset_to_array(struct lhset* hs, uint32_t* array, uint32_t size);
/* for debug */
void lhset_print(struct lhset *hs);


#ifdef __cplusplus
}
#endif
#endif

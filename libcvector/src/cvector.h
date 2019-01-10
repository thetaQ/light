#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdbool.h>


struct cvector
{
    size_t capacity;
    size_t elem_num;
    size_t elem_size;
    void(*free_cb)(void *);
    void *elem;
};


struct cvector *cvector_new(size_t elem_num, size_t elem_size, void (*free_cb)(void *));
void cvector_destroy(struct cvector *cv);
bool cvector_get(struct cvector *cv, size_t index, void *elem);
bool cvector_remove(struct cvector *cv, size_t index, void *elem);
bool cvector_add(struct cvector *cv, void *elem);
bool cvector_insert(struct cvector *cv, size_t index, void *elem);
void *cvector_to_array(struct cvector *cv);
size_t cvector_size(struct cvector *cv);


#ifdef __cplusplus
  }
#endif

#endif

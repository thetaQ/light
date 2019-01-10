#include "cvector.h"
#include <stdlib.h>
#include <string.h>

#define ELEM(v, i) ((char *)((v)->elem) + (i) * ((v)->elem_size))

static bool isbrim(struct cvector *cv)
{
    if(cv == NULL)
        return false;
    return cv->elem_num == cv->capacity ? true : false;
}


static bool grow(struct cvector *cv)
{
    if(cv == NULL)
        return false;
    size_t new_capacity = cv->capacity * 2;
    void *new_elems = realloc(cv->elem, new_capacity * cv->elem_size);
    if (new_elems == NULL)
        return false;
    cv->capacity = new_capacity;
    cv->elem = new_elems;
    return true;
}


struct cvector *cvector_new(size_t elem_num, size_t elem_size, void(*free_cb)(void *))
{
    struct cvector *cv = (struct cvector *)calloc(1, sizeof(struct cvector));
    if(cv == NULL)
    {
        return NULL;
    }

    cv->capacity = elem_num;
    cv->elem_num = 0;
    cv->elem_size = elem_size;
    cv->free_cb = free_cb;
    cv->elem = malloc(elem_num * elem_size);
    if(cv->elem == NULL)
    {
        free(cv);
        return NULL;
    }
    return cv;
}


void cvector_destroy(struct cvector *cv)
{
    if(cv == NULL)
        return;
    if(cv->free_cb != NULL)
    {
        int i = 0;
        for(; i < cv->elem_num; i++)
        {
            cv->free_cb(*(void **)ELEM(cv, i));
        }
    }
    free(cv->elem);
    free(cv);
}


bool cvector_get(struct cvector *cv, size_t index, void *elem)
{
    if (cv == NULL || index >= cv->elem_num || elem == NULL)
    {
        return false;
    }
    memcpy(elem, ELEM(cv, index), cv->elem_size);
    return true;
}


bool cvector_remove(struct cvector *cv, size_t index, void *elem)
{
    if(cv == NULL || index >= cv->elem_num)
    {
        return false;
    }
    if(elem != NULL)
    {
        memcpy(elem, ELEM(cv, index), cv->elem_size);
    }
    else if(cv->free_cb != NULL)
    {
        cv->free_cb(*(void **)(ELEM(cv, index)));
    }
    memmove(ELEM(cv, index), ELEM(cv, index + 1), (cv->elem_num-- - index + cv->elem_size));
    return true;
}


bool cvector_add(struct cvector *cv, void *elem)
{
    if (cv == NULL)
        return false;
    if(isbrim(cv) && !grow(cv))
        return false;
    memcpy(ELEM(cv, cv->elem_num++), elem, cv->elem_size);
    return true;
}


bool cvector_insert(struct cvector *cv, size_t index, void *elem)
{
    if(cv == NULL || index >= cv->elem_num)
        return false;
    if(isbrim(cv) && !grow(cv))
        return false;
    memmove(ELEM(cv, index+1), ELEM(cv, index), (cv->elem_num++ - index + cv->elem_size));
    memcpy(ELEM(cv, index), elem, cv->elem_size);
    return true;
}


void *cvector_to_array(struct cvector *cv)
{
    if(cv == NULL)
        return NULL;
    return cv->elem;
}


size_t cvector_size(struct cvector *cv)
{
    if(cv == NULL)
        return 0;
    return cv->elem_num;
}

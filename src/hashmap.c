#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

#define HM_INIT_CAP 16 /* 初始桶数，2^m*/

typedef struct Entry
{
    char *key; /* 键 */
    void *value;
    size_t hash;
    struct Entry *next; /* 冲突链 */
} Entry;

struct HashMap
{
    Entry **buckets;
    size_t capacity; /* 2 的幂 */
    size_t size;
};

/* FNV-1a 64 位哈希 */
static size_t hash_string(const char *s)
{
    size_t h = (size_t)1469598103934665603ULL;
    while (*s)
    {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }
    return h;
}

static char *dup_string(const char *s)
{
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (p)
        memcpy(p, s, n);
    return p;
}

HashMap *hashmap_create(void)
{
    HashMap *m = calloc(1, sizeof *m);
    if (!m)
        return NULL;
    m->capacity = HM_INIT_CAP;
    m->buckets = calloc(m->capacity, sizeof *m->buckets);
    if (!m->buckets)
    {
        free(m);
        return NULL;
    }
    return m;
}

void hashmap_destroy(HashMap *m, void (*free_value)(void *))
{
    if (!m)
        return;
    for (size_t i = 0; i < m->capacity; i++)
    {
        Entry *e = m->buckets[i];
        while (e)
        {
            Entry *next = e->next;
            if (free_value)
                free_value(e->value);
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(m->buckets);
    free(m);
}

static int hashmap_resize(HashMap *m, size_t newcap)
{
    Entry **nb = calloc(newcap, sizeof *nb);
    if (!nb)
        return -1;

    for (size_t i = 0; i < m->capacity; i++)
    {
        Entry *e = m->buckets[i];
        while (e)
        {
            Entry *next = e->next;
            size_t idx = e->hash & (newcap - 1);
            e->next = nb[idx];
            nb[idx] = e;
            e = next;
        }
    }
    free(m->buckets);
    m->buckets = nb;
    m->capacity = newcap;
    return 0;
}

int hashmap_put(HashMap *m, const char *key, void *value, void **old_value)
{
    size_t h = hash_string(key);
    size_t idx = h & (m->capacity - 1);

    for (Entry *e = m->buckets[idx]; e; e = e->next)
    {
        if (e->hash == h && strcmp(e->key, key) == 0)
        {
            if (old_value)
                *old_value = e->value;
            e->value = value;
            return 0;
        }
    }

    /* 负载因子 over 3/4 时 extends */
    if ((m->size + 1) * 4 > m->capacity * 3)
    {
        if (hashmap_resize(m, m->capacity * 2) != 0)
            return -1;
        idx = h & (m->capacity - 1);
    }

    Entry *e = malloc(sizeof *e);
    if (!e)
        return -1;
    e->key = dup_string(key);
    if (!e->key)
    {
        free(e);
        return -1;
    }

    e->value = value;
    e->hash = h;
    e->next = m->buckets[idx];
    m->buckets[idx] = e;
    m->size++;

    if (old_value)
        *old_value = NULL;
    return 0;
}

void *hashmap_get(const HashMap *m, const char *key)
{
    size_t h = hash_string(key);
    size_t idx = h & (m->capacity - 1);

    for (Entry *e = m->buckets[idx]; e; e = e->next)
        if (e->hash == h && strcmp(e->key, key) == 0)
            return e->value;
    return NULL;
}

int hashmap_contains(const HashMap *m, const char *key)
{
    size_t h = hash_string(key);
    size_t idx = h & (m->capacity - 1);

    for (Entry *e = m->buckets[idx]; e; e = e->next)
        if (e->hash == h && strcmp(e->key, key) == 0)
            return 1;
    return 0;
}

int hashmap_remove(HashMap *m, const char *key, void **old_value)
{
    size_t h = hash_string(key);
    size_t idx = h & (m->capacity - 1);

    Entry **pp = &m->buckets[idx];
    while (*pp)
    {
        Entry *e = *pp;
        if (e->hash == h && strcmp(e->key, key) == 0)
        {
            *pp = e->next;
            if (old_value)
                *old_value = e->value;
            free(e->key);
            free(e);
            m->size--;
            return 1;
        }
        pp = &e->next;
    }
    return 0;
}

size_t hashmap_size(const HashMap *m)
{
    return m->size;
}

void hashmap_foreach(const HashMap *m,
                     void (*fn)(const char *, void *, void *), void *ctx)
{
    if (!m || !fn)
        return;
    for (size_t i = 0; i < m->capacity; i++)
        for (Entry *e = m->buckets[i]; e; e = e->next)
            fn(e->key, e->value, ctx);
}
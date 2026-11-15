#ifndef HASHMAP_H
#define HASHMAP_H

// I love hash map

#include <stddef.h>

/* 不透明类型，外部看不到内部结构 */
typedef struct HashMap HashMap;

HashMap *hashmap_create(void);
void hashmap_destroy(HashMap *m, void (*free_value)(void *));

/* 返回 0 成功，-1 失败（内存不足）。
 * 若键已存在则覆盖；old_value 非 NULL 时带回旧值（新增时为 NULL）。 */
int hashmap_put(HashMap *m, const char *key, void *value, void **old_value);

void *hashmap_get(const HashMap *m, const char *key);
int hashmap_contains(const HashMap *m, const char *key);

/* 返回 1 表示删除成功，0 表示键不存在 */
int hashmap_remove(HashMap *m, const char *key, void **old_value);

size_t hashmap_size(const HashMap *m);

void hashmap_foreach(const HashMap *m,
                     void (*fn)(const char *key, void *value, void *ctx),
                     void *ctx);

#endif
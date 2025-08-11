#ifndef SAFE_MEMORY_H
#define SAFE_MEMORY_H

#include <stdlib.h>

#define safe_malloc(size) _safe_malloc(size, __FILE__, __LINE__)
void *_safe_malloc(size_t size, const char *file, int line);

#define safe_calloc(nmemb, size) _safe_calloc(nmemb, size, __FILE__, __LINE__)
void *_safe_calloc(size_t nmemb, size_t size, const char *file, int line);

#define safe_realloc(ptr, size) _safe_realloc(ptr, size, __FILE__, __LINE__)
void *_safe_realloc(void *ptr, size_t size, const char *file, int line);

#endif // SAFE_MEMORY_H

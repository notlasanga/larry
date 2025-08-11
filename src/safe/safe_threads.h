#ifndef SAFE_THREADS_H
#define SAFE_THREADS_H

#include <pthread.h>

#define safe_pthread_create(thread, attr, start_routine, arg) _safe_pthread_create(thread, attr, start_routine, arg, __FILE__, __LINE__)
void _safe_pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg, const char *file, int line);

#define safe_pthread_join(thread, retval) _safe_pthread_join(thread, retval, __FILE__, __LINE__)
void _safe_pthread_join(pthread_t thread, void **retval, const char *file, int line);

#endif // SAFE_THREADS_H

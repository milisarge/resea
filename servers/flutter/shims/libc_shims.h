#ifndef __LIBC_SHIMS_H__
#define __LIBC_SHIMS_H__

// task_t
typedef unsigned long int pthread_t;
// unused
typedef void pthread_attr_t;
// 1-origin integer
typedef unsigned int pthread_key_t;

/// The first 4 bytes (sizeof(int)) are initialized by zeros in glibc.
#define PTHREAD_MUTEX_INITIALIZER 0
#define PTHREAD_MUTEX_UNLOCKED    0
#define PTHREAD_MUTEX_LOCKED      1

/// glibc's pthread_mutex_t is larger than sizeof(int).
typedef int pthread_mutex_t;

/// unused
typedef void pthread_mutexattr_t;
#endif

#ifndef __LIBC_SHIMS_H__
#define __LIBC_SHIMS_H__

// task_t
typedef unsigned long int pthread_t;
// unused
typedef char pthread_attr_t;
// 1-origin integer
typedef unsigned int pthread_key_t;

#endif

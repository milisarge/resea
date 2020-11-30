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
typedef void pthread_cond_t;

struct stat64 {
    unsigned long st_dev;
    unsigned long st_ino;
    unsigned long st_nlink;
    unsigned st_mode;
    unsigned st_uid;
    unsigned st_gid;
    unsigned __pad0;
    unsigned long st_rdev;
    long st_size;
    // TODO: Add remaining fields.
} __packed;

#define S_IFREG   0100000
#define S_IFDIR   0040000

# define AT_FDCWD -100

#endif

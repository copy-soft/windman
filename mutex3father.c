#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OKTOWRITE "/condwrite"
#define MESSAGE "/msg"
#define MUTEX "/mutex_lock"

int main(int argc, char *argv[])
{
    pthread_cond_t* condition;
    pthread_mutex_t* mutex;
    char* message;
    int des_cond, des_msg, des_mutex;
    int mode = S_IRWXU | S_IRWXG;

    des_mutex = shm_open(MUTEX, O_CREAT | O_RDWR | O_TRUNC, mode);

    if (des_mutex < 0) {
        perror("failure on shm_open on des_mutex");
        exit(1);
    }

    if (ftruncate(des_mutex, sizeof(pthread_mutex_t)) == -1) {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        exit(-1);
    }

    mutex = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t),
            PROT_READ | PROT_WRITE, MAP_SHARED, des_mutex, 0);

    if (mutex == MAP_FAILED ) {
        perror("Error on mmap on mutex\n");
        exit(1);
    }

    des_cond = shm_open(OKTOWRITE, O_CREAT | O_RDWR | O_TRUNC, mode);

    if (des_cond < 0) {
        perror("failure on shm_open on des_cond");
        exit(1);
    }

    if (ftruncate(des_cond, sizeof(pthread_cond_t)) == -1) {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        exit(-1);
    }

    condition = (pthread_cond_t*) mmap(NULL, sizeof(pthread_cond_t),
            PROT_READ | PROT_WRITE, MAP_SHARED, des_cond, 0);

    if (condition == MAP_FAILED ) {
        perror("Error on mmap on condition\n");
        exit(1);
    }

    /* HERE WE GO */
    /**************************************/

        /* set mutex shared between processes */
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutex, &mutexAttr);

    /* set condition shared between processes */
    pthread_condattr_t condAttr;
    pthread_condattr_init(&condAttr);
    pthread_condattr_setpshared(&condAttr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(condition, &condAttr);

    /*************************************/


    printf("father waits on condition\n");

     pthread_mutex_lock(mutex);
     pthread_cond_wait(condition, mutex);
     pthread_mutex_unlock(mutex);

     printf("Signaled by son process, wake up!!!!!!!!\n");

    pthread_condattr_destroy(&condAttr);
    pthread_mutexattr_destroy(&mutexAttr);
    pthread_mutex_destroy(mutex);
    pthread_cond_destroy(condition);

    shm_unlink(OKTOWRITE);
    shm_unlink(MESSAGE);
    shm_unlink(MUTEX);

    exit(0);
}


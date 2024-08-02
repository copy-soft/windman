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

    des_mutex = shm_open(MUTEX, O_CREAT | O_RDWR, mode);

    if (des_mutex < 0) {
        perror("failure on shm_open on des_mutex");
        exit(1);
    }

    mutex = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t),
            PROT_READ | PROT_WRITE, MAP_SHARED, des_mutex, 0);

    if (mutex == MAP_FAILED ) {
        perror("Error on mmap on mutex\n");
        exit(1);
    }

    des_cond = shm_open(OKTOWRITE, O_CREAT | O_RDWR, mode);

    if (des_cond < 0) {
        perror("failure on shm_open on des_cond");
        exit(1);
    }

    condition = (pthread_cond_t*) mmap(NULL, sizeof(pthread_cond_t),
            PROT_READ | PROT_WRITE, MAP_SHARED, des_cond, 0);

    if (condition == MAP_FAILED ) {
        perror("Error on mmap on condition\n");
        exit(1);
    }

    pthread_mutex_lock(mutex);
    pthread_cond_signal(condition);
    printf("son signaled\n");
    pthread_mutex_unlock(mutex);
    exit(0);
}

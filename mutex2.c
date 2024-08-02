#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct shared {
    pthread_mutex_t mutex;
    int sharedResource;
};

int main()
{
    int fd = shm_open("/foo", O_CREAT | O_TRUNC | O_RDWR, 0600);
    ftruncate(fd, sizeof(struct shared));

    struct shared *p = (struct shared*)mmap(0, sizeof(struct shared),
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    p->sharedResource = 0;

    // Make sure it can be shared across processes
    pthread_mutexattr_t shared;
    pthread_mutexattr_init(&shared);
    pthread_mutexattr_setpshared(&shared, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&(p->mutex), &shared);

    int i;
    for (i = 0; i < 100; i++) {
        pthread_mutex_lock(&(p->mutex));
        printf("%d\n", p->sharedResource);
        pthread_mutex_unlock(&(p->mutex));
        sleep(1);
    }

    munmap(p, sizeof(struct shared*));
    shm_unlink("/foo");
}

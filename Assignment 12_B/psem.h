#ifndef PSEM_H
#define PSEM_H

#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

typedef struct {
    sem_t *sem;
    char name[32];
} psem_t;

void psem_init(psem_t *psem, const char *name, unsigned int value) {
    snprintf(psem->name, sizeof(psem->name), "/%s", name);
    psem->sem = sem_open(psem->name, O_CREAT, 0644, value);
    if (psem->sem == SEM_FAILED) {
        if (errno == EEXIST) {
            psem->sem = sem_open(psem->name, 0);
        } else {
            perror("sem_open failed");
        }
    }
}

void psem_wait(psem_t *psem) {
    sem_wait(psem->sem);
}

void psem_post(psem_t *psem) {
    sem_post(psem->sem);
}

void psem_destroy(psem_t *psem) {
    sem_close(psem->sem);
    sem_unlink(psem->name);
}

#endif

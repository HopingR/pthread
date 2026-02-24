#include <stdio.h>
#include <pthread.h>

// Thread function
void* worker(void* arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t tid;

    // Create thread
    pthread_create(&tid, NULL, worker, NULL);

    // Wait for thread to finish
    pthread_join(tid, NULL);

    printf("Back in main thread.\n");
    return 0;
}
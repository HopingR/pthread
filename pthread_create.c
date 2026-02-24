#include <stdio.h>
#include <pthread.h> // POSIX threads library (for pthread functions)

// Thread function
void* worker(void* arg) {
    printf("Hello from thread!\n"); // Print message from the new thread
    return NULL;
}

int main() {
    pthread_t tid; // Declare a variable to store the thread ID (thread handle)

    // Create thread
    pthread_create(&tid, NULL, worker, NULL);

    // Wait for thread to finish
    pthread_join(tid, NULL);

    printf("Back in main thread.\n");
    return 0;

}

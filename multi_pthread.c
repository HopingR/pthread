/*
mutex (Mutual Exclusion lock): Allow only ONE thread at a time to enter a critical section of code that accesses shared data.
pthread_mutex_t lock; // Declare a mutex variable (shared by all threads)
pthread_mutex_lock(&lock); // Critical section: Only one thread may pass this point at a time (e.g., counter, *p)

counter++ is NOT atomic: Load->Add->Store{Mutex ensures those 3 steps happen without interruption.}
**** Mutex provides:Mutual exclusion, Synchronization, Race condition prevention,Memory visibility guarantees

lock/unlock and run ie. pthread_mutex_lock(&lock) [ comment demo]
./pth_hello 10000
Final counter = 9843
Expected = 10000
Because of lost updates/updates to the shared variables were not done safely, so some increments were lost

int id = *(int*)ar--> That id variable lives on:That thread’s private stack
pthreads are same-process threads-->They share memory and resources of the process
They are lighter weight than processes (less overhead)
 pthread_t threads[n];   // Dynamic thread array
    int ids[n];             // Thread IDs , local variables inside main(). They are stored on the main thread's stack. 
    They are not shared between threads. Each thread gets its own copy of these variables on its own stack. 
    // The worker thread accesses its ID through the pointer passed to it, which points to the corresponding element
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Shared (process-wide) data
int counter = 0;                 // GLOBAL -> shared by all threads
int *p = NULL;                   // HEAP pointer -> shared by all threads
pthread_mutex_t lock;            // MUTEX -> shared by all threads

// Thread function
void* worker(void* arg) {
    int id = *(int*)arg;         // id is LOCAL -> on this thread's stack

    // Lock before touching shared data (counter, *p)
    pthread_mutex_lock(&lock); // cmment this line and run large thread count(10000) update lost in shared data/memory

    counter++;                   // safe shared update
    (*p) += 10;                  // safe shared heap update

    printf("Thread %d is running | counter=%d | *p=%d\n", id, counter, *p);

    pthread_mutex_unlock(&lock); //comment this line and run large thread count(10000)

    return NULL;
}

int main(int argc, char *argv[]) {
    // Check if user provided thread count
    if (argc != 2) {
        printf("Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please provide a positive number of threads.\n");
        return 1;
    }

    // Allocate shared heap memory
    p = (int*)malloc(sizeof(int));
    if (!p) {
        perror("malloc failed");
        return 1;
    }
    *p = 0;

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        free(p);
        return 1;
    }

    pthread_t threads[n];
    int ids[n];

    // Create threads
    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll %d threads finished.\n", n);
    printf("Final counter = %d (should be %d)\n", counter, n);
    printf("Final *p      = %d (should be %d)\n", *p, 10 * n);

    // Cleanup
    pthread_mutex_destroy(&lock); // Destroys mutex after use
    free(p); // free heap memory

    return 0;
}

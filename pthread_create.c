/*
initial thread (main thread)-->Only ONE thread exists → main thread
Begins at main()--> The main thread stack is created
Local variable: pthread_t tid-->is stored on main thread’s stack.
pthread_create() is Called:
Allocates a new stack for new thread
Allocates thread control block (TCB)
Initializes registers for new thread
New thread starts executing at worker() function    
Two threads exist:
- Main thread
- Worker thread
After pthread_create() returns:

Two threads can run independently

Without pthread_join, main might exit before worker prints. Main thread waits

It blocks until worker finishes, It cannot continue until worker exits
This ensures:
✔ Worker prints first
✔ No early exit of process
Worker Finishes
When worker returns--> OS marks thread as: TERMINATED
Resources are cleaned. Now pthread_join() unblocks

pthread.h library--> Include the POSIX Thread (Pthreads) API definitions." without, it throw error in compilation.error: unknown type name 'pthread_t',
It provides declarations (not implementations) of thread-related functions and types [demo]

pthread Data Types:
pthread_t  //handle to a thread.Internally (implementation-dependent), it may store: A numeric ID, A pointer to thread control block, Without pthread_t, can't track the thread.
pthread_attr_t
pthread_mutex_t
pthread_cond_t

pthread Functions:
int pthread_create(...) //Creates a new thread that executes a specified function.
int pthread_join(...) //pthread_join() waits for a specific thread to terminate. It blocks the calling thread (here: main thread)
int pthread_exit(...) //Terminates the calling thread.
int pthread_cancel(...) //Requests cancellation of a thread.
Time: O(1)--> Because the number of operations does not grow with input size
*/

#include <stdio.h>
#include <pthread.h> // POSIX threads library (for pthread functions)

// Thread function
void* worker(void* arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t tid; //Declare a variable to store the thread ID (thread handle)

    // Create thread
    pthread_create(&tid, NULL, worker, NULL); //O(1)

    // Wait for thread to finish
    pthread_join(tid, NULL);

    printf("Back in main thread.\n");
    return 0;
}


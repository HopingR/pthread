#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker(void* arg) {
    // Enable cancellation (default, but explicit for learning)
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    // Deferred cancellation (default): cancels only at cancellation points
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    while (1) {
        printf("Worker: running...\n");

        // Explicit cancellation point
        pthread_testcancel();

        // sleep() is also a cancellation point on POSIX systems
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t t;

    pthread_create(&t, NULL, worker, NULL);

    sleep(3); // let worker run a bit

    printf("Main: requesting cancellation...\n");
    pthread_cancel(t);

    // Join to reclaim resources and learn if it was canceled
    void* ret = NULL;
    pthread_join(t, &ret);

    if (ret == PTHREAD_CANCELED) {
        printf("Main: worker was canceled.\n");
    } else {
        printf("Main: worker exited normally.\n");
    }

    return 0;
}

# concurrency_synchronization
Mastering concurrent programming in C through multithreading, synchronization, shared resource management, and scheduling with POSIX threads

# Memory in C

    <The text segment> is usually read-only and stored in the lower part of the memory to prevent accidental modification of the code while the program is running.

    <The initialized data segment> is a type of data segment that stores the global and static variables created by the programmer.

    <The BSS segment> contains all the global and static variables that are not explicitly initialized by the programmer (or initialized with 0). Since the values of these variables can be modified during program execution, the BSS segment has read-write permission.
    
    <The heap> area begins at the end of the BSS segment and grows upward toward higher memory addresses. It is the memory segment used for dynamic memory allocation during program execution. Whenever additional memory is required, functions like malloc() and calloc() allocate space from the heap, causing it to grow upward.

    <The stack> is used to manage function calls and local variables. Each time a function is called, a stack frame is created, which stores the function’s local variables, parameters, and return address. When the function finishes, its stack frame is removed, following the LIFO principle.

# P_thread
    Stands for POSIX THREAD
    is a C library that allowed us the create multiples threads
    The thread argument points to a buffer of type pthread_t into which the unique identifier for this thread is copied before pthread_create() returns. This identifier can be used in later Pthreads calls to refer to the thread.
    The pthread_exit() function terminates the calling thread, and specifies a return value that can be obtained in another thread by calling pthread_join().
    The key difference between threads and processes is the easier sharing of information that threads provide, and this is the main reason that some application designs map better onto a multithread design than onto a multiprocess design.

    *terminated thread*: we must ensure that a normally terminating thread does not return an integer whose value matches PTHREAD_CANCELED on that Pthreads implementation.

# Mutex
    pthread_mutex_init() fills the memory occupied by the pthread_mutex_t object with whatever internal data the pthread library needs to make it a valid mutex
    When an automatically or dynamically allocated mutex is no longer required, it should be destroyed using pthread_mutex_destroy()
    It is safe to destroy a mutex only when it is unlocked, and no thread will subsequently try to lock it
    An automatically allocated mutex should be destroyed before its host function returns
    A mutex that has been destroyed with pthread_mutex_destroy() can subsequently be reinitialized by pthread_mutex_init()

    

Phase 1: Project skeleton
Phase 2: Argument parser
Phase 3: Initialization
Phase 4: Time functions
Phase 5: Logger
Phase 6: Heap (Priority Queue)
Phase 7: Threads
Phase 8: Dongles
Phase 9: Scheduler (FIFO)
Phase 10: Scheduler (EDF)
Phase 11: Monitor
Phase 12: Cleanup\

Process

│

├── Machine instructions

├── Heap

├── Stack

├── Global variables

├── Open files

├── Environment variables

├── File descriptors

├── Registers

└── One thread (initially)


concurrency: one thread swich between tasks
parallelism: multi cores has multi threads that excute at the smae time

If all threads only read the data and nobody modifies it, there is no race condition. The problem appears when one or more threads can write to shared data while others access it.
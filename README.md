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
Phase 12: Cleanup
# Codexion

*This project has been created as part of the 42 curriculum by FALAMLIH*

## Description

Codexion is a concurrency and synchronization project written in C using POSIX threads.

The project simulates multiple coders working concurrently. Each coder is represented by a thread and needs two shared resources called **dongles** to compile.

The main goal is to learn how to manage multiple threads safely while preventing:

* Data races
* Deadlocks
* Starvation
* Race conditions
* Incorrect resource access

The project also implements two scheduling algorithms:

* **FIFO** — First In, First Out
* **EDF** — Earliest Deadline First

A monitor thread checks the coders and detects burnout.

---

## Instructions

Compile the project:

```bash
make
```

Run the program:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Example:

```bash
./codexion 3 315 100 100 100 2 5 edf
```

The arguments are:

| Argument                      | Description                           |
| ----------------------------- | ------------------------------------- |
| `number_of_coders`            | Number of coder threads               |
| `time_to_burnout`             | Maximum time before a coder burns out |
| `time_to_compile`             | Compilation duration                  |
| `time_to_debug`               | Debugging duration                    |
| `time_to_refactor`            | Refactoring duration                  |
| `number_of_compiles_required` | Required number of compilations       |
| `dongle_cooldown`             | Dongle cooldown time                  |
| `scheduler`                   | `fifo` or `edf`                       |

### Make commands

```bash
make
```

Compile the project.

```bash
make clean
```

Remove object files.

```bash
make fclean
```

Remove object files and the executable.

```bash
make re
```

Clean and rebuild the project.

---

# Concurrency

Concurrency means that several tasks can make progress during overlapping periods of time.

In this project, every coder is a thread:

```text
Coder 1 → Thread
Coder 2 → Thread
Coder 3 → Thread
```

All threads belong to the same process and share memory.

Because they share resources, synchronization is required.

---

# Threads

Codexion uses POSIX threads (`pthread`).

The main functions used are:

```c
pthread_create()
pthread_join()
pthread_exit()
```

`pthread_create()` creates a new thread.

`pthread_join()` waits for a thread to finish.

`pthread_exit()` terminates the calling thread.

---

# Mutexes

A mutex allows only one thread at a time to access protected data.

The main functions are:

```c
pthread_mutex_init()
pthread_mutex_lock()
pthread_mutex_unlock()
pthread_mutex_destroy()
```

For example:

```c
pthread_mutex_lock(&coder->mutex_coder);

/* access shared data */

pthread_mutex_unlock(&coder->mutex_coder);
```

Mutexes are used to protect shared resources such as:

* Coder state
* Dongles
* Scheduler data
* System state
* Logs

A mutex must not be destroyed while it is still being used.

---

# Condition Variables

Condition variables allow threads to wait until something changes.

The main functions are:

```c
pthread_cond_init()
pthread_cond_wait()
pthread_cond_signal()
pthread_cond_broadcast()
pthread_cond_destroy()
```

`pthread_cond_wait()` releases the associated mutex while the thread waits.

When the thread wakes up, it automatically reacquires the mutex before returning.

This allows coders to wait for scheduler/resource changes without continuously checking in a loop.

---

# Scheduler

Codexion supports two scheduling algorithms.

## FIFO

FIFO means **First In, First Out**.

The coder that enters the queue first gets priority first.

```text
Coder 1 → Coder 2 → Coder 3
   ↓
First
```

## EDF

EDF means **Earliest Deadline First**.

The coder with the earliest deadline gets priority.

```text
Coder 1 → deadline 500
Coder 2 → deadline 200
Coder 3 → deadline 350
```

The order is:

```text
Coder 2 → Coder 3 → Coder 1
```

EDF uses a priority queue implemented with a binary min-heap.

---

# Heap

The heap is used by the EDF scheduler.

The smallest deadline is kept at the top of the heap.

Main operations:

```text
heap_init()
heap_insert()
heap_pop()
heap_destroy()
```

The main operations have:

* Insert: `O(log n)`
* Pop: `O(log n)`
* Get minimum: `O(1)`

---

# Monitor

The monitor is a separate thread that checks the coders.

It checks information such as:

* Last successful compilation
* Number of compilations
* Burnout time

The monitor uses the coder mutex when reading shared coder data.

This prevents it from reading data while another thread is modifying it.

When a coder burns out, the monitor requests the system to stop.

---

# Blocking Cases Handled

## Deadlock

A deadlock happens when threads wait for resources held by each other.

For example:

```text
Coder 1 → owns Dongle 1 → waits for Dongle 2
Coder 2 → owns Dongle 2 → waits for Dongle 1
```

Codexion prevents this by controlling the order in which dongles are acquired.

Using a consistent dongle order prevents circular waiting.

## Starvation

Starvation happens when a coder waits for a very long time because other coders continuously get the resources first.

The scheduler controls the order in which coders receive resources.

FIFO provides an arrival-based order, while EDF prioritizes the coder with the earliest deadline.

## Race Conditions

A race condition happens when multiple threads access shared data at the same time and at least one of them modifies it.

Shared data is protected with mutexes.

## Dongle Cooldown

After a dongle is released, the configured cooldown time must be respected before it can be used again.

## Burnout Detection

The monitor checks the time since the coder's last successful compilation.

The coder state is protected by a mutex while it is being read.

## Log Serialization

Multiple threads can print at the same time.

A dedicated print mutex ensures that log messages do not overlap.

---

# Thread Synchronization Mechanisms

Codexion mainly uses:

### `pthread_mutex_t`

Used to protect shared data and resources.

Examples:

```text
Coder state
Dongles
Scheduler
System stop state
Logging
```

### `pthread_cond_t`

Used for communication between threads and for waiting until scheduler conditions change.

### Scheduler synchronization

The scheduler protects its queue/heap so that multiple coder threads cannot modify it simultaneously.

### Monitor synchronization

Coder threads update their state while the monitor reads it.

A mutex ensures that these operations are synchronized.

Example:

```text
Coder thread
     │
     │ updates state
     ▼
  Mutex
     ▲
     │ reads state
     │
 Monitor thread
```

# Process and Threads

A process contains resources such as:

```text
Machine instructions
Heap
Stack
Global variables
File descriptors
Environment
Threads
```

Threads inside the same process share resources such as the heap and global variables.

This makes communication easier but also creates the need for synchronization.

---

# Cleanup

Before destroying shared resources, all threads must finish using them.

A simplified cleanup sequence is:

```text
Stop system
    ↓
Wake waiting threads
    ↓
pthread_join()
    ↓
Destroy mutexes / conditions
    ↓
Free allocated memory
```

This prevents threads from accessing resources after they have been destroyed.

---

# Testing

Because this is a multithreaded project, synchronization must be tested carefully.

Valgrind can be used to check memory problems:

```bash
valgrind --leak-check=full ./codexion ...
```

Helgrind can be used to detect threading problems:

```bash
valgrind --tool=helgrind ./codexion ...
```

These tools can help detect:

* Memory leaks
* Invalid memory accesses
* Data races
* Mutex problems
* Lock-order problems

---

# Resources

* POSIX Threads:
  https://man7.org/linux/man-pages/man7/pthreads.7.html

* Linux man-pages:
  https://man7.org/linux/man-pages/

* Linux programming interface:
    SECTION 30
https://ia601507.us.archive.org/22/items/linux-programming/the-linux-programming-interface.pdf


---

# AI Usage

AI was used as a learning and debugging assistant during the project.

It was used for:

* Understanding pthread functions.
* Understanding mutexes and condition variables.
* Understanding race conditions and deadlocks.
* Understanding FIFO and EDF scheduling.
* Helping with documentation.

The code and final implementation were developed, tested, and adapted according to the project's requirements.

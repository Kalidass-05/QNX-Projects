# QNX RTOS Programs

A collection of **small, independent C programs** developed using **QNX Neutrino RTOS and QNX Momentics IDE**.

The purpose of this repository is to learn and practice **RTOS, POSIX, threading, process management, IPC, synchronization, scheduling, and timing concepts** through simple programs.

Each folder contains a separate program demonstrating one concept.

---

## 🛠️ Tools Used

* **QNX Neutrino RTOS**
* **QNX Momentics IDE**
* **VMware Workstation**
* **C Programming**
* **Git & GitHub**

---

# 📂 Repository Structure

```text
QNX-RTOS-Programs/
│
├── 01_hello_world/
│   └── main.c
│
├── 02_thread_creation/
│   └── main.c
│
├── 03_multiple_threads/
│   └── main.c
│
├── 04_thread_join/
│   └── main.c
│
├── 05_thread_priority/
│   └── main.c
│
├── 06_mutex/
│   └── main.c
│
├── 07_condition_variable/
│   └── main.c
│
├── 08_process_creation/
│   └── main.c
│
├── 09_process_to_process/
│   ├── sender.c
│   └── receiver.c
│
├── 10_qnx_message_passing/
│   └── main.c
│
├── 11_channel_connection/
│   └── main.c
│
├── 12_timer/
│   └── main.c
│
├── 13_signal/
│   └── main.c
│
└── README.md
```

Each program is **independent** and can be built and executed separately.

---

# 📚 Programs

## 01 — Hello World

### Concept

Basic QNX C program.

### Topics

* QNX application
* `main()`
* `printf()`
* Compilation
* Execution

### Expected Output

```text
Hello World!
```

---

# 02 — Thread Creation

### Concept

Creating a thread using POSIX `pthread`.

### Topics

* Threads
* `pthread_create()`
* Thread function
* Thread ID

### Basic Flow

```text
Main
 │
 └── pthread_create()
          │
          ▼
     New Thread
          │
          ▼
       Execute
```

---

# 03 — Multiple Threads

### Concept

Creating multiple threads in one process.

### Topics

* Multiple threads
* Concurrent execution
* Thread scheduling

Example:

```text
Main Process
     │
 ┌───┼──────────┐
 ▼   ▼          ▼
T1   T2         T3
```

---

# 04 — Thread Join

### Concept

Waiting for a thread to complete.

### Function

```c
pthread_join()
```

### Flow

```text
Main
 │
 ├── Create Thread
 │
 ├── Create Thread
 │
 └── pthread_join()
          │
          ▼
     Wait for thread
```

---

# 05 — Thread Priority

### Concept

Changing and checking thread priority.

### Topics

* Thread priority
* Scheduling
* Preemption
* Real-time scheduling

Important functions:

```c
pthread_setschedparam()
pthread_getschedparam()
```

---

# 06 — Mutex

### Concept

Protecting shared data between threads.

### Topics

* Race condition
* Critical section
* Mutual exclusion
* Mutex

Functions:

```c
pthread_mutex_init()
pthread_mutex_lock()
pthread_mutex_unlock()
pthread_mutex_destroy()
```

---

# 07 — Condition Variable

### Concept

Thread synchronization using condition variables.

### Functions

```c
pthread_cond_init()
pthread_cond_wait()
pthread_cond_signal()
pthread_cond_broadcast()
pthread_cond_destroy()
```

Basic concept:

```text
Producer
   │
   ▼
Shared Data
   │
   │ signal
   ▼
Consumer
```

---

# 08 — Process Creation

### Concept

Creating a separate process.

### Topics

* Process
* Parent process
* Child process
* Process ID
* Process execution

Useful concepts/functions may include:

```c
getpid()
fork()
```

and QNX process-related mechanisms where applicable.

---

# 09 — Process-to-Process Communication

### Concept

Communication between two separate QNX processes.

Example:

```text
┌───────────────┐
│    Sender     │
│    Process    │
└───────┬───────┘
        │
        │ Message
        ▼
┌───────────────┐
│   Receiver    │
│    Process    │
└───────────────┘
```

This program demonstrates the basic idea of IPC.

---

# 10 — QNX Message Passing

### Concept

Using QNX native message-passing IPC.

Important functions:

```c
ChannelCreate()
ConnectAttach()
MsgSend()
MsgReceive()
MsgReply()
```

Communication:

```text
Client
  │
  │ MsgSend()
  ▼
Server
  │
  │ MsgReceive()
  ▼
Process Message
  │
  ▼
MsgReply()
```

This is one of the important concepts in QNX development.

---

# 11 — Channel and Connection

### Concept

Understanding how QNX processes establish communication.

Basic structure:

```text
Client Process
      │
      │ ConnectAttach()
      ▼
QNX Channel
      │
      ▼
Server Process
```

Topics:

* Channel
* Connection
* Connection ID
* Server
* Client

---

# 12 — Timer

### Concept

Working with timers and periodic execution.

Topics:

* System clock
* Timer
* Periodic execution
* Time intervals

Useful APIs include:

```c
clock_gettime()
timer_create()
timer_settime()
```

---

# 13 — Signals

### Concept

Handling asynchronous events using signals.

Topics:

* Signal generation
* Signal handling
* Asynchronous events

Example:

```text
Process
   │
   │ Signal
   ▼
Signal Handler
   │
   ▼
Handle Event
```

---

# 🧠 Concepts Covered

This repository gradually covers:

### Processes

* Process creation
* Parent/child processes
* Process IDs
* Process execution

### Threads

* Thread creation
* Multiple threads
* Thread termination
* Thread joining
* Thread priority

### Synchronization

* Mutex
* Condition variable
* Critical sections
* Race conditions

### IPC

* QNX channels
* Connections
* Message passing
* Client-server communication
* Process-to-process communication

### Timing

* System clock
* Timers
* Periodic execution
* Timeouts

### RTOS Concepts

* Scheduling
* Priority
* Preemption
* Concurrency
* Synchronization
* Inter-process communication
* Real-time timing

---

# 🖥️ How to Run the Programs

The programs are developed using **QNX Momentics IDE** and executed on the **QNX virtual machine running inside VMware**.

## Step 1 — Start VMware

Start your QNX virtual machine.

Make sure the QNX system has booted successfully.

You should reach the QNX terminal.

---

# Step 2 — Start Momentics

Open:

```text
QNX Momentics IDE
```

Make sure your QNX development environment is configured.

---

# Step 3 — Create a QNX Project

For a new program:

```text
File
 ↓
New
 ↓
QNX C Project
```

Give the project a name.

Example:

```text
thread_creation
```

Select the appropriate QNX executable project configuration.

---

# Step 4 — Add the C Source File

Create:

```text
main.c
```

Example:

```c
#include <stdio.h>

int main()
{
    printf("Hello from QNX!\n");

    return 0;
}
```

---

# Step 5 — Build the Program

In Momentics:

```text
Project
   ↓
Build Project
```

or use:

```text
Ctrl + B
```

Check the **Console** for compilation errors.

A successful build should generate the executable.

---

# Step 6 — Connect to the QNX VMware Target

Make sure the QNX VMware machine is running and reachable from Momentics.

The target should appear in the QNX target/target management area.

Example:

```text
Target
 └── QNX VMware
```

---

# Step 7 — Run the Program

Right-click the project and select:

```text
Run As
   ↓
QNX C/C++ Application
```

Select the QNX VMware target.

Then run the application.

---

# Step 8 — View the Output

The output can be viewed in the appropriate Momentics console/target output view.

For example:

```text
Hello from QNX!
```

You can also verify execution from the QNX VMware terminal if the executable is launched there.

---

# 🖥️ Running an Existing Program from GitHub

When downloading one of the programs from this repository:

### 1. Clone the repository

On your development machine:

```bash
git clone <repository-url>
```

### 2. Open the required folder

For example:

```text
02_thread_creation/
```

### 3. Import/create the corresponding QNX project in Momentics

Copy the `.c` source file into the project's source directory.

### 4. Build

```text
Project → Build Project
```

### 5. Select the QNX VMware target

### 6. Run

```text
Run As → QNX C/C++ Application
```

### 7. Check the output

---

# 🔄 Typical Development Cycle

For every program in this repository, the workflow is:

```text
Choose Concept
      │
      ▼
Create QNX Project
      │
      ▼
Write C Program
      │
      ▼
Build
      │
      ▼
Deploy to QNX VMware
      │
      ▼
Run
      │
      ▼
Check Output
      │
      ▼
Debug if Required
      │
      ▼
Save Program
      │
      ▼
Commit to GitHub
```

---

# 📌 GitHub Commit Example

After completing a program:

```bash
git add .
```

Then:

```bash
git commit -m "Add thread creation example"
```

Finally:

```bash
git push
```

Example commit history:

```text
Initial repository setup
Add Hello World program
Add thread creation program
Add multiple thread example
Add thread join example
Add thread priority example
Add mutex example
Add process creation example
Add process communication example
Add QNX message passing example
Add timer example
```

---

# 📈 Learning Progress

| #  | Program                          | Status      |
| -- | -------------------------------- | ----------- |
| 01 | Hello World                      | ✅ Completed |
| 02 | Thread Creation                  | 🔄 Learning |
| 03 | Multiple Threads                 | ⏳           |
| 04 | Thread Join                      | ⏳           |
| 05 | Thread Priority                  | ⏳           |
| 06 | Mutex                            | ⏳           |
| 07 | Condition Variable               | ⏳           |
| 08 | Process Creation                 | ⏳           |
| 09 | Process-to-Process Communication | ⏳           |
| 10 | QNX Message Passing              | ⏳           |
| 11 | Channel & Connection             | ⏳           |
| 12 | Timer                            | ⏳           |
| 13 | Signals                          | ⏳           |

---

# 🎯 Goal

The goal of this repository is **not to create one large application**.

Instead, it is a collection of small programs where each program focuses on **one QNX/RTOS concept**.

The learning path is:

```text
C
 │
 ├── Process
 │
 ├── Thread
 │
 ├── Multiple Threads
 │
 ├── Scheduling
 │
 ├── Priority
 │
 ├── Mutex
 │
 ├── Condition Variable
 │
 ├── Process Creation
 │
 ├── IPC
 │
 ├── QNX Message Passing
 │
 ├── Timers
 │
 └── Signals
```

Each program should be simple enough to understand, compile, execute, and debug independently.

---

# 👨‍💻 Author

**Kalidass L**

B.E. Electronics and Communication Engineering

Areas of interest:

* Embedded Systems
* Embedded C
* RTOS
* QNX
* Firmware
* Aerospace Embedded Systems
* Real-Time Systems

---

## 📜 License

This repository is intended primarily for educational and learning purposes.

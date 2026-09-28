# QNX RTOS – Client-Server IPC

## 1. What is IPC?

**IPC (Inter-Process Communication)** is a mechanism used by processes to communicate and exchange data.

In QNX, different processes normally have separate address spaces, so one process cannot directly access another process's variables.

```text
Process A                         Process B
+-------------+                  +-------------+
| Code        |                  | Code        |
| Data        |                  | Data        |
| Stack       |                  | Stack       |
| Heap        |                  | Heap        |
+-------------+                  +-------------+
       |                                |
       +-------- Separate memory -------+
```

IPC provides a controlled way for these processes to communicate.

---

# 2. Client-Server Model

QNX commonly uses a **client-server model** for IPC.

* **Server**: Provides a service and waits for requests.
* **Client**: Requests a service from the server.

Example:

```text
             REQUEST
Client --------------------> Server
       <--------------------
              REPLY
```

Example:

```text
Temperature Client
        |
        | "Give temperature"
        ↓
Temperature Server
        |
        | "35°C"
        ↓
Temperature Client
```

---

# 3. QNX Message Passing

One of the fundamental IPC mechanisms in QNX is **message passing**.

The basic operations are:

```text
Client                         Server

MsgSend()  ----------------->  MsgReceive()
                                  |
                                  | Process request
                                  ↓
           <-----------------  MsgReply()
```

### Important functions

| Function        | Purpose                       |
| --------------- | ----------------------------- |
| `name_attach()` | Server registers a name       |
| `name_open()`   | Client connects to the server |
| `MsgSend()`     | Client sends a request        |
| `MsgReceive()`  | Server receives a request     |
| `MsgReply()`    | Server sends a response       |
| `name_detach()` | Server removes its name       |
| `name_close()`  | Client closes connection      |

---

# 4. Channel

A **channel** is a communication endpoint created/used by the server.

Conceptually:

```text
Server
  |
  | name_attach()
  ↓
Channel
  ↑
  |
Connection
  ↑
  |
Client
```

The server receives messages through its channel.

```c
attach = name_attach(NULL, "myserver", 0);
```

The channel ID is available through:

```c
attach->chid
```

---

# 5. Connection

A client needs a connection to communicate with the server.

The client can obtain a connection using:

```c
coid = name_open("myserver", 0);
```

Here:

* `coid` = connection ID
* `"myserver"` = server name

Conceptually:

```text
Client
  |
  | name_open()
  ↓
Server Channel
```

---

# 6. Server Program

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>

typedef struct
{
    char msg[100];
} message_t;

int main()
{
    name_attach_t *attach;
    message_t msg;
    int rcvid;

    attach = name_attach(NULL, "myserver", 0);

    if (attach == NULL)
    {
        perror("name_attach");
        return 1;
    }

    printf("Server started\n");

    while (1)
    {
        rcvid = MsgReceive(
            attach->chid,
            &msg,
            sizeof(msg),
            NULL
        );

        if (rcvid == -1)
        {
            perror("MsgReceive");
            continue;
        }

        printf("Server received: %s\n", msg.msg);

        MsgReply(
            rcvid,
            EOK,
            "Hello Client",
            strlen("Hello Client") + 1
        );
    }

    name_detach(attach);

    return 0;
}
```

---

# 7. Server Code Explanation

## `name_attach()`

```c
attach = name_attach(NULL, "myserver", 0);
```

Registers the server with the QNX name service.

The server becomes available using the name:

```text
myserver
```

The client can then find it.

---

## `attach->chid`

```c
attach->chid
```

Contains the channel ID created for the server.

It is passed to:

```c
MsgReceive()
```

---

## `MsgReceive()`

```c
rcvid = MsgReceive(
    attach->chid,
    &msg,
    sizeof(msg),
    NULL
);
```

This waits for a message from a client.

Parameters:

```text
attach->chid
    ↓
Which channel?

&msg
    ↓
Where to store received data?

sizeof(msg)
    ↓
Maximum receive size

NULL
    ↓
No additional information required
```

If no message is available, the server thread can block waiting for one.

---

## `rcvid`

```c
int rcvid;
```

`rcvid` is the receive ID returned by `MsgReceive()`.

The server uses it when replying:

```c
MsgReply(rcvid, ...);
```

It identifies the request that should receive the reply.

---

## `MsgReply()`

```c
MsgReply(
    rcvid,
    EOK,
    "Hello Client",
    strlen("Hello Client") + 1
);
```

Sends a response to the client.

Important:

```text
rcvid
    ↓
Which client/request?

EOK
    ↓
Status of the operation

"Hello Client"
    ↓
Reply data

strlen(...) + 1
    ↓
Reply size including '\0'
```

---

# 8. Client Program

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>

int main()
{
    int coid;

    char send_msg[] = "Hello Server";
    char receive_msg[100];

    coid = name_open("myserver", 0);

    if (coid == -1)
    {
        perror("name_open");
        return 1;
    }

    printf("Sending message...\n");

    if (MsgSend(
            coid,
            send_msg,
            sizeof(send_msg),
            receive_msg,
            sizeof(receive_msg)) == -1)
    {
        perror("MsgSend");
        return 1;
    }

    printf("Server replied: %s\n", receive_msg);

    name_close(coid);

    return 0;
}
```

---

# 9. Client Code Explanation

## `name_open()`

```c
coid = name_open("myserver", 0);
```

Finds the server registered with the name:

```text
myserver
```

and establishes a connection.

The returned value:

```c
coid
```

is the connection ID.

---

# 10. MsgSend()

```c
MsgSend(
    coid,
    send_msg,
    sizeof(send_msg),
    receive_msg,
    sizeof(receive_msg)
);
```

This sends a request to the server.

### Parameters

```text
coid
    ↓
Connection to server

send_msg
    ↓
Data being sent

sizeof(send_msg)
    ↓
Size of send data

receive_msg
    ↓
Buffer for server reply

sizeof(receive_msg)
    ↓
Maximum reply size
```

The client normally waits for the server to receive the request and reply.

---

# 11. Complete Communication Flow

```text
                QNX CLIENT-SERVER IPC

       CLIENT                         SERVER
         |                              |
         |                              |
         |        name_attach()         |
         |                         +----+
         |                         |    |
         |                         | CH |
         |                         |    |
         |                         +----+
         |                              |
         |                              |
         | name_open("myserver")        |
         |----------------------------->|
         |                              |
         |                              |
         | MsgSend()                    |
         |----------------------------->|
         |       "Hello Server"         |
         |                              |
         |                         MsgReceive()
         |                              |
         |                         Process data
         |                              |
         |                         MsgReply()
         |<-----------------------------|
         |       "Hello Client"         |
         |                              |
         |                              |
```

---

# 12. Step-by-Step Execution

### Step 1: Start server

```bash
./server
```

Server executes:

```c
name_attach(NULL, "myserver", 0);
```

Output:

```text
Server started
```

---

### Step 2: Server waits

The server executes:

```c
MsgReceive(...)
```

It waits for a client request.

```text
Server
   |
   ↓
WAITING
```

---

### Step 3: Start client

```bash
./client
```

Client executes:

```c
name_open("myserver", 0);
```

---

### Step 4: Client sends message

```c
MsgSend(...)
```

The client sends:

```text
Hello Server
```

---

### Step 5: Server receives

```c
MsgReceive(...)
```

returns when the request arrives.

The server receives:

```text
msg.msg = "Hello Server"
```

---

### Step 6: Server processes request

```c
printf("Server received: %s\n", msg.msg);
```

Output:

```text
Server received: Hello Server
```

---

### Step 7: Server replies

```c
MsgReply(...)
```

Server sends:

```text
Hello Client
```

---

### Step 8: Client receives reply

`MsgSend()` completes after the server replies.

The client prints:

```text
Server replied: Hello Client
```

---

# 13. Expected Output

### Server

```text
Server started
Server received: Hello Server
```

### Client

```text
Sending message...
Server replied: Hello Client
```

---

# 14. Important Concept: Blocking

Consider:

```c
MsgReceive(...)
```

If there is no message:

```text
Server
   |
   ↓
MsgReceive()
   |
   ↓
BLOCKED / WAITING
```

When a client sends a message:

```text
Client
   |
   | MsgSend()
   ↓
Server
   |
   | MsgReceive() returns
   ↓
Process request
```

Similarly, the client can wait inside:

```c
MsgSend()
```

until the server handles the request and replies.

---

# 15. Message Structure

Messages do not have to contain only strings.

We can define a structure:

```c
typedef struct
{
    int command;
    int value;
} message_t;
```

Example:

```text
command = 1
value   = 100
```

The client can send:

```text
COMMAND = 1
VALUE   = 100
```

The server can process the command and return a result.

This is useful in embedded systems.

Example:

```text
Client
   |
   | command = MOTOR_START
   ↓
Motor Server
   |
   | Start motor
   ↓
Reply
```

---

# 16. Why Message Passing is Useful in Embedded Systems

Consider an embedded system:

```text
+-------------------+
| Sensor Process    |
+-------------------+
          |
          | sensor data
          ↓
+-------------------+
| Control Process   |
+-------------------+
          |
          | command
          ↓
+-------------------+
| Motor Process     |
+-------------------+
```

Each process can provide a service.

For example:

```text
Sensor Server
Motor Server
GPS Server
Logger Server
Network Server
```

Other processes can communicate with these servers using IPC.

---

# 17. Message Passing vs Shared Memory

| Feature         | Message Passing                | Shared Memory                 |
| --------------- | ------------------------------ | ----------------------------- |
| Main purpose    | Communication                  | Sharing large data            |
| Data transfer   | Message                        | Common memory                 |
| Synchronization | Built into request/reply model | Usually needs synchronization |
| Large data      | Less suitable                  | Suitable                      |
| Complexity      | Relatively simple              | More complex                  |
| Typical use     | Commands, requests, events     | High-volume data              |

Example:

### Message passing

```text
Process A
   |
   | command
   ↓
Process B
```

### Shared memory

```text
Process A ───┐
             ↓
       Shared Memory
             ↑
Process B ───┘
```

---

# 18. Message Passing vs Mutex

### Mutex

Used mainly for protecting shared resources.

```text
Thread A ──┐
           ↓
       Shared Data
           ↑
Thread B ──┘
```

### Message Passing

Used to communicate between processes.

```text
Process A
    |
    | Message
    ↓
Process B
```

Remember:

```text
Mutex           → Protect shared resource

Message Passing → Communicate between processes
```

---

# 19. Important QNX Functions to Remember

### Server

```c
name_attach()
MsgReceive()
MsgReply()
name_detach()
```

### Client

```c
name_open()
MsgSend()
name_close()
```

Memorize this sequence:

```text
SERVER

name_attach()
      ↓
MsgReceive()
      ↓
Process request
      ↓
MsgReply()


CLIENT

name_open()
      ↓
MsgSend()
      ↓
Receive reply
      ↓
name_close()
```

---

# 20. Important Terms

### IPC

Inter-Process Communication.

### Client

Process that requests a service.

### Server

Process that provides a service.

### Channel

Communication endpoint used by the server.

### Connection

Client's connection to a server channel.

### Message

Data/request transferred between client and server.

### `chid`

Channel ID.

### `coid`

Connection ID.

### `rcvid`

Receive ID returned by `MsgReceive()`.

---

# 21. Placement Interview Questions

### 1. What is IPC?

IPC is a mechanism that allows separate processes to communicate and exchange data.

### 2. Why is IPC required?

Because separate processes normally have separate address spaces and cannot directly access each other's memory.

### 3. What is the QNX client-server model?

A client sends a request to a server through a communication channel, and the server processes the request and sends a reply.

### 4. What functions are used for QNX message passing?

```text
MsgSend()
MsgReceive()
MsgReply()
```

### 5. What does `name_attach()` do?

It registers a server name with the QNX name service and provides the server with a communication channel.

### 6. What does `name_open()` do?

It allows a client to find and connect to a server registered with a particular name.

### 7. What is `chid`?

`chid` is the channel ID used by the server to receive messages.

### 8. What is `coid`?

`coid` is the connection ID used by the client to communicate with the server.

### 9. What is `rcvid`?

`rcvid` identifies the received request and is used by the server when calling `MsgReply()`.

### 10. What happens if no message is available?

`MsgReceive()` can block the calling thread until a message arrives.

### 11. Does message passing provide synchronization?

Yes. QNX message passing provides communication and synchronization through the request/reply mechanism.

### 12. Message passing vs shared memory?

Message passing transfers data through messages, while shared memory allows processes to access a common memory region. Shared memory is generally useful for large/high-volume data but requires proper synchronization.

---

# 22. Quick Revision

```text
                    IPC
                     |
            Inter-Process Communication
                     |
            QNX Client-Server
                     |
          +----------+----------+
          |                     |
        CLIENT                SERVER
          |                     |
    name_open()            name_attach()
          |                     |
       MsgSend()           MsgReceive()
          |                     |
          |                Process request
          |                     |
          |                 MsgReply()
          |                     |
          +<--------------------+
```

### Most important sequence

```text
Client                         Server

name_open()  --------------->  name_attach()

MsgSend()    --------------->  MsgReceive()

             <---------------  MsgReply()

name_close()
```

### Remember

```text
chid  → Channel ID
coid  → Connection ID
rcvid → Receive ID

MsgSend()
    ↓
MsgReceive()
    ↓
MsgReply()
```

---

# 23. One-Line Interview Answer

> **QNX provides client-server IPC using message passing, where the server creates/attaches to a communication channel, the client connects to it, sends a request using `MsgSend()`, the server receives it using `MsgReceive()`, processes it, and responds using `MsgReply()`.**

---

# 24. Practical Learning Order

After understanding this basic client-server example, practice these programs in order:

```text
1. Client sends a string
        ↓
2. Client sends an integer
        ↓
3. Server performs calculation
        ↓
4. Client sends a structure
        ↓
5. Server returns a structure
        ↓
6. Multiple clients → one server
        ↓
7. Server handles different commands
        ↓
8. Pulses
        ↓
9. Shared memory
        ↓
10. Semaphores between processes
```

This progression builds the QNX IPC concepts from basic message passing to practical RTOS communication.

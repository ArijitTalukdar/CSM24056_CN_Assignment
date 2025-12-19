# CN Lab - Assignment 8

## Objective
Using Thread library and TCP sockets.

## Exercise
Write a program in C using thread library and TCP sockets to build a chat server which enable clients communicating to each other through the chat server. Message logs must be maintained in the server in a text file. Each client will see the conversations in real time. Clients must handled by a server thread. (Keep it like a group chatbox)

## Implementation

### Server 
- Multi-threaded TCP server using pthread library
- Handles multiple clients concurrently
- Broadcasts messages to all connected clients
- Maintains message logs 
- Uses mutex for thread-safe operations

### Client 
- TCP client that connects to chat server
- Sends and receives messages in real-time
- Uses separate thread for receiving messages

## Compilation
Mininet: sudo mn --topo=linear,3

```bash
gcc server.c -o server -lpthread
gcc client.c -o client -lpthread
```

## Usage
1. Start server:
   ```bash
   ./server
   ```

2. Connect clients:
   ```bash
   ./client user1
   ./client user2
   ./client user3
   ```

3. Type messages in each client terminal
4. Messages are broadcast to all connected clients
5. Conversation log is saved 

## Learning Outcomes
1. Understanding multi-threading for TCP sockets.


CSM24056

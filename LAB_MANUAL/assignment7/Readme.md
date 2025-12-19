# CN Lab - Assignment 7

## Objective
Client server communication with UDP packets

## Exercise
Write UDP client server socket program where client sends one/two number(s) (integer or floating point) to server and a scientific calculator operation (like sin,cos,*,/, inv etc.) and server responds with the result after evaluating the value of operation as sent by the client. Server will maintain a scientific calculator. Detect in the mininet hosts with wireshark if there is any packet loss? Show it to the TA.

## Implementation

### Server 
- Listens on UDP port 8080
- Supports operations: sin, cos, tan, inv, +, -, *, /
- Uses math.h library for computations
- Handles packet loss detection with Wireshark

### Client 
- Sends operations and numbers to server
- Receives and displays results
- Uses Mininet IP (10.0.0.1)

## Compilation
```bash
gcc udp_server.c -o server -lm
gcc udp_client.c -o client -lm
```

## Usage
1. Start server:
   ```bash
   ./server
   ```

2. Run client:
   ```bash
   ./client sin 1.57
     ```

## Packet Loss Detection with Wireshark
1. Start Wireshark capture on the Mininet interface
2. Run client-server communication
3. Stop capture and analyze:
   - Look for duplicate packets (retransmissions)
   - Check for gaps in sequence numbers
   - Identify any missing packets

## Learning Outcomes
1. Understanding reliability of UDP for transactions.


CSM24056

TCP Client-Server Socket Programming Assignment

This assignment demonstrates basic TCP client-server communication where the client sends "Hi" and the server responds with "Hello".
Files Included

    tcpserver.c - Minimal TCP server program
    tcpclient.c - Minimal TCP client program

Compilation

To compile both programs, run:

gcc tcp_server -o server
gcc tcp_client -o client

This will create two executables:

    tcpserver
    tcpclient

Running the Programs in Mininet

    Start Mininet with two hosts:

sudo mn --topo single,2

    In the Mininet CLI, open terminals for both hosts:

xterm h1 h2

    In h1 terminal, start the server:

./server

    In h2 terminal, run the client:

./client

CSM24056

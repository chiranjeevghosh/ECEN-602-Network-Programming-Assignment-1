# ECEN-602-Network-Programming-Assignment-1:

This project implements a simple client-server implementation for a TCP echo service which does the following:

1. Start the server first with the command line: echos Port, where Port is
the port number on which the server is listening. The server must support
multiple simultaneous connections.
2. Start the client second with a command line: echo IPAdr Port, where
IPAdr is the IPv4 address of the server in dotted decimal notation and
Port is the port number on which the server is listening.
3. The client reads a line of text from its standard input and writes the line to
the network output to the server.
4. The sever reads the line from its network input and echoes the line back to
the client.
5. The client reads the echoed line and prints it on its standard input.
6. When the client reads an EOF from its standard input (e.g., terminal input
of Control-D), it closes the socket and exits. When the client closes the
socket, the server will receive a TCP FIN packet, and the server child
process’ read() command will return with a 0. The child process should then
exit.

Package content:
Server.c
Client.c
utils.h
Makefile
Usage:
'make clean' to remove all previously created object files.
'make server' to compile the server source code in the package.
'make client' to compile the client source code in the package.
./echos Port#
./echo Port# Server_IP_Address

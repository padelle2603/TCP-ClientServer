/*
 ============================================================================
 Author      : Michele Allegrini, Luca Lolaico
 ============================================================================
 */
#ifndef CONNECTION_H
#define CONNECTION_H

#include "protocol.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

int setup_server_socket(int port, const char *ip);
void accept_connections(int server_socket);
void handle_client(int client_socket, struct sockaddr_in cad);

#endif // CONNECTION_H

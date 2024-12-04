/*
 ============================================================================
 Author      : Michele Allegrini, Luca Lolaico
 ============================================================================
 */
#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include "protocol.h"
#include <stdio.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

int create_socket();
int connect_to_server(int c_socket, struct sockaddr_in *sad);
int get_input(char *input, size_t size);
void parse_input(char *input, password_request *request);
void handle_password_request(int c_socket);

#endif // CLIENT_UTILS_H

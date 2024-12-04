/*
 ============================================================================
 Author      : Michele Allegrini, Luca Lolaico
 ============================================================================
 */
#include "connection.h"
#include "password.h"
#include "utils.h"
#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define closesocket close
#endif

// Function to set up the server socket with the specified port and IP address
int setup_server_socket(int port, const char *ip) {


    // Create a TCP socket
    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0) {
        errorhandler("Error creating socket.");
        return -1;
    }

    // Configure the server address structure
    struct sockaddr_in sad;
    memset(&sad, 0, sizeof(sad));      		// Zero out the structure
    sad.sin_family = AF_INET;          		// Set the address family to Internet
    sad.sin_addr.s_addr = inet_addr(ip);  	// Set the IP address
    sad.sin_port = htons(port);        		// Set the port number

    // Bind the socket to the specified IP and port
    if (bind(server_socket, (struct sockaddr*)&sad, sizeof(sad)) < 0) {
        errorhandler("Error binding socket.");
        closesocket(server_socket);
        return -1;
    }


    // Listen for incoming connections with a backlog of 5
    if (listen(server_socket, QLEN) < 0) {
        errorhandler("Error in listen() function.");
        closesocket(server_socket);
        return -1;
    }

    return server_socket;
}

// Function to accept and handle incoming client connections
void accept_connections(int server_socket) {
    struct sockaddr_in cad;           		// Structure for client address
    socklen_t client_len = sizeof(cad);     // Length of the client address structure
    int count = 0;                    		// Connection counter

    while (1) {
        // Accept a new client connection
        int client_socket = accept(server_socket, (struct sockaddr*)&cad, &client_len);
        if (client_socket < 0) {
            errorhandler("Error accepting connection.");
            continue;  // Skip to the next iteration on error
        }

        printf("New connection from %s:%d, connection NO: %d\n",
               inet_ntoa(cad.sin_addr), ntohs(cad.sin_port), ++count);

        // Handle communication with the client
        handle_client(client_socket, cad);
    }
}

// Function to handle communication with a connected client
void handle_client(int client_socket, struct sockaddr_in cad) {
    password_request request;         // Structure for storing client request
    char password[BUFFER_SIZE];       // Buffer for storing generated password

    while (1) {
        // Receive a password request from the client
        int bytes_received = recv(client_socket, (char*)&request, sizeof(password_request), 0);
        if (bytes_received <= 0) {  // If no data is received, it could mean the client disconnected or an error occurred
            if (bytes_received == 0) {
                // Client closed the connection properly (graceful closure)
                printf("Request Accomplished. Connection closed by client %s:%d\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));
            } else {
                // If bytes_received is negative, it's an error in receiving data
                errorhandler("Error receiving request from client or client closed without informing server.");
            }
            break;  // Exit the loop if an error or client disconnection occurs
        }

        // Check if the client sent the 'Q' to exit gracefully
        if (toupper(request.type) == 'Q') {
            printf("Client %s:%d disconnected gracefully.\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));
            break; // Exit the loop if the client has sent 'Q'
        }

        // Generate a password based on the request
        generate_password(password, request);

        // Send the generated password back to the client
        if (send(client_socket, password, BUFFER_SIZE, 0) <= 0) {
            errorhandler("Error sending password.");
            break;
        }
    }

    // Close the client socket
    closesocket(client_socket);
    printf("Connection closed.\n\n");
}


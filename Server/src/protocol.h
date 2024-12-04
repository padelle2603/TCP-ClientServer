/*
 ============================================================================
 Author      : Michele Allegrini, Luca Lolaico
 ============================================================================
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H

#define PROTO_PORT 57015           // Default server port
#define PROTO_IP "127.0.0.1"       // Default server IP address
#define BUFFER_SIZE 512            // Buffer size for messages
#define QLEN 4 			   		   //maximum number of clients connected at the same time (it starts from 0)

// Structure for client request
typedef struct {
    char type;                     // Password type: 'n' for numeric, 'a' for alphabetic, 'm' for mixed, 's' for secure
    int length;                    // Password length
} password_request;

#endif // PROTOCOL_H

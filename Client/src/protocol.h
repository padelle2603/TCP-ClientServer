#ifndef PROTOCOL_H
#define PROTOCOL_H

#define PROTO_PORT 57015           // Default server port
#define PROTO_IP "127.0.0.1"       // Default server IP address
#define BUFFER_SIZE 512            // Buffer size for messages

#define MIN_PASSWORD_LENGTH 6      // Minimum password length
#define MAX_PASSWORD_LENGTH 32     // Maximum password length


// Structure for client request
typedef struct {
    char type;                     // Password type: 'n' for numeric, 'a' for alphabetic, 'm' for mixed, 's' for secure
    int length;                    // Password length
} password_request;

#endif // PROTOCOL_H

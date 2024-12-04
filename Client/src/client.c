
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <unistd.h>
	#define closesocket close
#endif

#include "protocol.h"
#include "connection.h"
#include "utils.h"

int main() {
	// Initialize Winsock (if on Windows)
	startup();

	// Create a socket for communication
	int c_socket = create_socket();
	if (c_socket < 0) {
		// If socket creation fails, clear Winsock and return an error
		clearwinsock();
		return -1;
	}

	// Set up the server address structure
	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad)); // Initialize the sockaddr_in structure to zero
	sad.sin_family = AF_INET;       // Set the address family to IPv4
	sad.sin_addr.s_addr = inet_addr(PROTO_IP); // Set the server IP address
	sad.sin_port = htons(PROTO_PORT);  // Set the server port number

	// Attempt to connect to the server using the created socket
	if (connect_to_server(c_socket, &sad) < 0) {
		// If the connection fails, close the socket and clear Winsock
		closesocket(c_socket);
		clearwinsock();
		return -1; // Return an error code
	}

	// Handle password request logic (user input and server communication)
	handle_password_request(c_socket);

    // Once done, close the server socket and clean up Winsock
    closesocket(c_socket);
    clearwinsock();
    return 0;
}

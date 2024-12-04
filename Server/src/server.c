#include "protocol.h"
#include "utils.h"
#include "connection.h"

#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <unistd.h>
	#define closesocket close
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
	// Initialize Winsock (only needed on Windows)
	startup();
	// Seed the random number generator using the current time
	srand((unsigned int) time(NULL));

	// Setup the server socket to listen for incoming client connections
	int server_socket = setup_server_socket(PROTO_PORT, PROTO_IP);
	if (server_socket < 0) { // Check for errors in socket creation
		clearwinsock();  // Cleanup Winsock resources
		return -1;       // Exit with error code
	}

	// Print the server's connection details to the console
	printf("Connection open.\nServer listening on %s:%d...\n\n", PROTO_IP,
	PROTO_PORT);

	// Accept client connections in a loop (blocking call)
	accept_connections(server_socket);

    // Once done, close the server socket and clean up Winsock
    closesocket(server_socket);
    clearwinsock();
    return 0;
}

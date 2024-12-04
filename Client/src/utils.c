#include "utils.h"
#include <stdio.h>

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

// Function to display an error message
void errorhandler(const char *errorMessage) {
	printf("%s\n", errorMessage);
}

// Function to initialize the Winsock library (only needed on Windows)
void startup() {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        errorhandler("Error in WSAStartup()");
    }
#endif
}

// Function to clear Winsock resources (only needed on Windows)
void clearwinsock() {
#ifdef _WIN32
    WSACleanup();
#endif
}

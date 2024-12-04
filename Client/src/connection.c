#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "protocol.h"
#include "connection.h"
#include "utils.h"

#ifdef _WIN32
	boolean err=0;
#else
	bool err=0;
	#include <stdlib.h>
#endif

// Function to create a TCP socket and return its descriptor
int create_socket() {
	// Create a socket using IPv4 (PF_INET), TCP (SOCK_STREAM), and the TCP protocol (IPPROTO_TCP)
	int c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket < 0) {
		// If socket creation fails, print an error message
		errorhandler("Error creating socket.");
	}
	return c_socket; // Return the socket descriptor
}

// Function to connect to the server
int connect_to_server(int c_socket, struct sockaddr_in *sad) {
	// Attempt to connect the client socket to the specified server address and port
	if (connect(c_socket, (struct sockaddr*) sad, sizeof(*sad)) < 0) {
		// If the connection fails, print an error message
		errorhandler("Error connecting to server.");
		return -1; // Return -1 to indicate failure
	}
	return 0; // Return 0 on successful connection
}

// Function to read user input from the console
int get_input(char *input, size_t size) {
	// Read a line of input from the user
	if (fgets(input, size, stdin) == NULL) {
		// If there is an error reading input, print an error message
		errorhandler("Error reading input.");
		return -1; // Return -1 to indicate failure
	}

	// Remove newline character from input
	input[strcspn(input, "\n")] = 0;

	// Check if the input is empty (only spaces)
	if (strlen(input) == 0) {
		printf(
				"Error: input cannot be empty. Please enter a valid password request.\n\n");
		return -1; // Return -1 to indicate invalid input
	}

	return 0; // Return 0 on successful input read
}

void parse_input(char *input, password_request *request) {
    err = false; // Reset err at the beginning of parsing
    do {
        // Trim leading and trailing whitespace
        char *start = input;
        while (isspace((unsigned char)*start)) start++;

        char *end = start + strlen(start) - 1;
        while (end > start && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0'; // Null-terminate the string after trimming

        // Find the first space in the input
        char *space = strchr(start, ' ');
        if (space == NULL) {
            printf("Error: input must contain exactly one space between type and length.\n\n");
            err = true;
            break;
        }

        // Ensure there is exactly one space and no extra spaces
        if (strchr(space + 1, ' ') != NULL) {
            printf("Error: input must not contain multiple spaces.\n\n");
            err = true;
            break;
        }

        // Split the input into two parts: type and length
        *space = '\0'; // Replace the space with a null terminator to split the string
        char *type_str = start;
        char *length_str = space + 1;

        // Validate the type
        if (strlen(type_str) != 1 || (toupper(type_str[0]) != 'N' && toupper(type_str[0]) != 'A' &&
                                      toupper(type_str[0]) != 'M' && toupper(type_str[0]) != 'S')) {
            printf("Error: invalid password type. Use 'n', 'a', 'm', or 's'.\n\n");
            err = true;
            break;
        }

        // Validate the length
        for (char *p = length_str; *p != '\0'; p++) {
            if (!isdigit((unsigned char)*p)) {
                printf("Error: length must be a valid number.\n\n");
                err = true;
                break;
            }
        }
        if (err) break; // Stop further checks if an error was found

        // Convert length to an integer
        int length = atoi(length_str);

        // Assign values to the request structure
        request->type = toupper(type_str[0]);
        request->length = length;
    } while (0);
}






void handle_password_request(int c_socket) {
    password_request request; // Structure to hold the password request
    char password[BUFFER_SIZE]; // Buffer to store the generated password
    char input[BUFFER_SIZE]; // Buffer to hold the user input

    // Instructions for the user on how to format their input
    printf("Use the format 'type length', e.g., 'n 12'. Type 'q' to exit.\n");

    // Loop to continuously get input from the user
    while (1) {
        if (get_input(input, sizeof(input)) == -1) {
            continue; // If there is an input error or empty input, continue asking for input
        }

        // Exit the loop if the user types 'q'
        if (toupper(input[0]) == 'Q') {
            printf("Exiting the program.\n");
		#ifdef WIN32
            	Sleep(1500);
		#else
            	sleep(1500);
		#endif
            break; // Break the loop if user wants to quit
        }

        parse_input(input, &request); // Parse the input into a password request

        // Skip sending or receiving if there was a parsing error
        if (err) {
            continue; // Go to the next iteration of the loop
        }

        // Validate the requested password length
        if (request.length < MIN_PASSWORD_LENGTH || request.length > MAX_PASSWORD_LENGTH) {
            printf("Error: password length must be between %d and %d characters.\n\n",
                   MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
            continue; // If the length is invalid, ask for the input again
        }

        // Send the password request to the server
        if (send(c_socket, (const char*) &request, sizeof(request), 0) <= 0) {
            errorhandler("Error sending request."); // Handle error if send fails
            break;
        }

        // Receive the generated password from the server
        if (recv(c_socket, password, BUFFER_SIZE, 0) <= 0) {
            errorhandler("Error receiving password."); // Handle error if receive fails
            break;
        }

        // Display the selected password type, length, and the generated password
        printf("You selected type: '%c', and length: %d\n", request.type, request.length);
        printf("Generated password: %s\n\n", password);
    }
}


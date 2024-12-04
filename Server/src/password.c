#include "password.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to generate a password based on the type specified in the request.
void generate_password(char *password, password_request request) {
    // Check the request type (converted to uppercase) and call the corresponding generation function.
    switch (toupper(request.type)) {
        case 'N':
            // Generate a numeric-only password if type is 'N'.
            generate_numeric(password, request.length);
            break;
        case 'A':
            // Generate an alphabetic-only password if type is 'A'.
            generate_alpha(password, request.length);
            break;
        case 'M':
            // Generate a mixed password (letters and numbers) if type is 'M'.
            generate_mixed(password, request.length);
            break;
        case 'S':
            // Generate a secure password (complex characters) if type is 'S'.
            generate_secure(password, request.length);
            break;
        default:
            // If the type is invalid, set the password message to indicate an error.
            strcpy(password, "Invalid request type");
            break;
    }
}


// Function to generate a numeric password
void generate_numeric(char *password, int length) {
    const char *numeric = "0123456789";
    int charset_len = strlen(numeric);

    for (int i = 0; i < length; i++) {
        password[i] = numeric[rand() % charset_len];
    }
    password[length] = '\0';  // Add null terminator
}

// Function to generate an alphabetic password
void generate_alpha(char *password, int length) {
    const char *alphabetic = "abcdefghijklmnopqrstuvwxyz";
    int charset_len = strlen(alphabetic);

    for (int i = 0; i < length; i++) {
        password[i] = alphabetic[rand() % charset_len];
    }
    password[length] = '\0';  // Add null terminator
}

// Function to generate a mixed (alphanumeric) password
void generate_mixed(char *password, int length) {
    const char *mixed = "abcdefghijklmnopqrstuvwxyz0123456789";
    int charset_len = strlen(mixed);

    for (int i = 0; i < length; i++) {
        password[i] = mixed[rand() % charset_len];
    }
    password[length] = '\0';  // Add null terminator
}

// Function to generate a secure password (alphanumeric with special characters)
void generate_secure(char *password, int length) {
    const char *secure = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    int charset_len = strlen(secure);

    for (int i = 0; i < length; i++) {
        password[i] = secure[rand() % charset_len];
    }
    password[length] = '\0';  // Add null terminator
}

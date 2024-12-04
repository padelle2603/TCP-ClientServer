#ifndef PASSWORD_H
#define PASSWORD_H

#include "protocol.h"

void generate_password(char *password, password_request request);
void generate_numeric(char *password, int length);
void generate_alpha(char *password, int length);
void generate_mixed(char *password, int length);
void generate_secure(char *password, int length);

#endif

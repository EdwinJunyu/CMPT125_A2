#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H

#include <stdbool.h>
#include <stdint.h>

/* Question 1 */

// adds the pair to the file
// if the username doesn't exit already
int add_user_password(const char* file_name, const char* username, const char* password);

//  searches the file for the username/password
int check_user_password(const char* file_name, const char* username, const char* password);


/* Question 2 */

// gets an input n and computes fib3(n)
int64_t fib3(unsigned int n);


/* Question 3 */

// gets a string str, and a char delim
// returns the number of tokens in str separated by delim.
int count_tokens(const char* str, char delim);

// gets a string str, and a char delim
// returns an array of tokens in str, ending with the NULL pointer
char** get_tokens(const char* str, char delim);

#endif

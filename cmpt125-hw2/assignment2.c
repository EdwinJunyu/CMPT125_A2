#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

int add_user_password(const char* file_name, const char* username, const char* password) {
    // implement me
    FILE* file;
    long ulen = strlen(username);
    long plen = strlen(password);

    file = fopen(file_name, "r+");
    if (!file) {
        file = fopen(file_name, "w"); //If file does not exist, make a new file right now.
        if (!file) return -1;

        fprintf(file, "%ld %ld ", ulen, plen);  
        fwrite(username, 1, ulen, file); //Write down username and password
        fwrite(password, 1, plen, file);
        fclose(file);
        return 1;
    }

    while (1) { // If the file exist
        long existing_ulen, existing_plen;
        if (fscanf(file, "%ld %ld ", &existing_ulen, &existing_plen) != 2) break; // then check the data if integrity

        char* existing_user = (char*)malloc(existing_ulen + 1); //Allocate memory for the username that is about to be read
        if (!existing_user) {
           fclose(file);
            return -1;
           }
        if (fread(existing_user, 1, existing_ulen, file) != existing_ulen) {
            free(existing_user);
            fclose(file);
            return -1;
        }
        existing_user[existing_ulen] = '\0';

       // Skip the password part corresponding to this user because we only want to check if the username exists here
        if (fseek(file, existing_plen, SEEK_CUR) != 0) {
            free(existing_user);
            fclose(file);
            return -1;
        }

        if (strcmp(existing_user, username) == 0) {
            free(existing_user);
            fclose(file);
            return 0;
        }

        free(existing_user);
    }

    fseek(file, 0, SEEK_END); //user does not exist then Move to the end of the file and write
    fprintf(file, "%ld %ld ", ulen, plen);
    fwrite(username, 1, ulen, file);
    fwrite(password, 1, plen, file);
    fclose(file);
    return 1;
}


int check_user_password(const char* file_name, const char* username, const char* password) {
    // implement me
    FILE* file;
    long ulen, plen;

    file = fopen(file_name, "r"); // reading mode
    if (!file) return -1; // the file does not exist

    while (1) {  // check username and password if exist
        if (fscanf(file, "%ld %ld ", &ulen, &plen) != 2) break;

        char* uname = (char*)malloc(ulen + 1);
        if (!uname) { 
          fclose(file);
          return -1; 
        } 
        if (fread(uname, 1, ulen, file) != ulen) { //read username
            free(uname); 
            fclose(file);
            return -1;
        }
        uname[ulen] = '\0'; //the last digit

        char* pword = (char*)malloc(plen + 1);
        if (!pword) { 
          free(uname); 
          fclose(file); 
          return -1; 
        }
        if (fread(pword, 1, plen, file) != plen) { // read password
            free(uname); 
            free(pword); 
            fclose(file); 
            return -1;
        }
        pword[plen] = '\0';

        if (strcmp(uname, username) == 0) {
            int result = strcmp(pword, password) == 0 ? 1 : -3;
            free(uname);
            free(pword); //release memory
            fclose(file);
            return result; // return 1 2 3 status code;
        }

        free(uname);
        free(pword);
    }

    fclose(file);
    return -2; // user DNE
}

/* Question 2 */

//int64_t fib3(unsigned int n) {
//  if (n == 0 || n ==1) // fib3(0) = 0, fib3(1) = 0
//  {
//    return 0;
//  }
//  if (n == 2) // fib3(2) = 1
//  {
//    return 1;
//  }
//  return fib3(n-1) + fib3(n-2) + fib3(n-3); //fib3(n) = fib3(n-1) + fib3(n-2) + fib3(n-3) for all n>=3 
//}

int64_t fib3(unsigned int n) {
    if (n == 0 || n == 1) return 0; //As recusive version, set a base case when n is 0 or 1, it will return 0
    if (n == 2) return 1; // when n is 2, return 1;
    
    int64_t a = 0, b = 0, c = 1, temp;
    for (unsigned int i = 3; i <= n; ++i) {
        temp = a + b + c; //Store everytime sum to the temp, and sum up at the end
        a = b;
        b = c;
        c = temp; //exanchge value
    }
    return c;
}

/* Question 3 */

int count_tokens(const char* str, char delim) {
  int cnt = 0; //counting
  int in_token = 0; //set up repeated status
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == delim) //find target;
    {
      in_token = 0;
    } else {
      if (in_token == 0) //check if repeat
      {
        cnt++;
        in_token = 1; //when it is a repeated target, set status to 1;
      }  
    }
  }
  return cnt;
}

char** get_tokens(const char* str, char delim) {
  // implement me
  int tokens = count_tokens(str,delim); // use pervious function to count token
  char** res = (char**)malloc((tokens + 1) * sizeof(char*));
  int start = -1;
  int idx = 0;
  // go through the whole string
  for (int i = 0; ; i++)
  {
    if (str[i] == delim || str[i] == '\0')
    {
      if(start != -1){ //Indicates that a token was entered before, and now it has ended
        int len = i - start;
        res[idx] = (char*)malloc(len+1); //Allocate memory for this token
        strncpy(res[idx], &str[start],len);
        res[idx][len] = '\0';
        idx++;
        start = -1;
      }
      if(str[i] == '\0') break;
    }else{ //If it is a non-separator and was not inside a token before
        if ((start == -1))
        {
          start = i;
        }
        
      }
    }
  res[idx] = NULL;
  return res;
}

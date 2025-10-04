#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

int add_user_password(const char* file_name, const char* username, const char* password) {
  // implement me
  FILE *file;
  long ulen = strlen(username);
  long plen = strlen(password);
  file = fopen(file_name, "r+");
  if(!file){ 
    file = fopen(file_name,"w"); //If file does not exist, make a new file right now.
    if (!file) // if fail to opne of make a file
    {
      return -1;
    }
    fprintf(file, "%ld %ld\n", ulen,plen);
    fwrite(username, 1, ulen, file); //Write down username and password
    fwrite(password, 1, plen, file);
    fclose(file);
    return 1;
  }

  while (1) // If the file exist
  {
    long existing_ulen;
    long existing_plen;
    if(fscanf(file, "%ld %ld\n", &existing_ulen, existing_plen) != 2){ // then check the data if integrity
      break;
    }
    char *existing_user = (char*)malloc(existing_ulen + 1); //Allocate memory for the username that is about to be read
    if (!existing_user)
    {
      fclose(file);
      return -1;
    }
    fread(existing_user, 1, existing_ulen, file); 
    existing_user[existing_ulen] = '\0';

    // Skip the password part corresponding to this user (because we only want to check if the username exists here)
    fseek(file, existing_plen,SEEK_CUR);
    if (strcmp(existing_user, username)==0)
    {
      free(existing_user);
      fclose(file);
      return 0;
    }
    free(existing_user);
  }
  fseek(file, 0, SEEK_END); //user does not exist then Move to the end of the file and write
  fprintf(file, "%ld %ld\n", ulen, plen);
  fwrite(username, 1, ulen, file);
  fwrite(password, 1, plen, file);
  fclose(file);

  return 1;
}

int check_user_password(const char* file_name, const char* username, const char* password) {
  // implement me
  FILE *file;
  long ulen, plen;
  long input_ulen = strlen(username);
  long input_plen = strlen(password);
  file = fopen(file_name, "r"); // reading mode
  if (!file) {
      return -1; // the file does not exist
  }
  while (1) {
      // check username and password if exist
      if (fscanf(file, "%ld %ld\n", &ulen, &plen) != 2) {
          break;
      }
      // read username
      char *uname = (char*)malloc(ulen+ 1);
      if (!uname)
      { 
        fclose(file); return -1; 
      }
      fread(uname, 1, ulen, file);
      uname[ulen] = '\0';
      // read password
      char *pword = (char*)malloc(plen +1);
      if (!pword) 
      { 
        free(uname); 
        fclose(file);
        return -1; 
      }
      fread(pword, 1, plen, file);
      pword[plen] = '\0';
      // check username
      if (strcmp(uname, username) == 0) {
          int result;
          if (strcmp(pword, password) == 0) {
              result = 1;  
          } else {
              result = -3; // The username exists but the password does not match.
          }
          free(uname);
          free(pword);
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

int64_t fib3(unsigned int n) {
  if (n == 0 || n ==1) // fib3(0) = 0, fib3(1) = 0
  {
    return 0;
  }
  if (n == 2) // fib3(2) = 1
  {
    return 1;
  }
  return fib3(n-1) + fib3(n-2) + fib3(n-3); //fib3(n) = fib3(n-1) + fib3(n-2) + fib3(n-3) for all n>=3 
}


/* Question 3 */

int count_tokens(const char* str, char delim) {
  int cnt = 0;
  int in_token = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == delim)
    {
      in_token = 0;
    } else {
      if (in_token == 0)
      {
        cnt++;
        in_token = 1;
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"


int main(int argc, char *argv[]){
 char * test = "; comment\n$testing$ ++- 1\n(display \"Hello, world!\")";
 size_t test_len = strlen(test);
 token_t * tokens = lex(test, test_len);
 free(tokens);
 return 0;
}

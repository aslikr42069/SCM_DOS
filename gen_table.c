#include <stdio.h>
#include <string.h>

int main(){
 printf("void  (*lex_lookup[])(char *, size_t, size_t *,\n");
 printf("                      token_t *, size_t *) = {\n");
 for(int row = 0; row < 32; row++){
  for(int j = 0; j < 4; j++){
   int i = (row * 4) + j;
   if((i >= 'a' && i <= 'z') ||
     (i >= 'A' && i <= 'Z') ||
     i == '!' || i == '$'   ||
     i == '%' || i == '&'   ||
     i == '*' || i == '/'   ||
     i == ':' || i == '<'   ||
     i == '=' || i == '>'   ||
     i == '?' || i == '~'   ||
     i == '_' || i == '^'
    ){
   printf("lex_ident, ");
   } else if(i >= '0' && i <= '9') {
   printf("lex_num, ");
   } else if(i == ';'){
   printf("lex_comment, ");
  } else if(i == '(' || i == ')'){
   printf("lex_paren, ");
  } else if(i == '\"'){
   printf("lex_string, ");
  }else {
   printf("incr_nop, ");
  }
  }
  printf("\n");
 }
 printf("\n};");
 return 0;
}

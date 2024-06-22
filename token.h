#ifndef TOKEN_H_
#define TOKEN_H_ 1
#define ASCII_MAGIC 128

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
enum lex_token_types{L_PAREN, R_PAREN, IDENT,
                     NUMB, STRING, HASHTAG, END};

typedef struct token_t{
 int8_t type;
 size_t start;
 size_t end;
}token_t;

token_t * lex         (char * str, size_t len);

void   lex_ident   (char * str, size_t len, size_t * pos,
                       token_t * tokens, size_t * count);
void   lex_num     (char * str, size_t len, size_t * pos,
                       token_t * tokens, size_t * count);
void   incr_nop    (char * str, size_t len, size_t * pos,
                       token_t * tokens, size_t * count);
void   lex_comment (char * str, size_t len, size_t * pos,
                       token_t * tokens, size_t * count);
void   lex_paren   (char * str, size_t len, size_t * pos,
                       token_t * tokens, size_t * count);
void   lex_string  (char * str, size_t len, size_t * pos,
                       token_t * tokens, size_t * count);

#endif

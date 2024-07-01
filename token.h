#ifndef TOKEN_H_
#define TOKEN_H_ 1
#define ASCII_MAGIC 128

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum lex_token_types{L_PAREN, R_PAREN, IDENT,
                     NUMB, STRING, HASHTAG,
                     DEF_KEYWORD, END};

typedef struct token_t{
 uint8_t type;
 uint32_t start; // MS-DOS has a max file-size of 4GB, which 32 bits can handle
 uint32_t end;
}token_t; // TODO: Find a way to optimize this struct size

token_t * lex         (char * str, uint32_t len);

void   lex_ident   (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);
void   lex_num     (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);
void   incr_nop    (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);
void   lex_comment (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);
void   lex_paren   (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);
void   lex_string  (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);
void   lex_hashtag (char * str, uint32_t len, uint32_t * pos,
                       token_t * tokens, uint32_t * count);

#endif

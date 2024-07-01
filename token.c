#include "token.h"
#define INIT_TOKENS 4

void  (*lex_lookup[])(char *, uint32_t, uint32_t *,
                      token_t *, uint32_t *) = {
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  incr_nop,  incr_nop,   incr_nop, 
 incr_nop,  lex_ident, lex_string, lex_hashtag, 
 lex_ident, lex_ident, lex_ident,  incr_nop, 
 lex_paren, lex_paren, lex_ident,  lex_ident, 
 incr_nop,  lex_ident, incr_nop,   lex_ident, 
 lex_num,   lex_num,   lex_num,    lex_num, 
 lex_num,   lex_num,   lex_num,    lex_num, 
 lex_num,   lex_num,   lex_ident,  lex_comment, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 incr_nop,  lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  incr_nop, 
 incr_nop,  incr_nop,  lex_ident,  lex_ident, 
 incr_nop,  lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  lex_ident, 
 lex_ident, lex_ident, lex_ident,  incr_nop, 
 incr_nop,  incr_nop,  lex_ident,  incr_nop,
};

token_t * lex(char * str, uint32_t len){
 uint32_t token_count   = INIT_TOKENS;
 uint32_t actual_tokens = 0;
 uint32_t pos           = 0;
 char   curr          = 0;
 token_t * tokens = calloc(INIT_TOKENS, sizeof(token_t));
 
 while(pos < len){
  if(actual_tokens == token_count){
   token_count = token_count * 2;
   tokens = reallocarray(tokens, token_count, sizeof(token_t));
  }
  if(str[pos] < 0 || str[pos] > ASCII_MAGIC){
   pos++;
  } else {
   curr = str[pos];
   lex_lookup[curr](str, len, &pos, tokens, &actual_tokens);
  }
 }
 if(actual_tokens == token_count){
   token_count = token_count * 2;
   tokens = reallocarray(tokens, token_count, sizeof(token_t));
 }
 tokens[actual_tokens].type = END;

 for(int i = 0; i < actual_tokens; i++){
  if(tokens[i].type == IDENT){
   if(strncmp(&str[tokens[i].start], "define", 6) == 0){
    tokens[i].type = DEF_KEYWORD;
   }
  }
 } 

 return tokens;
}

void lex_ident (char * str, uint32_t len, uint32_t * pos,
                token_t * tokens, uint32_t * count){
//------------------------------------------------ 
 char curr = str[(*pos)];
 tokens[(*count)].type = IDENT;
 tokens[(*count)].start = *pos;
  while((
   (curr >= 'a' && curr <= 'z') ||
   (curr >= 'A' && curr <= 'Z') ||
   (curr >= '0' && curr <= '9') ||
   curr == '!' || curr == '$'   ||
   curr == '%' || curr == '&'   ||
   curr == '*' || curr == '/'   ||
   curr == ':' || curr == '<'   ||
   curr == '=' || curr == '>'   ||
   curr == '?' || curr == '~'   ||
   curr == '_' || curr == '^'   ||
   curr == '.' || curr == '+'   ||
   curr == '-'
  ) && *pos < len){
  (*pos)++;
  curr = str[(*pos)];
 }
 tokens[(*count)].end = *pos; 
 (*count)++;
 return;
//------------------------------------------------
}

void lex_num (char * str, uint32_t len, uint32_t * pos,
                token_t * tokens, uint32_t * count){
//----------------------------------------------
 char curr = str[(*pos)];
 tokens[(*count)].type = NUMB;
 tokens[(*count)].start = *pos;
 while((
 curr >= '0' && curr <= '9'
 ) && *pos < len){
  (*pos)++;
  curr = str[(*pos)];
 }
 tokens[(*count)].end = *pos; 
 (*count)++;
 return;
//----------------------------------------------
}

void lex_paren (char * str, uint32_t len, uint32_t * pos,
                token_t * tokens, uint32_t * count){
//----------------------------------------------
 if(str[(*pos)] == '('){
  tokens[(*count)].type = L_PAREN;
 } else {
  tokens[(*count)].type = R_PAREN;
 }
 tokens[(*count)].start = *pos;
 (*pos)++;
 tokens[(*count)].end = *pos;
 (*count)++;
 return;
//----------------------------------------------
}

void lex_comment (char * str, uint32_t len, uint32_t * pos,
                  token_t * tokens, uint32_t * count){
//------------------------------------------------
 while(str[(*pos)] != '\n' && *pos < len){
  (*pos)++;
 }
 return;
//------------------------------------------------
}

void incr_nop (char * str, uint32_t len, uint32_t * pos,
               token_t * tokens, uint32_t * count){
//---------------------------------------------
 (*pos)++;
 return;
//---------------------------------------------
}

void lex_string (char * str, uint32_t len, uint32_t * pos,
                 token_t * tokens, uint32_t * count){
//-----------------------------------------------
 tokens[(*count)].start = *pos;
 tokens[(*count)].type = STRING;
 (*pos)++;
 while(str[(*pos)] != '\"' && *pos < len){
  (*pos)++;
 }
 (*pos)++;
 tokens[(*count)].end = *pos;
 (*count)++;
 return;
//-----------------------------------------------
}

void lex_hashtag (char * str, uint32_t len, uint32_t * pos,
                  token_t * tokens, uint32_t * count){
//------------------------------------------------
 tokens[(*count)].type = HASHTAG;
 tokens[(*count)].start = *pos;
 (*pos)++;
 tokens[(*count)].end = *pos;
 (*count)++;
//------------------------------------------------
}



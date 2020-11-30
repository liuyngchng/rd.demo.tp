#include "hiredis.h"

/**
 * push elememt "elmt" to the head of a list named "key".
 */
void push(char* key, char* elmt); 

/**
 * pop element from the bottom of a list named "key".
 */
char* pop(char* key); 

/**
 * trim list name "key" reserve element from "start" to "stop".
 * "start" index start from 0.
 */
void trim(char* key, int start, int stop);

/**
 * get the element number in list name "key".
 */
int get_len(char* key); 

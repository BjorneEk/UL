

/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 * assert and warning functions
 *
 *==========================================================*/

#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/**
 *  display warning functions
 **/
void log_warning(const char * msg)
{
  printf("[\033[33;1;4mWarning\033[0m]: %s\n", msg);
}

void log_warning_str(const char * msg, const char * str)
{
  printf("[\033[33;1;4mWarning\033[0m]: %s: '%s'\n", msg, str);
}

void log_warning_char(const char * msg, char c)
{
  printf("[\033[33;1;4mWarning\033[0m]: %s: %c\n", msg, c);
}

void log_warning_int(const char * msg, i32_t i)
{
  printf("[\033[33;1;4mWarning\033[0m]: %s: %i\n", msg, i);
}

/**
 *  display error functions
 **/
void log_error(const char * msg)
{
  fprintf(stderr, "[\033[31;1;4mError\033[0m]: %s | %s\n",msg, strerror( errno ));
}

void log_error_str(const char * msg, const char * str)
{
  fprintf(stderr, "[\033[31;1;4mError\033[0m]: %s: '%s' | %s\n",msg, str, strerror( errno ));
}

void log_error_char(const char * msg, char c)
{
  fprintf(stderr, "[\033[31;1;4mError\033[0m]: %s: %c\n",msg, c);
}

void log_error_int(const char * msg, int i)
{
  fprintf(stderr, "[\033[31;1;4mError\033[0m]: %s: %i\n",msg, i);
}


/**
 *  simple assert function, display error and exit with exit status 1
 *  if assertion is false

void assert(u8_t assertion, const char * msg)
{
  if (assertion) return;
  log_error_str("Assert", msg);
  exit(1);
}
*/


/**
 *  display warning when assertion is false
 *
void assert_w(u8_t assertion, const char * msg)
{
  if(!assertion) log_warning(msg);
}
*/
/**
 *  display error when assertion is false
 *
void assert_err(u8_t assertion, const char * msg)
{
  if(!assertion) log_error(msg);
}
*/

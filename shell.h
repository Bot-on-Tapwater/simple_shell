#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64       /* max number of whitespace/" " */

#define MAX_ARGS 64
#define MAX_PATH 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;

typedef struct linkedList
{
	char *str;
	struct linkedList *next;
} LL;

/* char *read_input(void); */
char* command_checker(char *command);
char **parse_input(char *line);
int execute_command(char **args, char *path[]);
void printString(char *str);
int getStringLength(const char *str);
void writeStringToStderr(char *str);
char *_getenv(const char *name);
char *concatenateStrings(char *str1, char *str2);
char *myStrcpy(char *dest, const char *src);
char *myStrcat(char *dest, const char *src);
int myStrncmp(const char *s1, const char *s2, size_t n);
void *my_memcpy(void *dest, const void *src, size_t n);
void *my_realloc(void *ptr, size_t size);
char **get_path_directories();
int printenv(void);
char *read_input(void);
int tokenize(char *input, char **tokens, int max_tokens);
void execute(char **tokens);
int my_strcmp(const char *str1, const char *str2);
void execute_builtins(char *token, char **env);
char * str_dup(char *str);
char* get_PATH(char *args);
void print_strings(char **strings);
LL *path_list();
void add_node(LL **head_ref, char *str);
void free_list(LL *head);
void print_list(LL *head);
char *find_executable(char *command, LL *path_list);
char *my_strdup(const char *str);

#endif

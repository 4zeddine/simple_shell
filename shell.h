#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define DELIMS " \t\n"
#define CALL_GETLINE 0

extern char **environ;

/**
 * struct singlylist - a singly linked list
 * @num: the number of field
 * @str: input string
 * @next: points to the next node
 */
typedef struct singlylist
{
	int num;
	char *str;
	struct singlylist *next;
} singl_t;

/**
 *struct shell_data - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@alias: alias node
 *@argc: argument counter
 *@args: contains arguments generated from getline
 *@argv: contains arguments strings generated from arg
 *@cmd_buff: address of pointer to cmd_buff
 *@cmd_opperators: CMD opperators ||, &&, ;
 *@his_counter: counter for line number of history
 *@error_num: error numbere for exit
 *@env: imported copy of environ
 *@environ: custom modified copy of environ from env
 *@env_changed: check if environ was changed
 *@fname: program filename
 *@history: history node
 *@linecount_flag: counts the lines of input
 *@line_count: error line counter
 *@path: string of the path for the current command
 *@readfd: file from which to read line input
 *@status: the status of the last executed command
 */
typedef struct shell_data
{
	singl_t *alias;
	int argc;
	char *args;
	char **argv;
	char **cmd_buff;
	int cmd_opperators;
	int his_counter;
	int error_num;
	singl_t *env;
	char **environ;
	int env_changed;
	char *fname;
	singl_t *history;
	int linecount_flag;
	unsigned int line_count;
	char *path;
	int readfd;
	int status;

} shell_t;

/**
 *struct builtins - contains the builtins and the executing functions
 *@flag: builtin command flag
 *@func: builtin function
 */
typedef struct builtins
{
	char *flag;
	int (*func)(shell_t *);
} builtins_t;


/* Printing String */
void print_string(char *str);
int print_char(char l);
int print_string_sfd(char *str, int fd);
int print_fd(char c, int fd);

/* Handling Strings */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char *check_start(const char *start, const char *input);

/* Handling Conversion */
char *convert_number(long int num, int base, int flags);
int replace_alias(shell_t *data);
int replace_vars(shell_t *data);
int replace_string(char **old, char *new);

/* Handling line */
int _getline(shell_t *data, char **buffer, size_t *length);
ssize_t get_command(shell_t *data);
ssize_t command_buffer(shell_t *data, char **buf, size_t *len);
void handl_signal(int signal);

/* Handling Errors*/
void print_err(char *str);
int print_char_err(char c);
void print_error(shell_t *data, char *str_e);
int print_d(int input, int fd);
int err_to_i(char *str);
void remove_comments(char *buffer);
void check_chain(shell_t *data, char *buff, size_t *idx, size_t i, size_t len);

/* Check Delimiter */
int is_delim(char l, char *delim);

/* Handling Builtins*/
int get_builtin(shell_t *data);
int _env(shell_t *data);
int _history(shell_t *data);
int __exit(shell_t *data);
int _help(shell_t *data);
int _set_env(shell_t *data);
int _unset_env(shell_t *data);
int _cd(shell_t *data);
int _alias(shell_t *data);

/* Handling Command*/
void check_cmd(shell_t *data);
int is_cmd(shell_t *data, char *path);
char *find_path(shell_t *data, char *path_str, char *cmd);
void exec_cmd(shell_t *data);
int is_opperator(shell_t *data, char *buf, size_t *p);
char *dup_chars(char *pathstr, int start, int stop);

/* Handling Shell */
int shell_loop(shell_t *data, char **argv);
ssize_t read_buffer(shell_t *data, char *buffer, size_t *i);

/* Handling History*/
int set_history(shell_t *data);
char *get_hfile(shell_t *data);
int build_hlist(shell_t *data, char *buffer, int counter);
int read_history(shell_t *data);
int his_recounter(shell_t *data);

/* Handling Lists */
size_t print_list_str(const singl_t *list);
singl_t *add_node_start(singl_t **head, const char *str, int num);
singl_t *add_node_end(singl_t **head, const char *str, int num);
int delete_node_at_index(singl_t **head, unsigned int index);
void free_list(singl_t **head);
size_t print_list(const singl_t *list);
ssize_t get_node_index(singl_t *head, singl_t *node);
singl_t *check_node_start(singl_t *node, char *prefix, char c);
char **list_to_strings(singl_t *head);
size_t list_size(const singl_t *head);

/* Handling Alias */
int init_alias(shell_t *data, char *str);
int unset_alias(shell_t *data, char *str);
int print_alias(singl_t *node);

/* Handling Memory*/
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int free_p(void **ptr);
void free_array(char **array);
void init_data(shell_t *data, char **argv);
void free_data(shell_t *data, int bool);

/* Handling env */
char **get_environ(shell_t *data);
char *_getenv(shell_t *data, const char *name);
int populate_env_list(shell_t *data);
int _setenv(shell_t *data, char *var, char *value);
int _unsetenv(shell_t *data, char *var);
int populate_env_list(shell_t *data);

/* Handling strtok*/
char **__strtok(char *str, char *d);
char **__strtok2(char *str, char d);

#endif

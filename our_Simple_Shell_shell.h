#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* write/for buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* To command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* ourtion_convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - The singly linked list
 * @num: All the number field
 * @str: The string
 * @next: The points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - is to contains pseudo-arguements to
 * pass into a function,allowing uniform prototype for
 * function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @path: string path for the current command
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @env_changed: on if environ was changed
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - This contains a builtin string and related function
 * @type: The builtin command flag
 * @func: The function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* Represent_Our_Simple_Shell_loop.c */
int ourtion_hsh(info_t *, char **);
int ourtion_find_builtin(info_t *);
void ourtion_find_cmd(info_t *);
void ourtion_fork_cmd(info_t *);

/* Represent_Our_Simple_Shell_parser.c */
int ourtion_is_cmd(info_t *, char *);
char *ourtion_dup_chars(char *, int, int);
char *ourtion_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* Represent_Our_Simple_Shell_errors.c */
void ourtion__eputs(char *);
int ourtion__eputchar(char);
int ourtion__putfd(char c, int fd);
int ourtion__putsfd(char *str, int fd);

/* Represent_Our_Simple_Shell_string.c */
int ourtion__strlen(char *);
int ourtion__strcmp(char *, char *);
char *ourtion_starts_with(const char *, const char *);
char *ourtion__strcat(char *, char *);

/* Represent_Our_Simple_Shell_string1.c */
char *ourtion__strcpy(char *, char *);
char *ourtion__strdup(const char *);
void ourtion__puts(char *);
int ourtion__putchar(char);

/* Represent_Our_Simple_Shell_exits.c */
char *ourtion__strncpy(char *, char *, int);
char *ourtion__strncat(char *, char *, int);
char *ourtion__strchr(char *, char);

/* Represent_Our_Simple_Shell_tokenizer.c */
char **ourtion_strtow(char *, char *);
char **ourtion_strtow2(char *, char);

/* Represent_Our_Simple_Shell_realloc.c */
char *ourtion__memset(char *, char, unsigned int);
void ourtion_ffree(char **);
void *ourtion__realloc(void *, unsigned int, unsigned int);

/* Represent_Our_Simple_Shell_memory.c */
int ourtion_bfree(void **);

/* Represent_Our_Simple_Shell_atoi.c */
int ourtion_interactive(info_t *);
int ourtion_is_delim(char, char *);
int ourtion__isalpha(int);
int ourtion__atoi(char *);

/* Represent_Our_Simple_Shell_errors1.c */
int ourtion__erratoi(char *);
void ourtion_print_error(info_t *, char *);
int ourtion_print_d(int, int);
char *ourtion_convert_number(long int, int, int);
void ourtion_remove_comments(char *);

/* Represent_Our_Simple_Shell_builtin1.c */
int ourtion_ourexit(info_t *);
int ourtion__ourcd(info_t *);
int ourtion__ourhelp(info_t *);

/* Represent_Our_Simple_Shell_builtin2.c */
int ourtion__ourhistory(info_t *);
int ourtion__ouralias(info_t *);

/*Represent_Our_Simple_Shell_getline.c */
ssize_t ourtion_get_input(info_t *);
int ourtion__getline(info_t *, char **, size_t *);
void ourtion_sigintHandler(int);

/* Represent_Our_Simple_Shell_getinfo.c */
void ourtion_clear_info(info_t *);
void ourtion_set_info(info_t *, char **);
void ourtion_free_info(info_t *, int);

/* Represent_Our_Simple_Shell_environ.c */
char *ourtion__getenv(info_t *, const char *);
int ourtion__ourenv(info_t *);
int ourtion__oursetenv(info_t *);
int ourtion__ourunsetenv(info_t *);
int ourtion_populate_env_list(info_t *);

/* Represent_Our_Simple_Shell_getenv.c */
char **ourtion_get_environ(info_t *);
int ourtion__unsetenv(info_t *, char *);
int ourtion__setenv(info_t *, char *, char *);

/* Represent_Our_Simple_Shell_history.c */
char *ourtion_get_history_file(info_t *info);
int ourtion_write_history(info_t *info);
int ourtion_read_history(info_t *info);
int ourtion_build_history_list(info_t *info, char *buf, int linecount);
int ourtion_renumber_history(info_t *info);

/* Represent_Our_Simple_Shell_lists1.c */
list_t *ourtion_add_node(list_t **, const char *, int);
list_t *ourtion_add_node_end(list_t **, const char *, int);
size_t ourtion_print_list_str(const list_t *);
int ourtion_delete_node_at_index(list_t **, unsigned int);
void ourtion_free_list(list_t **);

/* Represent_Our_Simple_Shell_lists2.c */
size_t ourtion_list_len(const list_t *);
char **ourtion_list_to_strings(list_t *);
size_t ourtion_print_list(const list_t *);
list_t *ourtion_node_starts_with(list_t *, char *, char);
ssize_t ourtion_get_node_index(list_t *, list_t *);

/* Represent_Our_Simple_Shell_vars.c */
int ourtion_is_chain(info_t *, char *, size_t *);
void ourtion_check_chain(info_t *, char *, size_t *, size_t, size_t);
int ourtion_replace_alias(info_t *);
int ourtion_replace_vars(info_t *);
int ourtion_replace_string(char **, char *);

#endif

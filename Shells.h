#ifndef SHELLS_H
#define SHELLS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <limits.h>

#define TRUE 1
#define FALSE !TRUE
#define MAX_HOSTNAME_LEN 1024
#define MAX_CMD_LEN 1024
#define LIM 256
#define LINEMAX 1024
#define LSH_RL_BUFSIZE 1024
#define TOK_DELIM " \t\r\n\a\""

/*signal handlers*/
void _child_handler(void);
void _int_handler(void);
int newProc(char **tp);

/*Shell pid | pgid | terminal modes*/
static pid_t __attribute__ ((unused)) PID_SH;
static pid_t __attribute__ ((unused)) PGID_SH;
static int __attribute__ ((unused)) INTERACTIVE_SH;
static struct termios __attribute__ ((unused)) MOD_SH;
static char __attribute__ ((unused)) *current_dir;
extern char __attribute__ ((unused)) **environ;
struct sigaction act_child;
struct sigaction act_int;
int no_prompt;
pid_t pid;

void shPpt(void);
int dirSwitch(char *args[]);
int envmgt(char *args[], int alt);
void handler(char *args[]);
char *lsh_readln(void);
void uninteractive(void);
char *readstr(void);
char **divline(char *ln);
int execar(char **args);
int ord(char *args[]);
void progStart(char **args, int bg);
void filo(char *args[], char *inputFile, char *outputFile, int opt);
void begin(void);

#endif

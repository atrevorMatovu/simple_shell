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
#define _DELIM " \t\r\n\a\""

/*signal handlers*/
void sig_child(int t);
void sig_int(int t);
int newProc(char **tp);

/*Shell pid | pgid | terminal modes*/
static pid_t shellPGID;
static pid_t shellPID;
static int SH_INTERACTIVE;
static char *currentDir;
extern char **environ;
struct sigaction childAction;
struct sigaction intAction;
int noPrompt;
pid_t pid;

void shPpt(void);
int dirSwitch(char *args[]);
int envmgt(char *args[], int alt);
void tunnels(char *args[]);
char *readln(void);
void uninteractive(void);
char *readstr(void);
char **divline(char *ln);
int execar(char **args);
int ord(char *args[]);
void progStart(char **args, int bg);
void filo(char *args[], char *inputFile, char *outputFile, int opt);
void begin(void);

#endif

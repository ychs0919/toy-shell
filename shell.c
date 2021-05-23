#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30
#define LEN_CWD	100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;

	
    while (true) {
        char *s;
        int len; 
		
		char hostname[LEN_HOSTNAME + 1];
		memset(hostname, 0x00, sizeof(hostname));
		gethostname(hostname, LEN_HOSTNAME);
		printf("\033[0;92;4m%s@%s\033[0m:", getpwuid(getuid())->pw_name, hostname);

		char cwd[LEN_CWD + 1];
		memset(cwd, 0x00, sizeof(cwd));
		getcwd(cwd, LEN_CWD);
		printf("\033[0;94;4m%s\033[0m$",cwd);

        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        printf("[%s]\n", command);

		if (strcmp(command, "exit") == 0) {
			printf("\033[1;31;6mWaiting for 3seconds\033[0m\n");
			printf("\033[1;31m3\033[0m\n");
			sleep(1);
			printf("\033[1;31m2\033[0m\n");
			sleep(1);
			printf("\033[1;31m1\033[0m\n");
			sleep(1);
			return 0;
		}
		
		
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("\033[35;3m[Child process terminated]\033[0m\n");
            if (WIFEXITED(status)) {
                printf("\033[35;3m[Exit status is %d]\033[0m\n", WEXITSTATUS(status)); 
			}
			
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
			if (strcmp(command, "ls -l") == 0) {

				system(command);
				return 0;

			}

			if (strcmp(command, "ls") == 0) {

				system(command);
				return 0;

			}
			if (strcmp(command, "pstree") == 0) {

				system(command);
				return 0;

			}
			if (strcmp(command, "clear") == 0) {

				system(command);
				return 0;

			}
			if (strcmp(command, "command") == 0) {

				printf("\033[1;33;1mavailable command list\n*ls\n*ls -l\n*pstree\n*exit\n*clear\n\033[0m");
				return 0;

			}
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
    }
    return 0;
}

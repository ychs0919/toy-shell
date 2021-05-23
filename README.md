# toy-shell

**How to Add Features**
---------------------------------------------------
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>

#define LEN_HOSTNAME	30

int main(void)
{
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    printf("username: %s\n", getpwuid(getuid())->pw_name);

    gethostname(hostname, LEN_HOSTNAME);
    printf("hostname: %s\n", hostname);

    return 0;
}
---------------------------------------------------
I implemented 'hostname' and 'username' with the files uploaded by the professor.
I made it in cwd referring to the file that professor uploaded.



----------------------------------------------------
if (strcmp(command, "ls") == 0) {

	system(command);
	return 0;

}
----------------------------------------------------  
This command that enables the operation of the letter entered between " and ".
I made functions using this.
 
**added functions**
exit
ls
ls -l
clear
pstree(I wrote down what I learned in class.)
command(It's just to let you know what commands are in the shell I created.)

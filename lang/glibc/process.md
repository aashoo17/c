# Process

## Process id
```c
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);
```
### get the process id and its parent's process id
```c
#include <stdio.h>
#include <unistd.h>

int main(){
    //process id
    printf("%d",getpid());
    //parent process id
    printf("%d",getpid());
}
```

## Environment variables
function signatures
```c
#include <stdlib.h>
char *getenv(const char *name);
int putenv(char *string);
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);
```

### get the list of all environment variables and print on stdout

```c
#include <stdio.h>
//environ hold an array of pointers to all the environment variables
//in the form "KEY=VALUE"
//but environ is not visible by default to any process
//use extern to make the variable visible
//TODO: check the extern working
extern char **environ;
int main(){
    //loop over environ untill *environ is not NULL
    while(*environ != NULL){
        //print the value on stdout
        puts(*environ);
        //increment the pointer to get the next env in the new iteration of loop
        *environ++;
    }
}
```

### get the env value of a perticular key/value pair using key
if say SHELL is variable which keeps record of the current shell get the value of SHELL
```c
#include <stdio.h>
//header to include getenv
#include <stdlib.h>

int main(){
    //get value of SHELL env var
    char *env = getenv("SHELL");
    //print on stdout
    puts(env);
}
```

### modify the env variable using its name in key
modify the value of an env variable
say change the SHELL env var to /bin/zsh i.e. z-shell  


```c
#include <stdio.h>
//header to include putenv
#include <stdlib.h>

int main(){
    //add the env variable with its value in the form "KEY=VALUE"
    //if KEY alread exists its value will be overwritten
    putenv("MYNAME=ASHU");
    puts(getenv("MYNAME"));
}
```

```c
#include <stdio.h>
//header to include setenv
#include <stdlib.h>

int main(){
    //set the value of a env var
    //we can control if value already exists should be overwritten or not
    setenv("SHELL","/bin/bash",1);
    puts(getenv("SHELL"));
}
```

### unset the value of a env variable
unset say SHELL so its like SHELL has no value or not defined


```c
#include <stdio.h>
//header to include unsetenv
#include <stdlib.h>

int main(){
    //set the value of a env var
    //we can control if value already exists should be overwritten or not
    unsetenv("SHELL");
    //prints null
    puts(getenv("SHELL"));
}
```

## child process => creation, termination, wait
```c
#include <unistd.h>
void _exit(int status);

#include <stdlib.h>
void exit(int status);

#include <sys/wait.h> 
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);


```
### process creation
```c
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid = fork();
}
```

### terminate the process





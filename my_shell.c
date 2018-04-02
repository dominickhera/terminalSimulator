#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <time.h>

extern char **getln();
void sigHandler(int sig);

int main() 
{
    int i,j, maxRand = 0, minRand = 0, addInt, count;
    char fileName[256];
    int backgroundCheck = 0;
    int randCheck = 0;
    int fileNameCheck = 0;
    int fileRedirectCheck = 0;
    char **args; 
    pid_t child_pid;
    FILE *fp;

    while(1) 
    {
        printf("/> ");
        args = getln();
        // printf("1\n");
        count = 0;
        for(i = 0; args[i] != NULL; i++)
        {
            count++;
        }
        // printf("2\n");

        if(strcmp(args[count - 1], "&") == 0)
        {
            backgroundCheck = 1;
            args[count - 1] = NULL;
        }
        // printf("3\n");

        for(int i = 0; i < count - 1; i++)
        {
            if(strcmp(args[i], ">") == 0)
            {
                fileNameCheck = 1;
                strcpy(fileName, args[i+1]);
                while(i != count - 1)
                {
                    args[i] = NULL;
                    i++;
                }
            }
            else if(strcmp(args[i], "<") == 0)
            {
                fileRedirectCheck = 1;
                strcpy(fileName, args[i+1]);
                while(i != count - 1)
                {
                    args[i] = NULL;
                    i++;
                }
            }
            else if(strcmp(args[i], "rand") == 0)
            {
                minRand = atoi(args[i + 1]);
                maxRand = atoi(args[i + 2]);
                randCheck = 1;
            }

        }
        // printf("4\n");
        if(fileNameCheck == 1)
        {
            fp = freopen(fileName, "w+", stdout);
        }
        // printf("5\n");
        if(fileRedirectCheck == 1)
        {
            if(access(fileName, F_OK) != -1)
            {
                // printf("6\n");
                fp = freopen(fileName, "r+", stdin);
            }
            else
            {
                printf("There was an error opening your file, %s...\n", fileName);
                // break;
                exit(0);
            }
        }
        // printf("7\n");
        // printf("count is %d\n", count);
        for(i = 0; args[i] != NULL; i++)
        {
            // printf("args[%s]\n", args[i]);
            if(count == 1)
            {
                if(strcmp(args[i], "exit") == 0)
                {
                    // printf("lol\n");
                    fclose(fp);
                    exit(1);
                }
                else
                { 

                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], args);
                        printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                    }

                    //             // fork();
                    // execvp(args[i], args);
                    // break;
                }
            }
            else if(count == 2)
            {

                if(backgroundCheck == 1)
                {
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        sigset(SIGINT, sigHandler);
                        execvp(args[i], &args[i]);
                        // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                    }
                    backgroundCheck = 0;
                    //             execvp(args[0], &args[i]);
                }
                else
                {
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], &args[i]);
                        //         // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                //         break;
            }
            else
            {
                if(backgroundCheck == 1)
                {
                    child_pid = fork();
                    if(child_pid == 0) 
                    {


                        // printf("this arg is %s\n", args[i]);
                        sigset(SIGINT, sigHandler);
                        execvp(args[i], &args[i]);

                        // printf("error\n");
                        exit(0);
                        // }
                }
                else
                {
                    wait(NULL);
                }

                //             execvp(args[0], &args[i]);
            }
            else
            {
                if(fileNameCheck == 1)
                {
                    // printf("hiya\n");
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], &args[i]);
                        //         // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);

                    }
                }
                else if(fileRedirectCheck == 1)
                {
                    // printf("uhhh\n");
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], &args[i]);

                        fclose(fp);
                        exit(0);
                        // printf("sort num\n");
                    }
                    else
                    {
                        // printf("why\n");
                        wait(NULL);
                    }
                    // printf("num\n");
                }
                else if(randCheck == 1)
                {
                    child_pid = fork();
                    if(child_pid == 0)
                    {
                        int range = maxRand - minRand + 1;
                        srand(time(NULL));
                        int randValue = rand() % range + minRand;
                        printf("A random value between %d and %d is %d\n", minRand, maxRand, randValue);

                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                // printf("num2\n");
                // }
                if(strcmp(args[i], "add") == 0)
                {
                    addInt = 0;
                    for(j = 1; j < count;j++)
                    {

                        for(int k = 0; k < strlen(args[j]); k++)
                        {
                            if(isalpha(args[j][k]))
                            {
                                int hexNum = (int)strtol(args[j],NULL, 16);
                                sprintf(args[j], "%d", hexNum);
                            }
                        }

                        addInt += atoi(args[j]);

                        if(j == count - 1)
                        {
                            printf("%s = ", args[j]);
                        }
                        else
                        {
                            printf("%s + ", args[j]);
                        }
                    }
                    printf("%d\n", addInt);
                    break;

                }

                // } 
        else if(strcmp(args[i], "args") == 0)
        {
            printf("argc = %d, args = ", count - 2);
            for(j = 1; j < count; j++)
            {
                if(j == count - 1)
                {
                    printf("%s\n", args[j]);
                }
                else
                {
                    printf("%s, ", args[j]);
                }
            }
        }
        else
        {
            child_pid = fork();
            if(child_pid == 0) 
            {
                execvp(args[i], &args[i]);
                //         // printf("error\n");
                exit(0);
            }
            else
            {
                wait(NULL);

            }
        }


    }

    if(fileNameCheck == 1)
    {
        // printf("lol\n");
        // fclose(fp);
        fileNameCheck = 0;
        // freopen(stdout, )
        freopen ("/dev/tty", "a", stdout);

        for(int k = 0; args[k] != NULL; i++)
        {
            // printf("1\n");
            child_pid = fork();
            // printf("2\n");
            if(child_pid == 0) 
            {

                execvp(args[k], &args[k]);

                exit(0);
                // break;
            }
            else
            {
                // printf("5\n");
                wait(NULL);
                // printf("6\n");
                break;
            }
        }

        printf("\nAbove output successfully copied output to File: %s\n", fileName);
    }
    else if(fileRedirectCheck == 1)
    {
        // printf("hreali\n");
        // fclose(fo);
        fileRedirectCheck = 0;

        fp = freopen("/dev/tty", "r+", stdin);
    }
    randCheck = 0;
    backgroundCheck = 0;
    // printf("done\n");
}
}
}
}

void sigHandler(int sig) {
    // printf("sig handler ay\n");
    exit(3);
}

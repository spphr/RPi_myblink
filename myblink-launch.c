#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char path[] = "home/rom/Freenove_Kit/Code/C_Code/mycode/myblink/myblink";
char buf[200];
int period = 2000;
int pON = 50;

/*start-stop-daemon -[param] [path] -- [args]*/
int start(void)
{
    sprintf(buf, "sudo start-stop-daemon -Sbvx %s -- %d %d", path, period, pON);
    system(buf);
    return 0;
}

void stop(void)
{
    sprintf(buf, "sudo start-stop-daemon -Kvx %s", path);
    system(buf);
}

int main(int argc, char *argv[])
{
    int num;

    if (argc < 2) {
        fprintf(stderr, "Requires 1 or more arguments\n");
        exit(EXIT_FAILURE);
    }
    else
        for (int i = 2; i < argc; i++) 
        {
            num = atoi(argv[i]);
            if (num < 0) 
            {
                fprintf(stderr, "Argv must be greater than or equal to 0\n");
                exit(EXIT_FAILURE);
            }
            switch(i)
            {
            case 2:
                period = num;
                break;
            case 3:
                pON = num;
                break;
            }
        }

    if (strcmp(argv[1], "start") == 0)
    {
        if (start())
        {
            fprintf(stderr, "Can't start programm");
            exit(EXIT_FAILURE);
        }
    } 
    else if (strcmp(argv[1], "stop") == 0)
        stop();

    return 0;
}
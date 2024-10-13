#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char path[] = "home/rom/Freenove_Kit/Code/C_Code/mycode/myblink/myblink";
char buf[200];
int period = 2000;
int pON = 50;

/*start-stop-daemon -[param] [path] -- [args]*/
int start(char *param)
{
    sprintf(buf, "sudo start-stop-daemon %s %s -- %d %d", param, path, period, pON);
    system(buf);
    return 0;
}

void stop(char *param)
{
    sprintf(buf, "sudo start-stop-daemon %s %s", param, path);
    system(buf);
}

int main(int argc, char *argv[])
{
    char buf[100];
    int num;

    if (argc < 2) {
        printf("Requires 1 or more arguments");
        return 0;
    }
    else
        for (int i = 2; i < argc; i++) 
        {
            num = atoi(argv[i]);
            if (num < 0) 
            {
                printf("ERROR: argv must be greater than or equal to 0");
                return 0;
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

    if (argv[1][1] == 'S')
        start(argv[1]);
    else if (argv[1][1] == 'K')
        stop(argv[1]);

    return 0;
}
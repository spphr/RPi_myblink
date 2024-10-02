#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define GPIO_PIN 17

int period = 2000;
int pON = 50;
int state = 1;

/*  output to stdout for string with 
    time mark [hour:min:sec]*/
void timeprint(char *s)
{
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    
    printf("[%02d:%02d:%02d] %s", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, s);
}

void* gpioHandler(void*) 
{
    while (state) 
    {
        timeprint("led turned on >>>\n");
        digitalWrite(GPIO_PIN, HIGH);
        delay((int)(period / (100.0 / pON)));
        
        timeprint("led turned off <<<\n");
        digitalWrite(GPIO_PIN, LOW);
        delay(period - (int)(period / (100.0 / pON)));
    }
    return NULL;
}

int main(int argc, char *argv[]) 
{
    int num;
    char input[100];
    
    for (int i = 1; i < argc; i++) {
        num = atoi(argv[i]);
        if (num < 0) 
        {
            printf("ERROR: argv must be greater than or equal to zero");
            return 0;
        }
        switch(i)
        {
        case 1:
            period = num;
            break;
        case 2:
            pON = num;
            break;
        }
    }

    wiringPiSetupGpio();
    pinMode(GPIO_PIN, OUTPUT);

    pthread_t thread;
    if (pthread_create(&thread, NULL, gpioHandler, NULL)) 
    {
        fprintf(stderr, "pthread_create");
        return -1;
    }
    
    printf("use \"start\" or \"stop\" || use Ctrl+C for exit...\n");
    
    while (1) 
    {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "stop") == 0 && state)
        {
            state = 0;
            pthread_join(thread, NULL);
            digitalWrite(GPIO_PIN, LOW);
            printf("led state = %s || input new period, pON:\n", state ? "on" : "off");
            scanf("%d %d", &period, &pON);
        }
        else if (strcmp(input, "start") == 0 && !state)
        {
            state = 1;
            if (pthread_create(&thread, NULL, gpioHandler, NULL)) 
            {
                fprintf(stderr, "pthread_create");
                return -1;
            }
            printf("led state = %s || period = %d || pON = %d%%\n", state ? "on" : "off", period, pON);
        }
    }
    
    pthread_join(thread, NULL);
    return 0;
}

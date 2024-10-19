#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <string.h>
#include <time.h>

#define GPIO_PIN 17

/*  Output to stdout str[] with 
    time mark [hour:min:sec]*/
void timeprint(char *str)
{
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    
    printf("[%02d:%02d:%02d] %s", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, str);
}

int main(int argc, char *argv[]) 
{
    int period = atoi(argv[1]), pON = atoi(argv[2]);

    wiringPiSetupGpio();
    pinMode(GPIO_PIN, OUTPUT);

    while (1) 
    {
        //timeprint("led turned on >>>\n");
        digitalWrite(GPIO_PIN, HIGH);
        delay((int)(period / (100.0 / pON)));
        
        //timeprint("led turned off <<<\n");
        digitalWrite(GPIO_PIN, LOW);
        delay(period - (int)(period / (100.0 / pON)));
    }
    
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

char device[] = "/dev/ttyACM0";

int fd;
unsigned long baud = 9600;
unsigned long time = 0;

int testNum = 0;

int main(void);
void loop(void);
void setup(void);
void interruptFunction(void);

void setup()
{
    printf("%s \n", "Raspberry Setup!");
    fflush(stdout);

    /*
    if((fd = serialOpen(device, baud)) < 0)
    {
        fprintf(stderr, "Unable to open serial device : %s \n", strerror(errno));
        exit(1);
    }
       */

    if(wiringPiSetup() == -1)
    {
        fprintf(stdout, "Unable to start wiringPi : %s\n", strerror(errno));
        exit(1);
    }

    pinMode(4, INPUT);
    if(wiringPiISR(4, INT_EDGE_BOTH, &interruptFunction) < 0)
    {
        printf("Unable interruptFunction\n");
    }
}

void loop()
{
    printf("textNum : %d\n", testNum);

    /*
    if(millis() - time >= 3000)
    {
        serialPuts (fd, "120");
        time=millis();
    }

    
    if(serialDataAvail (fd)) 
    {
        char newChar = serialGetchar(fd);
        printf("%c", newChar);
        fflush(stdout);
    }
    */
}

void interruptFunction()
{
    if(digitalRead(4))
     testNum++;    
}
int main()
{
    setup();
    while(1)
        loop();

    return 0;
}

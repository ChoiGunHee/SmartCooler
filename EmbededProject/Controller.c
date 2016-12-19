#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <signal.h>
#include <errno.h>

#define MSG_SIZE 1024

#define intterptPin 4

#define OUT1 0
#define OUT2 2
#define PWM1 1

#define OUT3 24
#define OUT4 25
#define PWM2 23

#define ECOHPIN 28
#define TRIGPIN 27

#define BUGERPIN 22

char device[] = "/dev/ttyACM0";
unsigned long baud = 9600;

int completFlag = 0;
int msgEnableFlag = 1;

int main(void);
void setup(void);
void completInterrupt(void);
void stop(void);
void go(void);
int ultraResult(void);
void buser(void);

void setup()
{
    printf("%s \n", "Rassberry Setup!");
    fflush(stdout);

    if(wiringPiSetup() == -1)
    {
        fprintf(stdout, "Unable to start wiringPi : %s\n", strerror(errno));
        exit(1);
    }

    pinMode(intterptPin, INPUT);

    pinMode(OUT1, OUTPUT);
    pinMode(OUT2, OUTPUT);
    pinMode(PWM1, OUTPUT);

    pinMode(OUT3, OUTPUT);
    pinMode(OUT4, OUTPUT);
    pinMode(PWM2, OUTPUT);
    
    pinMode(TRIGPIN, OUTPUT);
    pinMode(ECOHPIN, INPUT);
    
    pinMode(BUGERPIN, OUTPUT);

    if(wiringPiISR(intterptPin, INT_EDGE_BOTH, &completInterrupt) < 0)
    {
        printf("Unable completInterrupt\n");
    }
}

void completInterrupt(void)
{
    if(digitalRead(intterptPin))
        completFlag = 1;
    else
        completFlag = 0;    
}

int main(void)
{
    char msg[MSG_SIZE];
    int filedes;
    int nread, cnt;
    int msg_num;

    int serialFD;

    setup();

    unlink("./fifo");
    
    if(mkfifo("./fifo", 0666) == -1 )
    {
        printf("fail to call fifo()\n");
        exit(1);
    }

    if((filedes = open("./fifo", O_RDWR)) < 0)
    {
        printf("fail to call fifo()\n");
        exit(1);
    }

    //intterupt
     
    if((serialFD = serialOpen(device, baud)) < 0)
    {
        fprintf(stderr, "Unable to open serial device : %s\n", strerror(errno));
        exit(1);
    }
       
     while(1)
     {
         if(msgEnableFlag)
         {
            stop();

            if((nread = read(filedes, msg, MSG_SIZE)) < 0)
            {
                printf("fail to call read()\n");
                exit(1);
            }    
            else
            {
           
            }
       
            if('f' == msg[0])
            {
                printf("f call");
            }
            else
            {
                msg_num = atoi(msg);
                printf("num : %d\n", msg_num);
                serialPuts(serialFD, msg);          
            }
            
            msgEnableFlag = 0;

            printf("server send : %s\n", msg);
         }
         else //msgEnableFlag
         {  
            
            if(!completFlag)
            {
                if(ultraResult() == 0)
                {
                    go();   
                    printf("not Complet\n");
                }
                else
                {
                    stop();
                    printf("ultraResult stop\n");
                }
            }
            else
            {
               stop();
               msgEnableFlag = 1;
               serialPuts(serialFD, "-1");
               printf("Complet\n");
               buser(); 
            }
        
         }
     }
    
     unlink("./fifo");

    return 0;
}

void stop(void)
{
    digitalWrite(OUT1, 0);
    digitalWrite(OUT2, 0);
    digitalWrite(PWM1, 0);

    digitalWrite(OUT3, 0);
    digitalWrite(OUT4, 0);
    digitalWrite(PWM2, 0);
}

void go(void)
{
    digitalWrite(OUT1, 1);
    digitalWrite(OUT2, 0);
    digitalWrite(PWM1, 1);

    digitalWrite(OUT3, 1);
    digitalWrite(OUT4, 0);
    digitalWrite(PWM2, 1);
}

void buser()
{
    digitalWrite(BUGERPIN, 1);
    delay(2000);
    digitalWrite(BUGERPIN, 0);
}

int ultraResult()
{
    int startTime;
    int endTime;
    float distance;
    int result;

    digitalWrite(TRIGPIN, 0);
    delay(500);
    digitalWrite(TRIGPIN, 1);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, 0);

    while(digitalRead(ECOHPIN) == 0);
    startTime = micros();
    while(digitalRead(ECOHPIN) == 1);
    endTime = micros();

    distance = (endTime - startTime) / 58;
    printf("distance : %.2f\n", distance);

    if(distance<30) result = 1;
    else result = 0;

    return result;
}

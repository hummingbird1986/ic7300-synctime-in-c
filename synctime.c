//
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "serial_config.h"
#include "hr_min.h"

#define CMD_START '\xFE'
#define CMD_END '\xFD'
#define RIG_ADDR '\x94'
#define CONTROL_ADDR '\xE0'
#define MAIN_CMD '\x1A'
#define SUB_CMD '\x05'
#define TIME_RW1 '\x00'
#define TIME_RW2 '\x95'

int main(void){
printf("It's syncing the time.....please wait util the seconds tick to zero.");
struct tm *ptr;
time_t epochTime;
while((ptr->tm_sec)!=0)
{ 
printf("It's syncing the time.....please wait util the seconds tick to zero.\n");
do{ 
	epochTime=time(NULL);
	ptr=localtime(&epochTime);
	}
hr_min( &(ptr->tm_hour),&(ptr->tm_min));
unsigned char HOUR=ptr->tm_hour;
unsigned char MIN=ptr->tm_min;
unsigned char msg[100]={ CMD_START, CMD_START, RIG_ADDR, CONTROL_ADDR, MAIN_CMD, SUB_CMD, TIME_RW1, TIME_RW2, HOUR, MIN, CMD_END};
int serial_port;
speed_t baud=B9600;	
serial_config(&serial_port, baud);
write(serial_port,  msg, sizeof(msg));
close(serial_port);
} 

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "serial_config.h"
#include "num_hex.h"

#define CMD_START '\xFE'
#define CMD_END '\xFD'
#define RIG_ADDR '\x94'
#define CONTROL_ADDR '\xE0'
#define MAIN_CMD '\x1A'
#define SUB_CMD0 '\x05'
#define SUB_CMD1 '\x00'
#define SUB_CMD2 '\x94'
#define SUB_CMD3 '\x95'
#define YEAR_20XX '\x20'
int main(void){
printf("It's syncing the time.....please wait util the seconds tick to zero.\n");
struct tm *ptr;
time_t epochTime;
while((ptr->tm_sec)!=0){
	epochTime=time(NULL);
	ptr=localtime(&epochTime);
	}
int YEAR=ptr->tm_year%100;
int Month=ptr->tm_mon+1;
NumToHex(&YEAR, &Month, &(ptr->tm_mday), &(ptr->tm_hour),&(ptr->tm_min));
unsigned char MON=(Month);
unsigned char DATE=ptr->tm_mday;
unsigned char HOUR=ptr->tm_hour;
unsigned char MIN=ptr->tm_min;
unsigned char msg0[13]={ CMD_START, CMD_START, RIG_ADDR, CONTROL_ADDR, MAIN_CMD, SUB_CMD0, SUB_CMD1, SUB_CMD2, YEAR_20XX, YEAR, MON, DATE, CMD_END};
unsigned char msg1[12]={ CMD_START, CMD_START, RIG_ADDR, CONTROL_ADDR, MAIN_CMD, SUB_CMD0, SUB_CMD1, SUB_CMD3, HOUR, MIN, CMD_END};
int serial_port;
speed_t baud=B9600;	
serial_config(&serial_port, baud);
write(serial_port, msg0, sizeof(msg0));
write(serial_port, msg1, sizeof(msg1));
close(serial_port);
} 

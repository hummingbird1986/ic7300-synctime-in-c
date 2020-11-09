#include <stdio.h>
#include <time.h>
#include <string.h>
//#include <fcntl.h>
//#include <errno.h>
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
struct tm *ptr;
time_t epochTime;
printf("It's syncing the time.....please wait util the seconds tick to zero.");
do{ 
	epochTime=time(NULL);
	ptr=localtime(&epochTime);
	printf("=");
	}while((ptr->tm_sec)!=0);

hr_min( &(ptr->tm_hour),&(ptr->tm_min));
unsigned char HOUR=ptr->tm_hour;
unsigned char MIN=ptr->tm_min;
unsigned char msg[100]={ CMD_START, CMD_START, RIG_ADDR, CONTROL_ADDR, MAIN_CMD, SUB_CMD, TIME_RW1, TIME_RW2, HOUR, MIN, CMD_END};
int serial_port;
speed_t baud=B9600;	
serial_config(&serial_port, baud);
/*
int serial_port = open("/dev/ttyUSB0", O_RDWR);
struct termios tty;

if(tcgetattr(serial_port, &tty) != 0) {

  printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
  return 1;
}

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1) 
  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
  }*/
/*
struct tm *ptr;
time_t epochTime;
printf("It's syncing the time.....\n");
do
{ 
	epochTime=time(NULL);
	ptr=localtime(&epochTime);
	printf("|");
	}
while((ptr->tm_sec)!=0);
hr_min( &(ptr->tm_hour),&(ptr->tm_min));
unsigned char HOUR=ptr->tm_hour;
unsigned char MIN=ptr->tm_min;
unsigned char msg[100]={ CMD_START, CMD_START, RIG_ADDR, CONTROL_ADDR, MAIN_CMD, SUB_CMD, TIME_RW1, TIME_RW2, HOUR, MIN, CMD_END};
*/
write(serial_port,  msg, sizeof(msg));
close(serial_port);
} 

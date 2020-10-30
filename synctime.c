#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
/*
#define CMD_START FE
#define CMD_END FD
#define RIG_ADDR 94
#define CONTROL_ADDR E0
#define MAIN_CMD 1A
#define SUB_CMD 05
#define TIME_RW1 00
#define TIME_RW2 95
*/

int main(void){


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
  }

char msg[100]={ '\xFE', '\xFE', '\x94', '\xE0', '\x1A', '\x05', '\x00', '\x95', '\x14', '\x14', '\xFD'};
//char msg1[]={'\x14', '\x14', '\xFD'};
//strcat(msg, msg1);
//sprintf (buff,"%02lX",sizeof(msg));
write(serial_port,  msg, sizeof(msg));
//printf("write output %ls", msg);
/*  struct tm *ptr;
  time_t epochTime;
  epochTime=time(NULL);
  ptr=localtime(&epochTime);
  return 0;
  */
close(serial_port);
} 

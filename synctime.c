#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#define CMD_START '\xFE'
#define CMD_END '\xFD'
#define RIG_ADDR '\x94'
#define CONTROL_ADDR '\xE0'
#define MAIN_CMD '\x1A'
#define SUB_CMD '\x05'
#define TIME_RW1 '\x00'
#define TIME_RW2 '\x95'
//#define HOUR '\x14'
//#define MIN '\x14'	

int main(void){

unsigned char HOUR[24]={'\x00', '\x01', '\x02','\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x20', '\x21', '\x22', '\x23'};
unsigned char MIN[60]={'\x00', '\x01', '\x02','\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59' };

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

  struct tm *ptr;
  time_t epochTime;
  epochTime=time(NULL);
  ptr=localtime(&epochTime);
  

unsigned char msg[100]={ CMD_START, CMD_START, RIG_ADDR, CONTROL_ADDR, MAIN_CMD, SUB_CMD, TIME_RW1, TIME_RW2, HOUR[(ptr->tm_hour)], MIN[(ptr->tm_min)] /*MIN*/, CMD_END};

write(serial_port,  msg, sizeof(msg));
close(serial_port);
} 

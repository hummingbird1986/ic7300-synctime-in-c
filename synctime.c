#include <stdio.h>
#include <time.h>
#define CMD_START 0xFE
#define CMD_END 0xFD
#define RIG_ADDR 0x94
#define CONTROL_ADDR 0xE0
#define MAIN_CMD 0x1A
#define SUB_CMD 0x05
#define TIME_RW1 0x00
#define TIME_RW2 0x95

int main(void)
  
 { struct tm *ptr;
  time_t epochTime;
  epochTime=time(NULL);
  ptr=localtime(&epochTime);
  return 0;
 }

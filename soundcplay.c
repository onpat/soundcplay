#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int fd = -1;
static int fh = -1;

void SoundCortexOpen() {
  fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    perror("file open error");
    exit(EXIT_FAILURE);
  }
  if (ioctl(fd, I2C_SLAVE, 0x50)) {
    perror("can not set address");
    exit(EXIT_FAILURE);
  }
}

void SoundCortexSCCOpen() {
   fh = open("/dev/i2c-1", O_RDWR);
  if (fh < 0) {
    perror("file open error");
    exit(EXIT_FAILURE);
  }
  if (ioctl(fh, I2C_SLAVE, 0x51)) {
    perror("can not set address");
    exit(EXIT_FAILURE);
  }
}

void SoundCortexWrite
(unsigned char reg, unsigned char data) {
  if (fd < 0)
    SoundCortexOpen();
  unsigned char cmd[2];
  cmd[0] = reg;
  cmd[1] = data;
  write(fd, cmd, 2);
}

void SoundCortexSCCWrite (unsigned char reg, unsigned char data) {
 if (fh < 0)
    SoundCortexSCCOpen();
  unsigned char cmd[2];
  cmd[0] = reg;
  cmd[1] = data;
  write(fh, cmd, 2);
}

void SoundCortexPSGSCC(unsigned char reg, unsigned char data) { //PSG in SCC Write
unsigned char cmd[1] = {0xff};
if (reg == 0x06) { //noise
 SoundCortexWrite(0x06, data);
 return;
}
if (reg < 0x06) { //freq
 cmd[0] = reg + 0xa0;
} else if (reg < 0x0b && reg > 0x07) { //vol
 cmd[0] = reg + 0xa2;
} else if(reg == 0x07) {
 cmd[0] = 0xaf;
 data = data ^ 0x07;
} else if(reg > 0x0a && reg < 0x0e) {//envelope(don't use)
 return;
}
if (cmd[0] != 0xff) {
 SoundCortexSCCWrite(cmd[0], data);
}
}

void InitSCC() { // SCC+ have 5 unique wavetable (SCC has 4)
 int i;
 int j;
 char wfa[8] = {128, 0, 128, 255, 128, 0, 128, 255}; //ch1 waveform, write first 8 of 32
 char wfb[8] = {127, 127, 127, 127, 0, 0, 0, 0};
 char wfc[32] = {128, 255, 128, 128, 16, 16, 16, 64, 128, 16, 16, 255, 240, 240, 192, 64, 16, 64, 64, 128, 192, 208, 224, 255, 255, 0, 128, 128, 64, 128, 192, 255};
 for (i = 0; i < 8; i++) { //waveform transfer
   SoundCortexSCCWrite(i, wfa[i]);
   SoundCortexSCCWrite(i+32, wfb[i]);
   SoundCortexSCCWrite(i+64, wfc[i]);
 }
 //SoundCortexSCCWrite(0xa0, 0xfd);// freq 1 a0-a8
 //SoundCortexSCCWrite(0xa1, 0x01);//freq 2 a1-a9
 //SoundCortexSCCWrite(0xaa, 15);// vol aa-ae
 SoundCortexSCCWrite(0xaf, 0b00000111); //xxxedcba, 1 is on
}

void PlaySNG(char *filename, int mode) { //mode1=PSGSCC
FILE *fp;
char cr[65535]; //register
char ch[65535]; //value
int i = 0; //song size
int j = 0; //current position
fp = fopen(filename, "rb");
if (fp == NULL) {
 printf("file load failed\n");
 return;
}
printf("playing file %s\n", filename);
fseek(fp, 5, SEEK_SET);
cr[0] = fgetc(fp);
while((ch[i] = fgetc(fp)) != EOF) { //load file to array
 cr[i+1] = fgetc(fp);
 if (cr[i+1] == 0xff) {
  break;
 }
 i++;
}
printf("size: %d\n", i);
while(j < i) {
 if (cr[j] < 16) {
  if (mode == 0) {
   if (cr[j] < 0x0b) {
    SoundCortexWrite(cr[j], ch[j]);
   }
  } else {
   SoundCortexPSGSCC(cr[j], ch[j]);
  }
 //} else {
 // usleep(1000 * 20);
 //}
 } else if (cr[j] == 16) {
  usleep(1000 * 20);
 }
 j++;
}
}

void main(int argc, char *argv[]) {
 SoundCortexOpen();
SoundCortexSCCOpen();
InitSCC();
 
  //SoundCortexWrite(0x00, 0xfd);
  //SoundCortexWrite(0x01, 0x01);
  //SoundCortexWrite(0x07, 0xfe);
  //SoundCortexWrite(0x08, 0x0f);
  //SoundCortexPSGSCC(0x00, 0xfd);
  //SoundCortexPSGSCC(0x01, 0x01);
  //SoundCortexPSGSCC(0x07, 0xfe);
  //SoundCortexPSGSCC(0x08, 0x0f);
  
  if (argc == 3) {
  PlaySNG(argv[1], strtol(argv[2], NULL, 0));
  } else {
  printf("No file specified - init olny \r scplay filename mode(0=normal, 1=PSGSCC)\n");
  } 
}

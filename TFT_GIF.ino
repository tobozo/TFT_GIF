#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

struct frameInfo {
  String name;
  int frame;
  int imgwidth;
  int imgheight;
  int offsetleft;
  int offsettop;
  bool istransparent;
  unsigned short transparentcolor;
  const unsigned short* bytes;
};

struct animInfo {
  //int pagewidth;
  //int pageheight;
  int frames;
  unsigned short transparentcolor;
  //int delay;
};


/* warning memory full if too menay enabled */
#include "kuypqcp8.h";
#include "th_dickinson.h"
#include "th_godsquad.h"

/* enabling those requires some coding */
// #include "th_cowstairs.h"
// #include "th_horrorlama.h"


long count = 0; // Loop count
int iconpointer = 0;
int totalframes;
int animnum = 0;
int totalanim = 3;
long duration = 10000;
long last = 0;
unsigned short imgcache[20480];
// To speed up rendering we use a 64 pixel buffer
int BUFF_SIZE = 128;
int BUFF_LINES = 160;
// 64 * 320 = 20480 = 160 * 128

animInfo getAnimInfo() {
  switch(animnum) {
    case 0: return getAnimInfoth_dickinson(); break;
    case 1: return getAnimInfokuypqcp8(); break;
    case 2: return getAnimInfoth_godsquad(); break;
  }
}
frameInfo frame(int id) {
  switch(animnum) {
    case 0: return frameth_dickinson(id); break;
    case 1: return framekuypqcp8(id); break;
    case 2: return frameth_godsquad(id); break;
  }  
}
/*
void drawImage(int id) {
  frameInfo info = frame(id);
  const unsigned short* icon = info.bytes;
  uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)
  // full screen drawing
  tft.setAddrWindow(0, 0, tft.width()-1, tft.height()-1);
  // Work out the number whole buffers to send
  uint16_t nb = BUFF_LINES;//((uint16_t)height * (uint16_t)width) / BUFF_SIZE;
  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < BUFF_SIZE; j++) {
      uint16_t pix_word = pgm_read_word(&icon[i * BUFF_SIZE + j]);
      if(pix_word != 0) {
        pix_buffer[j] = pix_word;
      }
    }
    tft.pushColors(pix_buffer, BUFF_SIZE);
  }
}*/



void drawFrame(int id) {
  frameInfo info = frame(id);
  const unsigned short* icon = info.bytes;
  uint16_t pix_word;
  uint16_t pix_buffer[info.imgwidth]; // Pixel buffer (16 bits per pixel)
  uint16_t x, y, addr;
  uint16_t offset;

  tft.setAddrWindow(info.offsetleft, info.offsettop, info.offsetleft+info.imgwidth-1, info.offsettop+info.imgheight-1 );
  
  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < info.imgheight; i++) {
    for (int j = 0; j < info.imgwidth; j++) {
      offset = i * info.imgwidth + j;
      pix_word = pgm_read_word(&icon[offset]);

      x = info.offsetleft + (offset) % info.imgwidth ;
      y = info.offsettop + floor( (offset) / info.imgwidth );
      addr = ( y * tft.width() ) + x;
      
      if(!info.istransparent || (info.istransparent && pix_word != info.transparentcolor) || id==0) {
        pix_buffer[j] = pix_word;
        imgcache[addr] = pix_word;
      } else {
        pix_buffer[j] = imgcache[addr];
      }
    }
    tft.pushColors(pix_buffer, info.imgwidth);
  }
}



void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(2);  // 0/2 = portrait, 1/3 = landscape
  tft.fillScreen(TFT_BLACK);
  memset(imgcache,0,sizeof(imgcache));
  animInfo anim = getAnimInfo();
  totalframes = anim.frames;

}


void loop() {

  drawFrame(iconpointer);
  delay(10);
  iconpointer++;
  if(iconpointer>totalframes-1) iconpointer = 0;
  
  long now = millis();
  if(duration + last < now) {
    last = now;
    animnum++;
    memset(imgcache,0,sizeof(imgcache));
    if(animnum>=totalanim) animnum = 0;
    animInfo anim = getAnimInfo();
    totalframes = anim.frames;
  }
  
}


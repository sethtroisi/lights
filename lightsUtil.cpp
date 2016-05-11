#include <cassert>
#include <iostream>
#include <ctime>

#include <wiringPi.h>

#include "lightsUtil.h"


// TODO delete
#include <chrono>

/*
//TODO testing
#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000)
 
 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
 
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
 
int  mem_fd;
void *gpio_map;
 
// I/O access
volatile unsigned *gpio;
 
 
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock
 
void setup_io();
 
 
//
// Set up a memory regions to access GPIO
//
void setup_io()
{
   // open /dev/mem
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }
 
   // mmap GPIO
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
 
   close(mem_fd); //No need to keep mem_fd open after mmap
 
   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }
 
   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
 
 
} // setup_io
// */

using namespace std;


void delayNano(int ns) {
  if (ns > 0) {
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = ns;
    nanosleep(&tim, NULL);
  }
}

void writeAndWait(int port, int bit, int ns) {
//    auto T0 = chrono::high_resolution_clock::now()
//    auto begin = chrono::high_resolution_clock::now();

//    if (bit) {
//      GPIO_SET = bit * (1 << DATA_PORT);
//    } else {
//      GPIO_CLR = bit * (1 << DATA_PORT);
//    }

    digitalWrite(CLOCK_PORT, bit);

//    auto end = chrono::high_resolution_clock::now();
//    int durationNS = chrono::duration_cast<chrono::nanoseconds>(end-begin).count();
    int durationNS = 300;

//    auto T1 = chrono::high_resolution_clock::now();
//    int outer = chrono::duration_cast<chrono::nanoseconds>(T1 - T0).count();
//    cout << outer << " - " << durationNS << " = " << outer - durationNS << endl;


    delayNano(ns - durationNS);
//    cout << "bit " << bit << " " << durationNS << " adding " << ns - durationNS << endl;
}


void writeBit(bool bit) {
    // TODO pass as param or something.
    bool ws2818 = false;
    if (ws2818) {
      // One pin writing with timing based data
      writeAndWait(DATA_PORT, 1, bit ? WS2818_T1H_NS : WS2818_T0H_NS);
      writeAndWait(DATA_PORT, 0, bit ? WS2818_T1L_NS : WS2818_T0L_NS);
    } else {
      digitalWrite(DATA_PORT, bit);     // data
      delayMicroseconds(WRITE_DELAY_US);

      digitalWrite(CLOCK_PORT, 1);       // CLK up
      delayMicroseconds(WRITE_DELAY_US);

      digitalWrite(CLOCK_PORT, 0);       // CLK down
    }
}

void writeByte(int num) {
    assert (num >= 0);
    assert (num <= 255);

    // TODO replace this with WiringShift.h when it supports speed.

    for (int bit = 128; bit > 0; bit >>= 1) {
        writeBit((num & bit) > 0);
    }
}

void writeColor(int color[]) {
    writeByte(color[0]);
    writeByte(color[1]);
    writeByte(color[2]);
}

void setupLights(void) {
// /*
  if (wiringPiSetupGpio() == -1) {
    cout << "ERROR: Setup failed" << endl;
    exit;
  }

  pinMode (CLOCK_PORT, OUTPUT);
  pinMode (DATA_PORT, OUTPUT);

// */
/*
  // Set up gpi pointer for direct register access
  setup_io();

  INP_GPIO(CLOCK_PORT); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(CLOCK_PORT);
 
  INP_GPIO(DATA_PORT); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(DATA_PORT);
// */
}

// DELAY LATCH ~280us = .28ms

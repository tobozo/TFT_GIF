
#include <pgmspace.h>
#include "th_dickinson00.c"
#include "th_dickinson01.c"
#include "th_dickinson02.c"
#include "th_dickinson03.c"
#include "th_dickinson04.c"
#include "th_dickinson05.c"


animInfo getAnimInfoth_dickinson() {
  return animInfo{6, 0x0000};
}

frameInfo frameth_dickinson(int id) {
   switch(id) {
    case 0: return frameInfo{"th_dickinson.gif", 0, 128, 160, 0, 0, false, 0x0000, th_dickinson00}; break;
    case 1: return frameInfo{"th_dickinson.gif", 1, 118, 160, 10, 0, true, 0x0000, th_dickinson01}; break;
    case 2: return frameInfo{"th_dickinson.gif", 2, 116, 160, 12, 0, true, 0x0000, th_dickinson02}; break;
    case 3: return frameInfo{"th_dickinson.gif", 3, 115, 160, 13, 0, true, 0x0000, th_dickinson03}; break;
    case 4: return frameInfo{"th_dickinson.gif", 4, 119, 160, 9, 0, true, 0x0000, th_dickinson04}; break;
    case 5: return frameInfo{"th_dickinson.gif", 5, 121, 160, 7, 0, true, 0x0000, th_dickinson05}; break;

   }
};
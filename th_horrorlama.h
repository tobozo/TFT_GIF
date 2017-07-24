
#include <pgmspace.h>
#include "th_horrorlama00.c"
#include "th_horrorlama01.c"
#include "th_horrorlama02.c"
#include "th_horrorlama03.c"
#include "th_horrorlama04.c"
#include "th_horrorlama05.c"
#include "th_horrorlama06.c"
#include "th_horrorlama07.c"
#include "th_horrorlama08.c"
#include "th_horrorlama09.c"
#include "th_horrorlama10.c"
#include "th_horrorlama11.c"


animInfo getAnimInfoth_horrorlama() {
  return animInfo{12, 0x0000};
}

frameInfo frameth_horrorlama(int id) {
   switch(id) {
    case 0: return frameInfo{"th_horrorlama.gif", 0, 128, 160, 0, 0, false, 0x0000, th_horrorlama00}; break;
    case 1: return frameInfo{"th_horrorlama.gif", 1, 128, 160, 0, 0, false, 0x0000, th_horrorlama01}; break;
    case 2: return frameInfo{"th_horrorlama.gif", 2, 128, 160, 0, 0, false, 0x0000, th_horrorlama02}; break;
    case 3: return frameInfo{"th_horrorlama.gif", 3, 128, 154, 0, 6, false, 0x0000, th_horrorlama03}; break;
    case 4: return frameInfo{"th_horrorlama.gif", 4, 128, 157, 0, 3, false, 0x0000, th_horrorlama04}; break;
    case 5: return frameInfo{"th_horrorlama.gif", 5, 128, 160, 0, 0, false, 0x0000, th_horrorlama05}; break;
    case 6: return frameInfo{"th_horrorlama.gif", 6, 128, 160, 0, 0, false, 0x0000, th_horrorlama06}; break;
    case 7: return frameInfo{"th_horrorlama.gif", 7, 128, 160, 0, 0, false, 0x0000, th_horrorlama07}; break;
    case 8: return frameInfo{"th_horrorlama.gif", 8, 128, 160, 0, 0, false, 0x0000, th_horrorlama08}; break;
    case 9: return frameInfo{"th_horrorlama.gif", 9, 128, 160, 0, 0, false, 0x0000, th_horrorlama09}; break;
    case 10: return frameInfo{"th_horrorlama.gif", 10, 128, 160, 0, 0, false, 0x0000, th_horrorlama10}; break;
    case 11: return frameInfo{"th_horrorlama.gif", 11, 128, 160, 0, 0, false, 0x0000, th_horrorlama11}; break;

   }
};
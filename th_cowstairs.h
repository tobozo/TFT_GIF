
#include <pgmspace.h>
#include "th_cowstairs00.c"
#include "th_cowstairs01.c"
#include "th_cowstairs02.c"
#include "th_cowstairs03.c"
#include "th_cowstairs04.c"
#include "th_cowstairs05.c"
#include "th_cowstairs06.c"
#include "th_cowstairs07.c"
#include "th_cowstairs08.c"
#include "th_cowstairs09.c"
#include "th_cowstairs10.c"
#include "th_cowstairs11.c"
#include "th_cowstairs12.c"
#include "th_cowstairs13.c"
#include "th_cowstairs14.c"
#include "th_cowstairs15.c"


animInfo getAnimInfoth_cowstairs() {
  return animInfo{16, 0x0000};
}

frameInfo frameth_cowstairs(int id) {
   switch(id) {
    case 0: return frameInfo{"th_cowstairs.gif", 0, 128, 160, 0, 0, false, 0x0000, th_cowstairs00}; break;
    case 1: return frameInfo{"th_cowstairs.gif", 1, 128, 137, 0, 0, false, 0x0000, th_cowstairs01}; break;
    case 2: return frameInfo{"th_cowstairs.gif", 2, 128, 145, 0, 0, false, 0x0000, th_cowstairs02}; break;
    case 3: return frameInfo{"th_cowstairs.gif", 3, 128, 145, 0, 0, false, 0x0000, th_cowstairs03}; break;
    case 4: return frameInfo{"th_cowstairs.gif", 4, 128, 143, 0, 0, false, 0x0000, th_cowstairs04}; break;
    case 5: return frameInfo{"th_cowstairs.gif", 5, 128, 139, 0, 0, false, 0x0000, th_cowstairs05}; break;
    case 6: return frameInfo{"th_cowstairs.gif", 6, 128, 136, 0, 0, false, 0x0000, th_cowstairs06}; break;
    case 7: return frameInfo{"th_cowstairs.gif", 7, 128, 132, 0, 0, false, 0x0000, th_cowstairs07}; break;
    case 8: return frameInfo{"th_cowstairs.gif", 8, 128, 130, 0, 0, false, 0x0000, th_cowstairs08}; break;
    case 9: return frameInfo{"th_cowstairs.gif", 9, 128, 130, 0, 0, false, 0x0000, th_cowstairs09}; break;
    case 10: return frameInfo{"th_cowstairs.gif", 10, 128, 137, 0, 0, false, 0x0000, th_cowstairs10}; break;
    case 11: return frameInfo{"th_cowstairs.gif", 11, 128, 144, 0, 0, false, 0x0000, th_cowstairs11}; break;
    case 12: return frameInfo{"th_cowstairs.gif", 12, 128, 144, 0, 0, false, 0x0000, th_cowstairs12}; break;
    case 13: return frameInfo{"th_cowstairs.gif", 13, 128, 141, 0, 0, false, 0x0000, th_cowstairs13}; break;
    case 14: return frameInfo{"th_cowstairs.gif", 14, 128, 137, 0, 0, false, 0x0000, th_cowstairs14}; break;
    case 15: return frameInfo{"th_cowstairs.gif", 15, 128, 133, 0, 0, false, 0x0000, th_cowstairs15}; break;

   }
};
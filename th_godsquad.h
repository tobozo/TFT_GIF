
#include <pgmspace.h>
#include "th_godsquad00.c"
#include "th_godsquad01.c"
#include "th_godsquad02.c"
#include "th_godsquad03.c"
#include "th_godsquad04.c"
#include "th_godsquad05.c"


animInfo getAnimInfoth_godsquad() {
  return animInfo{6, 0x0000};
}

frameInfo frameth_godsquad(int id) {
   switch(id) {
    case 0: return frameInfo{"th_godsquad.gif", 0, 128, 160, 0, 0, false, 0x0000, th_godsquad00}; break;
    case 1: return frameInfo{"th_godsquad.gif", 1, 128, 160, 0, 0, true, 0x0000, th_godsquad01}; break;
    case 2: return frameInfo{"th_godsquad.gif", 2, 128, 160, 0, 0, true, 0x0000, th_godsquad02}; break;
    case 3: return frameInfo{"th_godsquad.gif", 3, 128, 160, 0, 0, true, 0x0000, th_godsquad03}; break;
    case 4: return frameInfo{"th_godsquad.gif", 4, 128, 160, 0, 0, true, 0x0000, th_godsquad04}; break;
    case 5: return frameInfo{"th_godsquad.gif", 5, 128, 160, 0, 0, true, 0x0000, th_godsquad05}; break;

   }
};
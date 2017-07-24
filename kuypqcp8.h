
#include <pgmspace.h>
#include "kuypqcp800.c"
#include "kuypqcp801.c"
#include "kuypqcp802.c"
#include "kuypqcp803.c"
#include "kuypqcp804.c"
#include "kuypqcp805.c"




animInfo getAnimInfokuypqcp8() {
  return animInfo{6, 0x0000};
}

frameInfo framekuypqcp8(int id) {
   switch(id) {
    case 0: return frameInfo{"kuypqcp8.gif", 0, 128, 160, 0, 0, false, 0x0000, kuypqcp800}; break;
    case 1: return frameInfo{"kuypqcp8.gif", 1, 128, 160, 0, 0, true, 0x0000, kuypqcp801}; break;
    case 2: return frameInfo{"kuypqcp8.gif", 2, 128, 160, 0, 0, true, 0x0000, kuypqcp802}; break;
    case 3: return frameInfo{"kuypqcp8.gif", 3, 128, 160, 0, 0, true, 0x0000, kuypqcp803}; break;
    case 4: return frameInfo{"kuypqcp8.gif", 4, 128, 160, 0, 0, true, 0x0000, kuypqcp804}; break;
    case 5: return frameInfo{"kuypqcp8.gif", 5, 128, 160, 0, 0, true, 0x0000, kuypqcp805}; break;

   }
};
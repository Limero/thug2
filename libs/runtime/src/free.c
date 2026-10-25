// free — SN ProDG newlib stub (byte-exact, ngccc -O2 -G0).
//
// The game has no heap: any call panics via OSPanic with the
// "*** Library error *** / An external call has been made to 'free'"
// message (lbl_802B1EB4) and the caller's address (ra - 4).
// range 0x8026AA2C-0x8026AA68 (60B). Byte-identical.
#include "types.h"

extern char lbl_802B1EB4[];

void free(void *ptr) {
    void *ra;
    (void)ptr;
    __asm__ volatile("mflr %0" : "=r"(ra));
    OSPanic(0, 0, (const char *)lbl_802B1EB4, (char *)ra - 4);
}

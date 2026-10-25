// range 0x8007C2D4-0x8007C2E8 (0x14 = 20B). Byte-identical.
// Identification: copies the bss global lbl_80364C38 into self->0, returns
// self (a snapshot/getter of a global word). Recipe 249 return-arg form.
// Suggested rename: Fn_8007C2D4_CopyGlobalWord.
#include "types.h"
extern s32 lbl_80364C38;
void *fn_8007C2D4(void *arg0) {
    *(s32 *)arg0 = lbl_80364C38;
    return arg0;
}

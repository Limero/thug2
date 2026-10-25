// range 0x8007C510-0x8007C52C (0x1C = 28B). Byte-identical.
// Identification: copies an indexed element of a global pointer array into
// self->0: `arr = *(s32**)lbl_80364C40; self->0 = arr[idx];` returns self
// (recipe 249). Suggested rename: Fn_8007C510_GetGlobalArrayElement.
#include "types.h"
extern char lbl_80364C40[];
void *fn_8007C510(void *arg0, s32 idx) {
    s32 *arr = *(s32 **)lbl_80364C40;
    *(s32 *)arg0 = arr[idx];
    return arg0;
}

// range 0x800A3D68-0x800A3D8C (0x24). Byte-identical.
// Identification: field initializer — sets +0x8 to the sentinel 1 and
// zeroes +0xc/+0x4/+0x0/+0x10, returning the object. Likely an "in-use"
// marker + clear.
//
// Matching key (recipe 253): want's order [0xc,8,4,0,0x10] is produced by
// source [8,4,0,0x10,0xc] + return arg0 (brute-forced permutation).
#include "types.h"
#include "structs.h"
void *fn_800A3D68(CStruct *r) {
    r->unk0x8 = 1;
    r->unk0x4 = 0;
    r->unk0x0 = 0;
    r->unk0x10 = 0;
    r->unk0xC = 0;
    return r;
}
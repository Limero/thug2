// range 0x80137C3C-0x80137C5C (0x20). Byte-identical.
// Identification: scattered zero-init of a subset of object fields
// (+0x40/+0x0/+0x2c/+0x30 words and the +0x34 byte), returning the
// object. Mixed byte/word zero stores.
//
// Matching key (recipe 253): mixed-width zero stores need brute-force
// permutation — want's order [0x40,0,0x2c,0x30,0x34] is produced by
// source [0,0x2c,0x30,0x34,0x40] + return arg0.
#include "types.h"
#include "structs.h"
void *fn_80137C3C(Unk_8B4EE1D5 *r) {
    r->unk0x0 = 0;
    r->unk0x2C = 0;
    r->unk0x30 = 0;
    r->unk0x34 = 0;
    r->unk0x40 = 0;
    return r;
}
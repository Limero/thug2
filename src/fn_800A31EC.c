// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A31EC-0x800A3270 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* 0xC-byte self-linked list node: word 0 unused, +4/+8 point at itself.
   Typed locally (M6.89d) because the shared CStruct class types unk0x4/unk0x8
   as s32; both self-link stores are single stw either way. */
typedef struct {
    s32 unk0x0;
    CStruct *unk0x4;
    CStruct *unk0x8;
} T31EC;

extern char lbl_8037BB58[];
extern char lbl_8037BB60[];
CStruct *Mem_Alloc2(s32 arg0);
void fn_800A31EC(s32 arg0, s32 arg1) {
    T31EC *t1;
    T31EC *t2;
    s32 *p;
    s32 *q;
    register s32 n2 __asm__("r3");
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        p = (s32 *) lbl_8037BB58;
        p[1] = 0;
        t1 = (T31EC *) Mem_Alloc2(0xC);
        *(s32 *) lbl_8037BB58 = (s32) t1;
        n2 = 0xC;
        q = (s32 *) lbl_8037BB60;
        __asm__ volatile("" ::: "memory");
        q[1] = 0;
        t1->unk0x8 = t1;
        t1->unk0x4 = t1;
        t2 = (T31EC *) Mem_Alloc2(n2);
        *(s32 *) lbl_8037BB60 = (s32) t2;
        t2->unk0x8 = t2;
        t2->unk0x4 = t2;
    }
}

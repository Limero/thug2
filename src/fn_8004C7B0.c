// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004C7B0-0x8004C840 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
void GetElement_2(void *, s32, s32, s32);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8004C7B0(Unk_C7387A53 *arg0, s32 arg1) {
    struct { void *f0; s32 f4; s32 f8; } sp8;
    s32 *temp_r30;

    temp_r30 = (char *)arg0 + 0x4C;
    GetElement_2(&sp8, arg0, arg1, 1);
    if ((s32) arg0->unk0x4C != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)temp_r30), temp_r30);
        arg0->unk0x4C = 0;
    }
    arg0->unk0x4C = (s32)sp8.f0;
    if (sp8.f0 != 0) {
        CObject_AddRefLink((CStruct *)sp8.f0, (Unk_9994C3F5 *)temp_r30);
    }
    __asm__("" ::: "memory");
    if (sp8.f0 != 0) {
        CObject_RemoveRefLink((CStruct *)sp8.f0, (CStruct *)&sp8);
        sp8.f0 = 0;
    }
}

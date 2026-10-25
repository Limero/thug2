// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184934-0x80184A2C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8018B568(void *, void *);
void fn_80184A2C(void *);
void *fn_8018B4C0(void *, s32 *, s32 *);
s32 fn_80184168(s32);
s32 fn_8018E514(void *);
s32 fn_8018E24C(void *);
void fn_80184934(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    void *res;
    void *vt;
    register s32 a0 __asm__("r29");

    a0 = arg0;
    sp8 = 0;
    goto test;
loop:
    res = fn_8018B4C0((void *)(a0 + 4), &sp8, &spC);
    vt = (void *)((Unk_C8FEE62D *)res)->unk0x14;
    if (((s32 (*)(void *))*(void **)((char *)vt + 0x24))((char *)res + *(s16 *)((char *)vt + 0x20)) != 0) {
        vt = (void *)((Unk_C8FEE62D *)res)->unk0x14;
        ((void (*)(void *))*(void **)((char *)vt + 0x94))((char *)res + *(s16 *)((char *)vt + 0x90));
    }
    if (fn_8018E514(res) != 0) {
        sp10 = fn_8018E24C(res);
        fn_8018B568((void *)(a0 + 4), &sp10);
        if (res != NULL) {
            vt = (void *)((Unk_C8FEE62D *)res)->unk0x14;
            ((void (*)(void *, s32))*(void **)((char *)vt + 0xC))((char *)res + *(s16 *)((char *)vt + 8), 3);
        }
    }
    sp8 += 1;
test:
    if (sp8 < fn_80184168(a0)) {
        goto loop;
    }
    fn_80184A2C((void *)a0);
}

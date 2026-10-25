// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8848-0x801A893C (244B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 fn_801A8204(CScript *, s32);
s32 fn_801FC0E0(void);
void fn_801FBF18(s32, s32);

bool fn_801A8848(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 v;
    CStruct *p;
    char *base;
    u32 count;
    s32 i;
    u32 j;

    p = *((void * *)&arg0->unk0x54);
    count = 0U;
    while (v = p->unk0x4, v == -1 && (p = NULL), p != NULL) {
        p = *((void * *)&p->unk0xC);
        count++;
    }
    for (i = 0; i < count; i++) {
        char *base = (char *)arg0 + 0x48;
        p = ((Unk_E266FB50_2 *)base)->unk0xC;
        j = (u32)i;
        goto lb8;
la8:
        if (j-- == 0U) {
            goto ld4;
        }
        p = *((void * *)&p->unk0xC);
lb8:
        v = p->unk0x4;
        if (v == -1) {
            p = NULL;
        }
        if (p != NULL) {
            goto la8;
        }
        __asm__("li %0,0" : "=r"(p));
ld4:
        if (fn_801A8204(p->unk0x4, arg1) == 0) {
            return false;
        }
    }
    if (*(s32 *)((char *)*(s32 *)&lbl_80305EAC + 0x388) == (s32)QB_LOAD_SK5ED_GAMEPLAY) {
        fn_801FBF18(fn_801FC0E0(), arg0->unk0x18);
    }
    return true;
}

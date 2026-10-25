// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127C14-0x80127C90 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80126F40(s32, s32);
void fn_80127438(void *, void *);
void CStruct_new(s32 arg0);
s32 fn_8009F4C4(s32);
void *fn_801252BC(void);
s32 CStruct_ctor(void);
#include "structs.h"

typedef union {
    u32 w;
    struct {
        u32 hi:9;
        u32 typ:7;
        u32 lo:16;
    } f;
} MaskU;

void fn_80127C14(CStruct *arg0, s32 arg1, CStruct *arg2) {
    CStruct *temp_r3;
    MaskU u;
    s32 v;

    fn_8009F4C4(0x10);
    temp_r3 = fn_801252BC();
    temp_r3->unk0x4 = arg1;
    u.w = temp_r3->unk0x0;
    u.f.typ = 0xa;
    temp_r3->unk0x0 = u.w;
    CStruct_new(8);
    v = CStruct_ctor();
    temp_r3->unk0x8 = v;
    fn_80126F40(v, arg2);
    fn_80127438(arg0, temp_r3);
}

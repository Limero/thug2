// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D1C4-0x8002D244 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_803003AC[];
extern char lbl_80291870[];
void *Mem_NewZero(s32);
s32 fn_80010434(Unk_9D99273B *, s32, s32, void *, s32);
void *fn_8002D108(Unk_FFAD6788 *);
void fn_8002D9B0(Unk_FFAD6788 *, s32, s32);
void fn_8002D1C4(s32 arg0, s32 arg1, s32 arg2) {
    void *obj;
    if (*(s32 *)&lbl_803003AC == 0) {
        fn_80010434(*(s32 *)&lbl_802FFE98, QB_ANIMHEAP, arg0, (s32)lbl_80291870, 0);
        obj = fn_8002D108(Mem_NewZero(0xE4));
        *(void **)&lbl_803003AC = obj;
        fn_8002D9B0(obj, arg1, arg2);
    }
}
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CCB94-0x800CCC98 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80302C34;
void fn_800CD39C(s32, s32, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8011A014(void *, s32, s32);
void fn_800CCC9C(s32, CStruct *);
s32 fn_800CCB94(s32 arg0, u32 arg1, CStruct *arg2, s32 arg3) {
    s32 sp8;
    s32 *base;
    s32 *rd;
    s32 cnt;
    s32 off;

    switch (arg1) {
    case QB_OBJ_ADJUSTSOUND:
        fn_800CD39C(arg0, arg2, arg3);
        return 1;
    case QB_OBJ_STOPSOUND:
        sp8 = 0;
        GetChecksum_2(arg2, 0, &sp8, 0);
        fn_8011A014(lbl_80302C34, arg0, sp8);
        base = (s32 *)((char *)arg0 + 0x3C);
        __asm__("mr %0,%1" : "=r"(rd) : "r"(base));
        cnt = 2;
        off = 0;
        do {
            if (*(s32 *)((char *)(off + (s32)rd)) == sp8) {
                *(s32 *)((char *)(off + (s32)base)) = 0;
            }
            off += 0x30;
            cnt -= 1;
        } while (cnt != 0);
        return 1;
    case QB_OBJ_SETSOUND:
        fn_800CCC9C(arg0, arg2);
        return 1;
    default:
        return 2;
    }
}

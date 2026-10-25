// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C5F0-0x8015C6A8 (184B). Byte-identical.
// extra_cflags: -fno-schedule-insns2 -fno-schedule-insns -fno-sched-spec
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_802FFE98[];
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80141FA4(Unk_5FCDF30E * arg0);
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_801450B8(Unk_C7387A53 * arg0);
extern void fn_8000F320(Unk_F12C5E01 * arg0);

bool ScriptReinsertSkaters(CStruct *pParams, CScript *pScript) {
    register s32 p __asm__("r9");
    register u32 cnt __asm__("r10");
    register s32 head __asm__("r11");
    register s32 ret __asm__("r3");
    s32 v;
    s32 eac3;
    u32 i;
    u32 idx;
    s32 skater;
    s32 ffeval;

    i = 0U;
    for (;;) {
        p = *(s32 *)&lbl_80305EAC;
        cnt = 0U;
        head = ((CStruct *)p)->unk0x38;
        v = ((CStruct *)head)->unk0x4;
        p = head;
        goto test;
        do {
            p = ((CStruct *)p)->unk0xC;
            cnt += 1U;
            v = ((CStruct *)p)->unk0x4;
        test:;
            if (v == -1) {
                p = NULL;
            }
        } while (p != NULL);
        if (i >= cnt) {
            return true;
        }
        eac3 = *(s32 *)&lbl_80305EAC;
        __asm__ volatile("" : "+r"(eac3));
        ret = fn_80141FA4((skater = fn_801746A4(eac3,
                                                (idx = i, i = i + 1U, idx)),
                           ffeval = *(volatile s32 *)&lbl_802FFE98,
                           skater));
        {
            register char *arrbase __asm__("r9");
            arrbase = (char *)ffeval + 0x1A4;
            ret <<= 2;
            fn_8000F2F8(ffeval, *(s32 *)((char *)((s32)arrbase + ret)));
        }
        fn_801450B8(skater);
        fn_8000F320(*(volatile s32 *)&lbl_802FFE98);
    }
}

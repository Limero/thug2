// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80194764-0x80194988 (548B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: slot-table cleanup/scan helper called from fn_8019457C
// (skater trick-slot management). Iterates 30 slots at arg0+0x4B4; for each
// populated slot it counts matching trick entries across the +0x74/+0x7C
// tables, and when count >= threshold finds a free slot in the +0x84 table
// (script event Script_RunScript on first find), clears the source slot, then
// re-flushes via fn_8019519C. Promoted via temp-pointer materialization
// (`s32 *tp = arr + i; *tp = 0;`) which flips stwx operand order to want's
// base-in-rA form.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_8019519C(Unk_C7387A53 *);
extern s32 fn_801745B4(s32);
extern s32 fn_801403CC(void *);
extern s32 fn_80182150(Unk_FFAD6788 *, s32, s32, s32, s32);
extern s32 fn_8018223C(Unk_FFAD6788 *, s32, s32, s32, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void fn_80194988(Unk_72E9CBBF *, s32);
extern s32 Game_GetGoalManager(void);
extern s32 fn_8018E24C(Unk_C7387A53 *);
extern s32 fn_80183D68(Unk_C7387A53 *, s32);

void fn_80194764(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 *arr;
    register s32 temp_r24 __asm__("r24");
    s32 i;
    s32 found;
    s32 ip1;
    s32 temp_r0;
    register s32 count __asm__("r29");
    s32 j;
    s32 v7C;
    s32 v74;
    s32 v78;
    register char *p74 __asm__("r9");
    register char *p78 __asm__("r9");
    s32 res;
    s32 temp;
    char *w23;
    s32 *w30;
    s32 off;
    register s32 cnt __asm__("r25");
    register char *b84 __asm__("r28");
    s32 *w8C;

    temp_r24 = fn_801403CC(fn_801745B4(*(s32 *)&lbl_80305EAC));
    arr = (s32 *)((char *)arg0 + 0x4B4);
    i = 0;
    GetInteger(arg0->unk0x20, QB_COMBO_SIZE, &sp8, 1);
    do {
        found = 0;
        ip1 = i + 1;
        if (arr[i] != 0) {
            count = 0;
            w23 = (char *)arg0 + 0x7C;
            w30 = (s32 *)((char *)arg0 + 0x94);
            off = 0;
            cnt = 0x1E;
            do {
                v7C = *(s32 *)((char *)(off + (s32)w23));
                if (v7C != 0) {
                    if (w30[-4] == 0) {
                        if (w30[-2] == i) {
                            res = fn_8018223C(temp_r24, v7C, w30[-1], w30[-3], w30[0]);
                            goto chk;
                        }
                    }
                } else {
                    p74 = (char *)arg0 + 0x74;
                    __asm__ volatile("" : "+r"(p74));
                    v74 = *(s32 *)(p74 + off);
                    if (v74 != 0) {
                        b84 = (char *)arg0 + 0x84;
                        if (w30[-4] == 0 && w30[-2] == i) {
                            res = fn_80182150(temp_r24, v74, w30[-1], w30[-3], w30[0]);
                            if (res > 0) {
                                goto inc;
                            }
                        }
                        p78 = (char *)arg0 + 0x78;
                        __asm__ volatile("" : "+r"(p78));
                        v78 = *(s32 *)(p78 + off);
                        if (v78 != 0) {
                        if (*(s32 *)(b84 + off) == 0) {
                            if (w30[-2] == i) {
                                res = fn_80182150(temp_r24, v78, w30[-1], w30[-3], w30[0]);
                            chk:
                                if (res > 0) {
                                inc:
                                    count++;
                                }
                            }
                        }
                    }
                }
                }
                w30 += 9;
                off += 0x24;
            } while (--cnt != 0);
            __asm__ volatile("" : "+r"(cnt));
            if (count >= sp8) {
                j = 0;
                b84 = (char *)arg0 + 0x84;
                w8C = (s32 *)((char *)arg0 + 0x8C);
                off = 0;
                do {
                    temp = *(s32 *)((char *)(off + (s32)b84));
                    off += 0x24;
                    if (temp == 0) {
                        if (w8C[0] == i) {
                            if (found == 0) {
                                Script_RunScript(QB_GOAL_TETRIS_PLAY_TRICK_REMOVED_SOUND, 0, 0, 0, 0);
                            }
                            found = 1;
                            fn_80194988(arg0, j);
                        }
                    }
                    j += 1;
                    w8C += 9;
                } while (j <= 0x1D);

                {
                    s32 *tp = arr + i;
                    *tp = 0;
                }
                if (fn_8019519C(arg0) != 0) {
                    fn_80183D68(Game_GetGoalManager(), fn_8018E24C(arg0));
                }
            }
        }
        i = ip1;
    } while (i <= 0x1D);
}

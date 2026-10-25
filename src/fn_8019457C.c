// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019457C-0x80194764 (488B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void AddInteger(CStruct *, s32, s32);
extern s32 fn_8019519C(Unk_C7387A53 *);
extern s32 fn_80195124(Unk_C7387A53 *);
extern s32 fn_801745B4(s32);
extern s32 fn_801403CC(void *);
extern void fn_80194764(Unk_C7387A53 *);
extern s32 fn_80182150(Unk_FFAD6788 *, s32, s32, s32, s32);
extern s32 fn_8018223C(Unk_FFAD6788 *, s32, s32, s32, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void fn_80194988(Unk_72E9CBBF *, s32);

void fn_8019457C(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 var_r30;
    s32 temp_r25;
    s32 var_r27;
    s32 var_r26;
    s32 var_r28;
    s32 v74;
    s32 v78;
    s32 v7C;
    char *pb84;
    char *pb90;
    char *pb88;
    char *p74;
    char *p78;
    char *p7C;
    char *p90;
    char *p88;
    char *p94;

    if (GetInteger(arg0->unk0x20, QB_TRICK_FLAG, &sp8, 0) != 0) {
        if (sp8 == 0) {
            return;
        }
        AddInteger(arg0->unk0x20, QB_TRICK_FLAG, 0);
    }
    var_r30 = 0;
    if ((fn_8019519C(arg0) != 0) || (fn_80195124(arg0) != 0)) {
        var_r30 = 1;
    }
    temp_r25 = fn_801403CC(fn_801745B4(*(s32 *)&lbl_80305EAC));
    if (var_r30 != 0) {
        fn_80194764(arg0);
        return;
    }
    var_r27 = 0;
    var_r26 = 0;
    pb84 = (char *)arg0 + 0x84;
    var_r28 = 0;
    do {
        if (*(s32 *)((char *)(var_r28 + (s32)pb84)) == 0) {
            p74 = (char *)arg0 + 0x74;
            v74 = *(s32 *)(p74 + var_r28);
            if (v74 != 0) {
                pb90 = (char *)arg0 + 0x90;
                pb88 = (char *)arg0 + 0x88;
                if ((fn_80182150(temp_r25, v74, *(s32 *)(pb90 + var_r28), *(s32 *)(pb88 + var_r28), 1) != 0) ||
                    ((p78 = (char *)arg0 + 0x78), (v78 = *(s32 *)(p78 + var_r28)) != 0 &&
                     fn_80182150(temp_r25, v78, *(s32 *)(pb90 + var_r28), *(s32 *)(pb88 + var_r28), 1) != 0)) {
                    if (var_r27 == 0) {
                        Script_RunScript(QB_GOAL_TETRIS_PLAY_TRICK_REMOVED_SOUND, 0, 0, 0, 0);
                    }
                    var_r27 = 1;
                    fn_80194988(arg0, var_r26);
                }
            } else if (((p7C = (char *)arg0 + 0x7C), (v7C = *(s32 *)(p7C + var_r28)) != 0) &&
                       (fn_8018223C(temp_r25, v7C,
                                    (*(p90 = (char *)arg0 + 0x90), *(s32 *)(p90 + var_r28)),
                                    (*(p88 = (char *)arg0 + 0x88), *(s32 *)(p88 + var_r28)),
                                    (*(p94 = (char *)arg0 + 0x94), *(s32 *)(p94 + var_r28))) != 0)) {
                if (var_r27 == 0) {
                    Script_RunScript(QB_GOAL_TETRIS_PLAY_TRICK_REMOVED_SOUND, 0, 0, 0, 0);
                }
                var_r27 = 1;
                fn_80194988(arg0, var_r26);
            }
        }
        var_r26 += 1;
        var_r28 += 0x24;
    } while (var_r26 <= 0x1D);
}

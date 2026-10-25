// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80180204-0x80180390 (396B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { s32 f0; s32 f4; char _08[0x24]; } L_t;
typedef struct {
    char _00[0x0C];
    s16 unk0xC;
    char _0E[0x06];
    s32 unk0x14;
    s32 unk0x18;
    char _1C[0x20];
    L_t unk0x3C;
    s32 unk0x68;
    f32 unk0x6C;
    char _70[0x0C];
    s32 unk0x7C;
} S_t;

s32 GetChecksum_3(s32, s32);
s32 *fn_8018322C(L_t *, s32 *, s32);
s32 fn_8017471C(s32, s16);
void fn_80181014(S_t *, s32, f32);
s32 fn_80141FA4(s32);
void fn_8017EE70(S_t *, s32);
void fn_801808C8(S_t *, s32);
void fn_80180858(S_t *);
void fn_80182B88(S_t *, s32);
void fn_801FE804(s32);
s32 Game_GetGoalManager(void);
void fn_80187424(s32);

extern s32 lbl_80305EAC;
extern f32 lbl_802A9360;
extern f64 lbl_802A9358;

void fn_80180204(S_t *arg0, s32 arg1) {
    s32 sp8 = 0;
    L_t *lst = &arg0->unk0x3C;
    s32 t;

    if (sp8 < lst->f4) {
        L_t *w = lst;
        do {
            s32 *p = (s32 *)((char *)fn_8018322C(&arg0->unk0x3C, &sp8, 0) + 0x20);
            s32 i = 4;
            do {
                *p = 0;
                p -= 1;
            } while (--i != 0);
            t = sp8 + 1;
            sp8 = t;
        } while (t < w->f4);
    }
    if (arg0->unk0x68 != 0) {
        arg0->unk0x14 = 0;
        if (arg1 == 0) {
            s32 obj = fn_8017471C(lbl_80305EAC, arg0->unk0xC);
            f32 v = (f32)(f64)arg0->unk0x18 * arg0->unk0x6C;
            fn_80181014(arg0, (s32)v, lbl_802A9360);
            fn_8017EE70(arg0, fn_80141FA4(obj));
        } else {
            fn_801808C8(arg0, 1);
            fn_80181014(arg0, 0, lbl_802A9360);
        }
    }
    fn_80180858(arg0);
    arg0->unk0x7C = 0;
    fn_80182B88(arg0, 0);
    fn_801FE804(GetChecksum_3(fn_8017471C(lbl_80305EAC, arg0->unk0xC),
                             0x8BCE7E66));
    fn_80187424(Game_GetGoalManager());
}

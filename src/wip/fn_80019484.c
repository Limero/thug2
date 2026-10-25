// PARKED 2026-10-03: DIFF, 69/223 words match (~31%) — was DIFF 26.5%.
// RE-TRIAGED 2026-10-19: sweep still DIFF — ~31% masked; wall stands. Parked as-is.
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80019484
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_vs_got.py 0x80019484
// ACHIEVED: object size now matches EXACTLY (892B) and the whole prologue matches
//   (stwu -0x118 / mflr / stfd f28-f31 @0xf8-0x110 / stmw r25 @0xdc / stw lr @0x11c).
//   Frame layout (single 0xC0-byte struct at r1+8, locals packed 8..0xC7, (f64)(s32)
//   double temp at 0xD0) is EXACT — see the struct comment below.
// REMAINING DIFF: only register allocation + instruction order. First divergence
//   +0x20: want `lis r28` (long-lived rodata page base) vs got `lis r30`; want keeps
//   the 0 const in r9 / 0xff in r11, got r10 / r8. Everything after shifts with it.
// RULED OUT (do not redo):
//  * `fn_80053558` takes 5 args and arg0 is sp70 ITSELF (r3 still holds the lwz
//    result): `fn_80053558(sp8.col[0],0,0,0,0)`, else a spurious `li r3,0` and a
//    missing `li r7,0` shift everything by one word.
//  * The 0.0f/1.0f/40.0f/0.5f must be LITERALS (0.0f,1.0f,40.0f,0.5f), not `extern
//    f32 lbl_...`: as externs ngccc cannot prove they don't alias the stores, so it
//    reloads lbl_8030012C inside the loop and refuses to hoist -> +1 word.
//  * Frame padding: unused `volatile` locals AND address-taken-in-dead-code locals
//    get NO slot (measured); only a real aggregate does. Hence the one-struct
//    reconstruction below instead of pad variables.
//  * ngccc frame layout rule (measured with probes tools/../p1.c,p2.c): aggregates
//    are allocated first in DECLARATION order, then 4-byte scalars in REVERSE
//    declaration order; f32 arrays get 8-byte alignment (so the 3 fp args must be
//    separate f32s, not f32[3]); function temporaries start at local_size rounded
//    up to 16, save areas are 4-byte GPR (stmw) / 8-byte FPR above that.
// NEXT IDEA: the want keeps &sp8.name in r29 and the rodata page in r28 across the
//   loop and reuses r9/r11/r10 for one pool entry each; try making the pool literals
//   locals of one `static const f32 pool[4]` (or forcing the address-taken name
//   buffer) to see if the allocation snaps to the want's shape.
// WIP DRAFT (non-matching) — C body hand-derived from the want disassembly.
// family=m2c range=0x80019484-0x80019800 size=892B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Frame shape (frame 0x118, local area 0x08..0xD8, GPR save 0xDC, FPR save 0xF8):
// one 0xC0-byte struct at r1+8 holds the display entry (fields +0x00..+0x43),
// the sprintf scratch name (+0x48), the ten parsed colour words (+0x68..+0x93),
// the per-item handle (+0x94-4), the three fp out-args (+0x94..+0x9F) and 0x20
// bytes the retail build never references.  The (f64)(s32) cast's double temp
// then lands at 0xD0 exactly like the want.
extern char lbl_80290D50[];
extern char lbl_80290D64[];
extern char lbl_80290D98[];
extern char lbl_80290DA0[];
extern char lbl_80290DA4[];
extern char lbl_80290DA8[];
extern char lbl_80290DAC[];
extern char lbl_80290DB0[];
extern char lbl_80290DB4[];
extern char lbl_80290DB8[];
extern char lbl_80290DBC[];
extern char lbl_80290DC0[];
extern f32 lbl_80290DC8;
extern f32 lbl_80290DCC;
extern f32 lbl_80290DD0;
extern f32 lbl_80290DD4;
extern f32 lbl_8030012C;
extern s32 lbl_80300138;
extern s32 lbl_8030013C;
#include "structs.h"

typedef struct MenuDisp {
    char pad0x0[0x4];
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
    f32 unk0x30;
    f32 unk0x34;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
    char pad0x44[0x4];
    char name[0x20];
    s32 col[11];
    f32 v0;
    f32 v1;
    f32 v2;
    char pad0xA0[0x20];
} MenuDisp;

typedef struct MenuFont {
    char pad0x0[0x8];
    s32 unk0x8;
} MenuFont;

s32 sprintf(char *, char *, ...);
void *fn_80094858(MenuDisp *, f32);
void fn_800948AC(MenuDisp *, s32);
void fn_8009533C(MenuDisp *);
void fn_800945F8(void *, s32, f32 *, f32 *);
s32 fn_80128170(CStruct *, void *, void *, s32);
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 fn_8012834C(CStruct *, void *, void *, s32);
void fn_80053558(s32, s32, s32, s32, s32);
MenuFont *fn_800537D8(s32);

bool ScriptNgc_Menu(CStruct *arg0) {
    f32 k3;
    f32 k1;
    f32 k0;
    s32 i;
    MenuDisp sp8;
    MenuFont *font;
    s32 t0;
    s32 t9;
    s32 t10;
    s32 t11;

    fn_80094858(&sp8, 0.0f);
    k0 = 0.0f;
    k1 = 1.0f;
    k3 = 0.5f;
    sp8.col[1] = 0;
    sp8.col[8] = 0x80;
    sp8.col[9] = 0xff;
    sp8.col[0] = 0;
    sp8.col[2] = 0x80;
    sp8.col[3] = 0x80;
    sp8.col[4] = 0x80;
    sp8.col[5] = 0xff;
    sp8.col[6] = 0x80;
    sp8.col[7] = 0x80;
    fn_80128170(arg0, lbl_80290D50, &sp8.col[0], 0);
    fn_80128294(arg0, lbl_80290D98, &sp8.col[1], 0);
    fn_80128294(arg0, lbl_80290DA0, &sp8.col[2], 0);
    fn_80128294(arg0, lbl_80290DA4, &sp8.col[3], 0);
    fn_80128294(arg0, lbl_80290DA8, &sp8.col[4], 0);
    fn_80128294(arg0, lbl_80290DAC, &sp8.col[5], 0);
    fn_80128294(arg0, lbl_80290DB0, &sp8.col[6], 0);
    fn_80128294(arg0, lbl_80290DB4, &sp8.col[7], 0);
    fn_80128294(arg0, lbl_80290DB8, &sp8.col[8], 0);
    fn_80128294(arg0, lbl_80290DBC, &sp8.col[9], 0);
    if ((sp8.col[0] != 0) && (sp8.col[1] != 0)) {
        fn_80053558(sp8.col[0], 0, 0, 0, 0);
        i = 0;
        font = fn_800537D8(sp8.col[0]);
        for (; i < sp8.col[1]; i++) {
            sp8.col[10] = 0;
            sprintf(sp8.name, lbl_80290DC0, i);
            fn_80128170(arg0, sp8.name, &sp8.col[10], 0);
            if (sp8.col[10] != 0) {
                sp8.unk0x1C = sp8.col[10];
                sp8.v0 = k1;
                fn_8012834C(arg0, lbl_80290D64, &sp8.v0, 0);
                if (i == lbl_80300138) {
                    t0 = sp8.col[5];
                    t11 = sp8.col[3];
                    t9 = sp8.col[4] << 8;
                    t10 = sp8.col[2];
                } else {
                    t0 = sp8.col[9];
                    t11 = sp8.col[7];
                    t9 = sp8.col[8] << 8;
                    t10 = sp8.col[6];
                }
                sp8.unk0x3C = t0 | t9 | (t11 << 0x10) | (t10 << 0x18);
                sp8.unk0x14 = font->unk0x8;
                fn_800945F8(font->unk0x8, sp8.unk0x1C, &sp8.v1, &sp8.v2);
                if (sp8.v1 > 40.0f) {
                    sp8.v1 = 40.0f;
                }
                sp8.unk0x2C = sp8.v0;
                sp8.unk0x24 = lbl_8030012C;
                sp8.unk0x28 = sp8.v0;
                sp8.unk0x20 = (40.0f - (sp8.v1 * sp8.v0)) * k3;
                sp8.unk0x40 = 0;
                sp8.unk0x34 = k0;
                sp8.unk0x30 = k0;
                fn_8009533C(&sp8);
                lbl_8030012C += (f32) (f64) (s32) (sp8.v2 * sp8.v0);
            }
        }
    }
    lbl_8030013C = sp8.col[1];
    fn_800948AC(&sp8, 2);
    return true;
}
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80030580-0x800306D0 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern u8 lbl_803003B6;
extern s32 lbl_80305F9C;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0x28];
    s32 unk0x30;
} Node;

typedef struct {
    char pad0x0[0x1A];
    union {
        u16 w;
        struct {
            u8 lo;
            u8 hi;
        } b;
    } unk0x1A;
    char pad0x1C[0x4];
} Ent;

typedef struct {
    char pad0x0[0x24];
    Node *unk0x24;
    char pad0x28[0x4];
    s32 unk0x2C;
    s32 unk0x30;
    char pad0x34[0x44];
    Ent *unk0x78;
} Obj;

typedef struct {
    s8 unk0x0;
    char pad0x1[1];
    s16 unk0x2;
    u16 *unk0x4;
    char pad0x8[0x20];
} Cmd;

s32 fn_8021B55C(s32, s32);
s32 fn_8021D358(s32, u16);
s32 fn_8022986C(Node *);
s32 fn_8022A9D0(Node *);
void fn_80137CB4(Cmd *);
void fn_8013DE78(s32, Cmd *);

void fn_80030580(Obj *arg0, s32 arg1, s32 arg2) {
    Cmd sp8;
    u16 sp30;
    s32 temp_cr0_eq;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    u16 temp_r9;
    Node *var_r0;
    Node *var_r3;
    Node *var_r9;
    Node *var_r9_2;

    if ((arg2 != 0) && (arg0->unk0x30 == 0)) {
        temp_r30 = lbl_80305F9C;
        temp_r3 = fn_8021D358(temp_r30, arg0->unk0x78->unk0x1A.w);
        if ((temp_r3 != 0) && (fn_8022986C(temp_r3) != 0)) {
            temp_r31 = fn_8021B55C(temp_r30, fn_8022A9D0(temp_r3));
            temp_r9 = (sp30 & 0xFF00) | (arg1 & 0xFF);
            sp30 = temp_r9;
            sp30 = (u8)temp_r9 | (arg0->unk0x78->unk0x1A.b.hi << 8);
            if ((s8)lbl_803003B6 != arg1) {
                fn_80137CB4(&sp8);
                sp8.unk0x4 = &sp30;
                sp8.unk0x2 = 2;
                sp8.unk0x0 = 0x3D;
                fn_8013DE78(temp_r31, &sp8);
                lbl_803003B6 = (u8)arg1;
            }
        }
    }
    var_r3 = arg0->unk0x24;
    temp_cr0_eq = (~var_r3->unk0x4 == 0);
    var_r9 = var_r3;
    if (temp_cr0_eq) {
        var_r9 = NULL;
    }
    var_r0 = (var_r9 != NULL) ? (Node *)((char *)var_r9 - 4) : NULL;
    if (var_r0 != NULL) {
        if (temp_cr0_eq) {
            var_r3 = NULL;
        }
        var_r9_2 = (var_r3 != NULL) ? (Node *)((char *)var_r3 - 4) : NULL;
        var_r9_2->unk0x30 = arg1;
    }
}

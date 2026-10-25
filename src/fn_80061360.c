// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80061360-0x8006150C (428B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80293EF0;
extern f32 lbl_80293EF4;

typedef struct T_Node T_Node;

typedef struct T_Item {
    void *unk0x0;
    char pad0x4[4];
    s32 unk0x8;
} T_Item;

struct T_Node {
    T_Item *unk0x0;
    struct T_Node *unk0x4;
};

typedef struct T_Vtable {
    char pad0x0[0x38];
    s16 unk0x38;
    void (*unk0x3C)(char *, s32 *);
} T_Vtable;

typedef struct T_Obj {
    char pad0x0[0x14];
    T_Vtable *unk0x14;
} T_Obj;

typedef struct T_List {
    char pad0x0[0x10];
    T_Node *unk0x10;
} T_List;

typedef union T_B4 {
    s32 w;
    struct {
        s8 x;
        s8 y;
        s8 z;
        u8 w;
    } b;
} T_B4;

typedef struct T_Frame {
    T_Node *sp08;
    s32 sp0C;
    T_Node *sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    T_B4 sp2C;
    s8 pad30[0x28];
} T_Frame;

void fn_80053D10(f32 *, f32 *, f32 *, f32, f32, f32);
s32 fn_8005F8E0(void *);

s32 fn_80061360(T_List *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    T_Frame fr;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r29;
    s32 flag;
    T_Obj *o;
    T_B4 *q;

    flag = (arg1 ^ 0xC4E78E22) == 0;
    var_r29 = 0;
    fr.sp08 = arg0->unk0x10;
    fr.sp10 = (fr.sp08 != NULL) ? fr.sp08->unk0x4 : NULL;
    if (fr.sp10 != fr.sp08) {
        temp_f30 = lbl_80293EF0;
        temp_f31 = lbl_80293EF4;
        do {
            if (((arg1 == fr.sp10->unk0x0->unk0x8) || !(!(flag || 0))) &&
                (fn_8005F8E0(fr.sp10->unk0x0->unk0x0) == 0)) {
                var_r29 = 1;
                fn_80053D10(&fr.sp20, &fr.sp24, &fr.sp28, farg0, farg1, farg2);
                q = &fr.sp2C;
                q->b.x = (s8) ((fr.sp20 * temp_f30) + temp_f31);
                q->b.y = (s8) ((fr.sp24 * temp_f30) + temp_f31);
                q->b.z = (s8) ((fr.sp28 * temp_f30) + temp_f31);
                q->b.w = 0xFF;
                o = fr.sp10->unk0x0->unk0x0;
                fr.sp18 = q->w;
                o->unk0x14->unk0x3C((char *)o + o->unk0x14->unk0x38, &fr.sp18);
            }
            fr.sp10 = fr.sp10->unk0x4;
        } while (fr.sp10 != fr.sp08);
    }
    return var_r29;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800567E4-0x800569A8 (452B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80293220[];
extern char lbl_80293240[];
extern char lbl_80293290[];

/* 0x20-byte object built by fn_800071D4: four psq_st, i.e. 8 floats 0x00..0x1F. */
typedef struct Pad8xF32 {
    f32 v[8];
} Pad8xF32;

/* 0x18-byte list node: +4 payload, +8 flag, +0xC next, +0x10 prev, +0x14 vtable. */
typedef struct Unk_Node18 {
    char pad0x0[0x4];
    void *unk0x4;
    s32 unk0x8;
    struct Unk_Node18 *unk0xC;
    struct Unk_Node18 *unk0x10;
    s32 unk0x14;
} Unk_Node18;

/* 0x10-byte list element; only the leading s32 is read (lwzx). */
typedef struct Unk_Elem10 {
    s32 unk0x0;
    char pad0x4[0xC];
} Unk_Elem10;

/* +0x30 s16 method offset (this-relative), +0x34 method pointer. */
typedef struct Unk_Vtbl34 {
    char pad0x0[0x30];
    s16 unk0x30;
    s32 (*unk0x34)(void *, s32);
} Unk_Vtbl34;

s32 fn_80055E74(Unk_CFB386B2 *, s32);
s32 fn_8005742C(Unk_CFB386B2 *);
void fn_80057C98(s32, s32);
void fn_80057D90(void *, s32);
void fn_800583FC(void *, s32);
void fn_80055EA4(Unk_CFB386B2 *, void *);
s32 fn_80058268(void *, Unk_Elem10 *);
void fn_80056B1C(Unk_CFB386B2 *, void *);
void *Mem_NewZero(s32);
s32 fn_800127E4(void *, s32, void *, s32, s32);
void fn_80056308(s32, s32, s32, s32, s32, s32, s32);
void fn_800071D4(s32);

s32 fn_800567E4(Unk_CFB386B2 *arg0, s32 arg1) {
    Pad8xF32 sp8;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r24_str;
    Unk_Node18 *temp_r3_2;
    Unk_Node18 *temp_r11;
    Unk_Vtbl34 *temp_r9;

    fn_800071D4(&sp8);
    if ((s32) arg0->unk0x15C == 0) {
        return 0;
    }
    var_r24_str = (s32)lbl_80293240;
    sprintf((char *)arg0 + 0x1E8,(s32)lbl_80293220, arg1, arg1, var_r24_str, fn_8005570C());
    temp_r3 = fn_800127E4((char *)arg0 + 0xD8, 0, 0, 0, 0);
    if (temp_r3 != 0) {
        fn_80056308(arg0, temp_r3, (char *)arg0 + 0x268, (char *)arg0 + 0x26C, (char *)arg0 + 0x270, &sp8, 0);
    }
    temp_r0 = arg0->unk0x268;
    if (temp_r0 > 0) {
        var_r28 = 0;
        if (var_r28 < (s32) arg0->unk0x268) {
        var_r24 = 1;
        var_r25 = (s32)lbl_80293290;
        var_r26 = 0;
        var_r29 = 0;
        do {
            var_r30 = fn_80055E74(arg0, *((s32 *)((char *)var_r29 + arg0->unk0x26C)));
            if (var_r30 == 0) {
                var_r30 = fn_8005742C(arg0);
                fn_80057C98(var_r30, *((s32 *)((char *)var_r29 + arg0->unk0x26C)));
                fn_80057D90(var_r30, 1);
                fn_800583FC(var_r30, 4);
                arg0->unk0x274 = var_r24;
                fn_80055EA4(arg0, var_r30);
                temp_r3_2 = Mem_NewZero(0x18);
                temp_r3_2->unk0xC = temp_r3_2;
                temp_r3_2->unk0x10 = temp_r3_2;
                temp_r3_2->unk0x14 = var_r25;
                temp_r3_2->unk0x4 = var_r30;
                temp_r3_2->unk0x8 = var_r26;
                temp_r11 = arg0->unk0x280;
                temp_r3_2->unk0x10 =  temp_r11->unk0x10;
                temp_r3_2->unk0xC = temp_r11;
                *(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0x10) + 0xC) = temp_r3_2;
                temp_r11->unk0x10 = temp_r3_2;
            }
            var_r28 += 1;
            fn_80058268(var_r30, arg0->unk0x26C + var_r29);
            var_r29 += 0x10;
        } while (var_r28 < (s32) arg0->unk0x268);
        }
        fn_80056B1C(arg0, arg0->unk0x27C);
    }
    temp_r9 = arg0->unk0x284;
    return temp_r9->unk0x34((char *)arg0 + temp_r9->unk0x30, arg1);
}

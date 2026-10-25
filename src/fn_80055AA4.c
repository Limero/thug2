// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055AA4-0x80055B9C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_800071D4(void *);
void *Mem_Alloc2(s32);
void *Mem_NewZero(s32);
s32 fn_80057724(void *, s32);

extern char lbl_802932A8[];
extern char lbl_80293278[];

typedef struct {
    char pad0[4];
    s32  unk4;
    s32  unk8;
    s32  unkC;
    s32  unk10;
    s32  unk14;
} NODE18;

typedef struct {
    u8   unk0x00;
    char pad0x004[8];
    s32  unk0x0C;
    char pad0x010[0x78];
    s32  unk0x088;
    s32  unk0x08C;
    char pad0x090[0x40];
    s32  unk0xD0;
    s32  unk0xD4;
    u8   unk0xD8;
    char pad0x0D9[0x7F];
    s32  unk0x158;
    s32  unk0x15C;
    s32  unk0x160;
    u8   unk0x164;
    char pad0x165[0x7F];
    s32  unk0x1E4;
    char pad0x1E8[0x80];
    s32  unk0x268;
    s32  unk0x26C;
    s32  unk0x270;
    s32  unk0x274;
    s32  unk0x278;
    s32  unk0x27C;
    s32  unk0x280;
    s32  unk0x284;
} OBJ;

void *fn_80055AA4(OBJ *arg0, s32 arg1) {
    NODE18 *temp_r3;
    NODE18 *temp_r3_2;

    arg0->unk0x284 = (s32)lbl_802932A8;
    fn_800071D4((char *)arg0 + 0x90);
    fn_800071D4((char *)arg0 + 0xB0);
    arg0->unk0xD4 = 0;
    arg0->unk0xD0 = fn_80057724(Mem_Alloc2(0x18), arg1);
    arg0->unk0x00 = 0;
    arg0->unk0xD8 = 0;
    arg0->unk0xD4 = 0;
    arg0->unk0x15C = 0;
    arg0->unk0x160 = 0;
    arg0->unk0x158 = 0;
    arg0->unk0x164 = 0;
    arg0->unk0x1E4 = 0;
    arg0->unk0x26C = 0;
    arg0->unk0x270 = 0;
    arg0->unk0x268 = 0;
    arg0->unk0x274 = 0;
    arg0->unk0x278 = 0;
    temp_r3 = (NODE18 *)Mem_NewZero(0x18);
    temp_r3->unk4 = -1;
    temp_r3->unk8 = 0;
    temp_r3->unkC = (s32)temp_r3;
    temp_r3->unk10 = (s32)temp_r3;
    temp_r3->unk14 = (s32)lbl_80293278;
    arg0->unk0x27C = (s32)temp_r3;
    temp_r3_2 = (NODE18 *)Mem_NewZero(0x18);
    temp_r3_2->unk4 = -1;
    temp_r3_2->unk14 = (s32)lbl_80293278;
    temp_r3_2->unk8 = 0;
    temp_r3_2->unkC = (s32)temp_r3_2;
    temp_r3_2->unk10 = (s32)temp_r3_2;
    arg0->unk0x280 = (s32)temp_r3_2;
    arg0->unk0x088 = 0;
    arg0->unk0x08C = 0;
    return arg0;
}

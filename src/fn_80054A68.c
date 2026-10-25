// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054A68-0x80054B24 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80293130[];
extern char lbl_80364C1C[];
extern char lbl_802931A8[];
typedef struct Unk_C7387A53 { char pad0x0[0x80]; s32 unk0x80; s32 unk0x84; } Unk_C7387A53;
typedef struct Unk_C8FEE62D { char pad0x0[0x4]; s32 unk0x4; s32 unk0x8; s32 unk0xC; s32 unk0x10; s32 unk0x14; } Unk_C8FEE62D;
s32 Script_GenerateCRC(s32);
void fn_80054894(char *arg0, s32 arg1, s32 arg2);
void fn_8005626C(void *arg0, char *arg1);
void fn_8001075C(s32 arg0);
void *Mem_NewZero(s32 size);
void fn_80010760(void);
void fn_80054A68(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    char sp8[0x80];
    Unk_C8FEE62D *temp_r3;
    char *hb;
    fn_80054894(sp8, arg1, arg4);
    arg0->unk0x80 = Script_GenerateCRC(arg1);
    arg0->unk0x84 = arg2;
    if (arg3 == 0) {
        fn_8005626C(arg0, sp8);
    }
    fn_8001075C((s32)lbl_80293130);
    temp_r3 = Mem_NewZero(0x18);
    *(volatile s32 *)&temp_r3->unk0xC = (s32)temp_r3;
    temp_r3->unk0x10 = (s32)temp_r3;
    temp_r3->unk0x14 = (s32)lbl_802931A8;
    temp_r3->unk0x4 = arg0;
    temp_r3->unk0x8 = 0;
    hb = (char *)lbl_80364C1C;
    temp_r3->unk0x10 = *(s32 *)(hb + 0x10);
    temp_r3->unk0xC = (s32)hb;
    *(s32 *)(*(s32 *)(hb + 0x10) + 0xC) = temp_r3;
    *(s32 *)(hb + 0x10) = temp_r3;
    fn_80010760();
}

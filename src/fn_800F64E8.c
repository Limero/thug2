// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F64E8-0x800F6610 (296B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301B40;
s32 Script_GenerateCRC(s32);
s32 fn_800F1F74(s32, u8 *);
void fn_8016A6C0(void *, void *, void *, void *);
s32 fn_800F2010(s32);
s32 fn_800F1C34(Unk_A231C4C2 *, s32, s32);
void fn_8012DF78(void);
s32 fn_80125A08(void *, s32);
void fn_800F3A6C(s32);
s32 fn_80013788(s32);
s32 fn_800F3794(void *, s32, s32);

void fn_800F64E8(Unk_C8FEE62D *arg0, void *arg1, s32 arg2) {
    s32 sp8[32];
    Unk_07FDFB02 *temp_r9;
    s32 temp_r0;
    s32 temp_r30;
    s32 var_r30;

    arg0->unk0x58 =
        Script_GenerateCRC(arg0->unk0x64);
    fn_800F1F74(arg0->unk0x64, &sp8);
    fn_8016A6C0((void *)arg0->unk0x64, arg1, 1, 1);
    var_r30 = lbl_80301B40;
    fn_800F1C34(var_r30,
        fn_800F2010(arg0->unk0x64),
        arg0->unk0x68);
    fn_8012DF78();
    temp_r30 = fn_80125A08(&sp8, 0);
    arg0->unk0x5C = Script_GenerateCRC(&sp8);
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((s32 (*)(void *, void *))temp_r9->unk0x5C)(
        (char *)arg0 + temp_r9->unk0x58, temp_r30);
    temp_r9 = *((void * *)&arg0->unk0x50);
    temp_r0 = ((s32 (*)(void *))*((s32 *)&temp_r9->unk0x14))(
        (char *)arg0 + temp_r9->unk0x10);
    arg0->unk0x60 = temp_r0;
    if (arg0->unk0x20 != 0) {
        fn_80013788(arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((s32 (*)(void *))*((s32 *)&temp_r9->unk0x84))(
        (char *)arg0 + temp_r9->unk0x80);
    fn_800F3A6C(arg0->unk0x64);
    arg0->unk0x64 = 0;
    fn_800F3794(arg0, arg1, arg2);
}

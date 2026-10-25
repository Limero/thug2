// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019DA3C-0x8019DB68 (300B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800168B0(void *);
void fn_800168B8(void);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
void AddInteger(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8019DA3C(Unk_C7387A53 *arg0) {
    char sp8[0x100];
    s16 sp108;
    Unk_C7387A53 *temp_r27;
    s32 temp_r3;
    s32 temp_r31;
    u8 temp_r0;
    u8 temp_r9;
    char *p;
    s32 var_r30;

    temp_r27 = *((void * *)&arg0->unk0x20);
    var_r30 = 0;
    temp_r3 = fn_800168B0(sp8);
    if (var_r30 < temp_r3) {
        p = sp8;
        do {
            temp_r9 = p[var_r30];
            if (((u32)(temp_r9 - 0x20) <= 0x5EU) || ((s8)temp_r9 == 0x19) || ((s8)temp_r9 == 0x18)) {
                temp_r31 = CStruct_ctor(CStruct_new(8));
                temp_r0 = p[var_r30];
                if ((s8)temp_r0 == 0x19) {
                    AddChecksum(temp_r31, 0, QB_GOT_ENTER);
                } else if ((s8)temp_r0 == 0x18) {
                    AddChecksum(temp_r31, 0, QB_GOT_BACKSPACE);
                } else {
                    sp108 = temp_r0 << 8;
                    AddString(temp_r31, QB_TEXT, &sp108);
                }
                AddInteger(temp_r31, QB_MAX_LENGTH, temp_r27->unk0x58);
                Script_RunScript(QB_HANDLE_KEYBOARD_INPUT, temp_r31, 0, 0, 0);
                if (temp_r31 != 0) {
                    CStruct_delete(temp_r31, 3);
                }
            }
            var_r30 += 1;
        } while (var_r30 < temp_r3);
    }
    fn_800168B8();
}

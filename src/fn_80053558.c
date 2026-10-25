// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053558-0x80053704 (428B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x18];
    s32 unk0x18;
} ScriptSlot;

extern ScriptSlot lbl_80364A38[0x10];
extern s32 lbl_80364BF8[6];
extern bool lbl_8030043C;
extern char lbl_80292F24[];
extern u8 lbl_803C9DF8[0x20];

char *strcpy(char *, const char *);
s32 fn_800537D8(s32);
void fn_800585E8(s32, s32, s32);
void fn_8005861C(s32, s32);
void fn_80058650(s32, s32);
s32 fn_8007BC68(s32);
void fn_80053A58(s32, s32, s32);
s32 Script_GenerateCRC(s32);
CStruct *fn_80125A08(char *, s32);
s32 fn_801293FC(CStruct *, s32);

void fn_80053558(s32 arg0, void *arg1, s32 arg2, void *arg3, void *arg4) {
    s32 i;
    ScriptSlot *slot;
    s32 crc;
    u32 j;
    CStruct *tbl;

    if (fn_800537D8(arg0) != 0) {
        fn_800585E8(fn_800537D8(arg0), arg1, arg2);
        if (arg3 != 0) {
            fn_8005861C(fn_800537D8(arg0), arg3);
        }
        fn_80058650(fn_800537D8(arg0), arg4);
        return;
    }

    i = 0;
    slot = lbl_80364A38;
    while (i <= 0xF) {
        if (slot->unk0x18 == 0) {
            slot->unk0x18 = fn_8007BC68(arg0);
            fn_800585E8(slot->unk0x18, arg1, arg2);
            if (arg3 != 0) {
                fn_8005861C(slot->unk0x18, arg3);
            }
            fn_80058650(slot->unk0x18, arg4);
            strcpy((char *)slot, (char *)arg0);
            crc = Script_GenerateCRC(arg0);
            fn_80053A58((s32)lbl_80364BF8, &crc, (s32)slot);
            break;
        }
        i++;
        slot++;
    }

    if (lbl_8030043C == 0) {
        tbl = fn_80125A08(lbl_80292F24, 0);
        if (tbl != NULL) {
            u8 *buf = lbl_803C9DF8;
            for (j = 0; j < 0x20; j++) {
                s32 v = ((u32)j < (u32)tbl->unk0x4) ? fn_801293FC(tbl, j) : 0;
                buf[j] = (v <= 9) ? v + 0x30 : v + 0x57;
            }
            lbl_8030043C = 1;
        }
    }
}

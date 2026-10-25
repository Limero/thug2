// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801611C4-0x80161274 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;

void *fn_8021D358(s32, s32);
void AddInteger(CStruct *, s32, s32);
s32 GetVector(CStruct *, s32, CStruct *, s32);

bool ScriptPlaceObject(CStruct *arg0, Unk_EFC8CFAD *arg1) {
    s32 sp8[4];
    Unk_EE36B018 *temp_r11;
    Unk_C7387A53 *temp_r3;
    __ps_t *dst;
    register s32 count __asm__("r11");
    s32 glob;

    temp_r11 = *((void * *)&arg1->unk0xBC);
    glob = lbl_80305F9C;
    __asm__("" : "+r"(glob));
    if (temp_r11 != NULL) {
        temp_r3 = fn_8021D358(glob, temp_r11->unk0x1A);
        if (temp_r3 != NULL) {
            AddInteger(arg1->unk0x18, QB_INDEX, temp_r3->unk0x38);
            GetVector(arg0, QB_POS, &sp8[0], 0);
            count = temp_r3->unk0x38;
            dst = (__ps_t *)((count * 16) + (s32)temp_r3);
            temp_r3->unk0x38 = count + 1;
            dst = (__ps_t *)((char *)dst + (s32)0x188);
            dst[0] = *(__ps_t *)&sp8[0];
            dst[1] = *(__ps_t *)&sp8[2];
            return true;
        }
    }
    return false;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800771FC-0x800772BC (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *Mem_NewZero(s32 size);
void fn_8007E86C(void *, void *);
void fn_8007E820(void *, void *);
void fn_8005626C(void *, void *);
void fn_80095574(void);
#include "structs.h"
s32 fn_8007E6D4(void *);
void DCFlushRange(void *, void *);
CStruct *fn_800768A8(void *, void *, s32, s32, s32);
s32 Script_GenerateCRC(char *);
extern char lbl_80295720[];

void *fn_800771FC(s32 arg0, void *arg1, s32 arg2, void *arg3, void *arg4) {
    char buf[12];
    CStruct *temp_r29;
    CStruct *temp_r30;
    sprintf(buf, (s32)lbl_80295720, arg0);
    DCFlushRange(arg1, arg2);
    temp_r29 = fn_800768A8(arg1, arg4, 0, 0, 0);
    temp_r29->unk0x80 = Script_GenerateCRC(buf);
    temp_r29->unk0x84 = (s32)arg4;
    fn_8005626C(temp_r29, buf);
    fn_80095574();
    temp_r30 = fn_8007E6D4(Mem_NewZero(0xD0));
    fn_8007E86C(temp_r30, arg3);
    fn_8007E820(temp_r30, temp_r29);
    temp_r30->unk0x4 = (s32)arg4;
    return temp_r30;
}

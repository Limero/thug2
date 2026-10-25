// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80105F70-0x80105FE8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// vtable view: offset field is s16 (retail `lha 0xa8`), method ptr at 0xAC.
typedef struct {
    s32 unk0x0;
    char unk0x4[0xA4];
    s16 unk0xA8;
    s16 unk0xAA;
    s32 unk0xAC;
} S_80105F70_vt;

void fn_80105F70(Unk_5CB48605 *arg0, void *arg1) {
    S_80105F70_vt *var_r9;
    s32 (*var_fp)(void *);
    s32 var_r3;
    s32 var_r11;
    s32 *vals;
    s32 *ptrs;

    var_r9 = *(S_80105F70_vt **)((char *)arg1 + 0xC);
    var_fp = *(s32 (**)(void *))((char *)var_r9 + 0xAC);
    var_r3 = var_fp((char *)arg1 + var_r9->unk0xA8);
    vals = (s32 *)((char *)arg0 + 0x24);
    ptrs = (s32 *)((char *)arg0 + 0x20);
    vals[arg0->unk0xFC0 * 2] = var_r3;
    var_r11 = arg0->unk0xFC0;
    ptrs[var_r11 * 2] = (s32)arg1;
    arg0->unk0xFC0 = var_r11 + 1;
    arg0->unk0xFC8 = arg0->unk0xFC8 + 1;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802437C0-0x80243840 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 Mem_NewZero(s32);
extern s32 fn_80243434(Unk_12004030 *);
void fn_802437C0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx;
    CStruct *entry;
    s32 *tbl;
    s32 cnt;
    char *flg;

    idx = arg3 * 4;
    tbl = (s32 *)((char *)arg0 + 4);
    entry = fn_80243434(Mem_NewZero(0xF0));
    *(s32 *)((char *)tbl + idx) = entry;
    cnt = *arg0;
    entry->unk0x4 = cnt;
    *arg0 = cnt + 1;
    *(s32 *)(*(s32 *)((char *)tbl + idx) + 0xC) = arg1;
    *(s32 *)(*(s32 *)((char *)tbl + idx) + 0x14) = arg2;
    *(s32 *)(*(s32 *)((char *)tbl + idx) + 0xE8) = arg3;
    flg = (char *)arg0 + 0x84;
    *(s32 *)(flg + idx) = 1;
}

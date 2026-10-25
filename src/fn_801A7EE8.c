// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7EE8-0x801A7F8C (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801259C8(s32, s32);
s32 GetChecksum(CStruct *, s32);
s32 fn_801A7F8C(Unk_C08FFCDD *, s32);
void fn_801A7EE8(Unk_C08FFCDD *arg0) {
    CStruct *list;
    s32 t;
    s32 i;
    char *base;

    arg0->unk0x404 = 0;
    list = (s32 *)fn_801259C8(QB_CONFIGURABLETRICKS, 0);
    i = 0;
    while (i < list->unk0x4) {
        base = (char *)arg0 + 4;
        t = GetChecksum((s32)list, i);
        if (fn_801A7F8C(arg0, t) == -1) {
            *(s32 *)(base + (arg0->unk0x404 << 2)) = t;
            arg0->unk0x404 += 1;
        }
        i++;
    }
}

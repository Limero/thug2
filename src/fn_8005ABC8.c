// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005ABC8-0x8005AC44 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
CStruct *fn_80059EE4(void *);
CStruct *fn_8005A0A8(CStruct *);
void fn_800577A0(CStruct *);
CStruct *fn_800577B4(CStruct *, s32 *);
CStruct *fn_80057CA0(CStruct *);
void fn_8005A3AC(CStruct *);

void fn_8005ABC8(s32 arg0, void *arg1) {
    CStruct *record;
    CStruct *list;
    CStruct *entry;

    if (arg1 != 0) {
        if ((record = fn_80059EE4(arg1)) != 0) {
            list = fn_8005A0A8(record);
            if (list != 0) {
                fn_800577A0(list);
                while ((entry = fn_800577B4(list, 0)) != 0) {
                    if (fn_80057CA0(entry) != 0) {
                        fn_8005A3AC(entry);
                    }
                }
            }
        }
    }
}

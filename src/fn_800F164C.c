// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F164C-0x800F16C8 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Iterates the list stored at arg0+0x10010 (array of 12-byte entries whose
// first word is a pointer); for the first bound[i] entries (bound = entry+4),
// resolves entry[i] via fn_80129528 and dispatches fn_800F16C8(arg0, arg1, i,
// entry). Suggested rename: Fn_800F164C_IterateEntries_Bound (an iteration &
// dispatch helper over a bounded element list).
#include "types.h"
#include "structs.h"
typedef struct { s32 p; s32 q; s32 r; } Ent;
s32 fn_800F16C8(void *, void *, void *, CStruct *);
s32 fn_80129528(CStruct *, void *);
void fn_800F164C(s32 arg0, s32 arg1) {
    u32 var_r31;
    CStruct *temp_r30;
    Ent *row;

    row = (Ent *)((char *)arg0 + 0x10010);
    var_r31 = 0U;
    temp_r30 = (void *)row[arg1].p;
    if (var_r31 < *((u32 *)&temp_r30->unk0x4)) {
        do {
            fn_800F16C8(arg0, arg1, var_r31, fn_80129528(temp_r30, var_r31));
            var_r31 += 1;
        } while (var_r31 < *((u32 *)&temp_r30->unk0x4));
    }
}
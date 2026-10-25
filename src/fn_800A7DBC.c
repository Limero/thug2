// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7DBC-0x800A7E30 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_800A7DBC(CStruct *arg0) {
    s32 i = 0;

    while (i < arg0->unk0x4) {
        s32 base = arg0->unk0x0;
        s32 *p = (s32 *)((i * 0xC) + (s32)base);

        if (*p != 0) {
            CObject_RemoveRefLink((CStruct *)*p, (CStruct *)p);
            *p = 0;
        }
        *p = 0;
        i += 1;
    }
}

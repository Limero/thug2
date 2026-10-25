// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7E30-0x800A7EC4 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_800A7E30(CStruct *arg0, CStruct *arg1) {
    s32 i;
    s32 off;
    s32 zero;
    CStruct **arr;
    CStruct *link;
    CStruct *e;
    for (i = 0; i < arg0->unk0x4; i++) {
        off = i * 0xC;
        arr = (CStruct **)arg0->unk0x0;
        link = (CStruct *)(off + (s32)arr);
        e = *(CStruct **)((char *)(off + (s32)arr));
        if (e == arg1) {
            zero = 0;
            if (arg1 != 0) {
                CObject_RemoveRefLink(arg1, link);
                *(CStruct **)((char *)(off + (s32)arr)) = zero;
            }
            *(CStruct **)((char *)(off + (s32)arr)) = zero;
        }
    }
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801289E4-0x80128A90 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80125480(s32);
// ContainsFlag @ 0x801289E4
bool ContainsFlag(CStruct *arg0, s32 arg1) {
    CStruct *v;
    v = *((void * *)&arg0->unk0x4);
    while (v != NULL) {
        if (v->unk0x4 == 0 && (*(s32 *)((char *)v) & 0x7F0000) == 0xD0000) {
            s32 id = v->unk0x8;
            if (id == arg1) {
                return true;
            }
            t2:;
            {
                void *t = fn_80125480(id);
                if (t != NULL && ((Unk_1D62F22E *)t)->unk0x2 == 0xA &&
                    ContainsFlag(((Unk_1D62F22E *)t)->unk0xC, arg1) != 0) {
                    return true;
                }
            }
        }
        v = *((void * *)&v->unk0xC);
    }
    return false;
}

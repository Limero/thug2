// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127F60-0x801280E0 (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80125480(s32);
s32 fn_80127F60(CStruct *arg0, s32 arg1, s32 arg2, f32 *arg3) {
    volatile double sp8d;
    volatile double _dummy;
    void *v = *((void * *)&arg0->unk0x4);
    s32 found = 0;
    if (v != NULL) {
        do {
            s32 key = ((CStruct *)v)->unk0x4;
            if (key == arg1) {
                if ((s32)((*(s32 *)v >> 16) & 0x7F) == arg2) {
                    found = 1;
                    *(s32 *)arg3 = ((CStruct *)v)->unk0x8;
                } else if ((*(s32 *)v & 0x7F0000) == 0x10000 && arg2 == 2) {
                    s32 val = ((CStruct *)v)->unk0x8;
                    found = 1;
                    *arg3 = (f32)val;
                } else if ((*(s32 *)v & 0x7F0000) == 0xD0000) {
                    void *t = fn_80125480(((CStruct *)v)->unk0x8);
                    if (t != NULL) {
                        u8 ty = ((Unk_1D62F22E *)t)->unk0x2;
                        if ((s32)ty == arg2) {
                            found = 1;
                            *(s32 *)arg3 = ((Unk_1D62F22E *)t)->unk0xC;
                        } else if ((s32)ty == 1 && arg2 == 2) {
                            s32 val = ((Unk_1D62F22E *)t)->unk0xC;
                            found = 1;
                            *arg3 = (f32)val;
                        }
                    }
                }
            } else if (key == 0 && (*(s32 *)v & 0x7F0000) == 0xD0000) {
                void *t = fn_80125480(((CStruct *)v)->unk0x8);
                if (t != NULL && ((Unk_1D62F22E *)t)->unk0x2 == 0xA &&
                    fn_80127F60(*((void * *)&((Unk_1D62F22E *)t)->unk0xC), arg1, arg2, (f32 *)&sp8d) != 0) {
                    found = 1;
                    *(s32 *)arg3 = *(s32 *)&sp8d;
                }
            }
            v = *((void * *)&((CStruct *)v)->unk0xC);
        } while (v != NULL);
    }
    return found;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801286D0-0x80128804 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.

#include "types.h"
#include "structs.h"
s32 fn_80125480(s32);
// WIP DRAFT — EXACT : rewritten from retail flow. Keys:
//  - arm order: key==arg1 first, then key==0 (both tag 0xD0000)
//  - validation gate tests ARG1 (search mode), not arg3 — hoisted into
//    callee-saved cr4 by the compiler (mfcr/mtcrf 8 ABI save/restore)
//  - decl order val-then-ne pins val->r30 / ne->r29
//  - truth value must be ((x ^ 0xA) == 0): emits subfic/adde carry form
// GetChecksum_2 = recursive keyed-entry lookup with reload-on-miss
// (suggested rename: FindEntryRecursive).
s32 fn_80129570(s32, s32);
// GetChecksum_2 @ 0x801286D0
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    void *v = *((void * *)&arg0->unk0x4);
    s32 found = 0;
    while (v != NULL) {
        s32 key = ((CStruct *)v)->unk0x4;
        if (key == arg1) {
            if ((*(s32 *)((char *)v) & 0x7F0000) == 0xD0000) {
                s32 val = ((CStruct *)v)->unk0x8;
                s32 ne = 0;
                if (arg1 == 0) {
                    void *t = fn_80125480(val);
                    if (t != NULL) {
                        ne = ((((Unk_1D62F22E *)t)->unk0x2 ^ 0xA) == 0);
                    }
                }
                if (ne == 0) {
                    *arg2 = val;
                    found = 1;
                }
            }
        } else if (key == 0 && (*(s32 *)((char *)v) & 0x7F0000) == 0xD0000) {
            void *t = fn_80125480(((CStruct *)v)->unk0x8);
            if (t != NULL && ((Unk_1D62F22E *)t)->unk0x2 == 0xA &&
                GetChecksum_2(*((void * *)&((Unk_1D62F22E *)t)->unk0xC), arg1, arg2, 0) != 0) {
                found = 1;
            }
        }
        v = *((void * *)&((CStruct *)v)->unk0xC);
    }
    if (arg3 != 0 && found == 0) {
        fn_80129570(arg0, 0);
    }
    return found;
}

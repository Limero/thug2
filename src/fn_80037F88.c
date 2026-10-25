// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80037F88-0x80038094 (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80037C40(s32, s32, s32, s32);
s32 fn_80036328(Unk_C8FEE62D *, s32);
s32 fn_8003A324(s32, s32);
s32 fn_8003A31C(s32);
s32 fn_80037BF0(void *arg2, s32 arg0, void *arg1);
CStruct *fn_801259C8(s32 arg0, s32 arg1);
s32 GetChecksum(CStruct *arg0, s32 arg1);
void fn_80037F88(Unk_C8FEE62D *arg0, Unk_9994C3F5 *arg1, s32 c) {
    s32 sp8[4];
    s32 h;
    s32 i;
    s32 id;
    s32 use;
    s32 j;
    CStruct *arr;

    h = arg1->unk0x8;
    i = 0;
    while (i < fn_8003A31C(h)) {
        id = fn_8003A324(h, i);
        if (fn_80036328(arg0, id) != 0) {
            if (fn_80037BF0(arg1, id, &sp8[0]) != 0) {
                use = 1;
                if (c != 0) {
                    arr = fn_801259C8(QB_NONLOCAL_BONES, 0);
                    if (arr != NULL) {
                        j = 0;
                        if ((u32)j < *(u32 *)&arr->unk0x4) {
                            do {
                                if (GetChecksum(arr, j) == id) {
                                    use = 0;
                                }
                                j += 1;
                            } while ((u32)j < *(u32 *)&arr->unk0x4);
                        }
                    }
                }
                fn_80037C40((s32)arg0, id, (s32)&sp8[0], use);
            }
        }
        i += 1;
    }
}

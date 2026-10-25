// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFE0C-0x800EFEB8 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800F116C(s32);
void *fn_800F1180(s32, s32);
void fn_800F123C(s32, void *);
void fn_800F1390(s32, s32);
void fn_800EFC38(void *, void *);
void Mem_Free(void *);
void fn_800EFE0C(CStruct *arg0, s32 arg1) {
    s32 sp8;
    Unk_C7387A53 *res;
    void *next;

    fn_800F116C(arg0->unk0x4);
    res = (Unk_C7387A53 *)fn_800F1180(arg0->unk0x4, 0);
    if (res != NULL) {
        do {
            next = fn_800F1180(arg0->unk0x4, 0);
            sp8 = res->unk0xC;
            if (res != NULL) {
                fn_800EFC38(res, (void *)3);
            }
            fn_800F123C(arg0->unk0x4, &sp8);
            res = (Unk_C7387A53 *)next;
        } while (res != NULL);
    }
    if (arg0->unk0x4 != 0) {
        fn_800F1390(arg0->unk0x4, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DF4E0-0x800DF5B4 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80009C00(CStruct *);
s32 fn_80009C84(Unk_9994C3F5 *);
void fn_8009F558(Unk_C8FEE62D *, s32);
extern char lbl_8029A500[];

void fn_800DF4E0(Unk_4E650DE8 *arg0, s32 arg1) {
    void *objA;
    void *objB;
    Unk_4E705049 *vtA;
    Unk_4E705049 *vtB;

    arg0->unk0x18 = (s32)lbl_8029A500;
    if (arg0->unk0x51C != NULL) {
        if (fn_80009C84(arg0->unk0x51C) != 0) {
            fn_80009C00(arg0->unk0x51C);
        }
        objA = arg0->unk0x51C;
        if (objA != NULL) {
            vtA = ((CScript *)objA)->unk0x18;
            ((s32 (*)(void *, s32))vtA->unk0x1C)(
                objA + vtA->unk0x18, 3);
        }
    }
    if (arg0->unk0x520 != NULL) {
        if (fn_80009C84(arg0->unk0x520) != 0) {
            fn_80009C00(arg0->unk0x520);
        }
        objB = arg0->unk0x520;
        if (objB != NULL) {
            vtB = ((CScript *)objB)->unk0x18;
            ((s32 (*)(void *, s32))vtB->unk0x1C)(
                objB + vtB->unk0x18, 3);
        }
    }
    fn_8009F558(arg0, arg1);
}

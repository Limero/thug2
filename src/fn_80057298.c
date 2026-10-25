// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057298-0x80057334 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
#include "types.h"
typedef struct {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} VT_57298;
s32 fn_80057870(s32);
void fn_8005840C(CStruct *, s32);
s32 fn_800577B4(CStruct *, s32 *);
void fn_800577A0(CStruct *);
s32 fn_800582C0(CStruct *o);
void fn_80107228(void *);
void fn_80057298(Unk_FFAD6788 *arg0) {
    void *item;
    VT_57298 *vt;
    if ((s32) arg0->unk0xD4 != 0) {
        fn_800577A0(arg0->unk0xD0);
        while ((item = fn_800577B4(arg0->unk0xD0, 0)) != NULL) {
            if (fn_800582C0(item) & 8) {
                fn_8005840C(item, 0x40);
                vt = (VT_57298 *)((CScript *)item)->unk0x18;
                ((s32 (*)(void *, s32))vt->unk0xC)((char *)item + vt->unk0x8, 3);
            }
        }
        fn_80107228(arg0->unk0xD4);
        fn_80057870(arg0->unk0xD0);
    }
}

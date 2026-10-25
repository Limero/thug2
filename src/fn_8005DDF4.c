// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DDF4-0x8005DE84 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_803C9E18[];
extern s32 lbl_80300DFC;
void CObject_AddRefLink(void *, void *);
void fn_800242B8(void *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8005DDF4(s32 arg0, CStruct *arg1) {
    s32 temp_r0;
    s32 temp_r29;
    void *temp_r31;

    temp_r0 = *((s32 *)((char *)lbl_80300DFC + (arg0 * 4)));
    if (temp_r0 != -1) {
        temp_r31 = *(s32 *)((char *)(temp_r0 * 4) + (s32)lbl_803C9E18);
        temp_r29 = temp_r31 + 0x18;
        fn_800242B8(temp_r31);
        if ((s32) ((CScript *)temp_r31)->unk0x18 != 0) {
            CObject_RemoveRefLink(*(s32 *)((char *)temp_r29), temp_r29);
            ((CScript *)temp_r31)->unk0x18 = 0;
        }
        ((CScript *)temp_r31)->unk0x18 = arg1;
        if (arg1 != 0) {
            CObject_AddRefLink(arg1, temp_r29);
        }
    }
}

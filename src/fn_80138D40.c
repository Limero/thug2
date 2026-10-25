// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80138D40-0x80138DB0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8029F280[];
extern char lbl_8029F2C0[];
void fn_8013B76C(void);
void fn_8013B4FC(Unk_C7387A53 *);
void *Mem_NewZero(s32);
void *fn_80009B04(Unk_5EF41E38 *, s32);
void *fn_80138D40(Unk_0DAF5178 *arg0) {
    CScript *temp_r29;
    s32 vt;

    fn_8013B76C();
    arg0->unk0x2300 = (s32)lbl_8029F280;
    temp_r29 = Mem_NewZero(0x24);
    vt = (s32)fn_8013B4FC;
    fn_80009B04((Unk_5EF41E38 *)temp_r29, -0x7D0);
    temp_r29->unk0x1C = vt;
    temp_r29->unk0x20 = (s32)arg0;
    temp_r29->unk0x18 = (s32)lbl_8029F2C0;
    arg0->unk0x1838 = (s32)temp_r29;
    return arg0;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E504-0x8007E5EC (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *Mem_Alloc(s32);
void *fn_800147E8(void *, void *);
s32 fn_80014904(void *, s32, s32, void *);
s32 fn_80014898(s32 arg0);
s32 fn_8007E4B0();
extern char lbl_802961D4[];
#include "structs.h"
s32 fn_8026A07C(s32, s32, s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_8007E504(Unk_FFAD6788 *arg0, Unk_C8FEE62D *arg1) {
    u32 sp8;
    void *handle;
    s32 temp_r3_2;
    s32 var_r3;

    handle = fn_800147E8(arg1, (void *)lbl_802961D4);
    fn_80014904(&sp8, 4, 1, handle);
    if (sp8 > 1U) {
        fn_80014904((char *)arg0 + 0xB0, 4, 1, handle);
    }
    fn_80014904((char *)arg0 + 0xC4, 4, 1, handle);
    temp_r3_2 = arg0->unk0xC4;
    if (temp_r3_2 != 0) {
        arg0->unk0xC0 = (s32)Mem_Alloc(temp_r3_2 * 0xC);
        fn_80014904((void *)arg0->unk0xC0, (s32)(arg0->unk0xC4 * 0xC), 1, handle);
        fn_8026A07C(arg0->unk0xC0, arg0->unk0xC4, 0xC, (s32)fn_8007E4B0);
    }
    fn_80014898((s32)handle);
    var_r3 = 1;
    if ((s32)arg0->unk0xC4 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}

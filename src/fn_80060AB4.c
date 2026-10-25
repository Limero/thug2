// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060AB4-0x80060B74 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80293EE4;
extern s32 fn_80052248(void *, void *, void *, void *, f32 *);

typedef struct {
    void *sp8;
    s32 pad0;
    void *sp10;
    s32 pad1;
    f32 sp18;
    char pad2[8];
} FR_60AB4;

f32 fn_80060AB4(CStruct *arg0, void *arg1, Unk_9994C3F5 *arg2, Unk_DB0E2BAB *arg3) {
    FR_60AB4 fr;
    f32 temp_f31;
    s32 temp_r0;
    CStruct *temp_r9;
    void *c;
    void *h;
    s32 n;
    s32 field;

    temp_r9 = arg0->unk0x10;
    fr.sp8 = temp_r9;
    temp_r0 = (temp_r9 != 0) ? temp_r9->unk0x4 : 0;
    fr.sp10 = (void *)temp_r0;
    if (temp_r0 != (s32)temp_r9) {
        temp_f31 = lbl_80293EE4;
        do {
            field = *(s32 *)((char *)(*(s32 *)((char *)*(volatile void **)&fr.sp10 + 0)) + 0x14);
            if (field != 0) {
                fr.sp18 = temp_f31;
                if (fn_80052248(field, arg1, arg2, arg3, &fr.sp18) != 0) {
                    return fr.sp18;
                }
            }
            c = *(volatile void **)&fr.sp10;
            h = *(volatile void **)&fr.sp8;
            n = *(s32 *)((char *)c + 4);
            fr.sp10 = (void *)n;
        } while (n != (s32)h);
    }
    return lbl_80293EE4;
}

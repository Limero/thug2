// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EDC58-0x801EDD7C (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 fn_80107B20(Unk_E9DCA07D * arg0, s32 arg1, void * arg2);
extern void fn_801ED890(Unk_EA529D06 * arg0, Unk_EA529D06 * arg1);
extern void fn_80107A80(Unk_C5652918 * arg0, s16 arg1, s16 arg2);
extern void fn_800B6578(Unk_9D191493 * arg0, Unk_2DB370CA * arg1, s32 arg2, f32 arg3);
extern void CObject_RemoveRefLink(CStruct * arg0, CStruct * arg1);
extern f32 lbl_802ADAC8;
extern f32 lbl_802ADACC;
void fn_801EDC58(Unk_C7387A53 *arg0, Unk_130D31C8 *arg1) {
    s32 sp8[0x30];
    s32 temp_r30;

    temp_r30 = fn_80107B20(arg1, 0, 0);
    fn_801ED890((char *)sp8, arg1);
    fn_80107A80((char *)sp8, 0, 0x20);
    ((Unk_F6393DBC *)sp8)->unk0x4 += lbl_802ADAC8;
    if (temp_r30 != 0) {
        ((Unk_4106303F *)sp8)->unk0x10 = arg1->unk0x88;
        ((Unk_4106303F *)sp8)->unk0x18 = arg1->unk0x90;
        ((Unk_F6393DBC *)sp8)->unk0x14 -= lbl_802ADACC;
    } else {
        __ps_t *base = (__ps_t *)(char *)sp8;
        __asm__("" : "+r"(base));
        ((Unk_4106303F *)sp8)->unk0x18 = base[1];
        ((Unk_4106303F *)sp8)->unk0x10 = ((Unk_4106303F *)sp8)->unk0x0;
    }
    if (fn_80107B20((char *)sp8, 0, 0) != 0) {
        fn_800B6578(arg0->unk0x28, (char *)sp8, 1, lbl_802ADACC);
    } else if (temp_r30 != 0) {
        fn_800B6578(arg0->unk0x28, arg1, 1, lbl_802ADACC);
    }
    {
        s32 v;
        char *p;
        if ((v = ((Unk_4106303F *)sp8)->unk0xA8, p = (char *)sp8 + 0xA8, v != 0)) {
            CObject_RemoveRefLink((void *)v, p);
            *(s32 *)p = 0;
        }
    }
}

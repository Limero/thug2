// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F7A4-0x8009F84C (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800A20B8(s32, s32);
void fn_8009E0B0(void *, s32);
extern char lbl_80297C08[];
extern s32 lbl_80301A38;

typedef struct VT_2EF06E12 {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} VT_2EF06E12;

void fn_8009F7A4(Unk_6A70655D *arg0, s32 arg1) {
    void *temp_r31;
    VT_2EF06E12 *temp_r9;

    arg0->unk0x8 = (s32)lbl_80297C08;
    arg0->unk0x114 = (s32) (arg0->unk0x114 | 0x80);
    if (arg0->unk0x110 != NULL) {
        do {
            temp_r31 = arg0->unk0x110;
            arg0->unk0x110 = ((Unk_C8FEE62D *)temp_r31)->unk0x10;
            fn_800A20B8(lbl_80301A38, temp_r31);
            if (temp_r31 != NULL) {
                temp_r9 = *(VT_2EF06E12 **)((char *)temp_r31 + 0x18);
                ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)temp_r31 + temp_r9->unk0x8, 3);
            }
        } while (arg0->unk0x110 != NULL);
    }
    fn_8009E0B0(arg0, arg1);
}

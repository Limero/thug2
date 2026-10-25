// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC5BC-0x800CC698 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80299548[];
extern char lbl_80294B28[];

/* want: lwz r9,0x14(r11) ; lha r3,8(r9) ; add r3,r11,r3 -> the +0x14 record
   has an s16 at +8 (same shape as fn_800CB68C's CbVt). */
typedef struct CcVt {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} CcVt;

void fn_8009F558(void *, s32);

void fn_800CC5BC(CScript *arg0c, s32 arg1) {
    Unk_C8FEE62D *temp_r10;
    Unk_C8FEE62D *temp_r9;
    void *var_r11;
    void *var_r31;
    s32 f;

    temp_r10 = (Unk_C8FEE62D *)((char *)arg0c + 0x1C);
    arg0c->unk0x18 = (s32)lbl_80299548;
    temp_r9 = (Unk_C8FEE62D *)temp_r10->unk0xC;
    f = temp_r9->unk0x4;
    var_r11 = temp_r9;
    if (f == -1) {
        var_r11 = NULL;
    }
    if (var_r11 != NULL) {
        do {
            temp_r9 = (Unk_C8FEE62D *)((Unk_C8FEE62D *)var_r11)->unk0xC;
            f = temp_r9->unk0x4;
            var_r31 = temp_r9;
            if (f == -1) {
                var_r31 = NULL;
            }
            if (var_r11 != NULL) {
                temp_r9 = (Unk_C8FEE62D *)((Unk_C8FEE62D *)var_r11)->unk0x14;
                ((void (*)(void *, s32))temp_r9->unk0xC)((char *)var_r11 + ((CcVt *)temp_r9)->unk0x8, 3);
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
    {
        Unk_C8FEE62D *t = (Unk_C8FEE62D *)((char *)arg0c + 0x1C);
        t->unk0x14 = (s32)lbl_80294B28;
        *(s32 *)(*(s32 *)((char *)((char *)t) + 0x10) + 0xC) = t->unk0xC;
        *(s32 *)(*(s32 *)((char *)((char *)t) + 0xC) + 0x10) = t->unk0x10;
        t->unk0xC = (s32)t;
        t->unk0x10 = (s32)t;
    }
    fn_8009F558(arg0c, arg1);
}

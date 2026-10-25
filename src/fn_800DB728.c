// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DB728-0x800DB79C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char _pad00[0x4];
    s32 unk4;
    char _pad08[0x10];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} DB728_t;

extern char lbl_80299E18[];
extern s32 lbl_80303148;
void *Mem_NewZero(s32);
void *fn_80009B04(void *, s32);
void fn_8000A578(void *, void *);
void fn_800DB79C(void);

void *fn_800DB728(DB728_t *arg0) {
    DB728_t *temp_r30;
    s32 ctor_v;

    temp_r30 = Mem_NewZero(0x24);
    ctor_v = (s32)fn_800DB79C;
    fn_80009B04(temp_r30, -0x44C);
    temp_r30->unk1C = ctor_v;
    temp_r30->unk18 = (s32)lbl_80299E18;
    temp_r30->unk20 = (s32)arg0;
    arg0->unk4 = (s32)temp_r30;
    fn_8000A578((void *)(lbl_80303148 + 8), (void *)temp_r30);
    return arg0;
}

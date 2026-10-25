// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E359C-0x800E3628 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef void (*VtblCall)(void *, s32);
typedef struct {
    char pad_0[8];
    s16 off_8;
    VtblCall fn_0xC;
} Vtbl_800E359C;
typedef struct {
    char pad_0[8];
    Vtbl_800E359C *vt_8;
} Link_800E359C;
s32 fn_8009F558(s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern char lbl_8029A7B0[];
void fn_800E359C(CScript *arg0, s32 arg1) {
    void *temp_r11;
    Vtbl_800E359C *temp_r9;
    char *link;

    temp_r11 = arg0->unk0x1C;
    link = (char *)arg0 + 0x1C;
    arg0->unk0x18 = (s32)lbl_8029A7B0;
    if (temp_r11 != NULL) {
        temp_r9 = ((Link_800E359C *)temp_r11)->vt_8;
        temp_r9->fn_0xC((char *)temp_r11 + temp_r9->off_8, 3);
    }
    if (arg0->unk0x1C != NULL) {
        CObject_RemoveRefLink(arg0->unk0x1C, link);
        arg0->unk0x1C = NULL;
    }
    fn_8009F558(arg0, arg1);
}

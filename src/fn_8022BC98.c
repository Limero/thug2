// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022BC98-0x8022BD0C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80303148[];
s32 fn_8022BD1C(void *arg0);
void fn_8000A578(void *arg0, s32 arg1);
void fn_80009C00(s32 arg0);

typedef struct {
    char pad0[0xEC];
    s32 unk0xEC;
    char pad1[0xF4];
    s32 unk0x1E4;
    s32 unk0x1E8;
} O22BC98;

void fn_8022BC98(O22BC98 *arg0, s32 arg1) {
    arg0->unk0x1E4 = arg1;
    switch (arg1) {
    case 1:
        fn_8000A578((void *)(*(s32 *)lbl_80303148 + 8), arg0->unk0xEC);
        fn_8022BC98(arg0, fn_8022BD1C(arg0));
        break;
    case 2:
        fn_80009C00(arg0->unk0xEC);
        break;
    }
}

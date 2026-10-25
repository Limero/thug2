// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F190-0x8009F204 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
void fn_80032088(s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_8012ED98(void);
void fn_8009F190(Unk_C8FEE62D *arg0) {
    s32 temp;
    if (arg0->unk0x14 == 0) {
        fn_8000F2F8((s32)*(void **)&lbl_802FFE98, *(s32 *)((char *)*(void **)&lbl_802FFE98 + 0x12C));
        fn_80032088(0xF8);
        temp = fn_8012ED98();
        arg0->unk0x14 = temp;
        fn_8012F260(temp, QB_EMPTY_SCRIPT, 0, (s32)arg0);
        fn_8000F320((s32)*(void **)&lbl_802FFE98);
    }
}

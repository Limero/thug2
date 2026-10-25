// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001033C-0x80010394 (88B). Byte-identical.
#include "types.h"
#include "structs.h"

struct Foo {
    char pad[0x11C];
    s32 f;
};
extern struct Foo *lbl_802FFE98;
extern char lbl_803C9314[];
void fn_80009A04(s32, s32);
void *fn_8000EE70(void);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8001033C(void) {
    void *temp_r3;
    s32 field;

    if (lbl_802FFE98 == NULL) {
        fn_80009A04(0x60C, (s32)lbl_803C9314);
        temp_r3 = fn_8000EE70();
        lbl_802FFE98 = temp_r3;
        field = ((struct Foo *)temp_r3)->f;
        fn_8000F2F8(temp_r3, field);
    }
}

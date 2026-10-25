// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136708-0x801367D8 (208B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
extern s32 lbl_80303434;
s32 DVDReadAsyncPrio(s32, s32, s32, s32, s32, s32);
void fn_801365EC(void);
bool fn_80136708(s32 arg0) {
    u32 temp_r0;
    Unk_2CEAE3B4 *p1;
    char *p2;
    char *arr;

    p1 = lbl_8039D940;
    if (p1->unk0xAC == 0) {
        goto ret0;
    }
    if (p1->unk0xB4 != 0) {
        goto ret0;
    }
    lbl_80303434 = 10;
    if (arg0 == 0) {
        temp_r0 = p1->unk0x9C;
        if (temp_r0 <= 9U) {
            lbl_80303434 = temp_r0;
        }
    }
    if (lbl_80303434 != 0) {
        p2 = lbl_8039D940;
        arr = p2 + 0xEC;
        if (DVDReadAsyncPrio((s32)(p2 + 8), *(s32 *)(arr + (((Unk_74BF3C95 *)p2)->unk0xE4 << 4)), ((Unk_74BF3C95 *)p2)->unk0xD0, ((Unk_74BF3C95 *)p2)->unk0xCC, (s32)fn_801365EC, 2) < 0) {
            ((Unk_74BF3C95 *)p2)->unk0xB0 = 1;
            return false;
        }
    }
    return true;
ret0:
    return false;
}

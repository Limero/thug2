// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BF60-0x8005C038 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802936A4[];
extern char lbl_802936A8[];
s32 fn_8005BE6C(void *);
void fn_8005BF60(void *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    char sp8[0x200];
    sprintf(&sp8, (s32)lbl_802936A4, arg1);
    if (arg2 != 0) {
        if (arg1[0] == 0x2E && arg1[1] == 0x2E && arg1[2] == 0x2F) {
            sprintf(&sp8, (s32)lbl_802936A4, arg1 + 3);
        } else {
            sprintf(&sp8, (s32)lbl_802936A8, arg1);
        }
    }
    *(s32 *)((char *)arg0 + (s32)0x0) = fn_8005BE6C(&sp8);
    {
        void *id = *(void **)((char *)arg0 + (s32)0x8);
        ((s32 (*)(void *, void *, void *, void *))*(s32 *)((char *)id + (s32)0x14))(arg0 + *(s16 *)((char *)id + (s32)0x10), &sp8, arg2, arg3);
    }
}

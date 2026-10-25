// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C88C-0x8024C970 (228B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B1B14[];
s32 fn_80250E24(CStruct *, s32);
void fn_80250E6C(CStruct *, s32);
s32 fn_80250EAC(CStruct *, s32);

u32 fn_8024C88C(Unk_C7387A53 *arg0, s32 arg1) {
    u32 cnt;
    s32 id;
    s32 i;
    u32 w;

    if (arg1 != 0) {
        cnt = 11;
        id = fn_80250E24(arg0->unk0x44, 11);
        for (i = 8; i != 0; i--) {
            if (id == 1) {
                fn_80250E6C(arg0->unk0x44, cnt);
                return cnt + 1;
            }
            id = (s32)((u32)id >> 1U);
            cnt--;
        }
        w = *(u32 *)(lbl_802B1B14 + (id << 2));
        fn_80250E6C(arg0->unk0x44, w >> 0x11U);
        return w & 0x1FFFFU;
    } else {
        cnt = 12;
        id = fn_80250E24(arg0->unk0x44, 12);
        for (i = 10; i != 0; i--) {
            if (id == 1) {
                fn_80250E6C(arg0->unk0x44, cnt);
                return cnt;
            }
            id = (s32)((u32)id >> 1U);
            cnt--;
        }
        return 3 - fn_80250EAC(arg0->unk0x44, 2);
    }
}

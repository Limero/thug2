// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80099A64-0x80099AE4 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80098F84(s32, void *, u32, Unk_C8FEE62D *);
void fn_80099A64(Unk_13E912CF *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 i;

    if ((arg3 != 0) && (arg1 != 0)) {
        i = 0;
        while (i < (s32) *(u16 *)((char *)arg0 + 0x5E)) {
            fn_80098F84(arg1, arg2, arg3,
                        *(Unk_C8FEE62D **)((char *)arg0->unk0x58 + i * 4));
            i += 1;
        }
    }
}

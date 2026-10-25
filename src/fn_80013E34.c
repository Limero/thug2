// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013E34-0x80013F8C (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802909AC[];

s32 fn_800147E8(s32 arg0, s32 arg1);
s32 fn_80014904(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_80014988(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80014898(s32 arg0);
void *Mem_Alloc_3(s32 arg0);

bool fn_80013E34(Unk_0469A169 *arg0, s32 arg1) {
    s32 sp8[2];
    s32 *p18;
    register s32 *a18 __asm__("r3");
    void *x;
    void **q29;
    s32 *q31;
    s32 handle;
    s32 count;
    s32 off;
    register s32 n __asm__("r9");
    char *o29;
    char *o31;
    s32 addr;
    register s32 i __asm__("r30");

    handle = fn_800147E8(arg1, (s32)lbl_802909AC);
    if (handle != 0) {
        if (fn_80014904(sp8, 1, 8, handle) == 8) {
            arg0->unk0x10 = sp8[1];
            a18 = (s32 *)((char *)arg0 + 0x18);
            p18 = a18;
            if (fn_80014904(a18, 1, sp8[1] * 0x10, handle) == (n = arg0->unk0x10) * 0x10) {
                i = n - 1;
                if (i >= 0) {
                    o29 = (char *)(i * 4 + 0x1C38);
                    o31 = (char *)(i * 0x10 + 0x1C);
                    q29 = (void **)(o29 + (s32)arg0);
                    q31 = (s32 *)(o31 + (s32)arg0);
                    do {
                        s32 t = *q31;
                        q31 -= 4;
                        *q29 = Mem_Alloc_3(t);
                        i--;
                        q29 -= 1;
                    } while (i >= 0);
                }
                count = 0;
                if (count < arg0->unk0x10) {
                    q29 = (void **)((char *)arg0 + 0x1C38);
                    q31 = (s32 *)((char *)arg0 + 0x1C);
                    off = 0;
                    do {
                        addr = off + (s32)p18;
                        i = *q31;
                        fn_80014988(handle, *(s32 *)addr, 0);
                        q31 += 4;
                        x = *q29;
                        q29 += 1;
                        if (fn_80014904(x, 1, i, handle) != i) {
                            goto fail;
                        }
                        count++;
                        off += 0x10;
                    } while (count < arg0->unk0x10);
                }
                fn_80014898(handle);
                arg0->unk0x2340 = 1;
                return true;
            }
        }
fail:
        fn_80014898(handle);
    }
    return false;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A8328-0x800A8410 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc2(s32);
s32 Mem_Alloc(s32);
void fn_8000F2F8(Unk_9994C3F5 *, void *);
void fn_8000F320(Unk_F12C5E01 *);
void *fn_800A7C88(void *);
void fn_800A7C9C(void *, s32);
extern char lbl_802FFE98[];
void fn_800A8328(CStruct *arg0, s32 arg1, s32 arg2, CStruct *arg3) {
    s32 count;
    s32 i;
    s32 offset;
    void *buf;
    void *walker;
    Unk_9994C3F5 *pool;

    pool = *(void **)&lbl_802FFE98;
    arg0->unk0xC = arg1;
    fn_8000F2F8(pool, pool->unk0x11C);

    count = arg0->unk0xC;
    i = count - 1;
    buf = Mem_Alloc((count * 8) + 8) + 8;
    *(s32 *)((char *)buf - 8) = count;
    walker = buf;
    if (count != 0) {
        do {
            fn_800A7C88(walker);
            walker += 8;
        } while (--i != -1);
    }

    i = 0;
    arg0->unk0x0 = buf;
    if (i < arg0->unk0xC) {
        offset = 0;
        do {
            i += 1;
            fn_800A7C9C(arg0->unk0x0 + offset, arg2);
            offset += 8;
        } while (i < arg0->unk0xC);
    }

    fn_800A7C9C(arg0->unk0x4 = fn_800A7C88(Mem_Alloc2(8)), arg3);
    fn_8000F320(*(s32 *)&lbl_802FFE98);
}

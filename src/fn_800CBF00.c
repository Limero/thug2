// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBF00-0x800CBFB4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char pad0x0[0xC]; void *unk0xC; void *unk0x10; void *unk0x14; char pad0x18[0x18]; s32 unk0x30; } R_CBF00;
typedef struct { char pad0x0[0xC]; void *unk0xC; } A_CBF00;
typedef struct { char pad0x0[0x18]; s16 unk0x18; char pad0x1A[0x2]; void *unk0x1C; } V_CBF00;
s32 fn_800CBEC0(void *, s32);
void *Mem_NewZero(s32);
void *fn_8002DF68(void *, void *, void *, s32);
void *fn_800CBF00(A_CBF00 *arg0, s32 arg1, s32 arg2) {
    void *alloc;
    R_CBF00 *res;
    V_CBF00 *vt;
    s16 off;
    void *fn;
    register A_CBF00 *node __asm__("r9");
    fn_800CBEC0(arg0, arg1);
    alloc = Mem_NewZero(0x84);
    res = fn_8002DF68(alloc, arg0->unk0xC, arg0, 0);
    res->unk0x30 = arg1;
    vt = res->unk0x14;
    off = vt->unk0x18;
    fn = vt->unk0x1C;
    ((void (*)(void *))fn)((char *)res + off);
    if (arg2 != 0) {
        node = (A_CBF00 *)((char *)arg0 + 0x2C);
        res->unk0x10 = node;
        res->unk0xC = node->unk0xC;
        *(void **)((char *)node->unk0xC + 0x10) = res;
        node->unk0xC = res;
    } else {
        node = (A_CBF00 *)((char *)arg0 + 0x2C);
        res->unk0x10 = *(void **)((char *)node + 0x10);
        res->unk0xC = node;
        *(void **)((char *)*(void **)((char *)node + 0x10) + 0xC) = res;
        *(void **)((char *)node + 0x10) = res;
    }
    return res;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CB4C-0x8002CC78 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
register s32 bzero __asm__("r11");
typedef struct T_8002CB4C {
    char pad0x00[0x04];
    s32 unk0x4;
    char pad0x08[0x04];
    s32 unk0xC;
    void *unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    void (*unk0x24)(void *);
    void *unk0x28;
    char pad0x2C[0x48];
    u8 unk0x74;
    u8 unk0x75;
    char pad0x76[0xF0];
    u16 unk0x166;
    u32 unk0x168;
} T_8002CB4C;
void fn_8002CA64(CScript *, s32);
void fn_8002CA8C(CScript *);
extern char lbl_802FFE98[];
void fn_8000F2F8(Unk_9F352E7C *, s32);
void Mem_Free2(void *);
void Mem_Free(void *);
void fn_8000F320(Unk_F12C5E01 *self);
s32 fn_80010400(s32 arg0, s32 arg1, s32 arg2);
void fn_8002CB4C(T_8002CB4C *arg0, s32 arg1) {
    s32 zero;
    s32 masked;
    s32 mgr;
    CScript *stz;
    s32 idx;
    s32 count;
    char *base;
    CScript *v;

    zero = 0;
    masked = arg0->unk0x168 & (s32)QB_UNKNOWN_0xFFF9FFFF;
    bzero = 0;
    arg0->unk0x75 = bzero;
    arg0->unk0x168 = masked;
    arg0->unk0x1C = zero;
    arg0->unk0x20 = zero;
    arg0->unk0x24 = 0;
    arg0->unk0x4 = zero;
    arg0->unk0x166 = zero;
    arg0->unk0x74 = bzero;
    arg0->unk0x18 = zero;
    arg0->unk0x14 = zero;
    if (arg0->unk0x10 != 0) {
        mgr = *(s32 *)&lbl_802FFE98;
        fn_8000F2F8((Unk_9F352E7C *)mgr, fn_80010400(mgr, QB_ANIMHEAP, 1));
        if (arg0->unk0x10 != 0) {
            Mem_Free2(arg0->unk0x10);
        }
        fn_8000F320((Unk_F12C5E01 *)*(s32 *)&lbl_802FFE98);
        arg0->unk0x10 = 0;
    }
    if (arg0->unk0x24 != 0) {
        arg0->unk0x24(arg0->unk0x28);
        arg0->unk0x24 = 0;
    }
    base = (char *)arg0 + 0x2C;
    stz = 0;
    idx = 0;
    count = 0x12;
    do {
        v = *(CScript **)((char *)(idx + (s32)base));
        if (v != 0) {
            fn_8002CA8C(v);
            v = *(CScript **)((char *)(idx + (s32)base));
            if (v != 0) {
                fn_8002CA64(v, 3);
            }
            *(CScript **)((char *)(idx + (s32)base)) = stz;
        }
        idx += 4;
        count -= 1;
    } while (count != 0);
    arg0->unk0xC = count;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}

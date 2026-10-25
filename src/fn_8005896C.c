// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005896C-0x80058A70 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005872C(void *);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
s32 Mem_Alloc(s32);
extern f32 lbl_802933B4;
extern Unk_89783F6B *lbl_802FFE98;

// the dispatch descriptor at arg0+0x50: signed-16 method offset, then fn ptr
typedef struct {
    char pad0x0[0x20];
    s16 off;
    void (*fn)(void *);
} Vt896C;

void fn_8005896C(CStruct *arg0, s32 arg1, f32 farg0, f32 farg1) {
    volatile double _dummy;
    volatile double _dummy1;
    s32 off;
    s32 cnt;
    void *base;
    void *p;
    f32 k;
    Unk_89783F6B *g;
    Vt896C *vt;

    if (arg0->unk0x4 == 0) {
        cnt = 0x5F;
        g = lbl_802FFE98;
        fn_8000F2F8(g, g->unk0x124);
        base = (void *)(Mem_Alloc(0x3C8) + 8);
        *(s32 *)((char *)base - 8) = 0x60;
        p = base;
        do {
            fn_8005872C(p);
            p += 0xA;
        } while (0 != cnt--);
        arg0->unk0x4 = (s32)base;
        fn_8000F320(lbl_802FFE98);
    }
    off = arg1 * 0xA;
    k = lbl_802933B4;
    *(s16 *)((char *)(off + (s32)arg0->unk0x4) + 4) = farg0 * k;
    *(s16 *)((char *)(off + (s32)arg0->unk0x4) + 6) = farg1 * k;
    vt = (Vt896C *)arg0->unk0x50;
    vt->fn((char *)arg0 + vt->off);
}

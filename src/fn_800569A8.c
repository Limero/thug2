// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800569A8-0x80056A6C (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x00[0x88];
    s32 unk0x88;
    char pad0x8C[0x24];
    __ps_t unk0xB0[4];
    char pad0xD0[0x4];
    s32 unk0xD4;
} Unk_Obj;

void *Mem_Alloc2(s32);
void fn_800071D4(void);
void *fn_80106428(void *);
void fn_80106608(void *, __ps_t *);

bool fn_800569A8(Unk_Obj *arg0, __ps_t *arg1) {
    s32 i;
    s32 j;
    void *p;
    __ps_t *row;
    __ps_t *q;

    if (arg0->unk0x88 == 0) {
        return false;
    }
    arg0->unk0xB0[0] = arg1[0];
    arg0->unk0xB0[1] = arg1[1];
    arg0->unk0xB0[2] = arg1[2];
    arg0->unk0xB0[3] = arg1[3];
    p = Mem_Alloc2(0x4B30);
    fn_800071D4();
    row = (__ps_t *)((char *)p + 0x30);
    for (i = 0x13; i != -1; i--) {
        q = row;
        j = 0x13;
        do {
            fn_80106428(q);
            q = (__ps_t *)((char *)q + 0x30);
        } while (0 != j--);
        row = (__ps_t *)((char *)row + 0x3C0);
    }
    arg0->unk0xD4 = (s32)p;
    fn_80106608(p, arg0->unk0xB0);
    return true;
}

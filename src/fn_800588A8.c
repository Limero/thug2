// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800588A8-0x8005896C (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* Exactly 0xA bytes: the lazy table's element.  MUST be a local typedef --
 * the corpus-merged Unk_2BAD2BE8 is 0x1A bytes and would scale index/addi
 * wrongly (this is the M6.89d-note case: the merged class loses the vote). */
typedef struct { u16 f0; u16 f2; u16 f4; u16 f6; u16 f8; } Elem;

/* Dispatch record: 0x20 is a SIGNED 16-bit offset (want `lha`), 0x24 the
 * method.  CStruct's merged unk0x20 is s32 and emits the wrong load. */
typedef struct { char pad0x0[0x20]; s16 off; void (*fn)(void *); } Vtbl;

typedef struct {
    s32 unk0x0;
    Elem *unk0x4;            /* 0x60-entry table, allocated lazily */
    char pad0x8[0x48];
    Vtbl *unk0x50;
} Obj;

/* Pointee of the .data pointer lbl_802FFE98; only +0x124 is read here. */
typedef struct { char pad0x0[0x124]; s32 unk0x124; } G;

void fn_8000F2F8(void *, s32);
void *Mem_Alloc(s32);
void fn_8005872C(void *);
void fn_8000F320(void *);
extern G *lbl_802FFE98;

void fn_800588A8(Obj *arg0, s32 arg1, u16 arg2, u16 arg3) {
    Vtbl *t;
    Elem *p;
    Elem *q;
    void *g;
    s32 n;

    if (arg0->unk0x4 == NULL) {
        g = lbl_802FFE98;
        fn_8000F2F8(g, lbl_802FFE98->unk0x124);
        q = (Elem *)((char *)Mem_Alloc(0x3C8) + 8);
        *(s32 *)((char *)q - 8) = 0x60;
        p = q;
        n = 0x5F;
        do {
            fn_8005872C(p);
            p = (Elem *)((char *)p + 0xA);
        } while (0 != n--);
        arg0->unk0x4 = q;
        fn_8000F320(lbl_802FFE98);
    }
    arg0->unk0x4[arg1].f0 = arg2;
    arg0->unk0x4[arg1].f2 = arg3;
    t = arg0->unk0x50;
    t->fn((char *)arg0 + t->off);
}

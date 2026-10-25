// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D0C74-0x801D0EF8 (644B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

/* file-local layout, copied from the promoted byte-identical zone-mate
   src/fn_801D1380.c (same object family, same +0x15A8/+0x15BC fields).
   The corpus-merged Unk_* classes type 0x15A8 as a pad and 0x15BC as s32. */
typedef struct {
    char pad0x0[0xC];
    void *unk0xC;
    char pad0x10[0x88];
    s32 unk0x98;
    s32 unk0x9C;
    char pad0xA0[0x1508];
    void *unk0x15A8;
    char pad0x15AC[0x10];
    void *unk0x15BC;
    void *unk0x15C0;
} Rec_801D0C74;

extern s32 lbl_80303150;
extern s32 lbl_80305F9C;
extern const f32 lbl_802AD3B8;
extern const f32 lbl_802AD3BC;
extern const f32 lbl_802AD3C0;

s32 Tmr_GetTime(void);
s32 fn_8009CF2C(s32);
void CObject_RemoveRefLink(void *, void *);
void Mem_Free(void *);
void fn_801D1458(s32, s32);

void fn_801D0C74(Rec_801D0C74 *arg0) {

    char *o;
    char *o2;
    f32 *sub;
    f32 *b2;
    f32 *b3;
    s32 *node;
    s32 *n2;
    s32 count;

    s32 zero;
    register s32 zt __asm__("r10");
    s32 m2;
    register s32 temp_r10 __asm__("r10");
    void *mm;
    void *mm2;
    void *p;
    s32 v1;
    register s32 *n3 __asm__("r9");
    f32 f31v;
    f32 f30v;
    f32 f12v;
    f32 f13v;
    f32 fld;

    if (fn_8009CF2C(lbl_80305F9C) == 0) {
        o = (char *)arg0->unk0xC;
        *(__ps_t *)(o + 0x68) = *(__ps_t *)(o + 0x58);
        *(__ps_t *)(o + 0x70) = *(__ps_t *)(o + 0x60);
        o2 = (char *)arg0->unk0xC;
        *(__ps_t *)((char *)arg0 + 0xA0) = *(__ps_t *)(o2 + 0x58);
        *(__ps_t *)((char *)arg0 + 0xA8) = *(__ps_t *)(o2 + 0x60);
    }

    f31v = lbl_802AD3B8;
    sub = (f32 *)((char *)arg0 + 0x298);
    f30v = lbl_802AD3BC;
    count = 0x17;
    sub[0] = f31v;
    sub[1] = f31v;
    sub[2] = f31v;
    sub[3] = f30v;

    arg0->unk0x98 = (s32)lbl_80303150 + Tmr_GetTime();
    m2 = *(volatile s32 *)&arg0->unk0xC;
    b2 = (f32 *)m2;
    b2[0x2E] = f31v;
    b3 = b2 + 0x2E;
    b3[1] = f31v;
    b3[2] = f31v;
    b3[3] = f30v;
    fn_801D1458((s32)arg0, 0);

    arg0->unk0x9C = 0;
    do {
        node = (s32 *)((s32)(count * 0xC) + (s32)arg0->unk0x15BC);
        node = (s32 *)((char *)node + 0x24);
        if (node[1] != 1) {
            node[1] = 1;
            node[2] = (s32)lbl_80303150 + Tmr_GetTime();
        }
        if (count == 7) {
            *(s32 *)((char *)arg0->unk0x15A8 + 0x24) = 1;
        }
        node = (s32 *)((s32)(count * 0xC) + (s32)arg0->unk0x15BC);
        node = (s32 *)((char *)node + 0x24);
        zero = 0;
        if (node[1] != zero) {
            node[1] = zero;
            node[2] = (s32)lbl_80303150 + Tmr_GetTime();
        }
        if (count == 7) {
            *(s32 *)((char *)arg0->unk0x15A8 + 0x24) = zero;
        }
    } while (0 != count--);

    mm = arg0->unk0xC;
    n2 = (s32 *)((char *)arg0->unk0x15BC + 0x30);
    temp_r10 = *(s32 *)((char *)mm + 0x120) ^ 1;
    if (n2[1] != temp_r10) {
        n2[1] = temp_r10;
        n2[2] = (s32)lbl_80303150 + Tmr_GetTime();
    }

    mm2 = arg0->unk0x15C0;
    p = *(void **)((char *)mm2 + 0x1C);
    if (p != NULL) {
        v1 = *(s32 *)p;
        *(s32 *)((char *)mm2 + 0x70) = v1;
        if (*(s32 *)p != 0) {
            CObject_RemoveRefLink(*(s32 *)p, p);
            *(s32 *)p = zero;
        }
        Mem_Free(p);
        *(void **)((char *)mm2 + 0x1C) = (void *)zero;
        *(s32 *)((char *)mm2 + 0x74) = (s32)lbl_80303150 + Tmr_GetTime();
    }

    b2 = (f32 *)((char *)arg0 + 0x170);
    zt = 0;
    *(s8 *)((char *)b2 + 0x75) = zt;
    f12v = lbl_802AD3B8;
    n3 = (s32 *)arg0->unk0x15BC;
    *(s32 *)((char *)arg0 + 0x374) = 1;
    *(f32 *)((char *)arg0 + 0x304) = f12v;
    *(s32 *)((char *)arg0 + 0x3F0) = zt;
    *(s32 *)((char *)arg0 + 0x418) = zt;
    *(s32 *)((char *)arg0 + 0x41C) = zt;
    *(s32 *)((char *)arg0 + 0x3D8) = zt;
    *(s32 *)((char *)arg0 + 0x3DC) = zt;
    *(s32 *)((char *)arg0 + 0x370) = zt;
    n3[0x58] = zt;
    f13v = lbl_802AD3C0;
    fld = *(f32 *)((char *)arg0 + 0x3B8);
    *(s32 *)((char *)arg0 + 0x25C) = zt;
    if (fld != f13v) {
        *(f32 *)((char *)arg0 + 0x3B8) = f12v;
    }
    *(f32 *)((char *)arg0 + 0x42C) = lbl_802AD3BC;
    *(s32 *)((char *)arg0 + 0x560) = zt;
    *(s32 *)((char *)arg0 + 0x564) = zt;
    *(s32 *)((char *)arg0 + 0x56C) = zt;
    *(f32 *)((char *)arg0 + 0x384) = f12v;
    *(s32 *)((char *)arg0 + 0x568) = zt;
}

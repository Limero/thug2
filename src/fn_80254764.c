// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80254764-0x802548F8 (404B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern void fn_80253D10(Unk_C7387A53 * arg0);
extern void fn_80257CC4(void *arg0, s32 arg1);
extern s32 fn_80257E48(CStruct * arg0, s32 arg1);
extern s32 fn_80253C60(Unk_C7387A53 * arg0, s32 arg1);
extern void *lbl_803CA358[];

s32 fn_80254764(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    Unk_C7387A53 *mgr;
    Unk_C8FEE62D *obj;
    CStruct *p24;
    void *tbl26;
    CStruct *bs;
    register s32 tmpp __asm__("r11");
    s32 *t120;
    s32 *t220;
    s32 v;
    s32 v4;
    s32 vt;
    s32 v2;
    s32 val;
    s32 eptr;
    register Unk_C7387A53 *e2 __asm__("r9");
    s32 w0;
    s32 w1;
    s32 i;
    s32 wk;
    s32 w;
    s32 x;
    s32 y;
    Unk_9994C3F5 *z;
    s32 anc;
    s32 i2;
    s32 x4;

    mgr = *((void * *)&arg0->unk0x2C);
    bs = (s32 *)((char *)arg0 + 4);
    obj = *(void **)mgr;
    p24 = *((void * *)&mgr->unk0x50);
    tbl26 = *((void * *)&obj->unk0x1C);
    fn_80253D10(arg0);
    w0 = arg1->unk0x0;
    w1 = arg1->unk0x4;
    fn_80257CC4(bs, 0x14);
    bs->unk0xC = w0;
    bs->unk0x8 = w0;
    bs->unk0x10 = w1;
    if (fn_80257E48(bs, 1) != 0) {
        return -0x87;
    }
    v = fn_80257E48(bs, p24->unk0x10);
    if (v == -1) {
        return -0x88;
    }
    arg0->unk0x28 = v;
    __asm__ volatile("" ::: "memory");
    vt = v * 4;
    __asm__ volatile("" ::: "memory");
    tmpp = (s32)((char *)tbl26 + 0x20);
    __asm__ volatile("mr %0,%1" : "=r"(v4) : "r"(vt));
    eptr = *(s32 *)((char *)tmpp + vt);
    __asm__ volatile("mr %0,%1" : "=r"(p24) : "r"(tmpp));
    val = *(s32 *)eptr;
    arg0->unk0x1C = val;
    if (val == 0) {
        arg0->unk0x18 = 0;
        arg0->unk0x20 = 0;
    } else {
        arg0->unk0x18 = fn_80257E48(bs, 1);
        v2 = fn_80257E48(bs, 1);
        arg0->unk0x20 = v2;
        if (v2 == -1) {
            return -0x88;
        }
    }
    t220 = (s32 *)((char *)tbl26 + 0x220);
    t120 = (s32 *)((char *)tbl26 + 0x120);
    i2 = arg0->unk0x1C * 4;
    arg0->unk0x24 = *(s32 *)((char *)tbl26 + i2);
    arg0->unk0x0 = fn_80253C60(arg0, (obj->unk0x4) * 4);
    i = 0;
    if (i < obj->unk0x4) {
        wk = 0;
        do {
            *(s32 *)(char *)(wk + arg0->unk0x0) =
                fn_80253C60(arg0, (arg0->unk0x24) * 4);
            wk += 4;
            i++;
        } while (i < obj->unk0x4);
    }
    e2 = *(s32 *)((char *)p24 + v4);
    __asm__ volatile("lis %0,%1@ha" : "=r"(anc) : "s"((char *)lbl_803CA358));
    __asm__ volatile("addi %0,%0,%1@l" : "+r"(anc) : "s"((char *)lbl_803CA358));
    {
        register void *a3 __asm__("r3");
        register s32 wv __asm__("r0");
        __asm__ volatile("mr %0,%2\n\tlwz %1,0xc(%3)"
                         : "=r"(a3), "=r"(wv)
                         : "r"(arg0), "r"(e2));
        x = ((s32 *)t120)[wv];
        y = ((s32 *)t220)[wv];
        x4 = x * 4;
        z = *(s32 *)((char *)anc + x4);
        return ((s32 (*)(void *, s32))z->unk0x8)(a3, y);
    }
}

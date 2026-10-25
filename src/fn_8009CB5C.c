// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CB5C-0x8009CCF8 (412B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802978A8[];

/* Stack walker instance.  Layout taken from the class descriptor that this
   method's own family uses: the descriptor pointer sits at +8 (see the
   promoted dtor src/fn_8009CEC4.c, `arg0->unk0x8 = lbl_802978A8`) and the
   current-list cursor at +4.  Declared deliberately short so that ngccc keeps
   the frame address in a register (see header note B). */
void fn_8009CB5C(void *arg0) {
    s32 sp8[2];
    double _pad;
    void *mgr;
    void *base;
    register void *node __asm__("r11");
    register void *sel __asm__("r9");
    void *next_node;
    void *cur;
    void *vt;
    s32 state;
    s32 f8;
    register s32 one __asm__("r0");

    *(s32 *)((char *)&sp8 + 8) = (s32)lbl_802978A8;
    *(s32 *)((char *)&sp8 + 4) = 0;
    mgr = *(s32 *)((char *)arg0 + (s32)0x20);
    if (*(s32 *)((char *)mgr + (s32)0x20) == 0) {
        *(s32 *)((char *)&sp8 + 8) = (s32)lbl_802978A8;
        return;
    }
    *(s32 *)((char *)mgr + (s32)0x20) = 0;
    base = mgr + 8;
    *(s32 *)((char *)&sp8 + 4) = (s32)base;
    node = *(s32 *)((char *)base + (s32)0xC);
    if (*(s32 *)((char *)node + (s32)0x4) == -1) {
        node = 0;
    }
    *(s32 *)((char *)&sp8 + 4) = (s32)node;
    if (node != 0) {
        sel = *(s32 *)((char *)node + (s32)0x4);
    } else {
        __asm__("" : "+r"(node));
        sel = 0;
    }
    next_node = sel;
    if (next_node != 0) {
        do {
            cur = next_node;
            node = *(s32 *)((char *)*(s32 *)((char *)&sp8 + 4) + (s32)0xC);
            if (*(s32 *)((char *)node + (s32)0x4) == -1) {
                node = 0;
            }
            *(s32 *)((char *)&sp8 + 4) = (s32)node;
            next_node = node != 0 ? *(s32 *)((char *)node + (s32)0x4) : 0;
            state = *(s32 *)((char *)cur + (s32)0x4);
            switch (state) {
            case 0:
                f8 = *(s32 *)((char *)cur + (s32)0x8);
                if (f8 == 1 || f8 == 3) {
                    vt = *(s32 *)((char *)cur + (s32)0x14);
                    ((void (*)(void *))*(s32 *)((char *)vt + (s32)0x14))(
                        (char *)cur + *(s16 *)((char *)vt + (s32)0x10));
                    *(s32 *)((char *)cur + (s32)0x8) = state;
                    __asm__("li %0,1" : "=r"(one));
                    *(s32 *)((char *)cur + (s32)0x4) = one;
                }
                break;
            case 1:
                f8 = *(s32 *)((char *)cur + (s32)0x8);
                if (f8 == 2) {
                    vt = *(s32 *)((char *)cur + (s32)0x14);
                    ((void (*)(void *))*(s32 *)((char *)vt + (s32)0x1C))(
                        (char *)cur + *(s16 *)((char *)vt + (s32)0x18));
                    *(s32 *)((char *)cur + (s32)0x4) = 0;
                    *(s32 *)((char *)cur + (s32)0x8) = 0;
                } else if (f8 == 3) {
                    vt = *(s32 *)((char *)cur + (s32)0x14);
                    ((void (*)(void *))*(s32 *)((char *)vt + (s32)0x1C))(
                        (char *)cur + *(s16 *)((char *)vt + (s32)0x18));
                    vt = *(s32 *)((char *)cur + (s32)0x14);
                    ((void (*)(void *))*(s32 *)((char *)vt + (s32)0x14))(
                        (char *)cur + *(s16 *)((char *)vt + (s32)0x10));
                    *(s32 *)((char *)cur + (s32)0x8) = 0;
                }
                break;
            }
        } while (next_node != 0);
    }
    *(s32 *)((char *)&sp8 + 8) = (s32)lbl_802978A8;
    __asm__("" : : "m"(_pad));
}

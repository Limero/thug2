// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8354-0x801A8520 (460B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-cse-follow-jumps
#include "types.h"
#include "structs.h"
extern char lbl_802AB9B0[];
extern char lbl_802AB9E0[];
extern char lbl_802ABA10[];
void Mem_Free(void *);
void fn_801A8354(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_C7387A53 *h;
    Unk_C8FEE62D *list;
    CStruct *cur;
    CStruct *nxt;
    void *nn;
    Unk_C7387A53 *prv;
    void *obj;
    Unk_F5317C5D *vt;
    u32 count;
    u32 i;
    u32 j;
    u32 ti;
    register void *wp __asm__("r9");

    arg0->unk0x14 = (s32)lbl_802AB9B0;
    count = 0;
    h = (char *)arg0 + 0x48;
    wp = *((void * *)&h->unk0xC);
    if (((CStruct *)wp)->unk0x4 == -1) {
        wp = NULL;
    }
    __asm__("" : "+r"(h));
    list = h;
    count_loop:
    if (wp != NULL) {
        wp = *((void * *)&((CStruct *)wp)->unk0xC);
        count += 1;
        if (((CStruct *)wp)->unk0x4 == -1) {
            wp = NULL;
        }
        goto count_loop;
    }
    i = 0;
    for (; i < count; i = ti) {
        wp = *((void * *)&list->unk0xC);
        j = 0;
        if (((CStruct *)wp)->unk0x4 == -1) {
            wp = NULL;
        }
        ti = i + 1;
        mid_loop:
        if (wp != NULL) {
            if (j-- == 0) {
                goto fjl;
            }
            wp = *((void * *)&((CStruct *)wp)->unk0xC);
            if (((CStruct *)wp)->unk0x4 == -1) {
                wp = NULL;
            }
            goto mid_loop;
        } else {
            __asm__("li %0, 0" : "=r"(wp));
        }
        fjl:
        {
            register void *gobj __asm__("r11");
            register Unk_F5317C5D *vt9 __asm__("r9");

            gobj = *((void * *)&((CStruct *)wp)->unk0x4);
            __asm__("" : : "r"(wp));
            if (gobj != NULL) {
                vt9 = ((Unk_C8FEE62D *)gobj)->unk0x14;
                ((s32 (*)(void *, s32))(vt9->unk0xC))((void *)((char *)gobj + (s32)vt9->unk0x8), 3);
            }
        }
    }
endph2:
    wp = *((void * *)&list->unk0xC);
    vt = ((CStruct *)wp)->unk0x4;
    __asm__("" : : "r"(vt), "r"(wp));
    cur = wp;
    if (vt == -1) {
        cur = NULL;
    }
    if (vt == -1) {
        cur = NULL;
    }
    while (cur != NULL) {
        register void *gnn __asm__("r8");

        nxt = *((void * *)&cur->unk0xC);
        gnn = nxt;
        if (nxt->unk0x4 == -1) {
            gnn = NULL;
        }
        prv = *((void * *)&cur->unk0x10);
        prv->unk0xC = nxt;
        *(s32 *)(*((void * *)&cur->unk0xC) + (s32)0x10) = *((void * *)&cur->unk0x10);
        cur->unk0xC = cur;
        cur->unk0x10 = cur;
        cur = gnn;
    }
tail:
    list->unk0x14 = (s32)lbl_802ABA10;
    *(s32 *)(*((void * *)&list->unk0x10) + (s32)0xC) = *((void * *)&list->unk0xC);
    *(s32 *)(*((void * *)&list->unk0xC) + (s32)0x10) = *((void * *)&list->unk0x10);
    list->unk0xC = list;
    list->unk0x10 = list;
    arg0->unk0x14 = (s32)lbl_802AB9E0;
    *(s32 *)(*((void * *)&arg0->unk0x10) + (s32)0xC) = *((void * *)&arg0->unk0xC);
    *(s32 *)(*((void * *)&arg0->unk0xC) + (s32)0x10) = *((void * *)&arg0->unk0x10);
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}

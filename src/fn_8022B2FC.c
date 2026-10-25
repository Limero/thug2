// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B2FC-0x8022B484 (392B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802B03E0[];
extern s32 fn_80219668(void *arg0);
extern void fn_8021B4C0(void *arg0);

struct LS { s32 pad; volatile s32 iter; void *hc; };

typedef struct { char pad0[0x8]; s16 off; char pad1[0x2]; void (*fn)(void *, s32); } VT;
typedef struct { char pad0[0x4]; char *next; char pad1[0xC]; VT *vtbl; } ND;

void fn_8022B2FC(void *arg0) {
    struct LS ls;
    struct LS *p;
    struct LS *q;
    register s32 cursor __asm__("r10");
    char *t178;
    register s32 n __asm__("r11");
    Unk_E266FB50_2 *itv;
    char *nxt;
    register s32 n9 __asm__("r9");
    ND *node;
    VT *vt;

    {
        register s32 ha __asm__("r11");
        ha = (s32)&lbl_802B03E0;
        p = &ls;
        cursor = (s32)((char *)arg0 + 0x190);
        p->hc = (void *)ha;
    }
    p->iter = cursor;
    __asm__ __volatile__("mr %0,%1" : "=r"(q) : "r"(p));
    n = (s32)((Unk_E266FB50_2 *)(void *)cursor)->unk0xC;
    if (((CStruct *)(void *)n)->unk0x4 == -1) {
        n = 0;
    }
    q->iter = n;
    if (n == 0) {
        __asm__ __volatile__("li %0,0" : "=r"(n));
    } else {
        n = (s32)((Unk_E266FB50_2 *)(void *)n)->unk0x4;
    }
    cursor = n;
    if (cursor != 0) {
        do {
            itv = (Unk_E266FB50_2 *)(void *)q->iter;
            n = (s32)itv->unk0xC;
            if (((CStruct *)(void *)n)->unk0x4 == -1) {
                n = 0;
            }
            q->iter = n;
            nxt = (n != 0) ? ((Unk_E266FB50_2 *)(void *)n)->unk0x4 : (char *)0;
            if (cursor != 0) {
                node = (ND *)(void *)cursor;
                vt = node->vtbl;
                vt->fn((char *)cursor + vt->off, 3);
            }
            cursor = (s32)nxt;
        } while (cursor != 0);
    }
    t178 = (char *)arg0 + 0x178;
    n9 = (s32)((Unk_E266FB50_2 *)(void *)t178)->unk0xC;
    q->iter = (s32)t178;
    if (((CStruct *)(void *)n9)->unk0x4 == -1) {
        n = 0;
    } else {
        n = n9;
    }
    q->iter = n;
    n9 = (n != 0) ? (s32)((Unk_E266FB50_2 *)(void *)n)->unk0x4 : 0;
    cursor = n9;
    if (cursor != 0) {
        do {
            itv = (Unk_E266FB50_2 *)(void *)q->iter;
            n = (s32)itv->unk0xC;
            if (((CStruct *)(void *)n)->unk0x4 == -1) {
                n = 0;
            }
            q->iter = n;
            nxt = (n != 0) ? ((Unk_E266FB50_2 *)(void *)n)->unk0x4 : (char *)0;
            if (cursor != 0) {
                node = (ND *)(void *)cursor;
                vt = node->vtbl;
                vt->fn((char *)cursor + vt->off, 3);
            }
            cursor = (s32)nxt;
        } while (cursor != 0);
    }
    if (fn_80219668(arg0) != 0) {
        fn_8021B4C0(arg0);
    }
    q->hc = &lbl_802B03E0;
}

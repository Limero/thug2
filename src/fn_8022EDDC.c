// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022EDDC-0x8022EF68 (396B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void memset(void *, s32, s32);
extern void *fn_80240C80(void *);
extern s32 fn_801FC0E0(void);
extern s32 fn_801FB358(Unk_C7387A53 *);

void fn_8022EDDC(Unk_9994C3F5 *arg0, Unk_DB0E2BAB *arg1) {
    s32 f;
    char *w;
    s32 temp_r0;
    s32 temp_r9;
    s32 var_r9;
    s32 i;
    s32 n;
    s32 h;
    Unk_9994C3F5 *p;
    Unk_C8FEE62D *t;
    s32 *wp;

    memset(arg1, 0, 0x18);
    p = *((void * *)&arg0->unk0x8);
    if (p != NULL) {
        do {
            t = fn_80240C80(p);
            f = t->unk0x4;
            if (!(f & 0x20)) {
                if (!(f & 0x80)) {
                    (arg1->unk0x0)++;
                }
            }
            f = t->unk0x4;
            if (!(f & 4)) {
                if (!(f & 0x100)) {
                    arg1->unk0x4 += *(s32 *)((char *)(t->unk0x14) + (s32)0x28);
                    arg1->unk0x8 += *(s32 *)((char *)(t->unk0x14) + (s32)0x2C);
                }
            }
            p = *((void * *)&p->unk0x8);
        } while (p != NULL);
    }
    arg1->unk0x4 += fn_801FB358(fn_801FC0E0());
    (arg1->unk0x0)++;
    w = (char *)arg0;
    for (i = 0; i < 0x12; i++) {
        if (((Unk_FFAD6788 *)w)->unk0xBC != 0) {
            (arg1->unk0x0)++;
        }
        if (((Unk_FFAD6788 *)w)->unk0xBC == 1) {
            (arg1->unk0x0)++;
        }
        if (((Unk_FFAD6788 *)w)->unk0xBC == 3) {
            (arg1->unk0x0)++;
        }
        if ((u32)(((Unk_FFAD6788 *)w)->unk0xBC - 5) <= 3U) {
            arg1->unk0x0 += 3;
        }
        w += 0x28;
    }
    n = arg1->unk0x0;
    h = arg1->unk0x4;
    arg1->unk0x14 = h;
    arg1->unk0x10 = n + (h * 2) + 0x12C;
    arg1->unk0xC = ((n * 6) + ((h * 8) - h)) + arg1->unk0x8 + 0x4F6;
}

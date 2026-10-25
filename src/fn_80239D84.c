// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80239D84-0x80239E18 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416F8(s32);
void fn_80239E18(Unk_C8FEE62D *, Unk_1D62F22E *);
void *fn_80237A88(Unk_673C6403 *, CStruct *, s32, s32, s32);
typedef struct {
    s32 a;
    u16 b;
} __attribute__((packed)) Unk6;
void fn_80239D84(Unk_C8FEE62D *arg0, void *arg1) {
    Unk6 sp8;
    CStruct *node = arg1;
    if (node != NULL) {
        Unk6 *p8 = &sp8;
        do {
            s32 node2 = fn_802416F8(fn_802432A0(node));
            if (node->unk0x4 < 0) {
                s32 ta = ((Unk_F5317C5D *)node2)->unk0x0;
                u16 tb = ((Unk_F5317C5D *)node2)->unk0x4;
                sp8.a = ta;
                p8->b = tb;
                fn_80239E18((void *)arg0, p8);
            }
            node->unk0x8 = (s32)fn_80237A88(arg0, (void *)node2, 0, node->unk0x4, 0);
            node = *((void * *)&node->unk0xC);
        } while (node != NULL);
    }
}

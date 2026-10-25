// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3680-0x800A3778 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80297F38[];
extern char lbl_80297FA8[];
extern char lbl_802929C8[];
extern char fn_8009F484[];
extern char fn_8009F464[];
void fn_800A3778(void *, void *, s32);

void fn_800A3680(Unk_C7387A53 *arg0, s32 arg1) {
    void *node;
    Unk_4E705049 *vt;
    volatile s32 *pa;
    CStruct *qa;
    volatile s32 *pb;
    CStruct *qb;

    arg0->unk0x2C = (s32)lbl_80297F38;
    fn_800A3778(arg0, (void *)fn_8009F484, 0);
    fn_800A3778(arg0, (void *)fn_8009F464, 0);
    node = (void *)arg0->unk0x48;
    if (node != NULL) {
        vt = *(Unk_4E705049 **)((char *)node + 0x18);
        ((s32 (*)(void *, s32))vt->unk0x1C)(node + vt->unk0x18, 3);
    }
    pa = (volatile s32 *)((char *)arg0 + 0x30);
    qa = (CStruct *)pa;
    pa[5] = (s32)lbl_802929C8;
    *(s32 *)(qa->unk0x10 + 0xC) = qa->unk0xC;
    *(s32 *)(qa->unk0xC + 0x10) = qa->unk0x10;
    pa[4] = (s32)pa;
    pa[3] = (s32)pa;
    arg0->unk0x2C = (s32)lbl_80297FA8;
    pb = (volatile s32 *)((char *)arg0 + 4);
    qb = (CStruct *)pb;
    pb[5] = (s32)lbl_802929C8;
    *(s32 *)(qb->unk0x10 + 0xC) = qb->unk0xC;
    *(s32 *)(qb->unk0xC + 0x10) = qb->unk0x10;
    pb[4] = (s32)pb;
    pb[3] = (s32)pb;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}

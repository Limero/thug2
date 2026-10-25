// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009EBC-0x80009F64 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80009EBC(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    CStruct *r10;
    CStruct *r11;
    CStruct *r9;
    CStruct *r8;
    s32 v;
    s32 u;
    s32 key;
    r8 = (CStruct *)((char *)arg0 + 8);
    arg0->unk0x4 = arg0->unk0x4 + 1;
    r10 = (CStruct *)arg1->unk0x8;
    key = r10->unk0x8;
    r11 = r8;
    for (;;) {
        r9 = (CStruct *)r11->unk0xC;
        v = r9->unk0x4;
        r11 = r9;
        if (v == -1) {
            r11 = NULL;
        }
        if (r11 == NULL) {
            break;
        }
        if ((s32)r11->unk0x8 <= key) {
            u = r11->unk0x10;
            r10->unk0xC = (s32)r11;
            r10->unk0x10 = u;
            ((CStruct *)r11->unk0x10)->unk0xC = (s32)r10;
            r11->unk0x10 = (s32)r10;
            goto done;
        }
    }
    u = r8->unk0x10;
    r10->unk0xC = (s32)r8;
    r10->unk0x10 = u;
    ((CStruct *)r8->unk0x10)->unk0xC = (s32)r10;
    r8->unk0x10 = (s32)r10;
done:
    arg1->unk0xC = (s32)arg0;
    arg1->unk0x10 = arg0->unk0x20 - 1;
    arg0->unk0x24 = 1;
    arg0->unk0x4 = arg0->unk0x4 - 1;
}

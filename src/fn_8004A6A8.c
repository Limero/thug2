// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004A6A8-0x8004A800 (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A3C50(Unk_DB0E2BAB *, s32);
void CObject_RemoveRefLink(s32, void *);
void Mem_Free(void *);
extern char lbl_80292960[];
extern char lbl_80292980[];
extern char lbl_802929C8[];
extern char lbl_80297FA8[];
void fn_8004A6A8(Unk_C7387A53 *arg0, s32 arg1) {
    s32 a0;
    s32 z1;
    s32 z2;
    s32 v;
    char *w1;
    char *w2;
    char *q58;
    char *q4c;
    char *q30;
    Unk_C8FEE62D *tail;

    a0 = (s32)arg0;
    arg0->unk0x48 = (s32)lbl_80292960;
    arg0->unk0x2C = (s32)lbl_80292980;
    if ((char *)a0 + 0x5C8 != NULL) {
        w1 = (char *)a0 + 0x6B8;
        if ((char *)a0 + 0x5C8 != w1) {
            z1 = 0;
            do {
                w1 -= 0x18;
                v = *(s32 *)w1;
                if (v != 0) {
                    CObject_RemoveRefLink(v, (void *)w1);
                    *(s32 *)w1 = z1;
                }
            } while ((char *)a0 + 0x5C8 != w1);
        }
    }
    q58 = (char *)a0 + 0x58;
    q4c = (char *)a0 + 0x4C;
    q30 = (char *)a0 + 0x30;
    tail = (Unk_C8FEE62D *)((char *)a0 + 4);
    if ((char *)a0 + 0x64 != NULL) {
        w2 = (char *)a0 + 0x5A4;
        if ((char *)a0 + 0x64 != w2) {
            z2 = 0;
            do {
                w2 -= 0x1C;
                v = *(s32 *)w2;
                if (v != 0) {
                    CObject_RemoveRefLink(v, (void *)w2);
                    *(s32 *)w2 = z2;
                }
            } while ((char *)a0 + 0x64 != w2);
        }
    }
    if (arg0->unk0x58 != 0) {
        CObject_RemoveRefLink(arg0->unk0x58, (void *)q58);
        arg0->unk0x58 = 0;
    }
    if (arg0->unk0x4C != 0) {
        CObject_RemoveRefLink(arg0->unk0x4C, (void *)q4c);
        arg0->unk0x4C = 0;
    }
    fn_800A3C50((Unk_DB0E2BAB *)q30, 0);
    arg0->unk0x2C = (s32)lbl_80297FA8;
    tail->unk0x14 = (s32)lbl_802929C8;
    *(s32 *)(*(s32 *)((char *)tail + 0x10) + 0xC) = tail->unk0xC;
    *(s32 *)(*(s32 *)((char *)tail + 0xC) + 0x10) = tail->unk0x10;
    tail->unk0xC = (s32)tail;
    tail->unk0x10 = (s32)tail;
    if (arg1 & 1) {
        Mem_Free((void *)a0);
    }
}

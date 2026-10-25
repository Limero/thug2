// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015EE0-0x80016094 (436B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80314640[];
void *Mem_NewZero(s32);
Unk_C8FEE62D *fn_8001621C(void *, s32, s32);
s32 CARDOpen(s32, char *, s32 *);
s32 CARDCreate(s32, char *, s32, s32 *);

/* vtable: s16 method offset at +8, fn ptr at +C (lha + lwz + mtlr/blrl), arg 3 */
typedef struct {
    char pad0x0[8];
    s16 off8;
    char padA[2];
    void *(*fnC)(void *, s32);
} Vt_15EE0;

void *fn_80015EE0(Unk_C8FEE62D *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    Unk_C8FEE62D *obj;
    Vt_15EE0 *vt;
    s32 i;
    register s32 c __asm__("r9");
    s32 v;
    s32 t;
    s32 res;

    obj = fn_8001621C(Mem_NewZero(0x84), 0, arg0);
    i = 0;
    c = arg1[0];
    lbl_80314640[0] = arg1[0];
    if (c != 0) {
        do {
            if (lbl_80314640[i] != '/' && lbl_80314640[i] != '\\' &&
                lbl_80314640[i] != '.') {
                i++;
            }
            c = *++arg1;
            *(lbl_80314640 + i) = arg1[0];
        } while (c != 0);
    }
    if (arg2 & 4) {
        v = arg0->unk0x8;
        t = arg3 - 1;
        arg3 = (t + v) & -v;
    }
    switch (arg2) {
    case 6:
        res = CARDOpen(arg0->unk0x18, lbl_80314640, &obj->unk0x50);
        if (res == -4) {
            res = CARDCreate(arg0->unk0x18, lbl_80314640, arg3, &obj->unk0x50);
        }
        break;
    case 4:
        res = CARDCreate(arg0->unk0x18, lbl_80314640, arg3, &obj->unk0x50);
        break;
    case 3:
        res = CARDOpen(arg0->unk0x18, lbl_80314640, &obj->unk0x50);
        break;
    case 1:
        res = CARDOpen(arg0->unk0x18, lbl_80314640, &obj->unk0x50);
        break;
    case 2:
        res = CARDOpen(arg0->unk0x18, lbl_80314640, &obj->unk0x50);
        break;
    default:
        res = -0x80;
        break;
    }
    if (res == -9) {
        arg0->unk0x1C = 2;
    }
    if (res == 0) {
        obj->unk0x64 = obj->unk0x54;
        return obj;
    }
    if (obj != 0) {
        vt = (Vt_15EE0 *)obj->unk0x14;
        vt->fnC((char *)obj + vt->off8, 3);
    }
    return 0;
}

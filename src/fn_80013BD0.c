// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013BD0-0x80013C40 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80290888[];
extern char lbl_802908B0[];
void fn_8009C838(void);
void *Mem_NewZero(s32);
void fn_80009B04(void *, s32);
void *fn_80013D00(void);
void *fn_80013BD0(Unk_C8FEE62D *arg0) {
    CScript *tmp;
    s32 fp;
    fn_8009C838();
    arg0->unk0x14 = (s32)lbl_80290888;
    tmp = Mem_NewZero(0x24);
    fp = (s32)fn_80013D00;
    fn_80009B04(tmp, 0);
    tmp->unk0x1C = fp;
    tmp->unk0x20 = (s32)arg0;
    tmp->unk0x18 = (s32)lbl_802908B0;
    arg0->unk0x18 = (s32)tmp;
    return arg0;
}

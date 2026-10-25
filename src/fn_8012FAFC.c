// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012FAFC-0x8012FBCC (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x20];
    s16 unk0x20;
    s32 unk0x24;
} Rec1_8012FAFC;
typedef struct {
    char pad0x0[0x68];
    s16 unk0x68;
    s32 unk0x6C;
} Rec2_8012FAFC;
void *GetChecksum_3(void *, s32);
s32 fn_8012FAFC(CStruct *arg0, s32 arg1, char *arg2, s32 arg3) {
    s32 type;
    Rec1_8012FAFC *rec;
    Rec2_8012FAFC *rec2;
    void *obj;
    s32 res;
    type = arg0->unk0x4;
    if (type == QB_OBJECT) {
        rec = *(Rec1_8012FAFC **)(arg2 + 8);
        res = ((s32 (*)(void *, void *, void *, void *))rec->unk0x24)(arg2 + rec->unk0x20, arg0, (void *)arg1, (void *)arg3);
    } else if (type == QB_COMPOSITEOBJECT) {
        rec = *(Rec1_8012FAFC **)(arg2 + 8);
        res = ((s32 (*)(void *, void *, void *, void *))rec->unk0x24)(arg2 + rec->unk0x20, arg0, (void *)arg1, (void *)arg3);
    } else {
        obj = GetChecksum_3(arg2, type);
        rec2 = *(Rec2_8012FAFC **)((char *)obj + 0x18);
        res = ((s32 (*)(void *, void *, void *, void *))rec2->unk0x6C)((char *)obj + rec2->unk0x68, arg0, (void *)arg1, (void *)arg3);
    }
    return res != 0;
}

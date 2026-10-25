// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005742C-0x80057470 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005742C(Unk_9D99273B *arg0) {
    Unk_DB0E2BAB *temp_r9;
    Unk_C8FEE62D *(*temp_r9_2)(char *);

    temp_r9 = (Unk_DB0E2BAB *)arg0->unk0x284;
    temp_r9_2 = (Unk_C8FEE62D * (*)(char *))temp_r9->unk0x44;
    temp_r9 = (Unk_DB0E2BAB *)temp_r9_2((char *)arg0 + (s32)temp_r9->unk0x40);
    ((Unk_C8FEE62D *)temp_r9)->unk0x10 = 0;
    ((Unk_C8FEE62D *)temp_r9)->unk0x14 = 0;
}

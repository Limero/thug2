// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001867C-0x800186CC (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S3_1867C;

extern char lbl_8031E7E0[];
extern char lbl_8031E788[];
void OSSleepThread(s32);
void dequeue(S3_1867C *, s32);

void fn_8001867C(void) {
    S3_1867C dst;
    S3_1867C src;

    while (1) {
        OSSleepThread((s32)lbl_8031E7E0);
        dequeue(&src, (s32)lbl_8031E788);
        dst = src;
    }
}

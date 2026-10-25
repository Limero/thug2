// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F60C-0x8009F644 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x60];
    s16 unk0x60;
    char pad0x62[0x2];
    s32 unk0x64;
} Unk_f60c_vt;
void fn_8009F60C(CScript *arg0, s32 *arg1) {
    s32 (*temp_r9_2)(char *, s32);
    Unk_f60c_vt *temp_r9;

    temp_r9 = (Unk_f60c_vt *)arg0->unk0x18;
    temp_r9_2 = (s32 (*)(char *, s32))temp_r9->unk0x64;
    temp_r9_2((char *)arg0 + temp_r9->unk0x60, *arg1);
}

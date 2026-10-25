// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023CE8C-0x8023CEFC (112B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct { s32 w; u16 h; } unk8_t;
s32 fn_80238C40(Unk_673C6403 *, Unk_ECD1B899 *, void *);
s32 fn_8023EEF4(Unk_5A2FF52D * arg0, Unk_F96D0DC8 * arg1);
void fn_8023CE8C(Unk_E3D41763 *arg0, Unk_F5317C5D *arg1) {
    unk8_t sp8;
    s32 sp10;
    s32 temp_r3;

    sp8.w = arg1->unk0x0;
    ((Unk_638CF717 *)&sp8)->unk0x4 = (u16) arg1->unk0x4;
    temp_r3 = fn_80238C40(arg0->unk0x0, &sp8, &sp10);
    if ((temp_r3 != 0) && (fn_8023EEF4(arg0, temp_r3) != 0)) {
        arg0->unk0xC0 = 0;
    }
}

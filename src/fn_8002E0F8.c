// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002E0F8-0x8002E174 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_80031FC4(void);
extern void fn_8012F024(void *);
extern f32 lbl_8029195C;
void fn_8002E0F8(CStruct *arg0) {
    f32 temp_f0;
    fn_80031FC4();
    arg0->unk0x4C = 0;
    *(f32 *)&arg0->unk0x50 = lbl_8029195C;
    if (arg0->unk0x70 != 0) {
        arg0->unk0x70 = 0;
        if (*(s32 *)((char *)arg0->unk0x78 + 0x14) != 0) {
            fn_8012F024((void *)*(s32 *)((char *)arg0->unk0x78 + 0x14));
        }
    }
    temp_f0 = lbl_8029195C;
    arg0->unk0x5C = 0;
    *(f32 *)&arg0->unk0x74 = temp_f0;
    *(f32 *)&arg0->unk0x6C = temp_f0;
}

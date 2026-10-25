// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E43E8-0x800E4470 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x00[0x0C];
    void *unk0x0C;
    char pad0x10[0x0C];
    void *unk0x1C;
    char pad0x20[0x08];
    s32 unk0x28;
} E43E8_obj;
typedef struct {
    char pad0x00[0x38];
    s16 unk0x38;
    void (*unk0x3C)(void *);
} E43E8_vt;
extern char lbl_8030044C[];
s32 fn_80068954(s32, s32);
void CObject_RemoveRefLink(void *, void *);
bool fn_800E43E8(E43E8_obj *arg0) {
    char *temp_link;
    s32 temp_zero;
    void *temp_r3;
    E43E8_vt *temp_r9;

    temp_link = (char *)arg0 + 0x1C;
    if (arg0->unk0x1C != 0) {
        temp_zero = 0;
        fn_80068954(*(s32 *)lbl_8030044C, arg0->unk0x28);
        if (arg0->unk0x1C != 0) {
            CObject_RemoveRefLink(arg0->unk0x1C, temp_link);
            arg0->unk0x1C = (void *)temp_zero;
        }
        arg0->unk0x1C = (void *)temp_zero;
    }
    temp_r3 = arg0->unk0x0C;
    temp_r9 = *(E43E8_vt **)((char *)temp_r3 + 8);
    ((void (*)(void *))temp_r9->unk0x3C)((char *)temp_r3 + temp_r9->unk0x38);
    return true;
}

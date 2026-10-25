// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80176AE8-0x80176B78 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern s32 lbl_80305EAC;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_80174ED8(Unk_C7387A53 * arg0);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
struct unkflags { u32 bit:1; u32 val:31; };
bool ScriptResetLevel(s32 arg0, void *arg1) {
    s32 temp_r29;
    u32 var_r28;

    var_r28 = 0;
    temp_r29 = lbl_80305EAC;
    if (arg1 != 0) {
        var_r28 = ((struct unkflags *)((char *)arg1 + 0xCC))->bit;
        ((struct unkflags *)((char *)arg1 + 0xCC))->bit = 0;
    }
    fn_8000F2F8(lbl_802FFE98, ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C);
    fn_80174ED8(temp_r29);
    fn_8000F320(lbl_802FFE98);
    if (arg1 != 0) {
        ((struct unkflags *)((char *)arg1 + 0xCC))->bit = var_r28;
    }
    return true;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C450-0x8015C50C (188B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_80172E64(s32, s32, s32);
bool ScriptInitializeSkaters(CStruct *pParams, CScript *pScript) {
    register s32 walker __asm__("r9");
    register s32 head __asm__("r11");
    s32 var_r0;
    s32 entry;
    Unk_4AA2E777 *vt;
    u32 count;
    u32 i;

    i = 0U;
    for (;;) {
        count = 0U;
        head = *(s32 *)((char *)(*(s32 *)&lbl_80305EAC) + 0x38);
        __asm__("" : "+r"(head));
        var_r0 = ((CStruct *)head)->unk0x4;
        walker = head;
        while ((((var_r0 == -1) && (walker = 0)), walker) != 0) {
            walker = ((CStruct *)walker)->unk0xC;
            count += 1;
            var_r0 = ((CStruct *)walker)->unk0x4;
        }
        if (i < count) {
            entry = fn_801746A4(*(s32 *)&lbl_80305EAC, i);
            if (((Unk_9994C3F5 *)entry)->unk0xC8 != 0) {
                vt = ((Unk_9994C3F5 *)entry)->unk0x8;
                ((s32 (*)(s32))vt->unk0x7C)(
                    entry + vt->unk0x78);
            }
            fn_80172E64(*(s32 *)&lbl_80305EAC, entry, 0);
            i += 1;
            continue;
        }
        return true;
    }
}

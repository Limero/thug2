// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199860-0x8019992C (204B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_801403CC(void *arg0);
extern s32 fn_801813F0(CStruct * arg0);
bool fn_80199860(void *arg0, s32 arg1) {
    register char *base __asm__("r26");
    register s32 a1 __asm__("r27");
    register s32 head __asm__("r28");
    register s32 tb __asm__("r29");
    register s32 ta __asm__("r30");
    register u32 i __asm__("r31");
    register u32 cnt __asm__("r11");
    register s32 p __asm__("r9");

    a1 = arg1;
    head = lbl_80305EAC;
    i = 0U;
    base = (char *)head + 0x2C;
again:
    p = ((Unk_1D62F22E_2 *)base)->unk0xC;
    cnt = 0U;
    goto chk;
    do {
        p = ((CStruct *)p)->unk0xC;
        cnt += 1U;
    chk:;
        if (((CStruct *)p)->unk0x4 == -1) {
            p = 0;
        }
    } while (p != NULL);
    if (i < cnt) {
        if ((u32)i != (u32)a1) {
            ta = fn_801403CC((void *)fn_801746A4(head, a1));
            tb = fn_801403CC((void *)fn_801746A4(head, (s32)i));
            ta = fn_801813F0(ta);
            if (ta < fn_801813F0(tb)) {
                return false;
            }
        }
        i += 1U;
        goto again;
    }
    return true;
}

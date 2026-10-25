// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E4BC-0x8013E5DC (288B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 pad;
    s32 cur;
    s32 end;
} Iter8013E4BC;
extern char lbl_8029F480[];
s32 fn_8013E428(void *);
s32 fn_80137764(Unk_F386DC9F *);
s32 fn_8013733C(Unk_1624B368 *);
s32 fn_8013FC08(Unk_A99C4F7E *);
int fn_8013F764(void *);
int fn_8013F734(void *);
s32 fn_8013E034(s32, CStruct *);
s32 fn_8013E068(void *, CStruct *);
bool fn_8013E4BC(void *arg0, s32 arg1) {
    Iter8013E4BC sp;
    register char *p9 __asm__("r9");
    register char *itp __asm__("r27");
    register char *tp __asm__("r26");
    register char *lblv __asm__("r28");
    register char *ha __asm__("r11");
    register s32 a0 __asm__("r29");
    register s32 a1 __asm__("r31");
    register s32 t __asm__("r30");
    s32 z;
    s32 node;

    __asm__ volatile("lis %0,%1@ha" : "=r"(ha) : "s"(lbl_8029F480));
    p9 = (char *)&sp;
    __asm__ ("addi %0,%2,%3@l\n\tli %1,0" : "=r"(lblv), "=r"(z) : "r"(ha), "s"(lbl_8029F480));
    a0 = (s32)arg0;
    a1 = arg1;
    ((Unk_4C649A8C *)p9)->unk0x8 = lblv;
    ((Unk_4C649A8C *)p9)->unk0x4 = z;
    itp = p9;
    t = fn_8013E428((s32)arg0);
    if (((tp = (char *)a1 + 0x34FC), t >= fn_80137764(((Unk_9C44AE00 *)a0)->unk0x1830))
        || ((t = fn_8013733C(tp)), t >= fn_8013FC08(a1))) {
        ((Unk_1D62F22E_2 *)itp)->unk0x8 = lblv;
        return true;
    }
    a1 = 0;
    for (node = fn_8013E034(a0, itp); node != 0; node = fn_8013E068(a0, &sp)) {
        if (fn_8013F764(node) != 0 && fn_8013F734(node) == 0) {
            a1 += 1;
        }
    }
    if (a1 == 0) {
        a1 = 1;
    }
    t = fn_80137764(((Unk_9C44AE00 *)a0)->unk0x1830) / a1;
    if (fn_8013733C(tp) > t) {
        ((Unk_1D62F22E_2 *)itp)->unk0x8 = (s32)lbl_8029F480;
        return true;
    }
    ((Unk_1D62F22E_2 *)itp)->unk0x8 = (s32)lbl_8029F480;
    return false;
}

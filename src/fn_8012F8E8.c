// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F8E8-0x8012F948 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_801309EC(void *);
#include "structs.h"
void fn_8012F68C(s32, s32, s32, s32, s32, s32);
s32 fn_8013465C(s32);
extern char lbl_8030342C[];
void fn_8012F8E8(Unk_FFAD6788 *arg0, s32 arg1, CStruct *arg2) {
    register s32 a1 __asm__("r28");
    register s32 a2 __asm__("r30");
    register char *pg __asm__("r9");
    s32 g;
pg = (char *)&lbl_8030342C;
    a1 = arg1;
    __asm__ volatile("");
    g = *(s32 *)((char *)pg);
    __asm__ volatile("");
    a2 = (s32)arg2;
    __asm__("" : "+r"(g));
    __asm__("" : "+r"(a1));
    fn_8012F68C(arg0, a1, fn_8013465C(g), (void *)a2, arg0->unk0xBC, 1);
    fn_801309EC(arg0);
}

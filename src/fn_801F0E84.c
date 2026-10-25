// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0E84-0x801F0F48 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_801F0DC8(void *, void *, void *, void *, void *);
void * fn_8021D358(s32, s32);
#include "structs.h"
s32 fn_801D16C0(s32);
void * fn_8021B55C(void *, s32);
s32 fn_8022A9D0(void);
extern char lbl_80305F9C[];
void fn_801F0E84(CScript *arg0) {
    s32 t;
    if ((s32) arg0->unk0x20 != 0) {
        fn_801F0F58();
        arg0->unk0x20 = 0;
    }
    if ((s32) arg0->unk0x24 != 0) {
        fn_801D16C0(arg0->unk0x34);
        arg0->unk0x24 = 0;
    }
    if ((s32) arg0->unk0x28 != 0) {
        fn_8021D358(*(s32 *)&lbl_80305F9C, *(u16 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x1A));
        t = *(s32 *)fn_8021B55C((void *)*(s32 *)&lbl_80305F9C, fn_8022A9D0());
        fn_801F0DC8(arg0, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x18), arg0->unk0x1C ^ 1, t, 1);
        arg0->unk0x28 = 0;
    }
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x30) + 0x1FC) = 0;
}

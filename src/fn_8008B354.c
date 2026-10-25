// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008B354-0x8008B3E0 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: LabelObjectCtor-family ctor (6 params) — installs two rodata strings
// (unk0x20/unk0x8), resolves the CAG handle via fn_8005CF80(lbl_80366478)
// and stores ->unk0x17C; label value from fn_80081794(arg4) -> unk0x178,
// arg5 -> unk0x179. EXACT after adding the missing fn_80081794 prototype
// (its absence forced an implicit call + crclr — AGENTS.md M5.22 recipe).
#include "types.h"
#include "structs.h"
s32 fn_8005CF80(Unk_9994C3F5 *, void *);
s32 fn_80081794(s32);
extern s32 lbl_80366478;
extern char lbl_80296B18[];
extern char lbl_80296B30[];
void *fn_8008B354(Unk_3FE1622A *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 arg5) {
    Unk_C7387A53 *temp_r3;
    s32 handle;

    fn_8006712C();
    arg0->unk0x20 = (s32)lbl_80296B18;
    arg0->unk0x8 = (s32)lbl_80296B30;
    arg0->unk0x17C = 0;
    handle = lbl_80366478;
    temp_r3 = fn_8005CF80((Unk_9994C3F5 *)handle, (void *)arg3);
    if (temp_r3 != NULL) {
        arg0->unk0x17C = (s32) temp_r3->unk0xC;
    }
    *(s8 *)&arg0->unk0x178 = (s8)fn_80081794((void *)arg4);
    *(s8 *)((char *)arg0 + 0x179) = arg5;
    return arg0;
}

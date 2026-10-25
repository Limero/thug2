// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ECD84-0x801ECE7C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void fn_801D488C(void *);
extern void fn_8009F010(void *, s32, s32);
extern s32 *fn_80108F94(void *, s32);
extern s32 Tmr_GetTime(void);
extern void *Mem_Alloc2(s32);
extern void Mem_Free(void *);
extern s32 lbl_80303150;
extern void CObject_RemoveRefLink(void *, void *);

void fn_801ECD84(Unk_7579AE80 *arg0) {
    Unk_C8FEE62D *obj;
    s32 h;
    s32 one;
    register s32 ps __asm__("r30");
    register s32 bs __asm__("r9");

    h = arg0->unk0x3CC;
    if (h != 0) {
        obj = arg0->unk0x15C0;
        ps = obj->unk0x1C;
        if (ps != 0) {
            obj->unk0x70 = *(s32 *)ps;
            if (*(s32 *)ps != 0) {
                CObject_RemoveRefLink((void *)(*(s32 *)ps), (void *)ps);
                *(s32 *)ps = 0;
            }
            Mem_Free((void *)ps);
            ps = 0;
            obj->unk0x1C = ps;
            obj->unk0x74 = lbl_80303150 + Tmr_GetTime();
        }
        one = 1;
        obj->unk0x1C = (s32)fn_80108F94(Mem_Alloc2(0xB8), h);
        bs = arg0->unk0x15BC;
        ps = bs + 0xC0;
        if (*(s32 *)((char *)ps + 4) != 1) {
            *(s32 *)((char *)ps + 4) = one;
            *(s32 *)((char *)ps + 8) = lbl_80303150 + Tmr_GetTime();
        }
        arg0->unk0x280 = one;
        fn_801D488C(arg0);
        if (arg0->unk0x3CC != 0) {
            fn_8009F010((void *)arg0->unk0x3CC, QB_SKITCHON, 0);
        }
    }
}

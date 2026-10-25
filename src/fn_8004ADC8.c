// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004ADC8-0x8004AEF4 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetElement_2(void *, void *, s32, s32);
void fn_8004C110(s32, s32 *, s32, s32);
void CScreenElement_SetChildLockState(s32, s32);
void fn_8004BCCC(void *, void *, void *, void *);
s32 fn_8012F5E4(Unk_15EF4A35 *, CStruct *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

/* vtable record: s16 `this` adjustment at +0x18/+0x08, method at +0x1C/+0x0C */
typedef struct {
    char p0[8];
    s16 o1;
    char p1[2];
    void *f1;
    char p2[8];
    s16 o2;
    char p3[2];
    void *f2;
} VT4ADC8;

/* the 12-byte out record GetElement_2 fills (unk0x0/unk0x4/unk0x8) */
typedef struct { CStruct *f0; s32 f4; s32 f8; } ELEM;

void fn_8004ADC8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, Unk_15EF4A35 *arg4) {
    ELEM sp8;
    CStruct **link;

    GetElement_2(&sp8, arg0, arg1, 1);
    if (arg2 != 0) {
        fn_8004C110(arg0, &sp8, 0, 0);
        link = &sp8;
        if (sp8.f0->unk0x58 != 0) {
            CScreenElement_SetChildLockState(sp8.f0->unk0x58, 0);
        }
        fn_8004BCCC(arg0, arg3, link, arg4);
    } else {
        fn_8004C110(arg0, &sp8, 0, 0);
        if ((arg4 != 0) && (sp8.f0 != NULL)) {
            fn_8012F5E4(arg4, sp8.f0);
        }
        link = &sp8;
        {
            VT4ADC8 *vt = (VT4ADC8 *)arg0->unk0x2C;
            ((s32 (*)(void *, void *))vt->f2)((char *)arg0 + vt->o2, sp8.f0);
        }
        if (sp8.f0 != NULL) {
            {
                VT4ADC8 *vt2 = (VT4ADC8 *)sp8.f0->unk0x8;
                ((s32 (*)(void *, s32))vt2->f1)((char *)sp8.f0 + vt2->o1, 3);
            }
        }
    }
    /*
     * The tail test reads `sp8.f0` THROUGH a volatile-qualified pointer so the
     * load is not CSE-folded into the guard of the vcall block above. Want
     * reloads 8(r1) at 0x8004AEC4 and re-tests (because the intervening
     * indirect `vt2->f1` call may write it); plain `if (sp8.f0 != NULL)`
     * lets ngccc forward the earlier value, and the `beq` at 0x8004AEA4 then
     * jumps one block too far (promote_wip's br_targets REFUSE). No asm.
     */
    {
        volatile CStruct **vpp = &sp8.f0;
        if (*vpp != NULL) {
            CObject_RemoveRefLink(*vpp, link);
            *vpp = NULL;
        }
    }
}

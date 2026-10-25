// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081920-0x80081C84 (868B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *Mem_Alloc2(s32);
void fn_80087E18(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_80088824(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_80089284(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_80089D5C(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008A7A4(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008B354(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008B994(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008C2C0(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008CFD0(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008ECD8(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_8008D868(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_80087638(void *, s32, s32, s32, s32, s32, s32, f32, s32);
void fn_80081920(Unk_3FE1622A *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0, s32 arg_sp8) {
    u32 x = arg1;
    volatile double _dummy;
    if (x == QB_FLATRIBBONTAIL) goto A_8D868;
    if (x > QB_FLATRIBBONTAIL) goto T_RIGHT;
    if (x == 0x15834EEA) goto A_89284;
    if (x > 0x15834EEA) goto T_LR;
    if (x == 0x97CB7A9) goto A_8A7A4;
    if (x == 0xEE6FC5B) goto A_8B994;
    goto DEF;
T_LR:
    if (x == QB_LINE) goto A_8B354;
    if (x == QB_STAR) goto A_89D5C;
    goto DEF;
T_RIGHT:
    if (x == QB_SMOOTH) goto A_88824;
    if (x > QB_SMOOTH) goto T_RR;
    if (x == 0x3F109FCC) goto A_8CFD0;
    if (x == 0x7EC7252D) goto A_8ECD8;
    goto DEF;
T_RR:
    if (x == 0xC4D5A4CB) goto A_8C2C0;
    if (x <= 0xC4D5A4CB) goto DEF;
    if (x != QB_SHADED) goto DEF;
A_87E18:
    fn_80087E18(Mem_Alloc2(0x178), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_88824:
    fn_80088824(Mem_Alloc2(0x178), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_89284:
    fn_80089284(Mem_Alloc2(0x188), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_89D5C:
    fn_80089D5C(Mem_Alloc2(0x188), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8A7A4:
    fn_8008A7A4(Mem_Alloc2(0x188), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8B354:
    fn_8008B354(Mem_Alloc2(0x180), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8B994:
    fn_8008B994(Mem_Alloc2(0x180), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8C2C0:
    fn_8008C2C0(Mem_Alloc2(0x180), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8CFD0:
    fn_8008CFD0(Mem_Alloc2(0x180), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8ECD8:
    fn_8008ECD8(Mem_Alloc2(0x188), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
A_8D868:
    fn_8008D868(Mem_Alloc2(0x188), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
DEF:
    fn_80087638(Mem_Alloc2(0x178), arg0, arg2, arg4, arg5, arg6, arg7, farg0, arg_sp8);
    return;
}

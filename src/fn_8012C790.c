// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012C790-0x8012C8F0 (352B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000A778(void *);
s32 fn_8009F4C4(s32);
void *fn_801252BC(s32);
u8 *fn_8012D62C(u8 *, s32, void *);
u8 *fn_8012D190(u8 *, s32, void *);
void fn_80117E28(void *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80128F94(s32);
u8 *fn_8012C48C(s32, u8 *, s32);
u8 *fn_8012B7C8(s32, u8 *, s32);
void *fn_80125568(void *);
s32 fn_8003E7CC(s32);
u8 *fn_8012C790(u8 *arg0, u8 *arg1, void *arg2) {
    typedef struct {
        union { u32 unk0x0; u16 unk0x0_lo; };
        u32 unk0x4;
        u32 unk0x8;
        u32 unk0xC;
    } VarR30_t;
    VarR30_t *var_r30;
    Unk_1D62F22E *ctx;
    u16 h;
    s32 t2;
    u32 t3;
    register s32 hh __asm__("r9");
    register s32 zz __asm__("r11");

    ctx = fn_80125568(arg0);
    ctx->unk0x8 = fn_8000A778(arg2);
    switch (*arg1) {
    case 0x0E:
        var_r30 = fn_801252BC(fn_8009F4C4(0x10));
        arg1 = fn_8012D62C(arg1, 0, var_r30);
        hh = var_r30->unk0x0_lo;
        zz = 0;
        ctx->unk0x2 = (u8) (hh & 0x7F);
        t3 = var_r30->unk0x8;
        ctx->unk0xC = t3;
        var_r30->unk0x8 = zz;
        fn_80117E28(var_r30);
        break;
    case 0x16:
    case 0x17:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1E:
    case 0x1F:
        var_r30 = fn_801252BC(fn_8009F4C4(0x10));
        arg1 = fn_8012D190(arg1, 0, var_r30);
        hh = var_r30->unk0x0_lo;
        zz = 0;
        ctx->unk0x2 = (u8) (hh & 0x7F);
        t3 = var_r30->unk0x8;
        ctx->unk0xC = t3;
        var_r30->unk0x8 = zz;
        fn_80117E28(var_r30);
        break;
    case 3:
        ctx->unk0x2 = 0xA;
        t2 = CStruct_ctor(CStruct_new(8));
        ctx->unk0xC = t2;
        arg1 = fn_8012C48C(t2, arg1, 0);
        break;
    case 5:
        ctx->unk0x2 = 0xC;
        t2 = fn_80128F94(fn_8003E7CC(0xC));
        ctx->unk0xC = t2;
        arg1 = fn_8012B7C8(t2, arg1, 0);
        break;
    default:
        break;
    }
    return arg1;
}

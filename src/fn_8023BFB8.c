// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023BFB8-0x8023C0EC (308B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80125A08(s32, s32);
extern s32 fn_8012954C(CStruct *, s32);
extern s32 fn_80240B2C(void *, s32);
extern s32 fn_801293FC(CStruct *, s32);
extern void fn_80240B34(Unk_F96D0DC8 *);

extern char lbl_802B0DEC[];

void fn_8023BFB8(Unk_F0530266 *arg0) {
    u32 var_r28;
    register s32 tbl __asm__("r26");
    s32 n;
    char *base;
    void *dst;
    register s32 p __asm__("r30");
    s32 e;
    s32 zero;

    var_r28 = 4;
    tbl = fn_80125A08((s32)lbl_802B0DEC, 1);
    n = ((CStruct *)tbl)->unk0x4;
    arg0->unk0x177A0 = n;
    if (var_r28 < n + 4) {
        zero = 0;
        base = (char *)arg0 + 0x10000;
        __asm__("" : "+r"(base));
        dst = base + 0x7788;
        do {
            e = fn_8012954C(tbl, var_r28);
            var_r28 += 1;
            p = fn_80240B2C(dst, 0);
            ((Unk_6A78CE27 *)p)->unk0x0 = (u8)fn_801293FC(e, 0);
            p = fn_80240B2C(dst, 2);
            ((Unk_6A78CE27 *)p)->unk0x0 = (u8)fn_801293FC(e, 1);
            p = fn_80240B2C(dst, 3);
            ((Unk_6A78CE27 *)p)->unk0x0 = (u8)fn_801293FC(e, 2);
            p = fn_80240B2C(dst, 5);
            ((Unk_6A78CE27 *)p)->unk0x0 = (u8)fn_801293FC(e, 3);
            *(u8 *)((char *)fn_80240B2C(dst, 1) + 0) = (u8)zero;
            fn_80240B34(dst);
            dst = (char *)dst + 6;
        } while (var_r28 < (u32)((Unk_A426F181 *)base)->unk0x77A0 + 4);
    }
    arg0->unk0x177A0 = arg0->unk0x177A0 + 4;
}

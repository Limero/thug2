// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D348-0x8016D3D4 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct D348 {
    char pad0x00[4];
    s32 unk0x4;
    s32 unk0x8;
    char pad0xC[0x148];
    s32 unk0x154;
    char pad0x158[0x18C];
    s32 unk0x2E4;
} D348;

s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 Mem_Alloc2(s32);
s32 fn_80172740(s32, s32);
void fn_8016D470(D348 *);

D348 *fn_8016D348(D348 *arg0) {
    s32 var_r31;
    s32 var_r29;
    s32 var_r9;

    var_r9 = 1;
    do {
        var_r9 -= 1;
    } while (var_r9 != -1);
    var_r31 = (s32)arg0 + 0x154;
    arg0->unk0x8 = CStruct_ctor(CStruct_new(8));
    var_r29 = (s32)arg0 + 0x2E4;
    arg0->unk0x4 = fn_80172740(Mem_Alloc2(0x18), 8);
    do {
        *(s32 *)var_r31 = CStruct_ctor(CStruct_new(8));
        var_r31 += 0x190;
    } while (var_r31 <= var_r29);
    fn_8016D470(arg0);
    return arg0;
}

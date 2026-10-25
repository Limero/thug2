// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801111E4-0x801112BC (216B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80128294(CStruct *, void *, void *, s32);
void fn_8006EBE0(s32 *);
extern char lbl_8029CFB0[];
extern char lbl_8029CFB4[];
extern char lbl_8029CFB8[];
extern char lbl_8029CFBC[];
typedef struct {
    s32 color;
    s32 c0;
    s32 c1;
    s32 c2;
    s32 c3;
    u32 packed;
} FogState;
bool ScriptSetFogColor(CStruct *pParams, CScript *pScript) {
    FogState fs;
    Unk_1D62F22E *pC0;
    Unk_1D62F22E *pb;
    s32 temp_r8;
    s32 temp_r11;
    s32 temp_r0;

    pC0 = &fs.c0;
    fs.c2 = fs.c1 = fs.c0 = 0xFF;
    fs.c3 = 0x80;
    fn_80128294(pParams, (void *)lbl_8029CFB0, pC0, 0);
    fn_80128294(pParams, (void *)lbl_8029CFB4, &fs.c1, 0);
    fn_80128294(pParams, (void *)lbl_8029CFB8, &fs.c2, 0);
    fn_80128294(pParams, (void *)lbl_8029CFBC, &fs.c3, 0);
    *(u8 *)&fs.packed = pC0->unk0x3;
    pb = (u8 *)&fs.packed;
    temp_r0 = fs.c1;
    temp_r8 = fs.c2;
    temp_r11 = fs.c3;
    pb->unk0x1 = temp_r0;
    pb->unk0x2 = temp_r8;
    pb->unk0x3 = temp_r11;
    fs.color = fs.packed;
    fn_8006EBE0(&fs.color);
    return true;
}

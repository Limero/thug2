// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206C48-0x80206D2C (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AF31C;
void fn_80206E24(void);
void fn_80206E48(void *);
void fn_80206E7C(Unk_76553646 *);
void fn_8020A35C(Unk_13928190 *);
void fn_80206C48(Unk_CF8B1206 *arg0) {
    s32 *p1;
    f32 *p2;
    char *var_r9;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 z;

    arg0->unk0x1C = 0;
    arg0->unk0xA5C = 0;
    arg0->unk0xA68 = 0;
    arg0->unk0xA70 = -1;
    arg0->unk0xA74 = -1;
    fn_80206E24();
    arg0->unk0x1274 = 0;
    arg0->unk0x1278 = 0;
    fn_80206E7C(arg0);
    arg0->unk0x12A8 = 0;
    fn_8020A35C(arg0);
    arg0->unk0x12F0 = 0;
    arg0->unk0x130C = 0;
    arg0->unk0x1310 = 0;
    arg0->unk0x1314 = 0;
    arg0->unk0x1318 = 0;
    arg0->unk0x131C = 0;
    arg0->unk0x1370 = 0;
    arg0->unk0x1374 = 0;
    fn_80206E48(arg0);
    var_ctr = 3;
    var_r9 = (char *)arg0 + 0x9A8;
    do {
        *((s32 *)var_r9) = 0;
        var_r9 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
    p1 = (s32 *)((char *)arg0 + 0xA04);
    z = 0;
    p2 = (f32 *)((char *)arg0 + 0x9AC);
    for (var_ctr_2 = 0; var_ctr_2 < 0x16; var_ctr_2++) {
        p1[var_ctr_2] = z;
        p2[var_ctr_2] = lbl_802AF31C;
    }
    arg0->unk0x1378 = 0;
    arg0->unk0x1C0C = 0;
}

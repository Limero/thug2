// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4E6C-0x801F4EF4 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O2
#include "types.h"
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F53C(void *);
void fn_801F1FD4(void *);
void fn_801F6164(void *);
void fn_801F61E8(void *);
extern char lbl_802AE3B8[];
void *fn_801F4E6C(Unk_E7466DF4 *arg0) {
    u32 var_r29;
    char *var_r31;

    var_r29 = 0x31;
    var_r31 = (char *)arg0 + 0x20;
    fn_8009F53C(arg0);
    arg0->unk0x18 = (s32)lbl_802AE3B8;
    do {
        fn_801F1FD4(var_r31);
        var_r31 += 0x370;
    } while (var_r29-- != 0);
    arg0->unk0x4 = QB_GOALEDITOR;
    fn_801F6164(arg0);
    fn_801F61E8(arg0);
    arg0->unk0xAC04 = 0;
    arg0->unk0xAC08 = 0;
    return arg0;
}

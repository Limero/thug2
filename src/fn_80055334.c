// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055334-0x800553EC (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern char lbl_80293164[];
extern char lbl_80293170[];
extern char lbl_80293178[];
s32 fn_8005529C(const char *, char *);
void LowerCase(char *);
s32 sprintf(char *, const char *, ...);
char *fn_8005570C(void);
void fn_8001075C(s32);
void fn_80010760(void);
Unk_FFAD6788 *fn_80077164(const char *, CStruct *, Unk_9994C3F5 *, s32, s32);
Unk_FFAD6788 *fn_80055334(const char *arg0, CStruct *arg1, Unk_9994C3F5 *arg2, s32 arg3) {
    char sp8[0x200];
    char sp208[0x200];
    register CStruct *node __asm__("r28") = arg1;
    char *out_path = sp208;
    Unk_9994C3F5 *context = arg2;
    s32 flag = arg3;
    s32 temp_r29;
    Unk_FFAD6788 *temp_r30;
    const char *var_r30;
    const char *asset_path = sp208;
    temp_r29 = fn_8005529C(arg0, &sp8);
    LowerCase(&sp8);
    if (temp_r29 != 0) {
        var_r30 = lbl_80293170;
    } else {
        var_r30 = lbl_80293178;
    }
    sprintf(out_path, lbl_80293164, &sp8, var_r30, fn_8005570C());
    fn_8001075C(asset_path);
    temp_r30 = fn_80077164(asset_path, node, context, temp_r29, flag);
    fn_80010760();
    __asm__("" : : "r"(out_path));
    return temp_r30;
}

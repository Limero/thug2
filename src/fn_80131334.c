// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131334-0x80131474 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void Script_RunScript(void *, void *, void *, void *, void *);
void fn_8012EE64(void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012F044(s32);
extern bool lbl_803032E8;
extern bool lbl_803032EC;
extern bool lbl_8039D4D0;
s32 fn_801309EC(Unk_DB0E2BAB *arg0);
s32 fn_8012ED7C(CStruct *self);
void fn_80131234(void);
typedef struct {
    char pad0[0x40];
    s16 unk0x40;
    s32 unk0x44;
} Tbl131334;
void fn_80131334(void) {
    s32 temp_r0;
    void *temp_r11;
    Unk_FFAD6788 *temp_r3;
    Tbl131334 *temp_r9;
    Unk_FFAD6788 *var_r31;
    void *var_r3;
    lbl_803032E8 = 1;
    lbl_8039D4D0 = 0;
    var_r31 = fn_8012ED7C(NULL);
    if (var_r31 != NULL) {
        do {
            var_r3 = var_r31;
            for (;;) {
                temp_r3 = fn_8012ED7C(var_r3);
                if (temp_r3 == NULL) {
                    break;
                }
                if ((s32) temp_r3->unk0xCC < 0) {
                    break;
                }
                var_r3 = temp_r3;
            }
            temp_r0 = var_r31->unk0xCC;
            if ((temp_r0 < 0) && (!(temp_r0 & QB_UNKNOWN_0x20000000) || (fn_8012F044(var_r31) == 0)) && (!(var_r31->unk0xCC & QB_UNKNOWN_0x10000000) || (temp_r11 = var_r31->unk0xBC, ((temp_r11 == NULL) != 0)) || (temp_r9 = (Tbl131334 *)((Unk_9994C3F5 *)temp_r11)->unk0x8, ((((s32 (*)(void *))temp_r9->unk0x44)((char *)temp_r11 + temp_r9->unk0x40) == 0) == 0))) && (fn_801309EC(var_r31) == 0)) {
                if ((s32) var_r31->unk0xD8 != 0) {
                    Script_RunScript(var_r31->unk0xD8, var_r31->unk0xDC, var_r31->unk0xBC, 0, 0);
                }
                if (var_r31 != NULL) {
                    fn_8012EE64(var_r31, 3);
                }
            }
            var_r31 = temp_r3;
        } while (var_r31 != NULL);
    }
    lbl_803032E8 = 0;
    if (lbl_803032EC != 0) {
        fn_80131234();
        lbl_803032EC = 0;
    }
}

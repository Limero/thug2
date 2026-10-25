// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243374-0x802433BC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80240B58(void);
void fn_802432A0(Unk_9994C3F5 *);
void fn_80243374(void **arg0) {
    Unk_C7387A53 *var_r31;

    var_r31 = *arg0;
    if (var_r31 != NULL) {
        do {
            fn_802432A0(var_r31);
            fn_80240B58();
            var_r31 = var_r31->unk0xC;
        } while (var_r31 != NULL);
    }
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E39C-0x8011E46C (208B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8038C8C0[];
extern char lbl_8029D5F8[];
s32 fn_8011BC38(void);
s32 strlen(char *);
s32 fn_8011E39C(s32 arg0, s32 arg1) {
    char *start;
    char *ret;
    s32 len;
    s32 i;
    s32 t;

    if (fn_8011BC38() != 0) {
        *(s32 *)lbl_8038C8C0 = *(s32 *)lbl_8029D5F8;
        ((Unk_21634967 *)lbl_8038C8C0)->unk0x4 = ((Unk_21634967 *)lbl_8029D5F8)->unk0x4;
        ((Unk_21634967 *)lbl_8038C8C0)->unk0x6 = ((Unk_21634967 *)lbl_8029D5F8)->unk0x6;
        return (s32)lbl_8038C8C0;
    }
    start = (char *)(arg1 * 0xCB0 + (arg0 * 0x28 + (s32)lbl_8038C8C0));
    ret = start;
    len = strlen(start);
    i = 0;
    while (i < len) {
        if ((start[i] == '\\') || (start[i] == '/')) {
            t = i + 1;
            ret = start + t;
        }
        i = i + 1;
    }
    return (s32)ret;
}

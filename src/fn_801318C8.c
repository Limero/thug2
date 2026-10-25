// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801318C8-0x80131960 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
Unk_FFAD6788 *fn_8012ED7C(Unk_FFAD6788 *);
s32 fn_80130E34(Unk_FFAD6788 *, s32);
void fn_8012F360(Unk_FFAD6788 *);
void fn_8012F4DC(Unk_FFAD6788 *);
void fn_801318C8(CStruct *arg0, s32 arg1, Unk_FFAD6788 *arg2) {
    Unk_FFAD6788 *cur;
    Unk_FFAD6788 *next;
    s32 flags;
    cur = fn_8012ED7C(NULL);
    if (cur != NULL) {
        do {
            next = fn_8012ED7C(cur);
            flags = cur->unk0xCC;
            if (flags < 0 && cur != arg2 && fn_80130E34(cur, (s32)arg0) != 0 && (s32)cur->unk0xD4 == arg1) {
                fn_8012F360(cur);
                fn_8012F4DC(cur);
            }
            cur = next;
        } while (cur != NULL);
    }
}

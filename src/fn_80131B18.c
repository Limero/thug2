// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131B18-0x80131BAC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Node1B18 { char _pad[0xC8]; s32 unk0xC8; } Node1B18;
Node1B18 *fn_8012ED7C(Node1B18 *arg0);
s32 fn_80130E34(Node1B18 *arg0, void *arg1);
void fn_8012F360(Node1B18 *arg0);
void fn_8012F4DC(Node1B18 *arg0);
void fn_80131B18(void *arg0, s32 arg1) {
    Node1B18 *p = fn_8012ED7C(0);
    if (p != 0) {
        do {
            if (fn_80130E34(p, arg0) != 0) {
                if ((arg1 == 0) || (p->unk0xC8 == arg1)) {
                    fn_8012F360(p);
                    fn_8012F4DC(p);
                }
            }
            p = fn_8012ED7C(p);
        } while (p != 0);
    }
}

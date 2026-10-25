// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125480-0x801254E4 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
typedef struct Node { char pad0[2]; u8 unk2; char pad1[9]; void *unkC; } Node;
void *fn_8012543C(void *arg0);
void *fn_80125480(void *arg0) {
    Node *p = fn_8012543C(arg0);

    if (p != NULL) {
        if (p->unk2 == 0xD) {
            for (;;) {
                Node *c = fn_8012543C(p->unkC);

                if (c == NULL)
                    return p;
                if (c->unk2 != 0xD)
                    return c;
                p = c;
            }
        }
    }
    return p;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7D94-0x800B7E1C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80298CDC;
extern f32 lbl_803CA200[8];
extern char lbl_8037E778[];
typedef struct B7D94Node {
    CStruct *owner;
    char _4[8];
} B7D94Node;
extern void CObject_AddRefLink(CStruct *, B7D94Node *);
void fn_800B7D94(CStruct *arg0) {
    volatile double _dummy;
    char *node_base;
    f32 *base;
    f32 value;
    s32 index;
    B7D94Node *node;

    node_base = lbl_8037E778;
    base = lbl_803CA200;
    value = lbl_80298CDC;
    node = (B7D94Node *)(node_base + 0x54);
    index = 7;
    do {
        if (node->owner == 0) {
            node->owner = arg0;
            if (arg0 != 0) {
                CObject_AddRefLink(arg0, node);
            }
            base[index] = value;
            return;
        }
        node--;
        index--;
    } while (index != -1);
}

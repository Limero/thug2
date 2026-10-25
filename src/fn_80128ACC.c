// Identification: recursive script-node subtree search — returns 1 if arg1 is
// the node itself or is found among descendants reachable via unk0x4 (first
// child) / unk0xC (next sibling); descends only through nodes whose type field
// (unk0x0 & 0x7F0000) is 0xA0000. Used by fn_8012F2D8 to test whether an object
// is contained in a script-node subtree.
// Suggested rename: ScriptNode_SubtreeContains.
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128ACC-0x80128B48 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
bool fn_80128ACC(CStruct *arg0, CStruct *arg1) {
    CStruct *node;

    if (arg1 == arg0) {
        return true;
    }
    node = arg0->unk0x4;
    while (node != NULL) {
        if (((node->unk0x0 & 0x7F0000) == 0xA0000) && (fn_80128ACC(node->unk0x8, arg1) != 0)) {
            return true;
        }
        node = node->unk0xC;
    }
    return false;
}

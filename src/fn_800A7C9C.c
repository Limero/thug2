// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7C9C-0x800A7D1C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc(s32);
void fn_800A7DBC(void *arg0);
typedef struct { s32 a; s32 b; s32 c; } N12;
void fn_800A7C9C(CStruct *arg0, s32 arg1) {
    N12 *data;
    N12 *node;
    s32 i;

    data = (N12 *)((char *)Mem_Alloc((arg1 * 0xC) + 8) + 8);
    *(s32 *)((char *)data - 0x8) = arg1;
    node = data;
    i = arg1 - 1;
    if (arg1 - 1 != -1) {
        do {
            node->b = 0;
            node->c = 0;
            node->a = 0;
            node++;
        } while (--i != -1);
    }
    arg0->unk0x4 = arg1;
    arg0->unk0x0 = (s32)data;
    fn_800A7DBC(arg0);
}

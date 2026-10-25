// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127A18-0x80127AAC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 pad : 9;
    s32 type : 7;
    s32 pad2 : 16;
    s32 unk4;
    s32 unk8;
} NodeHdr;
typedef struct {
    s32 pad0;
    f32 f4;
    f32 f8;
} Node2S;
void fn_8009F4C4(s32);
s32 fn_801252BC();
void fn_80128EF4(s32);
s32 fn_80125000();
void fn_80127438(void *, void *);
void fn_80127A18(CStruct *arg0, s32 arg1, f32 farg0, f32 farg1) {
    volatile double _dummy;
    volatile double _dummy2;
    NodeHdr *node;
    Node2S *node2;
    fn_8009F4C4(0x10);
    node = (NodeHdr *)fn_801252BC();
    node->unk4 = arg1;
    node->type = 5;
    fn_80128EF4(0xC);
    node2 = (Node2S *)fn_80125000();
    node->unk8 = (s32)node2;
    node2->f4 = farg0;
    ((Node2S *)node->unk8)->f8 = farg1;
    fn_80127438(arg0, node);
}

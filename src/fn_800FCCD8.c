// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCCD8-0x800FCD88 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800FCCD8(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register void *t __asm__("r11");
    register void *p __asm__("r9");
    s32 result;
    s32 v;
    CStruct *cur;
    s32 found;
    Unk_C7387A53 *node;
    Unk_4AA2E777 *vt;
    s16 off;
    t = *((void * *)&arg0->unk0x10);
    p = *((void * *)&((Unk_C7387A53 *)t)->unk0xC);
    result = 0;
    for (; (v = ((CStruct *)p)->unk0x4, cur = p, v == -1 && (cur = NULL), cur != NULL); ) {
        found = 0;
        node = *((void * *)&cur->unk0x4);
        vt = *((void * *)&node->unk0xC);
        off = vt->unk0x78;
        if (((s32 (*)(void *, s32, s32, s32, s32))(*((void * *)&vt->unk0x7C)))(
                (char *)node + off, arg1, arg2, arg3, arg4) != 0 || result != 0) {
            found = 1;
        }
        p = *((void * *)&cur->unk0xC);
        result = found;
    }
    return result;
}
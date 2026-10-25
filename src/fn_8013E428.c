// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E428-0x8013E4BC (148B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 pad;
    s32 cur;
    s32 end;
} Iter8013E428;
extern char lbl_8029F480[];
s32 fn_8013E034(s32, CStruct *);
s32 fn_8013E068(void *, CStruct *);
int fn_8013F764(void *);
s32 fn_8013733C(Unk_1624B368 *);
s32 fn_8013E428(void *arg0) {
    Iter8013E428 sp;
    register Iter8013E428 *p __asm__("r4");
    register char *itp __asm__("r28");
    register s32 sum __asm__("r30");
    s32 node;

    p = &sp;
    itp = (char *)p;
    p->end = (s32)lbl_8029F480;
    p->cur = 0;
    sum = 0;
    for (node = fn_8013E034(arg0, p); node != 0; node = fn_8013E068(arg0, &sp)) {
        if (fn_8013F764(node)) {
            sum += fn_8013733C((char *)node + 0x34FC);
        }
    }
    ((Unk_1D62F22E_2 *)itp)->unk0x8 = (s32)lbl_8029F480;
    return sum;
}

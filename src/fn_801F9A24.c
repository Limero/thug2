// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9A24-0x801F9B20 (252B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_801FC2F4(s32);
extern void *fn_801F9540(CStruct *);
void fn_801F99D8(Unk_C7387A53 *, Unk_C4654E77 *);

void *fn_801F9A24(Unk_C7387A53 *arg0, void *arg1, f32 minX, f32 minY, f32 maxX, f32 maxY) {
    volatile double _dummy;
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    void *ret = arg1;
    s32 found = 0;
    void *saved = NULL;
    void *node = *((void * *)&arg0->unk0xC);
    f32 *p;

    if (node != NULL) {
        do {
            f32 temp_f0 = *((f32 *)&((Unk_DB0E2BAB *)node)->unk0x8);
            p = (f32 *)((char *)node + 8);
            if ((temp_f0 > minX) && (temp_f0 < maxX)) {
                f32 temp_f1 = p[2];
                if ((temp_f1 > minY) && (temp_f1 < maxY)) {
                    if (found != 0) {
                        if (saved != NULL) {
                            void *nn = fn_801F9540(fn_801FC2F4(0x14));
                            void *tmp = saved;
                            ((CStruct *)nn)->unk0x4 = ret;
                            ret = nn;
                            saved = NULL;
                            fn_801F99D8(nn, tmp);
                        }
                        fn_801F99D8(ret, node);
                    } else {
                        saved = node;
                    }
                    found = 1;
                } else {
                    saved = NULL;
                    found = 0;
                }
            } else {
                saved = NULL;
                found = 0;
            }
        } while ((node = *((void * *)&((Unk_DB0E2BAB *)node)->unk0x24)) != NULL);
    }
    return ret;
}

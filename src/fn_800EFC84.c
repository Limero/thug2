// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFC84-0x800EFD38 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc_3(s32 arg0);
void Mem_Free_3(void *arg0);
void fn_800EFC84(CStruct *arg0, s16 arg1) {
    s32 count = arg0->unk0x4;
    s16 *arr = (s16 *) arg0->unk0x8;
    s32 off;
    s32 i;
    register s32 o9 __asm__("r9");

    __asm__ ("add %0,%1,%1" : "=r"(o9) : "r"(count), "r"(arr));
    count = count + 1;
    *(s16 *) (o9 + (s32) arr) = arg1;
    arg0->unk0x4 = count;
    if (count == (count / 100) * 100) {
        void *old = arg0->unk0x8;
        void *nb = Mem_Alloc_3((count + 100) * 2);

        i = 0;
        arg0->unk0x8 = nb;
        if (i < arg0->unk0x4) {
            off = 0;
            do {
                u16 tmp = *(u16 *) (char *) (off + (s32) old);
                *(u16 *) (char *) (off + (s32) arg0->unk0x8) = tmp;
                i++;
                off += 2;
            } while (i < arg0->unk0x4);
        }
        Mem_Free_3(old);
    }
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183068-0x80183140 (216B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Mem_Alloc_3(s32);
void Mem_Free_3(s32);
void fn_80183068(CStruct *arg0, s32 arg1) {
    s32 newsize;
    s32 newarr;
    register s32 i __asm__("r11");

    if (arg0->unk0x8 <= arg0->unk0xC) {
        newsize = arg0->unk0x8 + arg0->unk0x10;
        newarr = Mem_Alloc_3(newsize * 4);
        i = 0;
        if (i < arg0->unk0x8) {
            s32 w = 0;
            do {
                *(s32 *)(w + newarr) =
                    *(s32 *)(w + arg0->unk0x4);
                w += 4;
                i += 1;
            } while (i < arg0->unk0x8);
        }
        {
            register s32 n __asm__("r11");
            s32 z;
            char *zp;

            n = arg0->unk0x8;
            if (n < newsize) {
                zp = (char *)(n * 4 + newarr);
                n = newsize - n;
                z = 0;
                do {
                    *(s32 *)zp = z;
                    zp += 4;
                } while (--n != 0);
            }
        }
        Mem_Free_3(arg0->unk0x4);
        arg0->unk0x4 = newarr;
        arg0->unk0x8 = newsize;
    }
    {
        register s32 idx __asm__("r11");
        register s32 base __asm__("r10");
        s32 cnt;

        cnt = arg0->unk0xC;
        base = arg0->unk0x4;
        idx = cnt * 4;
        *(s32 *)(idx + base) = arg1;
        __asm__("" ::: "memory");
        arg0->unk0xC = cnt + 1;
    }
}

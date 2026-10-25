// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80056660-0x800567E4 (388B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *Mem_Alloc2(s32 size);
void fn_800071D4(void);
void fn_80070244(void *);
void fn_80057C98(void *, s32);
void fn_80055EA4(void *, void *);
void fn_80057D90(void *, s32);
void fn_800583FC(void *, s32);
void fn_80058268(void *, char *);
void *fn_80055E74(void *, s32);
void *fn_8005742C(void *);
void fn_80106428(void *);
void fn_80106608(void *, void *);
void fn_8010672C(void *, s32 *, s32);
void fn_80056308(Unk_FFAD6788 *, void *, s32 *, s32 **, s32 **, void *, s32);
s32 Script_GetInteger(s32 arg0, s32 arg1);
extern s32 lbl_80300454;

s32 fn_80056660(Unk_FFAD6788 *arg0, void *arg2, s32 arg1) {
    void *grid;
    void *obj;
    s32 i;
    u32 j;
    s32 *row;
    s32 *cur;
    s32 n;
    s32 off;

    fn_80056308(arg0, arg2, &arg0->unk0x158, &arg0->unk0x15C, &arg0->unk0x160, &arg0->unk0xB0, arg1);
    if (arg0->unk0x158 > 0) {
        if (arg0->unk0x88 != 0) {
            grid = Mem_Alloc2(0x4B30);
            fn_800071D4();
            row = (s32 *)((char *)grid + 0x30);
            for (i = 0x13; i != -1; i--) {
                /* Zero-code barrier: the row pointer birth has to stay ahead
                   of the first grid write, which the scheduler hoists. */
                __asm__ volatile("" ::: "memory");
                cur = row;
                j = 0x13;
                do {
                    fn_80106428(cur);
                    cur = (s32 *)((char *)cur + 0x30);
                } while (j--);
                row = (s32 *)((char *)row + 0x3C0);
            }
            arg0->unk0xD4 = (s32)grid;
            fn_80106608(grid, &arg0->unk0xB0);
            fn_8010672C(arg0->unk0xD4, arg0->unk0x15C, arg0->unk0x158);
        }
        n = 0;
        if (n < arg0->unk0x158) {
            off = 0;
            do {
                obj = fn_80055E74(arg0, *(s32 *)(off + (s32)arg0->unk0x15C));
                if (obj == NULL) {
                    obj = fn_8005742C(arg0);
                    fn_80057C98(obj, *(s32 *)(off + (s32)arg0->unk0x15C));
                    fn_80057D90(obj, 1);
                    fn_80055EA4(arg0, obj);
                }
                fn_80058268(obj, (char *)arg0->unk0x15C + off);
                off += 0x10;
                fn_800583FC(obj, 0x40);
                n++;
            } while (n < arg0->unk0x158);
        }
    }
    if (Script_GetInteger(QB_UNKNOWN_0xBA1E4254, 0) != 0) {
        fn_80070244(lbl_80300454);
    }
    return 1;
}

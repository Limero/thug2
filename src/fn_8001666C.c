// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001666C-0x800167E4 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 *lbl_802FFE98;
extern void fn_8000F2F8(void *, void *);
extern void fn_80010D94(s32, s32);
extern s32 Mem_Alloc_3(s32);
extern void fn_80010E78(s32);
extern void fn_8000F320(void *);
extern s32 CARDRead(void *, s32, s32, s32);
s32 fn_8001666C(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 rem;
    s32 chunk;
    s32 remaining;
    register s32 a1 __asm__("r29");
    a1 = arg1;
    rem = arg0->unk0x74 % ((s32 *)arg0->unk0x80)[2];
    chunk = ((s32 *)arg0->unk0x80)[2] - rem;
    if (arg0->unk0x78 == 0) {
        fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk0x11C);
        fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
        arg0->unk0x78 = Mem_Alloc_3(((s32 *)arg0->unk0x80)[2]);
        fn_80010E78(lbl_802FFE98->unk0x11C);
        fn_8000F320(lbl_802FFE98);
        if (CARDRead((char *)arg0 + 0x50, arg0->unk0x78, ((s32 *)arg0->unk0x80)[2],
                     arg0->unk0x74 - rem) != 0) {
            return 0;
        }
    } else if (rem == 0) {
        if (CARDRead((char *)arg0 + 0x50, arg0->unk0x78, ((s32 *)arg0->unk0x80)[2],
                     arg0->unk0x74 - rem) != 0) {
            return 0;
        }
    }
    remaining = arg2;
    for (;;) {
        if (remaining < chunk) {
            if (remaining != 0) {
                memcpy(a1, arg0->unk0x78 + rem, remaining);
                arg0->unk0x74 = arg0->unk0x74 + remaining;
            }
            return arg2;
        }
        memcpy(a1, arg0->unk0x78 + rem, chunk);
        a1 = a1 + chunk;
        remaining = remaining - chunk;
        arg0->unk0x74 = arg0->unk0x74 + chunk;
        if (remaining == 0) {
            return arg2;
        }
        if (CARDRead((char *)arg0 + 0x50, arg0->unk0x78, ((s32 *)arg0->unk0x80)[2],
                     arg0->unk0x74) != 0) {
            return 0;
        }
        rem = 0;
        chunk = ((s32 *)arg0->unk0x80)[2];
    }
}

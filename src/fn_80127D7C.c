// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127D7C-0x80127E38 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* the QB node object built by fn_801252BC (byte-proven by the promoted
   src/fn_801252BC.c): word 0 is a :8/:1/:7/:16 bitfield set, so the 7-bit
   field at LSB 16..22 is `c` (want: rlwimi r0,r9,0x10,9,0xf) and the halfword
   at offset 2 is `d` (want: sth r27,2(r31)). */
typedef struct {
    u32 a : 8;
    u32 b : 1;
    u32 c : 7;
    u32 d : 16;
    s32 unk0x04;
    void *unk0x08;
    s32 unk0x0C;
} QNode;

/* allocation stack behind lbl_802FFE98; only the 0x12C "top" slot is read. */
typedef struct {
    char pad0[0x12C];
    void *top;
} AllocStack;

extern AllocStack *lbl_802FFE98;
void *fn_8009F4C4(s32);
void *fn_801252BC(void *);
void fn_8000F2F8(AllocStack *, void *);
void fn_8000F320(AllocStack *);
void *Mem_Alloc_3(s32);
void fn_80127438(void *, void *);

void fn_80127D7C(CStruct *arg0, s32 arg1, u8 *arg2, u16 arg3) {
    u32 var_r11;
    u8 *var_r28;
    u8 *var_r9;
    QNode *node;
    u8 *buf;

    node = (QNode *)fn_801252BC(fn_8009F4C4(0x10));
    node->unk0x04 = arg1;
    node->c = 7;
    node->d = arg3;
    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->top);
    buf = (u8 *)Mem_Alloc_3(arg3);
    fn_8000F320(lbl_802FFE98);
    var_r28 = arg2;
    var_r11 = 0U;
    var_r9 = buf;
    if (var_r11 < arg3) {
        do {
            *var_r9 = *var_r28;
            var_r11 += 1;
            var_r28 += 1;
            var_r9 += 1;
        } while (var_r11 < arg3);
    }
    node->unk0x08 = buf;
    fn_80127438(arg0, node);
}

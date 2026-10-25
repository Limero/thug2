// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024F5C0-0x8024F65C (156B). Byte-identical.
#include "types.h"
#include "structs.h"

register s32 frag_src __asm__("r12");
register s32 frag_str __asm__("r14");
register s32 frag_dst __asm__("r15");
register s32 ca0 __asm__("r20");
register s32 ca1 __asm__("r21");
register s32 ca2 __asm__("r22");
register s32 ca3 __asm__("r23");
register s32 ca4 __asm__("r24");
register s32 ca5 __asm__("r25");
register s32 ca6 __asm__("r26");
register s32 ca7 __asm__("r27");

void fn_8024F5C0(void) {
    __asm__ volatile("dcbz 0,%0" : : "r"(frag_dst));
    ca0 = ((Unk_41EA2015 *)frag_src)->unk0x0;
    ca1 = ((Unk_41EA2015 *)frag_src)->unk0x4;
    ca2 = ((Unk_59AB5482_2 *)frag_src)->unk0x8;
    ca3 = ((Unk_41EA2015 *)frag_src)->unk0xC;
    ca4 = ((Unk_41EA2015 *)frag_src)->unk0x10;
    ca5 = ((Unk_41EA2015 *)frag_src)->unk0x14;
    ca6 = ((Unk_41EA2015 *)frag_src)->unk0x18;
    ca7 = ((Unk_41EA2015 *)frag_src)->unk0x1C;
    frag_src += frag_str;
    ((Unk_41EA2015 *)frag_dst)->unk0x0 = ca0;
    ((Unk_41EA2015 *)frag_dst)->unk0x4 = ca1;
    ((Unk_59AB5482_2 *)frag_dst)->unk0x8 = ca2;
    ((Unk_41EA2015 *)frag_dst)->unk0xC = ca3;
    ((Unk_41EA2015 *)frag_dst)->unk0x10 = ca4;
    ((Unk_41EA2015 *)frag_dst)->unk0x14 = ca5;
    ((Unk_41EA2015 *)frag_dst)->unk0x18 = ca6;
    ((Unk_41EA2015 *)frag_dst)->unk0x1C = ca7;
    __asm__ volatile("dcbst 0,%0" : : "r"(frag_dst));
    frag_dst += frag_str;
    __asm__ volatile("dcbz 0,%0" : : "r"(frag_dst));
    ca0 = ((Unk_41EA2015 *)frag_src)->unk0x0;
    ca1 = ((Unk_41EA2015 *)frag_src)->unk0x4;
    ca2 = ((Unk_59AB5482_2 *)frag_src)->unk0x8;
    ca3 = ((Unk_41EA2015 *)frag_src)->unk0xC;
    ca4 = ((Unk_41EA2015 *)frag_src)->unk0x10;
    ca5 = ((Unk_41EA2015 *)frag_src)->unk0x14;
    ca6 = ((Unk_41EA2015 *)frag_src)->unk0x18;
    ca7 = ((Unk_41EA2015 *)frag_src)->unk0x1C;
    ((Unk_41EA2015 *)frag_dst)->unk0x0 = ca0;
    ((Unk_41EA2015 *)frag_dst)->unk0x4 = ca1;
    ((Unk_59AB5482_2 *)frag_dst)->unk0x8 = ca2;
    ((Unk_41EA2015 *)frag_dst)->unk0xC = ca3;
    ((Unk_41EA2015 *)frag_dst)->unk0x10 = ca4;
    ((Unk_41EA2015 *)frag_dst)->unk0x14 = ca5;
    ((Unk_41EA2015 *)frag_dst)->unk0x18 = ca6;
    ((Unk_41EA2015 *)frag_dst)->unk0x1C = ca7;
    __asm__ volatile("dcbst 0,%0" : : "r"(frag_dst));
}

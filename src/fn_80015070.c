// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015070-0x800150EC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* Script/object vtable reached through arg0->unk0x3C: +0x10 is a signed
   self-offset (lha), +0x14 is the method pointer. */
typedef struct {
    char pad0x0[0x10];
    s16 unk0x10;
    char pad0x12[0x2];
    s32 (*unk0x14)(void *, void *, s32, s32, s32);
} ObjVtbl;

/* Global counter bumped on every entry (.data, 4 bytes at 0x802FFF10).
   Reached through the array form so ngccc keeps the @ha/@l pair and the
   folded -0xF0 displacement want uses. */
extern char lbl_802FFF10[];

/* K&R on purpose: old-style + no-arg call emits no crclr (M5.0g rule), and
   only the K&R form keeps the entry fold. r3 is preset via `target`. */
void fn_8001B754();

bool fn_80015070(Unk_C8FEE62D *arg0) {
    register s32 dead __asm__("r0");
    register s32 target __asm__("r3");
    ObjVtbl *vt;

    *(s32 *)&lbl_802FFF10 += 1;
    arg0->unk0x38 += 1;
    target = (s32)((char *)arg0 + 0x8C);
    __asm__ volatile ("lwz %0,0x38(%1)" : "=r"(dead) : "r"(arg0));
    __asm__ volatile ("" :: "r"(dead));
    __asm__ volatile ("" : "+r"(target));
    fn_8001B754();
    vt = (ObjVtbl *)arg0->unk0x3C;
    vt->unk0x14((char *)arg0 + vt->unk0x10, arg0->unk0x14, 0, 0, 0);
    return true;
}

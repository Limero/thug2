// WIP DRAFT (non-matching) — hand reconstruction from the original function.
// family=m2c range=0x80014BC4-0x80014D54 size=400B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BEHAVIOUR: copy the caller's NUL-terminated path into a 0x100-byte stack
// buffer turning '\\' into '/' on the way, then fix up the extension: a name
// ending in "pre" gets its last letter rewritten to 'g', and a second pass
// over an overlapping window rotates the last two bytes.  After that a global
// counter and this->0x38 are bumped, the buffer is handed to fn_8001B658
// (this+0x8C, buffer); on success this->0x2C is refreshed through
// fn_8001B6A8 / fn_80014B34 and the object's own hook (this->0x3C) is
// dispatched with a signed this-adjustment from the vtable.
//
// SHAPE NOTES (the parts that decide the codegen):
//   * the buffer is reached through a materialised `char *` so the array base
//     (used only for the '/' store, an unsigned byte compare) and the pointer
//     walk are separate pseudos — retail keeps three bases: the array itself,
//     the pointer, and a block-scope copy of the pointer that only the copy
//     loop uses.
//   * the source-character type must be SIGNED: retail sign-extends the byte
//     it tests for the loop exit, which a plain `char` (unsigned on PPC) does
//     not produce.
//   * the "pre" fix-up reads and writes the buffer as `u8`, so every compare
//     there is a zero-extended byte load.
//   * the length is a signed int from strlen and is used both as a positive
//     index (buffer[len]) and as len-1..len-4, so it must stay one web.
//
// RULED OUT (measured previously): scalar `u8 sp8` buffer (frame collapses and
// the callee prototype grows to five args); hoisting the vtable read above the
// fn_8001B658 call; volatile lvalue on 0x2C; char* vs void* on the callee
// prototypes.  Still unexplained: retail re-reads this->0x38 once, dead, just
// before the fn_8001B658 call.
//
// STATE: 37% NEAR, size-exact. The copy loop is right (the source byte is the
// loop condition, not the destination), the '\\'-to-'/' fix-up reads the
// destination at the current index, the two "pre"->"prg" fix-ups and the
// counter bumps are in place, and the tail (init call, two conversions, the
// mtlr/blrl dispatch through this->0x3C) is account-in. Residual: cc1 keeps
// the source character in one pseudo (in-place sign extension) where retail
// keeps two (the byte it stores and the sign-extended copy it tests), and it
// stores the first character after the exit test instead of before it.
#include "types.h"
#include "structs.h"
extern s32 lbl_802EFF10;
extern s32 strlen(const char *);
extern s32 fn_8001B658(void *, char *);
extern s32 fn_8001B6A8(void *);
extern s32 fn_80014B34(s32);
typedef struct {
    char pad0x00[0x14];
    s32 unk0x14;
    char pad0x18[0x14];
    s32 unk0x2c;
    s32 unk0x30;
    char pad0x34[4];
    s32 unk0x38;
    Unk_4E705049 *unk0x3C;
} Bc4;
s32 fn_80014BC4(Bc4 *arg0, s8 *src) {
    char buf[0x100];
    s32 i;
    s32 len;
    s8 c;
    Unk_4E705049 *vt;

    arg0->unk0x30 = 0;
    i = 0;
    c = *src;
    buf[i] = c;
    while (c != 0) {
        if (buf[i] == '\\') {
            buf[i] = '/';
        }
        i++;
        c = *++src;
        buf[i] = c;
    }
    buf[i] = 0;
    len = strlen(buf);
    if ((buf[len - 1] == 'e') && (buf[len - 2] == 'r') && (buf[len - 3] == 'p')) {
        buf[len - 1] = 'g';
    }
    if ((buf[len - 2] == 'e') && (buf[len - 3] == 'r') && (buf[len - 4] == 'p')) {
        buf[len - 2] = buf[len - 1];
        buf[len - 1] = buf[len];
    }
    lbl_802EFF10 = lbl_802EFF10 + 1;
    arg0->unk0x38 = arg0->unk0x38 + 1;
    if (fn_8001B658(&arg0->pad0x00[0x8C], buf) == 0) {
        return 0;
    }
    arg0->unk0x2c = fn_8001B6A8(&arg0->pad0x00[0x8C]);
    arg0->unk0x2c = fn_80014B34(arg0->unk0x2c);
    vt = arg0->unk0x3C;
    ((void (*)(void *, s32, void *, s32))vt->unk0x14)((char *)arg0 + vt->unk0x18, 0, &arg0->pad0x00[0x8C], arg0->unk0x2c);
    return 1;
}

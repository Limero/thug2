// __getreent — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Returns newlib's _impure_ptr (lbl_803CA420, r13-relative): the pointer to
// the global struct _reent. Plain C cannot emit the r13 form under -G0, so
// the address is read with an inline-asm wedge (§6aw-173). Sole active
// caller: errno-setting code (strtod draft, math fn_802704A4).
// range 0x8026E5A4-0x8026E5AC (8B). Byte-identical.
#include "types.h"
extern s32 lbl_803CA420;
struct _reent;
extern struct _reent *_impure_ptr;
struct _reent *__getreent(void) {
    struct _reent *r;
    r = lbl_803CA420;
    return r;
}

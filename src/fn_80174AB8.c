// range 0x80174AB8-0x80174AE0 (0x28). Byte-identical.
// Identification: singleton passthrough wrapper — calls the matched
// fn_801A5D9C with the object at lbl_80305EFC and the caller's second
// argument passed straight through in r4.
//
// Matching key: the second call arg must be the function's OWN second
// parameter (`void *unused, s32 arg1`); passing a literal 0 makes ngccc
// emit `li r4,0` and a 3-arg form emits `mr r4,r3`, neither of which want
// has — want's bl uses r4 untouched (10/10 only via the passthrough form).
#include "types.h"
extern char lbl_80305EFC[];
extern s32 fn_801A5D9C(void *, s32);
s32 fn_80174AB8(void *unused, s32 arg1) {
    return fn_801A5D9C(*(void **)lbl_80305EFC, arg1);
}

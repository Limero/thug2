// range 0x8000E014-0x8000E08C (0x78). Byte-identical.
// Identification: singleton-guard wrapper in the E08C/E104 family. Acquires
// the global object (*(void**)&lbl_802FFE84) through the guarded lookup
// fn_8000D3DC(key=arg3); if it succeeds, sets the in-use flag
// lbl_802FFE88 = 1 and forwards to fn_8000CF20(obj->4, arg0, arg1*arg2),
// otherwise clears the flag and returns 0. Sibling of fn_8000E08C /
// fn_8000E104 (same globals + guard pattern).
//
// Matching key (recipe 246): in the success path the call-arg computations
// (reload ptr, arg1*arg2, load obj->4) are emitted BEFORE the `lbl_802FFE88 =
// 1` store and the arg0 re-home. Materializing each as a temp in that order —
// `void *temp_r9 = *ptr; s32 temp_r5 = arg1*arg2; s32 temp_r0 = *(obj+4);
// lbl_802FFE88 = 1; return fn(temp_r0, arg0, temp_r5);` — is what flips the
// 20/30 scheduler-order miss into 30/30.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE84[];
extern s32 lbl_802FFE88;
s32 fn_8000D3DC(Unk_C8FEE62D *, s32);
s32 fn_8000CF20(CStruct *, void *, s32);
s32 fn_8000E014(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r3;
    temp_r3 = fn_8000D3DC(*(void * *)&lbl_802FFE84, arg3);
    if (temp_r3 != 0) {
        void *temp_r9 = *(void * *)&lbl_802FFE84;
        s32 temp_r5 = arg1 * arg2;
        s32 temp_r0 = *(s32 *)((s32 *)temp_r9 + 1);
        lbl_802FFE88 = 1;
        return fn_8000CF20(temp_r0, arg0, temp_r5);
    }
    lbl_802FFE88 = temp_r3;
    return 0;
}
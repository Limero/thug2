// range=0x80058FE8-0x80058FF4 size=12B
// Leaf: multiplies float arg by *(float*)(arg0 + 0x20).
// Suggested rename: ScaleFloat_0x20
#include "types.h"
#include "structs.h"

f32 fn_80058FE8(Unk_C7387A53 *arg0, f32 farg0) {
    return farg0 * *((f32 *)&arg0->unk0x20);
}

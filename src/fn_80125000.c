// range 0x80125000-0x80125020 (0x20 = 32B). Byte-identical.
// Identification: float initializer — self->1 = 0; self->4 = self->8 = f,
// where f is the float constant at lbl_8029E46C (.rodata2); returns self.
// The two float stores need source order [8, 4] (recipe 249 rotation) to
// come out want's [4, 8]. Suggested rename: Fn_80125000_InitWithFloatConst.
#include "types.h"
#include "structs.h"
extern char lbl_8029E46C[];
void *fn_80125000(Unk_C71E6DE1 *arg0) {
    f32 f = *(f32 *)lbl_8029E46C;
    arg0->unk0x1 = 0;
    *((f32 *)&arg0->unk0x8) = f;
    *((f32 *)&arg0->unk0x4) = f;
    return arg0;
}

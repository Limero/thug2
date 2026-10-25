// range 0x8005ED88-0x8005EDB0 (0x28). Byte-identical.
// Identification: vector/range init — writes 0.0f into +0/+4/+8 and the
// large range max 10000.0f (lbl_80293C70) into +0xc, returning the
// object. Sibling of fn_8005EE50/EEFC in the same float-init cluster.
//
// Matching key: two-distinct-pool-const float stores — source in
// want's emission order [+0,+4,+8,+0xc] (brute-forced) + return self.
#include "types.h"
#include "structs.h"
void *fn_8005ED88(CStruct *self) {
    *((f32 *)&self->unk0x0) = 0.0f;
    *((f32 *)&self->unk0x4) = 0.0f;
    *((f32 *)&self->unk0x8) = 0.0f;
    *((f32 *)&self->unk0xC) = 10000.0f;
    return self;
}
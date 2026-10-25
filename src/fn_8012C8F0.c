// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012C8F0-0x8012C9F0 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* file-local layout copied from the promoted byte-identical src/fn_80125480.c */
typedef struct Node { char pad0[2]; u8 unk2; char pad1[9]; void *unkC; } Node;

u8 *fn_8012E168(u8 *);
u8 *fn_8012B2A0(u8 *);
void fn_8012CB2C();        /* deliberately unprototyped: want keeps crclr cr1eq */
u8 *fn_80125480(s32);
u8 *fn_8012CB7C(u8 *, u32);

void fn_8012C8F0(void *arg0) {
    s32 sp8;
    u8 *var_r31;
    s32 var_r0;
    Node *temp_r3;

    var_r31 = fn_8012E168(arg0);
    var_r0 = *(u8 *)var_r31;
    if (var_r0 != 0x24) {
        do {
            if ((var_r0 & 0xFF) != 0x16) {
                if ((var_r0 & 0xFF) == 0x47) {
                    var_r31 = fn_8012B2A0(var_r31);
                    if (*(u8 *)var_r31 == 0x39) {
                        var_r31 += 1;
                    }
                    continue;
                } else {
                    goto block_13;
                }
            } else {
                var_r31 += 1;
                fn_8012CB2C(&sp8, var_r31);
                var_r31 += 4;
                temp_r3 = fn_80125480(sp8);
                if (temp_r3 != NULL) {
                    if (temp_r3->unk2 == 8) {
                        *(u8 *)((char *)var_r31 - 5) = 0x43;
                        fn_8012CB7C(var_r31 - 4, (u32)temp_r3->unkC);
                    } else if (temp_r3->unk2 == 9) {
                        if (temp_r3->unkC != 0) {
                            fn_8012CB7C(var_r31 - 4, (u32)temp_r3->unkC);
                            *(u8 *)((char *)var_r31 - 5) = 0x46;
                        } else {
                            *(u8 *)((char *)var_r31 - 5) = 0x44;
                        }
                    }
                }
            }
block_13:
            var_r31 = fn_8012E168(var_r31);
        } while ((var_r0 = *(u8 *)var_r31) != 0x24);
    }
}

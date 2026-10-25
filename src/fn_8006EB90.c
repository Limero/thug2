// range 0x8006EB90-0x8006EBB8 (0x28). Byte-identical.
// Identification: float global setter + notify — stores f1 to lbl_80301474,
// then calls fn_800872FC (unmatched).
#include "types.h"
extern char lbl_80301474[];
extern void fn_800872FC(void);
void fn_8006EB90(f32 f1) {
    *(f32 *)lbl_80301474 = f1;
    fn_800872FC();
}

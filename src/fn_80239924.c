// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80239924-0x802399E8 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
void fn_80240B44(Unk_F96D0DC8 *);
s32 fn_80237D14(void *, Unk_8C3FE072 *, s32, Unk_4CED4D63 *, void *);
void fn_80243318(CStruct *, s32);
s32 fn_8024336C(CStruct *);
s32 fn_802432A0(Unk_9994C3F5 *);
s32 fn_802416F8(s32);
void fn_80243320(s32 *, s32);

/* The 6-byte descriptor: a word plus a halfword, 8-aligned so it cannot share
   the out-param's slot. */
typedef struct {
    s32 a;
    u16 b;
} __attribute__((aligned(8))) Pay39924;

/* One frame object: the shared out-param slot first, the descriptor at +8. */
typedef struct {
    s32 out;
    Pay39924 pl;
} Frm39924;

s32 fn_80239924(s32 arg0, Unk_F5317C5D *arg1) {
    Frm39924 fr;
    Pay39924 *pl;
    Unk_C7387A53 *var_r30;

    fn_80240B44(arg1);
    pl = &fr.pl;
    pl->a = arg1->unk0x0;
    pl->b = arg1->unk0x4;
    fn_80243318(&fr.out, fn_80237D14(arg0, (Unk_8C3FE072 *)pl, 0, 0, 1));
    var_r30 = fn_8024336C(&fr.out);
    if (var_r30 != NULL) {
        do {
            if (*(s32 *)((char *)fn_802416F8(fn_802432A0(var_r30)) + 8) & 0x4000) {
                fn_80243320(&fr.out, 2);
                return 1;
            }
            var_r30 = *((void * *)&var_r30->unk0xC);
        } while (var_r30 != NULL);
    }
    fn_80243320(&fr.out, 2);
    return 0;
}

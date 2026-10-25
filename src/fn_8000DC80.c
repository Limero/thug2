// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DC80-0x8000DD2C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80290340[];
s32 sprintf(char *, ...);
void OSVReport(char *, s32);
s32 fn_8000ED30(s32, void *, s32);
void fn_8000EE30(s32, void *);
void fn_8000CC48(s32, s32);

void fn_8000DC80(Unk_C8FEE62D *arg0, void *arg1, s32 arg2) {
	char sp8[128];
	s32 temp_r3;
	if (arg0->unk0x18 == 0 && (((temp_r3 = fn_8000ED30(arg0->unk0x14, arg1, 1)), (temp_r3 != 0)) || arg2 == 0)) {
		sprintf(sp8, lbl_80290340, arg1);
		OSVReport(sp8, 0);
		fn_8000EE30(arg0->unk0x14, arg1);
		if (temp_r3 != 0) {
			fn_8000CC48(temp_r3, 3);
		}
	}
}

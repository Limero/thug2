// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801322F8-0x8013237C (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_801266EC(Unk_5D1D68CC *);

void fn_801322F8(Unk_B1CD4D9E *arg0) {
	s32 i = 0x14;
	void *walker = (char *)arg0 + 4;
	s32 off;
	register s32 b1s __asm__("r8");
	register s32 b2s __asm__("r10");
	register s32 zBs __asm__("r11");
	register s32 zAs __asm__("r0");

	do {
		fn_801266EC(walker);
		walker += 0x10;
	} while (--i != 0);

	zAs = 0;
	arg0->unk0x144 = zAs;
	arg0->unk0x1E8 = zAs;

	b1s = (s32)arg0 + 0x148;
	zBs = 0;
	b2s = (s32)arg0 + 0x14C;
	for (off = 0; off < 0xA0; off += 8) {
		*(s32 *)((char *)off + (s32)b1s) = zBs;
		*(s32 *)((char *)off + (s32)b2s) = zBs;
	}

	arg0->unk0x1EC = 0;
	arg0->unk0x1F4 = 0;
}

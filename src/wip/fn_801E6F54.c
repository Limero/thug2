// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group E)
// PARKED: DOC-29 VMX WALL - want mixes FOUR genuine AltiVec
// vmhaddshs words (opcode 4, XO6=32, e.g. @0x801E7144 w=0x11AD4C20,
// VD=v13/VA=v13/VB=v9/VC=v16) into each of the four dot-product windows
// (@0x801E7138-0x801E7160, 0x801E7198-0x801E71AC, 0x801E71D0-0x801E71E4,
// 0x801E7200-0x801E7214), interleaved with REAL Gekko PS ops (ps_mul xo5=25,
// ps_madd xo5=29, ps_sum0 xo5=10, ps_rsqrte xo5=26) and psq_l/st pair moves.
// Genuine VMX stays unemittable (docs/parkings/29-altivec-vmx-unemittable.md;
// §7b-140 correction covers vpkuhum only, NOT vmhaddshs). Park immediately
// per §6o-103.
//
// Decoded structure for future retry (all non-VMX parts verified against
// want; callees audited):
//   s32 fn(void *obj /*r31*/, void *ent /*r27*/, s32 arg3 /*r26*/)
//   mgr = obj->0x15BC;
//   if (mgr->0x1C==1 && mgr->0xF4==0 && mgr->0x130==0 &&
//       (t==ent || t==ent->0x48 || t==ent->0x4C)) return 0;
//   t = obj->0x25C;
//   if (t==0) goto stateset;
//   if (t==ent || t==ent->0x48 || t==ent->0x4C) goto L260(skip);
//   if (*( (*lbl_80305FF8) + 0x44 ) == 0xA443A2BC) goto stateset;
//   if (t->0x48 == NULL || ent->0x48 == NULL) goto stateset;
//   // 7 calls: s32 fn_801AE5A4(void *out, s32 base, s32 idx);
//   //   A(&sp18,t) [r5 passthrough!] B(&sp28,arg1) C(&sp28,t)
//   //   D(&sp38,t->48) E(&sp48,arg1) F(&sp48,t->48) G(&sp58,a48)
//   // diffs d1=A-B(sp8/sp10), d2=C-D(sp18/sp20), d3=D-E(sp28/sp30),
//   // then FOUR dot/fabs checks vs *(f32*)&lbl_802AD84C, any fail -> skip;
//   // all pass -> stateset. THE DOTS CONTAIN THE VMX WORDS.
//   // stateset: p=mgr+0x6C; if(p[1]!=1){p[1]=1;p[2]=lbl_80303150+Tmr_GetTime();}
//   // L260 final bool r29:
//   //   if (mgr->0x70==0 && (u32)(lbl_80303150+Tmr_GetTime()-obj->0x264)
//   //       <= (u32)obj->0x26C) return 0;
//   //   if (arg3!=0) return 1;
//   //   if (mgr->0x1C==4) return 0;
//   //   if (mgr->0x4C==0) return 1;
//   //   if (*(f32*)(obj->0xC+0xBC) <= *(f32*)&lbl_802AD84C...) hmm see asm
//   //     (lfs -0x27b4 => lbl_802AD84C value) -> ble return 0 else return 1
// family=m2c range=0x801E6F54-0x801E72F0 size=924B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

// Body NOT reconstructable byte-exact until the VMX wall falls; see park
// note above for the full verified structure. Kept as a compiling placeholder.
s32 fn_801E6F54(Unk_71062261 *arg0, void *arg1, s32 arg3, s32 arg2) {
    void *mgr = *((void * *)&arg0->unk0x15BC);
    if (((Unk_C7387A53 *)mgr)->unk0x70 == 0 && arg3 == 0) {
        return 0;
    }
    return 1;
}

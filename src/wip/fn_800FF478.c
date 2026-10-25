// WIP draft - PARKED. See notes below.
// family=m2c range=0x800FF478-0x800FF8CC size=1108B
// PARKED: AltiVec VMX (vpkuhum @0x800FF83C) + paired-single psq_l/psq_st
// (@0x800FF7F8-0x800FF854). ngccc cannot emit VMX; hard park (see fn_800FE42C).
//
// Structural sketch (0x454 bytes, frame 0x10A8, saves f30+f31+r26-r31):
//   twin of fn_800FF030 with different arg layout/helpers:
//   fn_8010391c(*(arg0+8), &sp1068, sp+8, 0x800) -> list
//   per node: state16 idiom; masks vs *(u16*)(arg2+0x820)/(arg2+0x822);
//   3 verts -> sp1008/18/28 (f30 = rodata -0x7fd6:-0x3e44 splat)
//   if (*(f32*)(arg2+0x818) == f30const) fn_800FAE1C(arg1, 5 stack pts)
//   if ok && *(u32*)(arg2+0x81C)!=0x20:
//     slot = arg2 + (*(u32*)(arg2+0x81C)<<6) + 8   (stride 0x40!)
//     psq copy 2 pairs + singles: node u16@+0x3C(rlwinm bit25),
//     *(u32*)arg0 @+0x38, trio @+8/+0x10/+0x18/+0x24(+fcmpu guard),
//     ++*(u32*)(arg2+0x81C); if (*(u32*)(arg2+0x824)==2) return 1;
//   tail: return *(u32*)(arg2+0x81C) > 0;
#include "types.h"

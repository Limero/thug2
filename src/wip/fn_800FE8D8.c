// WIP draft - PARKED. See notes below.
// family=m2c range=0x800FE8D8-0x800FF030 size=1880B
// PARKED: AltiVec VMX (vmhaddshs/vmsumshm @0x800FEC90-0x800FED38) + paired-single
// psq_l/psq_st. ngccc cannot emit VMX; hard park (see fn_800FE42C note).
//
// Structural sketch (0x758 bytes, frame 0x1120, saves f31+r14-r31):
//   twin of fn_800FE42C with different helpers/masks:
//   fn_8010391c(*(arg0+8), &sp1088, sp+8, 0x800) -> list (r20)
//   loop over nodes: state = ((u16*)t->[0xC])[node*4] or +node*10 (t=obj->8)
//     mask tests vs *(u16*)(arg3+0xD04)/(arg3+0xD06) (and./andc.)
//     3 vertices loaded to sp1008/sp1018/sp1028 (same vtab t->[0x3C]/[0x30]
//     stride-0xC pattern, f31 = rodata -0x7fd6:-0x3e50 splat)
//     fn_800F8858(...); PS transform block; VMX dot products;
//     result appended, counter bumped; returns count!=0 style boolean.
#include "types.h"

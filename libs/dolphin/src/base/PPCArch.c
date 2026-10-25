#include <dolphin/dolphin.h>
#include <dolphin/base/PPCArch.h>

asm u32 PPCMfmsr() {
    nofralloc
    mfmsr r3
    blr    
}

asm void PPCMtmsr(__REGISTER u32 newMSR) {
    nofralloc
    mtmsr newMSR
    blr
}

asm u32 PPCMfhid0() {
    nofralloc
    mfspr r3, HID0
    blr
}

asm void PPCMthid0(__REGISTER u32 newHID0) {
    nofralloc
    mtspr HID0, newHID0
    blr
}

asm u32 PPCMfl2cr() {
    nofralloc
    mfspr r3, L2CR
    blr
}

asm void PPCMtl2cr(__REGISTER u32 newL2cr) {
    nofralloc
    mtspr L2CR, newL2cr
    blr
}

asm void PPCMtdec(__REGISTER u32 newDec) {
    nofralloc
    mtdec newDec
    blr
}

asm void PPCSync() {
    nofralloc
    sc
    blr
}

asm void PPCHalt() {
    nofralloc
    sync
loop:
    nop
    li r3, 0
    nop
    b loop
}

asm void PPCMtmmcr0(__REGISTER u32 newMmcr0) {
    nofralloc
    mtspr MMCR0, newMmcr0
    blr
}

asm void PPCMtmmcr1(__REGISTER u32 newMmcr1) {
    nofralloc
    mtspr MMCR1, newMmcr1
    blr
}

asm void PPCMtpmc1(__REGISTER u32 newPmc1) {
    nofralloc
    mtspr PMC1, newPmc1
    blr
}

asm void PPCMtpmc2(__REGISTER u32 newPmc2) {
    nofralloc
    mtspr PMC2, newPmc2
    blr
}

asm void PPCMtpmc3(__REGISTER u32 newPmc3) {
    nofralloc
    mtspr PMC3, newPmc3
    blr
}

asm void PPCMtpmc4(__REGISTER u32 newPmc4) {
    nofralloc
    mtspr PMC4, newPmc4
    blr
}

u32 PPCMffpscr() {
    union FpscrUnion m;

    asm {
        mffs fp31
        stfd fp31, m.f;
    }

    return m.u.fpscr; 
}

void PPCMtfpscr(__REGISTER u32 newFPSCR) {
    union FpscrUnion m;

    asm {
        li    r4, 0
        stw   r4, m.u.fpscr_pad;
        stw   newFPSCR, m.u.fpscr
        lfd   fp31, m.f
        mtfsf 0xff, fp31
    }
}

asm u32 PPCMfhid2() {
    nofralloc
    mfspr r3, HID2
    blr
}

asm void PPCMthid2(__REGISTER u32 newhid2) {
    nofralloc
    mtspr HID2, newhid2
    blr
}

asm void PPCMtwpar(__REGISTER u32 newwpar) {
    nofralloc
    mtspr WPAR, newwpar
    blr
}

void PPCDisableSpeculation(void) {
    PPCMthid0(PPCMfhid0() | HID0_SPD);
}

asm void PPCSetFpNonIEEEMode() {
	nofralloc
	mtfsb1 29
	blr
}

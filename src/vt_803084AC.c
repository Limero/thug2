// Vtable 0x803084AC as real C data (tier-2).
// Slots reference the renamed methods (docs/data-vtables.tsv).

extern void Vtable0x803084AC_m0(void);
extern void Vtable0x803084AC_m1(void);
extern void Vtable0x803084AC_m2(void);
extern void Vtable0x803084AC_m3(void);
extern void Vtable0x803084AC_m4(void);
extern void Vtable0x803084AC_m5(void);

void *lbl_803084AC[6] __attribute__((section(".data"))) = {
    (void *)Vtable0x803084AC_m0,
    (void *)Vtable0x803084AC_m1,
    (void *)Vtable0x803084AC_m2,
    (void *)Vtable0x803084AC_m3,
    (void *)Vtable0x803084AC_m4,
    (void *)Vtable0x803084AC_m5
};

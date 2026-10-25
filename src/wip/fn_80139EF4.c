// WIP DRAFT — PARKED (non-matching). Hand-rebuilt from the want; the m2c draft
// compiled to only 56 B of the 1188 B function because its `switch` had no real
// case labels, so every arm fell through one shared block.
// reproduce: LEAF_TMPDIR=<scratch> \
//     tools/venv/bin/python tools/want_got.py 0x80139EF4  -> 1164B / 273 diffs / 6.19%
//
// family=m2c range=0x80139EF4-0x8013A398 size=1188B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Progression while rebuilding (want 1188 B):
//   56 B / 12 diffs   m2c husk (no case labels)
//   1160 B / 265      real switch, wrong Vtbl offsets
//   1164 B / 270      + case 0xF fallthrough store
//   1164 B / 273      + byte-offset virtual call, two payload objects
//   1164 B / 273      + 0xA8 payload size -> frame now EXACTLY -0x188
//
// The 0xA8 payload size is not a guess: want has case 0xE's payload at
// r1+0x18 and case 0xF's at r1+0xC0, with the saved-GPR block at 0x168, so the
// struct is exactly 0xC0-0x18 = 0xA8 bytes and the two cases own SEPARATE
// instances (declaring one shared `Pld` gives -0x90 and breaks both offsets).
//
// Parked on one C-vs-C++ codegen wall:
//   want materialises `&sp8` into a callee-saved register ONCE per case
//   (`addi r11,r1,8` / `mr r26,r11` / `mr r10,r26`) and then addresses sp8
//   through r10/r26 for the rest of the arm (`stw r9,4(r26)`, `lwz r9,4(r10)`).
//   Plain C keeps addressing r1-relative. That is `this`-pointer codegen, i.e.
//   the original sp8 is a C++ object with an inlined destructor — the repeated
//   `sp8.unk8 = lbl_8029F3B0` on every exit path is that destructor storing a
//   constant into the object, and the register-held address is how ngccc
//   carries `this` across the calls it makes. Per AGENTS §4b this project stays
//   in C, and this is not reachable without inline asm.
// Residual (non-blocking) semantic points already corrected vs the m2c draft:
//   * fn_8000F2F8 is called with ONE argument (the 0x80300000 the draft passed
//     is a reloc artefact of the harness, not a second argument);
//   * the virtual call target is `(char *)node + vtable->unk8` where unk8 is an
//     s16 BYTE offset (want: `lha r3,8(r9)` then `add r3,r29,r3`), not an array
//     index — the m2c draft's spelling produced `mulli r3,r3,0x1c`, which does
//     not exist in the want;
//   * case 0xE's alloc block appears ONCE, shared by the search-loop
//     fallthrough, not duplicated per branch.
#include "types.h"
extern char lbl_802FFE98[];
extern char lbl_8029F3B0[];
void *memcpy(void *, const void *, u32);
s32 strcpy(char *, const char *);

typedef struct Buf Buf;
struct Buf {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    char padC[0x20];
    void *unk2C;
    void *unk30;
    s32 unk3C;
};

typedef struct Vtbl Vtbl;
struct Vtbl {
    s32 pad0[2];
    s16 unk8;
    char padA[2];
    void *unkC;
};

typedef struct Node Node;
struct Node {
    void *unk0;
    s32 unk4;
    char pad8[4];
    Node *unkC;
    void *unk10;
    Vtbl *unk14;
    Buf *unk18;
};

/* arg0 */
typedef struct A0 A0;
struct A0 {
    char *unk0;
    u8 unk4;
    char pad5[3];
    s32 unk8;
    char *unkC;
    char *unk10;
};

/* the r1+8 object: {unk0, unk4, vtable-ish 0x8029F3B0}; the epilogue always
   rewrites unk8 to lbl_8029F3B0, i.e. an inlined destructor. */
typedef struct Sp8 Sp8;
struct Sp8 {
    s32 unk0;
    Node *unk4;
    s32 unk8;
};

/* stack payload built for fn_80138038 / fn_801399D8 */
typedef struct Pld Pld;
struct Pld {
    void *unk0;
    u8 unk4;
    char pad5[3];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    char tail[0xA8 - 0x18];
};

void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
void *Mem_Alloc2(s32);
void *Mem_Alloc(s32);
void Mem_Free2(void *);
void *Mem_NewZero(s32);
void *fn_80137C3C(void);
void *fn_80137C10(void *);
void fn_80137C5C(s32);
void fn_80138038(Pld *);
s32 fn_801399D8(char *, Pld *);
s32 Crc_GenerateCRCCaseSensitive(void *, s32);

#define K_TAIL (s32)lbl_8029F3B0

s32 fn_80139EF4(A0 *arg0) {
    Sp8 sp8;
    Node *n;
    Buf *b;
    void *p;
    s32 i;

    fn_8000F2F8(*(void **)lbl_802FFE98,
                *(s32 *)(*(char **)lbl_802FFE98 + 0x134));

    switch (arg0->unk4) {
    case 0xE: {
        Pld pld;
        n = (Node *)(arg0->unk10 + 0x2084);
        sp8.unk8 = K_TAIL;
        sp8.unk4 = n;
        n = n->unkC;
        if (n->unk4 == -1) {
            n = NULL;
        }
        sp8.unk4 = n;
        n = (n != NULL) ? n->unkC : NULL;
        if (n != NULL) {
            do {
                b = n->unk18;
                if (b->unk4 == *(s32 *)(arg0->unk0 + 0x24)) {
                    fn_8000F320(*(void **)lbl_802FFE98);
                    sp8.unk8 = K_TAIL;
                    return 4;
                }
                n = sp8.unk4->unkC;
                if (n->unk4 == -1) {
                    n = NULL;
                }
                sp8.unk4 = n;
                n = (n != NULL) ? n->unkC : NULL;
            } while (n != NULL);
        }

        b = fn_80137C3C();
        strcpy((char *)b + 9, arg0->unk0);
        b->unk0 = *(s32 *)(arg0->unk0 + 0x20);
        b->unk4 = *(s32 *)(arg0->unk0 + 0x24);
        b->unk3C = *(s32 *)(arg0->unk0 + 0x28);
        b->unk8 = *(u8 *)(arg0->unk0 + 0x2C);
        b->unk2C = Mem_Alloc(*(s32 *)(arg0->unk0 + 0x20));
        b->unk30 = b->unk2C;
        i = *(s32 *)(arg0->unk0 + 0x20);
        if (i > 0x100) {
            i = 0x100;
        }
        memcpy(b->unk2C, arg0->unk0 + 0x2D, i);
        b->unk30 = (void *)((char *)b->unk30 + i);
        Mem_NewZero(0x1C);
        n = (Node *)fn_80137C10(b);
        i = 0;
        n->unkC = (Node *)(arg0->unk10 + 0x2084);
        n->unk0 = *(void **)((char *)n->unkC + 0x10);
        *(void **)((char *)n->unk0 + 0xC) = n;
        *(void **)((char *)n->unkC + 0x10) = n;

        if ((s32)((char *)b->unk30 - (char *)b->unk2C) < b->unk0) {
            sp8.unk8 = K_TAIL;
            fn_8000F320(*(void **)lbl_802FFE98);
            return 1;
        }

        fn_80138038(&pld);
        pld.unk10 = (s32)arg0->unk10;
        pld.unkC = (s32)arg0->unkC;
        pld.unk14 = 0;
        pld.unk4 = b->unk8;
        pld.unk8 = b->unk0;
        pld.unk0 = Mem_Alloc(b->unk0);
        memcpy(pld.unk0, b->unk2C, b->unk0);
        i = fn_801399D8(arg0->unkC + 4, &pld);
        if (i != 5 && i != 3) {
            if (n->unk18 != NULL) {
                fn_80137C5C(3);
            }
            if (n != NULL) {
                ((s32(*)(void *, s32))n->unk14->unkC)((char *)n + n->unk14->unk8, 3);
            }
        }
        if (pld.unk0 != NULL) {
            Mem_Free2(pld.unk0);
        }
        fn_8000F320(*(void **)lbl_802FFE98);
        sp8.unk8 = K_TAIL;
        return i;
    }

    case 0xF: {
        Pld pld2;
        n = (Node *)(arg0->unk10 + 0x2084);
        sp8.unk8 = K_TAIL;
        sp8.unk4 = n;
        n = n->unkC;
        if (n->unk4 == -1) {
            n = NULL;
        }
        sp8.unk4 = n;
        n = (n != NULL) ? n->unkC : NULL;
        while (n != NULL) {
            b = n->unk18;
            if (b->unk4 == *(s32 *)arg0->unk0) {
                memcpy(b->unk30, arg0->unk0 + 4, arg0->unk8 - 4);
                b->unk30 = (void *)((char *)b->unk30 + (arg0->unk8 - 4));
                if ((s32)((char *)b->unk30 - (char *)b->unk2C) >= b->unk0) {
                    fn_80138038(&pld2);
                    pld2.unk10 = (s32)arg0->unk10;
                    pld2.unkC = (s32)arg0->unkC;
                    pld2.unk14 = 0;
                    pld2.unk4 = b->unk8;
                    pld2.unk8 = b->unk0;
                    pld2.unk0 = Mem_Alloc(b->unk0);
                    memcpy(pld2.unk0, b->unk2C, b->unk0);
                    if (Crc_GenerateCRCCaseSensitive(pld2.unk0, b->unk0) !=
                        b->unk3C) {
                        pld2.unk14 |= 4;
                    }
                    i = fn_801399D8(arg0->unkC + 4, &pld2);
                    if (i != 5 && i != 3) {
                        if (n->unk18 != NULL) {
                            fn_80137C5C(3);
                        }
                        if (n != NULL) {
                            ((s32(*)(void *, s32))n->unk14->unkC)((char *)n + n->unk14->unk8, 3);
                        }
                    }
                    if (pld2.unk0 != NULL) {
                        Mem_Free2(pld2.unk0);
                    }
                    fn_8000F320(*(void **)lbl_802FFE98);
                    sp8.unk8 = K_TAIL;
                    return i;
                }
            }
            n = sp8.unk4->unkC;
            if (n->unk4 == -1) {
                n = NULL;
            }
            sp8.unk4 = n;
            n = (n != NULL) ? n->unkC : NULL;
        }
        sp8.unk8 = K_TAIL;
        break;
    }
    default:
        break;
    }

    fn_8000F320(*(void **)lbl_802FFE98);
    return 1;
}
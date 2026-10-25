// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016928-0x800169FC (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
#include "structs.h"

#define OS_LANGUAGE_ENGLISH 0
#define OS_LANGUAGE_GERMAN  1
#define OS_LANGUAGE_FRENCH  2
#define OS_LANGUAGE_SPANISH 3
#define OS_LANGUAGE_ITALIAN 4
#define OS_LANGUAGE_DUTCH   5

extern char lbl_80290BA0[];
s32 fn_80014904(s32, s32, s32, s32);
extern char lbl_80290B98[];
extern char lbl_80290BB8[];
extern s32 lbl_802FFE48; // language
s32 fn_800146E0(s32);
s32 fn_800147E8(Unk_C8FEE62D *, void *);
s32 fn_80023E94(s32);
u8 OSGetLanguage(void);
void *memcpy(void *, const void *, s32);

// Plat_Init @ 0x80016928
void Plat_Init(void) {
    s32 size;
    char* temp_r30;
    void* temp_r31;
    s32 temp_r3_2;

    switch (OSGetLanguage()) {
    case OS_LANGUAGE_GERMAN:
        lbl_802FFE48 = 5; // German
        break;
    case OS_LANGUAGE_FRENCH:
        lbl_802FFE48 = 3; // French

        temp_r31 = fn_80023E94((s32)lbl_80290B98);
        temp_r3_2 = fn_800147E8(lbl_80290BA0, lbl_80290BB8); // open font file
        if (temp_r3_2) {
            size = fn_800146E0(temp_r3_2);
            temp_r30 = NEW_ARRAY(char, size); // original: new char[size]
            fn_80014904(temp_r30, size, 1, temp_r3_2); // read font file
            memcpy(temp_r31, temp_r30, size);
            DELETE_ARRAY(temp_r30); // original: delete[]
        }
        break;
    case OS_LANGUAGE_ENGLISH:
    case OS_LANGUAGE_SPANISH:
    case OS_LANGUAGE_ITALIAN:
    case OS_LANGUAGE_DUTCH:
    default:
        lbl_802FFE48 = 2; // English
        break;
    }
}

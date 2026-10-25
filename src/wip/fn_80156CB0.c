// WIP DRAFT (non-matching) — semantic reconstruction from the retail DOL.
// family=m2c range=0x80156CB0-0x80156DC4 size=276B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED: 84.1% (58/69 words), object .text exactly 276B. Semantics are
// complete and the opcodes/control flow are identical; the residual is one
// allocator role rotation.
//
// Body: reads the QB_NAME checksum, constructs the 0x68-byte temporary
// appearance (vtable at temp+0x08, data object at temp+0x58), looks up the
// profile manager, then either copies the QB_APPEARANCE_STRUCTURE into the
// temporary or takes the QB_PLAYER profile's appearance at profile+4. It then
// resolves the profile entry by name, tests QB_NOFACETEXTURE and either
// destroys/copies the existing entry (entry+0x5C with source+0x58) or
// overwrites it from the source, and finally tears the temporary down.
//
// The original keeps entry in r30 and entry_data in r31; the previous body
// produced the opposite pair, which cascaded through every later address
// (entry+0x5C, source+0x58, both call argument copies, and the else-arm
// source). This revision declares entry_data BEFORE entry so its pseudo is
// born first and should take the higher callee-saved register, matching the
// original pair. Everything else is the measured best: the source pointer is
// assigned before the copy call (the original materialises the call's first
// argument from the same value), and all callee prototypes are audited from
// the retail call sites.
//
// Sibling reference: fn_80156DC4 is the byte-identical counterpart (same
// manager lookup, same entry/entry+4 pair, same QB_NOFACETEXTURE arm).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct ProfileManager {
    char pad0x0[0x1C];
    s32 profiles[64];
} ProfileManager;

typedef struct CStructSmall {
    char pad0x0[2];
    u8 unk0x2;
    char pad0x3;
    s32 unk0x4;
} CStructSmall;

typedef struct TemporaryAppearance {
    char pad0x0[8];
    s32 vtable;
    char pad0xC[0x4C];
    CStructSmall data;
    s32 buffer;
    s32 tail;
} TemporaryAppearance;

extern ProfileManager *lbl_80305EFC;

s32 GetChecksum_2(CStruct *arg0, s32 hash, s32 *out, s32 defval);
char *fn_8003A754(CStruct *out);
s32 fn_8003A944(TemporaryAppearance *appearance, CStruct *data, s32 copy);
s32 GetStructure_2(CStruct *arg0, s32 hash, CStruct **out, s32 defval);
s32 GetInteger(CStruct *arg0, s32 hash, s32 *out, s32 defval);
char *fn_801A5D9C(ProfileManager *manager, s32 player);
char *fn_801A6464(ProfileManager *manager, s32 name);
s32 ContainsFlag(CStruct *arg0, s32 flag);
void CStruct_dtor(CStruct *arg0);
void fn_80126FF4(Unk_80577C09 *arg0, CStruct *arg1);
Unk_31DE137E *fn_8003A80C(Unk_31DE137E *dst, Unk_31DE137E *src);
void fn_8003A7A4(CStruct *arg0, s32 mode);

bool ScriptRememberTemporaryAppearance(CStruct *arg0, CScript *arg1) {
    TemporaryAppearance temp;
    s32 name;
    CStruct *appearance;
    s32 player;
    ProfileManager *manager;
    char *source;
    char *entry_data;
    char *entry;
    s32 noface;
    CStruct *source_data;

    GetChecksum_2(arg0, QB_NAME, &name, 1);
    fn_8003A754((CStruct *)&temp);
    manager = lbl_80305EFC;
    if (GetStructure_2(arg0, QB_APPEARANCE_STRUCTURE, &appearance, 0) != 0) {
        source = (char *)&temp;
        fn_8003A944(&temp, appearance, 1);
    } else {
        GetInteger(arg0, QB_PLAYER, &player, 1);
        source = fn_801A5D9C(manager, player) + 4;
    }
    entry = fn_801A6464(manager, name);
    entry_data = entry + 4;
    noface = ContainsFlag(arg0, QB_NOFACETEXTURE);
    if (noface != 0) {
        entry += 0x5C;
        source_data = (CStruct *)(source + 0x58);
        CStruct_dtor((CStruct *)entry);
        fn_80126FF4((Unk_80577C09 *)entry, source_data);
    } else {
        fn_8003A80C((Unk_31DE137E *)entry_data, (Unk_31DE137E *)source);
    }
    fn_8003A7A4((CStruct *)&temp, 2);
    return true;
}

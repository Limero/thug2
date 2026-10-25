// range 0x8000A778-0x8000A7F8 (0x80). Byte-identical.
// Identification: path/string checksum (same table CRC as Crc_GenerateCRCCaseSensitive, over
// lbl_802FFA3C). Reads chars with sign-extension (extsb); folds A-Z to
// lowercase (c += 0x20) and maps '/' to '\\' so path-style strings hash
// case/path-normalized. Per char: hash = tbl[(u8)hash ^ (u8)c] ^ (hash>>8),
// starting at 0xFFFFFFFF; returns 0 for a NULL string. The '/' -> '\\' fold
// strongly suggests this hashes file/resource paths. Sibling of
// Crc_GenerateCRCCaseSensitive (raw byte CRC, parked at 21/23).
//
// Matching key (recipe 245): unlike A6D4, want does NOT materialize the u8
// mask — it emits `xor r0,r10,r8` on the FULL hash then folds the mask into
// the index `rlwinm`. The index must be written inline as
// `((unsigned char)hash) ^ (unsigned char)c` (hash FIRST) so the xor puts the
// hash in rS; a materialized `u8 lo` temp flips the xor operand order (or
// collapses the fold) and breaks it. Also: hash init must come AFTER the
// first `c = *str++` and the null-check must stay first, or GCC hoists
// `li r10,-1` above the `or. r3,r3,r3` guard (want keeps it at 0x14).
//
// WARNING (masked-branch trap): the '/' -> '\\' check is a SEPARATE if AFTER
// the A-Z fold, reached in both cases (`bgt` at 0x38 skips only the fold and
// lands on `cmpwi r8,0x2f` at 0x44). NESTING the '/' check inside the fold if
// compiles a bgt that skips 3 extra insns to 0x50 — the per-function masked
// test (REL14 mask 0xFFFF0003) still reports 32/32 because branch
// displacements are masked, but the linked DOL then DIFFERS by that one
// bgt displacement byte. Always verify intra-function branch addends
// (sym=fn_8000A778) after promoting.
#include "types.h"
#include "qb_constants.h"
extern unsigned int lbl_802FFA3C[];
unsigned int fn_8000A778(const char *str) {
    unsigned int hash;
    char c;
    if (!str)
        return 0;
    c = *str++;
    hash = QB_UINT32_MAX;
    while (c) {
        if (c >= 'A' && c <= 'Z')
            c = (char)(c + 0x20);
        if (c == '/')
            c = '\\';
        hash = lbl_802FFA3C[((unsigned char)hash) ^ (unsigned char)c] ^ (hash >> 8);
        c = *str++;
    }
    return hash;
}
// range 0x80128F94-0x80128FB4 (0x20 = 32B). Byte-identical.
// Identification: zeroes self->1, self->2 (bytes) and self->8, self->4
// (words), returns self. Mixed byte/word zero-fill: the store rotation
// rule (recipe 249) needs source order [2b, 8w, 4w, 1b] to emit want's
// [1b, 2b, 8w, 4w] (found by brute-forcing the 24 permutations).
// Suggested rename: Fn_80128F94_ZeroMixedFields.
#include "types.h"
#include "structs.h"
void *fn_80128F94(Unk_9D4ED6AF *arg0) {
    arg0->unk0x2 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0x4 = 0;
    arg0->unk0x1 = 0;
    return arg0;
}

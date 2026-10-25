// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B0BC-0x8000B148 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

u32 strlen(const char *);
char *strcpy(char *, const char *);
// NOTE 2026-09-17: the MSL symbol is `strcasecmp` (0x8026B04C), NOT `stricmp`
// — the draft's `stricmp` was undefined at link time. Same semantics.
s32 strcasecmp(const char *, const char *);

// sIsPrefixedWith @ 0x8000B0BC
bool sIsPrefixedWith(const char *s, const char *prefix) {
    char buf[100];
    s32 s_len;
    s32 prefix_len;

    if (!s || !prefix) {
        return false;
    }

    s_len = strlen(s);
    prefix_len = strlen(prefix);
    if (prefix_len>s_len) {
      return false;
    }

    if (prefix_len <= s_len) {
        strcpy(buf, s);
        buf[prefix_len] = 0;

        if (strcasecmp(buf, prefix) == 0) {
          return true;
        }
    }
    return false;
}

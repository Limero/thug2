// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125088-0x8012515C (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u32 checksum;
    char *str;
} Entry;

extern bool lbl_80303198;
extern Entry *lbl_80303194;
extern char *lbl_8030318C;

u32 strlen(const char *);
char *strcpy(char *, const char *);
u32 Crc_GenerateCRCCaseSensitive(const void *, u32);

// sAddToSpecialStringHeap @ 0x80125088
char *sAddToSpecialStringHeap(const char *str) {
    u32 len = strlen(str);
    u32 checksum = Crc_GenerateCRCCaseSensitive(str, len);
    Entry *e = lbl_80303194;
    u32 i;

    for (i = 0; i < lbl_80303198; i++) {
        if (e->checksum == checksum) {
            return e->str;
        }
        e++;
    }

    {
        char *ret = lbl_8030318C;
        strcpy(ret, str);
        lbl_8030318C = lbl_8030318C + len + 1;
        lbl_80303194[lbl_80303198].checksum = checksum;
        lbl_80303194[lbl_80303198].str = ret;
        lbl_80303198++;
        return ret;
    }
}

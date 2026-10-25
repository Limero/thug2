// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EBC4-0x8012EC50 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
void fn_8012E604(s32, s32, s32);
void fn_8012E228(s32, s32, s32, s32, s32);
void fn_8012EA18(void);
extern char lbl_8029E718[];
u32 strlen(const char *);
int strcmp(const char *, const char *);
void fn_8012EBC4(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    if ((s32) *arg1 == QB_UNKNOWN_0xB075EF6F) {
        fn_8012E604(arg0, arg1, arg2);
    } else {
        strcmp((const char *)((arg0 + strlen((const char *)arg0)) - 3), lbl_8029E718);
        fn_8012E228(arg0, arg1, arg2, arg3, arg4);
    }
    fn_8012EA18();
}

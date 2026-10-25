// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161354-0x80161420 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: ScriptAnnounceNeedToPlaceObjects — script command
// announcing objects need to be placed in a goal. Broadcasts msg.b=0x91 to
// every goal node via fn_8013CC84; win came from flipping fn_80137CB4's
// proto to s32 (return-live arg-setup order).
// Suggested rename: ScriptAnnounceNeedToPlaceObjects.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern char lbl_802A83F8[];
s32 fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8021B554(Unk_9994C3F5 *);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);

typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;

typedef struct {
    u8 b;
    u8 pad0;
    u16 h;
    void *ptr;
    s32 unk8;
    s32 w;
    s8 e;
    char pad1[0x17];
} msg_t;

bool ScriptAnnounceNeedToPlaceObjects(CStruct *pParams, CScript *pScript) {
    search_t sp8;
    msg_t msg;
    s32 ctx;
    s32 mgr;
    void *node;
    register search_t *s0 __asm__("r30");
    register search_t *s1 __asm__("r25");

    s0 = &sp8;
    ctx = *(s32 *)&lbl_80305F9C;
    s0->name = lbl_802A83F8;
    s0->cursor = 0;
    fn_80137CB4(&msg);
    s1 = s0;
    mgr = fn_8021B554(ctx);
    node = (void *)fn_8021D454(ctx, s0, 1);
    if (node != NULL) {
        do {
            msg.b = 0x91;
            msg.w = 2;
            msg.e = 8;
            fn_8013CC84(mgr, fn_8022A9B8(node), &msg);
            node = (void *)fn_8021D4E8(ctx, (void *)&sp8, 1);
        } while (node != NULL);
    }
    s1->name = lbl_802A83F8;
    return true;
}

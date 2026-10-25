// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222368-0x80222538 (464B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    s32 f08, f0C, f10, f14, f18, f1C;
    s32 pad20;
    s32 f24, f28, f2C, f30, f34, f38;
    s32 pad3C;
} req_t;

typedef struct {
    u8 cmd;
    u16 len;
    void *data;
    s32 pad08;
    s32 f4C;
    u8 f50;
    char pad11[0x17];
} msg_t;

extern void fn_80137CB4(Unk_9F066EC1 *);
extern s32 fn_8021E024(void *);
extern s32 fn_80140068(s32, void *, void *);
extern s32 fn_8021F6D4(CStruct *);
extern s32 fn_8021B55C(s32, s32);
extern void fn_8013DE78(void *, Unk_C71E6DE1 *);
extern s32 lbl_80305F9C;

bool ScriptFCFSRequestStartGame(CStruct *pParams, CScript *pScript) {
    req_t req;
    msg_t msg;
    CScript *mgr;
    s32 res;
    s32 t;

    fn_80137CB4(&msg);
    mgr = lbl_80305F9C;
    res = fn_8021E024(mgr);
    req.f10 = fn_80140068(res, QB_SKILL_LEVEL, QB_CHECKSUM);
    req.f14 = fn_80140068(res, QB_FIREBALL_DIFFICULTY, QB_CHECKSUM);
    req.f08 = fn_8021F6D4(mgr);
    req.f0C = fn_80140068(res, QB_TIME_LIMIT, QB_CHECKSUM);
    req.f24 = 0;
    req.f24 = fn_80140068(res, QB_TARGET_SCORE, QB_CHECKSUM);
    req.f18 = fn_80140068(res, QB_PLAYER_COLLISION, QB_CHECKSUM);
    req.f1C = fn_80140068(res, QB_FRIENDLY_FIRE, QB_CHECKSUM);
    req.f28 = fn_80140068(res, QB_STOP_AT_ZERO, QB_CHECKSUM);
    req.f2C = fn_80140068(res, QB_SCORE_RESET, QB_CHECKSUM);
    req.f30 = fn_80140068(res, QB_CTF_GAME_TYPE, QB_CHECKSUM);
    req.f34 = fn_80140068(res, QB_GOALS, QB_CHECKSUM);
    req.f38 = fn_80140068(res, QB_TEAM_GRAFFITI_MODE, QB_CHECKSUM);
    t = fn_8021B55C(mgr, 0);
    msg.data = &req;
    msg.len = 0x34;
    msg.cmd = 0x60;
    msg.f4C = 2;
    msg.f50 = 8;
    fn_8013DE78(t, &msg);
    mgr->unk0x1DC = 1;
    return true;
}

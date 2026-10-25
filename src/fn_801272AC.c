// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801272AC-0x80127358 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct ScriptComponent {
    u32 flags;
    u32 name;
    u32 value;
    struct ScriptComponent *next;
} ScriptComponent;

typedef struct ScriptStructure {
    u32 flags;
    ScriptComponent *head;
} ScriptStructure;

typedef struct ScriptSymbol {
    u8 pad0[2];
    u8 type;
    u8 pad3[9];
    ScriptStructure *structure;
} ScriptSymbol;

void *fn_80125480(u32 name);

ScriptComponent *fn_801272AC(ScriptStructure *arg0, u32 arg1) {
    u32 name;
    ScriptSymbol *symbol;
    ScriptComponent *nested;
    ScriptComponent *result;
    ScriptComponent *node;

    node = arg0->head;
    result = NULL;
    if (node != NULL) {
        do {
            name = node->name;
            if (name == arg1) {
                result = node;
            } else if ((name == 0) && ((node->flags & 0x7F0000) == 0xD0000)) {
                symbol = fn_80125480(node->value);
                if ((symbol != NULL) && (symbol->type == 0xA)) {
                    nested = fn_801272AC(symbol->structure, arg1);
                    if (nested != NULL) {
                        result = nested;
                    }
                }
            }
            node = node->next;
        } while (node != NULL);
    }
    return result;
}

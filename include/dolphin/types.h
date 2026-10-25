// Compatibility redirect: game scalar types now live in include/types.h.
// This file exists only because frozen SDK headers under
// libs/dolphin/include spell #include "dolphin/types.h" — with -I include
// on the game compile line that path must still resolve to the game types
// (which lack BOOL/TRUE/FALSE). Game sources include "types.h" directly;
// do not add new references to this path.
#include "../types.h"

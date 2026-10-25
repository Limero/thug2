#include <dolphin/dolphin.h>
#include <dolphin/ax.h>

#include "__ax.h"

extern AXPROFILE* __AXProfile;
extern u32 __AXMaxProfiles;
extern u32 __AXCurrentProfile;
extern u32 __AXProfileInitialized;

AXPROFILE* __AXGetCurrentProfile(void)
{
    AXPROFILE* profile;

    if (__AXProfileInitialized != 0U)
    {
        profile = &__AXProfile[__AXCurrentProfile];
        __AXCurrentProfile += 1;
        __AXCurrentProfile %= __AXMaxProfiles;
        return profile;
    }
    return 0;
}

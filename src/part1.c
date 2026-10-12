#include "global.h"
#include "part1.h"

// Reuse the engine's RTC-updated daily seed, without adding a clock or save field.
u16 GetPart1DailyQuestion(void)
{
    return gSaveBlock1Ptr->dailySeed % 3;
}

// Base experience is calculated by Cmd_getexp. Recipient multipliers remain upstream.
void CalculatePart1ExpShares(u32 baseExp, u32 participantCount, u32 legacyShareCount, bool32 modernEnabled, u32 *participantExp, u32 *sharedExp)
{
    if (modernEnabled)
    {
        *participantExp = baseExp ? baseExp : 1;
        *sharedExp = baseExp / 2 ? baseExp / 2 : 1;
    }
    else if (legacyShareCount)
    {
        *participantExp = participantCount ? baseExp / 2 / participantCount : 0;
        *sharedExp = baseExp / 2 / legacyShareCount;
        if (*participantExp == 0)
            *participantExp = 1;
        if (*sharedExp == 0)
            *sharedExp = 1;
    }
    else
    {
        *participantExp = participantCount ? baseExp / participantCount : 0;
        if (*participantExp == 0)
            *participantExp = 1;
        *sharedExp = 0;
    }
}

#ifndef GUARD_PART1_H
#define GUARD_PART1_H
u16 GetPart1DailyQuestion(void);
void CalculatePart1ExpShares(u32 baseExp, u32 participantCount, u32 legacyShareCount, bool32 modernEnabled, u32 *participantExp, u32 *sharedExp);
#endif

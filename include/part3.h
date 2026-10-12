#ifndef GUARD_PART3_H
#define GUARD_PART3_H
u16 Part3EnteiAfterBattle(u16 state, u8 outcome);
u16 Part3EnteiAfterHallOfFame(u16 state);
void BeginPart3EnteiBattle(void);
void FinishPart3EnteiBattle(void);
void SyncPart3EnteiObject(void);
void ResetPart3EnteiAfterHallOfFame(void);
void GetPart3LeadHotSpringType(void);
struct ScriptContext;
void StopDefeatedRoute113Trainers(struct ScriptContext *ctx);
#endif

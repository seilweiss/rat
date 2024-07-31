#ifndef XRUMBLEMANAGER_H
#define XRUMBLEMANAGER_H

#include "xRumbleEmitter.h"
#include "xScrFx.h"
#include "xPad.h"

namespace xRumble {

struct effectInternal
{
    const emitterBase* pEmitter;
    F32 timeToLive;
    F32 prevMagFraction;
    cameraFX* cameraEffect;
    bool rumbleForever;

    void updateCameraShake(F32 intensity);
    void EndCameraShake();
    F32 GetIntensity(const xVec3& playerPos);
};

struct padInfo
{
    effectInternal m_effects[16];
    effectInternal* m_currentExclusive;

    void FindNewExclusive();
};

class Manager
{
public:
    void store(padInfo* pInfo, const emitterBase* pEmitter, effectInternal* pEffectInternal, F32 timeToLive, bool rumbleForever);
    bool Add(xPad* pad, emitterBase* pEmitter);
    bool Stop(xPad* pad, emitterBase* pEmitter);
    void Update(xPad* pad, const xVec3& playerPos, F32 timeElapsed, bool bPauseState);
    static Manager& Get();
    void Reset();
    Manager();
    void StopRumbling();
    void StopCameraShake(S32 padNum);
    void StopCameraShake();

private:
    padInfo m_padInfo[4];
};

}

#endif

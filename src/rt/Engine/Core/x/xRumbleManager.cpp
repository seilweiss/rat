#include "xRumbleManager.h"

#include "xGlobals.h"
#include "zPlayer.h"

#include <string.h>

namespace xRumble {

static const S32 kMaxRumblingPads = 4;
static const F32 RUMBLELIVE_MAXTHRESHOLD = 4.0f;

void effectInternal::updateCameraShake(F32 intensity)
{
    const effectAsset* pAsset = pEmitter->pEffectAsset;
    if (pAsset->type != 1 || !xfeq0(intensity)) {
        cameraEffect->shake.magnitude = intensity * pAsset->shakeMagnitude;
        cameraEffect->shake.rotate_magnitude = intensity * pAsset->shakeRotationalMagnitude;
    } else if (!xfeq0(prevMagFraction)) {
        cameraEffect->shake.dampenRate = prevMagFraction / 20.0f;
    } else {
        cameraEffect->shake.magnitude -= cameraEffect->shake.dampenRate * pAsset->shakeMagnitude;
        cameraEffect->shake.rotate_magnitude -= cameraEffect->shake.dampenRate * pAsset->shakeRotationalMagnitude;
        if (cameraEffect->shake.magnitude < 0.0f) {
            cameraEffect->shake.magnitude = 0.0f;
        }
        if (cameraEffect->shake.rotate_magnitude < 0.0f) {
            cameraEffect->shake.rotate_magnitude = 0.0f;
        }
    }
}

void effectInternal::EndCameraShake()
{
    xASSERT(62, cameraEffect);

    xCameraFXShakeEnd(cameraEffect, 0.3f);
    cameraEffect = NULL;
    
    prevMagFraction = 0.0f;
}

F32 effectInternal::GetIntensity(const xVec3& playerPos)
{
    F32 intensity = 0.0f;
    const effectAsset* pAsset = pEmitter->pEffectAsset;

    if (pEmitter->GetIntensity(playerPos, intensity)) {
        intensity *= pAsset->GetIntensity(pEmitter->pEffectAsset->time - timeToLive, pEmitter->pEffectAsset->time);

        F32 magFraction = intensity / pAsset->intensity;
        if (cameraEffect) {
            updateCameraShake(magFraction);
        } else if ((!xfeq0(pAsset->shakeMagnitude) || !xfeq0(pAsset->shakeRotationalMagnitude)) && !xfeq0(pAsset->shakeCycleMax)) {
            cameraEffect = xCameraFXShakeForever(magFraction * pAsset->shakeMagnitude,
                                                 pAsset->shakeCycleMax,
                                                 magFraction * pAsset->shakeRotationalMagnitude,
                                                 0.0f,
                                                 NULL,
                                                 NULL,
                                                 pAsset->shakeY);
        }

        prevMagFraction = magFraction;
    } else if (cameraEffect) {
        EndCameraShake();
    }

    return intensity;
}

void padInfo::FindNewExclusive()
{
    m_currentExclusive = NULL;

    U32 maxPriority = 0;
    for (U32 i = 0; i < 16; i++) {
        if (m_effects[i].pEmitter && (m_effects[i].rumbleForever || m_effects[i].timeToLive > 0.0f)) {
            U32 currentPriority = m_effects[i].pEmitter->pEffectAsset->priority;
            if (currentPriority > maxPriority) {
                m_currentExclusive = &m_effects[i];
                maxPriority = currentPriority;
            }
        }
    }
}

void Manager::store(padInfo* pInfo, const emitterBase* pEmitter, effectInternal* pEffectInternal, F32 timeToLive, bool rumbleForever)
{
    pEffectInternal->pEmitter = pEmitter;
    pEffectInternal->timeToLive = timeToLive;
    pEffectInternal->rumbleForever = rumbleForever;

    if (!pInfo->m_currentExclusive && pEffectInternal->pEmitter->pEffectAsset->priority > 0) {
        pInfo->m_currentExclusive = pEffectInternal;
    }
}

bool Manager::Add(xPad* pad, emitterBase* pEmitter)
{
    xASSERTONCE(119, pEmitter);
    if (!pEmitter) return false;
    if (!pad) return false;
    
    S32 counter = 0;
    for (S32 i = 0; i < xglobals->players.size(); i++) {
        if (xglobals->players[i]->IsDead() && pEmitter->pEffectAsset->id != xStrHash("VibrationSet")) {
            counter++;
        }
    }
    if (counter == xglobals->players.size()) return false;

    xASSERTMSG(137, pad->port != -1, "There is no controller inserted/initialized for this pad !");
    xASSERTMSG(138, (pad->port > -1 && pad->port < kMaxRumblingPads), "Rumbling is not supported for this pad");
    if (pad->port == -1) return false;

    padInfo* pInfo = &m_padInfo[pad->port];
    F32 timeToLive = pEmitter->pEffectAsset->time;
    bool rumbleForever = (pEmitter->pEffectAsset->time == 0.0f);
    xASSERTFMT(149, (!(rumbleForever || timeToLive > RUMBLELIVE_MAXTHRESHOLD )),
               "Rumble effect was started with lifetime higher than %f", RUMBLELIVE_MAXTHRESHOLD);
    
    effectInternal* currentExclusive = pInfo->m_currentExclusive;

    const emitterBase* pCurrentEmitter = NULL;
    if (pInfo->m_currentExclusive) {
        pCurrentEmitter = pInfo->m_currentExclusive->pEmitter;
    }
    if (pCurrentEmitter && pEmitter->pEffectAsset->id != 0 && pEmitter->pEffectAsset->id == pCurrentEmitter->pEffectAsset->id) {
        store(pInfo, pEmitter, pInfo->m_currentExclusive, timeToLive, rumbleForever);
        pInfo->m_currentExclusive = NULL;
        if (pEmitter->pEffectAsset->priority == 0) {
            pInfo->FindNewExclusive();
        }
        return true;
    }

    U32 effectPriority = pEmitter->pEffectAsset->priority;
    if (currentExclusive &&
        ((effectPriority != 0 && currentExclusive->pEmitter->pEffectAsset->priority >= effectPriority) || effectPriority == 0) &&
        (currentExclusive->rumbleForever || currentExclusive->timeToLive >= timeToLive)) {
        return false;
    }

    effectInternal* freeEffect = NULL;
    for (U32 i = 0; i < 16; i++) {
        if (pEmitter->pEffectAsset->id != 0 &&
            pInfo->m_effects[i].pEmitter &&
            pEmitter->pEffectAsset->id == pInfo->m_effects[i].pEmitter->pEffectAsset->id) {
            store(pInfo, pEmitter, &pInfo->m_effects[i], timeToLive, rumbleForever);
            return true;
        }
        if (!freeEffect && !pInfo->m_effects[i].rumbleForever && pInfo->m_effects[i].timeToLive <= 0.0f) {
            freeEffect = &pInfo->m_effects[i];
        }
    }
    xASSERTMSG(184, freeEffect, "number of current rumblings has exceeded the limit.");
    if (freeEffect) {
        store(pInfo, pEmitter, freeEffect, timeToLive, rumbleForever);
    }
    return true;
}

bool Manager::Stop(xPad* pad, emitterBase* pEmitter)
{
    padInfo* pInfo = &m_padInfo[pad->port];
    for (U32 i = 0; i < 16; i++) {
        if (pInfo->m_effects[i].pEmitter && pEmitter->pEffectAsset == pInfo->m_effects[i].pEmitter->pEffectAsset) {
            pInfo->m_effects[i].timeToLive = 0.0f;
            pInfo->m_effects[i].rumbleForever = false;
            return true;
        }
    }
    return false;
}

void Manager::Update(xPad* pad, const xVec3& playerPos, F32 timeElapsed, bool bPauseState)
{
    if (!pad || pad->port >= kMaxRumblingPads) return;

    padInfo* pInfo = &m_padInfo[pad->port];
    for (U32 i = 0; i < 16; i++) {
        if (pInfo->m_effects[i].pEmitter &&
            (!bPauseState || pInfo->m_effects[i].pEmitter->pEffectAsset->rumbleInPause) &&
            pInfo->m_effects[i].timeToLive >= 0.0f) {
            pInfo->m_effects[i].timeToLive -= timeElapsed;
        }
    }

    F32 intensity = 0.0f;
    if (pInfo->m_currentExclusive) {
        F32 timeToLive = pInfo->m_currentExclusive->timeToLive;
        if (pInfo->m_currentExclusive->rumbleForever) {
            if (pInfo->m_currentExclusive &&
                (!bPauseState || pInfo->m_currentExclusive->pEmitter->pEffectAsset->rumbleInPause)) {
                intensity = pInfo->m_currentExclusive->GetIntensity(playerPos);
            }
        } else {
            pInfo->FindNewExclusive();
            if (pInfo->m_currentExclusive &&
                (!bPauseState || pInfo->m_currentExclusive->pEmitter->pEffectAsset->rumbleInPause)) {
                intensity = pInfo->m_currentExclusive->GetIntensity(playerPos);
            }
        }
    } else {
        for (U32 i = 0; i < 16; i++) {
            if (pInfo->m_effects[i].rumbleForever || pInfo->m_effects[i].timeToLive > 0.0f) {
                if (!bPauseState || pInfo->m_effects[i].pEmitter->pEffectAsset->rumbleInPause) {
                    intensity += pInfo->m_effects[i].GetIntensity(playerPos);
                }
            } else if (pInfo->m_effects[i].cameraEffect) {
                pInfo->m_effects[i].EndCameraShake();
            }
        }
    }
    if (intensity > 1.0f) {
        intensity = 1.0f;
    }
    if (xfeq0(intensity)) {
        iPadStopRumble(pad);
    } else {
        iPadStartRumble(pad, intensity);
    }
}

Manager& Manager::Get()
{
    static Manager rumbleManager;
    return rumbleManager;
}

void Manager::Reset()
{
    StopRumbling();
    StopCameraShake();
    memset(this, 0, sizeof(Manager));
}

Manager::Manager()
{
    memset(this, 0, sizeof(Manager));
}

void Manager::StopRumbling()
{
    for (S32 i = 0; i < kMaxRumblingPads; i++) {
        iPadStopRumble(&mPad[i]);
    }
}

void Manager::StopCameraShake(S32 padNum)
{
    padInfo* pInfo = &m_padInfo[padNum];
    for (U32 j = 0; j < 16; j++) {
        if (pInfo->m_effects[j].cameraEffect) {
            pInfo->m_effects[j].EndCameraShake();
        }
    }
}

void Manager::StopCameraShake()
{
    for (S32 i = 0; i < kMaxRumblingPads; i++) {
        StopCameraShake(i);
    }
}

}

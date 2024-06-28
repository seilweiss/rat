#ifndef ZEVENT_H
#define ZEVENT_H

#include "xEvent.h"

enum en_xEventTags
{
    eEventUnknown,
    eEventEnable,
    eEventDisable,
    eEventVisible,
    eEventInvisible,
    eEventEnterPlayer,
    eEventExitPlayer,
    eEventDebugReset,
    eEventControlOff,
    eEventControlOn,
    eEventReset,
    eEventIncrement,
    eEventDecrement,
    UNUSED_eEventOpen,
    UNUSED_eEventClose,
    eEventToggle,
    eEventTeleportPlayer,
    eEventOutOfBounds,
    eEventRun,
    eEventStop,
    eEventExpired,
    UNUSED_eEventMove,
    eEventDestroy,
    eEventPause,
    eEventPlay,
    UNUSED_eEventPlayOne,
    eEventPlayMaybe,
    UNUSED_eEventRoomStart,
    UNUSED_eEventInvalidate,
    UNUSED_eEventTilt,
    eEventUntilt,
    eEventArrive,
    eEventMount,
    eEventDismount,
    UNUSED_eEventBreak,
    eEventPickup,
    eEventKilled,
    eEventKill,
    eEventOn,
    eEventOff,
    eEventNPCPatrol,
    eEventNPCPatrolOff,
    eEventLeverSwitchTurnedOn,
    eEventLeverSwitchTurnedOff,
    eEventNPCDetectOn,
    eEventNPCDetectOff,
    eEventNPCChaseOn,
    eEventNPCChaseOff,
    eEventNPCAttackOn,
    eEventNPCAttackOff,
    UNUSED_eEventNPCRespawn,
    eEventPlayerDeath,
    UNUSED_eEventGiveChance,
    UNUSED_eEventGiveShinyObjects,
    UNUSED_eEventGiveHealth,
    eEventPress,
    eEventUnpress,
    eEventArriveHalfway,
    eEventHit,
    eEventAttachTo,
    eEventEvaluate,
    eEventTrue,
    eEventFalse,
    eEventPadPressX,
    eEventPadPressSquare,
    eEventPadPressO,
    eEventPadPressTriangle,
    eEventPadPressL1,
    eEventPadPressL2,
    eEventPadPressR1,
    eEventPadPressR2,
    eEventPadPressStart,
    eEventPadPressSelect,
    eEventPadPressUp,
    eEventPadPressDown,
    eEventPadPressRight,
    eEventPadPressLeft,
    eEventFontBackdropOn,
    eEventFontBackdropOff,
    eEventUISelect,
    eEventUIUnselect,
    eEventUIFocusOn,
    eEventUIFocusOff,
    eEventCollisionOn,
    eEventCollisionOff,
    eEventCollision_Visible_On,
    eEventCollision_Visible_Off,
    eEventSceneBegin,
    eEventSceneEnd,
    eEventRoomBegin,
    eEventRoomEnd,
    UNUSED_eEventLobMasterShoot,
    UNUSED_eEventLobMasterReset,
    eEventFallToDeath,
    eEventUIFocusOn_Select,
    eEventUIFocusOff_Unselect,
    eEventDispatcher_PadCfg_PresetA,
    eEventDispatcher_PadCfg_PresetB,
    eEventDispatcher_PadCfg_PresetC,
    eEventDispatcher_PadCfg_PresetD,
    eEventDispatcher_PadVibrateOn_P1,
    eEventDispatcher_PadVibrateOff_P1,
    eEventDispatcher_SoundMono,
    eEventDispatcher_SoundStereo,
    eEventDispatcher_SoundMasterIncrease,
    eEventDispatcher_SoundMasterDecrease,
    eEventDispatcher_SoundMusicIncrease,
    eEventDispatcher_SoundMusicDecrease,
    eEventDispatcher_SoundSFXIncrease,
    eEventDispatcher_SoundSFXDecrease,
    eEventDispatcher_IntroState_Sony,
    eEventDispatcher_IntroState_Publisher,
    eEventDispatcher_IntroState_Developer,
    eEventDispatcher_IntroState_License,
    eEventDispatcher_IntroState_Count,
    eEventDispatcher_TitleState_Start,
    eEventDispatcher_TitleState_Attract,
    eEventDispatcher_TitleState_Count,
    eEventDispatcher_LoadState_SelectMemCard,
    eEventDispatcher_LoadState_SelectSlot,
    eEventDispatcher_LoadState_Loading,
    UNUSED_eEventDispatcher_LoadState_Count,
    eEventDispatcher_OptionsState_Options,
    UNUSED_eEventDispatcher_OptionsState_Count,
    eEventDispatcher_SaveState_SelectMemCard,
    eEventDispatcher_SaveState_SelectSlot,
    eEventDispatcher_SaveState_Saving,
    UNUSED_eEventDispatcher_SaveState_Count,
    eEventDispatcher_PauseState_Pause,
    eEventDispatcher_PauseState_Options,
    UNUSED_eEventDispatcher_PauseState_Count,
    eEventDispatcher_GameState_FirstTime,
    eEventDispatcher_GameState_Play,
    eEventDispatcher_GameState_LoseChance,
    eEventDispatcher_GameState_GameOver,
    eEventDispatcher_GameState_SceneSwitch,
    eEventDispatcher_GameState_Dead,
    eEventDispatcher_SetIntroState_Sony,
    eEventDispatcher_SetIntroState_Publisher,
    eEventDispatcher_SetIntroState_Developer,
    eEventDispatcher_SetIntroState_License,
    eEventDispatcher_SetIntroState_Count,
    eEventDispatcher_SetTitleState_Start,
    eEventDispatcher_SetTitleState_Attract,
    eEventDispatcher_SetTitleState_Count,
    eEventDispatcher_SetLoadState_SelectMemCard,
    eEventDispatcher_SetLoadState_SelectSlot,
    eEventDispatcher_SetLoadState_Loading,
    eEventDispatcher_SetLoadState_Count,
    eEventDispatcher_SetOptionsState_Options,
    eEventDispatcher_SetOptionsState_Count,
    eEventDispatcher_SetSaveState_SelectMemCard,
    eEventDispatcher_SetSaveState_SelectSlot,
    eEventDispatcher_SetSaveState_Saving,
    eEventDispatcher_SetSaveState_Count,
    eEventDispatcher_SetPauseState_Pause,
    eEventDispatcher_SetPauseState_Options,
    eEventDispatcher_SetPauseState_Count,
    eEventDispatcher_SetGameState_FirstTime,
    eEventDispatcher_SetGameState_Play,
    eEventDispatcher_SetGameState_LoseChance,
    eEventDispatcher_SetGameState_GameOver,
    eEventDispatcher_SetGameState_SceneSwitch,
    eEventDispatcher_SetGameState_Dead,
    UNUSED_eEventDigup,
    eEventDispatcher_GameState_Exit,
    eEventDispatcher_SetGameState_Exit,
    UNUSED_eEventLobMasterShootFromWidget,
    eEventDispatcher_SLBack,
    eEventDispatcher_SLCancel,
    eEventDispatcher_SLRetry,
    eEventDispatcher_SLSelectCard,
    eEventDispatcher_SLSelectSlot,
    eEventDispatcher_SLOkay,
    UNUSED_eEventVilHurtBoss,
    UNUSED_eEventAttack,
    UNUSED_eEventAttackOn,
    UNUSED_eEventAttackOff,
    eEventDrop,
    eEventUIAddChar,
    eEventUIDelChar,
    eEventUIStringEmpty,
    eEventUIStringFull,
    eEventUISendStringAsCheat,
    eEventUISetMaxChars,
    eEventUICheatOK,
    eEventUICheatBad,
    UNUSED_eEventVilReport_StartingChase,
    UNUSED_eEventVilReport_StartingAttack,
    UNUSED_eEventVilReport_StartingRetreat,
    eEventPreload,
    eEventDone,
    eEventArcto,
    UNUSED_eEventDigupReaction,
    eEventDispatcher_StoreCheckPoint,
    eEventAnimPlay,
    eEventAnimPlayLoop,
    eEventAnimStop,
    eEventAnimPause,
    eEventAnimResume,
    eEventAnimTogglePause,
    eEventAnimPlayRandom,
    eEventAnimPlayMaybe,
    eEventSetSpeed,
    eEventAccelerate,
    eEventMoveToTarget,
    eEventSwingerFollow,
    eEventImpact,
    eEventEffectTurnedOn,
    eEventEffectTurnedOff,
    eEventUIReset,
    eEventSetScaleFactor,
    eEventEnterEntity,
    eEventExitEntity,
    eEventEnterEntityFLAG,
    eEventExitEntityFLAG,
    eEventDrivenby,
    UNUSED_eEventFollowTarget,
    UNUSED_eEventFaceTarget,
    UNUSED_eEventWatchTarget,
    UNUSED_eEventCarChangeLaneRight,
    UNUSED_eEventCarChangeLaneLeft,
    UNUSED_eEventCarStart,
    UNUSED_eEventCarSetSwerveMode,
    eEventIncreaseSpeed,
    eEventDecreaseSpeed,
    eEventStartMoving,
    eEventStopMoving,
    eEventSwoosh,
    eEventTurretDestroyed,
    eEventNPCSpeakStop,
    eEventStartRumbleEffect,
    UNUSED_eEventNavigateTo,
    eEventNPCSpeakStart,
    eEventNPCAlert,
    eEventNPCPatrolDelay,
    eEventNPCScrambleActionEnd,
    UNUSED_eEventVilFakeChaseOff,
    UNUSED_eEventBossMMPushButton,
    UNUSED_eEventVilReport_DecayComplete,
    UNUSED_eEventVilGuardWidget,
    eEventTextureAnimateOn,
    eEventTextureAnimateOff,
    eEventTextureAnimateToggle,
    eEventColorEffectOn,
    eEventColorEffectOff,
    eEventColorEffectToggle,
    eEventSetTextureAnimGroup,
    eEventSetTextureAnimSpeed,
    eEventTextureAnimateStep,
    eEventEmit,
    eEventEmitted,
    UNUSED_eEventTranslucentOn,
    UNUSED_eEventTranslucentOff,
    UNUSED_eEventTranslucentToggle,
    eEventZipLineEnvDamage,
    UNUSED_eEventVilGangTalkOff,
    eEventGivePowerUp,
    UNUSED_eEventRaceTimerReset,
    UNUSED_eEventFireCruiseBubble,
    UNUSED_eEventCarSuccessAnimPlay,
    UNUSED_eEventCarFailureAnimPlay,
    eEventDisableGroupContents,
    UNUSED_eEventNPCCharge,
    eEventOccludeOn,
    eEventOccludeOff,
    UNUSED_eEventRaceTimerPause,
    UNUSED_eEventRaceTimerResume,
    UNUSED_eEventRaceTimerSetBestTime,
    UNUSED_eEventRaceTimerWarning1,
    UNUSED_eEventRaceTimerWarning2,
    UNUSED_eEventRaceTimerWarning3,
    UNUSED_eEventRingChallengeStart,
    UNUSED_eEventCarStop,
    UNUSED_eEventRingChallengeRun,
    UNUSED_eEventRingChallengeReset,
    UNUSED_eEventRingChallengeSuccess,
    UNUSED_eEventRingChallengeFailed,
    UNUSED_eEventFormationChanged,
    UNUSED_eEventChargeResume,
    UNUSED_eEventChargePause,
    UNUSED_eEventNPCChargeStop,
    UNUSED_eEventNPCChargeCompleted,
    UNUSED_eEventFormationChargeStart,
    UNUSED_eEventSituationPlayerSuccess,
    UNUSED_eEventSituationPlayerFailure,
    eEventDispatcher_ShowHud,
    eEventDispatcher_HideHud,
    eEventDispatcher_FadeOut,
    eEventSetRain,
    eEventSetSnow,
    eEventScriptNoop,
    eEventScriptReset,
    UNUSED_eEventWaitForInput,
    eEventPlayMovie,
    UNUSED_eEventCelebrationAnimPlay,
    eEventDispatcher_SetGameState_GameStats,
    eEventMusicNewSong,
    eEventForward,
    eEventReverse,
    UNUSED_eEventDeprecatedRumbleTest,
    UNUSED_eEventDeprecatedRumbleLight,
    UNUSED_eEventDeprecatedRumbleMedium,
    UNUSED_eEventDeprecatedRumbleHeavy,
    eEventDispatcherScreenAdjustON,
    eEventDispatcherScreenAdjustOFF,
    eEventSetSkyDome,
    eEventConnectToChild,
    UNUSED_eEventDuploWaveBegin,
    UNUSED_eEventDuploWaveComplete,
    UNUSED_eEventDuploNPCBorn,
    UNUSED_eEventDuploNPCKilled,
    UNUSED_eEventDuploExpiredMaxNPC,
    UNUSED_eEventDuploPause,
    UNUSED_eEventDuploResume,
    eEventSetGoo,
    UNUSED_eEventNPCScript_ScriptBegin,
    UNUSED_eEventNPCScript_ScriptEnd,
    UNUSED_eEventNPCScript_ScriptReady,
    UNUSED_eEventNPCScript_Halt,
    UNUSED_eEventNPCScript_SetPos,
    UNUSED_eEventNPCScript_SetDir,
    UNUSED_eEventNPCScript_LookNormal,
    UNUSED_eEventNPCScript_LookAlert,
    UNUSED_eEventNPCScript_FaceWidget,
    UNUSED_eEventNPCScript_FaceWidgetDone,
    UNUSED_eEventNPCScript_GotoWidget,
    UNUSED_eEventNPCScript_GotoWidgetDone,
    UNUSED_eEventNPCScript_AttackWidget,
    UNUSED_eEventNPCScript_AttackWidgetDone,
    UNUSED_eEventNPCScript_FollowWidget,
    UNUSED_eEventNPCScript_PlayAnim,
    UNUSED_eEventNPCScript_PlayAnimDone,
    UNUSED_eEventNPCScript_LeadPlayer,
    eEventSetText,
    eEventStartConversation,
    eEventEndConversation,
    eEventSwitch,
    eEventAddText,
    eEventClearText,
    UNUSED_eEventOpenTBox,
    UNUSED_eEventCloseTBox,
    eEventTalkBox_OnSignal0,
    eEventTalkBox_OnSignal1,
    eEventTalkBox_OnSignal2,
    eEventTalkBox_OnSignal3,
    eEventTalkBox_OnSignal4,
    eEventTalkBox_OnSignal5,
    eEventTalkBox_OnSignal6,
    eEventTalkBox_OnSignal7,
    eEventTalkBox_OnSignal8,
    eEventTalkBox_OnSignal9,
    eEventTalkBox_StopWait,
    eEventTalkBox_OnStart,
    eEventTalkBox_OnStop,
    eEventHit_Melee,
    eEventHit_BubbleBounce,
    eEventHit_BubbleBash,
    eEventHit_BubbleBowl,
    eEventHit_PatrickSlam,
    eEventHit_Throw,
    eEventHit_PaddleLeft,
    eEventHit_PaddleRight,
    eEventTaskBox_Initiate,
    eEventTaskBox_SetSuccess,
    eEventTaskBox_SetFailure,
    eEventTaskBox_OnAccept,
    eEventTaskBox_OnDecline,
    eEventTaskBox_OnComplete,
    eEventGenerateBoulder,
    eEventLaunchBoulderAtWidget,
    eEventLaunchBoulderAtPoint,
    eEventLaunchBoulderAtPlayer,
    UNUSED_eEventDuploSuperDuperDone,
    UNUSED_eEventDuploDuperIsDoner,
    UNUSED_eEventBusStopSwitchChr,
    eEventGroupUpdateTogether,
    eEventSetUpdateDistance,
    eEventTranslLocalX,
    eEventTranslLocalY,
    eEventTranslLocalZ,
    eEventTranslWorldX,
    eEventTranslWorldY,
    eEventTranslWorldZ,
    eEventRotLocalX,
    eEventRotLocalY,
    eEventRotLocalZ,
    eEventRotWorldX,
    eEventRotWorldY,
    eEventRotWorldZ,
    eEventTranslLocalXDone,
    eEventTranslLocalYDone,
    eEventTranslLocalZDone,
    eEventTranslWorldXDone,
    eEventTranslWorldYDone,
    eEventTranslWorldZDone,
    eEventRotLocalXDone,
    eEventRotLocalYDone,
    eEventRotLocalZDone,
    eEventRotWorldXDone,
    eEventRotWorldYDone,
    eEventRotWorldZDone,
    eEventCount1,
    eEventCount2,
    eEventCount3,
    eEventCount4,
    eEventCount5,
    eEventCount6,
    eEventCount7,
    eEventCount8,
    eEventCount9,
    eEventCount10,
    eEventCount11,
    eEventCount12,
    eEventCount13,
    eEventCount14,
    eEventCount15,
    eEventCount16,
    eEventCount17,
    eEventCount18,
    eEventCount19,
    eEventCount20,
    UNUSED_eEventSetState,
    eEventEnterMrI,
    eEventEnterFrozone,
    eEventEnterOne,
    eEventEnterAll,
    eEventExitMrI,
    eEventExitFrozone,
    eEventExitOne,
    eEventExitAll,
    eEventGooSetWarb,
    eEventGooSetFreezeDuration,
    eEventGooMelt,
    UNUSED_eEventSetStateRange,
    UNUSED_eEventSetStateDelay,
    UNUSED_eEventSetTransitionDelay,
    UNUSED_eEventNPCFightOn,
    UNUSED_eEventNPCFightOff,
    UNUSED_eEventNPCSplineOKOn,
    UNUSED_eEventNPCSplineOKOff,
    UNUSED_eEventNPCKillQuietly,
    UNUSED_eEventHitHead,
    UNUSED_eEventHitUpperBody,
    UNUSED_eEventHitLeftArm,
    UNUSED_eEventHitRightArm,
    UNUSED_eEventHitLeftLeg,
    UNUSED_eEventHitRightLeg,
    UNUSED_eEventHitLowerBody,
    UNUSED_eEventGiveCurrLevelSocks,
    UNUSED_eEventGiveCurrLevelPickup,
    UNUSED_eEventSetCurrLevelSocks,
    UNUSED_eEventSetCurrLevelPickup,
    eEventTalkBox_OnYes,
    eEventTalkBox_OnNo,
    eEventHit_Cruise,
    UNUSED_eEventDuploKillKids,
    eEventTalkBox_OnSignal10,
    eEventTalkBox_OnSignal11,
    eEventTalkBox_OnSignal12,
    eEventTalkBox_OnSignal13,
    eEventTalkBox_OnSignal14,
    eEventTalkBox_OnSignal15,
    eEventTalkBox_OnSignal16,
    eEventTalkBox_OnSignal17,
    eEventTalkBox_OnSignal18,
    eEventTalkBox_OnSignal19,
    UNUSED_eEventSpongeballOn,
    UNUSED_eEventSpongeballOff,
    eEventLaunchShrapnel,
    eEventSetIntensity,
    eEventSetFrequency,
    eEventNPCSetActiveOn,
    eEventNPCSetActiveOff,
    UNUSED_eEventPlrSwitchCharacter,
    eEventLevelBegin,
    eEventSceneReset,
    eEventSceneEnter,
    UNUSED_eEventSituationDestroyedTiki,
    UNUSED_eEventSituationDestroyedRobot,
    UNUSED_eEventSituationSeeWoodTiki,
    UNUSED_eEventSituationSeeLoveyTiki,
    UNUSED_eEventSituationSeeShhhTiki,
    UNUSED_eEventSituationSeeThunderTiki,
    UNUSED_eEventSituationSeeStoneTiki,
    UNUSED_eEventSituationSeeFodder,
    UNUSED_eEventSituationSeeHammer,
    UNUSED_eEventSituationSeeTarTar,
    UNUSED_eEventSituationSeeGLove,
    UNUSED_eEventSituationSeeMonsoon,
    UNUSED_eEventSituationSeeSleepyTime,
    UNUSED_eEventSituationSeeArf,
    UNUSED_eEventSituationSeeTubelets,
    UNUSED_eEventSituationSeeSlick,
    UNUSED_eEventSituationSeeKingJellyfish,
    UNUSED_eEventSituationSeePrawn,
    UNUSED_eEventSituationSeeDutchman,
    UNUSED_eEventSituationSeeSandyBossUNUSED,
    UNUSED_eEventSituationSeePatrickBoss,
    UNUSED_eEventSituationSeeSpongeBobBoss,
    UNUSED_eEventSituationSeeRobotPlankton,
    eEventUIChangeTexture,
    UNUSED_eEventNPCCheerForMe,
    eEventFastVisible,
    eEventFastInvisible,
    eEventZipLineMount,
    eEventZipLineDismount,
    eEventTarget,
    eEventFire,
    eEventCameraFXShake,
    eEventBulletTime,
    eEventThrown,
    UNUSED_eEventNPCPatrol,
    UNUSED_eEventEnterCruise,
    UNUSED_eEventExitCruise,
    UNUSED_eEventCruiseFired,
    UNUSED_eEventCruiseDied,
    UNUSED_eEventCruiseAddLife,
    UNUSED_eEventCruiseSetLife,
    UNUSED_eEventCruiseResetLife,
    eEventCameraCollideOff,
    eEventCameraCollideOn,
    UNUSED_eEventOnSliding,
    UNUSED_eEventOffSliding,
    eEventTimerSet,
    eEventTimerAdd,
    UNUSED_eEventNPCForceConverseStart,
    UNUSED_eEventMakeASplash,
    eEventCreditsStart,
    eEventCreditsStop,
    eEventCreditsEnded,
    UNUSED_eEventBubbleWipe,
    eEventSetLightKit,
    eEventSetOpacity,
    eEventDispatcher_SetSoundEffect,
    eEventScale,
    eEventSetReference,
    eEventWarpSetWorld,
    eEventWarpSetTask,
    eEventWarpGo,
    eEventSetCount,
    UNUSED_eEventGetDashSpeed,
    eEventDashTrip,
    UNUSED_eEventDashBurst,
    UNUSED_eEventDashFast,
    UNUSED_eEventDashNormal,
    UNUSED_eEventDashSlow,
    UNUSED_eEventTakeSocks,
    eEventDispatcherAssert,
    UNUSED_eEventBorn,
    eEventPlatPause,
    eEventPlatUnpause,
    UNUSED_eEventStoreOptions,
    UNUSED_eEventRestoreOptions,
    eEventUISetMotion,
    eEventUIMotionFinished,
    eEventUIMotionLoop,
    eEventDestructibleLaunch,
    eEventDestructibleRespawn,
    UNUSED_eEventKaboomStart,
    UNUSED_eEventKaboomStop,
    UNUSED_eEventNPCAttack,
    UNUSED_eEventNPCDefend,
    UNUSED_eEventTrainCarSpeed,
    UNUSED_eEventTrainJunctOut1,
    UNUSED_eEventTrainJunctOut2,
    UNUSED_eEventTrainJunctSwitch,
    UNUSED_eEventTrainJunctPassed,
    UNUSED_eEventTrainCarDetach,
    UNUSED_eEventTrainCarExplode,
    eEventNet_InitNetAPI,
    eEventNet_UpdateConnection,
    eEventNet_UpdateOnlineTask,
    eEventNet_UpdateUserList,
    eEventNet_CheckForNewContent,
    eEventNet_SelectDevice,
    eEventNet_SelectContent,
    eEventNet_VerifyContent,
    eEventNet_RemoveContent,
    eEventNet_SelectDeviceAfterRemove,
    eEventNet_ConfirmUseContentIdx,
    eEventNet_ConfirmNoUseContentIdx,
    eEventNet_NoContentInstalled,
    eEventNet_NoContentAvailable,
    eEventNet_NewContentAvailable,
    eEventSceneEnableDraw,
    eEventSceneDisableDraw,
    eEventLightningStart,
    eEventLightningStop,
    UNUSED_eEventChangeBossUIStage,
    eEventStaticCameraStart,
    eEventStaticCameraEnd,
    eEventSetCameraStartOrientation,
    UNUSED_eEventNMESetMovepointPath,
    UNUSED_eEventNMEScareBegin,
    UNUSED_eEventNMEScareSkip,
    UNUSED_eEventNMESetMovepointGroup,
    eEventVentSetStateIdle,
    eEventVentSetStateWarn,
    eEventVentSetStateDamage,
    eEventVentSetStateOff,
    eEventWaterhoseStart,
    eEventWaterhoseStop,
    eEventWaterhoseSetLength,
    eEventCarried,
    eEventExplode,
    eEventJumpTo,
    eEventJumpOnSpawn,
    eEventPlayerHit,
    eEventStartFade,
    eEventFadeDownDone,
    eEventFadeUpDone,
    eEventBounce,
    eEventLaunchNPC,
    eEventUpgradePowerUp,
    UNUSED_eEventBulletStreak,
    eEventSetFollowCameraOrientation,
    eEventHDRFade,
    eEventStart,
    eEventSuccess,
    eEventFailure,
    eEventEnableRestore,
    eEventDisableRestore,
    UNUSED_eEventNPCSpawn,
    eEventSpawnDone,
    eEventSpawnedNPCKilled,
    eEventSpawnedNPCNoHealth,
    eEventSpawnedNPCAllKilled,
    eEventSpawnedNPCAllNoHealth,
    eEventDashTimerSet,
    UNUSED_eEventDashNotOutOfTime,
    eEventDashOutOfTime,
    eEventForceSceneReset,
    UNUSED_eEventNPCActive,
    UNUSED_eEventNPCInactive,
    eEventDuplicatorActive,
    eEventDuplicatorInactive,
    eEventDashEnterTunnel,
    eEventDashExitTunnel,
    eEventStopRumbleEffect,
    eEventDashChaseLasersOn,
    eEventDashChaseLasersOff,
    eEventJumpRandomOnSpawn,
    UNUSED_eEventHit_Cartwheel,
    eEventUIVisible_FocusOn_Select,
    eEventUIFocusOff_Unselect_Invisible,
    eEventCopyReference,
    eEventUIMotionFinishedIn,
    eEventUIMotionFinishedOut,
    eEventUISignalActivateScreen,
    eEventUISignalDeactivateScreen,
    eEventUISignalActivatedScreen,
    eEventUISignalSwitchScreens,
    eEventUISignalStartFadeOut,
    eEventUISignalStartFadeIn,
    eEventUISignalScreenMotionInDone,
    eEventUISignalScreenMotionOutDone,
    UNUSED_eEventUISignalMainBoxInDone,
    UNUSED_eEventUISignalMainBoxOutDone,
    eEventUIResetMotion,
    eEventUIEnableHDR,
    eEventUIDisableHDR,
    eEventUIBrighten,
    eEventUIUnbrighten,
    eEventUISignalDeactivatedScreen,
    UNUSED_eEventNPCDetectAlways,
    UNUSED_eEventNPCDetectNever,
    UNUSED_eEventNPCDetectNormal,
    UNUSED_eEventNPCFightDefault,
    eEventCameraCollidePartial,
    eEventMusicTempSong,
    eEvaluateCounterValue,
    eEventCount0,
    eEventRotToAbsoluteX,
    eEventRotToAbsoluteY,
    eEventRotToAbsoluteZ,
    eEventTriggerAnim,
    eEventTriggeredAnimDone,
    eEventUISignalMore,
    eEventUISignalNoMore,
    eEventUISignalLess,
    eEventUISignalNoLess,
    eEventUISignalUp,
    eEventUISignalDown,
    eEventUISignalSyncToCurrent,
    eEventUISignalEffect,
    UNUSED_eEventFreezePlayer,
    UNUSED_eEventUnfreezePlayer,
    eEventUISignalMapStart,
    eEventUISignalMapEnd,
    eEventTransToAbsoluteX,
    eEventTransToAbsoluteY,
    eEventTransToAbsoluteZ,
    eEventJSPVisibilityIncrement,
    eEventJSPVisibilityDecrement,
    eEventEnterCamera,
    eEventExitCamera,
    eEventPadPressE,
    eEventSetDashJumpParameters,
    UNUSED_eEventViperFacePlayer,
    UNUSED_eEventViperFaceMovement,
    eEventRequestStart,
    eEventUIAutoMenuRun,
    eEventUIAutoMenuRunUp,
    eEventUIAutoMenuRunDown,
    eEventUIAutoMenuRunLeft,
    eEventUIAutoMenuRunRight,
    eEventIncrementSuccess,
    eEventDecrementSuccess,
    eEventIncrementFailed,
    eEventDecrementFailed,
    eEventMusicTempSongStop,
    eEventNPCScrambleActionBegin,
    eEventNPCScrambleAlert,
    eEventNPCSetTurretAttackRadius,
    eEventGooFreezeStart,
    eEventGooMeltStart,
    eEventNPCNotice,
    UNUSED_eEventBossStageSet,
    UNUSED_eEventBossStageBegan,
    UNUSED_eEventBossStageEnded,
    eEventBossStageBeganA,
    eEventBossStageEndedA,
    eEventBossStageBeganB,
    eEventBossStageEndedB,
    eEventBossStageBeganC,
    eEventBossStageEndedC,
    eEventVisibilityCullOn,
    eEventVisibilityCullOff,
    eEventRBandCameraStart,
    eEventRBandCameraEnd,
    UNUSED_eEventMindyStart,
    UNUSED_eEventMindyEnd,
    eEventFlamethrowerStart,
    eEventFlamethrowerStop,
    eEventFlamethrowerSetLength,
    eEventNPCTakeNoDamageOn,
    eEventNPCTakeNoDamageOff,
    UNUSED_eEventStaticCameraStartFOVFilter,
    UNUSED_eEventStaticCameraRestoreFOV,
    eEventUIXboxDemoExitToLauncher,
    eEventSpawn,
    eEventSpawned,
    eEventCreditsSetDest,
    eEventAllowAttractMode,
    eEventDisallowAttractMode,
    UNUSED_eEventRocketAttack,
    eEventCollisionReset,
    eEventAutoSave,
    eEventOpenBonus,
    UNUSED_eEventFlagLevel,
    UNUSED_eEventLevelEnd,
    eEventNet_GetLocalContentDevice,
    eEventDispatcher_PauseGame_Safe,
    eEventOverrideFreqency,
    eEventResetFrequency,
    UNUSED_eEventSetShotDelay,
    UNUSED_eEventSetShotsInGroup,
    eEventDispatcher_UserSelectYes,
    eEventDispatcher_UserSelectNo,
    eEventDispatcher_UserSelectBack,
    UNUSED_eEventLaunchFireWorks,
    eEventDispatcher_UserSelectionReset,
    eEventSetAsBounceBack,
    eEventUIResetUnlockables,
    eEventUISysMessageWaitResponse,
    eEventUISysMessageWaitConfirm,
    eEventUISysMessageConfirm,
    eEventUISysMessageAccept,
    eEventUISysMessageDecline,
    UNUSED_eEventSetAsBounceBack_Cancel,
    eEventDispatcher_PauseGame,
    UNUSED_eEventPattyWagonStartEngine,
    UNUSED_eEventPattyWagonStopEngine,
    UNUSED_eEventSpawnBubblesOn,
    UNUSED_eEventSpawnBubblesOff,
    eEventNet_XBLiveToggleSignIn,
    eEventNet_XBLiveManageFriends,
    eEventApplyOnResetOn,
    eEventApplyOnResetOff,
    eEventSnapTo,
    eEventThrow,
    eEventFirstZipLine,
    eEventFirstLedgeGrab,
    eEventFirstIncredimeterPickup,
    eEventUISparkTrail,
    UNUSED_eEventUIGetBattleScenes,
    UNUSED_eEventUIBattleScenesAvailable,
    UNUSED_eEventUIBattleScenesNotAvailable,
    eEventNet_XBLiveToggleAppearOnline,
    eEventSys_ReturnPrevScreen,
    eEventSys_Nope,
    eEventDispatcher_SubtitlesOn,
    eEventDispatcher_SubtitlesOff,
    eEventUISetBoxMapping,
    UNUSED_eEventTBoxPlayerEjected,
    eEventDamagePlayer,
    eEventFirstHealthPickup,
    UNUSED_eEventTokenPickupComplete,
    eEventDispatcher_LoadSavePromptDead,
    eEventUIFlipVisibility,
    eEventNet_XBLiveRebootToDashboard,
    UNUSED_eEventFirstPowerupPoint,
    UNUSED_eEventUIIsBattleScene,
    UNUSED_eEventUIBattleSceneYes,
    UNUSED_eEventUIBattleSceneNo,
    eEventUILock,
    eEventUIUnlock,
    eEventDrivenbyOff,
    eEventDrivenbyOn,
    eEventUISignalCreditCode,
    eEventUISignalHILogo,
    eEventDispatcher_DisableAutoSave,
    eEventUISignalEnlargeWindow,
    eEventDispatcher_PromptExiting,
    eEventDispatcher_PromptForceExit,
    eEventUISysMessageActionConfirmed,
    eEventUISysMessageActionDeclined,
    eEventUnpause,
    eEventSetColorIntensity,
    eEventStartLightEffect,
    eEventStopLightEffect,
    eEventNPCHasTakenDamage,
    eEventNPCHalfHealth,
    eEventNPCQuarterHealth,
    eEventNPCHitWithoutDamage,
    eEventNPCHasArrived,
    eEventNPCKillsPlayer,
    eEventNPCCeaseToExist,
    eEventNPCPlayAnim,
    eEventNPCRetreatToCover,
    eEventNPCAttackPlayer,
    eEventNPCFreeze,
    eEventNPCThaw,
    eEventNPCMoveTo,
    eEventCameraTransitionBegin,
    eEventCameraTransitionDone,
    eEventNPCEnterSpawn,
    eEventNPCEnterScare,
    eEventNPCStartCustomAV,
    eEventCustomAVAnimStarted,
    eEventCustomAVAnimFinished,
    eEventCustomAVSoundStarted,
    eEventCustomAVSoundFinished,
    eEventCustomAVFinished,
    eEventNPCAttackWidget,
    eEventNPCAttackWidgetForever,
    eEventNPCAttackedWidget,
    eEventNPCFinishedAttackingWidget,
    eEventNPCFindCover,
    eEventNPCEnterDriller,
    eEventDeactivate,
    eEventActivate,
    eEventNPCLeverOn,
    eEventNPCLeverOff,
    eEventNPCLeverIgnore,
    eEventNPCEnterRunningSpawn,
    eEventNPCRespawned,
    eEventLaunchGrub,
    eEventLaunchTGrub,
    eEventNPCEnterDefaultJumpSpawn,
    eEventNPCDeathDamage,
    eEventNPCGotoIdle,
    eEventNPCGotoCombatIdle,
    eEventNPCGotoChase,
    eEventDispatcher_SetPauseType,
    eEventUIJoinDropGame,
    eEventNPCFinishedSpawning,
    eEventNPCScientistScared,
    eEventNPCScientistComputer,
    eEventNPCScientistPoint,
    eEventNPCScientistInvestigate,
    eEventNPCScientistWalk,
    eEventNPCScientistRun,
    eEventNPCScientistKill,
    eEventNPCScientistIdle,
    eEventNPCTakeDamageOn,
    eEventNPCTakeDamageOff,
    eEventSetActiveNavigationMesh,
    eEventNPCIsStuck,
    eEventStopIceGlide,
    eEventEnterAny,
    eEventExitAny,
    eEventPlayerCameraFocusOff,
    eEventPlayerCameraFocusOn,
    eEventNPCEnterIdleSpawn,
    eEventEnterCameraTarget,
    eEventExitCameraTarget,
    eEventSetCounterToCurrentLevel,
    eEventSetCounterToLevelStatus,
    eEventCameraFocusOnAI,
    eEventCameraFocusOnAIReset,
    eEventRotSetOrientation,
    eEventRotGotoOrientation,
    eEventNPCRangerSetFiringPattern,
    eEventRotGotoOrientationDone,
    eEventScaleDone,
    eEventScaleX,
    eEventScaleY,
    eEventScaleZ,
    eEventScaleXDone,
    eEventScaleYDone,
    eEventScaleZDone,
    eEventNPCDrillOff,
    eEventNPCDrillOn,
    eEventCameraTransitionToADone,
    eEventCameraTransitionToBDone,
    eEventSmashMePleaseOn,
    eEventSmashMePleaseOff,
    eEventChangeVolume,
    eEventFadeVolume,
    eEventNPCSetMovementRadius,
    eEventNPCNoMovementRadius,
    eEventNPCDrillDownAndWait,
    eEventNPCEnterCustomAnimSpawn,
    eEventNPCScientistCheer,
    eEventEnableGroupContents,
    eEventStartMovingHalfway,
    eEventSetLightEffectSpeed,
    eEventBlastDoorsOpening,
    eEventBlastDoorsOpened,
    eEventUIHUDOn,
    eEventUIHUDOff,
    eEventUIHUDHealthChange,
    eEventUIHUDMRIExpPointsChange,
    eEventUIHUDMRIExpPointsToUpgradeChange,
    eEventUIHUDMRIPowerUpAdd,
    eEventUIHUDHumanPlayerPauseGame,
    eEventUIHUDAIPlayerPauseGame,
    eEventUIHUDSwitchPlayers,
    eEventNPCBrokeCover,
    eEventUIHUDPauseGame,
    eEventUIHUDResumeGame,
    eEventUIHUDPlayerMRIActive,
    eEventUIHUDPlayerMRIFollow,
    eEventUIHUDPlayerMRICloseFollow,
    eEventUIHUDPlayerMRIStunned,
    eEventUIHUDPlayerMRIGuard,
    eEventUIHUDPlayerFROActive,
    eEventUIHUDPlayerFROFollow,
    eEventUIHUDPlayerFROCloseFollow,
    eEventUIHUDPlayerFROStunned,
    eEventUIHUDPlayerFROGuard,
    eEventUIHUDFROExpPointsChange,
    eEventUIHUDFROExpPointsToUpgradeChange,
    eEventUIHUDFROPowerUpAdd,
    eEventUIHUDMRIPowerUpRemove,
    eEventUIHUDFROPowerUpRemove,
    eEventNPCPlayTaunt,
    eEventNPCFinishedTakingDamage,
    eEventNPCNukeOn,
    eEventNPCNukeOff,
    eEventNPCArrivedAtPointer,
    eEventNPCMoveToReset,
    eEventAvailable,
    eEventUnavailable,
    eEventUIHUDMRIPowerUpUpgrade,
    eEventUIHUDFROPowerUpUpgrade,
    eEventCheckpointActivate,
    eEventObjectNPCCollisionOn,
    eEventObjectNPCCollisionOff,
    eEventUIQuitGame,
    eEventNPCEnterFallingDirtSpawn,
    eEventNPCEnterFallingIceSpawn,
    eEventBossStageBeganD,
    eEventBossStageEndedD,
    eEventCameraYTrackingOn,
    eEventCameraYTrackingReset,
    eEventUIHUDPlayerMRIHealthIncrease,
    eEventUIHUDPlayerMRIHealthDecrease,
    eEventUIHUDPlayerFROHealthIncrease,
    eEventUIHUDPlayerFROHealthDecrease,
    eEventUIHUDGenericIncrease,
    eEventUIHUDGenericDecrease,
    eEventUISysMessageActionCanceled,
    eEventUI_StartNewGame,
    eEventUI_StartNewGameNoCreateGame,
    eEventUI_StartNewGameYesCreateGame,
    eEventNPCTankSetAttackPattern,
    eEventNPCThreeQuarterHealth,
    eEventNPCPoolCreated,
    eEventUISysMessageWaitInfo,
    eEventNPCPoolReset,
    eEventUIModelBarOffsetNext,
    eEventUIModelBarOffsetPrevious,
    eEventBossMinionsDead,
    eEventNPCOneLiner,
    eEventNPCEnterFallingNoFX,
    eEventCreditsEndedBackToMainMenu,
    eEventDestroyAllRubbles,
    eEventNPCSetCloseEnoughToTargetDist,
    eEventBossStageBeganA1,
    eEventBossStageEndedA1,
    eEventBossStageBeganB1,
    eEventBossStageEndedB1,
    eEventBossStageBeganC1,
    eEventBossStageEndedC1,
    eEventBossStageBeganA2,
    eEventBossStageEndedA2,
    eEventBossStageBeganB2,
    eEventBossStageEndedB2,
    eEventBossStageBeganC2,
    eEventBossStageEndedC2,
    eEventBossStageBeganA3,
    eEventBossStageEndedA3,
    eEventBossStageBeganB3,
    eEventBossStageEndedB3,
    eEventBossStageBeganC3,
    eEventBossStageEndedC3,
    eEventNPCScientistInDanger,
    eEventNPCIgnoreAllDamageOn,
    eEventNPCIgnoreAllDamageOff,
    eEventUIEnterControlsScreen,
    eEventSwitchLeverStart,
    eEventUIHUDLeftPlayerDrop,
    eEventPlayerWalkOnDisable,
    eEventPlayerWalkOnEnable,
    eEventSwitchLeverStop,
    eEventUIMainMenuSecondPlayerJoin,
    eEventUIMainMenuSecondPlayerDrop,
    eEventUIHUDRecoveryFRO,
    eEventUIHUDRecoveryMRI,
    eEventDispatcher_PadVibrateOn_P2,
    eEventDispatcher_PadVibrateOff_P2,
    eEventHitFiltered,
    eEventDestroyFiltered,
    eEventUISignalCreditCodeStart,
    eEventSuperMoveStarted,
    eEventSuperMoveFinished,
    eEventNPCAttackWidgetSmashMe,
    eEventDispatcher_SLContinue,
    eEventUISysMessageWaitResponseExtra,
    eEventHeistExecute,
    eEventDetected,
    eEventDistracted,
    eEventCookingMinigameStart,
    eEventCookingMinigameScore,
    eEventAlerted,
    eEventPacified,
    eEventAlertedFromDetected,
    eEventTaskWasCompleted,
    eEventTaskWasFailed,
    eEventTaskWasMadeAvailable,
    eEventTaskFail,
    eEventTaskComplete,
    eEventTaskMakeAvailable,
    eEventTaskMakeRequired,
    eEventTaskMakeBonus,
    eEventMissionWasUnlocked,
    eEventMissionWasCompleted,
    eEventMissionWasFailed,
    eEventMissionUnlock,
    eEventMissionLock,
    eEventDetectionEnable,
    eEventDetectionDisable,
    eEventHeistLookoutStart,
    eEventHeistLookoutStop,
    eEventHeistLookoutXCentered,
    eEventHeistLookoutYCentered,
    eEventHeistLookoutRight,
    eEventHeistLookoutLeft,
    eEventHeistLookoutUp,
    eEventHeistLookoutDown,
    eEventMiniGameWin,
    eEventMiniGameLose,
    eEventMiniGameTie,
    eEventMiniGameStageFinish,
    eEventOpenPath,
    eEventClosePath,
    eEventBlockerOn,
    eEventBlockerOff,
    eEventGangMemberOn,
    eEventGangMemberOff,
    eEventFinishedDistraction,
    eEventDistractionStarted,
    eEventNPCAnimStopped,
    eEventHUDCompassSwapTexture,
    eEventPickupUseStartAction,
    eEventPickupUseStopAction,
    eEventAnalogDeflection,
    eEventAnalogDirection,
    eEventControlOffNoLetterbox,
    eEventHighRateThreshold,
    eEventMedRateThreshold,
    eEventLowRateThreshold,
    eEventNoRateThreshold,
    eEventSwitchNPCWalls,
    eEventSetAttractor,
    eEventSetRepeller,
    eEventDisableAttractor,
    eEventDisableRepeller,
    eEventSetMagneticOn,
    eEventSetMagneticOff,
    eEventMiniGameSetPlayerCount,
    eEventAnalogValue,
    eEventMiniGameEnd,
    eEventMiniGameReset,
    eEventCMG_DDRSuccess,
    eEventCMG_DDRFailure,
    eEventCMG_DDRGroupSuccess,
    eEventCMG_DDRGroupFailure,
    eEventSetBoundAvoidance,
    eEventSetBoundSize,
    eEventMiniGameWinnerP1,
    eEventMiniGameWinnerP2,
    eEventMiniGameWinnerP3,
    eEventMiniGameWinnerP4,
    eEventContextFX,
    eEventPlayerDetected,
    eEventCount
};

#endif

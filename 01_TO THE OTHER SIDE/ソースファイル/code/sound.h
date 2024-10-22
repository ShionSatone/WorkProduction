//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 佐藤根詩音
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,			// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_BGM002,				// BGM2
	SOUND_LABEL_BGM003,				// BGM3
	SOUND_LABEL_BGM004,				// BGM4
	SOUND_LABEL_BGMBOSS,			// BGM_BOSS
	SOUND_LABEL_SE_ENTER000,		// 決定音0
	SOUND_LABEL_SE_WALK000,			// 歩く音0
	SOUND_LABEL_SE_JUMP000,			// ジャンプ音0
	SOUND_LABEL_SE_ENEMY000,		// 踏む音0
	SOUND_LABEL_SE_BUTTON000,		// ボタン音0
	SOUND_LABEL_SE_DAMAGE000,		// ダメージ音0
	SOUND_LABEL_SE_SHADOW000,		// 影切り替え音0
	SOUND_LABEL_SE_GET000,			// アイテムゲット0
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

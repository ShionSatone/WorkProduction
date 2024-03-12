//==============================================================
//
//DirectX[pause.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _PAUSE_H_				//このマクロ定義がされていなかったら
#define _PAUSE_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//タイトルの状態
typedef enum
{
	PAUSESTATE_APPEAR = 0,			//出現状態(点滅)
	PAUSESTATE_NORMAL,				//通常状態
	PAUSESTATE_WAIT,				//出現待ち状態(表示なし)
	PAUSESTATE_MAX
} PAUSESTATE;

//タイトル構造体の定義
typedef struct
{
	PAUSESTATE state;		//状態
	int nCounterState;		//状態管理カウンター
	int nCounterAppear;		//点滅の時間
	bool bUse;				//表示するかしないか
} Pause;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif

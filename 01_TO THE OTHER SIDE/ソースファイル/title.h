//==============================================================
//
//DirectX[title.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _TITLE_H_				//このマクロ定義がされていなかったら
#define _TITLE_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//タイトルの状態
typedef enum
{
	TITLESTATE_APPEAR = 0,			//出現状態(点滅)
	TITLESTATE_NORMAL,				//通常状態
	TITLESTATE_WAIT,				//出現待ち状態(表示なし)
	TITLESTATE_MAX
} TITLESTATE;

//タイトル構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	TITLESTATE state;		//状態
	int nCounterState;		//状態管理カウンター
	int nCounterAppear;		//点滅の時間
	int nCounterColor;		//色の透明度
	int nCounterRank;		//ランキング表示のカウンター
	bool bUse;				//表示するかしないか
} Title;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif

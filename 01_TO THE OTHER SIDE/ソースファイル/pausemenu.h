//==============================================================
//
//DirectX[pausemenu.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _PAUSEMENU_H_				//このマクロ定義がされていなかったら
#define _PAUSEMENU_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,		//ゲームに戻る
	PAUSE_MENU_RETRY,				//ゲームをやり直す
	PAUSE_MENU_QUIT,				//タイトル画面に戻る
	PAUSE_MENU_MAX
} PAUSE_MENU;

//プロトタイプ宣言
void InitPauseMenu(void);
void UninitPauseMenu(void);
void UpdatePauseMenu(void);
void DrawPauseMenu(void);

#endif

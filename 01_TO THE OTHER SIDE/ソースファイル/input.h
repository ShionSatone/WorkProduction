//==============================================================
//
//DirectX[input.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _INPUT_H
#define _INPUT_H

#include"main.h"
#include"Xinput.h"

#pragma comment(lib,"xinput.lib")

//ゲームパッド
typedef enum
{
	BUTTON_UP = 0,		//十字キー上
	BUTTON_DOWN,		//十字キー下
	BUTTON_LEFT,		//十字キー左
	BUTTON_RIGHT,		//十字キー右
	BUTTON_START,		//スタートボタン
	BUTTON_BACK,		//バックボタン
	BUTTON_LSTICK,		//左スティック押し込み
	BUTTON_RSTICK,		//右スティック押し込み
	BUTTON_LB,			//LB
	BUTTON_RB,			//RB
	//BUTTON_01,			//
	//BUTTON_02,			//
	//BUTTON_A,			//A
	//BUTTON_B,			//B
	//BUTTON_X,			//X
	//BUTTON_Y,			//Y
	BUTTON00,

	BUTTON_MAX
} BUTTON;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

HRESULT InitGamepad(void);
void UninitGamepad(void);
void UpdateGamepad(void);
bool GetGamepadPress(BUTTON Key, int nPlayer);
bool GetGamepadTrigger(BUTTON Key, int nPlayer);
bool GetGamepadRelease(BUTTON Key, int nPlayer);

#endif
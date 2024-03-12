//==============================================================
//
//DirectX[input.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"input.h"

//マクロ定義
#define NUM_KEY_MAX		(256)		//キーの最大数
#define NUM_PLAYER		(4)			//プレイヤーの数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイス（キーボード）へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのトリガー情報

XINPUT_STATE g_aButtonState[NUM_KEY_MAX];					//キーボードのプレス情報
XINPUT_STATE g_aButtonStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
XINPUT_STATE g_aButtonStateRelease[NUM_KEY_MAX];			//キーボードのトリガー情報

//==============================================================
//キーボードの初期化処理
//==============================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//==============================================================
//キーボードの終了処理
//==============================================================
void UninitKeyboard(void)
{
	//入力デバイス（キーボード）の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//==============================================================
//キーボードの更新処理
//==============================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];				//キーボードのリリース情報を保存
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];					//キーボードのトリガー情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];																		//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();						//キーボードへのアクセス権を獲得
	}
}

//==============================================================
//キーボードのプレス情報を取得
//==============================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//==============================================================
//キーボードのトリガー情報を取得
//==============================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==============================================================
//キーボードのリリース情報を取得
//==============================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//==============================================================
//ゲームパッドの初期化処理
//==============================================================
HRESULT InitGamepad(void)
{
	//xinputのステートの設定
	XInputEnable(true);
	int nCount;

	for (nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		//メモリーをクリアする
		memset(&g_aButtonState[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_aButtonStateTrigger[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_aButtonStateRelease[nCount], 0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}

//==============================================================
//ゲームパッドの終了処理
//==============================================================
void UninitGamepad(void)
{
	//xinputのステートの設定
	XInputEnable(false);
}

//==============================================================
//ゲームパッドの更新処理
//==============================================================
void UpdateGamepad(void)
{
	XINPUT_STATE aGamepadState[NUM_PLAYER];
	static int nCntSpece;
	int nCntPad;

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//入力デバイスからデータを取得
		if (XInputGetState(nCntPad, &aGamepadState[nCntPad]) == ERROR_SUCCESS)
		{
			g_aButtonStateTrigger[nCntPad].Gamepad.wButtons =
				~g_aButtonState[nCntPad].Gamepad.wButtons
				& aGamepadState[nCntPad].Gamepad.wButtons;		//トリガー

			g_aButtonStateRelease[nCntPad].Gamepad.wButtons =
				((g_aButtonState[nCntPad].Gamepad.wButtons
					^ aGamepadState[nCntPad].Gamepad.wButtons)
					& g_aButtonState[nCntPad].Gamepad.wButtons);	//リリース

			g_aButtonState[nCntPad] = aGamepadState[nCntPad];		//プレス
		}
	}
}

//==============================================================
//キーボードのプレス情報を取得
//==============================================================
bool GetGamepadPress(BUTTON Key, int nPlayer)
{
	return (g_aButtonState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//==============================================================
//キーボードのトリガー情報を取得
//==============================================================
bool GetGamepadTrigger(BUTTON Key, int nPlayer)
{
	return (g_aButtonStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//==============================================================
//キーボードのリリース情報を取得
//==============================================================
bool GetGamepadRelease(BUTTON Key, int nPlayer)
{
	return (g_aButtonStateRelease[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
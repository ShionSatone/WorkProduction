//==============================================================
//
//DirectX[game.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"game.h"
#include"input.h"
#include"bg.h"
#include"player.h"
#include"splayer.h"
#include"block.h"
#include"sblock.h"
#include"enemy.h"
#include"goal.h"
#include"fade.h"
#include"Set.h"
#include"item.h"
#include"remain.h"
#include"pausemenu.h"
#include"exit.h"
#include"effect.h"
#include"particle.h"
#include"sound.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲームの状態
int g_nCounterGameState = 0;				//状態管理カウンター
bool g_bPause = false;						//ポーズ状態のON/OFF
bool g_bStart = true;						//スタートを使用しているか

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitGame(void)
{
	//背景の初期化
	Initbg();

	//プレイヤーの初期化
	InitPlayer();

	//プレイヤー（影）の初期化処理
	InitSPlayer();

	//ゴールの初期化処理
	InitGoal();

	//ブロックの初期化処理
	InitBlock();

	//ブロックの設定処理
	Load();
	Set();

	//ブロック（影）の初期化処理
	InitSBlock();

	//ブロック(影)の設定処理
	SLoad();
	SSet();

	//ボタン
	SetSBlock(D3DXVECTOR3(3400.0f, 650.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(3800.0f, 290.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(5500.0f, 650.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(7330.0f, 650.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(7335.0f, 860.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(8110.0f, 850.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(10650.0f, 650.0f, 0.0f), 4);

	//敵の初期化処理
	InitEnemy();

	//敵の設定処理
	SetEnemy(D3DXVECTOR3(2200.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(3500.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(5400.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(6600.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(6900.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(9300.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(9600.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(9900.0f, 300.0f, 0.0f), 1);

	//アイテムの初期化処理
	InitItem();

	//アイテムの設定
	SetItem(D3DXVECTOR3(6200.0f, 600.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(6500.0f, 50.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(8330.0f, 100.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(9500.0f, 400.0f, 0.0f), 2);
	SetItem(D3DXVECTOR3(9700.0f, 400.0f, 0.0f), 2);
	SetItem(D3DXVECTOR3(9900.0f, 400.0f, 0.0f), 2);

	//残機の初期化処理
	InitRemain();

	//敵が死ぬ時の初期化処理
	InitExit();

	//ポーズメニューの初期化処理
	InitPauseMenu();

	//エフェクトの初期化処理
	InitEffect();

	//パーティクルの初期化処理
	InitParticle();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);

	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	g_nCounterGameState = 0;
	g_bStart = true;
	g_bPause = false;
}

//==============================================================
//ゲーム画面の終了処理
//==============================================================
void UninitGame(void)
{
	//サウンドの停止
	StopSound();

	//背景の終了処理
	Uninitbg();

	//プレイヤーの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	//プレイヤー（影）の終了処理
	UninitSPlayer();

	//ブロックの終了処理
	UninitBlock();

	//ブロック（影）の終了処理
	UninitSBlock();

	//ゴールの終了処理
	UninitGoal();

	//アイテムの終了処理
	UninitItem();

	//残機の終了処理
	UninitRemain();

	//敵が死ぬときの終了処理
	UninitExit();

	//ポーズメニューの終了処理
	UninitPauseMenu();

	//エフェクトの終了処理
	UninitEffect();
}

//==============================================================
//ゲーム画面の更新処理
//==============================================================
void UpdateGame(void)
{
	Player *pPlayer = GetPlayer();

	if (g_bPause == false)
	{
		//背景の更新処理
		Updatebg();

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の終了処理
		UpdateEnemy();

		//プレイヤー（影）の更新処理
		UpdateSPlayer();

		//ブロックの更新処理
		UpdateBlock();

		//ブロック（影）の更新処理
		UpdateSBlock();

		//ゴールの更新処理
		UpdateGoal();

		//アイテムの更新処理
		UpdateItem();

		//残機の更新処理
		UpdateRemain();

		//敵が死ぬときの更新処理
		UpdateExit();

		//エフェクトの更新処理
		UpdateEffect();

		//パーティクルの更新処理
		UpdateParticle();
	}
	else if (g_bPause == true)
	{
		UpdatePauseMenu();
	}

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = (g_bPause == false) ? true : false;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:						//通常状態
		break;
	case GAMESTATE_END:							//終了状態
		g_nCounterGameState++;
		if (g_nCounterGameState <= 160)
		{
			g_gameState = GAMESTATE_NORMAL;		//何もしていない状態に設定
			//モード設定(リザルト画面に移行)
			SetFade(MODE_RESULT);				//フェードアウト
		}
		break;
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawGame(void)
{
	//背景の描画処理
	Drawbg();

	//ブロック（影）の描画処理
	DrawSBlock();

	//プレイヤー（影）の描画処理
	DrawSPlayer();

	//敵が死ぬときの描画処理
	DrawExit();

	//エフェクトの描画処理
	DrawEffect();

	//敵の描画処理
	DrawEnemy();

	//ブロックの描画処理
	DrawBlock();

	//ゴールの描画処理
	DrawGoal();

	//アイテムの描画処理
	DrawItem();

	//残機の描画処理
	DrawRemain();

	//プレイヤーの描画処理
	DrawPlayer();

	if (g_bPause == true)
	{
		DrawPauseMenu();
	}
}

//==============================================================
//ゲーム状態の設定
//==============================================================
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
}

//==============================================================
//ゲーム状態の取得
//==============================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//==============================================================
//ポーズ画面の設定処理
//==============================================================
void SetEnablePauseMenu(bool bPouse)
{
	g_bPause = bPouse;
}
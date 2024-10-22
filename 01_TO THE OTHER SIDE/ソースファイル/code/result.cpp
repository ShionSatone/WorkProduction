//==============================================================
//
//DirectX[result.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"result.h"
#include"input.h"
#include"player.h"
#include"goal.h"
#include"enemy.h"
#include"item.h"
#include"fade.h"
#include"sound.h"

//マクロ定義
#define NUM_RESULT		(3)		//背景の数
#define COL_R			(255)	//赤色の数値
#define COL_G			(255)	//緑色の数値
#define COL_B			(255)	//青色の数値
#define COL_A			(255)	//不透明度の数値
#define RESULT_TIME		(800)	//リザルト画面表示時間

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_RESULT] = {};	//テクスチャ(3等分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//頂点バッファへのポインタ
int g_nCounterResult;

//==============================================================
//リザルト画面の初期化処理
//==============================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	Player *pPlayer = GetPlayer();
	int nCntResult;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear001.jpg",
		&g_pTextureResult[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear000.jpg",
		&g_pTextureResult[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear002.jpg",
		&g_pTextureResult[2]);

	g_nCounterResult = 0;		//カウンターの初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	if (pPlayer->bDisp == false)
	{//プレイヤー死んだ
		//サウンドの再生
		PlaySound(SOUND_LABEL_BGM004);
	}
	else if (GetNumItem() == 3)
	{//アイテム全部取った
		//サウンドの再生
		PlaySound(SOUND_LABEL_BGM002);
	}
	else if (GetNumEnemy() == 0)
	{//普通のクリア
		//サウンドの再生
		PlaySound(SOUND_LABEL_BGM003);
	}
}

//==============================================================
//リザルト画面の終了処理
//==============================================================
void UninitResult(void)
{
	int nCntGame;

	//サウンドの停止
	StopSound();

	for (nCntGame = 0; nCntGame < NUM_RESULT; nCntGame++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCntGame] != NULL)
		{
			g_pTextureResult[nCntGame]->Release();
			g_pTextureResult[nCntGame] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//==============================================================
//リザルト画面の更新処理
//==============================================================
void UpdateResult(void)
{
	g_nCounterResult++;

	if (GetKeyboardTrigger(DIK_RETURN) == true || (g_nCounterResult % RESULT_TIME) == 0)
	{//決定キー(ENTERキー)が押された
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_TITLE);				//フェードアウト
	}
}

//==============================================================
//リザルト画面の描画処理
//==============================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	Player *pPlayer = GetPlayer();
	Goal *pGoal = GetGoal();

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (pPlayer->bDisp == false)
	{//ゲームオーバー
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[0]);
	}
	else if (GetNumItem() == 3)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[2]);
	}
	else if (GetNumEnemy() == 0)
	{//クリア
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[1]);
	}
	
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,												//プリミティブ（ポリゴンの数）
		2);												//描画するプリミティブ数
}
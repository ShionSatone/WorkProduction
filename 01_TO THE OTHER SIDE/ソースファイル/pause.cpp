//==============================================================
//
//DirectX[pause.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"pause.h"
#include"input.h"
#include"game.h"
#include"fade.h"

//マクロ定義
#define NUM_PAUSE		(2)		//ポーズ画面の数
#define COL_R			(255)	//赤色の数値
#define COL_G			(255)	//緑色の数値
#define COL_B			(255)	//青色の数値
#define COL_A			(255)	//不透明度の数値

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePause[NUM_PAUSE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//頂点バッファのポインタ
Pause g_Pause[NUM_PAUSE];										//ポーズの情報

//==============================================================
//ポーズ画面の初期化処理
//==============================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntPause;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial000.jpg",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title003.png",
		&g_pTexturePause[1]);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		g_Pause[nCntPause].nCounterAppear = 0;						//点滅の時間を初期化
		g_Pause[nCntPause].nCounterState = 0;
		if (nCntPause == 0)
		{
			g_Pause[nCntPause].state = PAUSESTATE_NORMAL;	//状態を初期化
		}
		else if (nCntPause == 1)
		{
			g_Pause[nCntPause].state = PAUSESTATE_APPEAR;	//状態を初期化
		}
		g_Pause[nCntPause].bUse = true;								//表示する
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (nCntPause == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCntPause == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(800.0f, 580.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1250.0f, 580.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800.0f, 690.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1250.0f, 690.0f, 0.0f);
		}

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

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//==============================================================
//ポーズ画面の終了処理
//==============================================================
void UninitPause(void)
{
	int nCntPause;

	//テクスチャの破棄
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//==============================================================
//ポーズ画面の更新処理
//==============================================================
void UpdatePause(void)
{
	int nCntPause;
	int nCounterAppear = 0;
	g_Pause[1].nCounterState++;

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		switch (g_Pause[nCntPause].state)
		{
		case PAUSESTATE_APPEAR:
			if ((g_Pause[1].nCounterState % 40) == 0)
			{
				g_Pause[1].bUse = (g_Pause[1].bUse == false) ? true : false;
			}

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				////サウンドの停止
				//StopSound();

				////サウンドの再生
				//PlaySound(SOUND_LABEL_SE_ENTER000);

				g_Pause[1].state = PAUSESTATE_WAIT;
			}

			break;


		case PAUSESTATE_NORMAL:

			break;

		case PAUSESTATE_WAIT:
			//素早く点滅
			if ((g_Pause[1].nCounterState % 3) == 0)
			{
				g_Pause[1].bUse = (g_Pause[1].bUse == false) ? true : false;
				nCounterAppear++;
			}

			if (nCounterAppear >= 1)
			{
				//モード設定(ゲーム画面に移行)
				SetFade(MODE_GAME);				//フェードアウト
			}

			break;
		}
	}
}

//==============================================================
//ポーズ画面の描画処理
//==============================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntPause;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (g_Pause[nCntPause].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePause[nCntPause]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntPause * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}
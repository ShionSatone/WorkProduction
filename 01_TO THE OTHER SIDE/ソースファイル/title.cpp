//==============================================================
//
//DirectX[title.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"title.h"
#include"input.h"
#include"fade.h"
//#include"pause.h"
#include"sound.h"

//マクロ定義
#define NUM_TITLE		(3)		//タイトルの数
#define COL_R			(255)	//赤色の数値
#define COL_G			(255)	//緑色の数値
#define COL_B			(255)	//青色の数値
#define COL_A			(255)	//不透明度の数値

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファのポインタ
Title g_title[NUM_TITLE];									//プレイヤーの情報
bool bUseTitleSound = true;									//曲を流すか流さないか

//==============================================================
//タイトル画面の初期化処理
//==============================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntTitle;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title000.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title001.png",
		&g_pTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title002.png",
		&g_pTextureTitle[2]);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_title[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化する
		g_title[nCntTitle].state = TITLESTATE_NORMAL;			//タイトルの状態を初期化する
		g_title[nCntTitle].nCounterState = 0;					//状態管理カウンターを初期化する
		g_title[nCntTitle].nCounterAppear = 20;					//点滅時間を初期化する
		g_title[nCntTitle].nCounterRank = 0;					//ランキング画面の時間を初期化する
		g_title[nCntTitle].bUse = true;							//表示するかしないかを初期化する
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (nCntTitle == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCntTitle == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(200.0f, 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1080.0f, 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(200.0f, 250.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1080.0f, 250.0f, 0.0f);
		}
		else if (nCntTitle == 2)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(400.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(880.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(880.0f, 600.0f, 0.0f);
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

		pVtx += 4;			//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}

//==============================================================
//タイトル画面の終了処理
//==============================================================
void UninitTitle(void)
{
	int nCntTitle;

	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//==============================================================
//タイトル画面の更新処理
//==============================================================
void UpdateTitle(void)
{
	int nCntTitle;
	int nCounterAppear = 0;
	g_title[2].nCounterState++;

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_title[nCntTitle].nCounterRank++;

		switch (g_title[nCntTitle].state)
		{
		case TITLESTATE_APPEAR:
			//普通の点滅
			if ((g_title[2].nCounterState % 40) == 0)
			{
				g_title[2].bUse = (g_title[2].bUse == false) ? true : false;
			}

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadPress(BUTTON00, 0) == true)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_ENTER000);

				g_title[2].state = TITLESTATE_WAIT;
			}
			break;

		case TITLESTATE_NORMAL:
			if (g_title[2].state == TITLESTATE_NORMAL)
			{
				g_title[2].state = TITLESTATE_APPEAR;
			}

			//if ((g_title[nCntTitle].nCounterRank % 500) == 0)
			//{
			//	//モード設定(ランキング画面に移行)
			//	SetFade(MODE_RANKING);			//フェードアウト
			//}

			break;

		case TITLESTATE_WAIT:
			//素早く点滅
			if ((g_title[2].nCounterState % 3) == 0)
			{
				g_title[2].bUse = (g_title[2].bUse == false) ? true : false;
				nCounterAppear++;
			}

			if (nCounterAppear >= 1)
			{
				//モード設定(ポーズ画面に移行)
				SetFade(MODE_GAME);			//フェードアウト
			}

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//==============================================================
//タイトル画面の描画処理
//==============================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntTitle;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_title[nCntTitle].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntTitle * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}
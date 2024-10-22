//==============================================================
//
//DirectX[Exit.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"main.h"
#include"Exit.h"
#include"input.h"
#include"enemy.h"

//マクロ定義
#define MAX_EXIT		(128)		//弾の最大数
#define NUM_EXIT		(2)			//敵の種類
#define DEF_POS_Z		(0.0f)		//プレイヤーのpos.zの初期値
#define COL_R			(1.0f)		//赤色の数値
#define COL_G			(1.0f)		//緑色の数値
#define COL_B			(1.0f)		//青色の数値
#define COL_A			(1.0f)		//不透明度の数値
#define TEX_LEFT_X		(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X		(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y		(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y		(1.0f)		//テクスチャの下yの初期値
#define BOSS_WIDTH		(90.0f)		//ボスの幅
#define BOSS_HEIGHT		(170.0f)	//ボスの高さ
#define ENEMY_WIDTH		(30.0f)		//雑魚敵の幅
#define ENEMY_HEIGHT	(60.0f)		//雑魚敵の高さ

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	float fWidth;			//幅
	float fHeight;			//高さ
	float fColor;			//敵の透明度
	int nType;				//種類
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	bool bUse;				//使用しているかどうか
} Exit;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExit[NUM_EXIT] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExit = NULL;				//頂点バッファのポインタ
Exit g_aExit[MAX_EXIT];										//弾の情報

//==============================================================
//爆発の初期化処理
//==============================================================
void InitExit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExit;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exitenemy001.png",
		&g_pTextureExit[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exitenemy002.png",
		&g_pTextureExit[1]);

	//弾の情報の初期化
	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		g_aExit[nCntExit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aExit[nCntExit].move = D3DXVECTOR3(1.0f, 10.0f, 1.0f);	//移動量の初期化
		g_aExit[nCntExit].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);	//色の初期化
		g_aExit[nCntExit].fWidth = 0.0f;							//幅の初期化
		g_aExit[nCntExit].fHeight = 0.0f;							//高さの初期化
		g_aExit[nCntExit].fColor = 1.0f;							//敵の透明度の初期化
		g_aExit[nCntExit].nType = nCntExit;							//種類の初期化
		g_aExit[nCntExit].bUse = false;								//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExit,
		NULL);

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT_X, TEX_UP_Y);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_UP_Y);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT_X, TEX_DOWN_Y);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_DOWN_Y);

		pVtx += 4;			//頂点データのポインタを４つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExit->Unlock();
}

//==============================================================
//爆発の終了処理
//==============================================================
void UninitExit(void)
{
	int nCntExit;
	//テクスチャの破棄
	for (nCntExit = 0; nCntExit < NUM_EXIT; nCntExit++)
	{
		if (g_pTextureExit[nCntExit] != NULL)
		{
			g_pTextureExit[nCntExit]->Release();
			g_pTextureExit[nCntExit] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExit != NULL)
	{
		g_pVtxBuffExit->Release();
		g_pVtxBuffExit = NULL;
	}
}

//==============================================================
//爆発の更新処理
//==============================================================
void UpdateExit(void)
{
	int nCntExit;
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_aExit[nCntExit].bUse == true)
		{//爆発が使用されている
			g_aExit[nCntExit].fColor -= 0.05f;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
		}
		pVtx += 4;											//頂点データのポインタを４つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExit->Unlock();
}

//==============================================================
//爆発の描画処理
//==============================================================
void DrawExit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExit;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExit = 0; nCntExit < MAX_ENEMY; nCntExit++)
	{
		if (g_aExit[nCntExit].bUse == true)
		{//敵が使用されている	
		 //テクスチャの設定
			if (g_aExit[nCntExit].nType == 0)
			{
				pDevice->SetTexture(0, g_pTextureExit[0]);
			}
			else if (g_aExit[nCntExit].nType == 1)
			{
				pDevice->SetTexture(0, g_pTextureExit[1]);
			}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntExit * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}

//==============================================================
//爆発の設定処理
//==============================================================
void SetExit(D3DXVECTOR3 pos, D3DXCOLOR col, int nType)
{
	int nCntExit;
	VERTEX_2D *pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_aExit[nCntExit].bUse == false)
		{//爆発が使用されていない
			g_aExit[nCntExit].pos = pos;
			g_aExit[nCntExit].col = col;
			g_aExit[nCntExit].nType = nType;
			g_aExit[nCntExit].nCounterAnim = 0;
			g_aExit[nCntExit].nPatternAnim = 0;

			if (g_aExit[nCntExit].nType == 0)
			{//ボス
				g_aExit[nCntExit].fWidth = BOSS_WIDTH;
				g_aExit[nCntExit].fHeight = BOSS_HEIGHT;
			}
			else if (g_aExit[nCntExit].nType == 1)
			{//雑魚敵
				g_aExit[nCntExit].fWidth = ENEMY_WIDTH;
				g_aExit[nCntExit].fHeight = ENEMY_HEIGHT;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);

			g_aExit[nCntExit].bUse = true;		//使用している状態にする

			break;
		}
		pVtx += 4;											//頂点データのポインタを４つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExit->Unlock();
}
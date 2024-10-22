//==============================================================
//
//DirectX[item.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"item.h"
#include"player.h"
#include"splayer.h"
#include"input.h"
#include"sound.h"

//マクロ定義
#define NUM_ITEM			(2)			//アイテムの種類
#define MAX_ITEM			(128)		//アイテムの数
#define DEF_POS_X			(500.0f)	//アイテムのpos.xの初期値
#define DEF_POS_Y			(400.0f)	//アイテムのpos.yの初期値
#define DEF_POS_Z			(0.0f)		//アイテムのpos.zの初期値
#define ITEM_WIDTH			(20.0f)		//アイテムの幅の初期値
#define ITEM_HEIGHT			(20.0f)		//アイテムの高さの初期値
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(1.0f)		//テクスチャの下yの初期値

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};	//テクスチャ1へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//頂点バッファへのポインタ
Item g_aItem[MAX_ITEM];
int g_aNumGetItem;									//アイテムの数
int g_nCounterLife;									//寿命

//テクスチャファイル名


//==============================================================
//アイテムの初期化処理
//==============================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	int nCntItem;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item000.png",
		&g_pTextureItem[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\life001.png",
		&g_pTextureItem[1]);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//位置を初期化する
		g_aItem[nCntItem].fWidth = ITEM_WIDTH;										//幅を初期化する
		g_aItem[nCntItem].fHeight = ITEM_HEIGHT;									//高さを初期化する
		g_aItem[nCntItem].nType = 0;												//種類を初期化する
		g_aItem[nCntItem].nCounterItem = 0;											//アイテムの動きのカウンターを初期化する
		g_aItem[nCntItem].bUse = false;												//使用していない状態にする
		g_aItem[nCntItem].bShadowUse = true;										//実物をしようしている状態にする
	}

	g_aNumGetItem = 0;																//アイテムの数の初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点・座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);

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

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//==============================================================
//アイテムの終了処理
//==============================================================
void UninitItem(void)
{
	int nCntItem;

	//テクスチャの破棄
	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//==============================================================
//アイテムの更新処理
//==============================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();
	int nCntItem;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPlayer->nJudgeDirection == 0)
			{//左に出た場合
				g_aItem[nCntItem].pos.x += SCREEN_WIDTH;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{//右に出た場合
				g_aItem[nCntItem].pos.x -= SCREEN_WIDTH;
			}

			/*if (g_aItem[nCntItem].nType == 2)
			{
				

			}*/

			//頂点・座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
		}
		else if (g_aItem[nCntItem].bUse == false)
		{
			if (g_aItem[nCntItem].nType == 1)
			{
				g_nCounterLife++;

				if (g_nCounterLife >= 600)
				{
					g_aItem[nCntItem].bUse = true;
					g_nCounterLife = 0;
				}
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//==============================================================
//アイテムの描画処理
//==============================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntItem;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (g_aItem[nCntItem].nType == 0)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem[0]);
			}
			else if (g_aItem[nCntItem].nType == 1 || g_aItem[nCntItem].nType == 2)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem[1]);
			}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntItem * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}

//==============================================================
//アイテムの設定処理
//==============================================================
void SetItem(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ
	int nCntItem;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].nType = nType;

			//頂点・座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);

			if (g_aItem[nCntItem].nType == 0 || g_aItem[nCntItem].nType == 2)
			{
				g_aItem[nCntItem].bUse = true;
			}

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//==============================================================
//アイテムのヒット処理
//==============================================================
void HitItem(void)
{
	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_GET000);

	g_aNumGetItem += 1;
}

//==============================================================
//情報
//==============================================================
Item *GetItem(void)
{
	return &g_aItem[0];		//アイテムの情報の先頭アドレスを返す
}

//==============================================================
//アイテムの総数の取得
//==============================================================
int GetNumItem(void)
{
	return g_aNumGetItem;
}

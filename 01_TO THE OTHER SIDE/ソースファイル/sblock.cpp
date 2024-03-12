//==============================================================
//
//DirectX[sblock.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"sblock.h"
#include"input.h"
#include"splayer.h"
#include"player.h"
#include"block.h"
#include"enemy.h"
#include"item.h"
#include"sound.h"

//マクロ定義
#define MAX_SBLOCK			(128)		//ブロック（影）の数
#define DEF_POS_X			(500.0f)	//ブロック（影）のpos.xの初期値
#define DEF_POS_Y			(400.0f)	//ブロック（影）のpos.yの初期値
#define DEF_POS_Z			(0.0f)		//ブロック（影）のpos.zの初期値
#define SBLOCK_WIDTH0		(50.0f)		//1マスブロック（影）の幅の初期値
#define SBLOCK_HEIGHT0		(50.0f)		//1マスブロック（影）の高さの初期値
#define SBLOCK_WIDTH2		(640.0f)	//横長ブロック（影）の幅の初期値
#define SBLOCK_HEIGHT2		(60.0f)		//横長ブロック（影）の高さの初期値
#define SBLOCK_WIDTH3		(50.0f)		//縦長ブロック（影）の幅の初期値
#define SBLOCK_HEIGHT3		(100.0f)	//縦長ブロック（影）の高さの初期値
#define SBLOCK_WIDTH4		(30.0f)		//ボタンブロック（影）の幅の初期値
#define SBLOCK_HEIGHT4		(30.0f)		//ボタンブロック（影）の高さの初期値
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(1.0f)		//テクスチャの下yの初期値
#define SHADOW_X			(200.0f)	//影のXの位置
#define SHADOW_Y			(220.0f)	//影のYの位置
#define PLAYER_WIDTH		(15.0f)		//プレイヤーの幅から引く幅
#define PLAYER_HEIGHT		(0.0f)		//プレイヤーの高さに足す高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureSBlock = NULL;			//テクスチャ1へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSBlock = NULL;		//頂点バッファへのポインタ
SBlock g_aSBlock[MAX_SBLOCK];

//==============================================================
//ブロック（影）の初期化処理
//==============================================================
void InitSBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	int nCntSBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg_shadow000.png",
		&g_pTextureSBlock);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		g_aSBlock[nCntSBlock].pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//位置を初期化する
		g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH0;									//幅を初期化する
		g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT0;									//高さを初期化する
		g_aSBlock[nCntSBlock].nType = 0;												//種類を初期化する
		g_aSBlock[nCntSBlock].nCounterSBlock = 0;										//ブロック（影）の動きのカウンターを初期化する
		g_aSBlock[nCntSBlock].bUse = false;												//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SBLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSBlock,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x, g_aSBlock[nCntSBlock].pos.y, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x, g_aSBlock[nCntSBlock].pos.y + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);

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

		pVtx += 4;						//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSBlock->Unlock();
}

//==============================================================
//ブロック（影）の終了処理
//==============================================================
void UninitSBlock(void)
{
	//テクスチャの破棄
	if (g_pTextureSBlock != NULL)
	{
		g_pTextureSBlock->Release();
		g_pTextureSBlock = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSBlock != NULL)
	{
		g_pVtxBuffSBlock->Release();
		g_pVtxBuffSBlock = NULL;
	}
}

//==============================================================
//ブロック（影）の更新処理
//==============================================================
void UpdateSBlock(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();
	int nCntSBlock;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		g_aSBlock[nCntSBlock].nCounterSBlock++;

		if (g_aSBlock[nCntSBlock].bUse == true)
		{
			if (g_aSBlock[nCntSBlock].nType == 1)
			{//横移動
				if (g_aSBlock[nCntSBlock].nCounterSBlock <= 200)
				{
					g_aSBlock[nCntSBlock].pos.x += 1.0f;
				}
				else if (g_aSBlock[nCntSBlock].nCounterSBlock <= 400)
				{
					g_aSBlock[nCntSBlock].pos.x -= 1.0f;
				}
				else if (g_aSBlock[nCntSBlock].nCounterSBlock <= 600)
				{
					g_aSBlock[nCntSBlock].nCounterSBlock = 0;
				}
			}

			if (pPlayer->nJudgeDirection == 0)
			{
				g_aSBlock[nCntSBlock].pos.x += SCREEN_WIDTH;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{
				g_aSBlock[nCntSBlock].pos.x -= SCREEN_WIDTH;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
		}

		pVtx += 4;						//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSBlock->Unlock();
}

//==============================================================
//ブロック（影）の描画処理
//==============================================================
void DrawSBlock(void)
{
	int nCntSBlock;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		if (g_aSBlock[nCntSBlock].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSBlock);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntSBlock * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}

//==============================================================
//ブロック（影）の設定処理
//==============================================================
void SetSBlock(D3DXVECTOR3 pos, int nType)
{
	int nCntSBlock;
	VERTEX_2D *pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		if (g_aSBlock[nCntSBlock].bUse == false)
		{//ブロック（影）が使用されていない
			g_aSBlock[nCntSBlock].pos = pos;
			g_aSBlock[nCntSBlock].nType = nType;

			if (g_aSBlock[nCntSBlock].nType == 0)
			{//1マス
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH0;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT0;
			}
			else if (g_aSBlock[nCntSBlock].nType == 2)
			{//横長
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH2;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT2;
			}
			else if (g_aSBlock[nCntSBlock].nType == 3)
			{//縦長
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH3;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT3;
			}
			else if (g_aSBlock[nCntSBlock].nType == 4)
			{//ボタンブロック（影）
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH4;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT4;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);

			g_aSBlock[nCntSBlock].bUse = true;		//使用している状態にする

			break;
		}
		pVtx += 4;									//頂点データのポインタを４つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSBlock->Unlock();
}

//==============================================================
//ブロック（影）との当たり判定処理
//==============================================================
bool CollisionSBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, SBlock **pSBlock)
{
	Player *pPlayer = GetPlayer();
	int nCntSBlock;
	bool bLand = false;		//着地したかどうか

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		if (g_aSBlock[nCntSBlock].bUse == true && pPlayer->state == PLAYERSTATE_SHADOW)
		{
			if (pPosOld->y <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->y >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth)
			{//下にめり込んだ場合
				bLand = true;
				pPos->y = g_aSBlock[nCntSBlock].pos.y - SHADOW_Y;													//ブロック（影）の上に立たせる
				pMove->y = 0.0f;																					//移動量を０にする

				if (g_aSBlock[nCntSBlock].nType == 4)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_BUTTON000);

					g_aSBlock[nCntSBlock].bUse = false;
					CollisionSButton(nCntSBlock);
				}

				if (pSBlock != NULL)
				{//ブロック（影）のアドレスを入れる場所がある
					*pSBlock = &g_aSBlock[nCntSBlock];																	//ブロック（影）のアドレスを代入
				}
			}
			else if (pPosOld->y - fHeight - PLAYER_HEIGHT >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth)
			{//上にめり込んだ場合
				bLand = false;
				pPos->y = g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight + fHeight + PLAYER_HEIGHT;			//ブロック（影）の下に立たせる
				pMove->y = 0.0f;																									//移動量を０にする
			}
			else if (pPosOld->x + fWidth - PLAYER_WIDTH <= g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->x + fWidth - PLAYER_WIDTH >= g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->y >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight)
			{//左にめり込んだ場合
				pPos->x = g_aSBlock[nCntSBlock].pos.x + SHADOW_X - fWidth + PLAYER_WIDTH;											//ブロック（影）の左に立たせる
				pMove->x = 0.0f;																									//移動量を０にする

				bLand = false;
			}
			else if (pPosOld->x - fWidth + PLAYER_WIDTH >= g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth
				&& pPos->x - fWidth + PLAYER_WIDTH <= g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth
				&& pPos->y >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight)
			{//右にめり込んだ場合
				pPos->x = g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth + fWidth - PLAYER_WIDTH;			//ブロック（影）の左に立たせる
				pMove->x = 0.0f;																									//移動量を０にする

				bLand = false;
			}
		}
	}

	return bLand;
}

//==============================================================
//ボタン（影）との当たり判定処理
//==============================================================
void CollisionSButton(int nCntSBlock)
{
	if (nCntSBlock == 94)
	{
		SetBlock(D3DXVECTOR3(300.0f, 660.0f, 0.0f), 2);
		SetSBlock(D3DXVECTOR3(300.0f, 660.0f, 0.0f), 2);
	}
	else if (nCntSBlock == 95)
	{
		SetBlock(D3DXVECTOR3(910.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(910.0f, 660.0f, 0.0f), 3);
	}
	else if (nCntSBlock == 96)
	{
		SetBlock(D3DXVECTOR3(400.0f, 660.0f, 0.0f), 2);
		SetSBlock(D3DXVECTOR3(400.0f, 660.0f, 0.0f), 2);
	}
	else if (nCntSBlock == 97)
	{
		SetSBlock(D3DXVECTOR3(900.0f, 870.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(950.0f, 870.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(900.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(950.0f, 660.0f, 0.0f), 3);
	}
	else if (nCntSBlock == 98)
	{
		SetSBlock(D3DXVECTOR3(700.0f, 500.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(750.0f, 500.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(500.0f, 400.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(550.0f, 400.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(300.0f, 300.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(350.0f, 300.0f, 0.0f), 0);
	}
	else if (nCntSBlock == 99)
	{
		SetBlock(D3DXVECTOR3(820.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(870.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(920.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(970.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(1020.0f, 660.0f, 0.0f), 3);

		SetSBlock(D3DXVECTOR3(820.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(870.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(920.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(970.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(1020.0f, 660.0f, 0.0f), 3);

		SetSBlock(D3DXVECTOR3(110.0f, 500.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(160.0f, 500.0f, 0.0f), 0);
	}
	else if (nCntSBlock == 100)
	{
		//サウンドの停止
		StopSound();

		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0, 100.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 200.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 300.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 400.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 600.0f, 0.0f), 3);

		SetSBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0, 100.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 200.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 300.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 400.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 600.0f, 0.0f), 3);

		SetEnemy(D3DXVECTOR3(700.0f, 0.0f, 0.0f), 0);

		SetItem(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), 1);
	}
}
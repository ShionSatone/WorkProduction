//==============================================================
//
//DirectX[block.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"block.h"
#include"player.h"
#include"input.h"

//マクロ定義
#define MAX_BLOCK			(128)		//ブロックの数
#define DEF_POS_X			(500.0f)	//ブロックのpos.xの初期値
#define DEF_POS_Y			(400.0f)	//ブロックのpos.yの初期値
#define DEF_POS_Z			(0.0f)		//ブロックのpos.zの初期値
#define BLOCK_WIDTH0		(50.0f)		//1マスブロックの幅の初期値
#define BLOCK_HEIGHT0		(50.0f)		//1マスブロックの高さの初期値
#define BLOCK_WIDTH2		(640.0f)	//横長ブロックの幅の初期値
#define BLOCK_HEIGHT2		(60.0f)		//横長ブロックの高さの初期値
#define BLOCK_WIDTH3		(50.0f)		//縦長ブロックの幅の初期値
#define BLOCK_HEIGHT3		(100.0f)	//縦長ブロックの高さの初期値
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(1.0f)		//テクスチャの下yの初期値
#define PLAYER_WIDTH		(15.0f)		//プレイヤーの幅から引く幅
#define PLAYER_HEIGHT		(0.0f)		//プレイヤーの高さに足す高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			//テクスチャ1へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		//頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];

//テクスチャファイル名


//==============================================================
//ブロックの初期化処理
//==============================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block000.png",
		&g_pTextureBlock);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//位置を初期化する
		g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH0;									//幅を初期化する
		g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT0;								//高さを初期化する
		g_aBlock[nCntBlock].nType = 0;												//種類を初期化する
		g_aBlock[nCntBlock].nCounterBlock = 0;										//ブロックの動きのカウンターを初期化する
		g_aBlock[nCntBlock].bUse = false;											//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);

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
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//ブロックの終了処理
//==============================================================
void UninitBlock(void)
{
	//テクスチャの破棄
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//==============================================================
//ブロックの更新処理
//==============================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();	//プレイヤーの情報を読み込む
	int nCntBlock;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].nCounterBlock++;

		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].nType == 1)
			{//横移動
				if (g_aBlock[nCntBlock].nCounterBlock <= 200)
				{
					g_aBlock[nCntBlock].pos.x += 1.0f;
				}
				else if (g_aBlock[nCntBlock].nCounterBlock <= 400)
				{
					g_aBlock[nCntBlock].pos.x -= 1.0f;
				}
				else if (g_aBlock[nCntBlock].nCounterBlock <= 600)
				{
					g_aBlock[nCntBlock].nCounterBlock = 0;
				}
			}

			if (pPlayer->nJudgeDirection == 0)
			{//左に出た場合
				g_aBlock[nCntBlock].pos.x += SCREEN_WIDTH;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{//右に出た場合
				g_aBlock[nCntBlock].pos.x -= SCREEN_WIDTH;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
		}

		pVtx += 4;						//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//ブロックの描画処理
//==============================================================
void DrawBlock(void)
{
	int nCntBlock;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntBlock * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}

//==============================================================
//ブロックの設定処理
//==============================================================
void SetBlock(D3DXVECTOR3 pos, int nType)
{
	int nCntBlock;
	VERTEX_2D *pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].nType = nType;

			if (g_aBlock[nCntBlock].nType == 0)
			{//1マス
				g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH0;
				g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT0;
			}
			else if (g_aBlock[nCntBlock].nType == 2)
			{//横長
				g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH2;
				g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT2;
			}
			else if (g_aBlock[nCntBlock].nType == 3 || g_aBlock[nCntBlock].nType == 5)
			{//縦長 or 見せかけブロック
				g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH3;
				g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT3;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);

			g_aBlock[nCntBlock].bUse = true;		//使用している状態にする

			break;
		}
		pVtx += 4;									//頂点データのポインタを４つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//ブロックとの当たり判定処理
//==============================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Block **pBlock)
{
	int nCntBlock;
	bool bLand = false;		//着地したかどうか

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType != 5)
		{
			if (pPosOld->y <= g_aBlock[nCntBlock].pos.y
				&& pPos->y >= g_aBlock[nCntBlock].pos.y
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//下にめり込んだ場合
				bLand = true;
				pPos->y = g_aBlock[nCntBlock].pos.y;																//ブロックの上に立たせる
				pMove->y = 0.0f;																					//移動量を０にする

				if (pBlock != NULL)
				{//ブロックのアドレスを入れる場所がある
					*pBlock = &g_aBlock[nCntBlock];																	//ブロックのアドレスを代入
				}
			}
			else if (pPosOld->y - fHeight - PLAYER_HEIGHT >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//上にめり込んだ場合
				bLand = false;
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight + PLAYER_HEIGHT;			//ブロックの下に立たせる
				pMove->y = 0.0f;																						//移動量を０にする
			}
			else if (pPosOld->x + fWidth - PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x
				&& pPos->x + fWidth - PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x
				&& pPos->y >= g_aBlock[nCntBlock].pos.y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{//左にめり込んだ場合
				pPos->x = g_aBlock[nCntBlock].pos.x - fWidth + 14.0f;													//ブロックの左に立たせる
				pMove->x = 0.0f;																						//移動量を０にする

				bLand = false;
			}
			else if (pPosOld->x - fWidth + PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
				&& pPos->x - fWidth + PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
				&& pPos->y >= g_aBlock[nCntBlock].pos.y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{//右にめり込んだ場合
				pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth - 14.0f;						//ブロックの左に立たせる
				pMove->x = 0.0f;																						//移動量を０にする

				bLand = false;
			}
		}
	}

	return bLand;
}

//==============================================================
//
//DirectX[goal.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"goal.h"
#include"player.h"
#include"input.h"

//マクロ定義
#define MAX_Goal			(1)			//ゴールの数
#define DEF_POS_X			(500.0f)	//ゴールのpos.xの初期値
#define DEF_POS_Y			(400.0f)	//ゴールのpos.yの初期値
#define DEF_POS_Z			(0.0f)		//ゴールのpos.zの初期値
#define Goal_WIDTH0			(50.0f)		//1マスゴールの幅の初期値
#define Goal_HEIGHT0		(50.0f)		//1マスゴールの高さの初期値
#define Goal_WIDTH2			(640.0f)	//横長ゴールの幅の初期値
#define Goal_HEIGHT2		(60.0f)		//横長ゴールの高さの初期値
#define Goal_WIDTH3			(50.0f)		//縦長ゴールの幅の初期値
#define Goal_HEIGHT3		(100.0f)	//縦長ゴールの高さの初期値
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
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			//テクスチャ1へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;		//頂点バッファへのポインタ
Goal g_aGoal;

//テクスチャファイル名


//==============================================================
//ゴールの初期化処理
//==============================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\goal.jpg",
		&g_pTextureGoal);


	g_aGoal.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//位置を初期化する
	g_aGoal.fWidth = Goal_WIDTH0;									//幅を初期化する
	g_aGoal.fHeight = Goal_HEIGHT0;									//高さを初期化する
	g_aGoal.nType = 0;												//種類を初期化する
	g_aGoal.nCounterGoal = 0;										//ゴールの動きのカウンターを初期化する
	g_aGoal.bUse = false;											//使用していない状態にする
	g_aGoal.bShadowUse = true;										//実物をしようしている状態にする


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点・座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//ゴールの終了処理
//==============================================================
void UninitGoal(void)
{
	//テクスチャの破棄
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//==============================================================
//ゴールの更新処理
//==============================================================
void UpdateGoal(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aGoal.bUse == true)
	{
		if (pPlayer->nJudgeDirection == 0)
		{//左に出た場合
			g_aGoal.pos.x += 1280.0f;
		}
		else if (pPlayer->nJudgeDirection == 1)
		{//右に出た場合
			g_aGoal.pos.x -= 1280.0f;
		}

		//頂点・座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//ゴールの描画処理
//==============================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_aGoal.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureGoal);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			0,												//プリミティブ（ポリゴンの数）
			2);												//描画するプリミティブ数
	}
}

//==============================================================
//ゴールの設定処理
//==============================================================
void SetGoal(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aGoal.bUse == false)
	{
		g_aGoal.pos = pos;
		g_aGoal.nType = nType;

		//頂点・座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);

		g_aGoal.bUse = true;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//ゴールとの当たり判定処理
//==============================================================
bool CollisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Goal **pGoal)
{
	bool bLand = false;		//着地したかどうか

	if (g_aGoal.bUse == true && g_aGoal.bShadowUse == true)
	{
		if (pPosOld->y <= g_aGoal.pos.y
			&& pPos->y >= g_aGoal.pos.y
			&& pPos->x + fWidth - PLAYER_WIDTH > g_aGoal.pos.x
			&& pPos->x - fWidth + PLAYER_WIDTH < g_aGoal.pos.x + g_aGoal.fWidth)
		{//下にめり込んだ場合
			bLand = true;
			pPos->y = g_aGoal.pos.y;																//ゴールの上に立たせる
			pMove->y = 0.0f;																					//移動量を０にする

			if (pGoal != NULL)
			{//ゴールのアドレスを入れる場所がある
				*pGoal = &g_aGoal;																	//ゴールのアドレスを代入
			}
		}
		else if (pPosOld->y - fHeight - PLAYER_HEIGHT >= g_aGoal.pos.y + g_aGoal.fHeight
			&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aGoal.pos.y + g_aGoal.fHeight
			&& pPos->x + fWidth - PLAYER_WIDTH > g_aGoal.pos.x
			&& pPos->x - fWidth + PLAYER_WIDTH < g_aGoal.pos.x + g_aGoal.fWidth)
		{//上にめり込んだ場合
			bLand = false;
			pPos->y = g_aGoal.pos.y + g_aGoal.fHeight + fHeight + PLAYER_HEIGHT;			//ゴールの下に立たせる
			pMove->y = 0.0f;																						//移動量を０にする
		}
		else if (pPosOld->x + fWidth - PLAYER_WIDTH <= g_aGoal.pos.x
			&& pPos->x + fWidth - PLAYER_WIDTH >= g_aGoal.pos.x
			&& pPos->y >= g_aGoal.pos.y
			&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aGoal.pos.y + g_aGoal.fHeight)
		{//左にめり込んだ場合
			bLand = false;
			pPos->x = g_aGoal.pos.x - fWidth + 14.0f;													//ゴールの左に立たせる
			pMove->x = 0.0f;																						//移動量を０にする
		}
		else if (pPosOld->x - fWidth + PLAYER_WIDTH >= g_aGoal.pos.x + g_aGoal.fWidth
			&& pPos->x - fWidth + PLAYER_WIDTH <= g_aGoal.pos.x + g_aGoal.fWidth
			&& pPos->y >= g_aGoal.pos.y
			&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aGoal.pos.y + g_aGoal.fHeight)
		{//右にめり込んだ場合
			bLand = false;
			pPos->x = g_aGoal.pos.x + g_aGoal.fWidth + fWidth - 14.0f;						//ゴールの左に立たせる
			pMove->x = 0.0f;																						//移動量を０にする
		}
	}

	return bLand;
}

//==============================================================
//情報
//==============================================================
Goal *GetGoal(void)
{
	return &g_aGoal;		//敵の情報の先頭アドレスを返す
}
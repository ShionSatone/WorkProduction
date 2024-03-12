//==============================================================
//
//DirectX[bg.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"main.h"
#include"bg.h"
#include"player.h"

//マクロ定義
#define NUM_BG				(6)			//背景の数
#define DEF_POS_Z			(0.0f)		//pos.zの初期値
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(1.0f)		//テクスチャの下yの初期値

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBG[NUM_BG] = {};	//テクスチャ(3等分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//頂点バッファへのポインタ
float g_aTexV[NUM_BG];							//テクスチャ座標の開始位置（V値）
D3DXVECTOR3 pos[NUM_BG];

//==============================================================
//背景の初期化処理
//==============================================================
void Initbg(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg002.jpeg",
		&g_pTextureBG[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg001.png",
		&g_pTextureBG[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial001.png",
		&g_pTextureBG[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial002.png",
		&g_pTextureBG[3]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial003.png",
		&g_pTextureBG[4]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial004.png",
		&g_pTextureBG[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (nCntBG == 0 || nCntBG == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCntBG == 2)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(300.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(300.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(400.0f, 550.0f, 0.0f);
		}
		else if (nCntBG == 3)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(700.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(700.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(900.0f, 600.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(800.0f, 550.0f, 0.0f);
		}
		else if (nCntBG == 4)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(1500.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1600.0f, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1500.0f, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1600.0f, 400.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(2300.0f, 300.0f, 0.0f);
		}
		else if (nCntBG == 5)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(2700.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(2900.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(2700.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(2900.0f, 600.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(2800.0f, 200.0f, 0.0f);
		}

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

		pVtx += 4;			//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//==============================================================
//背景の終了処理
//==============================================================
void Uninitbg(void)
{
	int nCntBG;

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_pTextureBG[nCntBG] != NULL)
		{
			g_pTextureBG[nCntBG]->Release();
			g_pTextureBG[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//==============================================================
//背景の更新処理
//==============================================================
void Updatebg(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();
	int nCntBG;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (pPlayer->nJudgeDirection == 0)
		{//左に出た場合
			pos[nCntBG].x += SCREEN_WIDTH;
		}
		else if (pPlayer->nJudgeDirection == 1)
		{//右に出た場合
			pos[nCntBG].x -= SCREEN_WIDTH;
		}


		if (nCntBG == 1 && pPlayer->state != PLAYERSTATE_SHADOW)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
			pVtx[1].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
			pVtx[2].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
			pVtx[3].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
		}
		else if (nCntBG == 1 && pPlayer->state == PLAYERSTATE_SHADOW)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
			pVtx[1].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
			pVtx[2].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
			pVtx[3].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
		}
		else if (nCntBG == 2 || nCntBG == 3)
		{
			//頂点・座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y - 50.0f, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y - 50.0f, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y + 50.0f, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y + 50.0f, DEF_POS_Z);
		}
		else if (nCntBG == 4)
		{
			//頂点・座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos[nCntBG].x - 60.0f, pos[nCntBG].y - 120.0f, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(pos[nCntBG].x + 60.0f, pos[nCntBG].y - 120.0f, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(pos[nCntBG].x - 60.0f, pos[nCntBG].y + 120.0f, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(pos[nCntBG].x + 60.0f, pos[nCntBG].y + 120.0f, DEF_POS_Z);
		}
		else if (nCntBG == 5)
		{
			//頂点・座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y - 150.0f, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y - 150.0f, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y + 150.0f, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y + 150.0f, DEF_POS_Z);
		}

		pVtx += 4;			//頂点データのポインタを４つ分進める
	}

	pPlayer->nJudgeDirection = -1;

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//==============================================================
//背景の描画処理
//==============================================================
void Drawbg(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[nCntBG]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			nCntBG * 4,										//プリミティブ（ポリゴンの数）
			2);												//描画するプリミティブ数
	}
}
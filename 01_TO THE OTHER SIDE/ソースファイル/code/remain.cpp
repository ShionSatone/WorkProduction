//==============================================================
//
//DirectX[remain.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"main.h"
#include"remain.h"
#include"player.h"

//マクロ定義
#define NUM_REMAIN			(5)			//残機表示の数
#define DEF_RHW				(1.0f)		//rhwの初期値
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(1.0f)		//テクスチャの下yの初期値

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRemain/*[NUM_REMAIN]*/ = NULL /*{}*/;	//テクスチャ(3等分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemain = NULL;		//頂点バッファへのポインタ
bool bUseRemain[NUM_REMAIN];							//使われているかいないか

//==============================================================
//残機の初期化処理
//==============================================================
void InitRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntRemain;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\life000.png",
		&g_pTextureRemain);

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{

		bUseRemain[nCntRemain] = true;					//使われている状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_REMAIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemain,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3((nCntRemain * 50.0f) + -50.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((nCntRemain * 50.0f) + 0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((nCntRemain * 50.0f) + -50.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((nCntRemain * 50.0f) + 0.0f, 50.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = DEF_RHW;
		pVtx[1].rhw = DEF_RHW;
		pVtx[2].rhw = DEF_RHW;
		pVtx[3].rhw = DEF_RHW;

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
	g_pVtxBuffRemain->Unlock();
}

//==============================================================
//残機の終了処理
//==============================================================
void UninitRemain(void)
{
	if (g_pTextureRemain != NULL)
	{
		g_pTextureRemain->Release();
		g_pTextureRemain = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRemain != NULL)
	{
		g_pVtxBuffRemain->Release();
		g_pVtxBuffRemain = NULL;
	}
}

//==============================================================
//残機の更新処理
//==============================================================
void UpdateRemain(void)
{
	Player *pPlayer = GetPlayer();
	int nCntRemain;

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		if (bUseRemain[nCntRemain] == true)
		{
			if (pPlayer->nRemain == nCntRemain)
			{
				bUseRemain[nCntRemain] = false;
			}
		}
		else if (bUseRemain[nCntRemain] == false)
		{
			if (pPlayer->nRemain > nCntRemain)
			{
				bUseRemain[nCntRemain] = true;
			}
		}
	}
}

//==============================================================
//残機の描画処理
//==============================================================
void DrawRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntRemain;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRemain, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		if (bUseRemain[nCntRemain] == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRemain);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntRemain * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}
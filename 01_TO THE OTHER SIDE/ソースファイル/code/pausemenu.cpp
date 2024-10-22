//==============================================================
//
//DirectX[PauseMenu.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"pausemenu.h"
#include"input.h"
#include"title.h"
#include"game.h"
#include"fade.h"
#include"sound.h"

//マクロ定義
#define NUM_PAUSE_MENU		(3)		//ポーズ画面の数
#define COL_R				(1.0f)	//赤色の数値
#define COL_G				(1.0f)	//緑色の数値
#define COL_B				(1.0f)	//青色の数値
#define COL_A				(1.0f)	//不透明度の数値

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu[NUM_PAUSE_MENU] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;				//頂点バッファのポインタ
PAUSE_MENU g_pauseMenu;											//ポーズメニュー
int nPauseMenu[NUM_PAUSE_MENU];
bool bUse;

//==============================================================
//ポーズ画面の初期化処理
//==============================================================
void InitPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntPauseMenu;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause000.png",
		&g_pTexturePauseMenu[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_pTexturePauseMenu[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_pTexturePauseMenu[2]);

	g_pauseMenu = PAUSE_MENU_CONTINUE;		//ポーズメニューの初期化

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		nPauseMenu[nCntPauseMenu] = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(280.0f, (nCntPauseMenu * 150) + 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(980.0f, (nCntPauseMenu * 150) + 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(280.0f, (nCntPauseMenu * 150) + 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(980.0f, (nCntPauseMenu * 150) + 200.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMenu->Unlock();
}

//==============================================================
//ポーズ画面の終了処理
//==============================================================
void UninitPauseMenu(void)
{
	int nCntPauseMenu;

	//テクスチャの破棄
	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		if (g_pTexturePauseMenu[nCntPauseMenu] != NULL)
		{
			g_pTexturePauseMenu[nCntPauseMenu]->Release();
			g_pTexturePauseMenu[nCntPauseMenu] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//==============================================================
//ポーズ画面の更新処理
//==============================================================
void UpdatePauseMenu(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntPauseMenu;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		if (GetKeyboardTrigger(DIK_P) == true)
		{//Pキーが押された
			g_pauseMenu = PAUSE_MENU_CONTINUE;		//ポーズメニューの初期化
			nPauseMenu[nCntPauseMenu] = 0;			//選択肢の初期化
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{//Wキーが押された
			if (nPauseMenu[nCntPauseMenu] >= 1)
			{//下へ進む
				nPauseMenu[nCntPauseMenu]--;
			}
			else if (nPauseMenu[nCntPauseMenu] == 0)
			{//CONTINUEに戻る
				nPauseMenu[nCntPauseMenu] = 2;
			}
		}
		else if (GetKeyboardTrigger(DIK_S) == true)
		{//Sキーが押された
			if (nPauseMenu[nCntPauseMenu] == 2)
			{//QUITに戻る
				nPauseMenu[nCntPauseMenu] = 0;
			}
			else if (nPauseMenu[nCntPauseMenu] >= 0)
			{//上へ進む
				nPauseMenu[nCntPauseMenu]++;
			}
		}

		switch (nPauseMenu[nCntPauseMenu])
		{//モード選択
		case PAUSE_MENU_CONTINUE:
			g_pauseMenu = PAUSE_MENU_CONTINUE;
			break;

		case PAUSE_MENU_RETRY:
			g_pauseMenu = PAUSE_MENU_RETRY;
			break;

		case PAUSE_MENU_QUIT:
			g_pauseMenu = PAUSE_MENU_QUIT;
			break;
		}

		if (g_pauseMenu == nCntPauseMenu)
		{//選択している
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		}

		if (g_pauseMenu != nCntPauseMenu)
		{//選択していない
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		}

		pVtx += 4;			//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMenu->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//決定キー（ENTERキー）が押された
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			//ゲーム再開
			SetEnablePauseMenu(false);
			break;

		case PAUSE_MENU_RETRY:
			//モード設定(ゲーム画面の最初に移行)
			SetFade(MODE_GAME);				//フェードアウト
			break;

		case PAUSE_MENU_QUIT:
			//モード設定(タイトル画面に移行)
			SetFade(MODE_TITLE);			//フェードアウト
			break;
		}
	}
}

//==============================================================
//ポーズ画面の描画処理
//==============================================================
void DrawPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntPauseMenu;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseMenu[nCntPauseMenu]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			nCntPauseMenu * 4,								//プリミティブ（ポリゴンの数）
			2);												//描画するプリミティブ数
	}
}
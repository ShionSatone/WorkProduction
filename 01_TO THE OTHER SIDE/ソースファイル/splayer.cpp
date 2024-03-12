//==============================================================
//
//DirectX[splayer.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"splayer.h"
#include"input.h"
#include"sblock.h"
#include"player.h"
#include"item.h"
#include"sound.h"

//マクロ定義
#define DEF_POS_X			(100.0f)	//プレイヤーのpos.xの初期値
#define DEF_POS_Y			(150.0f)	//プレイヤーのpos.yの初期値
#define DEF_POS_Z			(0.0f)		//プレイヤーのpos.zの初期値
#define DEF_MOVE			(0.0f)		//移動量の初期値
#define DEF_ROT				(0.0f)		//向きの初期値
#define DEF_RHW				(1.0f)		//rhwの初期値
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(0.25f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(0.5f)		//テクスチャの下yの初期値
#define WIDTH_SPLAYER		(25.0f)		//プレイヤーの幅
#define HEIGHT_SPLAYER		(90.0f)		//プレイヤーの高さ
#define ANGLE_UP			(0.75f)		//角度（上）
#define ANGLE_DOWN			(0.25f)		//角度（下）
#define GROUND_HEIGHT		(660.0f)	//地面の高さ
#define CEIL_HEIGHT			(10.0f)		//天井の高さ
#define POS_X				(3.2f)		//位置更新
#define MOVE_X				(0.2f)		//移動量
#define MOVE_Y				(0.5f)		//移動量(慣性)
#define MOVE_JUMP			(-14.0f)	//移動量(ジャンプの重力)
#define SHADOW_X			(200.0f)	//影のXの位置
#define SHADOW_Y			(220.0f)	//影のYの位置
#define ITEM_POS			(20.0f)		//アイテムの大きさ

//プロトタイプ宣言
void CollisionSPlayer(void);

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureSPlayer = NULL;		//テクスチャ1へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSPlayer = NULL;	//頂点バッファへのポインタ
SPlayer g_SPlayer;									//プレイヤーの情報
int g_nCounterAnimSPlayer;							//アニメーションカウンター
int g_nPatternAnimSPlayer;							//アニメーションパターンNo.
int g_nCounterSSe;									//歩く影のseのカウンター
float g_fLengthSPlayer;								//対角線の長さ
float g_fAngleSPlayer;								//対角線の角度

//==============================================================
//プレイヤーの初期化処理
//==============================================================
void InitSPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\splayer000.png",
		&g_pTextureSPlayer);

	g_nCounterAnimSPlayer = 0;											//カウンターを初期化する
	g_nPatternAnimSPlayer = 0;											//パターンNo.を初期化する
	g_nCounterSSe = 0;
	g_SPlayer.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//位置を初期化する
	g_SPlayer.move = D3DXVECTOR3(DEF_MOVE, DEF_MOVE, DEF_MOVE);			//移動量を初期化する
	g_SPlayer.rot = D3DXVECTOR3(DEF_ROT, DEF_ROT, DEF_ROT);				//向きを初期化する(Z値を使用)
	g_SPlayer.nCounterDirect = 0;										//アニメーションの向きを初期化する
	g_SPlayer.fWidth = WIDTH_SPLAYER;									//幅を初期化
	g_SPlayer.fHeight = HEIGHT_SPLAYER;									//高さを初期化
	g_SPlayer.pBlock = NULL;											//ブロックの情報を初期化
	g_SPlayer.bJump = false;											//ジャンプを使用していない
	g_SPlayer.bDisp = true;												//プレイヤー（影）を使用している


	//対角線の長さを算出する
	g_fLengthSPlayer = sqrtf(WIDTH_SPLAYER * WIDTH_SPLAYER + HEIGHT_SPLAYER * HEIGHT_SPLAYER) * 0.5f;

	//対角線の角度を算出する
	g_fAngleSPlayer = atan2f(WIDTH_SPLAYER, HEIGHT_SPLAYER);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSPlayer,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[1].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[2].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);
	pVtx[3].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);

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
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_DOWN_Y);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT_X, TEX_UP_Y);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_DOWN_Y);

	//頂点バッファをアンロックする
	g_pVtxBuffSPlayer->Unlock();
}

//==============================================================
//プレイヤーの終了処理
//==============================================================
void UninitSPlayer(void)
{
	//テクスチャの破棄
	if (g_pTextureSPlayer != NULL)
	{
		g_pTextureSPlayer->Release();
		g_pTextureSPlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSPlayer != NULL)
	{
		g_pVtxBuffSPlayer->Release();
		g_pVtxBuffSPlayer = NULL;
	}
}

//==============================================================
//プレイヤーの更新処理
//==============================================================
void UpdateSPlayer(void)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();		//プレイヤーの情報を読み込む
	g_nCounterAnimSPlayer++;			//カウンターを加算
	g_nCounterSSe++;

	g_SPlayer.posOld = g_SPlayer.pos;	//前回の位置を保存

	//if (g_SPlayer.pBlock != NULL)
	//{//ブロックに乗っている
	//	g_SPlayer.pos.x += g_SPlayer.pBlock;
	//}
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_nPatternAnimSPlayer = 0;
		}
		else
		{
			if ((g_nCounterAnimSPlayer % 10) == 0)
			{//一定時間経過
				g_nPatternAnimSPlayer += 1;
			}

			//左方向
			g_SPlayer.nCounterDirect = 1;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_nPatternAnimSPlayer = 0;
		}
		else
		{
			if ((g_nCounterAnimSPlayer % 10) == 0)
			{//一定時間経過
				g_nPatternAnimSPlayer += 1;
			}

			//右方向
			g_SPlayer.nCounterDirect = 0;
		}
	}
	else
	{
		g_nPatternAnimSPlayer = 0;
	}

	//プレイヤーを使用しているか
	if (pPlayer->bDisp == false)
	{
		g_SPlayer.bDisp = false;
	}
	else if (pPlayer->bDisp == true)
	{
		g_SPlayer.bDisp = true;
	}

	if (pPlayer->state == PLAYERSTATE_SHADOW)
	{
		CollisionSPlayer();
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (pPlayer->state)
	{
	case PLAYERSTATE_NORMAL:			//通常状態
		//プレイヤー(影)にプレイヤーのposを足す
		g_SPlayer.pos.x = pPlayer->pos.x + SHADOW_X;
		g_SPlayer.pos.y = pPlayer->pos.y - SHADOW_Y;

		break;

	case PLAYERSTATE_SHADOW:			//影状態
		//重力処理
		g_SPlayer.move.y += MOVE_Y;

		//画面外へ行ったとき
		if (g_SPlayer.pos.x - WIDTH_SPLAYER <= 0)
		{
			g_SPlayer.pos.x = WIDTH_SPLAYER;
		}
		else if (g_SPlayer.pos.x + WIDTH_SPLAYER >= SCREEN_WIDTH)
		{
			g_SPlayer.pos.x = SCREEN_WIDTH - WIDTH_SPLAYER;
		}

		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			if (g_SPlayer.bJump == false)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_JUMP000);

				g_SPlayer.bJump = true;
				g_SPlayer.move.y = MOVE_JUMP;
			}
		}

		if (GetKeyboardPress(DIK_A) == true)
		{//Aキーが押された
			if (g_SPlayer.bJump == false)
			{
				if ((g_nCounterSSe % 17) == 0)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_WALK000);
				}
			}

				g_SPlayer.pos.x -= POS_X;

				//移動量を更新（増加させる）
				g_SPlayer.move.x -= MOVE_X;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーが押された
			if (g_SPlayer.bJump == false)
			{
				if ((g_nCounterSSe % 17) == 0)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_WALK000);
				}
			}

			g_SPlayer.pos.x += POS_X;

			//移動量を更新（増加させる）
			g_SPlayer.move.x += MOVE_X;
		}

		//位置を更新
		g_SPlayer.pos.x += g_SPlayer.move.x;
		g_SPlayer.pos.y += g_SPlayer.move.y;

		//移動量を更新
		g_SPlayer.move.x += (0.0f - g_SPlayer.move.x) * 0.1f;
		g_SPlayer.move.z += (0.0f - g_SPlayer.move.z) * 0.2f;

		//ブロックとの当たり判定処理
		if (CollisionSBlock(&g_SPlayer.pos, &g_SPlayer.posOld, &g_SPlayer.move, WIDTH_SPLAYER, HEIGHT_SPLAYER, &g_SPlayer.pBlock) == true)
		{
			g_SPlayer.bJump = false;		//着地状態にする
		}
		else
		{
			g_SPlayer.bJump = true;			//ジャンプ状態にする
		}

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		break;

	case PLAYERSTATE_APPEAR:			//点滅状態
		//プレイヤー(影)にプレイヤーのposを足す
		g_SPlayer.pos.x = pPlayer->pos.x + SHADOW_X;
		g_SPlayer.pos.y = pPlayer->pos.y - SHADOW_Y;
		break;
	}

	if (pPlayer->state != PLAYERSTATE_SHADOW)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[1].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[2].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);
	pVtx[3].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);

	if (g_SPlayer.nCounterDirect == 0)
	{
		//テクスチャ座標の再設定
		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_UP_Y);
		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_UP_Y);
		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
	}
	else if (g_SPlayer.nCounterDirect == 1)
	{
		//テクスチャ座標の再設定
		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSPlayer->Unlock();
}

//==============================================================
//プレイヤーの描画処理
//==============================================================
void DrawSPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_SPlayer.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffSPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureSPlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			0,												//プリミティブ（ポリゴンの数）
			2);												//描画するプリミティブ数
	}
}

//==============================================================
//プレイヤーとアイテムのヒット処理
//==============================================================
void CollisionSPlayer(void)
{
	Item *pItem = GetItem();
	Player *pPlayer = GetPlayer();
	int nCntPlayer;

	for (nCntPlayer = 0; nCntPlayer < 128; nCntPlayer++, pItem++)
	{
		if (pItem->bUse == true)
		{//敵が使用されている
			switch (pItem->nType)
			{
			case 0:		//アイテム
				if (g_SPlayer.pos.x + g_SPlayer.fWidth >= pItem->pos.x - ITEM_POS && g_SPlayer.pos.x - g_SPlayer.fWidth <= pItem->pos.x + ITEM_POS
					&& g_SPlayer.pos.y >= pItem->pos.y - ITEM_POS && g_SPlayer.pos.y - g_SPlayer.fHeight <= pItem->pos.y + ITEM_POS)
				{//アイテムに当たった
					HitItem();
					pItem->bUse = false;
				}
				break;

			case 1:
				if (g_SPlayer.pos.x + g_SPlayer.fWidth >= pItem->pos.x - ITEM_POS && g_SPlayer.pos.x - g_SPlayer.fWidth <= pItem->pos.x + ITEM_POS
					&& g_SPlayer.pos.y >= pItem->pos.y - ITEM_POS && g_SPlayer.pos.y - g_SPlayer.fHeight <= pItem->pos.y + ITEM_POS)
				{//アイテムに当たった
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_GET000);

					if (pPlayer->nRemain < 5)
					{
						pPlayer->nRemain += 1;
					}
					pItem->bUse = false;
				}
				break;

			case 2:
				if (g_SPlayer.pos.x + g_SPlayer.fWidth >= pItem->pos.x - ITEM_POS && g_SPlayer.pos.x - g_SPlayer.fWidth <= pItem->pos.x + ITEM_POS
					&& g_SPlayer.pos.y >= pItem->pos.y - ITEM_POS && g_SPlayer.pos.y - g_SPlayer.fHeight <= pItem->pos.y + ITEM_POS)
				{//アイテムに当たった
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_GET000);

					if (pPlayer->nRemain < 5)
					{
						pPlayer->nRemain += 1;
					}
					pItem->bUse = false;
				}
				break;
			}
		}
	}
}

//==============================================================
//プレイヤーのヒット処理
//==============================================================
void HitSPlayer(int nDamage, int nType)
{
	
}

//==============================================================
//プレイヤーの取得
//==============================================================
SPlayer *GetSPlayer(void)
{
	return &g_SPlayer;		//敵の情報の先頭アドレスを返す
}
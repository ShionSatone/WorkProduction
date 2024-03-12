//==============================================================
//
//DirectX[player.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"splayer.h"
#include"block.h"
#include"enemy.h"
#include"goal.h"
#include"game.h"
#include"sound.h"

//マクロ定義
#define MAX_TEX				(2)			//テクスチャの最大値
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
#define WIDTH_PLAYER		(25.0f)		//プレイヤーの幅
#define HEIGHT_PLAYER		(90.0f)		//プレイヤーの高さ
#define ANGLE_UP			(0.75f)		//角度（上）
#define ANGLE_DOWN			(0.25f)		//角度（下）
#define GROUND_HEIGHT		(660.0f)	//地面の高さ
#define CEIL_HEIGHT			(10.0f)		//天井の高さ
#define POS_X				(3.2f)		//位置更新
#define MOVE_X				(0.2f)		//移動量
#define MOVE_Y				(0.5f)		//移動量(慣性)
#define MOVE_JUMP			(-14.0f)	//移動量(ジャンプの重力)
#define LIFE_MAX			(1)			//体力の最大値

//プロトタイプ宣言
void CollisionPlayer(void);

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[MAX_TEX] = {};	//テクスチャ1へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;	//頂点バッファへのポインタ
Player g_player;									//プレイヤーの情報
int g_nCounterAnimPlayer;							//アニメーションカウンター
int g_nPatternAnimPlayer;							//アニメーションパターンNo.
int g_nCounterSe;									//歩くseのカウンター
int g_nPatternJump;									//ジャンプ切り替え
float g_fLengthPlayer;								//対角線の長さ
float g_fAnglePlayer;								//対角線の角度
VERTEX_2D g_aVertex[4];								//頂点座標を格納

//==============================================================
//プレイヤーの初期化処理
//==============================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player000.png",
		&g_pTexturePlayer[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\jumpPlayer000.png",
		&g_pTexturePlayer[1]);

	g_nCounterAnimPlayer = 0;											//カウンターを初期化する
	g_nPatternAnimPlayer = 0;											//パターンNo.を初期化する
	g_nCounterSe = 0;													//歩くSEのカウンターを初期化する
	g_nPatternJump = 0;													//ジャンプ切り替えを初期化する
	g_player.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//位置を初期化する
	g_player.move = D3DXVECTOR3(DEF_MOVE, DEF_MOVE, DEF_MOVE);			//移動量を初期化する
	g_player.rot = D3DXVECTOR3(DEF_ROT, DEF_ROT, DEF_ROT);				//向きを初期化する(Z値を使用)
	g_player.state = PLAYERSTATE_NORMAL;								//通常状態にする
	g_player.nLife = LIFE_MAX;											//体力を初期化する
	g_player.nRemain = 5;												//残機を初期化する
	g_player.nCounterDirect = 0;										//アニメーションの向きを初期化する
	g_player.nJudgeDirection = -1;										//画面外に出た時の判定を初期化する
	g_player.nCounterState = 0;											//状態管理カウンターを初期化する
	g_player.nCounterAppear = 0;										//点滅時間を初期化する
	g_player.nCounterRevival = 0;										//プレイヤー復活時間を初期化する
	g_player.fWidth = WIDTH_PLAYER;										//幅を初期化
	g_player.fHeight = HEIGHT_PLAYER;									//高さを初期化
	g_player.pBlock = NULL;												//ブロックの情報を初期化
	g_player.bJump = false;												//ジャンプを使用していない
	g_player.bDisp = true;												//プレイヤーを使用している

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf(WIDTH_PLAYER * WIDTH_PLAYER + HEIGHT_PLAYER * HEIGHT_PLAYER) * 0.5f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(WIDTH_PLAYER, HEIGHT_PLAYER);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, DEF_POS_Z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, DEF_POS_Z);

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
	g_pVtxBuffplayer->Unlock();
}

//==============================================================
//プレイヤーの終了処理
//==============================================================
void UninitPlayer(void)
{
	int nCntPlayer;

	//テクスチャの破棄
	for (nCntPlayer = 0; nCntPlayer < MAX_TEX; nCntPlayer++)
	{
		if (g_pTexturePlayer[nCntPlayer] != NULL)
		{
			g_pTexturePlayer[nCntPlayer]->Release();
			g_pTexturePlayer[nCntPlayer] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}
}

//==============================================================
//プレイヤーの更新処理
//==============================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ
	SPlayer *pSPlayer = GetSPlayer();
	g_nCounterAnimPlayer++;				//カウンターを加算
	g_nCounterSe++;

	g_player.posOld = g_player.pos;		//前回の位置を保存

	//if (g_player.pBlock != NULL)
	//{//ブロックに乗っている
	//	g_player.pos.x += g_player.pBlock;
	//}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_player.state == PLAYERSTATE_NORMAL || g_player.state == PLAYERSTATE_SHADOW)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_SHADOW000);

			g_player.state = (g_player.state == PLAYERSTATE_NORMAL) ? PLAYERSTATE_SHADOW : PLAYERSTATE_NORMAL;
			pSPlayer->bJump = true;

		}
	}

	if (g_player.state != PLAYERSTATE_SHADOW)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//Aキーが押された
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_nPatternAnimPlayer = 0;
			}
			else
			{
				if ((g_nCounterAnimPlayer % 10) == 0)
				{//一定時間経過
					g_nPatternAnimPlayer += 1;
				}

				if (g_player.bJump == false)
				{
					if ((g_nCounterSe % 17) == 0)
					{
						//サウンドの再生
						PlaySound(SOUND_LABEL_SE_WALK000);
					}
				}

				g_player.pos.x -= POS_X;

				//移動量を更新（増加させる）
				g_player.move.x -= MOVE_X;

				//左方向
				g_player.nCounterDirect = 1;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーが押された
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_nPatternAnimPlayer = 0;
			}
			else
			{
				if ((g_nCounterAnimPlayer % 10) == 0)
				{//一定時間経過
					g_nPatternAnimPlayer += 1;
				}

				if (g_player.bJump == false)
				{
					if ((g_nCounterSe % 17) == 0)
					{
						//サウンドの再生
						PlaySound(SOUND_LABEL_SE_WALK000);
					}
				}

				g_player.pos.x += POS_X;

				//移動量を更新（増加させる）
				g_player.move.x += MOVE_X;

				//右方向
				g_player.nCounterDirect = 0;
			}
		}
		else
		{
			g_nPatternAnimPlayer = 0;
		}

		//重力処理
		g_player.move.y += MOVE_Y;

		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			if (g_player.bJump == false)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_JUMP000);

				g_player.bJump = true;
				g_player.move.y = MOVE_JUMP;
				g_nPatternJump = 1;
			}
		}

		//位置を更新
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		//移動量を更新
		g_player.move.x += (0.0f - g_player.move.x) * 0.1f;
		g_player.move.z += (0.0f - g_player.move.z) * 0.2f;

		//向きを更新
		g_player.rot.z += g_player.move.z;

		//画面外に出た場合
		if (g_player.pos.x - WIDTH_PLAYER + 5.0f <= 0)
		{//左に出た場合
			g_player.pos.x = SCREEN_WIDTH - WIDTH_PLAYER;
			g_player.pos.y = 660.0f;
			g_player.nJudgeDirection = 0;
		}
		else if (g_player.pos.x + WIDTH_PLAYER - 5.0f >= SCREEN_WIDTH)
		{//右に出た場合
			g_player.pos.x = WIDTH_PLAYER;
			g_player.pos.y = 660.0f;
			g_player.nJudgeDirection = 1;
		}
		else if (g_player.pos.y - HEIGHT_PLAYER >= SCREEN_HEIGHT)
		{//下に落ちた場合
			//プレイヤーのヒット処理
			HitPlayer(LIFE_MAX, 0);
		}
		else
		{
			//ブロックとの当たり判定処理
			if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, WIDTH_PLAYER, HEIGHT_PLAYER, &g_player.pBlock) == true)
			{
				g_player.bJump = false;		//着地状態にする
			}
			else
			{
				g_player.bJump = true;		//ジャンプ状態にする
			}

			if (g_player.state != PLAYERSTATE_APPEAR)
			{
				//敵との当たり判定処理
				if (CollisionEnemy(&g_player.pos, &g_player.posOld, &g_player.move, WIDTH_PLAYER, HEIGHT_PLAYER) == true)
				{
					g_player.bJump = false;		//着地状態にする
				}
			}
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, DEF_POS_Z);

		if (g_player.nCounterDirect == 0)
		{
			//テクスチャ座標の再設定
			pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_UP_Y);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_UP_Y);
			pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		}
		else if (g_player.nCounterDirect == 1)
		{
			//テクスチャ座標の再設定
			pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
			pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		}
		//else if (g_nPatternJump == 1)
		//{
		//	if (g_player.nCounterDirect == 0)
		//	{
		//		//テクスチャ座標の再設定
		//		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_UP_Y);
		//		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_UP_Y);
		//		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_DOWN_Y);
		//		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		//	}
		//	else if (g_player.nCounterDirect == 1)
		//	{
		//		//テクスチャ座標の再設定
		//		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_DOWN_Y);
		//		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		//		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		//		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		//	}
		//	
		//}

		//頂点バッファをアンロックする
		g_pVtxBuffplayer->Unlock();
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:
		if ((g_player.nCounterAppear % 3) == 0)
		{
			g_player.bDisp = (g_player.bDisp == false) ? true : false;
		}

		if (g_player.nCounterAppear > 0)
		{
			g_player.nCounterAppear--;
		}
		else if (g_player.nCounterAppear <= 0)
		{
			g_player.bDisp = true;
			g_player.state = PLAYERSTATE_NORMAL;
		}

		break;

	case PLAYERSTATE_NORMAL:
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		CollisionPlayer();
		break;

	case PLAYERSTATE_SHADOW:
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		}

		break;

	case PLAYERSTATE_WAIT:
		g_player.nCounterRevival++;
		g_player.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);			//位置を初期化する

		if (g_player.nCounterRevival >= 80)
		{//プレイヤー復活
			g_player.nCounterAppear = 99;
			g_player.state = PLAYERSTATE_APPEAR;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			g_player.nLife = LIFE_MAX;
			g_player.nCounterRevival = 0;
		}
		break;

	case PLAYERSTATE_DEATH:
		
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffplayer->Unlock();
}

//==============================================================
//プレイヤーの描画処理
//==============================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntPlayer;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPlayer = 0; nCntPlayer < MAX_TEX; nCntPlayer++)
	{
		if (g_player.bDisp == true)
		{
			/*if (g_player.nCounterDirect == 0)
			{*/
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexturePlayer[0]);
			//}
			//else if (g_player.nCounterDirect == 1)
			//{
			//	//テクスチャの設定
			//	pDevice->SetTexture(0, g_pTexturePlayer[0]);
			//}
			//else if (g_nPatternJump == 1)
			//{
			//	if (g_player.nCounterDirect == 0)
			//	{
			//		//テクスチャの設定
			//		pDevice->SetTexture(0, g_pTexturePlayer[1]);
			//	}
			//	else if (g_player.nCounterDirect == 1)
			//	{
			//		//テクスチャの設定
			//		pDevice->SetTexture(0, g_pTexturePlayer[1]);
			//	}
			//}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntPlayer * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}

//==============================================================
//プレイヤーとゴールの当たり判定処理
//==============================================================
void CollisionPlayer(void)
{
	Goal *pGoal = GetGoal();		//敵の情報の先頭アドレスが代入される

	if (pGoal->bUse == true)
	{//敵が使用されている
		switch (pGoal->nType)
		{
		case 0:		//ゴール
			if (g_player.pos.x >= pGoal->pos.x - 50.0f && g_player.pos.x <= pGoal->pos.x + 50.0f 
				&& g_player.pos.y >= pGoal->pos.y - 50.0f && g_player.pos.y <= pGoal->pos.y + 50.0f)
			{//ゴールに当たった
				//ゲーム状態の設定
				SetGameState(GAMESTATE_END, 50);

				pGoal->bUse = false;
			}
			break;
		}
	}
}

//==============================================================
//プレイヤーのヒット処理
//==============================================================
void HitPlayer(int nDamage, int nType)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ
	Goal *pGoal = GetGoal();

	g_player.nLife -= nDamage;

	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_DAMAGE000);

	if (g_player.nLife <= 0)
	{//プレイヤーの体力がなくなった
		g_player.nRemain--;
		
		g_player.bDisp = false;

		if (g_player.nRemain != 0)
		{
			g_player.state = PLAYERSTATE_WAIT;
		}
		else if (g_player.nRemain <= 0)
		{
			g_player.state = PLAYERSTATE_DEATH;

			//ゲーム状態の設定
			SetGameState(GAMESTATE_END, 50);
		}
	}
	else if (g_player.nLife != 0)
	{//プレイヤーの体力が残っている
		g_player.state = PLAYERSTATE_DAMAGE;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.nCounterState = 5;			//ダメージ状態を保つ時間を設定

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffplayer->Unlock();
	}
}

//==============================================================
//プレイヤーの取得
//==============================================================
Player *GetPlayer(void)
{
	return &g_player;		//敵の情報の先頭アドレスを返す
}
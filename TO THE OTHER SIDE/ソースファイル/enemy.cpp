//==============================================================
//
//DirectX[enemy.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"main.h"
#include"enemy.h"
#include"input.h"
#include"player.h"
#include"exit.h"
#include"particle.h"
#include"game.h"
#include"sound.h"

//マクロ定義
#define NUM_ENEMY		(2)			//敵の種類
#define DEF_POS_Z		(0.0f)		//プレイヤーのpos.zの初期値
#define COL_R			(1.0f)		//赤色の数値
#define COL_G			(1.0f)		//緑色の数値
#define COL_B			(1.0f)		//青色の数値
#define COL_A			(1.0f)		//不透明度の数値
#define TEX_LEFT_X		(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X		(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y		(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y		(1.0f)		//テクスチャの下yの初期値
#define TEX_NUM			(2)			//テクスチャの数
#define TEX_NUM_SIDE	(0.5f)		//横のテクスチャ
#define TEX_NUM_VER		(1.0f)		//縦のテクスチャ
#define BOSS_WIDTH		(90.0f)		//ボスの幅
#define BOSS_HEIGHT		(170.0f)	//ボスの高さ
#define ENEMY_WIDTH		(30.0f)		//雑魚敵の幅
#define ENEMY_HEIGHT	(60.0f)		//雑魚敵の高さ
#define PLAYER_WIDTH	(25.0f)		//プレイヤーの引く幅
#define PLAYER_HEIGHT	(25.0f)		//プレイヤーの引く高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファのポインタ
Enemy g_aEnemy[MAX_ENEMY];									//敵の種類
int g_nCounterEnemy;										//弾のカウンター
int g_nNumEnemy;											//敵の総数
int g_nCounterBgm;											//BGMカウンター
int nCounterPar;											//パーティクル発動カウンターを初期化


//==============================================================
//敵の初期化処理
//==============================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy001.png",
		&g_pTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy000.png",
		&g_pTextureEnemy[1]);

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);			//位置の初期化
		g_aEnemy[nCntEnemy].pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置2の初期化
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aEnemy[nCntEnemy].nType = nCntEnemy;							//敵の種類の初期化
		g_aEnemy[nCntEnemy].nLife = 1;									//敵の体力の初期化
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					//敵の状態の初期化
		g_aEnemy[nCntEnemy].fWidth = BOSS_WIDTH;						//ボスの幅を初期化
		g_aEnemy[nCntEnemy].fHeight = BOSS_HEIGHT;						//ボスの高さを初期化
		g_aEnemy[nCntEnemy].g_fLengthEnemy = 0;							//対角線の長さの初期化
		g_aEnemy[nCntEnemy].g_fAngleEnemy = 0;							//対角線の角度の初期化
		g_aEnemy[nCntEnemy].nCounterAnimEnemy = 0;						//アニメーションカウンター0の初期化
		g_aEnemy[nCntEnemy].nPatternAnimEnemy = 0;						//パターンNo.の初期化0
		g_aEnemy[nCntEnemy].nCounterMove = 0;							//敵の移動カウンターの初期化
		g_aEnemy[nCntEnemy].fCurve = 0.0f;								//角度の初期化
		g_aEnemy[nCntEnemy].fBossPos = 0.0f;							//ボスの降下制限の初期化
		g_aEnemy[nCntEnemy].nCounterBulletTime = 0;						//敵が打つ時間を初期化
		g_aEnemy[nCntEnemy].bUse = false;								//使用していない状態にする
		g_aEnemy[nCntEnemy].bJump = false;
	}

	g_nNumEnemy = 0;													//敵の総数の初期化
	g_nCounterBgm = 0;
	nCounterPar = 0;							//パーティクル発動カウンターを初期化

	//対角線の長さを算出する
	g_aEnemy[nCntEnemy].g_fLengthEnemy = sqrtf(80.0f * 80.0f + 20.0f * 20.0f) * 0.5f;

	//対角線の角度を算出する
	g_aEnemy[nCntEnemy].g_fAngleEnemy = atan2f(80.0f, 20.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);

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
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//敵の終了処理
//==============================================================
void UninitEnemy(void)
{
	int nCntEnemy;

	//テクスチャの破棄
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//==============================================================
//敵の更新処理
//==============================================================
void UpdateEnemy(void)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ
	Player *pPlayer = GetPlayer();
	int nCntEnemy;
	int nMove;							//敵のランダムな行動を入れる

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使われているとき
			g_aEnemy[nCntEnemy].nCounterMove++;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			if (pPlayer->nJudgeDirection == 0)
			{
				g_aEnemy[nCntEnemy].pos.x += SCREEN_WIDTH;
				g_aEnemy[nCntEnemy].pos.y = 650.0f;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{
				g_aEnemy[nCntEnemy].pos.x -= SCREEN_WIDTH;
				g_aEnemy[nCntEnemy].pos.y = 650.0f;
			}
			else
			{
				if (CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, &g_aEnemy[nCntEnemy].pBlock) == true)
				{
					g_aEnemy[nCntEnemy].bJump = false;

					if (g_aEnemy[nCntEnemy].nType == 0)
					{
						nCounterPar += 1;

						if (nCounterPar <= 1)
						{
							SetParticle(g_aEnemy[nCntEnemy].pos, 0);
						}
					}
				}
				else
				{
					if (g_aEnemy[nCntEnemy].nType == 0)
					{
						nCounterPar = 0;
					}
					g_aEnemy[nCntEnemy].bJump = true;
				}
			}

			if (g_aEnemy[nCntEnemy].pos.x >= 0 && g_aEnemy[nCntEnemy].pos.x <= SCREEN_WIDTH)
			{
				g_aEnemy[nCntEnemy].move.y += 0.5f;
			}
			else
			{
				g_aEnemy[nCntEnemy].move.y = 0.0f;
			}

			if (g_aEnemy[nCntEnemy].nType == 0)
			{//ボス
				g_aEnemy[nCntEnemy].nCounterAnimEnemy++;

				nMove = rand() % 5 + 1;

				if (g_nCounterBgm == 50)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_BGMBOSS);
				}

				g_nCounterBgm += 1;

				if ((g_aEnemy[nCntEnemy].nCounterMove % 150) == 0)
				{
					//敵を移動させる
					g_aEnemy[nCntEnemy].move.y -= 20.0f;

					switch (nMove)
					{
					case 1:
						if (g_aEnemy[nCntEnemy].pos.x - BOSS_WIDTH >= BOSS_WIDTH + 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x -= 100.0f;
						}
						break;

					case 2:
						if (g_aEnemy[nCntEnemy].pos.x + BOSS_WIDTH <= SCREEN_WIDTH - BOSS_WIDTH - 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x += 100.0f;
						}
						break;

					case 3:
						if (g_aEnemy[nCntEnemy].pos.x - BOSS_WIDTH >= BOSS_WIDTH + 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x -= 50.0f;
						}
						break;

					case 4:
						if (g_aEnemy[nCntEnemy].pos.x + BOSS_WIDTH <= SCREEN_WIDTH - BOSS_WIDTH - 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x += 50.0f;
						}
						break;

					case 5:

						break;
					}
				}
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{//雑魚敵
				g_aEnemy[nCntEnemy].nCounterAnimEnemy++;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);

			if (g_aEnemy[nCntEnemy].nType == 0 && g_aEnemy[nCntEnemy].nLife == 0)
			{
				SetGameState(GAMESTATE_END, 50);
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
					pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
					pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
					pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
				}
				break;

			case ENEMYSTATE_WAIT:

				break;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnimEnemy % 30) == 0)
			{//一定時間経過
				g_aEnemy[nCntEnemy].nPatternAnimEnemy = (g_aEnemy[nCntEnemy].nPatternAnimEnemy + 1) % 2;

				//テクスチャ座標の再設定
				pVtx[0].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER);
				pVtx[1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE + TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER);
				pVtx[2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER + TEX_NUM_VER);
				pVtx[3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE + TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER + TEX_NUM_VER);
			}
		}
		pVtx += 4;									//頂点データのポインタを４つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//敵の描画処理
//==============================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている	
			//テクスチャの設定
			if (g_aEnemy[nCntEnemy].nType == 0)
			{
				pDevice->SetTexture(0, g_pTextureEnemy[0]);
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{
				pDevice->SetTexture(0, g_pTextureEnemy[1]);
			}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
				nCntEnemy * 4,									//プリミティブ（ポリゴンの数）
				2);												//描画するプリミティブ数
		}
	}
}

//==============================================================
//敵の設定処理
//==============================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].pos2 = pos;
			g_aEnemy[nCntEnemy].nType = nType;

			if (g_aEnemy[nCntEnemy].nType == 0)
			{//ボス
				g_aEnemy[nCntEnemy].fWidth = BOSS_WIDTH;
				g_aEnemy[nCntEnemy].fHeight = BOSS_HEIGHT;
				g_aEnemy[nCntEnemy].nLife = 16;

				g_nNumEnemy++;
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{//雑魚敵
				g_aEnemy[nCntEnemy].fWidth = ENEMY_WIDTH;
				g_aEnemy[nCntEnemy].fHeight = ENEMY_HEIGHT;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

			g_aEnemy[nCntEnemy].bUse = true;		//使用している状態にする

			break;
		}
		pVtx += 4;									//頂点データのポインタを４つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//敵との当たり判定処理
//==============================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	int nCntEnemy;
	bool bLand = false;		//着地したかどうか

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].nType == 0)
			{
				if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f)
				{//下にめり込んだ場合
					bLand = true;

					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_ENEMY000);

					//敵のヒット処理
					HitEnemy(nCntEnemy, 1);
					pPos->y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;										//敵の上に立たせる
					pMove->y = -14.0f;																						//移動量を０にする
				}
				else if (pPosOld->y - fHeight >= g_aEnemy[nCntEnemy].pos.y
					&& pPos->y - fHeight <= g_aEnemy[nCntEnemy].pos.y
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f)
				{//上にめり込んだ場合
					bLand = false;

					//プレイヤーのヒット処理
					HitPlayer(1, 0);

					pPos->y = g_aEnemy[nCntEnemy].pos.y + fHeight + PLAYER_HEIGHT;											//敵の下に立たせる
					pMove->y = 0.0f;																						//移動量を０にする
				}
				else if (pPosOld->x + fWidth <= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->x + fWidth >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//左にめり込んだ場合
					bLand = false;

					//プレイヤーのヒット処理
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth - fWidth + 40.0f;						//敵の左に立たせる
					pMove->x = 0.0f;																						//移動量を０にする
				}
				else if (pPosOld->x - fWidth >= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f
					&& pPos->x - fWidth <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//右にめり込んだ場合
					bLand = false;

					//プレイヤーのヒット処理
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + fWidth - 40.0f;						//敵の左に立たせる
					pMove->x = 0.0f;																						//移動量を０にする
				}
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{
				if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f)
				{//下にめり込んだ場合
					bLand = true;

					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_ENEMY000);

					//敵のヒット処理
					HitEnemy(nCntEnemy, 1);
					pPos->y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;										//敵の上に立たせる
					pMove->y = -14.0f;																						//移動量を０にする
				}
				else if (pPosOld->y - fHeight >= g_aEnemy[nCntEnemy].pos.y
					&& pPos->y - fHeight <= g_aEnemy[nCntEnemy].pos.y
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f)
				{//上にめり込んだ場合
					bLand = false;

					//プレイヤーのヒット処理
					HitPlayer(1, 0);

					pPos->y = g_aEnemy[nCntEnemy].pos.y + fHeight + PLAYER_HEIGHT;											//敵の下に立たせる
					pMove->y = 0.0f;																						//移動量を０にする
				}
				else if (pPosOld->x + fWidth <= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->x + fWidth >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//左にめり込んだ場合
					bLand = false;

					//プレイヤーのヒット処理
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth - fWidth + 10.0f;						//敵の左に立たせる
					pMove->x = 0.0f;																						//移動量を０にする
				}
				else if (pPosOld->x - fWidth >= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f
					&& pPos->x - fWidth <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//右にめり込んだ場合
					bLand = false;

					//プレイヤーのヒット処理
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + fWidth - 10.0f;						//敵の左に立たせる
					pMove->x = 0.0f;																						//移動量を０にする
				}
			}
		}
	}

	return bLand;
}


//==============================================================
//敵の取得
//==============================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];		//敵の情報の先頭アドレスを返す
}

//==============================================================
//敵のヒット処理
//==============================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D *pVtx;					//頂点情報へのポインタ

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife == 0)
	{//敵の体力がなくなった
		//敵が消える処理
		SetExit(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nType);

		if (g_aEnemy[nCntEnemy].nType == 0)
		{
			g_nNumEnemy--;

			//サウンドの停止
			StopSound();
		}

		if (g_nNumEnemy <= 0 && g_aEnemy[nCntEnemy].nType == 0)
		{
			SetGameState(GAMESTATE_END, 50);
		}

		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{//敵の体力が残っている
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;			//ダメージ状態を保つ時間を設定

		//サウンドの再生
		//PlaySound(SOUND_LABEL_SE_HIT002);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntEnemy * 4;							//頂点データのポインタを４つ分集める

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
	}
}

//==============================================================
//敵の数を引く処理
//==============================================================
void SubNumEnemy(void)
{
	g_nNumEnemy--;
}

//==============================================================
//敵の総数の取得
//==============================================================
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}
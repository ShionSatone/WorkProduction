//==============================================================
//
//DirectX[particle.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"main.h"
#include"particle.h"
#include"effect.h"
#include"player.h"
#include"enemy.h"

//マクロ定義
#define MAX_PARTICLE		(128)		//パーティクルの最大数

//パーティクル構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置（発生位置）
	int nLife;				//寿命（発生時間）
	D3DXCOLOR col;			//色
	float fRadius;			//半径（大きさ）
	int nType;				//種類
	bool bUse;				//使用しているかどうか
} Particle;

//グローバル変数
Particle g_aParticle[MAX_PARTICLE];							//パーティクルの情報

//==============================================================
//パーティクルの初期化処理
//==============================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//デバイスの取得
	pDevice = GetDevice();

	//弾の情報の初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置（発生位置）の初期化
		g_aParticle[nCntParticle].nLife = 0;								//寿命（発生時間）の初期化
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色の初期化
		g_aParticle[nCntParticle].fRadius = 10.0f;							//半径の初期化
		g_aParticle[nCntParticle].nType = 0;								//種類の初期化
		g_aParticle[nCntParticle].bUse = false;								//使用していない状態にする
	}
}

//==============================================================
//パーティクルの終了処理
//==============================================================
void UninitParticle(void)
{
	
}

//==============================================================
//パーティクルの更新処理
//==============================================================
void UpdateParticle(void)
{
	int nCntParticle, nCntAppear, nLife;
	float fAngle, fMove, fRadius;
	D3DXVECTOR3 move, pos;
	D3DXCOLOR col;
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//パーティクルが使用されている
			//パーティクルの生成
			for (nCntAppear = 0; nCntAppear < 5; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 0)
				{
					//位置の設定
					pos = pEnemy->pos;

					//角度を求める
					fAngle = (float)(rand() % 314 - 624) / 100.0f;

					//移動量を求める
					fMove = (float)(rand() % 100) / 10.0f + 8.0f;

					//移動量の設定
					move.x = sinf(fAngle) * fMove;
					move.y = cosf(fAngle) * fMove;

					//色の設定
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//半径の設定
					fRadius = 0.5f;

					//寿命の設定
					nLife = g_aParticle[nCntParticle].nLife;
				}

				//エフェクトの設定
				SetEffect(pos,
					move,
					col,
					fRadius,
					nLife);
			}

			//寿命のカウントダウン
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{//寿命が尽きた場合
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}

//==============================================================
//パーティクルの描画処理
//==============================================================
void DrawParticle(void)
{
	
}

//==============================================================
//パーティクルの設定処理
//==============================================================
void SetParticle(D3DXVECTOR3 pos, int nType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//パーティクルが使用されていない
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;

			/*if (g_aParticle[nCntParticle].nType == 0)
			{*/
				g_aParticle[nCntParticle].nLife = 7;
			//}

			g_aParticle[nCntParticle].bUse = true;		//使用している状態にする

			break;
		}
	}
}
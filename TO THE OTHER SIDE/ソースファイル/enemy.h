//==============================================================
//
//DirectX[enemy.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"
#include"block.h"

//マクロ定義
#define MAX_ENEMY		(128)		//敵の最大数

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,			//通常状態
	ENEMYSTATE_DAMAGE,				//ダメージ状態
	ENEMYSTATE_WAIT,				//出現待ち状態(表示なし)
	ENEMYSTATE_DEATH,				//死亡状態
	ENEMYSTATE_MAX
} ENEMYSTATE;

//敵構造他の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置(現在)
	D3DXVECTOR3 posOld;		//位置
	D3DXVECTOR3 pos2;		//位置（仮入れ）
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	int nType;				//種類
	int nLife;				//体力
	ENEMYSTATE state;		//状態
	float fWidth;			//幅
	float fHeight;			//高さ
	float g_fLengthEnemy;	//対角線の長さ
	float g_fAngleEnemy;	//対角線の角度
	float fCurve;			//角度
	float fBossPos;			//ボスの降下制限
	int nCounterState;		//状態管理カウンター
	int nCounterAnimEnemy;	//アニメーションカウンター
	int nPatternAnimEnemy;	//パターンNo.
	int nCounterMove;		//敵の移動カウンター
	int nCounterBulletTime;	//敵が打つ時間
	bool bUse;				//使用しているかどうか
	bool bJump;				//ジャンプを使用しているか
	Block *pBlock;			//ブロックの情報
} Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int nDamage);
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);
Enemy *GetEnemy(void);
int GetNumEnemy(void);
void SubNumEnemy(void);

#endif
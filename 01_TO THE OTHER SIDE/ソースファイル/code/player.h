//==============================================================
//
//DirectX[player.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _PLAYER_H_				//このマクロ定義がされていなかったら
#define _PLAYER_H_				//2重インクルード防止のマクロを定義する

#include"main.h"
#include"block.h"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,			//出現状態(点滅)
	PLAYERSTATE_NORMAL,				//通常状態
	PLAYERSTATE_SHADOW,				//影状態
	PLAYERSTATE_DAMAGE,				//ダメージ状態
	PLAYERSTATE_WAIT,				//出現待ち状態(表示なし)
	PLAYERSTATE_DEATH,				//死亡状態
	PLAYERSTATE_MAX
} PLAYERSTATE;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量
	PLAYERSTATE state;		//状態
	int nLife;				//体力
	int nRemain;			//残機
	int nCounterDirect;		//アニメーションの方向
	int nJudgeDirection;	//画面外に出た時の判定
	int nCounterState;		//状態管理カウンター
	int nCounterAppear;		//点滅の時間
	int nCounterRevival;	//プレイヤー復活時間
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bJump;				//ジャンプしているか
	bool bDisp;				//プレイヤーを使用しているか
	Block *pBlock;			//ブロックの情報
} Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage, int nType);
void CollisionPlayer(void);
Player *GetPlayer(void);

#endif

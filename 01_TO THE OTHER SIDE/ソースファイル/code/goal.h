//==============================================================
//
//DirectX[goal.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _GOAL_H_				//このマクロ定義がされていなかったら
#define _GOAL_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//ブロックのテクスチャ
typedef enum
{
	GOALTYPE_GROUND = 0,		//地面
	GOALTYPE_WALL,				//壁
	GOALTYPE_GOAL,			//1マスブロック
	GOALTYPE_MAX
} GoalTYPE;

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
	int nCounterGoal;		//ブロックの動きのカウンター
	bool bUse;				//使用しているかどうか
	bool bShadowUse;		//実物かの判定
} Goal;

//プロトタイプ宣言
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos, int nType);
bool CollisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Goal **pGoal);
Goal *GetGoal(void);

#endif
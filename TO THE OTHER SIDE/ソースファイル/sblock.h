//==============================================================
//
//DirectX[sblock.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _SBLOCK_H_				//このマクロ定義がされていなかったら
#define _SBLOCK_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
	int nCounterSBlock;		//ブロックの動きのカウンター
	bool bUse;				//使用しているかどうか
} SBlock;

//プロトタイプ宣言
void InitSBlock(void);
void UninitSBlock(void);
void UpdateSBlock(void);
void DrawSBlock(void);
void SetSBlock(D3DXVECTOR3 pos, int nType);
bool CollisionSBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, SBlock **pBlock);
void CollisionSButton(int nCntSBlock);

#endif
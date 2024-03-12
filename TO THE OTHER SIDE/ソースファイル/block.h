//==============================================================
//
//DirectX[sblock.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _BLOCK_H_				//このマクロ定義がされていなかったら
#define _BLOCK_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//ブロックのテクスチャ
typedef enum
{
	BLOCKTYPE_GROUND = 0,		//地面
	BLOCKTYPE_WALL,				//壁
	BLOCKTYPE_BLOCK,			//1マスブロック
	BLOCKTYPE_MAX
} BLOCKTYPE;

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
	int nCounterBlock;		//ブロックの動きのカウンター
	bool bUse;				//使用しているかどうか
} Block;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Block **pBlock);

#endif
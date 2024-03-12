//==============================================================
//
//DirectX[item.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _ITEM_H_				//このマクロ定義がされていなかったら
#define _ITEM_H_				//2重インクルード防止のマクロを定義する

#include"main.h"

//ブロックのテクスチャ
typedef enum
{
	ITEMTYPE_GROUND = 0,		//地面
	ITEMTYPE_WALL,				//壁
	ITEMTYPE_Item,			//1マスブロック
	ITEMTYPE_MAX
} ITEMTYPE;

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
	int nCounterItem;		//ブロックの動きのカウンター
	bool bUse;				//使用しているかどうか
	bool bShadowUse;		//実物かの判定
} Item;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType);
void HitItem(void);
Item *GetItem(void);
int GetNumItem(void);

#endif
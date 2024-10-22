//==============================================================
//
//DirectX[splayer.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _SPLAYER_H_				//このマクロ定義がされていなかったら
#define _SPLAYER_H_				//2重インクルード防止のマクロを定義する

#include"main.h"
#include"sblock.h"

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量
	int nCounterDirect;		//アニメーションの方向
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bJump;				//ジャンプしているか
	bool bDisp;				//プレイヤー（影）を使用しているか
	SBlock *pBlock;			//ブロックの情報
} SPlayer;

//プロトタイプ宣言
void InitSPlayer(void);
void UninitSPlayer(void);
void UpdateSPlayer(void);
void DrawSPlayer(void);
void HitSPlayer(int nDamage, int nType);
SPlayer *GetSPlayer(void);

#endif

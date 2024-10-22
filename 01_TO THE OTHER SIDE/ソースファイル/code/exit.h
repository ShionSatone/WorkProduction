//==============================================================
//
//DirectX[exit.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _EXIT_H_
#define _EXIT_H_

#include"main.h"

//プロトタイプ宣言
void InitExit(void);
void UninitExit(void);
void UpdateExit(void);
void DrawExit(void);
void SetExit(D3DXVECTOR3 pos, D3DXCOLOR move, int nType);

#endif
//==============================================================
//
//DirectX[Set.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include"Set.h"
#include"block.h"
#include"sblock.h"

//マクロ定義
#define MAX_BLOCK		(128)				//ブロックの最大数
#define MAX_SBLOCK		(128)				//ブロック(影)の最大数

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
} SetData;

//ブロック(影)構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
} SSetData;

//グローバル変数宣言
SetData g_aSet[MAX_BLOCK];			//ブロック
SSetData g_aSSet[MAX_SBLOCK];		//ブロック(影)
int nCounter = 0;					//ブロック数のカウンター
int nSCounter = 0;					//ブロック(影)数のカウンター

//==============================================================
//ブロックの外部ファイル読み込み
//==============================================================
void Load(void)
{
	FILE *pFile;		//ブロックファイル
	int nCntSet = 0;
	int nResult;

	nCounter = 0;

	//ファイルを読み込む
	pFile = fopen("data\\TEXT\\block.txt", "r");

	if (pFile != NULL)
	{//ファイルがある場合
		while (1)
		{
			nResult = fscanf(pFile, "%f, %f, %f, %d", &g_aSet[nCntSet].pos.x, &g_aSet[nCntSet].pos.y, &g_aSet[nCntSet].pos.z, &g_aSet[nCntSet].nType);


			if (EOF == nResult)
			{
				break;
			}
			nCounter += 1;
			nCntSet += 1;
		}
	}
}

//==============================================================
//ブロックの設定処理
//==============================================================
void Set(void)
{
	int nCntSet;

	for (nCntSet = 0; nCntSet < nCounter; nCntSet++)
	{
		SetBlock(g_aSet[nCntSet].pos, g_aSet[nCntSet].nType);
	}
}

//==============================================================
//ブロック(影)の外部ファイル読み込み
//==============================================================
void SLoad(void)
{
	FILE *pSFile;		//ブロックファイル
	int nCntSet = 0;
	int nResult;

	nSCounter = 0;

	//ファイルを読み込む
	pSFile = fopen("data\\TEXT\\sblock.txt", "r");

	if (pSFile != NULL)
	{//ファイルがある場合
		while (1)
		{
			nResult = fscanf(pSFile, "%f, %f, %f, %d", &g_aSSet[nCntSet].pos.x, &g_aSSet[nCntSet].pos.y, &g_aSSet[nCntSet].pos.z, &g_aSSet[nCntSet].nType);

			if (EOF == nResult)
			{
				break;
			}
			nSCounter += 1;
			nCntSet += 1;
		}
	}
}

//==============================================================
//ブロック(影)の設定処理
//==============================================================
void SSet(void)
{
	int nCntSet;

	for (nCntSet = 0; nCntSet < nSCounter; nCntSet++)
	{
		SetSBlock(g_aSSet[nCntSet].pos, g_aSSet[nCntSet].nType);
	}
}
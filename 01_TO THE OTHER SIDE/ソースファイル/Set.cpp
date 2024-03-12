//==============================================================
//
//DirectX[Set.cpp]
//Author:����������
//
//==============================================================
#include"Set.h"
#include"block.h"
#include"sblock.h"

//�}�N����`
#define MAX_BLOCK		(128)				//�u���b�N�̍ő吔
#define MAX_SBLOCK		(128)				//�u���b�N(�e)�̍ő吔

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
} SetData;

//�u���b�N(�e)�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
} SSetData;

//�O���[�o���ϐ��錾
SetData g_aSet[MAX_BLOCK];			//�u���b�N
SSetData g_aSSet[MAX_SBLOCK];		//�u���b�N(�e)
int nCounter = 0;					//�u���b�N���̃J�E���^�[
int nSCounter = 0;					//�u���b�N(�e)���̃J�E���^�[

//==============================================================
//�u���b�N�̊O���t�@�C���ǂݍ���
//==============================================================
void Load(void)
{
	FILE *pFile;		//�u���b�N�t�@�C��
	int nCntSet = 0;
	int nResult;

	nCounter = 0;

	//�t�@�C����ǂݍ���
	pFile = fopen("data\\TEXT\\block.txt", "r");

	if (pFile != NULL)
	{//�t�@�C��������ꍇ
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
//�u���b�N�̐ݒ菈��
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
//�u���b�N(�e)�̊O���t�@�C���ǂݍ���
//==============================================================
void SLoad(void)
{
	FILE *pSFile;		//�u���b�N�t�@�C��
	int nCntSet = 0;
	int nResult;

	nSCounter = 0;

	//�t�@�C����ǂݍ���
	pSFile = fopen("data\\TEXT\\sblock.txt", "r");

	if (pSFile != NULL)
	{//�t�@�C��������ꍇ
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
//�u���b�N(�e)�̐ݒ菈��
//==============================================================
void SSet(void)
{
	int nCntSet;

	for (nCntSet = 0; nCntSet < nSCounter; nCntSet++)
	{
		SetSBlock(g_aSSet[nCntSet].pos, g_aSSet[nCntSet].nType);
	}
}
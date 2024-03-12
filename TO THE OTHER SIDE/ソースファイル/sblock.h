//==============================================================
//
//DirectX[sblock.h]
//Author:����������
//
//==============================================================
#ifndef _SBLOCK_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SBLOCK_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
	int nCounterSBlock;		//�u���b�N�̓����̃J�E���^�[
	bool bUse;				//�g�p���Ă��邩�ǂ���
} SBlock;

//�v���g�^�C�v�錾
void InitSBlock(void);
void UninitSBlock(void);
void UpdateSBlock(void);
void DrawSBlock(void);
void SetSBlock(D3DXVECTOR3 pos, int nType);
bool CollisionSBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, SBlock **pBlock);
void CollisionSButton(int nCntSBlock);

#endif
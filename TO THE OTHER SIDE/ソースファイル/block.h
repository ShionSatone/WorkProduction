//==============================================================
//
//DirectX[sblock.h]
//Author:����������
//
//==============================================================
#ifndef _BLOCK_H_				//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�u���b�N�̃e�N�X�`��
typedef enum
{
	BLOCKTYPE_GROUND = 0,		//�n��
	BLOCKTYPE_WALL,				//��
	BLOCKTYPE_BLOCK,			//1�}�X�u���b�N
	BLOCKTYPE_MAX
} BLOCKTYPE;

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
	int nCounterBlock;		//�u���b�N�̓����̃J�E���^�[
	bool bUse;				//�g�p���Ă��邩�ǂ���
} Block;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Block **pBlock);

#endif
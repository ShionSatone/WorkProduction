//==============================================================
//
//DirectX[splayer.h]
//Author:����������
//
//==============================================================
#ifndef _SPLAYER_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SPLAYER_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
#include"sblock.h"

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 move;		//�ړ���
	int nCounterDirect;		//�A�j���[�V�����̕���
	float fWidth;			//��
	float fHeight;			//����
	bool bJump;				//�W�����v���Ă��邩
	bool bDisp;				//�v���C���[�i�e�j���g�p���Ă��邩
	SBlock *pBlock;			//�u���b�N�̏��
} SPlayer;

//�v���g�^�C�v�錾
void InitSPlayer(void);
void UninitSPlayer(void);
void UpdateSPlayer(void);
void DrawSPlayer(void);
void HitSPlayer(int nDamage, int nType);
SPlayer *GetSPlayer(void);

#endif

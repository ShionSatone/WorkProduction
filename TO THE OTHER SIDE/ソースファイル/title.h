//==============================================================
//
//DirectX[title.h]
//Author:����������
//
//==============================================================
#ifndef _TITLE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�^�C�g���̏��
typedef enum
{
	TITLESTATE_APPEAR = 0,			//�o�����(�_��)
	TITLESTATE_NORMAL,				//�ʏ���
	TITLESTATE_WAIT,				//�o���҂����(�\���Ȃ�)
	TITLESTATE_MAX
} TITLESTATE;

//�^�C�g���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	TITLESTATE state;		//���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nCounterAppear;		//�_�ł̎���
	int nCounterColor;		//�F�̓����x
	int nCounterRank;		//�����L���O�\���̃J�E���^�[
	bool bUse;				//�\�����邩���Ȃ���
} Title;

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif

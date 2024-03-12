//==============================================================
//
//DirectX[pause.h]
//Author:����������
//
//==============================================================
#ifndef _PAUSE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _PAUSE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�^�C�g���̏��
typedef enum
{
	PAUSESTATE_APPEAR = 0,			//�o�����(�_��)
	PAUSESTATE_NORMAL,				//�ʏ���
	PAUSESTATE_WAIT,				//�o���҂����(�\���Ȃ�)
	PAUSESTATE_MAX
} PAUSESTATE;

//�^�C�g���\���̂̒�`
typedef struct
{
	PAUSESTATE state;		//���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nCounterAppear;		//�_�ł̎���
	bool bUse;				//�\�����邩���Ȃ���
} Pause;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif

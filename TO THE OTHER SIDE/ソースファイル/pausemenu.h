//==============================================================
//
//DirectX[pausemenu.h]
//Author:����������
//
//==============================================================
#ifndef _PAUSEMENU_H_				//���̃}�N����`������Ă��Ȃ�������
#define _PAUSEMENU_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,		//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,				//�Q�[������蒼��
	PAUSE_MENU_QUIT,				//�^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX
} PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPauseMenu(void);
void UninitPauseMenu(void);
void UpdatePauseMenu(void);
void DrawPauseMenu(void);

#endif

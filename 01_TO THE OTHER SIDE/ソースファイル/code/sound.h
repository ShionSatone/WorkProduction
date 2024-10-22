//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ����������
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,			// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_BGM002,				// BGM2
	SOUND_LABEL_BGM003,				// BGM3
	SOUND_LABEL_BGM004,				// BGM4
	SOUND_LABEL_BGMBOSS,			// BGM_BOSS
	SOUND_LABEL_SE_ENTER000,		// ���艹0
	SOUND_LABEL_SE_WALK000,			// ������0
	SOUND_LABEL_SE_JUMP000,			// �W�����v��0
	SOUND_LABEL_SE_ENEMY000,		// ���މ�0
	SOUND_LABEL_SE_BUTTON000,		// �{�^����0
	SOUND_LABEL_SE_DAMAGE000,		// �_���[�W��0
	SOUND_LABEL_SE_SHADOW000,		// �e�؂�ւ���0
	SOUND_LABEL_SE_GET000,			// �A�C�e���Q�b�g0
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

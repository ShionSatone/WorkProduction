//==============================================================
//
//DirectX[input.h]
//Author:����������
//
//==============================================================
#ifndef _INPUT_H
#define _INPUT_H

#include"main.h"
#include"Xinput.h"

#pragma comment(lib,"xinput.lib")

//�Q�[���p�b�h
typedef enum
{
	BUTTON_UP = 0,		//�\���L�[��
	BUTTON_DOWN,		//�\���L�[��
	BUTTON_LEFT,		//�\���L�[��
	BUTTON_RIGHT,		//�\���L�[�E
	BUTTON_START,		//�X�^�[�g�{�^��
	BUTTON_BACK,		//�o�b�N�{�^��
	BUTTON_LSTICK,		//���X�e�B�b�N��������
	BUTTON_RSTICK,		//�E�X�e�B�b�N��������
	BUTTON_LB,			//LB
	BUTTON_RB,			//RB
	//BUTTON_01,			//
	//BUTTON_02,			//
	//BUTTON_A,			//A
	//BUTTON_B,			//B
	//BUTTON_X,			//X
	//BUTTON_Y,			//Y
	BUTTON00,

	BUTTON_MAX
} BUTTON;

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

HRESULT InitGamepad(void);
void UninitGamepad(void);
void UpdateGamepad(void);
bool GetGamepadPress(BUTTON Key, int nPlayer);
bool GetGamepadTrigger(BUTTON Key, int nPlayer);
bool GetGamepadRelease(BUTTON Key, int nPlayer);

#endif
//==============================================================
//
//DirectX[input.cpp]
//Author:����������
//
//==============================================================
#include"input.h"

//�}�N����`
#define NUM_KEY_MAX		(256)		//�L�[�̍ő吔
#define NUM_PLAYER		(4)			//�v���C���[�̐�

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���

XINPUT_STATE g_aButtonState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
XINPUT_STATE g_aButtonStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_aButtonStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���

//==============================================================
//�L�[�{�[�h�̏���������
//==============================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//==============================================================
//�L�[�{�[�h�̏I������
//==============================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//==============================================================
//�L�[�{�[�h�̍X�V����
//==============================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];				//�L�[�{�[�h�̃����[�X����ۑ�
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];					//�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];																		//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();						//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//==============================================================
//�L�[�{�[�h�̃v���X�����擾
//==============================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//==============================================================
//�L�[�{�[�h�̃g���K�[�����擾
//==============================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==============================================================
//�L�[�{�[�h�̃����[�X�����擾
//==============================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//==============================================================
//�Q�[���p�b�h�̏���������
//==============================================================
HRESULT InitGamepad(void)
{
	//xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(true);
	int nCount;

	for (nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		//�������[���N���A����
		memset(&g_aButtonState[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_aButtonStateTrigger[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_aButtonStateRelease[nCount], 0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}

//==============================================================
//�Q�[���p�b�h�̏I������
//==============================================================
void UninitGamepad(void)
{
	//xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}

//==============================================================
//�Q�[���p�b�h�̍X�V����
//==============================================================
void UpdateGamepad(void)
{
	XINPUT_STATE aGamepadState[NUM_PLAYER];
	static int nCntSpece;
	int nCntPad;

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCntPad, &aGamepadState[nCntPad]) == ERROR_SUCCESS)
		{
			g_aButtonStateTrigger[nCntPad].Gamepad.wButtons =
				~g_aButtonState[nCntPad].Gamepad.wButtons
				& aGamepadState[nCntPad].Gamepad.wButtons;		//�g���K�[

			g_aButtonStateRelease[nCntPad].Gamepad.wButtons =
				((g_aButtonState[nCntPad].Gamepad.wButtons
					^ aGamepadState[nCntPad].Gamepad.wButtons)
					& g_aButtonState[nCntPad].Gamepad.wButtons);	//�����[�X

			g_aButtonState[nCntPad] = aGamepadState[nCntPad];		//�v���X
		}
	}
}

//==============================================================
//�L�[�{�[�h�̃v���X�����擾
//==============================================================
bool GetGamepadPress(BUTTON Key, int nPlayer)
{
	return (g_aButtonState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//==============================================================
//�L�[�{�[�h�̃g���K�[�����擾
//==============================================================
bool GetGamepadTrigger(BUTTON Key, int nPlayer)
{
	return (g_aButtonStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//==============================================================
//�L�[�{�[�h�̃����[�X�����擾
//==============================================================
bool GetGamepadRelease(BUTTON Key, int nPlayer)
{
	return (g_aButtonStateRelease[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//==============================================================
//
//DirectX[pause.cpp]
//Author:����������
//
//==============================================================
#include"pause.h"
#include"input.h"
#include"game.h"
#include"fade.h"

//�}�N����`
#define NUM_PAUSE		(2)		//�|�[�Y��ʂ̐�
#define COL_R			(255)	//�ԐF�̐��l
#define COL_G			(255)	//�ΐF�̐��l
#define COL_B			(255)	//�F�̐��l
#define COL_A			(255)	//�s�����x�̐��l

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[NUM_PAUSE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//���_�o�b�t�@�̃|�C���^
Pause g_Pause[NUM_PAUSE];										//�|�[�Y�̏��

//==============================================================
//�|�[�Y��ʂ̏���������
//==============================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntPause;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial000.jpg",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title003.png",
		&g_pTexturePause[1]);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		g_Pause[nCntPause].nCounterAppear = 0;						//�_�ł̎��Ԃ�������
		g_Pause[nCntPause].nCounterState = 0;
		if (nCntPause == 0)
		{
			g_Pause[nCntPause].state = PAUSESTATE_NORMAL;	//��Ԃ�������
		}
		else if (nCntPause == 1)
		{
			g_Pause[nCntPause].state = PAUSESTATE_APPEAR;	//��Ԃ�������
		}
		g_Pause[nCntPause].bUse = true;								//�\������
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (nCntPause == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCntPause == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(800.0f, 580.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1250.0f, 580.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800.0f, 690.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1250.0f, 690.0f, 0.0f);
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DCOLOR_RGBA(COL_R, COL_G, COL_B, COL_A);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//==============================================================
//�|�[�Y��ʂ̏I������
//==============================================================
void UninitPause(void)
{
	int nCntPause;

	//�e�N�X�`���̔j��
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//==============================================================
//�|�[�Y��ʂ̍X�V����
//==============================================================
void UpdatePause(void)
{
	int nCntPause;
	int nCounterAppear = 0;
	g_Pause[1].nCounterState++;

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		switch (g_Pause[nCntPause].state)
		{
		case PAUSESTATE_APPEAR:
			if ((g_Pause[1].nCounterState % 40) == 0)
			{
				g_Pause[1].bUse = (g_Pause[1].bUse == false) ? true : false;
			}

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				////�T�E���h�̒�~
				//StopSound();

				////�T�E���h�̍Đ�
				//PlaySound(SOUND_LABEL_SE_ENTER000);

				g_Pause[1].state = PAUSESTATE_WAIT;
			}

			break;


		case PAUSESTATE_NORMAL:

			break;

		case PAUSESTATE_WAIT:
			//�f�����_��
			if ((g_Pause[1].nCounterState % 3) == 0)
			{
				g_Pause[1].bUse = (g_Pause[1].bUse == false) ? true : false;
				nCounterAppear++;
			}

			if (nCounterAppear >= 1)
			{
				//���[�h�ݒ�(�Q�[����ʂɈڍs)
				SetFade(MODE_GAME);				//�t�F�[�h�A�E�g
			}

			break;
		}
	}
}

//==============================================================
//�|�[�Y��ʂ̕`�揈��
//==============================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntPause;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (g_Pause[nCntPause].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePause[nCntPause]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntPause * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}
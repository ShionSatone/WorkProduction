//==============================================================
//
//DirectX[title.cpp]
//Author:����������
//
//==============================================================
#include"title.h"
#include"input.h"
#include"fade.h"
//#include"pause.h"
#include"sound.h"

//�}�N����`
#define NUM_TITLE		(3)		//�^�C�g���̐�
#define COL_R			(255)	//�ԐF�̐��l
#define COL_G			(255)	//�ΐF�̐��l
#define COL_B			(255)	//�F�̐��l
#define COL_A			(255)	//�s�����x�̐��l

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�̃|�C���^
Title g_title[NUM_TITLE];									//�v���C���[�̏��
bool bUseTitleSound = true;									//�Ȃ𗬂��������Ȃ���

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntTitle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title000.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title001.png",
		&g_pTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title002.png",
		&g_pTextureTitle[2]);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_title[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������������
		g_title[nCntTitle].state = TITLESTATE_NORMAL;			//�^�C�g���̏�Ԃ�����������
		g_title[nCntTitle].nCounterState = 0;					//��ԊǗ��J�E���^�[������������
		g_title[nCntTitle].nCounterAppear = 20;					//�_�Ŏ��Ԃ�����������
		g_title[nCntTitle].nCounterRank = 0;					//�����L���O��ʂ̎��Ԃ�����������
		g_title[nCntTitle].bUse = true;							//�\�����邩���Ȃ���������������
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (nCntTitle == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCntTitle == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(200.0f, 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1080.0f, 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(200.0f, 250.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1080.0f, 250.0f, 0.0f);
		}
		else if (nCntTitle == 2)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(400.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(880.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(880.0f, 600.0f, 0.0f);
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

		pVtx += 4;			//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void UninitTitle(void)
{
	int nCntTitle;

	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void UpdateTitle(void)
{
	int nCntTitle;
	int nCounterAppear = 0;
	g_title[2].nCounterState++;

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_title[nCntTitle].nCounterRank++;

		switch (g_title[nCntTitle].state)
		{
		case TITLESTATE_APPEAR:
			//���ʂ̓_��
			if ((g_title[2].nCounterState % 40) == 0)
			{
				g_title[2].bUse = (g_title[2].bUse == false) ? true : false;
			}

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadPress(BUTTON00, 0) == true)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_ENTER000);

				g_title[2].state = TITLESTATE_WAIT;
			}
			break;

		case TITLESTATE_NORMAL:
			if (g_title[2].state == TITLESTATE_NORMAL)
			{
				g_title[2].state = TITLESTATE_APPEAR;
			}

			//if ((g_title[nCntTitle].nCounterRank % 500) == 0)
			//{
			//	//���[�h�ݒ�(�����L���O��ʂɈڍs)
			//	SetFade(MODE_RANKING);			//�t�F�[�h�A�E�g
			//}

			break;

		case TITLESTATE_WAIT:
			//�f�����_��
			if ((g_title[2].nCounterState % 3) == 0)
			{
				g_title[2].bUse = (g_title[2].bUse == false) ? true : false;
				nCounterAppear++;
			}

			if (nCounterAppear >= 1)
			{
				//���[�h�ݒ�(�|�[�Y��ʂɈڍs)
				SetFade(MODE_GAME);			//�t�F�[�h�A�E�g
			}

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntTitle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_title[nCntTitle].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntTitle * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}
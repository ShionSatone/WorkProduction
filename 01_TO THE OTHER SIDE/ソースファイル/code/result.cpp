//==============================================================
//
//DirectX[result.cpp]
//Author:����������
//
//==============================================================
#include"result.h"
#include"input.h"
#include"player.h"
#include"goal.h"
#include"enemy.h"
#include"item.h"
#include"fade.h"
#include"sound.h"

//�}�N����`
#define NUM_RESULT		(3)		//�w�i�̐�
#define COL_R			(255)	//�ԐF�̐��l
#define COL_G			(255)	//�ΐF�̐��l
#define COL_B			(255)	//�F�̐��l
#define COL_A			(255)	//�s�����x�̐��l
#define RESULT_TIME		(800)	//���U���g��ʕ\������

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_RESULT] = {};	//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterResult;

//==============================================================
//���U���g��ʂ̏���������
//==============================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	int nCntResult;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear001.jpg",
		&g_pTextureResult[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear000.jpg",
		&g_pTextureResult[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear002.jpg",
		&g_pTextureResult[2]);

	g_nCounterResult = 0;		//�J�E���^�[�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
	g_pVtxBuffResult->Unlock();

	if (pPlayer->bDisp == false)
	{//�v���C���[����
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_BGM004);
	}
	else if (GetNumItem() == 3)
	{//�A�C�e���S�������
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_BGM002);
	}
	else if (GetNumEnemy() == 0)
	{//���ʂ̃N���A
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_BGM003);
	}
}

//==============================================================
//���U���g��ʂ̏I������
//==============================================================
void UninitResult(void)
{
	int nCntGame;

	//�T�E���h�̒�~
	StopSound();

	for (nCntGame = 0; nCntGame < NUM_RESULT; nCntGame++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCntGame] != NULL)
		{
			g_pTextureResult[nCntGame]->Release();
			g_pTextureResult[nCntGame] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//==============================================================
//���U���g��ʂ̍X�V����
//==============================================================
void UpdateResult(void)
{
	g_nCounterResult++;

	if (GetKeyboardTrigger(DIK_RETURN) == true || (g_nCounterResult % RESULT_TIME) == 0)
	{//����L�[(ENTER�L�[)�������ꂽ
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_TITLE);				//�t�F�[�h�A�E�g
	}
}

//==============================================================
//���U���g��ʂ̕`�揈��
//==============================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	Goal *pGoal = GetGoal();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (pPlayer->bDisp == false)
	{//�Q�[���I�[�o�[
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[0]);
	}
	else if (GetNumItem() == 3)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[2]);
	}
	else if (GetNumEnemy() == 0)
	{//�N���A
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[1]);
	}
	
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,												//�v���~�e�B�u�i�|���S���̐��j
		2);												//�`�悷��v���~�e�B�u��
}
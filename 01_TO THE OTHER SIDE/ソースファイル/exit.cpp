//==============================================================
//
//DirectX[Exit.cpp]
//Author:����������
//
//==============================================================
#include"main.h"
#include"Exit.h"
#include"input.h"
#include"enemy.h"

//�}�N����`
#define MAX_EXIT		(128)		//�e�̍ő吔
#define NUM_EXIT		(2)			//�G�̎��
#define DEF_POS_Z		(0.0f)		//�v���C���[��pos.z�̏����l
#define COL_R			(1.0f)		//�ԐF�̐��l
#define COL_G			(1.0f)		//�ΐF�̐��l
#define COL_B			(1.0f)		//�F�̐��l
#define COL_A			(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X		(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X		(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y		(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y		(1.0f)		//�e�N�X�`���̉�y�̏����l
#define BOSS_WIDTH		(90.0f)		//�{�X�̕�
#define BOSS_HEIGHT		(170.0f)	//�{�X�̍���
#define ENEMY_WIDTH		(30.0f)		//�G���G�̕�
#define ENEMY_HEIGHT	(60.0f)		//�G���G�̍���

//�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	float fWidth;			//��
	float fHeight;			//����
	float fColor;			//�G�̓����x
	int nType;				//���
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	bool bUse;				//�g�p���Ă��邩�ǂ���
} Exit;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExit[NUM_EXIT] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExit = NULL;				//���_�o�b�t�@�̃|�C���^
Exit g_aExit[MAX_EXIT];										//�e�̏��

//==============================================================
//�����̏���������
//==============================================================
void InitExit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExit;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exitenemy001.png",
		&g_pTextureExit[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exitenemy002.png",
		&g_pTextureExit[1]);

	//�e�̏��̏�����
	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		g_aExit[nCntExit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aExit[nCntExit].move = D3DXVECTOR3(1.0f, 10.0f, 1.0f);	//�ړ��ʂ̏�����
		g_aExit[nCntExit].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);	//�F�̏�����
		g_aExit[nCntExit].fWidth = 0.0f;							//���̏�����
		g_aExit[nCntExit].fHeight = 0.0f;							//�����̏�����
		g_aExit[nCntExit].fColor = 1.0f;							//�G�̓����x�̏�����
		g_aExit[nCntExit].nType = nCntExit;							//��ނ̏�����
		g_aExit[nCntExit].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExit,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(TEX_LEFT_X, TEX_UP_Y);
		pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_UP_Y);
		pVtx[2].tex = D3DXVECTOR2(TEX_LEFT_X, TEX_DOWN_Y);
		pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_DOWN_Y);

		pVtx += 4;			//���_�f�[�^�̃|�C���^���S���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExit->Unlock();
}

//==============================================================
//�����̏I������
//==============================================================
void UninitExit(void)
{
	int nCntExit;
	//�e�N�X�`���̔j��
	for (nCntExit = 0; nCntExit < NUM_EXIT; nCntExit++)
	{
		if (g_pTextureExit[nCntExit] != NULL)
		{
			g_pTextureExit[nCntExit]->Release();
			g_pTextureExit[nCntExit] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExit != NULL)
	{
		g_pVtxBuffExit->Release();
		g_pVtxBuffExit = NULL;
	}
}

//==============================================================
//�����̍X�V����
//==============================================================
void UpdateExit(void)
{
	int nCntExit;
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_aExit[nCntExit].bUse == true)
		{//�������g�p����Ă���
			g_aExit[nCntExit].fColor -= 0.05f;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aExit[nCntExit].fColor);
		}
		pVtx += 4;											//���_�f�[�^�̃|�C���^���S���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExit->Unlock();
}

//==============================================================
//�����̕`�揈��
//==============================================================
void DrawExit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExit;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExit = 0; nCntExit < MAX_ENEMY; nCntExit++)
	{
		if (g_aExit[nCntExit].bUse == true)
		{//�G���g�p����Ă���	
		 //�e�N�X�`���̐ݒ�
			if (g_aExit[nCntExit].nType == 0)
			{
				pDevice->SetTexture(0, g_pTextureExit[0]);
			}
			else if (g_aExit[nCntExit].nType == 1)
			{
				pDevice->SetTexture(0, g_pTextureExit[1]);
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntExit * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================
//�����̐ݒ菈��
//==============================================================
void SetExit(D3DXVECTOR3 pos, D3DXCOLOR col, int nType)
{
	int nCntExit;
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExit->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExit = 0; nCntExit < MAX_EXIT; nCntExit++)
	{
		if (g_aExit[nCntExit].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExit[nCntExit].pos = pos;
			g_aExit[nCntExit].col = col;
			g_aExit[nCntExit].nType = nType;
			g_aExit[nCntExit].nCounterAnim = 0;
			g_aExit[nCntExit].nPatternAnim = 0;

			if (g_aExit[nCntExit].nType == 0)
			{//�{�X
				g_aExit[nCntExit].fWidth = BOSS_WIDTH;
				g_aExit[nCntExit].fHeight = BOSS_HEIGHT;
			}
			else if (g_aExit[nCntExit].nType == 1)
			{//�G���G
				g_aExit[nCntExit].fWidth = ENEMY_WIDTH;
				g_aExit[nCntExit].fHeight = ENEMY_HEIGHT;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y - g_aExit[nCntExit].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x - g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aExit[nCntExit].pos.x + g_aExit[nCntExit].fWidth, g_aExit[nCntExit].pos.y, DEF_POS_Z);

			g_aExit[nCntExit].bUse = true;		//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;											//���_�f�[�^�̃|�C���^���S���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExit->Unlock();
}
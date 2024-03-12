//==============================================================
//
//DirectX[bg.cpp]
//Author:����������
//
//==============================================================
#include"main.h"
#include"bg.h"
#include"player.h"

//�}�N����`
#define NUM_BG				(6)			//�w�i�̐�
#define DEF_POS_Z			(0.0f)		//pos.z�̏����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBG[NUM_BG] = {};	//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
float g_aTexV[NUM_BG];							//�e�N�X�`�����W�̊J�n�ʒu�iV�l�j
D3DXVECTOR3 pos[NUM_BG];

//==============================================================
//�w�i�̏���������
//==============================================================
void Initbg(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg002.jpeg",
		&g_pTextureBG[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg001.png",
		&g_pTextureBG[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial001.png",
		&g_pTextureBG[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial002.png",
		&g_pTextureBG[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial003.png",
		&g_pTextureBG[4]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial004.png",
		&g_pTextureBG[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (nCntBG == 0 || nCntBG == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCntBG == 2)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(300.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(300.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(400.0f, 550.0f, 0.0f);
		}
		else if (nCntBG == 3)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(700.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(700.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(900.0f, 600.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(800.0f, 550.0f, 0.0f);
		}
		else if (nCntBG == 4)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(1500.0f, 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1600.0f, 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1500.0f, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1600.0f, 400.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(2300.0f, 300.0f, 0.0f);
		}
		else if (nCntBG == 5)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(2700.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(2900.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(2700.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(2900.0f, 600.0f, 0.0f);

			pos[nCntBG] = D3DXVECTOR3(2800.0f, 200.0f, 0.0f);
		}

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

		pVtx += 4;			//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//==============================================================
//�w�i�̏I������
//==============================================================
void Uninitbg(void)
{
	int nCntBG;

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_pTextureBG[nCntBG] != NULL)
		{
			g_pTextureBG[nCntBG]->Release();
			g_pTextureBG[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//==============================================================
//�w�i�̍X�V����
//==============================================================
void Updatebg(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	int nCntBG;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (pPlayer->nJudgeDirection == 0)
		{//���ɏo���ꍇ
			pos[nCntBG].x += SCREEN_WIDTH;
		}
		else if (pPlayer->nJudgeDirection == 1)
		{//�E�ɏo���ꍇ
			pos[nCntBG].x -= SCREEN_WIDTH;
		}


		if (nCntBG == 1 && pPlayer->state != PLAYERSTATE_SHADOW)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
			pVtx[1].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
			pVtx[2].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
			pVtx[3].col = D3DXCOLOR(0.88f, 0.85f, 0.85f, COL_A);
		}
		else if (nCntBG == 1 && pPlayer->state == PLAYERSTATE_SHADOW)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
			pVtx[1].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
			pVtx[2].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
			pVtx[3].col = D3DXCOLOR(0.95f, 0.95f, 0.95f, COL_A);
		}
		else if (nCntBG == 2 || nCntBG == 3)
		{
			//���_�E���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y - 50.0f, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y - 50.0f, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y + 50.0f, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y + 50.0f, DEF_POS_Z);
		}
		else if (nCntBG == 4)
		{
			//���_�E���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos[nCntBG].x - 60.0f, pos[nCntBG].y - 120.0f, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(pos[nCntBG].x + 60.0f, pos[nCntBG].y - 120.0f, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(pos[nCntBG].x - 60.0f, pos[nCntBG].y + 120.0f, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(pos[nCntBG].x + 60.0f, pos[nCntBG].y + 120.0f, DEF_POS_Z);
		}
		else if (nCntBG == 5)
		{
			//���_�E���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y - 150.0f, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y - 150.0f, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(pos[nCntBG].x - 100.0f, pos[nCntBG].y + 150.0f, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(pos[nCntBG].x + 100.0f, pos[nCntBG].y + 150.0f, DEF_POS_Z);
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	pPlayer->nJudgeDirection = -1;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//==============================================================
//�w�i�̕`�揈��
//==============================================================
void Drawbg(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCntBG]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			nCntBG * 4,										//�v���~�e�B�u�i�|���S���̐��j
			2);												//�`�悷��v���~�e�B�u��
	}
}
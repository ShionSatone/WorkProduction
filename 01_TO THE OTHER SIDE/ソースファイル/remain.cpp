//==============================================================
//
//DirectX[remain.cpp]
//Author:����������
//
//==============================================================
#include"main.h"
#include"remain.h"
#include"player.h"

//�}�N����`
#define NUM_REMAIN			(5)			//�c�@�\���̐�
#define DEF_RHW				(1.0f)		//rhw�̏����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRemain/*[NUM_REMAIN]*/ = NULL /*{}*/;	//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemain = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseRemain[NUM_REMAIN];							//�g���Ă��邩���Ȃ���

//==============================================================
//�c�@�̏���������
//==============================================================
void InitRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntRemain;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\life000.png",
		&g_pTextureRemain);

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{

		bUseRemain[nCntRemain] = true;					//�g���Ă����Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_REMAIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemain,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((nCntRemain * 50.0f) + -50.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((nCntRemain * 50.0f) + 0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((nCntRemain * 50.0f) + -50.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((nCntRemain * 50.0f) + 0.0f, 50.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = DEF_RHW;
		pVtx[1].rhw = DEF_RHW;
		pVtx[2].rhw = DEF_RHW;
		pVtx[3].rhw = DEF_RHW;

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
	g_pVtxBuffRemain->Unlock();
}

//==============================================================
//�c�@�̏I������
//==============================================================
void UninitRemain(void)
{
	if (g_pTextureRemain != NULL)
	{
		g_pTextureRemain->Release();
		g_pTextureRemain = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRemain != NULL)
	{
		g_pVtxBuffRemain->Release();
		g_pVtxBuffRemain = NULL;
	}
}

//==============================================================
//�c�@�̍X�V����
//==============================================================
void UpdateRemain(void)
{
	Player *pPlayer = GetPlayer();
	int nCntRemain;

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		if (bUseRemain[nCntRemain] == true)
		{
			if (pPlayer->nRemain == nCntRemain)
			{
				bUseRemain[nCntRemain] = false;
			}
		}
		else if (bUseRemain[nCntRemain] == false)
		{
			if (pPlayer->nRemain > nCntRemain)
			{
				bUseRemain[nCntRemain] = true;
			}
		}
	}
}

//==============================================================
//�c�@�̕`�揈��
//==============================================================
void DrawRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntRemain;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRemain, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		if (bUseRemain[nCntRemain] == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRemain);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntRemain * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}
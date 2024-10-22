//==============================================================
//
//DirectX[item.cpp]
//Author:����������
//
//==============================================================
#include"item.h"
#include"player.h"
#include"splayer.h"
#include"input.h"
#include"sound.h"

//�}�N����`
#define NUM_ITEM			(2)			//�A�C�e���̎��
#define MAX_ITEM			(128)		//�A�C�e���̐�
#define DEF_POS_X			(500.0f)	//�A�C�e����pos.x�̏����l
#define DEF_POS_Y			(400.0f)	//�A�C�e����pos.y�̏����l
#define DEF_POS_Z			(0.0f)		//�A�C�e����pos.z�̏����l
#define ITEM_WIDTH			(20.0f)		//�A�C�e���̕��̏����l
#define ITEM_HEIGHT			(20.0f)		//�A�C�e���̍����̏����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};	//�e�N�X�`��1�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];
int g_aNumGetItem;									//�A�C�e���̐�
int g_nCounterLife;									//����

//�e�N�X�`���t�@�C����


//==============================================================
//�A�C�e���̏���������
//==============================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	int nCntItem;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\item000.png",
		&g_pTextureItem[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\life001.png",
		&g_pTextureItem[1]);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//�ʒu������������
		g_aItem[nCntItem].fWidth = ITEM_WIDTH;										//��������������
		g_aItem[nCntItem].fHeight = ITEM_HEIGHT;									//����������������
		g_aItem[nCntItem].nType = 0;												//��ނ�����������
		g_aItem[nCntItem].nCounterItem = 0;											//�A�C�e���̓����̃J�E���^�[������������
		g_aItem[nCntItem].bUse = false;												//�g�p���Ă��Ȃ���Ԃɂ���
		g_aItem[nCntItem].bShadowUse = true;										//���������悤���Ă����Ԃɂ���
	}

	g_aNumGetItem = 0;																//�A�C�e���̐��̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_�E���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//==============================================================
//�A�C�e���̏I������
//==============================================================
void UninitItem(void)
{
	int nCntItem;

	//�e�N�X�`���̔j��
	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//==============================================================
//�A�C�e���̍X�V����
//==============================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	int nCntItem;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPlayer->nJudgeDirection == 0)
			{//���ɏo���ꍇ
				g_aItem[nCntItem].pos.x += SCREEN_WIDTH;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{//�E�ɏo���ꍇ
				g_aItem[nCntItem].pos.x -= SCREEN_WIDTH;
			}

			/*if (g_aItem[nCntItem].nType == 2)
			{
				

			}*/

			//���_�E���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
		}
		else if (g_aItem[nCntItem].bUse == false)
		{
			if (g_aItem[nCntItem].nType == 1)
			{
				g_nCounterLife++;

				if (g_nCounterLife >= 600)
				{
					g_aItem[nCntItem].bUse = true;
					g_nCounterLife = 0;
				}
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//==============================================================
//�A�C�e���̕`�揈��
//==============================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntItem;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (g_aItem[nCntItem].nType == 0)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[0]);
			}
			else if (g_aItem[nCntItem].nType == 1 || g_aItem[nCntItem].nType == 2)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[1]);
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntItem * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================
//�A�C�e���̐ݒ菈��
//==============================================================
void SetItem(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^
	int nCntItem;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].nType = nType;

			//���_�E���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y - ITEM_HEIGHT, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_WIDTH, g_aItem[nCntItem].pos.y + ITEM_HEIGHT, DEF_POS_Z);

			if (g_aItem[nCntItem].nType == 0 || g_aItem[nCntItem].nType == 2)
			{
				g_aItem[nCntItem].bUse = true;
			}

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//==============================================================
//�A�C�e���̃q�b�g����
//==============================================================
void HitItem(void)
{
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_GET000);

	g_aNumGetItem += 1;
}

//==============================================================
//���
//==============================================================
Item *GetItem(void)
{
	return &g_aItem[0];		//�A�C�e���̏��̐擪�A�h���X��Ԃ�
}

//==============================================================
//�A�C�e���̑����̎擾
//==============================================================
int GetNumItem(void)
{
	return g_aNumGetItem;
}

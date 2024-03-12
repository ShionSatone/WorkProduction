//==============================================================
//
//DirectX[sblock.cpp]
//Author:����������
//
//==============================================================
#include"sblock.h"
#include"input.h"
#include"splayer.h"
#include"player.h"
#include"block.h"
#include"enemy.h"
#include"item.h"
#include"sound.h"

//�}�N����`
#define MAX_SBLOCK			(128)		//�u���b�N�i�e�j�̐�
#define DEF_POS_X			(500.0f)	//�u���b�N�i�e�j��pos.x�̏����l
#define DEF_POS_Y			(400.0f)	//�u���b�N�i�e�j��pos.y�̏����l
#define DEF_POS_Z			(0.0f)		//�u���b�N�i�e�j��pos.z�̏����l
#define SBLOCK_WIDTH0		(50.0f)		//1�}�X�u���b�N�i�e�j�̕��̏����l
#define SBLOCK_HEIGHT0		(50.0f)		//1�}�X�u���b�N�i�e�j�̍����̏����l
#define SBLOCK_WIDTH2		(640.0f)	//�����u���b�N�i�e�j�̕��̏����l
#define SBLOCK_HEIGHT2		(60.0f)		//�����u���b�N�i�e�j�̍����̏����l
#define SBLOCK_WIDTH3		(50.0f)		//�c���u���b�N�i�e�j�̕��̏����l
#define SBLOCK_HEIGHT3		(100.0f)	//�c���u���b�N�i�e�j�̍����̏����l
#define SBLOCK_WIDTH4		(30.0f)		//�{�^���u���b�N�i�e�j�̕��̏����l
#define SBLOCK_HEIGHT4		(30.0f)		//�{�^���u���b�N�i�e�j�̍����̏����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l
#define SHADOW_X			(200.0f)	//�e��X�̈ʒu
#define SHADOW_Y			(220.0f)	//�e��Y�̈ʒu
#define PLAYER_WIDTH		(15.0f)		//�v���C���[�̕����������
#define PLAYER_HEIGHT		(0.0f)		//�v���C���[�̍����ɑ�������

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureSBlock = NULL;			//�e�N�X�`��1�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSBlock = NULL;		//���_�o�b�t�@�ւ̃|�C���^
SBlock g_aSBlock[MAX_SBLOCK];

//==============================================================
//�u���b�N�i�e�j�̏���������
//==============================================================
void InitSBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	int nCntSBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg_shadow000.png",
		&g_pTextureSBlock);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		g_aSBlock[nCntSBlock].pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//�ʒu������������
		g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH0;									//��������������
		g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT0;									//����������������
		g_aSBlock[nCntSBlock].nType = 0;												//��ނ�����������
		g_aSBlock[nCntSBlock].nCounterSBlock = 0;										//�u���b�N�i�e�j�̓����̃J�E���^�[������������
		g_aSBlock[nCntSBlock].bUse = false;												//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SBLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSBlock,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x, g_aSBlock[nCntSBlock].pos.y, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x, g_aSBlock[nCntSBlock].pos.y + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);

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

		pVtx += 4;						//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSBlock->Unlock();
}

//==============================================================
//�u���b�N�i�e�j�̏I������
//==============================================================
void UninitSBlock(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSBlock != NULL)
	{
		g_pTextureSBlock->Release();
		g_pTextureSBlock = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSBlock != NULL)
	{
		g_pVtxBuffSBlock->Release();
		g_pVtxBuffSBlock = NULL;
	}
}

//==============================================================
//�u���b�N�i�e�j�̍X�V����
//==============================================================
void UpdateSBlock(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	int nCntSBlock;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		g_aSBlock[nCntSBlock].nCounterSBlock++;

		if (g_aSBlock[nCntSBlock].bUse == true)
		{
			if (g_aSBlock[nCntSBlock].nType == 1)
			{//���ړ�
				if (g_aSBlock[nCntSBlock].nCounterSBlock <= 200)
				{
					g_aSBlock[nCntSBlock].pos.x += 1.0f;
				}
				else if (g_aSBlock[nCntSBlock].nCounterSBlock <= 400)
				{
					g_aSBlock[nCntSBlock].pos.x -= 1.0f;
				}
				else if (g_aSBlock[nCntSBlock].nCounterSBlock <= 600)
				{
					g_aSBlock[nCntSBlock].nCounterSBlock = 0;
				}
			}

			if (pPlayer->nJudgeDirection == 0)
			{
				g_aSBlock[nCntSBlock].pos.x += SCREEN_WIDTH;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{
				g_aSBlock[nCntSBlock].pos.x -= SCREEN_WIDTH;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
		}

		pVtx += 4;						//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSBlock->Unlock();
}

//==============================================================
//�u���b�N�i�e�j�̕`�揈��
//==============================================================
void DrawSBlock(void)
{
	int nCntSBlock;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		if (g_aSBlock[nCntSBlock].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSBlock);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntSBlock * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================
//�u���b�N�i�e�j�̐ݒ菈��
//==============================================================
void SetSBlock(D3DXVECTOR3 pos, int nType)
{
	int nCntSBlock;
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		if (g_aSBlock[nCntSBlock].bUse == false)
		{//�u���b�N�i�e�j���g�p����Ă��Ȃ�
			g_aSBlock[nCntSBlock].pos = pos;
			g_aSBlock[nCntSBlock].nType = nType;

			if (g_aSBlock[nCntSBlock].nType == 0)
			{//1�}�X
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH0;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT0;
			}
			else if (g_aSBlock[nCntSBlock].nType == 2)
			{//����
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH2;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT2;
			}
			else if (g_aSBlock[nCntSBlock].nType == 3)
			{//�c��
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH3;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT3;
			}
			else if (g_aSBlock[nCntSBlock].nType == 4)
			{//�{�^���u���b�N�i�e�j
				g_aSBlock[nCntSBlock].fWidth = SBLOCK_WIDTH4;
				g_aSBlock[nCntSBlock].fHeight = SBLOCK_HEIGHT4;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, g_aSBlock[nCntSBlock].pos.y - SHADOW_Y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aSBlock[nCntSBlock].pos.x + SHADOW_X, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3((g_aSBlock[nCntSBlock].pos.x + SHADOW_X) + g_aSBlock[nCntSBlock].fWidth, (g_aSBlock[nCntSBlock].pos.y - SHADOW_Y) + g_aSBlock[nCntSBlock].fHeight, DEF_POS_Z);

			g_aSBlock[nCntSBlock].bUse = true;		//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;									//���_�f�[�^�̃|�C���^���S���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSBlock->Unlock();
}

//==============================================================
//�u���b�N�i�e�j�Ƃ̓����蔻�菈��
//==============================================================
bool CollisionSBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, SBlock **pSBlock)
{
	Player *pPlayer = GetPlayer();
	int nCntSBlock;
	bool bLand = false;		//���n�������ǂ���

	for (nCntSBlock = 0; nCntSBlock < MAX_SBLOCK; nCntSBlock++)
	{
		if (g_aSBlock[nCntSBlock].bUse == true && pPlayer->state == PLAYERSTATE_SHADOW)
		{
			if (pPosOld->y <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->y >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth)
			{//���ɂ߂荞�񂾏ꍇ
				bLand = true;
				pPos->y = g_aSBlock[nCntSBlock].pos.y - SHADOW_Y;													//�u���b�N�i�e�j�̏�ɗ�������
				pMove->y = 0.0f;																					//�ړ��ʂ��O�ɂ���

				if (g_aSBlock[nCntSBlock].nType == 4)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_BUTTON000);

					g_aSBlock[nCntSBlock].bUse = false;
					CollisionSButton(nCntSBlock);
				}

				if (pSBlock != NULL)
				{//�u���b�N�i�e�j�̃A�h���X������ꏊ������
					*pSBlock = &g_aSBlock[nCntSBlock];																	//�u���b�N�i�e�j�̃A�h���X����
				}
			}
			else if (pPosOld->y - fHeight - PLAYER_HEIGHT >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth)
			{//��ɂ߂荞�񂾏ꍇ
				bLand = false;
				pPos->y = g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight + fHeight + PLAYER_HEIGHT;			//�u���b�N�i�e�j�̉��ɗ�������
				pMove->y = 0.0f;																									//�ړ��ʂ��O�ɂ���
			}
			else if (pPosOld->x + fWidth - PLAYER_WIDTH <= g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->x + fWidth - PLAYER_WIDTH >= g_aSBlock[nCntSBlock].pos.x + SHADOW_X
				&& pPos->y >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight)
			{//���ɂ߂荞�񂾏ꍇ
				pPos->x = g_aSBlock[nCntSBlock].pos.x + SHADOW_X - fWidth + PLAYER_WIDTH;											//�u���b�N�i�e�j�̍��ɗ�������
				pMove->x = 0.0f;																									//�ړ��ʂ��O�ɂ���

				bLand = false;
			}
			else if (pPosOld->x - fWidth + PLAYER_WIDTH >= g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth
				&& pPos->x - fWidth + PLAYER_WIDTH <= g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth
				&& pPos->y >= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aSBlock[nCntSBlock].pos.y - SHADOW_Y + g_aSBlock[nCntSBlock].fHeight)
			{//�E�ɂ߂荞�񂾏ꍇ
				pPos->x = g_aSBlock[nCntSBlock].pos.x + SHADOW_X + g_aSBlock[nCntSBlock].fWidth + fWidth - PLAYER_WIDTH;			//�u���b�N�i�e�j�̍��ɗ�������
				pMove->x = 0.0f;																									//�ړ��ʂ��O�ɂ���

				bLand = false;
			}
		}
	}

	return bLand;
}

//==============================================================
//�{�^���i�e�j�Ƃ̓����蔻�菈��
//==============================================================
void CollisionSButton(int nCntSBlock)
{
	if (nCntSBlock == 94)
	{
		SetBlock(D3DXVECTOR3(300.0f, 660.0f, 0.0f), 2);
		SetSBlock(D3DXVECTOR3(300.0f, 660.0f, 0.0f), 2);
	}
	else if (nCntSBlock == 95)
	{
		SetBlock(D3DXVECTOR3(910.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(910.0f, 660.0f, 0.0f), 3);
	}
	else if (nCntSBlock == 96)
	{
		SetBlock(D3DXVECTOR3(400.0f, 660.0f, 0.0f), 2);
		SetSBlock(D3DXVECTOR3(400.0f, 660.0f, 0.0f), 2);
	}
	else if (nCntSBlock == 97)
	{
		SetSBlock(D3DXVECTOR3(900.0f, 870.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(950.0f, 870.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(900.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(950.0f, 660.0f, 0.0f), 3);
	}
	else if (nCntSBlock == 98)
	{
		SetSBlock(D3DXVECTOR3(700.0f, 500.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(750.0f, 500.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(500.0f, 400.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(550.0f, 400.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(300.0f, 300.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(350.0f, 300.0f, 0.0f), 0);
	}
	else if (nCntSBlock == 99)
	{
		SetBlock(D3DXVECTOR3(820.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(870.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(920.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(970.0f, 660.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(1020.0f, 660.0f, 0.0f), 3);

		SetSBlock(D3DXVECTOR3(820.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(870.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(920.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(970.0f, 660.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(1020.0f, 660.0f, 0.0f), 3);

		SetSBlock(D3DXVECTOR3(110.0f, 500.0f, 0.0f), 0);
		SetSBlock(D3DXVECTOR3(160.0f, 500.0f, 0.0f), 0);
	}
	else if (nCntSBlock == 100)
	{
		//�T�E���h�̒�~
		StopSound();

		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0, 100.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 200.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 300.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 400.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 3);
		SetBlock(D3DXVECTOR3(0.0f, 600.0f, 0.0f), 3);

		SetSBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0, 100.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 200.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 300.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 400.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 3);
		SetSBlock(D3DXVECTOR3(0.0f, 600.0f, 0.0f), 3);

		SetEnemy(D3DXVECTOR3(700.0f, 0.0f, 0.0f), 0);

		SetItem(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), 1);
	}
}
//==============================================================
//
//DirectX[block.cpp]
//Author:����������
//
//==============================================================
#include"block.h"
#include"player.h"
#include"input.h"

//�}�N����`
#define MAX_BLOCK			(128)		//�u���b�N�̐�
#define DEF_POS_X			(500.0f)	//�u���b�N��pos.x�̏����l
#define DEF_POS_Y			(400.0f)	//�u���b�N��pos.y�̏����l
#define DEF_POS_Z			(0.0f)		//�u���b�N��pos.z�̏����l
#define BLOCK_WIDTH0		(50.0f)		//1�}�X�u���b�N�̕��̏����l
#define BLOCK_HEIGHT0		(50.0f)		//1�}�X�u���b�N�̍����̏����l
#define BLOCK_WIDTH2		(640.0f)	//�����u���b�N�̕��̏����l
#define BLOCK_HEIGHT2		(60.0f)		//�����u���b�N�̍����̏����l
#define BLOCK_WIDTH3		(50.0f)		//�c���u���b�N�̕��̏����l
#define BLOCK_HEIGHT3		(100.0f)	//�c���u���b�N�̍����̏����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l
#define PLAYER_WIDTH		(15.0f)		//�v���C���[�̕����������
#define PLAYER_HEIGHT		(0.0f)		//�v���C���[�̍����ɑ�������

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			//�e�N�X�`��1�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];

//�e�N�X�`���t�@�C����


//==============================================================
//�u���b�N�̏���������
//==============================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block000.png",
		&g_pTextureBlock);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//�ʒu������������
		g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH0;									//��������������
		g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT0;								//����������������
		g_aBlock[nCntBlock].nType = 0;												//��ނ�����������
		g_aBlock[nCntBlock].nCounterBlock = 0;										//�u���b�N�̓����̃J�E���^�[������������
		g_aBlock[nCntBlock].bUse = false;											//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);

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
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//�u���b�N�̏I������
//==============================================================
void UninitBlock(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//==============================================================
//�u���b�N�̍X�V����
//==============================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();	//�v���C���[�̏���ǂݍ���
	int nCntBlock;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].nCounterBlock++;

		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].nType == 1)
			{//���ړ�
				if (g_aBlock[nCntBlock].nCounterBlock <= 200)
				{
					g_aBlock[nCntBlock].pos.x += 1.0f;
				}
				else if (g_aBlock[nCntBlock].nCounterBlock <= 400)
				{
					g_aBlock[nCntBlock].pos.x -= 1.0f;
				}
				else if (g_aBlock[nCntBlock].nCounterBlock <= 600)
				{
					g_aBlock[nCntBlock].nCounterBlock = 0;
				}
			}

			if (pPlayer->nJudgeDirection == 0)
			{//���ɏo���ꍇ
				g_aBlock[nCntBlock].pos.x += SCREEN_WIDTH;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{//�E�ɏo���ꍇ
				g_aBlock[nCntBlock].pos.x -= SCREEN_WIDTH;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
		}

		pVtx += 4;						//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//�u���b�N�̕`�揈��
//==============================================================
void DrawBlock(void)
{
	int nCntBlock;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntBlock * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================
//�u���b�N�̐ݒ菈��
//==============================================================
void SetBlock(D3DXVECTOR3 pos, int nType)
{
	int nCntBlock;
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].nType = nType;

			if (g_aBlock[nCntBlock].nType == 0)
			{//1�}�X
				g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH0;
				g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT0;
			}
			else if (g_aBlock[nCntBlock].nType == 2)
			{//����
				g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH2;
				g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT2;
			}
			else if (g_aBlock[nCntBlock].nType == 3 || g_aBlock[nCntBlock].nType == 5)
			{//�c�� or ���������u���b�N
				g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH3;
				g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT3;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, DEF_POS_Z);

			g_aBlock[nCntBlock].bUse = true;		//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;									//���_�f�[�^�̃|�C���^���S���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//�u���b�N�Ƃ̓����蔻�菈��
//==============================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Block **pBlock)
{
	int nCntBlock;
	bool bLand = false;		//���n�������ǂ���

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType != 5)
		{
			if (pPosOld->y <= g_aBlock[nCntBlock].pos.y
				&& pPos->y >= g_aBlock[nCntBlock].pos.y
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//���ɂ߂荞�񂾏ꍇ
				bLand = true;
				pPos->y = g_aBlock[nCntBlock].pos.y;																//�u���b�N�̏�ɗ�������
				pMove->y = 0.0f;																					//�ړ��ʂ��O�ɂ���

				if (pBlock != NULL)
				{//�u���b�N�̃A�h���X������ꏊ������
					*pBlock = &g_aBlock[nCntBlock];																	//�u���b�N�̃A�h���X����
				}
			}
			else if (pPosOld->y - fHeight - PLAYER_HEIGHT >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
				&& pPos->x + fWidth - PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x
				&& pPos->x - fWidth + PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//��ɂ߂荞�񂾏ꍇ
				bLand = false;
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight + PLAYER_HEIGHT;			//�u���b�N�̉��ɗ�������
				pMove->y = 0.0f;																						//�ړ��ʂ��O�ɂ���
			}
			else if (pPosOld->x + fWidth - PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x
				&& pPos->x + fWidth - PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x
				&& pPos->y >= g_aBlock[nCntBlock].pos.y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{//���ɂ߂荞�񂾏ꍇ
				pPos->x = g_aBlock[nCntBlock].pos.x - fWidth + 14.0f;													//�u���b�N�̍��ɗ�������
				pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���

				bLand = false;
			}
			else if (pPosOld->x - fWidth + PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
				&& pPos->x - fWidth + PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
				&& pPos->y >= g_aBlock[nCntBlock].pos.y
				&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{//�E�ɂ߂荞�񂾏ꍇ
				pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth - 14.0f;						//�u���b�N�̍��ɗ�������
				pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���

				bLand = false;
			}
		}
	}

	return bLand;
}

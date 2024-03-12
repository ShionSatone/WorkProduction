//==============================================================
//
//DirectX[goal.cpp]
//Author:����������
//
//==============================================================
#include"goal.h"
#include"player.h"
#include"input.h"

//�}�N����`
#define MAX_Goal			(1)			//�S�[���̐�
#define DEF_POS_X			(500.0f)	//�S�[����pos.x�̏����l
#define DEF_POS_Y			(400.0f)	//�S�[����pos.y�̏����l
#define DEF_POS_Z			(0.0f)		//�S�[����pos.z�̏����l
#define Goal_WIDTH0			(50.0f)		//1�}�X�S�[���̕��̏����l
#define Goal_HEIGHT0		(50.0f)		//1�}�X�S�[���̍����̏����l
#define Goal_WIDTH2			(640.0f)	//�����S�[���̕��̏����l
#define Goal_HEIGHT2		(60.0f)		//�����S�[���̍����̏����l
#define Goal_WIDTH3			(50.0f)		//�c���S�[���̕��̏����l
#define Goal_HEIGHT3		(100.0f)	//�c���S�[���̍����̏����l
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
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			//�e�N�X�`��1�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Goal g_aGoal;

//�e�N�X�`���t�@�C����


//==============================================================
//�S�[���̏���������
//==============================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\goal.jpg",
		&g_pTextureGoal);


	g_aGoal.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//�ʒu������������
	g_aGoal.fWidth = Goal_WIDTH0;									//��������������
	g_aGoal.fHeight = Goal_HEIGHT0;									//����������������
	g_aGoal.nType = 0;												//��ނ�����������
	g_aGoal.nCounterGoal = 0;										//�S�[���̓����̃J�E���^�[������������
	g_aGoal.bUse = false;											//�g�p���Ă��Ȃ���Ԃɂ���
	g_aGoal.bShadowUse = true;										//���������悤���Ă����Ԃɂ���


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_�E���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//�S�[���̏I������
//==============================================================
void UninitGoal(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//==============================================================
//�S�[���̍X�V����
//==============================================================
void UpdateGoal(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aGoal.bUse == true)
	{
		if (pPlayer->nJudgeDirection == 0)
		{//���ɏo���ꍇ
			g_aGoal.pos.x += 1280.0f;
		}
		else if (pPlayer->nJudgeDirection == 1)
		{//�E�ɏo���ꍇ
			g_aGoal.pos.x -= 1280.0f;
		}

		//���_�E���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//�S�[���̕`�揈��
//==============================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_aGoal.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGoal);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			0,												//�v���~�e�B�u�i�|���S���̐��j
			2);												//�`�悷��v���~�e�B�u��
	}
}

//==============================================================
//�S�[���̐ݒ菈��
//==============================================================
void SetGoal(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aGoal.bUse == false)
	{
		g_aGoal.pos = pos;
		g_aGoal.nType = nType;

		//���_�E���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + 50.0f, g_aGoal.pos.y + 50.0f, 0.0f);

		g_aGoal.bUse = true;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//�S�[���Ƃ̓����蔻�菈��
//==============================================================
bool CollisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Goal **pGoal)
{
	bool bLand = false;		//���n�������ǂ���

	if (g_aGoal.bUse == true && g_aGoal.bShadowUse == true)
	{
		if (pPosOld->y <= g_aGoal.pos.y
			&& pPos->y >= g_aGoal.pos.y
			&& pPos->x + fWidth - PLAYER_WIDTH > g_aGoal.pos.x
			&& pPos->x - fWidth + PLAYER_WIDTH < g_aGoal.pos.x + g_aGoal.fWidth)
		{//���ɂ߂荞�񂾏ꍇ
			bLand = true;
			pPos->y = g_aGoal.pos.y;																//�S�[���̏�ɗ�������
			pMove->y = 0.0f;																					//�ړ��ʂ��O�ɂ���

			if (pGoal != NULL)
			{//�S�[���̃A�h���X������ꏊ������
				*pGoal = &g_aGoal;																	//�S�[���̃A�h���X����
			}
		}
		else if (pPosOld->y - fHeight - PLAYER_HEIGHT >= g_aGoal.pos.y + g_aGoal.fHeight
			&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aGoal.pos.y + g_aGoal.fHeight
			&& pPos->x + fWidth - PLAYER_WIDTH > g_aGoal.pos.x
			&& pPos->x - fWidth + PLAYER_WIDTH < g_aGoal.pos.x + g_aGoal.fWidth)
		{//��ɂ߂荞�񂾏ꍇ
			bLand = false;
			pPos->y = g_aGoal.pos.y + g_aGoal.fHeight + fHeight + PLAYER_HEIGHT;			//�S�[���̉��ɗ�������
			pMove->y = 0.0f;																						//�ړ��ʂ��O�ɂ���
		}
		else if (pPosOld->x + fWidth - PLAYER_WIDTH <= g_aGoal.pos.x
			&& pPos->x + fWidth - PLAYER_WIDTH >= g_aGoal.pos.x
			&& pPos->y >= g_aGoal.pos.y
			&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aGoal.pos.y + g_aGoal.fHeight)
		{//���ɂ߂荞�񂾏ꍇ
			bLand = false;
			pPos->x = g_aGoal.pos.x - fWidth + 14.0f;													//�S�[���̍��ɗ�������
			pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���
		}
		else if (pPosOld->x - fWidth + PLAYER_WIDTH >= g_aGoal.pos.x + g_aGoal.fWidth
			&& pPos->x - fWidth + PLAYER_WIDTH <= g_aGoal.pos.x + g_aGoal.fWidth
			&& pPos->y >= g_aGoal.pos.y
			&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aGoal.pos.y + g_aGoal.fHeight)
		{//�E�ɂ߂荞�񂾏ꍇ
			bLand = false;
			pPos->x = g_aGoal.pos.x + g_aGoal.fWidth + fWidth - 14.0f;						//�S�[���̍��ɗ�������
			pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���
		}
	}

	return bLand;
}

//==============================================================
//���
//==============================================================
Goal *GetGoal(void)
{
	return &g_aGoal;		//�G�̏��̐擪�A�h���X��Ԃ�
}
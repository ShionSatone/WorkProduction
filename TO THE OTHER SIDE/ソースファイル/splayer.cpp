//==============================================================
//
//DirectX[splayer.cpp]
//Author:����������
//
//==============================================================
#include"splayer.h"
#include"input.h"
#include"sblock.h"
#include"player.h"
#include"item.h"
#include"sound.h"

//�}�N����`
#define DEF_POS_X			(100.0f)	//�v���C���[��pos.x�̏����l
#define DEF_POS_Y			(150.0f)	//�v���C���[��pos.y�̏����l
#define DEF_POS_Z			(0.0f)		//�v���C���[��pos.z�̏����l
#define DEF_MOVE			(0.0f)		//�ړ��ʂ̏����l
#define DEF_ROT				(0.0f)		//�����̏����l
#define DEF_RHW				(1.0f)		//rhw�̏����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(0.25f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(0.5f)		//�e�N�X�`���̉�y�̏����l
#define WIDTH_SPLAYER		(25.0f)		//�v���C���[�̕�
#define HEIGHT_SPLAYER		(90.0f)		//�v���C���[�̍���
#define ANGLE_UP			(0.75f)		//�p�x�i��j
#define ANGLE_DOWN			(0.25f)		//�p�x�i���j
#define GROUND_HEIGHT		(660.0f)	//�n�ʂ̍���
#define CEIL_HEIGHT			(10.0f)		//�V��̍���
#define POS_X				(3.2f)		//�ʒu�X�V
#define MOVE_X				(0.2f)		//�ړ���
#define MOVE_Y				(0.5f)		//�ړ���(����)
#define MOVE_JUMP			(-14.0f)	//�ړ���(�W�����v�̏d��)
#define SHADOW_X			(200.0f)	//�e��X�̈ʒu
#define SHADOW_Y			(220.0f)	//�e��Y�̈ʒu
#define ITEM_POS			(20.0f)		//�A�C�e���̑傫��

//�v���g�^�C�v�錾
void CollisionSPlayer(void);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureSPlayer = NULL;		//�e�N�X�`��1�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
SPlayer g_SPlayer;									//�v���C���[�̏��
int g_nCounterAnimSPlayer;							//�A�j���[�V�����J�E���^�[
int g_nPatternAnimSPlayer;							//�A�j���[�V�����p�^�[��No.
int g_nCounterSSe;									//�����e��se�̃J�E���^�[
float g_fLengthSPlayer;								//�Ίp���̒���
float g_fAngleSPlayer;								//�Ίp���̊p�x

//==============================================================
//�v���C���[�̏���������
//==============================================================
void InitSPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\splayer000.png",
		&g_pTextureSPlayer);

	g_nCounterAnimSPlayer = 0;											//�J�E���^�[������������
	g_nPatternAnimSPlayer = 0;											//�p�^�[��No.������������
	g_nCounterSSe = 0;
	g_SPlayer.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//�ʒu������������
	g_SPlayer.move = D3DXVECTOR3(DEF_MOVE, DEF_MOVE, DEF_MOVE);			//�ړ��ʂ�����������
	g_SPlayer.rot = D3DXVECTOR3(DEF_ROT, DEF_ROT, DEF_ROT);				//����������������(Z�l���g�p)
	g_SPlayer.nCounterDirect = 0;										//�A�j���[�V�����̌���������������
	g_SPlayer.fWidth = WIDTH_SPLAYER;									//����������
	g_SPlayer.fHeight = HEIGHT_SPLAYER;									//������������
	g_SPlayer.pBlock = NULL;											//�u���b�N�̏���������
	g_SPlayer.bJump = false;											//�W�����v���g�p���Ă��Ȃ�
	g_SPlayer.bDisp = true;												//�v���C���[�i�e�j���g�p���Ă���


	//�Ίp���̒������Z�o����
	g_fLengthSPlayer = sqrtf(WIDTH_SPLAYER * WIDTH_SPLAYER + HEIGHT_SPLAYER * HEIGHT_SPLAYER) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	g_fAngleSPlayer = atan2f(WIDTH_SPLAYER, HEIGHT_SPLAYER);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSPlayer,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[1].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[2].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);
	pVtx[3].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);

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
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_DOWN_Y);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT_X, TEX_UP_Y);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT_X, TEX_DOWN_Y);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSPlayer->Unlock();
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void UninitSPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSPlayer != NULL)
	{
		g_pTextureSPlayer->Release();
		g_pTextureSPlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSPlayer != NULL)
	{
		g_pVtxBuffSPlayer->Release();
		g_pVtxBuffSPlayer = NULL;
	}
}

//==============================================================
//�v���C���[�̍X�V����
//==============================================================
void UpdateSPlayer(void)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();		//�v���C���[�̏���ǂݍ���
	g_nCounterAnimSPlayer++;			//�J�E���^�[�����Z
	g_nCounterSSe++;

	g_SPlayer.posOld = g_SPlayer.pos;	//�O��̈ʒu��ۑ�

	//if (g_SPlayer.pBlock != NULL)
	//{//�u���b�N�ɏ���Ă���
	//	g_SPlayer.pos.x += g_SPlayer.pBlock;
	//}
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_nPatternAnimSPlayer = 0;
		}
		else
		{
			if ((g_nCounterAnimSPlayer % 10) == 0)
			{//��莞�Ԍo��
				g_nPatternAnimSPlayer += 1;
			}

			//������
			g_SPlayer.nCounterDirect = 1;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_nPatternAnimSPlayer = 0;
		}
		else
		{
			if ((g_nCounterAnimSPlayer % 10) == 0)
			{//��莞�Ԍo��
				g_nPatternAnimSPlayer += 1;
			}

			//�E����
			g_SPlayer.nCounterDirect = 0;
		}
	}
	else
	{
		g_nPatternAnimSPlayer = 0;
	}

	//�v���C���[���g�p���Ă��邩
	if (pPlayer->bDisp == false)
	{
		g_SPlayer.bDisp = false;
	}
	else if (pPlayer->bDisp == true)
	{
		g_SPlayer.bDisp = true;
	}

	if (pPlayer->state == PLAYERSTATE_SHADOW)
	{
		CollisionSPlayer();
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (pPlayer->state)
	{
	case PLAYERSTATE_NORMAL:			//�ʏ���
		//�v���C���[(�e)�Ƀv���C���[��pos�𑫂�
		g_SPlayer.pos.x = pPlayer->pos.x + SHADOW_X;
		g_SPlayer.pos.y = pPlayer->pos.y - SHADOW_Y;

		break;

	case PLAYERSTATE_SHADOW:			//�e���
		//�d�͏���
		g_SPlayer.move.y += MOVE_Y;

		//��ʊO�֍s�����Ƃ�
		if (g_SPlayer.pos.x - WIDTH_SPLAYER <= 0)
		{
			g_SPlayer.pos.x = WIDTH_SPLAYER;
		}
		else if (g_SPlayer.pos.x + WIDTH_SPLAYER >= SCREEN_WIDTH)
		{
			g_SPlayer.pos.x = SCREEN_WIDTH - WIDTH_SPLAYER;
		}

		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			if (g_SPlayer.bJump == false)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_JUMP000);

				g_SPlayer.bJump = true;
				g_SPlayer.move.y = MOVE_JUMP;
			}
		}

		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ
			if (g_SPlayer.bJump == false)
			{
				if ((g_nCounterSSe % 17) == 0)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_WALK000);
				}
			}

				g_SPlayer.pos.x -= POS_X;

				//�ړ��ʂ��X�V�i����������j
				g_SPlayer.move.x -= MOVE_X;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ
			if (g_SPlayer.bJump == false)
			{
				if ((g_nCounterSSe % 17) == 0)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_WALK000);
				}
			}

			g_SPlayer.pos.x += POS_X;

			//�ړ��ʂ��X�V�i����������j
			g_SPlayer.move.x += MOVE_X;
		}

		//�ʒu���X�V
		g_SPlayer.pos.x += g_SPlayer.move.x;
		g_SPlayer.pos.y += g_SPlayer.move.y;

		//�ړ��ʂ��X�V
		g_SPlayer.move.x += (0.0f - g_SPlayer.move.x) * 0.1f;
		g_SPlayer.move.z += (0.0f - g_SPlayer.move.z) * 0.2f;

		//�u���b�N�Ƃ̓����蔻�菈��
		if (CollisionSBlock(&g_SPlayer.pos, &g_SPlayer.posOld, &g_SPlayer.move, WIDTH_SPLAYER, HEIGHT_SPLAYER, &g_SPlayer.pBlock) == true)
		{
			g_SPlayer.bJump = false;		//���n��Ԃɂ���
		}
		else
		{
			g_SPlayer.bJump = true;			//�W�����v��Ԃɂ���
		}

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		break;

	case PLAYERSTATE_APPEAR:			//�_�ŏ��
		//�v���C���[(�e)�Ƀv���C���[��pos�𑫂�
		g_SPlayer.pos.x = pPlayer->pos.x + SHADOW_X;
		g_SPlayer.pos.y = pPlayer->pos.y - SHADOW_Y;
		break;
	}

	if (pPlayer->state != PLAYERSTATE_SHADOW)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[1].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y - g_SPlayer.fHeight, DEF_POS_Z);
	pVtx[2].pos = D3DXVECTOR3(g_SPlayer.pos.x - g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);
	pVtx[3].pos = D3DXVECTOR3(g_SPlayer.pos.x + g_SPlayer.fWidth, g_SPlayer.pos.y, DEF_POS_Z);

	if (g_SPlayer.nCounterDirect == 0)
	{
		//�e�N�X�`�����W�̍Đݒ�
		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_UP_Y);
		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_UP_Y);
		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
	}
	else if (g_SPlayer.nCounterDirect == 1)
	{
		//�e�N�X�`�����W�̍Đݒ�
		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimSPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSPlayer->Unlock();
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void DrawSPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_SPlayer.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffSPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSPlayer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			0,												//�v���~�e�B�u�i�|���S���̐��j
			2);												//�`�悷��v���~�e�B�u��
	}
}

//==============================================================
//�v���C���[�ƃA�C�e���̃q�b�g����
//==============================================================
void CollisionSPlayer(void)
{
	Item *pItem = GetItem();
	Player *pPlayer = GetPlayer();
	int nCntPlayer;

	for (nCntPlayer = 0; nCntPlayer < 128; nCntPlayer++, pItem++)
	{
		if (pItem->bUse == true)
		{//�G���g�p����Ă���
			switch (pItem->nType)
			{
			case 0:		//�A�C�e��
				if (g_SPlayer.pos.x + g_SPlayer.fWidth >= pItem->pos.x - ITEM_POS && g_SPlayer.pos.x - g_SPlayer.fWidth <= pItem->pos.x + ITEM_POS
					&& g_SPlayer.pos.y >= pItem->pos.y - ITEM_POS && g_SPlayer.pos.y - g_SPlayer.fHeight <= pItem->pos.y + ITEM_POS)
				{//�A�C�e���ɓ�������
					HitItem();
					pItem->bUse = false;
				}
				break;

			case 1:
				if (g_SPlayer.pos.x + g_SPlayer.fWidth >= pItem->pos.x - ITEM_POS && g_SPlayer.pos.x - g_SPlayer.fWidth <= pItem->pos.x + ITEM_POS
					&& g_SPlayer.pos.y >= pItem->pos.y - ITEM_POS && g_SPlayer.pos.y - g_SPlayer.fHeight <= pItem->pos.y + ITEM_POS)
				{//�A�C�e���ɓ�������
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_GET000);

					if (pPlayer->nRemain < 5)
					{
						pPlayer->nRemain += 1;
					}
					pItem->bUse = false;
				}
				break;

			case 2:
				if (g_SPlayer.pos.x + g_SPlayer.fWidth >= pItem->pos.x - ITEM_POS && g_SPlayer.pos.x - g_SPlayer.fWidth <= pItem->pos.x + ITEM_POS
					&& g_SPlayer.pos.y >= pItem->pos.y - ITEM_POS && g_SPlayer.pos.y - g_SPlayer.fHeight <= pItem->pos.y + ITEM_POS)
				{//�A�C�e���ɓ�������
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_GET000);

					if (pPlayer->nRemain < 5)
					{
						pPlayer->nRemain += 1;
					}
					pItem->bUse = false;
				}
				break;
			}
		}
	}
}

//==============================================================
//�v���C���[�̃q�b�g����
//==============================================================
void HitSPlayer(int nDamage, int nType)
{
	
}

//==============================================================
//�v���C���[�̎擾
//==============================================================
SPlayer *GetSPlayer(void)
{
	return &g_SPlayer;		//�G�̏��̐擪�A�h���X��Ԃ�
}
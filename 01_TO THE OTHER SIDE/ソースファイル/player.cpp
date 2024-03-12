//==============================================================
//
//DirectX[player.cpp]
//Author:����������
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"splayer.h"
#include"block.h"
#include"enemy.h"
#include"goal.h"
#include"game.h"
#include"sound.h"

//�}�N����`
#define MAX_TEX				(2)			//�e�N�X�`���̍ő�l
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
#define WIDTH_PLAYER		(25.0f)		//�v���C���[�̕�
#define HEIGHT_PLAYER		(90.0f)		//�v���C���[�̍���
#define ANGLE_UP			(0.75f)		//�p�x�i��j
#define ANGLE_DOWN			(0.25f)		//�p�x�i���j
#define GROUND_HEIGHT		(660.0f)	//�n�ʂ̍���
#define CEIL_HEIGHT			(10.0f)		//�V��̍���
#define POS_X				(3.2f)		//�ʒu�X�V
#define MOVE_X				(0.2f)		//�ړ���
#define MOVE_Y				(0.5f)		//�ړ���(����)
#define MOVE_JUMP			(-14.0f)	//�ړ���(�W�����v�̏d��)
#define LIFE_MAX			(1)			//�̗͂̍ő�l

//�v���g�^�C�v�錾
void CollisionPlayer(void);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer[MAX_TEX] = {};	//�e�N�X�`��1�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_player;									//�v���C���[�̏��
int g_nCounterAnimPlayer;							//�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;							//�A�j���[�V�����p�^�[��No.
int g_nCounterSe;									//����se�̃J�E���^�[
int g_nPatternJump;									//�W�����v�؂�ւ�
float g_fLengthPlayer;								//�Ίp���̒���
float g_fAnglePlayer;								//�Ίp���̊p�x
VERTEX_2D g_aVertex[4];								//���_���W���i�[

//==============================================================
//�v���C���[�̏���������
//==============================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player000.png",
		&g_pTexturePlayer[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\jumpPlayer000.png",
		&g_pTexturePlayer[1]);

	g_nCounterAnimPlayer = 0;											//�J�E���^�[������������
	g_nPatternAnimPlayer = 0;											//�p�^�[��No.������������
	g_nCounterSe = 0;													//����SE�̃J�E���^�[������������
	g_nPatternJump = 0;													//�W�����v�؂�ւ�������������
	g_player.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);		//�ʒu������������
	g_player.move = D3DXVECTOR3(DEF_MOVE, DEF_MOVE, DEF_MOVE);			//�ړ��ʂ�����������
	g_player.rot = D3DXVECTOR3(DEF_ROT, DEF_ROT, DEF_ROT);				//����������������(Z�l���g�p)
	g_player.state = PLAYERSTATE_NORMAL;								//�ʏ��Ԃɂ���
	g_player.nLife = LIFE_MAX;											//�̗͂�����������
	g_player.nRemain = 5;												//�c�@������������
	g_player.nCounterDirect = 0;										//�A�j���[�V�����̌���������������
	g_player.nJudgeDirection = -1;										//��ʊO�ɏo�����̔��������������
	g_player.nCounterState = 0;											//��ԊǗ��J�E���^�[������������
	g_player.nCounterAppear = 0;										//�_�Ŏ��Ԃ�����������
	g_player.nCounterRevival = 0;										//�v���C���[�������Ԃ�����������
	g_player.fWidth = WIDTH_PLAYER;										//����������
	g_player.fHeight = HEIGHT_PLAYER;									//������������
	g_player.pBlock = NULL;												//�u���b�N�̏���������
	g_player.bJump = false;												//�W�����v���g�p���Ă��Ȃ�
	g_player.bDisp = true;												//�v���C���[���g�p���Ă���

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(WIDTH_PLAYER * WIDTH_PLAYER + HEIGHT_PLAYER * HEIGHT_PLAYER) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(WIDTH_PLAYER, HEIGHT_PLAYER);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, DEF_POS_Z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, DEF_POS_Z);

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
	g_pVtxBuffplayer->Unlock();
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void UninitPlayer(void)
{
	int nCntPlayer;

	//�e�N�X�`���̔j��
	for (nCntPlayer = 0; nCntPlayer < MAX_TEX; nCntPlayer++)
	{
		if (g_pTexturePlayer[nCntPlayer] != NULL)
		{
			g_pTexturePlayer[nCntPlayer]->Release();
			g_pTexturePlayer[nCntPlayer] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}
}

//==============================================================
//�v���C���[�̍X�V����
//==============================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^
	SPlayer *pSPlayer = GetSPlayer();
	g_nCounterAnimPlayer++;				//�J�E���^�[�����Z
	g_nCounterSe++;

	g_player.posOld = g_player.pos;		//�O��̈ʒu��ۑ�

	//if (g_player.pBlock != NULL)
	//{//�u���b�N�ɏ���Ă���
	//	g_player.pos.x += g_player.pBlock;
	//}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_player.state == PLAYERSTATE_NORMAL || g_player.state == PLAYERSTATE_SHADOW)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_SHADOW000);

			g_player.state = (g_player.state == PLAYERSTATE_NORMAL) ? PLAYERSTATE_SHADOW : PLAYERSTATE_NORMAL;
			pSPlayer->bJump = true;

		}
	}

	if (g_player.state != PLAYERSTATE_SHADOW)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_nPatternAnimPlayer = 0;
			}
			else
			{
				if ((g_nCounterAnimPlayer % 10) == 0)
				{//��莞�Ԍo��
					g_nPatternAnimPlayer += 1;
				}

				if (g_player.bJump == false)
				{
					if ((g_nCounterSe % 17) == 0)
					{
						//�T�E���h�̍Đ�
						PlaySound(SOUND_LABEL_SE_WALK000);
					}
				}

				g_player.pos.x -= POS_X;

				//�ړ��ʂ��X�V�i����������j
				g_player.move.x -= MOVE_X;

				//������
				g_player.nCounterDirect = 1;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_nPatternAnimPlayer = 0;
			}
			else
			{
				if ((g_nCounterAnimPlayer % 10) == 0)
				{//��莞�Ԍo��
					g_nPatternAnimPlayer += 1;
				}

				if (g_player.bJump == false)
				{
					if ((g_nCounterSe % 17) == 0)
					{
						//�T�E���h�̍Đ�
						PlaySound(SOUND_LABEL_SE_WALK000);
					}
				}

				g_player.pos.x += POS_X;

				//�ړ��ʂ��X�V�i����������j
				g_player.move.x += MOVE_X;

				//�E����
				g_player.nCounterDirect = 0;
			}
		}
		else
		{
			g_nPatternAnimPlayer = 0;
		}

		//�d�͏���
		g_player.move.y += MOVE_Y;

		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			if (g_player.bJump == false)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_JUMP000);

				g_player.bJump = true;
				g_player.move.y = MOVE_JUMP;
				g_nPatternJump = 1;
			}
		}

		//�ʒu���X�V
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		//�ړ��ʂ��X�V
		g_player.move.x += (0.0f - g_player.move.x) * 0.1f;
		g_player.move.z += (0.0f - g_player.move.z) * 0.2f;

		//�������X�V
		g_player.rot.z += g_player.move.z;

		//��ʊO�ɏo���ꍇ
		if (g_player.pos.x - WIDTH_PLAYER + 5.0f <= 0)
		{//���ɏo���ꍇ
			g_player.pos.x = SCREEN_WIDTH - WIDTH_PLAYER;
			g_player.pos.y = 660.0f;
			g_player.nJudgeDirection = 0;
		}
		else if (g_player.pos.x + WIDTH_PLAYER - 5.0f >= SCREEN_WIDTH)
		{//�E�ɏo���ꍇ
			g_player.pos.x = WIDTH_PLAYER;
			g_player.pos.y = 660.0f;
			g_player.nJudgeDirection = 1;
		}
		else if (g_player.pos.y - HEIGHT_PLAYER >= SCREEN_HEIGHT)
		{//���ɗ������ꍇ
			//�v���C���[�̃q�b�g����
			HitPlayer(LIFE_MAX, 0);
		}
		else
		{
			//�u���b�N�Ƃ̓����蔻�菈��
			if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, WIDTH_PLAYER, HEIGHT_PLAYER, &g_player.pBlock) == true)
			{
				g_player.bJump = false;		//���n��Ԃɂ���
			}
			else
			{
				g_player.bJump = true;		//�W�����v��Ԃɂ���
			}

			if (g_player.state != PLAYERSTATE_APPEAR)
			{
				//�G�Ƃ̓����蔻�菈��
				if (CollisionEnemy(&g_player.pos, &g_player.posOld, &g_player.move, WIDTH_PLAYER, HEIGHT_PLAYER) == true)
				{
					g_player.bJump = false;		//���n��Ԃɂ���
				}
			}
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, DEF_POS_Z);

		if (g_player.nCounterDirect == 0)
		{
			//�e�N�X�`�����W�̍Đݒ�
			pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_UP_Y);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_UP_Y);
			pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		}
		else if (g_player.nCounterDirect == 1)
		{
			//�e�N�X�`�����W�̍Đݒ�
			pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
			pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 4) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		}
		//else if (g_nPatternJump == 1)
		//{
		//	if (g_player.nCounterDirect == 0)
		//	{
		//		//�e�N�X�`�����W�̍Đݒ�
		//		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_UP_Y);
		//		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_UP_Y);
		//		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_DOWN_Y);
		//		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		//	}
		//	else if (g_player.nCounterDirect == 1)
		//	{
		//		//�e�N�X�`�����W�̍Đݒ�
		//		pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_DOWN_Y);
		//		pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y);
		//		pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		//		pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimPlayer % 6) * TEX_RIGHT_X + TEX_RIGHT_X, TEX_DOWN_Y + TEX_DOWN_Y);
		//	}
		//	
		//}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffplayer->Unlock();
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:
		if ((g_player.nCounterAppear % 3) == 0)
		{
			g_player.bDisp = (g_player.bDisp == false) ? true : false;
		}

		if (g_player.nCounterAppear > 0)
		{
			g_player.nCounterAppear--;
		}
		else if (g_player.nCounterAppear <= 0)
		{
			g_player.bDisp = true;
			g_player.state = PLAYERSTATE_NORMAL;
		}

		break;

	case PLAYERSTATE_NORMAL:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		CollisionPlayer();
		break;

	case PLAYERSTATE_SHADOW:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.5f);
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		}

		break;

	case PLAYERSTATE_WAIT:
		g_player.nCounterRevival++;
		g_player.pos = D3DXVECTOR3(DEF_POS_X, DEF_POS_Y, DEF_POS_Z);			//�ʒu������������

		if (g_player.nCounterRevival >= 80)
		{//�v���C���[����
			g_player.nCounterAppear = 99;
			g_player.state = PLAYERSTATE_APPEAR;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			g_player.nLife = LIFE_MAX;
			g_player.nCounterRevival = 0;
		}
		break;

	case PLAYERSTATE_DEATH:
		
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffplayer->Unlock();
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntPlayer;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPlayer = 0; nCntPlayer < MAX_TEX; nCntPlayer++)
	{
		if (g_player.bDisp == true)
		{
			/*if (g_player.nCounterDirect == 0)
			{*/
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePlayer[0]);
			//}
			//else if (g_player.nCounterDirect == 1)
			//{
			//	//�e�N�X�`���̐ݒ�
			//	pDevice->SetTexture(0, g_pTexturePlayer[0]);
			//}
			//else if (g_nPatternJump == 1)
			//{
			//	if (g_player.nCounterDirect == 0)
			//	{
			//		//�e�N�X�`���̐ݒ�
			//		pDevice->SetTexture(0, g_pTexturePlayer[1]);
			//	}
			//	else if (g_player.nCounterDirect == 1)
			//	{
			//		//�e�N�X�`���̐ݒ�
			//		pDevice->SetTexture(0, g_pTexturePlayer[1]);
			//	}
			//}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntPlayer * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================
//�v���C���[�ƃS�[���̓����蔻�菈��
//==============================================================
void CollisionPlayer(void)
{
	Goal *pGoal = GetGoal();		//�G�̏��̐擪�A�h���X����������

	if (pGoal->bUse == true)
	{//�G���g�p����Ă���
		switch (pGoal->nType)
		{
		case 0:		//�S�[��
			if (g_player.pos.x >= pGoal->pos.x - 50.0f && g_player.pos.x <= pGoal->pos.x + 50.0f 
				&& g_player.pos.y >= pGoal->pos.y - 50.0f && g_player.pos.y <= pGoal->pos.y + 50.0f)
			{//�S�[���ɓ�������
				//�Q�[����Ԃ̐ݒ�
				SetGameState(GAMESTATE_END, 50);

				pGoal->bUse = false;
			}
			break;
		}
	}
}

//==============================================================
//�v���C���[�̃q�b�g����
//==============================================================
void HitPlayer(int nDamage, int nType)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^
	Goal *pGoal = GetGoal();

	g_player.nLife -= nDamage;

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_DAMAGE000);

	if (g_player.nLife <= 0)
	{//�v���C���[�̗̑͂��Ȃ��Ȃ���
		g_player.nRemain--;
		
		g_player.bDisp = false;

		if (g_player.nRemain != 0)
		{
			g_player.state = PLAYERSTATE_WAIT;
		}
		else if (g_player.nRemain <= 0)
		{
			g_player.state = PLAYERSTATE_DEATH;

			//�Q�[����Ԃ̐ݒ�
			SetGameState(GAMESTATE_END, 50);
		}
	}
	else if (g_player.nLife != 0)
	{//�v���C���[�̗̑͂��c���Ă���
		g_player.state = PLAYERSTATE_DAMAGE;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.nCounterState = 5;			//�_���[�W��Ԃ�ۂ��Ԃ�ݒ�

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffplayer->Unlock();
	}
}

//==============================================================
//�v���C���[�̎擾
//==============================================================
Player *GetPlayer(void)
{
	return &g_player;		//�G�̏��̐擪�A�h���X��Ԃ�
}
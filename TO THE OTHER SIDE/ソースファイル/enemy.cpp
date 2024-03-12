//==============================================================
//
//DirectX[enemy.cpp]
//Author:����������
//
//==============================================================
#include"main.h"
#include"enemy.h"
#include"input.h"
#include"player.h"
#include"exit.h"
#include"particle.h"
#include"game.h"
#include"sound.h"

//�}�N����`
#define NUM_ENEMY		(2)			//�G�̎��
#define DEF_POS_Z		(0.0f)		//�v���C���[��pos.z�̏����l
#define COL_R			(1.0f)		//�ԐF�̐��l
#define COL_G			(1.0f)		//�ΐF�̐��l
#define COL_B			(1.0f)		//�F�̐��l
#define COL_A			(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X		(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X		(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y		(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y		(1.0f)		//�e�N�X�`���̉�y�̏����l
#define TEX_NUM			(2)			//�e�N�X�`���̐�
#define TEX_NUM_SIDE	(0.5f)		//���̃e�N�X�`��
#define TEX_NUM_VER		(1.0f)		//�c�̃e�N�X�`��
#define BOSS_WIDTH		(90.0f)		//�{�X�̕�
#define BOSS_HEIGHT		(170.0f)	//�{�X�̍���
#define ENEMY_WIDTH		(30.0f)		//�G���G�̕�
#define ENEMY_HEIGHT	(60.0f)		//�G���G�̍���
#define PLAYER_WIDTH	(25.0f)		//�v���C���[�̈�����
#define PLAYER_HEIGHT	(25.0f)		//�v���C���[�̈�������

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];									//�G�̎��
int g_nCounterEnemy;										//�e�̃J�E���^�[
int g_nNumEnemy;											//�G�̑���
int g_nCounterBgm;											//BGM�J�E���^�[
int nCounterPar;											//�p�[�e�B�N�������J�E���^�[��������


//==============================================================
//�G�̏���������
//==============================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy001.png",
		&g_pTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy000.png",
		&g_pTextureEnemy[1]);

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);			//�ʒu�̏�����
		g_aEnemy[nCntEnemy].pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu2�̏�����
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aEnemy[nCntEnemy].nType = nCntEnemy;							//�G�̎�ނ̏�����
		g_aEnemy[nCntEnemy].nLife = 1;									//�G�̗̑͂̏�����
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					//�G�̏�Ԃ̏�����
		g_aEnemy[nCntEnemy].fWidth = BOSS_WIDTH;						//�{�X�̕���������
		g_aEnemy[nCntEnemy].fHeight = BOSS_HEIGHT;						//�{�X�̍�����������
		g_aEnemy[nCntEnemy].g_fLengthEnemy = 0;							//�Ίp���̒����̏�����
		g_aEnemy[nCntEnemy].g_fAngleEnemy = 0;							//�Ίp���̊p�x�̏�����
		g_aEnemy[nCntEnemy].nCounterAnimEnemy = 0;						//�A�j���[�V�����J�E���^�[0�̏�����
		g_aEnemy[nCntEnemy].nPatternAnimEnemy = 0;						//�p�^�[��No.�̏�����0
		g_aEnemy[nCntEnemy].nCounterMove = 0;							//�G�̈ړ��J�E���^�[�̏�����
		g_aEnemy[nCntEnemy].fCurve = 0.0f;								//�p�x�̏�����
		g_aEnemy[nCntEnemy].fBossPos = 0.0f;							//�{�X�̍~�������̏�����
		g_aEnemy[nCntEnemy].nCounterBulletTime = 0;						//�G���ł��Ԃ�������
		g_aEnemy[nCntEnemy].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
		g_aEnemy[nCntEnemy].bJump = false;
	}

	g_nNumEnemy = 0;													//�G�̑����̏�����
	g_nCounterBgm = 0;
	nCounterPar = 0;							//�p�[�e�B�N�������J�E���^�[��������

	//�Ίp���̒������Z�o����
	g_aEnemy[nCntEnemy].g_fLengthEnemy = sqrtf(80.0f * 80.0f + 20.0f * 20.0f) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	g_aEnemy[nCntEnemy].g_fAngleEnemy = atan2f(80.0f, 20.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);

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
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//�G�̏I������
//==============================================================
void UninitEnemy(void)
{
	int nCntEnemy;

	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//==============================================================
//�G�̍X�V����
//==============================================================
void UpdateEnemy(void)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^
	Player *pPlayer = GetPlayer();
	int nCntEnemy;
	int nMove;							//�G�̃����_���ȍs��������

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g���Ă���Ƃ�
			g_aEnemy[nCntEnemy].nCounterMove++;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			if (pPlayer->nJudgeDirection == 0)
			{
				g_aEnemy[nCntEnemy].pos.x += SCREEN_WIDTH;
				g_aEnemy[nCntEnemy].pos.y = 650.0f;
			}
			else if (pPlayer->nJudgeDirection == 1)
			{
				g_aEnemy[nCntEnemy].pos.x -= SCREEN_WIDTH;
				g_aEnemy[nCntEnemy].pos.y = 650.0f;
			}
			else
			{
				if (CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, &g_aEnemy[nCntEnemy].pBlock) == true)
				{
					g_aEnemy[nCntEnemy].bJump = false;

					if (g_aEnemy[nCntEnemy].nType == 0)
					{
						nCounterPar += 1;

						if (nCounterPar <= 1)
						{
							SetParticle(g_aEnemy[nCntEnemy].pos, 0);
						}
					}
				}
				else
				{
					if (g_aEnemy[nCntEnemy].nType == 0)
					{
						nCounterPar = 0;
					}
					g_aEnemy[nCntEnemy].bJump = true;
				}
			}

			if (g_aEnemy[nCntEnemy].pos.x >= 0 && g_aEnemy[nCntEnemy].pos.x <= SCREEN_WIDTH)
			{
				g_aEnemy[nCntEnemy].move.y += 0.5f;
			}
			else
			{
				g_aEnemy[nCntEnemy].move.y = 0.0f;
			}

			if (g_aEnemy[nCntEnemy].nType == 0)
			{//�{�X
				g_aEnemy[nCntEnemy].nCounterAnimEnemy++;

				nMove = rand() % 5 + 1;

				if (g_nCounterBgm == 50)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_BGMBOSS);
				}

				g_nCounterBgm += 1;

				if ((g_aEnemy[nCntEnemy].nCounterMove % 150) == 0)
				{
					//�G���ړ�������
					g_aEnemy[nCntEnemy].move.y -= 20.0f;

					switch (nMove)
					{
					case 1:
						if (g_aEnemy[nCntEnemy].pos.x - BOSS_WIDTH >= BOSS_WIDTH + 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x -= 100.0f;
						}
						break;

					case 2:
						if (g_aEnemy[nCntEnemy].pos.x + BOSS_WIDTH <= SCREEN_WIDTH - BOSS_WIDTH - 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x += 100.0f;
						}
						break;

					case 3:
						if (g_aEnemy[nCntEnemy].pos.x - BOSS_WIDTH >= BOSS_WIDTH + 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x -= 50.0f;
						}
						break;

					case 4:
						if (g_aEnemy[nCntEnemy].pos.x + BOSS_WIDTH <= SCREEN_WIDTH - BOSS_WIDTH - 10.0f)
						{
							g_aEnemy[nCntEnemy].pos.x += 50.0f;
						}
						break;

					case 5:

						break;
					}
				}
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{//�G���G
				g_aEnemy[nCntEnemy].nCounterAnimEnemy++;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);

			if (g_aEnemy[nCntEnemy].nType == 0 && g_aEnemy[nCntEnemy].nLife == 0)
			{
				SetGameState(GAMESTATE_END, 50);
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
					pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
					pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
					pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
				}
				break;

			case ENEMYSTATE_WAIT:

				break;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnimEnemy % 30) == 0)
			{//��莞�Ԍo��
				g_aEnemy[nCntEnemy].nPatternAnimEnemy = (g_aEnemy[nCntEnemy].nPatternAnimEnemy + 1) % 2;

				//�e�N�X�`�����W�̍Đݒ�
				pVtx[0].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER);
				pVtx[1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE + TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER);
				pVtx[2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER + TEX_NUM_VER);
				pVtx[3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnimEnemy % TEX_NUM) * TEX_NUM_SIDE + TEX_NUM_SIDE, (g_aEnemy[nCntEnemy].nPatternAnimEnemy / 1) * TEX_NUM_VER + TEX_NUM_VER);
			}
		}
		pVtx += 4;									//���_�f�[�^�̃|�C���^���S���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���	
			//�e�N�X�`���̐ݒ�
			if (g_aEnemy[nCntEnemy].nType == 0)
			{
				pDevice->SetTexture(0, g_pTextureEnemy[0]);
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{
				pDevice->SetTexture(0, g_pTextureEnemy[1]);
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCntEnemy * 4,									//�v���~�e�B�u�i�|���S���̐��j
				2);												//�`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================
//�G�̐ݒ菈��
//==============================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].pos2 = pos;
			g_aEnemy[nCntEnemy].nType = nType;

			if (g_aEnemy[nCntEnemy].nType == 0)
			{//�{�X
				g_aEnemy[nCntEnemy].fWidth = BOSS_WIDTH;
				g_aEnemy[nCntEnemy].fHeight = BOSS_HEIGHT;
				g_aEnemy[nCntEnemy].nLife = 16;

				g_nNumEnemy++;
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{//�G���G
				g_aEnemy[nCntEnemy].fWidth = ENEMY_WIDTH;
				g_aEnemy[nCntEnemy].fHeight = ENEMY_HEIGHT;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, DEF_POS_Z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, DEF_POS_Z);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

			g_aEnemy[nCntEnemy].bUse = true;		//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;									//���_�f�[�^�̃|�C���^���S���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//�G�Ƃ̓����蔻�菈��
//==============================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	int nCntEnemy;
	bool bLand = false;		//���n�������ǂ���

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].nType == 0)
			{
				if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f)
				{//���ɂ߂荞�񂾏ꍇ
					bLand = true;

					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_ENEMY000);

					//�G�̃q�b�g����
					HitEnemy(nCntEnemy, 1);
					pPos->y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;										//�G�̏�ɗ�������
					pMove->y = -14.0f;																						//�ړ��ʂ��O�ɂ���
				}
				else if (pPosOld->y - fHeight >= g_aEnemy[nCntEnemy].pos.y
					&& pPos->y - fHeight <= g_aEnemy[nCntEnemy].pos.y
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f)
				{//��ɂ߂荞�񂾏ꍇ
					bLand = false;

					//�v���C���[�̃q�b�g����
					HitPlayer(1, 0);

					pPos->y = g_aEnemy[nCntEnemy].pos.y + fHeight + PLAYER_HEIGHT;											//�G�̉��ɗ�������
					pMove->y = 0.0f;																						//�ړ��ʂ��O�ɂ���
				}
				else if (pPosOld->x + fWidth <= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->x + fWidth >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 40.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//���ɂ߂荞�񂾏ꍇ
					bLand = false;

					//�v���C���[�̃q�b�g����
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth - fWidth + 40.0f;						//�G�̍��ɗ�������
					pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���
				}
				else if (pPosOld->x - fWidth >= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f
					&& pPos->x - fWidth <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 40.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//�E�ɂ߂荞�񂾏ꍇ
					bLand = false;

					//�v���C���[�̃q�b�g����
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + fWidth - 40.0f;						//�G�̍��ɗ�������
					pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���
				}
			}
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{
				if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f)
				{//���ɂ߂荞�񂾏ꍇ
					bLand = true;

					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_ENEMY000);

					//�G�̃q�b�g����
					HitEnemy(nCntEnemy, 1);
					pPos->y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;										//�G�̏�ɗ�������
					pMove->y = -14.0f;																						//�ړ��ʂ��O�ɂ���
				}
				else if (pPosOld->y - fHeight >= g_aEnemy[nCntEnemy].pos.y
					&& pPos->y - fHeight <= g_aEnemy[nCntEnemy].pos.y
					&& pPos->x + fWidth > g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->x - fWidth < g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f)
				{//��ɂ߂荞�񂾏ꍇ
					bLand = false;

					//�v���C���[�̃q�b�g����
					HitPlayer(1, 0);

					pPos->y = g_aEnemy[nCntEnemy].pos.y + fHeight + PLAYER_HEIGHT;											//�G�̉��ɗ�������
					pMove->y = 0.0f;																						//�ړ��ʂ��O�ɂ���
				}
				else if (pPosOld->x + fWidth <= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->x + fWidth >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth + 10.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//���ɂ߂荞�񂾏ꍇ
					bLand = false;

					//�v���C���[�̃q�b�g����
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth - fWidth + 10.0f;						//�G�̍��ɗ�������
					pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���
				}
				else if (pPosOld->x - fWidth >= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f
					&& pPos->x - fWidth <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth - 10.0f
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight
					&& pPos->y - fHeight - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y)
				{//�E�ɂ߂荞�񂾏ꍇ
					bLand = false;

					//�v���C���[�̃q�b�g����
					HitPlayer(1, 0);

					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + fWidth - 10.0f;						//�G�̍��ɗ�������
					pMove->x = 0.0f;																						//�ړ��ʂ��O�ɂ���
				}
			}
		}
	}

	return bLand;
}


//==============================================================
//�G�̎擾
//==============================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];		//�G�̏��̐擪�A�h���X��Ԃ�
}

//==============================================================
//�G�̃q�b�g����
//==============================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife == 0)
	{//�G�̗̑͂��Ȃ��Ȃ���
		//�G�������鏈��
		SetExit(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nType);

		if (g_aEnemy[nCntEnemy].nType == 0)
		{
			g_nNumEnemy--;

			//�T�E���h�̒�~
			StopSound();
		}

		if (g_nNumEnemy <= 0 && g_aEnemy[nCntEnemy].nType == 0)
		{
			SetGameState(GAMESTATE_END, 50);
		}

		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{//�G�̗̑͂��c���Ă���
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;			//�_���[�W��Ԃ�ۂ��Ԃ�ݒ�

		//�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_HIT002);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntEnemy * 4;							//���_�f�[�^�̃|�C���^���S���W�߂�

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}

//==============================================================
//�G�̐�����������
//==============================================================
void SubNumEnemy(void)
{
	g_nNumEnemy--;
}

//==============================================================
//�G�̑����̎擾
//==============================================================
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}
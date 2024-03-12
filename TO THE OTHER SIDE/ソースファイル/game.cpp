//==============================================================
//
//DirectX[game.cpp]
//Author:����������
//
//==============================================================
#include"game.h"
#include"input.h"
#include"bg.h"
#include"player.h"
#include"splayer.h"
#include"block.h"
#include"sblock.h"
#include"enemy.h"
#include"goal.h"
#include"fade.h"
#include"Set.h"
#include"item.h"
#include"remain.h"
#include"pausemenu.h"
#include"exit.h"
#include"effect.h"
#include"particle.h"
#include"sound.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
int g_nCounterGameState = 0;				//��ԊǗ��J�E���^�[
bool g_bPause = false;						//�|�[�Y��Ԃ�ON/OFF
bool g_bStart = true;						//�X�^�[�g���g�p���Ă��邩

//==============================================================
//�Q�[����ʂ̏���������
//==============================================================
void InitGame(void)
{
	//�w�i�̏�����
	Initbg();

	//�v���C���[�̏�����
	InitPlayer();

	//�v���C���[�i�e�j�̏���������
	InitSPlayer();

	//�S�[���̏���������
	InitGoal();

	//�u���b�N�̏���������
	InitBlock();

	//�u���b�N�̐ݒ菈��
	Load();
	Set();

	//�u���b�N�i�e�j�̏���������
	InitSBlock();

	//�u���b�N(�e)�̐ݒ菈��
	SLoad();
	SSet();

	//�{�^��
	SetSBlock(D3DXVECTOR3(3400.0f, 650.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(3800.0f, 290.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(5500.0f, 650.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(7330.0f, 650.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(7335.0f, 860.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(8110.0f, 850.0f, 0.0f), 4);
	SetSBlock(D3DXVECTOR3(10650.0f, 650.0f, 0.0f), 4);

	//�G�̏���������
	InitEnemy();

	//�G�̐ݒ菈��
	SetEnemy(D3DXVECTOR3(2200.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(3500.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(5400.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(6600.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(6900.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(9300.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(9600.0f, 300.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(9900.0f, 300.0f, 0.0f), 1);

	//�A�C�e���̏���������
	InitItem();

	//�A�C�e���̐ݒ�
	SetItem(D3DXVECTOR3(6200.0f, 600.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(6500.0f, 50.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(8330.0f, 100.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(9500.0f, 400.0f, 0.0f), 2);
	SetItem(D3DXVECTOR3(9700.0f, 400.0f, 0.0f), 2);
	SetItem(D3DXVECTOR3(9900.0f, 400.0f, 0.0f), 2);

	//�c�@�̏���������
	InitRemain();

	//�G�����ʎ��̏���������
	InitExit();

	//�|�[�Y���j���[�̏���������
	InitPauseMenu();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);

	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_bStart = true;
	g_bPause = false;
}

//==============================================================
//�Q�[����ʂ̏I������
//==============================================================
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�w�i�̏I������
	Uninitbg();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	//�v���C���[�i�e�j�̏I������
	UninitSPlayer();

	//�u���b�N�̏I������
	UninitBlock();

	//�u���b�N�i�e�j�̏I������
	UninitSBlock();

	//�S�[���̏I������
	UninitGoal();

	//�A�C�e���̏I������
	UninitItem();

	//�c�@�̏I������
	UninitRemain();

	//�G�����ʂƂ��̏I������
	UninitExit();

	//�|�[�Y���j���[�̏I������
	UninitPauseMenu();

	//�G�t�F�N�g�̏I������
	UninitEffect();
}

//==============================================================
//�Q�[����ʂ̍X�V����
//==============================================================
void UpdateGame(void)
{
	Player *pPlayer = GetPlayer();

	if (g_bPause == false)
	{
		//�w�i�̍X�V����
		Updatebg();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̏I������
		UpdateEnemy();

		//�v���C���[�i�e�j�̍X�V����
		UpdateSPlayer();

		//�u���b�N�̍X�V����
		UpdateBlock();

		//�u���b�N�i�e�j�̍X�V����
		UpdateSBlock();

		//�S�[���̍X�V����
		UpdateGoal();

		//�A�C�e���̍X�V����
		UpdateItem();

		//�c�@�̍X�V����
		UpdateRemain();

		//�G�����ʂƂ��̍X�V����
		UpdateExit();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();
	}
	else if (g_bPause == true)
	{
		UpdatePauseMenu();
	}

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = (g_bPause == false) ? true : false;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:						//�ʏ���
		break;
	case GAMESTATE_END:							//�I�����
		g_nCounterGameState++;
		if (g_nCounterGameState <= 160)
		{
			g_gameState = GAMESTATE_NORMAL;		//�������Ă��Ȃ���Ԃɐݒ�
			//���[�h�ݒ�(���U���g��ʂɈڍs)
			SetFade(MODE_RESULT);				//�t�F�[�h�A�E�g
		}
		break;
	}
}

//==============================================================
//�Q�[����ʂ̕`�揈��
//==============================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	Drawbg();

	//�u���b�N�i�e�j�̕`�揈��
	DrawSBlock();

	//�v���C���[�i�e�j�̕`�揈��
	DrawSPlayer();

	//�G�����ʂƂ��̕`�揈��
	DrawExit();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�G�̕`�揈��
	DrawEnemy();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�S�[���̕`�揈��
	DrawGoal();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�c�@�̕`�揈��
	DrawRemain();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	if (g_bPause == true)
	{
		DrawPauseMenu();
	}
}

//==============================================================
//�Q�[����Ԃ̐ݒ�
//==============================================================
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
}

//==============================================================
//�Q�[����Ԃ̎擾
//==============================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//==============================================================
//�|�[�Y��ʂ̐ݒ菈��
//==============================================================
void SetEnablePauseMenu(bool bPouse)
{
	g_bPause = bPouse;
}
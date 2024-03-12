//==============================================================
//
//DirectX[PauseMenu.cpp]
//Author:����������
//
//==============================================================
#include"pausemenu.h"
#include"input.h"
#include"title.h"
#include"game.h"
#include"fade.h"
#include"sound.h"

//�}�N����`
#define NUM_PAUSE_MENU		(3)		//�|�[�Y��ʂ̐�
#define COL_R				(1.0f)	//�ԐF�̐��l
#define COL_G				(1.0f)	//�ΐF�̐��l
#define COL_B				(1.0f)	//�F�̐��l
#define COL_A				(1.0f)	//�s�����x�̐��l

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu[NUM_PAUSE_MENU] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;				//���_�o�b�t�@�̃|�C���^
PAUSE_MENU g_pauseMenu;											//�|�[�Y���j���[
int nPauseMenu[NUM_PAUSE_MENU];
bool bUse;

//==============================================================
//�|�[�Y��ʂ̏���������
//==============================================================
void InitPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntPauseMenu;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause000.png",
		&g_pTexturePauseMenu[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_pTexturePauseMenu[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_pTexturePauseMenu[2]);

	g_pauseMenu = PAUSE_MENU_CONTINUE;		//�|�[�Y���j���[�̏�����

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		nPauseMenu[nCntPauseMenu] = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(280.0f, (nCntPauseMenu * 150) + 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(980.0f, (nCntPauseMenu * 150) + 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(280.0f, (nCntPauseMenu * 150) + 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(980.0f, (nCntPauseMenu * 150) + 200.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMenu->Unlock();
}

//==============================================================
//�|�[�Y��ʂ̏I������
//==============================================================
void UninitPauseMenu(void)
{
	int nCntPauseMenu;

	//�e�N�X�`���̔j��
	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		if (g_pTexturePauseMenu[nCntPauseMenu] != NULL)
		{
			g_pTexturePauseMenu[nCntPauseMenu]->Release();
			g_pTexturePauseMenu[nCntPauseMenu] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//==============================================================
//�|�[�Y��ʂ̍X�V����
//==============================================================
void UpdatePauseMenu(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntPauseMenu;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		if (GetKeyboardTrigger(DIK_P) == true)
		{//P�L�[�������ꂽ
			g_pauseMenu = PAUSE_MENU_CONTINUE;		//�|�[�Y���j���[�̏�����
			nPauseMenu[nCntPauseMenu] = 0;			//�I�����̏�����
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{//W�L�[�������ꂽ
			if (nPauseMenu[nCntPauseMenu] >= 1)
			{//���֐i��
				nPauseMenu[nCntPauseMenu]--;
			}
			else if (nPauseMenu[nCntPauseMenu] == 0)
			{//CONTINUE�ɖ߂�
				nPauseMenu[nCntPauseMenu] = 2;
			}
		}
		else if (GetKeyboardTrigger(DIK_S) == true)
		{//S�L�[�������ꂽ
			if (nPauseMenu[nCntPauseMenu] == 2)
			{//QUIT�ɖ߂�
				nPauseMenu[nCntPauseMenu] = 0;
			}
			else if (nPauseMenu[nCntPauseMenu] >= 0)
			{//��֐i��
				nPauseMenu[nCntPauseMenu]++;
			}
		}

		switch (nPauseMenu[nCntPauseMenu])
		{//���[�h�I��
		case PAUSE_MENU_CONTINUE:
			g_pauseMenu = PAUSE_MENU_CONTINUE;
			break;

		case PAUSE_MENU_RETRY:
			g_pauseMenu = PAUSE_MENU_RETRY;
			break;

		case PAUSE_MENU_QUIT:
			g_pauseMenu = PAUSE_MENU_QUIT;
			break;
		}

		if (g_pauseMenu == nCntPauseMenu)
		{//�I�����Ă���
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		}

		if (g_pauseMenu != nCntPauseMenu)
		{//�I�����Ă��Ȃ�
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
			pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
			pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
			pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, 0.3f);
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMenu->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//����L�[�iENTER�L�[�j�������ꂽ
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			//�Q�[���ĊJ
			SetEnablePauseMenu(false);
			break;

		case PAUSE_MENU_RETRY:
			//���[�h�ݒ�(�Q�[����ʂ̍ŏ��Ɉڍs)
			SetFade(MODE_GAME);				//�t�F�[�h�A�E�g
			break;

		case PAUSE_MENU_QUIT:
			//���[�h�ݒ�(�^�C�g����ʂɈڍs)
			SetFade(MODE_TITLE);			//�t�F�[�h�A�E�g
			break;
		}
	}
}

//==============================================================
//�|�[�Y��ʂ̕`�揈��
//==============================================================
void DrawPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntPauseMenu;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPauseMenu = 0; nCntPauseMenu < NUM_PAUSE_MENU; nCntPauseMenu++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseMenu[nCntPauseMenu]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			nCntPauseMenu * 4,								//�v���~�e�B�u�i�|���S���̐��j
			2);												//�`�悷��v���~�e�B�u��
	}
}
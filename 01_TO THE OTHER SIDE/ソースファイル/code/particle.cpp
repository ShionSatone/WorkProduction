//==============================================================
//
//DirectX[particle.cpp]
//Author:����������
//
//==============================================================
#include"main.h"
#include"particle.h"
#include"effect.h"
#include"player.h"
#include"enemy.h"

//�}�N����`
#define MAX_PARTICLE		(128)		//�p�[�e�B�N���̍ő吔

//�p�[�e�B�N���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu�i�����ʒu�j
	int nLife;				//�����i�������ԁj
	D3DXCOLOR col;			//�F
	float fRadius;			//���a�i�傫���j
	int nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
} Particle;

//�O���[�o���ϐ�
Particle g_aParticle[MAX_PARTICLE];							//�p�[�e�B�N���̏��

//==============================================================
//�p�[�e�B�N���̏���������
//==============================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�̏��̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�i�����ʒu�j�̏�����
		g_aParticle[nCntParticle].nLife = 0;								//�����i�������ԁj�̏�����
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F�̏�����
		g_aParticle[nCntParticle].fRadius = 10.0f;							//���a�̏�����
		g_aParticle[nCntParticle].nType = 0;								//��ނ̏�����
		g_aParticle[nCntParticle].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
	}
}

//==============================================================
//�p�[�e�B�N���̏I������
//==============================================================
void UninitParticle(void)
{
	
}

//==============================================================
//�p�[�e�B�N���̍X�V����
//==============================================================
void UpdateParticle(void)
{
	int nCntParticle, nCntAppear, nLife;
	float fAngle, fMove, fRadius;
	D3DXVECTOR3 move, pos;
	D3DXCOLOR col;
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//�p�[�e�B�N�����g�p����Ă���
			//�p�[�e�B�N���̐���
			for (nCntAppear = 0; nCntAppear < 5; nCntAppear++)
			{
				if (g_aParticle[nCntParticle].nType == 0)
				{
					//�ʒu�̐ݒ�
					pos = pEnemy->pos;

					//�p�x�����߂�
					fAngle = (float)(rand() % 314 - 624) / 100.0f;

					//�ړ��ʂ����߂�
					fMove = (float)(rand() % 100) / 10.0f + 8.0f;

					//�ړ��ʂ̐ݒ�
					move.x = sinf(fAngle) * fMove;
					move.y = cosf(fAngle) * fMove;

					//�F�̐ݒ�
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//���a�̐ݒ�
					fRadius = 0.5f;

					//�����̐ݒ�
					nLife = g_aParticle[nCntParticle].nLife;
				}

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos,
					move,
					col,
					fRadius,
					nLife);
			}

			//�����̃J�E���g�_�E��
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{//�������s�����ꍇ
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}

//==============================================================
//�p�[�e�B�N���̕`�揈��
//==============================================================
void DrawParticle(void)
{
	
}

//==============================================================
//�p�[�e�B�N���̐ݒ菈��
//==============================================================
void SetParticle(D3DXVECTOR3 pos, int nType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�p�[�e�B�N�����g�p����Ă��Ȃ�
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;

			/*if (g_aParticle[nCntParticle].nType == 0)
			{*/
				g_aParticle[nCntParticle].nLife = 7;
			//}

			g_aParticle[nCntParticle].bUse = true;		//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}
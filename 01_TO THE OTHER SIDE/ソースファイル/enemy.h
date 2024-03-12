//==============================================================
//
//DirectX[enemy.h]
//Author:����������
//
//==============================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"
#include"block.h"

//�}�N����`
#define MAX_ENEMY		(128)		//�G�̍ő吔

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,			//�ʏ���
	ENEMYSTATE_DAMAGE,				//�_���[�W���
	ENEMYSTATE_WAIT,				//�o���҂����(�\���Ȃ�)
	ENEMYSTATE_DEATH,				//���S���
	ENEMYSTATE_MAX
} ENEMYSTATE;

//�G�\�����̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(����)
	D3DXVECTOR3 posOld;		//�ʒu
	D3DXVECTOR3 pos2;		//�ʒu�i������j
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	int nType;				//���
	int nLife;				//�̗�
	ENEMYSTATE state;		//���
	float fWidth;			//��
	float fHeight;			//����
	float g_fLengthEnemy;	//�Ίp���̒���
	float g_fAngleEnemy;	//�Ίp���̊p�x
	float fCurve;			//�p�x
	float fBossPos;			//�{�X�̍~������
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nCounterAnimEnemy;	//�A�j���[�V�����J�E���^�[
	int nPatternAnimEnemy;	//�p�^�[��No.
	int nCounterMove;		//�G�̈ړ��J�E���^�[
	int nCounterBulletTime;	//�G���ł���
	bool bUse;				//�g�p���Ă��邩�ǂ���
	bool bJump;				//�W�����v���g�p���Ă��邩
	Block *pBlock;			//�u���b�N�̏��
} Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int nDamage);
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);
Enemy *GetEnemy(void);
int GetNumEnemy(void);
void SubNumEnemy(void);

#endif
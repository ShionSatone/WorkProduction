//==============================================================
//
//DirectX[player.h]
//Author:����������
//
//==============================================================
#ifndef _PLAYER_H_				//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
#include"block.h"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,			//�o�����(�_��)
	PLAYERSTATE_NORMAL,				//�ʏ���
	PLAYERSTATE_SHADOW,				//�e���
	PLAYERSTATE_DAMAGE,				//�_���[�W���
	PLAYERSTATE_WAIT,				//�o���҂����(�\���Ȃ�)
	PLAYERSTATE_DEATH,				//���S���
	PLAYERSTATE_MAX
} PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 move;		//�ړ���
	PLAYERSTATE state;		//���
	int nLife;				//�̗�
	int nRemain;			//�c�@
	int nCounterDirect;		//�A�j���[�V�����̕���
	int nJudgeDirection;	//��ʊO�ɏo�����̔���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nCounterAppear;		//�_�ł̎���
	int nCounterRevival;	//�v���C���[��������
	float fWidth;			//��
	float fHeight;			//����
	bool bJump;				//�W�����v���Ă��邩
	bool bDisp;				//�v���C���[���g�p���Ă��邩
	Block *pBlock;			//�u���b�N�̏��
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage, int nType);
void CollisionPlayer(void);
Player *GetPlayer(void);

#endif

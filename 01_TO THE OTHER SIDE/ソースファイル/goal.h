//==============================================================
//
//DirectX[goal.h]
//Author:����������
//
//==============================================================
#ifndef _GOAL_H_				//���̃}�N����`������Ă��Ȃ�������
#define _GOAL_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�u���b�N�̃e�N�X�`��
typedef enum
{
	GOALTYPE_GROUND = 0,		//�n��
	GOALTYPE_WALL,				//��
	GOALTYPE_GOAL,			//1�}�X�u���b�N
	GOALTYPE_MAX
} GoalTYPE;

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
	int nCounterGoal;		//�u���b�N�̓����̃J�E���^�[
	bool bUse;				//�g�p���Ă��邩�ǂ���
	bool bShadowUse;		//�������̔���
} Goal;

//�v���g�^�C�v�錾
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos, int nType);
bool CollisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Goal **pGoal);
Goal *GetGoal(void);

#endif
//==============================================================
//
//DirectX[item.h]
//Author:����������
//
//==============================================================
#ifndef _ITEM_H_				//���̃}�N����`������Ă��Ȃ�������
#define _ITEM_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//�u���b�N�̃e�N�X�`��
typedef enum
{
	ITEMTYPE_GROUND = 0,		//�n��
	ITEMTYPE_WALL,				//��
	ITEMTYPE_Item,			//1�}�X�u���b�N
	ITEMTYPE_MAX
} ITEMTYPE;

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
	int nCounterItem;		//�u���b�N�̓����̃J�E���^�[
	bool bUse;				//�g�p���Ă��邩�ǂ���
	bool bShadowUse;		//�������̔���
} Item;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType);
void HitItem(void);
Item *GetItem(void);
int GetNumItem(void);

#endif
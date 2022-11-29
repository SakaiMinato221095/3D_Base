
//=======================
//=
//= �r���{�[�h�̃w�b�^�[[Billboard.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _BILLBOARD_H_	//���̃}�N������`����Ȃ�������
#define _BILLBOARD_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//�r���{�[�h�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nShadowNum;			//�e�̔ԍ�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Billboard;

//�v���g�^�C�v�錾
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos);

#endif 
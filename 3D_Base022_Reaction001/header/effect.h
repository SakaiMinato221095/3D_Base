
//=======================
//=
//= �G�t�F�N�g�̃w�b�^�[[Effect.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _EFFECT_H_	//���̃}�N������`����Ȃ�������
#define _EFFECT_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

#define EFFECT_SIZE_X	(10.0f)		//�G�t�F�N�g�̑傫��
#define EFFECT_SIZE_Y	(10.0f)		//�G�t�F�N�g�̑傫��

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	float fRadins;			//�傫��
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nLife;				//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);
void ResetEffect(int nCutEffect);
void ClearEffect(void);
Effect *GetEffect(void);

#endif 
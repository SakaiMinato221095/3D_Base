
//=======================
//=
//= �I�u�W�F�N�g���f���̃w�b�^�[[model_object.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _MODEL_ENEMY_H_	//���̃}�N������`����Ȃ�������
#define _MODEL_ENEMY_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//�I�u�W�F�N�g���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 size;		//�傫��
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
}ModelEnemy;

//�v���g�^�C�v�錾
void InitModelEnemy(void);
void UninitModelEnemy(void);
void UpdateModelEnemy(void);
void DrawModelEnemy(void);
bool CollisionModelEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelEnemy **pModelEnemy);

#endif 

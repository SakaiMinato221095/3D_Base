
//=======================
//=
//= �e�̃w�b�^�[[Bullet.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _BULLET_H_	//���̃}�N������`����Ȃ�������
#define _BULLET_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

#define BULLET_MAX		(128)		//�e�̍ő吔

//�e�̎��
typedef enum
{
	BULLET_TYPE_PLAYER = 0,		//�v���C���[�̒e
	BULLET_TYPE_ENEMY = 0,		//�G�̒e
	BULLET_TYPE_MAX,			//�e�̎�ނ̍ő吔
}BulletType;

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 size;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	int nLife;					//����
	int nShadowNum;				//�e�̔ԍ�
	bool bUse;					//�g�p���Ă��邩�ǂ���
	Wall *pWall;				//�Ώۂ̕ǂ̃|�C���^
	ModelObject *pModelObject;	//�Ώۂ̃I�u�W�F�N�g���f���̃|�C���^
	ModelEnemy *pModelEnemy;	//�Ώۂ̃G�l�~�[���f���̃|�C���^
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nLife, BulletType type);
void ResetBullet(int nCutBullet);
void ClearBullet(void);
Bullet *GetBullet(void);

#endif 
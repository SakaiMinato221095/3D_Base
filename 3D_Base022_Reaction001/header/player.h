//=======================
//=
//= �v���C���[�̃w�b�^�[[player.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _PLAYER_H_	//���̃}�N������`����Ȃ�������
#define _PLAYER_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	D3DXVECTOR3 rotDiff;		//�p�x�̍���
	int nShadowNum = -1;		//�e�̔ԍ�
	Wall *pWall;				//�Ώۂ̕ǂ̃|�C���^
	ModelObject *pModelObject;	//�Ώۂ̃I�u�W�F�N�g���f���̃|�C���^
	ModelEnemy *pModelEnemy;	//�Ώۂ̃G�l�~�[���f���̃|�C���^
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif 
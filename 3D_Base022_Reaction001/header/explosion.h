
//=======================
//=
//= DirectX�̒e�̔����̃w�b�^�[[explosion.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _EXPLOSION_H_	//���̃}�N������`����Ȃ�������
#define _EXPLOSION_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"



//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void ReSetExplosion(int nCutExplosion);

#endif 
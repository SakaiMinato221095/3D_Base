
//=======================
//=
//= �p�[�e�B�N���̃w�b�^�[[particle.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _PARTICLE_H_	//���̃}�N������`����Ȃ�������
#define _PARTICLE_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//�}�N��
#define PARTICLE_HIT_NUMBER		(32)	//�q�b�g���̃p�[�e�B�N����

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nEffectNumber);

#endif 



//=======================
//=
//= �e�̃w�b�^�[[shadow.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _SHADOW_H_	//���̃}�N������`����Ȃ�������
#define _SHADOW_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void ShadowPositionShadow(int nldxShadow,D3DXVECTOR3 pos);
void ReSetShadow(int nldxShadow);


#endif 

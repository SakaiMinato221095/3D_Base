
//=======================
//=
//= �t�B�[���h�̃w�b�^�[[polygon.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _FIELD_H_	//���̃}�N������`����Ȃ�������
#define _FIELD_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#define FIELD_SIZE_X	(500.0f)	//�t�B�[���h�̑傫���iX���j
#define FIELD_SIZE_Y	(0.0f)		//�t�B�[���h�̑傫���iY���j
#define FIELD_SIZE_Z	(500.0f)	//�t�B�[���h�̑傫���iZ���j

//�v���g�^�C�v�錾
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif 

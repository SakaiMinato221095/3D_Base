
//=======================
//=
//= �|���S���̃w�b�^�[[polygon.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _POLYGON_H_	//���̃}�N������`����Ȃ�������
#define _POLYGON_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#define POLYGON_SIZE_X	(500.0f)	//�|���S���̑傫���iX���j
#define POLYGON_SIZE_Y	(0.0f)		//�|���S���̑傫���iY���j
#define POLYGON_SIZE_Z	(500.0f)	//�|���S���̑傫���iZ���j

//�v���g�^�C�v�錾
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

#endif 

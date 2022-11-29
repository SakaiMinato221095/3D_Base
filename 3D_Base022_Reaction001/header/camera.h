
//=======================
//=
//= �J�����̃w�b�^�[[camera.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _CAMERA_H_	//���̃}�N������`����Ȃ�������
#define _CAMERA_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//�J�������[�h�I���̗񋓌^
typedef enum
{
	CAMERA_MODE_NORMAL = 0,
	CAMERA_MODE_FOLLOWING,
}CameraMode;

//�J�����̍\����
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXMATRIX mtxProjectien;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	float fLength;				//����
	CameraMode mode;			//���[�h
}Camera;



//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif 
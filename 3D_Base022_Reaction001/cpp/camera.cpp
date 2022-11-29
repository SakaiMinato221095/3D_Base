
//=======================
//=
//= �f�o�b�N�̏���[debug.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "camera.h"

#include "input.h"

#include "player.h"

//�}�N��
#define CAMERA_TEX			(1)			//�J�����̃e�N�X�`���̐�

#define CAMERA_V_DECREASE	(0.3f)		//���_�̌���
#define CAMERA_R_DECREASE	(0.3f)		//�����_�̌���
#define CAMERA_ROT_DECREASE	(0.3f)		//�����̌���

#define CAMERA_PLAYER_RANGE	(20.0f)		//�J�����ƃv���C���[�̋���
#define CAMERA_RESET_TIME	(120)		//�J�����̃��Z�b�g���鎞��

//�O���[�o���ϐ�
Camera g_camera;						//�J�����̏��
int nResetTime;							//�v���C���[�̑���̂Ȃ�����

//====================================
//= �J�����̏���������
//=====================================
void InitCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//�O���[�o���ϐ��̏�����
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 250.0f, -100.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.fLength = 300.0f;

		g_camera.mode = CAMERA_MODE_FOLLOWING;

		nResetTime = 0;

		//�J�����̏����擾
		Player *pPlayer = GetPlayer();

		//�����_�ƃv���C���[�̋���
		D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(sinf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE, 0.0f, cosf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE);

		//���_�̐ݒ�
		g_camera.posV.x = pPlayer->pos.x + (sinf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.x;
		g_camera.posV.z = pPlayer->pos.z + (cosf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.z;

		//�����_�̐ݒ�
		g_camera.posR.x = pPlayer->pos.x + cameraPlayer.x;
		g_camera.posR.z = pPlayer->pos.z + cameraPlayer.z;
	}
}

//=====================================
//= �J�����̏I������
//=====================================
void UninitCamera(void)
{

}

//=====================================
//= �J�����̍X�V����
//=====================================
void UpdateCamera(void)
{
	switch (g_camera.mode)
	{
		//�ʏ�J����
	case CAMERA_MODE_NORMAL:
		//�ړ�
		if (GetKeyboardPress(DIK_UP) == true)
		{//�E�̈ړ�[����L�[�������ꂽ�Ƃ�]

			g_camera.posV.z += 2.0f;
			g_camera.posR.z += 2.0f;

		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//�E�̈ړ�[�����L�[�������ꂽ�Ƃ�]

			g_camera.posV.z -= 2.0f;
			g_camera.posR.z -= 2.0f;

		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{//���̈ړ�[�����L�[�������ꂽ�Ƃ�]
			g_camera.posV.x -= 2.0f;
			g_camera.posR.x -= 2.0f;

		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{//�E�̈ړ�[�E���L�[�������ꂽ�Ƃ�]

			g_camera.posV.x += 2.0f;
			g_camera.posR.x += 2.0f;

		}

		//�����_�̉�]
		if (GetKeyboardPress(DIK_Q) == true)
		{//[Q�L�[�������ꂽ�Ƃ�]

			g_camera.rot.y -= 0.05f;

			//�����_�̈ʒu���X�V
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
		}
		if (GetKeyboardPress(DIK_E) == true)
		{//[E�L�[�������ꂽ�Ƃ�]

			g_camera.rot.y += 0.05f;

			//�����_�̈ʒu���X�V
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

		}

		//���_�̉�]
		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rot.y -= 0.05f;

			//���_�̈ʒu���X�V
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;
		}
		if (GetKeyboardPress(DIK_C) == true)
		{//[E�L�[�������ꂽ�Ƃ�]
			g_camera.rot.y += 0.05f;

			//���_�̈ʒu���X�V
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;
		}

		if (GetKeyboardPress(DIK_RETURN) == true)
		{//[�G���^�[�L�[�������ꂽ�Ƃ�]
			g_camera.posV = D3DXVECTOR3(0.0f, 50.0f, -200.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
			g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�����_�̈ʒu���X�V
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;
		}
		break;
		//�Ǐ]�J����
	case CAMERA_MODE_FOLLOWING:

		//�J�����̏����擾
		Player *pPlayer = GetPlayer();

		//�����_�ƃv���C���[�̋���
		D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(sinf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE, 0.0f, cosf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE);

		//nResetTime++;

		//���Z�b�g������͂��m�F
		if (GetKeyboardPress(DIK_W) == true ||
			GetKeyboardPress(DIK_S) == true || 
			GetKeyboardPress(DIK_A) == true || 
			GetKeyboardPress(DIK_D) == true ||
			GetKeyboardPress(DIK_Z) == true ||
			GetKeyboardPress(DIK_C) == true)
		{
			//���Ԃ̃��Z�b�g
			nResetTime = 0;
		}

		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rotDest.y += 0.03f;
		}
		if (GetKeyboardPress(DIK_C) == true)
		{//[E�L�[�������ꂽ�Ƃ�]
			g_camera.rotDest.y -= 0.03f;
		}

		if (GetKeyboardPress(DIK_RETURN) == true)
		{//[�G���^�[�L�[�������ꂽ�Ƃ�]
			g_camera.posV = D3DXVECTOR3(0.0f, 140.0f, -100.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
			g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.fLength = 200.0f;

			g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//���_�̐ݒ�
			g_camera.posV.x = pPlayer->pos.x + (sinf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.x;
			g_camera.posV.z = pPlayer->pos.z + (cosf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.z;

			//�����_�̐ݒ�
			g_camera.posR.x = pPlayer->pos.x + cameraPlayer.x;
			g_camera.posR.z = pPlayer->pos.z + cameraPlayer.z;
		}

		if (nResetTime >= CAMERA_RESET_TIME)
		{
			g_camera.rotDest.y = (pPlayer->rot.y - D3DX_PI);

			//���Ԃ̃��Z�b�g
			nResetTime = 0;
		}

		//�p�x�̏C��
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
			g_camera.rotDest.y = -D3DX_PI + (g_camera.rotDest.y - D3DX_PI);
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
			g_camera.rotDest.y = D3DX_PI + (g_camera.rotDest.y + D3DX_PI);
		}

		//���_�̈ʒu���X�V
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;

		//�ړI�̎��_�̈ʒu
		g_camera.posVDest.x = pPlayer->pos.x + (sinf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.x;
		g_camera.posVDest.z = pPlayer->pos.z + (cosf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.z;

		//�ړI�̒����_�̈ʒu
		g_camera.posRDest.x = pPlayer->pos.x + cameraPlayer.x;
		g_camera.posRDest.z = pPlayer->pos.z + cameraPlayer.z;

		//���_�̕␳
		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_V_DECREASE;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_V_DECREASE;

		//�����_�̕␳
		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_R_DECREASE;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_R_DECREASE;

		//�p�x�̕␳
		g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * CAMERA_ROT_DECREASE;

		break;

	}


}

//=====================================
//= �J�����̐ݒ菈��
//=====================================
void SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�v���W�F�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjectien);

	//�v���W�F�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjectien,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_PROJECTION,
		&g_camera.mtxProjectien);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);
		
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,		//���_
		&g_camera.posR,		//�����_
		&g_camera.vecU);	//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_VIEW,
		&g_camera.mtxView);
}


//=====================================
//= �J�����̎擾����
//=====================================
Camera *GetCamera(void)
{
	return &g_camera;
}

//=======================
//=
//= �v���C���[�̏���[player.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "player.h"

#include "input.h"

#include "camera.h"

#include "shadow.h"

#include "bullet.h"
#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

//�}�N��
#define PLAYER_TEX			(8)			//�v���C���[�̃e�N�X�`���̐�

#define PLAYER_SPEED		(1.0f)		//�v���C���[�̑��x
#define PLAYER_DECREASE		(0.3f)		//�����̒l
#define PLAYER_ROT_DECREASE	(0.1f)		//�����̌����̒l

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshPlayer = NULL;						//���b�V���̏��̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;					//�}�e���A���̃|�C���^
DWORD g_dwNumMatPlayer = 0;								//�}�e���A���̐�
LPDIRECT3DTEXTURE9 g_pTexturePlayer[PLAYER_TEX] = {};	//�e�N�X�`���̃|�C���^

Player g_player;										//�v���C���[�̏��
D3DXMATRIX g_mtxWorldPlayer;							//���[���h�}�g���b�N�X

//====================================
//= �v���C���[�̏���������
//=====================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	//�O���[�o���ϐ��̏�����
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.posOld = g_player.pos;
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.nShadowNum = SetShadow();
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\alien000.x",		//�v���C���[��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,				//�}�e���A���̏��
		NULL,
		&g_dwNumMatPlayer,				//�}�e���A���̐�
		&g_pMeshPlayer);				//���b�V���̏��

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	//�}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatPlayer; nCutMat++)
	{
		if (pMat[nCutMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(pDevice,
				pMat[nCutMat].pTextureFilename,
				&g_pTexturePlayer[nCutMat]);
		}
	}
}

//=====================================
//= �v���C���[�̏I������
//=====================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//=====================================
//= �v���C���[�̍X�V����
//=====================================
void UpdatePlayer(void)
{
	//�J�����̏����擾
	Camera *pCamera = GetCamera();

	//�O��̈ړ��ɑ��
	g_player.posOld = g_player.pos;

	//���͂̏���
	{
		//�ړ�
		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�������ꂽ�Ƃ�
			if (GetKeyboardPress(DIK_A) == true)
			{//����ړ�
			 //�ړ���
				g_player.move.x -= sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//�E��ړ�
			 //�ړ���
				g_player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else
			{
				//�ړ���
				g_player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 1.0f) + pCamera->rot.y;

			}
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�������ꂽ�Ƃ�
			if (GetKeyboardPress(DIK_A) == true)
			{//�����ړ�
			 //�ړ���
				g_player.move.x -= sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//�E���ړ�
			 //�ړ���
				g_player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else
			{
				//�ړ���
				g_player.move.x += sinf((D3DX_PI * 1.0f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 1.0f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.0f) + pCamera->rot.y;
			}
		}

		else if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ�Ƃ�
			if (GetKeyboardPress(DIK_W) == true)
			{//����ړ�
			 //�ړ���
				g_player.move.x -= sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�����ړ�
			 //�ړ���
				g_player.move.x -= sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else
			{//���ړ�
			 //�ړ���
				g_player.move.x -= sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.5f) + pCamera->rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ�Ƃ�
			if (GetKeyboardPress(DIK_W) == true)
			{//�E��ړ�
			 //�ړ���
				g_player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�E���ړ�
			 //�ړ���
				g_player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else
			{
				//�ړ���
				g_player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.5f) + pCamera->rot.y;
			}
		}

		//�v���C���[�̒e�𔭎�
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 20.0f, g_player.pos.z), D3DXVECTOR3(sinf(g_player.rot.y) * -1.0f, 0.0f, cosf(g_player.rot.y) * -1.0f), 240, BULLET_TYPE_PLAYER);
		}

		//�v���C���[�̈ʒu��������
		if (GetKeyboardPress(DIK_RETURN) == true)
		{//[�G���^�[�L�[�������ꂽ�Ƃ�]
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			ClearBullet();
		}
	}

	//�ړ������̍���
	g_player.rotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//�p�x�̏C��
	if (g_player.rotDiff.y > D3DX_PI)
	{
		g_player.rotDiff.y = -D3DX_PI;
	}
	else if (g_player.rotDiff.y < -D3DX_PI)
	{
		g_player.rotDiff.y = D3DX_PI;
	}

	//�ړ������i�p�x�j�̕␳
	g_player.rot.y += g_player.rotDiff.y * 0.15f;

	//�p�x�̏C��
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = -D3DX_PI;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = D3DX_PI;
	}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;

	//�ړ��ʂ��X�V
	g_player.move.x += (0.0f - g_player.move.x) * PLAYER_DECREASE;
	g_player.move.z += (0.0f - g_player.move.z) * PLAYER_DECREASE;

	//�v���C���[�ƕǂ̓����蔻��
	if (CollisionWall       (g_player.pos, D3DXVECTOR3(20.0f, 0.0f, 0.0f), &g_player.pWall) == true ||
		CollisionModelObject(g_player.pos, D3DXVECTOR3(30.0f, 0.0f, 30.0f), &g_player.pModelObject) == true ||
		CollisionModelEnemy(g_player.pos, D3DXVECTOR3(30.0f, 0.0f, 30.0f), &g_player.pModelEnemy) == true)
	{
		g_player.pos = g_player.posOld;
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�̍X�V����
	ShadowPositionShadow(g_player.nShadowNum, g_player.pos);
}

//=====================================
//= �v���C���[�̕`�揈��
//=====================================
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldPlayer);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	//�}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatPlayer; nCutMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		//�e�N�X�`���̐ݒ�i���j
		pDevice->SetTexture(0, g_pTexturePlayer[nCutMat]);

		//�v���C���[�i�p�[�c�j�̕`��
		g_pMeshPlayer->DrawSubset(nCutMat);
	}

	//�ۑ����Ă����}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=====================================
//= �v���C���[�̎擾����
//=====================================
Player *GetPlayer(void)
{
	return &g_player;
}
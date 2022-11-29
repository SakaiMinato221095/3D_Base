
//=======================
//=
//= ���f���G�l�~�[�̏���[model_enemy.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "model_enemy.h"

#include "input.h"

#include "camera.h"

#include "shadow.h"

#include "bullet.h"
#include "wall.h"

//�}�N��
#define MODEL_ENEMY_TEX			(8)								//���f���G�l�~�[�̃e�N�X�`���̐�

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshModelEnemy = NULL;							//���b�V���̏��̃|�C���^
LPD3DXBUFFER g_pBuffMatModelEnemy = NULL;						//�}�e���A���̃|�C���^
DWORD g_dwNumMatModelEnemy = 0;									//�}�e���A���̐�
LPDIRECT3DTEXTURE9 g_pTextureModelEnemy[MODEL_ENEMY_TEX] = {};	//�e�N�X�`���̃|�C���^

ModelEnemy g_modelObject;										//���f���G�l�~�[�̏��
D3DXMATRIX g_mtxWorldModelEnemy;								//���[���h�}�g���b�N�X

//====================================
//= ���f���G�l�~�[�̏���������
//=====================================
void InitModelEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	//�O���[�o���ϐ��̏�����
	{
		g_modelObject.pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		g_modelObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_modelObject.size = D3DXVECTOR3(25.0f, 0.0f, 15.0f);

	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\alien001.x",		//���f���G�l�~�[��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModelEnemy,				//�}�e���A���̏��
		NULL,
		&g_dwNumMatModelEnemy,				//�}�e���A���̐�
		&g_pMeshModelEnemy);				//���b�V���̏��

											//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModelEnemy->GetBufferPointer();

	//�}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelEnemy; nCutMat++)
	{
		if (pMat[nCutMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(pDevice,
				pMat[nCutMat].pTextureFilename,
				&g_pTextureModelEnemy[nCutMat]);
		}
	}
}

//=====================================
//= ���f���G�l�~�[�̏I������
//=====================================
void UninitModelEnemy(void)
{
	//���b�V���̔j��
	if (g_pMeshModelEnemy != NULL)
	{
		g_pMeshModelEnemy->Release();
		g_pMeshModelEnemy = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModelEnemy != NULL)
	{
		g_pBuffMatModelEnemy->Release();
		g_pBuffMatModelEnemy = NULL;
	}
}

//=====================================
//= ���f���G�l�~�[�̍X�V����
//=====================================
void UpdateModelEnemy(void)
{

}

//=====================================
//= ���f���G�l�~�[�̕`�揈��
//=====================================
void DrawModelEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModelEnemy);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_modelObject.rot.y, g_modelObject.rot.x, g_modelObject.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModelEnemy, &g_mtxWorldModelEnemy, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_modelObject.pos.x, g_modelObject.pos.y, g_modelObject.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModelEnemy, &g_mtxWorldModelEnemy, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldModelEnemy);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModelEnemy->GetBufferPointer();

	//�}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelEnemy; nCutMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		//�e�N�X�`���̐ݒ�i���j
		pDevice->SetTexture(0, g_pTextureModelEnemy[nCutMat]);

		//���f���G�l�~�[�i�p�[�c�j�̕`��
		g_pMeshModelEnemy->DrawSubset(nCutMat);
	}

	//�ۑ����Ă����}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=====================================
//= �I�u�W�F�N�g���f���̓����蔻�菈��
//=====================================
bool CollisionModelEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelEnemy **pModelEnemy)
{
	//�ϐ��錾
	bool bCollison = false;	//����̗L

	if (pos.x >= g_modelObject.pos.x - g_modelObject.size.x &&
		pos.x <= g_modelObject.pos.x + g_modelObject.size.x &&
		pos.z >= g_modelObject.pos.z - g_modelObject.size.z &&
		pos.z <= g_modelObject.pos.z + g_modelObject.size.z)
	{
		bCollison = true;

		//�ǂ̃A�h���X����
		if (pModelEnemy != NULL)
		{//�ǂ̃A�h���X������ꏊ������
			*pModelEnemy = &g_modelObject;		//�ǂ̃A�h���X����
		}
	}

	return bCollison;
}
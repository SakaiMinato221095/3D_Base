
//=======================
//=
//= ���f���I�u�W�F�N�g�̏���[model_object.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "model_object.h"

#include "input.h"

#include "camera.h"

#include "shadow.h"

#include "bullet.h"
#include "wall.h"

//�}�N��
#define PLAYER_TEX			(8)								//���f���I�u�W�F�N�g�̃e�N�X�`���̐�

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshModelObject = NULL;						//���b�V���̏��̃|�C���^
LPD3DXBUFFER g_pBuffMatModelObject = NULL;					//�}�e���A���̃|�C���^
DWORD g_dwNumMatModelObject = 0;							//�}�e���A���̐�
LPDIRECT3DTEXTURE9 g_pTextureModelObject[PLAYER_TEX] = {};	//�e�N�X�`���̃|�C���^

ModelObject g_modelObject;									//���f���I�u�W�F�N�g�̏��
D3DXMATRIX g_mtxWorldModelObject;							//���[���h�}�g���b�N�X

//====================================
//= ���f���I�u�W�F�N�g�̏���������
//=====================================
void InitModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	//�O���[�o���ϐ��̏�����
	{
		g_modelObject.pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		g_modelObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_modelObject.size = D3DXVECTOR3(45.0f, 0.0f, 15.0f);

	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\Scarecrow000.x",		//���f���I�u�W�F�N�g��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModelObject,				//�}�e���A���̏��
		NULL,
		&g_dwNumMatModelObject,				//�}�e���A���̐�
		&g_pMeshModelObject);				//���b�V���̏��

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModelObject->GetBufferPointer();

	//�}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelObject; nCutMat++)
	{
		if (pMat[nCutMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile
			(pDevice,
				pMat[nCutMat].pTextureFilename,
				&g_pTextureModelObject[nCutMat]);
		}
	}
}

//=====================================
//= ���f���I�u�W�F�N�g�̏I������
//=====================================
void UninitModelObject(void)
{
	//���b�V���̔j��
	if (g_pMeshModelObject != NULL)
	{
		g_pMeshModelObject->Release();
		g_pMeshModelObject = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModelObject != NULL)
	{
		g_pBuffMatModelObject->Release();
		g_pBuffMatModelObject = NULL;
	}
}

//=====================================
//= ���f���I�u�W�F�N�g�̍X�V����
//=====================================
void UpdateModelObject(void)
{

}

//=====================================
//= ���f���I�u�W�F�N�g�̕`�揈��
//=====================================
void DrawModelObject(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModelObject);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_modelObject.rot.y, g_modelObject.rot.x, g_modelObject.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModelObject, &g_mtxWorldModelObject, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_modelObject.pos.x, g_modelObject.pos.y, g_modelObject.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModelObject, &g_mtxWorldModelObject, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldModelObject);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModelObject->GetBufferPointer();

	//�}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelObject; nCutMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		//�e�N�X�`���̐ݒ�i���j
		pDevice->SetTexture(0, g_pTextureModelObject[nCutMat]);

		//���f���I�u�W�F�N�g�i�p�[�c�j�̕`��
		g_pMeshModelObject->DrawSubset(nCutMat);
	}

	//�ۑ����Ă����}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=====================================
//= �I�u�W�F�N�g���f���̓����蔻�菈��
//=====================================
bool CollisionModelObject(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelObject **pModelObject)
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
		if (pModelObject != NULL)
		{//�ǂ̃A�h���X������ꏊ������
			*pModelObject = &g_modelObject;		//�ǂ̃A�h���X����
		}
	}

	return bCollison;
}
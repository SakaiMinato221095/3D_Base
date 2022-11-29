
//=======================
//=
//= ���b�V���t�B�[���h�̏���[meshfield.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "meshfield.h"

//�}�N��
#define MESH_FIELD_TEX		(1)			//���b�V���t�B�[���h�̃e�N�X�`���̐�

#define MESH_FIELD_W		(8 + 1)		//���b�V���t�B�[���h�̉���
#define MESH_FIELD_H		(8 + 1)		//���b�V���t�B�[���h�̏c��

#define MESH_FIELD_POS_X	(0.0f)		//�����̊J�n�ʒu
#define MESH_FIELD_POS_Z	(0.0f)		//�����̊J�n�ʒu

//���b�V���t�B�[���h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
}MeshField;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;				//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField[MESH_FIELD_TEX] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshField = NULL;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshField g_meshField;											//���b�V���t�B�[���h�̍\����

//====================================
//= ���b�V���t�B�[���h�̏���������
//=====================================
void InitMeshField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutMeshFieldW, nCutMeshFieldH;

	//�O���[�o���ϐ��̏�����
	{
		g_meshField.pos = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
		g_meshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshField[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (MESH_FIELD_W * MESH_FIELD_H),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W
	for (nCutMeshFieldH = 0; nCutMeshFieldH < MESH_FIELD_H; nCutMeshFieldH++)
	{
		for (nCutMeshFieldW = 0; nCutMeshFieldW < MESH_FIELD_W; nCutMeshFieldW++)
		{
			//���_���W�̐ݒ�
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].pos = D3DXVECTOR3((MESH_FIELD_POS_X + (100.0f * nCutMeshFieldW)), 0.0f, (MESH_FIELD_POS_Z - (100.0f * nCutMeshFieldH)));
			//�@���x�N�g���̐ݒ�
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[��ݒ�
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`���̍��W��ݒ�
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].tex = D3DXVECTOR2(1.0f * nCutMeshFieldW, 1.0f * nCutMeshFieldH);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	int nData = ((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2));

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshField,
		NULL);

	//�C���f�b�N�X���̃|�C���^
	WORD *pldx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pldxBuffMeshField->Lock(
		0,
		0,
		(void**)&pldx,
		0);

	//���_�ԍ��f�[�^�̐ݒ�
	for (nCutMeshFieldH = 0; nCutMeshFieldH < MESH_FIELD_H - 1; nCutMeshFieldH++)
	{
		for (nCutMeshFieldW = 0; nCutMeshFieldW < MESH_FIELD_W; nCutMeshFieldW++)
		{
			int nData1 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (nCutMeshFieldW * 2),
				nData2 = (nCutMeshFieldH * MESH_FIELD_W) + (MESH_FIELD_W + nCutMeshFieldW);

			int nData11 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (nCutMeshFieldW * 2) + 1,
				nData22 = (nCutMeshFieldH * MESH_FIELD_W) + (nCutMeshFieldW);

			pldx[(nCutMeshFieldH * (MESH_FIELD_W * 2) + 2) + (nCutMeshFieldW * 2)] = (nCutMeshFieldH * MESH_FIELD_W) + (MESH_FIELD_W + nCutMeshFieldW);
			pldx[(nCutMeshFieldH * (MESH_FIELD_W * 2) + 2) + (nCutMeshFieldW * 2) + 1] = (nCutMeshFieldH * MESH_FIELD_W) + (nCutMeshFieldW);

		}

		if (nCutMeshFieldH > MESH_FIELD_H - 2)
		{
			break;
		}

		int nData111 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2),
			nData221 = ((MESH_FIELD_W) * (nCutMeshFieldH + 1) - 1);

		int nData113 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2) + 1,
			nData223 = (MESH_FIELD_W) * (nCutMeshFieldH + 2);

		pldx[(nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2)] = ((MESH_FIELD_W) * (nCutMeshFieldH + 1) - 1);
		pldx[(nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2) + 1] = (MESH_FIELD_W) * (nCutMeshFieldH + 2);


	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pldxBuffMeshField->Unlock();
}

//=====================================
//= ���b�V���t�B�[���h�̏I������
//=====================================
void UninitMeshField(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < MESH_FIELD_TEX; nCount++)
	{
		if (g_pTextureMeshField[nCount] != NULL)
		{
			g_pTextureMeshField[nCount]->Release();
			g_pTextureMeshField[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pldxBuffMeshField != NULL)
	{
		g_pldxBuffMeshField->Release();
		g_pldxBuffMeshField = NULL;
	}
}

//=====================================
//= ���b�V���t�B�[���h�̍X�V����
//=====================================
void UpdateMeshField(void)
{

}

//=====================================
//= ���b�V���t�B�[���h�̕`�揈��
//=====================================
void DrawMeshField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshField.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshField.rot.y, g_meshField.rot.x, g_meshField.rot.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_meshField.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffMeshField,
		0,
		sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pldxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		g_pTextureMeshField[0]);

	int nData = ((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2)) - 2;

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//�v���~�e�B�u�̎��
		0,																				//�`�悷��ŏ��̒��_�C���f�b�N�X
		0,
		(MESH_FIELD_W * MESH_FIELD_H),													//�p�ӂ������_��
		0,
		((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2)) - 2);		//�v���~�e�B�u�́i���b�V���t�B�[���h�j��

}



//=======================
//=
//= ���b�V���E�H�[���̏���[wall.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "meshwall.h"

//�}�N��
#define MESH_WALL_TEX	(1)			//���b�V���E�H�[���̃e�N�X�`���̐�

#define MESH_WALL_W		(16 + 1)	//���b�V���E�H�[���̉���
#define MESH_WALL_H		(2 + 1)		//���b�V���E�H�[���̏c��

#define MESH_WALL_POS_X	(0.0f)		//�����̊J�n�ʒu
#define MESH_WALL_POS_Y	(0.0f)		//�����̊J�n�ʒu

//���b�V���E�H�[���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
}MeshWall;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;				//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshWall[MESH_WALL_TEX] = {};		//�e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshWall = NULL;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshWall g_meshWall;											//���b�V���E�H�[���̍\����

//====================================
//= ���b�V���E�H�[���̏���������
//=====================================
void InitMeshWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutMeshWallW, nCutMeshWallH;

	//�O���[�o���ϐ��̏�����
	{
		g_meshWall.pos = D3DXVECTOR3(-500.0f, 100.0f, 500.0f);
		g_meshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshWall[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (MESH_WALL_W * MESH_WALL_H),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W
	for (nCutMeshWallH = 0; nCutMeshWallH < MESH_WALL_H; nCutMeshWallH++)
	{
		for (nCutMeshWallW = 0; nCutMeshWallW < MESH_WALL_W; nCutMeshWallW++)
		{
			//���_���W�̐ݒ�
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].pos = D3DXVECTOR3((MESH_WALL_POS_X + (50.0f * nCutMeshWallW)), (MESH_WALL_POS_Y - (50.0f * nCutMeshWallH)), 0.0f );
			//�@���x�N�g���̐ݒ�
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[��ݒ�
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`���̍��W��ݒ�
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].tex = D3DXVECTOR2(1.0f * nCutMeshWallW, 1.0f * nCutMeshWallH);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	int nData = ((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2));

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshWall,
		NULL);

	//�C���f�b�N�X���̃|�C���^
	WORD *pldx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pldxBuffMeshWall->Lock(
		0,
		0,
		(void**)&pldx,
		0);

	//���_�ԍ��f�[�^�̐ݒ�
	for (nCutMeshWallH = 0; nCutMeshWallH < MESH_WALL_H - 1; nCutMeshWallH++)
	{
		for (nCutMeshWallW = 0; nCutMeshWallW < MESH_WALL_W; nCutMeshWallW++)
		{
			int nData1 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (nCutMeshWallW * 2),
				nData2 = (nCutMeshWallH * MESH_WALL_W) + (MESH_WALL_W + nCutMeshWallW);

			int nData11 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (nCutMeshWallW * 2) + 1,
				nData22 = (nCutMeshWallH * MESH_WALL_W) + (nCutMeshWallW);

			pldx[(nCutMeshWallH * (MESH_WALL_W * 2) + 2) + (nCutMeshWallW * 2)] = (nCutMeshWallH * MESH_WALL_W) + (MESH_WALL_W + nCutMeshWallW);
			pldx[(nCutMeshWallH * (MESH_WALL_W * 2) + 2) + (nCutMeshWallW * 2) + 1] = (nCutMeshWallH * MESH_WALL_W) + (nCutMeshWallW);

		}

		if (nCutMeshWallH > MESH_WALL_H - 2)
		{
			break;
		}

		int nData111 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2),
			nData221 = ((MESH_WALL_W) * (nCutMeshWallH + 1) - 1);

		int nData113 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2) + 1,
			nData223 = (MESH_WALL_W) * (nCutMeshWallH + 2);

		pldx[(nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2)] = ((MESH_WALL_W) * (nCutMeshWallH + 1) - 1);
		pldx[(nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2) + 1] = (MESH_WALL_W) * (nCutMeshWallH + 2);


	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pldxBuffMeshWall->Unlock();
}

//=====================================
//= ���b�V���E�H�[���̏I������
//=====================================
void UninitMeshWall(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < MESH_WALL_TEX; nCount++)
	{
		if (g_pTextureMeshWall[nCount] != NULL)
		{
			g_pTextureMeshWall[nCount]->Release();
			g_pTextureMeshWall[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pldxBuffMeshWall != NULL)
	{
		g_pldxBuffMeshWall->Release();
		g_pldxBuffMeshWall = NULL;
	}
}

//=====================================
//= ���b�V���E�H�[���̍X�V����
//=====================================
void UpdateMeshWall(void)
{

}

//=====================================
//= ���b�V���E�H�[���̕`�揈��
//=====================================
void DrawMeshWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshWall.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshWall.rot.y, g_meshWall.rot.x, g_meshWall.rot.z);
	D3DXMatrixMultiply(&g_meshWall.mtxWorld, &g_meshWall.mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_meshWall.pos.x, g_meshWall.pos.y, g_meshWall.pos.z);
	D3DXMatrixMultiply(&g_meshWall.mtxWorld, &g_meshWall.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_meshWall.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffMeshWall,
		0,
		sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pldxBuffMeshWall);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		g_pTextureMeshWall[0]);

	int nData = ((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2)) - 2;

	//���b�V���E�H�[���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,														//�v���~�e�B�u�̎��
		0,																			//�`�悷��ŏ��̒��_�C���f�b�N�X
		0,
		(MESH_WALL_W * MESH_WALL_H),												//�p�ӂ������_��
		0,
		((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2)) - 2);		//�v���~�e�B�u�́i���b�V���E�H�[���j��

}


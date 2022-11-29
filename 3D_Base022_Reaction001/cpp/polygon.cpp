
//=======================
//=
//= �|���S���̏���[polygon.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "polygon.h"

//�}�N��
#define POLYGON_TEX	(1)	//�|���S���̃e�N�X�`���̐�

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;			//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePolygon[POLYGON_TEX] = {};		//�e�N�X�`���̃|�C���^
D3DXVECTOR3 g_posPolygon;									//�ʒu
D3DXVECTOR3 g_rotPolygon;									//����
D3DXMATRIX g_mtxWorldPolygon;								//���[���h�}�g���b�N�X

//====================================
//= �|���S���̏���������
//=====================================
void InitPolygon(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�O���[�o���ϐ��̏�����
	{
		g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTexturePolygon[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(
		0,
		0,
		(void**)&pVtx,
		0);


	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-POLYGON_SIZE_X, 0.0f,  POLYGON_SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3( POLYGON_SIZE_X, 0.0f,  POLYGON_SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-POLYGON_SIZE_X, 0.0f, -POLYGON_SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3( POLYGON_SIZE_X, 0.0f, -POLYGON_SIZE_Z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[��ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//=====================================
//= �|���S���̏I������
//=====================================
void UninitPolygon(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < POLYGON_TEX; nCount++)
	{
		if (g_pTexturePolygon[nCount] != NULL)
		{
			g_pTexturePolygon[nCount]->Release();
			g_pTexturePolygon[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=====================================
//= �|���S���̍X�V����
//=====================================
void UpdatePolygon(void)
{

}

//=====================================
//= �|���S���̕`�揈��
//=====================================
void DrawPolygon(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon, &mtxRot);
					   
	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldPolygon);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffPolygon,
		0,
		sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		g_pTexturePolygon[0]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);						//�v���~�e�B�u�́i�|���S���j��

}


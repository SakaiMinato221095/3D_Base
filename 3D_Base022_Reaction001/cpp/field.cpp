
//=======================
//=
//= �t�B�[���h�̏���[field.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "field.h"

//�}�N��
#define FIELD_TEX	(1)									//�t�B�[���h�̃e�N�X�`���̐�

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;			//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureField[FIELD_TEX] = {};		//�e�N�X�`���̃|�C���^
D3DXVECTOR3 g_posField;									//�ʒu
D3DXVECTOR3 g_rotField;									//����
D3DXMATRIX g_mtxWorldField;								//���[���h�}�g���b�N�X

//====================================
//= �t�B�[���h�̏���������
//=====================================
void InitField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�O���[�o���ϐ��̏�����
	{
		g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureField[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffField->Lock(
		0,
		0,
		(void**)&pVtx,
		0);


	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE_X, 0.0f, FIELD_SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(FIELD_SIZE_X, 0.0f, FIELD_SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-FIELD_SIZE_X, 0.0f, -FIELD_SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(FIELD_SIZE_X, 0.0f, -FIELD_SIZE_Z);

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
	g_pVtxBuffField->Unlock();
}

//=====================================
//= �t�B�[���h�̏I������
//=====================================
void UninitField(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < FIELD_TEX; nCount++)
	{
		if (g_pTextureField[nCount] != NULL)
		{
			g_pTextureField[nCount]->Release();
			g_pTextureField[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=====================================
//= �t�B�[���h�̍X�V����
//=====================================
void UpdateField(void)
{

}

//=====================================
//= �t�B�[���h�̕`�揈��
//=====================================
void DrawField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffField,
		0,
		sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		g_pTextureField[0]);

	//�t�B�[���h�̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);						//�v���~�e�B�u�́i�t�B�[���h�j��

}


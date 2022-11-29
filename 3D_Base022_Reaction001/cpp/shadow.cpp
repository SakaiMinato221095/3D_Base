
//=======================
//=
//= �e�̏���[shadow.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "shadow.h"

//�}�N��
#define SHADOW_TEX		(1)			//�e�̃e�N�X�`���̐�
#define SHADOW_MAX		(128)		//�e�̍ő吔

#define SHADOW_SIZE_X	(15.0f)		//�e�̑傫���iX���j
#define SHADOW_SIZE_Y	(0.0f)		//�e�̑傫���iY���j
#define SHADOW_SIZE_Z	(15.0f)		//�e�̑傫���iZ���j

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Shadow;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow[SHADOW_TEX] = {};	//�e�N�X�`���̃|�C���^
Shadow g_aShadow[SHADOW_MAX];							//�e�̏��

//====================================
//= �e�̏���������
//=====================================
void InitShadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutShadow;

	//�O���[�o���ϐ��̏�����
	for (nCutShadow = 0; nCutShadow < SHADOW_MAX; nCutShadow++)
	{
		g_aShadow[nCutShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCutShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCutShadow].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (SHADOW_MAX * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffShadow->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutShadow = 0; nCutShadow < SHADOW_MAX; nCutShadow++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE_X, 0.0f, SHADOW_SIZE_Z);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE_X, 0.0f, SHADOW_SIZE_Z);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE_X, 0.0f, -SHADOW_SIZE_Z);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE_X, 0.0f, -SHADOW_SIZE_Z);

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

		//�|�C���^�𒸓_�i�S�j���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=====================================
//= �e�̏I������
//=====================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < SHADOW_TEX; nCount++)
	{
		if (g_pTextureShadow[nCount] != NULL)
		{
			g_pTextureShadow[nCount]->Release();
			g_pTextureShadow[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=====================================
//= �e�̍X�V����
//=====================================
void UpdateShadow(void)
{

}

//=====================================
//= �e�̕`�揈��
//=====================================
void DrawShadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	int nCutShadow;

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(
		D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	for (nCutShadow = 0; nCutShadow < SHADOW_MAX; nCutShadow++)
	{
		if (g_aShadow[nCutShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCutShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCutShadow].rot.y, g_aShadow[nCutShadow].rot.x, g_aShadow[nCutShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCutShadow].mtxWorld, &g_aShadow[nCutShadow].mtxWorld, &mtxRot);

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCutShadow].pos.x, g_aShadow[nCutShadow].pos.y, g_aShadow[nCutShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCutShadow].mtxWorld, &g_aShadow[nCutShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aShadow[nCutShadow].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffShadow,
				0,
				sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(
				0,
				g_pTextureShadow[0]);

			//�e�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCutShadow,			//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);						//�v���~�e�B�u�́i�e�j��
		}
	}

	//a�u�����f�B���O�����Ƃɖ߂�
	pDevice->SetRenderState(
		D3DRS_BLENDOP,
		D3DBLENDOP_ADD);
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA);

}

//=====================================
//= �e�̐ݒ菈��
//=====================================
int SetShadow(void)
{
	int nCutShadow = -1;

	for (nCutShadow = 0; nCutShadow < SHADOW_MAX; nCutShadow++)
	{
		if (g_aShadow[nCutShadow].bUse == false)
		{
			g_aShadow[nCutShadow].bUse = true;

			return nCutShadow;
		}
	}

	return -1;
}

//=====================================
//= �e�̏��̏���������
//=====================================
void ReSetShadow(int nldxShadow)
{
	g_aShadow[nldxShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aShadow[nldxShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aShadow[nldxShadow].bUse = false;
}
//=====================================
//= �e�̈ʒu�ݒ菈��
//=====================================
void ShadowPositionShadow(int nldxShadow, D3DXVECTOR3 pos)
{
	if (nldxShadow >= 0)
	{
		g_aShadow[nldxShadow].pos = pos;
	}
	
}
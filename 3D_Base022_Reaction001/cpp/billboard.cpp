
//=======================
//=
//= �r���{�[�h�̏���[bullet.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "billboard.h"

#include "shadow.h"

#include "player.h"

//�}�N��
#define BILLBOARD_MAX		(64)		//�r���{�[�h�̍ő吔
#define BILLBOARD_TEX		(1)			//�e�N�X�`���̐�
#define BILLBOARD_SIZE_X	(30.0f)		//�v���C���[�̃r���{�[�h�̑傫��
#define BILLBOARD_SIZE_Y	(30.0f)		//�v���C���[�̃r���{�[�h�̑傫��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARD_TEX] = {};		//�e�N�X�`���̃|�C���^

Billboard g_aBillboard[BILLBOARD_MAX];							//�r���{�[�h�̏��

//====================================
//= �r���{�[�h�̏���������
//=====================================
void InitBillboard(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutBillboard;

	//�r���{�[�h�̏���������
	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		g_aBillboard[nCutBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCutBillboard].nShadowNum = -1;
		g_aBillboard[nCutBillboard].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\tree000.png",
		&g_pTextureBillboard[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * BILLBOARD_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X, BILLBOARD_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE_X, BILLBOARD_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X, -BILLBOARD_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE_X, -BILLBOARD_SIZE_Y, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=====================================
//= �r���{�[�h�̏I������
//=====================================
void UninitBillboard(void)
{
	for (int nCount = 0; nCount < BILLBOARD_TEX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBillboard[nCount] != NULL)
		{
			g_pTextureBillboard[nCount]->Release();
			g_pTextureBillboard[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=====================================
//= �r���{�[�h�̍X�V����
//=====================================
void UpdateBillboard(void)
{
	//�ϐ��錾
	int nCutBillboard;

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		if (g_aBillboard[nCutBillboard].bUse == true)
		{//�r���{�[�h���g�p����Ă���
			//�e�̍X�V����
			ShadowPositionShadow(g_aBillboard[nCutBillboard].nShadowNum, D3DXVECTOR3(g_aBillboard[nCutBillboard].pos.x, 0.0f, g_aBillboard[nCutBillboard].pos.z));
		}
	}
}

//=====================================
//= �r���{�[�h�̕`�揈��
//=====================================
void DrawBillboard(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView[BILLBOARD_MAX];	//�r���[�}�g���b�N�X�̎擾�p
	int nCutBillboard;

	//Z�e�X�g�𖳌���
	pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_ALWAYS);
	pDevice->SetRenderState(
		D3DRS_ZWRITEENABLE,
		FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(
		D3DRS_ALPHATESTENABLE,
		TRUE);
	pDevice->SetRenderState(
		D3DRS_ALPHAFUNC,
		D3DCMP_GREATER);
	pDevice->SetRenderState(
		D3DRS_ALPHAREF,
		0);

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		if (g_aBillboard[nCutBillboard].bUse == true)
		{//�r���{�[�h���g�p����Ă���

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCutBillboard].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutBillboard]);

			//�|���S�����J�����̈ʒu�Ɍ�����ύX
			D3DXMatrixInverse(
				&g_aBillboard[nCutBillboard].mtxWorld,
				NULL,
				&mtxView[nCutBillboard]);

			g_aBillboard[nCutBillboard].mtxWorld._41 = 0.0f;
			g_aBillboard[nCutBillboard].mtxWorld._42 = 0.0f;
			g_aBillboard[nCutBillboard].mtxWorld._43 = 0.0f;

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCutBillboard].pos.x, g_aBillboard[nCutBillboard].pos.y, g_aBillboard[nCutBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCutBillboard].mtxWorld, &g_aBillboard[nCutBillboard].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aBillboard[nCutBillboard].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffBillboard,
				0,
				sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(
				0,
				g_pTextureBillboard[0]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCutBillboard * 4,			//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);						//�v���~�e�B�u�́i�|���S���j��
		}
	}

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(
		D3DRS_ZWRITEENABLE,
		TRUE);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(
		D3DRS_ALPHATESTENABLE,
		FALSE);

	pDevice->SetRenderState(
		D3DRS_ALPHAFUNC,
		D3DCMP_ALWAYS);

	pDevice->SetRenderState(
		D3DRS_ALPHAREF,
		0);
}

//=====================================
//= �r���{�[�h�̐ݒ菈��
//=====================================
void SetBillboard(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	int nCutBillboard;

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		if (g_aBillboard[nCutBillboard].bUse == false)
		{//�r���{�[�h���Ȃ�
			g_aBillboard[nCutBillboard].bUse = true;

			g_aBillboard[nCutBillboard].pos = pos;
			g_aBillboard[nCutBillboard].nShadowNum = SetShadow();

			break;
		}

	}
}



//=======================
//=
//= �G�t�F�N�g�̏���[bullet.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "effect.h"

#include "player.h"
#include "wall.h"

//�}�N��
#define EFFECT_TEX		(1)			//�e�N�X�`���̐�
#define EFFECT_MAX		(1024)		//�G�t�F�N�g�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_TEX] = {};	//�e�N�X�`���̃|�C���^

Effect g_aEffect[EFFECT_MAX];							//�G�t�F�N�g�̏��

//====================================
//= �G�t�F�N�g�̏���������
//=====================================
void InitEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutEffect;

	//�G�t�F�N�g�̏���������
	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		g_aEffect[nCutEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].nLife = 0;
		g_aEffect[nCutEffect].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\EFFECT\\effect000.jpg",
		&g_pTextureEffect[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * EFFECT_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EFFECT_SIZE_X, -EFFECT_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_SIZE_X, -EFFECT_SIZE_Y, 0.0f);

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
	g_pVtxBuffEffect->Unlock();
}

//=====================================
//= �G�t�F�N�g�̏I������
//=====================================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < EFFECT_TEX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount]->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=====================================
//= �G�t�F�N�g�̍X�V����
//=====================================
void UpdateEffect(void)
{
	int nCutEffect;


	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		if (g_aEffect[nCutEffect].bUse == true)
		{
			//�����x�������Ă���
			g_aEffect[nCutEffect].col.a -= g_aEffect[nCutEffect].col.a / g_aEffect[nCutEffect].nLife;

			//���_�J���[��ݒ�
			pVtx[0].col = g_aEffect[nCutEffect].col;
			pVtx[1].col = g_aEffect[nCutEffect].col;
			pVtx[2].col = g_aEffect[nCutEffect].col;
			pVtx[3].col = g_aEffect[nCutEffect].col;

			//�ړ��ʂ����Z
			g_aEffect[nCutEffect].pos += g_aEffect[nCutEffect].move;

			//�����̃J�E���g�_�E��
			g_aEffect[nCutEffect].nLife--;

			//�������s����
			if (g_aEffect[nCutEffect].nLife < 0)
			{
				ResetEffect(nCutEffect);
			}
		}
		//�|�C���^�𒸓_�i�S�j���i�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=====================================
//= �G�t�F�N�g�̕`�揈��
//=====================================
void DrawEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView[EFFECT_MAX];		//�r���[�}�g���b�N�X�̎擾�p
	int nCutEffect;

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(
		D3DRS_BLENDOP,
		D3DBLENDOP_ADD);
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE);

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
		1);

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		if (g_aEffect[nCutEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

		 //���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCutEffect].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutEffect]);

			//�|���S�����J�����̈ʒu�Ɍ�����ύX
			D3DXMatrixInverse(
				&g_aEffect[nCutEffect].mtxWorld,
				NULL,
				&mtxView[nCutEffect]);

			g_aEffect[nCutEffect].mtxWorld._41 = 0.0f;
			g_aEffect[nCutEffect].mtxWorld._42 = 0.0f;
			g_aEffect[nCutEffect].mtxWorld._43 = 0.0f;

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCutEffect].pos.x, g_aEffect[nCutEffect].pos.y, g_aEffect[nCutEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCutEffect].mtxWorld, &g_aEffect[nCutEffect].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aEffect[nCutEffect].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffEffect,
				0,
				sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(
				0,
				g_pTextureEffect[0]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCutEffect * 4,			//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);						//�v���~�e�B�u�́i�|���S���j��
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
		1);
}

//=====================================
//= �G�t�F�N�g�̐ݒ菈��
//=====================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	//�ϐ��錾
	int nCutEffect;

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		if (g_aEffect[nCutEffect].bUse == false)
		{//�G�t�F�N�g���Ȃ�
			g_aEffect[nCutEffect].bUse = true;

			g_aEffect[nCutEffect].pos = pos;
			g_aEffect[nCutEffect].move = move;
			g_aEffect[nCutEffect].nLife = nLife;
			g_aEffect[nCutEffect].col = col;

			break;
		}

	}
}
//=====================================
//= �G�t�F�N�g�̏���������
//=====================================
void ResetEffect(int nCutEffect)
{
	g_aEffect[nCutEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect[nCutEffect].nLife = 0;
	g_aEffect[nCutEffect].bUse = false;
}

//=====================================
//= �G�t�F�N�g��S����
//=====================================
void ClearEffect(void)
{
	for (int nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		g_aEffect[nCutEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].nLife = 0;
		g_aEffect[nCutEffect].bUse = false;
	}
}
//=====================================
//= �G�t�F�N�g�̎擾����
//=====================================
Effect *GetEffect(void)
{
	return &g_aEffect[0];
}
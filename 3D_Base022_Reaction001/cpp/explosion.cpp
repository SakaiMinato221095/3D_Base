
//=======================
//=
//= �����̏���[explosion.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "explosion.h"

//�}�N��
#define EXPLOSION_TEX		(1)			//�e�N�X�`���̐�
#define EXPLOSION_MAX		(128)		//�����̍ő吔

#define EXPLOSION_SIZE_X	(20.0f)		//�����̑傫���iX�j
#define EXPLOSION_SIZE_Y	(20.0f)		//�����̑傫���iY�j

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;				//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureExplosion[EXPLOSION_TEX] = {};		//�e�N�X�`���̃|�C���^

//�����̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nAnimaCut;			//�A�j���[�V�����̐i�߂邽�߂̃J�E���g
	int nAnimaPatternCut;	//�A�j���[�V�����̌��݂̐�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Explosion;

Explosion g_aExplosion[EXPLOSION_MAX];	//�����̏��


//====================================
//= �����̏���������
//=====================================
void InitExplosion(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutExplosion;

	//�����̏���������
	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		g_aExplosion[nCutExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCutExplosion].bUse = false;
		g_aExplosion[nCutExplosion].nAnimaCut = 0;
		g_aExplosion[nCutExplosion].nAnimaPatternCut = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * EXPLOSION_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_SIZE_X, -EXPLOSION_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EXPLOSION_SIZE_X, -EXPLOSION_SIZE_Y, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		//�|�C���^�𒸓_�i�S�j���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=====================================
//= �����̏I������
//=====================================
void UninitExplosion(void)
{
	for (int nCount = 0; nCount < EXPLOSION_TEX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureExplosion[nCount] != NULL)
		{
			g_pTextureExplosion[nCount]->Release();
			g_pTextureExplosion[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=====================================
//= �����̍X�V����
//=====================================
void UpdateExplosion(void)
{
	//�ϐ��錾
	int nCutExplosion;

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		if (g_aExplosion[nCutExplosion].bUse == true)
		{
			//�A�j���[�V�����̏���
			g_aExplosion[nCutExplosion].nAnimaCut++;

			if (g_aExplosion[nCutExplosion].nAnimaCut >= 10)
			{
				g_aExplosion[nCutExplosion].nAnimaCut = 0;
				g_aExplosion[nCutExplosion].nAnimaPatternCut++;
				if (g_aExplosion[nCutExplosion].nAnimaPatternCut >= 9)
				{
					ReSetExplosion(nCutExplosion);
				}
			}

			//�e�N�X�`���̍��W��ݒ�
			pVtx[0].tex = D3DXVECTOR2((0.125f *  g_aExplosion[nCutExplosion].nAnimaPatternCut), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(((0.125f * g_aExplosion[nCutExplosion].nAnimaPatternCut) + 0.125f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((0.125f *  g_aExplosion[nCutExplosion].nAnimaPatternCut), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(((0.125f * g_aExplosion[nCutExplosion].nAnimaPatternCut) + 0.125f), 1.0f);
		}


		//�|�C���^�𒸓_�i�S�j���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=====================================
//= �����̕`�揈��
//=====================================
void DrawExplosion(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView[EXPLOSION_MAX];	//�r���[�}�g���b�N�X�̎擾�p
	int nCutExplosion;

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

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		if (g_aExplosion[nCutExplosion].bUse == true)
		{//�������g�p����Ă���

		 //���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aExplosion[nCutExplosion].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutExplosion]);

			//�|���S�����J�����̈ʒu�Ɍ�����ύX
			D3DXMatrixInverse(
				&g_aExplosion[nCutExplosion].mtxWorld,
				NULL,
				&mtxView[nCutExplosion]);

			g_aExplosion[nCutExplosion].mtxWorld._41 = 0.0f;
			g_aExplosion[nCutExplosion].mtxWorld._42 = 0.0f;
			g_aExplosion[nCutExplosion].mtxWorld._43 = 0.0f;

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCutExplosion].pos.x, g_aExplosion[nCutExplosion].pos.y, g_aExplosion[nCutExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCutExplosion].mtxWorld, &g_aExplosion[nCutExplosion].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aExplosion[nCutExplosion].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffExplosion,
				0,
				sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(
				0,
				g_pTextureExplosion[0]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCutExplosion * 4,			//�`�悷��ŏ��̒��_�C���f�b�N�X
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
//= �����̐ݒ菈��
//=====================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	int nCutExplosion;

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		if (g_aExplosion[nCutExplosion].bUse == false)
		{//�������Ȃ�
			g_aExplosion[nCutExplosion].bUse = true;

			g_aExplosion[nCutExplosion].pos = pos;

			break;
		}

	}
}

//=====================================
//= �����̏�񏉊�������
//=====================================
void ReSetExplosion(int nCutExplosion)
{
	g_aExplosion[nCutExplosion].bUse = false;
	g_aExplosion[nCutExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion[nCutExplosion].nAnimaCut = 0;
	g_aExplosion[nCutExplosion].nAnimaPatternCut = 0;
	
}
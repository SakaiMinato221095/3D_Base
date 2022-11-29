
//=======================
//=
//= �e�̏���[bullet.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "bullet.h"

#include "shadow.h"

#include "player.h"

#include "effect.h"
#include "Particle.h"

#include "explosion.h"

#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

//�}�N��
#define BULLET_TEX		(1)			//�e�N�X�`���̐�
#define BULLET_SIZE_X	(10.0f)		//�v���C���[�̒e�̑傫��
#define BULLET_SIZE_Y	(10.0f)		//�v���C���[�̒e�̑傫��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLET_TEX] = {};	//�e�N�X�`���̃|�C���^

Bullet g_aBullet[BULLET_MAX];							//�e�̏��

//====================================
//= �e�̏���������
//=====================================
void InitBullet(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutBullet;

	//�e�̏���������
	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		g_aBullet[nCutBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].posOld = g_aBullet[nCutBullet].pos;
		g_aBullet[nCutBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].nLife = 0;
		g_aBullet[nCutBullet].nShadowNum = -1;
		g_aBullet[nCutBullet].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * BULLET_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE_X,  BULLET_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( BULLET_SIZE_X,  BULLET_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE_X, -BULLET_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( BULLET_SIZE_X, -BULLET_SIZE_Y, 0.0f);
		
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
	g_pVtxBuffBullet->Unlock();
}

//=====================================
//= �e�̏I������
//=====================================
void UninitBullet(void)
{
	for (int nCount = 0; nCount < BULLET_TEX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCount] != NULL)
		{
			g_pTextureBullet[nCount]->Release();
			g_pTextureBullet[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=====================================
//= �e�̍X�V����
//=====================================
void UpdateBullet(void)
{
	int nCutBullet;

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{
			//�O��̈ʒu�Ɍ��݂̈ʒu����
			g_aBullet[nCutBullet].posOld = g_aBullet[nCutBullet].pos;

			//�ʒu���X�V
			g_aBullet[nCutBullet].pos += g_aBullet[nCutBullet].move;

			//�G�t�F�N�g�̐ݒ菈��
			SetEffect(g_aBullet[nCutBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.5f),30);

			//�e�̍X�V����
			ShadowPositionShadow(g_aBullet[nCutBullet].nShadowNum, D3DXVECTOR3(g_aBullet[nCutBullet].pos.x, 0.0f, g_aBullet[nCutBullet].pos.z));

			//�����̃J�E���g�_�E��
			g_aBullet[nCutBullet].nLife--;

			//�������s����
			if (g_aBullet[nCutBullet].nLife < 0)
			{
	 			ResetBullet(nCutBullet);
				break;
			}

			//�ǂƃ��f���Ƃ̓����蔻��
			if (CollisionWall(g_aBullet[nCutBullet].pos, g_aBullet[nCutBullet].size,&g_aBullet[nCutBullet].pWall) == true ||
				CollisionModelObject(g_aBullet[nCutBullet].pos, g_aBullet[nCutBullet].size, &g_aBullet[nCutBullet].pModelObject) == true ||
				CollisionModelEnemy(g_aBullet[nCutBullet].pos, g_aBullet[nCutBullet].size, &g_aBullet[nCutBullet].pModelEnemy) == true)
			{
				SetExplosion(g_aBullet[nCutBullet].pos);
				ResetBullet(nCutBullet);
			}
		}

	}
}

//=====================================
//= �e�̕`�揈��
//=====================================
void DrawBullet(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView[BULLET_MAX];		//�r���[�}�g���b�N�X�̎擾�p
	int nCutBullet;

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

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{//�e���g�p����Ă���

		 //���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCutBullet].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutBullet]);

			//�|���S�����J�����̈ʒu�Ɍ�����ύX
			D3DXMatrixInverse(
				&g_aBullet[nCutBullet].mtxWorld,
				NULL,
				&mtxView[nCutBullet]);

			g_aBullet[nCutBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCutBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCutBullet].mtxWorld._43 = 0.0f;

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCutBullet].pos.x, g_aBullet[nCutBullet].pos.y, g_aBullet[nCutBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCutBullet].mtxWorld, &g_aBullet[nCutBullet].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aBullet[nCutBullet].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffBullet,
				0,
				sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(
				0,
				g_pTextureBullet[0]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCutBullet * 4,			//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);						//�v���~�e�B�u�́i�|���S���j��
		}
	}

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
//= �e�̐ݒ菈��
//=====================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BulletType type)
{
	//�ϐ��錾
	int nCutBullet;

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == false)
		{//�e���Ȃ�
			g_aBullet[nCutBullet].bUse = true;

			g_aBullet[nCutBullet].pos = pos;
			g_aBullet[nCutBullet].move = move;
			g_aBullet[nCutBullet].nLife = nLife;
			g_aBullet[nCutBullet].nShadowNum = SetShadow();

			break;
		}

	}
}
//=====================================
//= �e�̏���������
//=====================================
void ResetBullet(int nCutBullet)
{
	g_aBullet[nCutBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBullet[nCutBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBullet[nCutBullet].nLife = 0;
	ReSetShadow(g_aBullet[nCutBullet].nShadowNum);
	g_aBullet[nCutBullet].nShadowNum = -1;
	g_aBullet[nCutBullet].bUse = false;
}

//=====================================
//= �e��S����
//=====================================
void ClearBullet(void)
{
	for (int nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		g_aBullet[nCutBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].nLife = 0;
		g_aBullet[nCutBullet].bUse = false;
	}
}
//=====================================
//= �e�̎擾����
//=====================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}
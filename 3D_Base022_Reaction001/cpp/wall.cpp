
//=======================
//=
//= �ǂ̏���[wall.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "wall.h"

#include "polygon.h"
#include "bullet.h"
#include "explosion.h"
#include "Particle.h"

//�}�N��
#define WALL_TEX	(1)				//�ǂ̃e�N�X�`���̐�
#define WALL_MAX	(4)				//�ǂ̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall[WALL_TEX] = {};		//�e�N�X�`���̃|�C���^
Wall g_aWall[WALL_MAX];									//�ǂ̏��

//====================================
//= �ǂ̏���������
//=====================================
void InitWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCutWall;

	//�O���[�o���ϐ��̏�����
	for (nCutWall = 0;  nCutWall < WALL_MAX; nCutWall++)
	{
			g_aWall[nCutWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aWall[nCutWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aWall[nCutWall].size = D3DXVECTOR3(WALL_SIZE_X, WALL_SIZE_Y, WALL_SIZE_Z);
			g_aWall[nCutWall].bUse = false;
	}
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * WALL_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffWall->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutWall = 0; nCutWall < WALL_MAX; nCutWall++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCutWall].size.x,  g_aWall[nCutWall].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( g_aWall[nCutWall].size.x,  g_aWall[nCutWall].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCutWall].size.x, -g_aWall[nCutWall].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( g_aWall[nCutWall].size.x, -g_aWall[nCutWall].size.y, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

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
	g_pVtxBuffWall->Unlock();
}

//=====================================
//= �ǂ̏I������
//=====================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < WALL_TEX; nCount++)
	{
		if (g_pTextureWall[nCount] != NULL)
		{
			g_pTextureWall[nCount]->Release();
			g_pTextureWall[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=====================================
//= �ǂ̍X�V����
//=====================================
void UpdateWall(void)
{

}

//=====================================
//= �ǂ̕`�揈��
//=====================================
void DrawWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	int nCutWall;

	for (nCutWall = 0; nCutWall < WALL_MAX; nCutWall++)
	{
		if (g_aWall[nCutWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCutWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCutWall].rot.y, g_aWall[nCutWall].rot.x, g_aWall[nCutWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCutWall].mtxWorld, &g_aWall[nCutWall].mtxWorld, &mtxRot);

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCutWall].pos.x, g_aWall[nCutWall].pos.y, g_aWall[nCutWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCutWall].mtxWorld, &g_aWall[nCutWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aWall[nCutWall].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffWall,
				0,
				sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(
				0,
				g_pTextureWall[0]);

			//�ǂ̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCutWall,			//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);						//�v���~�e�B�u�́i�ǁj��
		}

	}
}

//=====================================
//= �ǂ̐ݒ菈��
//=====================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ϐ��錾
	int nCutWall;

	for (nCutWall = 0; nCutWall < WALL_MAX; nCutWall++)
	{
		if (g_aWall[nCutWall].bUse == false)
		{
			g_aWall[nCutWall].bUse = true;

			g_aWall[nCutWall].pos = pos;
			g_aWall[nCutWall].rot = rot;

			break;
		}

	}
}

//=====================================
//= �ǂ̓����蔻�菈��
//=====================================
bool CollisionWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, Wall **pWall)
{
	//�ϐ��錾
	bool bCollison = false;	//����̗L��

	D3DXVECTOR3 pos0 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	D3DXVECTOR3 pos1 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	D3DXVECTOR3 pos2 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	D3DXVECTOR3 pos3 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);

	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecToPos;
	
	pos0 = D3DXVECTOR3(-490.0f, 0.0f, 490.0f);
	pos1 = D3DXVECTOR3(490.0f, 0.0f, 490.0f);
	pos2 = D3DXVECTOR3(-490.0f, 0.0f, -490.0f);
	pos3 = D3DXVECTOR3(490.0f, 0.0f, -490.0f);

	vecLine = pos1 - pos0;
	vecToPos = pos - pos0;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	vecLine = pos3 - pos1;
	vecToPos = pos - pos1;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	vecLine = pos2 - pos3;
	vecToPos = pos - pos3;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	vecLine = pos0 - pos2;
	vecToPos = pos - pos2;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	//int nCutWall;
	//
	//for (nCutWall = 0; nCutWall < 1; nCutWall++)
	//{
	//	if (g_aWall[nCutWall].bUse == true)
	//	{
	//		if (g_aWall[nCutWall].rot.y == 0.0f ||
	//			g_aWall[nCutWall].rot.y == -D3DX_PI)
	//		{
	//			if (pos.x >= g_aWall[nCutWall].pos.x - g_aWall[nCutWall].size.x &&
	//				pos.x <= g_aWall[nCutWall].pos.x + g_aWall[nCutWall].size.x &&
	//				pos.z >= g_aWall[nCutWall].pos.z - 10.0f &&
	//				pos.z <= g_aWall[nCutWall].pos.z + 10.0f)
	//			{
	//				bCollison = true;

	//				//�ǂ̃A�h���X����
	//				if (pWall != NULL)
	//				{//�ǂ̃A�h���X������ꏊ������
	//					*pWall = &g_aWall[nCutWall];		//�ǂ̃A�h���X����
	//				}

	//				break;
	//			}
	//		}
	//		else if (g_aWall[nCutWall].rot.y == D3DX_PI * 0.5f ||
	//			   	 g_aWall[nCutWall].rot.y == -D3DX_PI * 0.5f)
	//		{
	//			if (pos.x >= g_aWall[nCutWall].pos.x - 10.0f &&
	//				pos.x <= g_aWall[nCutWall].pos.x + 10.0f &&
	//				pos.z >= g_aWall[nCutWall].pos.z - g_aWall[nCutWall].size.z &&
	//				pos.z <= g_aWall[nCutWall].pos.z + g_aWall[nCutWall].size.z)
	//			{
	//				bCollison = true;
	//				break;
	//			}
	//		}
	//	}
	//}
	return bCollison;
}

//=====================================
//= �ǂ̎擾����
//=====================================
Wall *GetWall(void)
{
	return &g_aWall[0];
}
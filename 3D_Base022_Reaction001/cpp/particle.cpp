;
//=======================
//=
//= DirectX�̃p�[�e�B�N������[Particle.cpp]
//= Author Sakai Minato
//=
//=======================

#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "particle.h"
#include "effect.h"
#include "explosion.h"

//�}�N��
#define MAX_PARTICLE		(128)	//�p�[�e�B�N���̍ő吔

//�p�[�e�B�N���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nLife;				//�����i�\�����ԁj
	int nEffectLife;		//�G�t�F�N�g�̎����i�\�����ԁj
	int nEffectNumber;		//�\��������G�t�F�N�g�̐�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Particle;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//���_�o�b�t�@�̃|�C���^
Particle g_aParticle[MAX_PARTICLE];					//�p�[�e�B�N���̏��

//====================================
//= �p�[�e�B�N���̏���������
//=====================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCutParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�p�[�e�B�N���̏���������
	for (nCutParticle = 0; nCutParticle < MAX_PARTICLE; nCutParticle++)
	{
		g_aParticle[nCutParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCutParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCutParticle].nEffectLife = 0;
		g_aParticle[nCutParticle].nLife = 0;
		g_aParticle[nCutParticle].nEffectNumber = 0;
		g_aParticle[nCutParticle].bUse = false;
	}

}

//=====================================
//= �p�[�e�B�N���̏I������
//=====================================
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=====================================
//= �p�[�e�B�N���̍X�V����
//=====================================
void UpdateParticle(void)
{
	//�ϐ��錾
	int nCutParticle;
	int nCutAppear;

	for (nCutParticle = 0; nCutParticle < MAX_PARTICLE; nCutParticle++)
	{
		if (g_aParticle[nCutParticle].bUse == true)
		{//�p�[�e�B�N�����g�p����Ă���
			for (nCutAppear = 0; nCutAppear < g_aParticle[nCutParticle].nEffectNumber; nCutAppear++)
			{
				float fRotData;
				float fRotMove;

				fRotData = (float)(rand() % 629 - 314) / 100.0f;
				fRotMove = (float)(rand() % 100) / 50.0f;

				SetEffect(
					g_aParticle[nCutParticle].pos,
					D3DXVECTOR3((sinf(fRotData) * fRotMove),(cosf(fRotData) * fRotMove), 0.0f),
					g_aParticle[nCutParticle].col, 
					g_aParticle[nCutParticle].nEffectLife);
			}

			g_aParticle[nCutParticle].nLife--;

			if (g_aParticle[nCutParticle].nLife <= 0)
			{
				g_aParticle[nCutParticle].bUse = false;
			}
		}
	}
}

//=====================================
//= �p�[�e�B�N���̕`�揈��
//=====================================
void DrawParticle(void)
{
}

//=====================================
//= �p�[�e�B�N���̐ݒ菈��
//=====================================
void SetParticle(D3DXVECTOR3 pos, int nEffectNumber)
{
	//�ϐ��錾
	int nCutParticle;

	for (nCutParticle = 0; nCutParticle < MAX_PARTICLE; nCutParticle++)
	{
		if (g_aParticle[nCutParticle].bUse == false)
		{//�p�[�e�B�N�����Ȃ�
			//�Ԃ�l���p�[�e�B�N�����ɑ��
			g_aParticle[nCutParticle].pos = pos;
			g_aParticle[nCutParticle].nEffectNumber = nEffectNumber;

			//�p�[�e�B�N���̐ݒ�
			g_aParticle[nCutParticle].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 0.6f);

			g_aParticle[nCutParticle].bUse = true;
			break;
		}
	}
}
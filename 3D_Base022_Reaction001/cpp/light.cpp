
//=======================
//=
//= ���C�g�̏���[light.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "light.h"

//�}�N��
#define LIGHT_TEX	(1)			//���C�g�̃e�N�X�`���̐�
#define LIGHT_MAX	(3)			//���C�g�̍ő吔

//�O���[�o���ϐ�
D3DLIGHT9 g_light[LIGHT_MAX];	//���C�g�̏��

//====================================
//= ���C�g�̏���������
//=====================================
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXVECTOR3 vecDir[LIGHT_MAX];	//�ݒ�p�����x�N�g��
	int nCutLight;


	for (nCutLight = 0; nCutLight < LIGHT_MAX; nCutLight++)
	{

		//�O���[�o���ϐ��̏�����
		ZeroMemory(&g_light[nCutLight], sizeof(D3DLIGHT9));
		
		//���C�g�̎�ނ�ݒ�
		g_light[nCutLight].Type = D3DLIGHT_DIRECTIONAL;
		
		if (nCutLight == 0)
		{
			//���C�g�̊g�U����ݒ�
			g_light[nCutLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���C�g�̕�����ݒ�
			vecDir[nCutLight] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		}
		else  if (nCutLight == 1)
		{
			//���C�g�̊g�U����ݒ�
			g_light[nCutLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			//���C�g�̕�����ݒ�
			vecDir[nCutLight] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
		}
		else if (nCutLight == 2)
		{
			//���C�g�̊g�U����ݒ�
			g_light[nCutLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			//���C�g�̕�����ݒ�
			vecDir[nCutLight] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
		}

		//�x�N�g���𐳋K������i1.0f�j�ɂ���
		D3DXVec3Normalize(&vecDir[nCutLight], &vecDir[nCutLight]);
		g_light[nCutLight].Direction = vecDir[nCutLight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCutLight, &g_light[nCutLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCutLight, TRUE);

	}
}

//=====================================
//= ���C�g�̏I������
//=====================================
void UninitLight(void)
{
}

//=====================================
//= ���C�g�̍X�V����
//=====================================
void UpdateLight(void)
{

}
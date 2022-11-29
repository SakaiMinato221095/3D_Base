
//=======================
//=
//= ライトの処理[light.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "light.h"

//マクロ
#define LIGHT_TEX	(1)			//ライトのテクスチャの数
#define LIGHT_MAX	(3)			//ライトの最大数

//グローバル変数
D3DLIGHT9 g_light[LIGHT_MAX];	//ライトの情報

//====================================
//= ライトの初期化処理
//=====================================
void InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXVECTOR3 vecDir[LIGHT_MAX];	//設定用方向ベクトル
	int nCutLight;


	for (nCutLight = 0; nCutLight < LIGHT_MAX; nCutLight++)
	{

		//グローバル変数の初期化
		ZeroMemory(&g_light[nCutLight], sizeof(D3DLIGHT9));
		
		//ライトの種類を設定
		g_light[nCutLight].Type = D3DLIGHT_DIRECTIONAL;
		
		if (nCutLight == 0)
		{
			//ライトの拡散光を設定
			g_light[nCutLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//ライトの方向を設定
			vecDir[nCutLight] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		}
		else  if (nCutLight == 1)
		{
			//ライトの拡散光を設定
			g_light[nCutLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			//ライトの方向を設定
			vecDir[nCutLight] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
		}
		else if (nCutLight == 2)
		{
			//ライトの拡散光を設定
			g_light[nCutLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			//ライトの方向を設定
			vecDir[nCutLight] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
		}

		//ベクトルを正規化する（1.0f）にする
		D3DXVec3Normalize(&vecDir[nCutLight], &vecDir[nCutLight]);
		g_light[nCutLight].Direction = vecDir[nCutLight];

		//ライトを設定する
		pDevice->SetLight(nCutLight, &g_light[nCutLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCutLight, TRUE);

	}
}

//=====================================
//= ライトの終了処理
//=====================================
void UninitLight(void)
{
}

//=====================================
//= ライトの更新処理
//=====================================
void UpdateLight(void)
{

}
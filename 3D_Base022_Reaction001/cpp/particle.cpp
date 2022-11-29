;
//=======================
//=
//= DirectXのパーティクル処理[Particle.cpp]
//= Author Sakai Minato
//=
//=======================

#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "particle.h"
#include "effect.h"
#include "explosion.h"

//マクロ
#define MAX_PARTICLE		(128)	//パーティクルの最大数

//パーティクルの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nLife;				//寿命（表示時間）
	int nEffectLife;		//エフェクトの寿命（表示時間）
	int nEffectNumber;		//表示させるエフェクトの数
	bool bUse;				//使用しているかどうか
}Particle;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//頂点バッファのポインタ
Particle g_aParticle[MAX_PARTICLE];					//パーティクルの情報

//====================================
//= パーティクルの初期化処理
//=====================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCutParticle;

	//デバイスの取得
	pDevice = GetDevice();

	//パーティクルの情報を初期化
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
//= パーティクルの終了処理
//=====================================
void UninitParticle(void)
{
	//テクスチャの破棄
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=====================================
//= パーティクルの更新処理
//=====================================
void UpdateParticle(void)
{
	//変数宣言
	int nCutParticle;
	int nCutAppear;

	for (nCutParticle = 0; nCutParticle < MAX_PARTICLE; nCutParticle++)
	{
		if (g_aParticle[nCutParticle].bUse == true)
		{//パーティクルが使用されている
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
//= パーティクルの描画処理
//=====================================
void DrawParticle(void)
{
}

//=====================================
//= パーティクルの設定処理
//=====================================
void SetParticle(D3DXVECTOR3 pos, int nEffectNumber)
{
	//変数宣言
	int nCutParticle;

	for (nCutParticle = 0; nCutParticle < MAX_PARTICLE; nCutParticle++)
	{
		if (g_aParticle[nCutParticle].bUse == false)
		{//パーティクルがない
			//返り値をパーティクル情報に代入
			g_aParticle[nCutParticle].pos = pos;
			g_aParticle[nCutParticle].nEffectNumber = nEffectNumber;

			//パーティクルの設定
			g_aParticle[nCutParticle].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 0.6f);

			g_aParticle[nCutParticle].bUse = true;
			break;
		}
	}
}

//=======================
//=
//= 影の処理[shadow.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "shadow.h"

//マクロ
#define SHADOW_TEX		(1)			//影のテクスチャの数
#define SHADOW_MAX		(128)		//影の最大数

#define SHADOW_SIZE_X	(15.0f)		//影の大きさ（X軸）
#define SHADOW_SIZE_Y	(0.0f)		//影の大きさ（Y軸）
#define SHADOW_SIZE_Z	(15.0f)		//影の大きさ（Z軸）

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使用しているかどうか
}Shadow;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow[SHADOW_TEX] = {};	//テクスチャのポインタ
Shadow g_aShadow[SHADOW_MAX];							//影の情報

//====================================
//= 影の初期化処理
//=====================================
void InitShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutShadow;

	//グローバル変数の初期化
	for (nCutShadow = 0; nCutShadow < SHADOW_MAX; nCutShadow++)
	{
		g_aShadow[nCutShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCutShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCutShadow].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (SHADOW_MAX * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffShadow->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutShadow = 0; nCutShadow < SHADOW_MAX; nCutShadow++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE_X, 0.0f, SHADOW_SIZE_Z);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE_X, 0.0f, SHADOW_SIZE_Z);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE_X, 0.0f, -SHADOW_SIZE_Z);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE_X, 0.0f, -SHADOW_SIZE_Z);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーを設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタを頂点（４つ）分進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//=====================================
//= 影の終了処理
//=====================================
void UninitShadow(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < SHADOW_TEX; nCount++)
	{
		if (g_pTextureShadow[nCount] != NULL)
		{
			g_pTextureShadow[nCount]->Release();
			g_pTextureShadow[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=====================================
//= 影の更新処理
//=====================================
void UpdateShadow(void)
{

}

//=====================================
//= 影の描画処理
//=====================================
void DrawShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	int nCutShadow;

	//aブレンディングを減算合成に設定
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
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCutShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCutShadow].rot.y, g_aShadow[nCutShadow].rot.x, g_aShadow[nCutShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCutShadow].mtxWorld, &g_aShadow[nCutShadow].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCutShadow].pos.x, g_aShadow[nCutShadow].pos.y, g_aShadow[nCutShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCutShadow].mtxWorld, &g_aShadow[nCutShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aShadow[nCutShadow].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffShadow,
				0,
				sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(
				0,
				g_pTextureShadow[0]);

			//影の描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCutShadow,			//描画する最初の頂点インデックス
				2);						//プリミティブの（影）数
		}
	}

	//aブレンディングをもとに戻す
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
//= 影の設定処理
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
//= 影の情報の初期化処理
//=====================================
void ReSetShadow(int nldxShadow)
{
	g_aShadow[nldxShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aShadow[nldxShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aShadow[nldxShadow].bUse = false;
}
//=====================================
//= 影の位置設定処理
//=====================================
void ShadowPositionShadow(int nldxShadow, D3DXVECTOR3 pos)
{
	if (nldxShadow >= 0)
	{
		g_aShadow[nldxShadow].pos = pos;
	}
	
}

//=======================
//=
//= フィールドの処理[field.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "field.h"

//マクロ
#define FIELD_TEX	(1)									//フィールドのテクスチャの数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;			//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureField[FIELD_TEX] = {};		//テクスチャのポインタ
D3DXVECTOR3 g_posField;									//位置
D3DXVECTOR3 g_rotField;									//向き
D3DXMATRIX g_mtxWorldField;								//ワールドマトリックス

//====================================
//= フィールドの初期化処理
//=====================================
void InitField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//グローバル変数の初期化
	{
		g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureField[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffField->Lock(
		0,
		0,
		(void**)&pVtx,
		0);


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE_X, 0.0f, FIELD_SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(FIELD_SIZE_X, 0.0f, FIELD_SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-FIELD_SIZE_X, 0.0f, -FIELD_SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(FIELD_SIZE_X, 0.0f, -FIELD_SIZE_Z);

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

	//頂点バッファをアンロックする
	g_pVtxBuffField->Unlock();
}

//=====================================
//= フィールドの終了処理
//=====================================
void UninitField(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < FIELD_TEX; nCount++)
	{
		if (g_pTextureField[nCount] != NULL)
		{
			g_pTextureField[nCount]->Release();
			g_pTextureField[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=====================================
//= フィールドの更新処理
//=====================================
void UpdateField(void)
{

}

//=====================================
//= フィールドの描画処理
//=====================================
void DrawField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffField,
		0,
		sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(
		0,
		g_pTextureField[0]);

	//フィールドの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//描画する最初の頂点インデックス
		2);						//プリミティブの（フィールド）数

}


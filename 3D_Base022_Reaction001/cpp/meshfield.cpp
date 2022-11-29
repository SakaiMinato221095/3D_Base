
//=======================
//=
//= メッシュフィールドの処理[meshfield.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "meshfield.h"

//マクロ
#define MESH_FIELD_TEX		(1)			//メッシュフィールドのテクスチャの数

#define MESH_FIELD_W		(8 + 1)		//メッシュフィールドの横幅
#define MESH_FIELD_H		(8 + 1)		//メッシュフィールドの縦幅

#define MESH_FIELD_POS_X	(0.0f)		//増加の開始位置
#define MESH_FIELD_POS_Z	(0.0f)		//増加の開始位置

//メッシュフィールドの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
}MeshField;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;				//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField[MESH_FIELD_TEX] = {};	//テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshField = NULL;				//インデックスバッファへのポインタ
MeshField g_meshField;											//メッシュフィールドの構造体

//====================================
//= メッシュフィールドの初期化処理
//=====================================
void InitMeshField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutMeshFieldW, nCutMeshFieldH;

	//グローバル変数の初期化
	{
		g_meshField.pos = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
		g_meshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshField[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (MESH_FIELD_W * MESH_FIELD_H),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMeshField->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//頂点座標
	for (nCutMeshFieldH = 0; nCutMeshFieldH < MESH_FIELD_H; nCutMeshFieldH++)
	{
		for (nCutMeshFieldW = 0; nCutMeshFieldW < MESH_FIELD_W; nCutMeshFieldW++)
		{
			//頂点座標の設定
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].pos = D3DXVECTOR3((MESH_FIELD_POS_X + (100.0f * nCutMeshFieldW)), 0.0f, (MESH_FIELD_POS_Z - (100.0f * nCutMeshFieldH)));
			//法線ベクトルの設定
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//頂点カラーを設定
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャの座標を設定
			pVtx[(nCutMeshFieldH * MESH_FIELD_W) + nCutMeshFieldW].tex = D3DXVECTOR2(1.0f * nCutMeshFieldW, 1.0f * nCutMeshFieldH);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();

	int nData = ((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2));

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshField,
		NULL);

	//インデックス情報のポインタ
	WORD *pldx;

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pldxBuffMeshField->Lock(
		0,
		0,
		(void**)&pldx,
		0);

	//頂点番号データの設定
	for (nCutMeshFieldH = 0; nCutMeshFieldH < MESH_FIELD_H - 1; nCutMeshFieldH++)
	{
		for (nCutMeshFieldW = 0; nCutMeshFieldW < MESH_FIELD_W; nCutMeshFieldW++)
		{
			int nData1 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (nCutMeshFieldW * 2),
				nData2 = (nCutMeshFieldH * MESH_FIELD_W) + (MESH_FIELD_W + nCutMeshFieldW);

			int nData11 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (nCutMeshFieldW * 2) + 1,
				nData22 = (nCutMeshFieldH * MESH_FIELD_W) + (nCutMeshFieldW);

			pldx[(nCutMeshFieldH * (MESH_FIELD_W * 2) + 2) + (nCutMeshFieldW * 2)] = (nCutMeshFieldH * MESH_FIELD_W) + (MESH_FIELD_W + nCutMeshFieldW);
			pldx[(nCutMeshFieldH * (MESH_FIELD_W * 2) + 2) + (nCutMeshFieldW * 2) + 1] = (nCutMeshFieldH * MESH_FIELD_W) + (nCutMeshFieldW);

		}

		if (nCutMeshFieldH > MESH_FIELD_H - 2)
		{
			break;
		}

		int nData111 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2),
			nData221 = ((MESH_FIELD_W) * (nCutMeshFieldH + 1) - 1);

		int nData113 = (nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2) + 1,
			nData223 = (MESH_FIELD_W) * (nCutMeshFieldH + 2);

		pldx[(nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2)] = ((MESH_FIELD_W) * (nCutMeshFieldH + 1) - 1);
		pldx[(nCutMeshFieldH * ((MESH_FIELD_W * 2) + 2)) + (MESH_FIELD_W * 2) + 1] = (MESH_FIELD_W) * (nCutMeshFieldH + 2);


	}

	//インデックスバッファをアンロックする
	g_pldxBuffMeshField->Unlock();
}

//=====================================
//= メッシュフィールドの終了処理
//=====================================
void UninitMeshField(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < MESH_FIELD_TEX; nCount++)
	{
		if (g_pTextureMeshField[nCount] != NULL)
		{
			g_pTextureMeshField[nCount]->Release();
			g_pTextureMeshField[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファの破棄
	if (g_pldxBuffMeshField != NULL)
	{
		g_pldxBuffMeshField->Release();
		g_pldxBuffMeshField = NULL;
	}
}

//=====================================
//= メッシュフィールドの更新処理
//=====================================
void UpdateMeshField(void)
{

}

//=====================================
//= メッシュフィールドの描画処理
//=====================================
void DrawMeshField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshField.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshField.rot.y, g_meshField.rot.x, g_meshField.rot.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_meshField.mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffMeshField,
		0,
		sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pldxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(
		0,
		g_pTextureMeshField[0]);

	int nData = ((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2)) - 2;

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//プリミティブの種類
		0,																				//描画する最初の頂点インデックス
		0,
		(MESH_FIELD_W * MESH_FIELD_H),													//用意した頂点数
		0,
		((MESH_FIELD_H - 1) * (MESH_FIELD_W * 2) + ((MESH_FIELD_H - 2) * 2)) - 2);		//プリミティブの（メッシュフィールド）数

}



//=======================
//=
//= ポリゴンの処理[polygon.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "polygon.h"

//マクロ
#define POLYGON_TEX	(1)	//ポリゴンのテクスチャの数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;			//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePolygon[POLYGON_TEX] = {};		//テクスチャのポインタ
D3DXVECTOR3 g_posPolygon;									//位置
D3DXVECTOR3 g_rotPolygon;									//向き
D3DXMATRIX g_mtxWorldPolygon;								//ワールドマトリックス

//====================================
//= ポリゴンの初期化処理
//=====================================
void InitPolygon(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//グローバル変数の初期化
	{
		g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTexturePolygon[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffPolygon->Lock(
		0,
		0,
		(void**)&pVtx,
		0);


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-POLYGON_SIZE_X, 0.0f,  POLYGON_SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3( POLYGON_SIZE_X, 0.0f,  POLYGON_SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-POLYGON_SIZE_X, 0.0f, -POLYGON_SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3( POLYGON_SIZE_X, 0.0f, -POLYGON_SIZE_Z);

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
	g_pVtxBuffPolygon->Unlock();
}

//=====================================
//= ポリゴンの終了処理
//=====================================
void UninitPolygon(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < POLYGON_TEX; nCount++)
	{
		if (g_pTexturePolygon[nCount] != NULL)
		{
			g_pTexturePolygon[nCount]->Release();
			g_pTexturePolygon[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=====================================
//= ポリゴンの更新処理
//=====================================
void UpdatePolygon(void)
{

}

//=====================================
//= ポリゴンの描画処理
//=====================================
void DrawPolygon(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon, &mtxRot);
					   
	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldPolygon);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffPolygon,
		0,
		sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(
		0,
		g_pTexturePolygon[0]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//描画する最初の頂点インデックス
		2);						//プリミティブの（ポリゴン）数

}



//=======================
//=
//= メッシュウォールの処理[wall.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "meshwall.h"

//マクロ
#define MESH_WALL_TEX	(1)			//メッシュウォールのテクスチャの数

#define MESH_WALL_W		(16 + 1)	//メッシュウォールの横幅
#define MESH_WALL_H		(2 + 1)		//メッシュウォールの縦幅

#define MESH_WALL_POS_X	(0.0f)		//増加の開始位置
#define MESH_WALL_POS_Y	(0.0f)		//増加の開始位置

//メッシュウォールの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
}MeshWall;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;				//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshWall[MESH_WALL_TEX] = {};		//テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshWall = NULL;				//インデックスバッファへのポインタ
MeshWall g_meshWall;											//メッシュウォールの構造体

//====================================
//= メッシュウォールの初期化処理
//=====================================
void InitMeshWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutMeshWallW, nCutMeshWallH;

	//グローバル変数の初期化
	{
		g_meshWall.pos = D3DXVECTOR3(-500.0f, 100.0f, 500.0f);
		g_meshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshWall[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (MESH_WALL_W * MESH_WALL_H),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffMeshWall->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//頂点座標
	for (nCutMeshWallH = 0; nCutMeshWallH < MESH_WALL_H; nCutMeshWallH++)
	{
		for (nCutMeshWallW = 0; nCutMeshWallW < MESH_WALL_W; nCutMeshWallW++)
		{
			//頂点座標の設定
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].pos = D3DXVECTOR3((MESH_WALL_POS_X + (50.0f * nCutMeshWallW)), (MESH_WALL_POS_Y - (50.0f * nCutMeshWallH)), 0.0f );
			//法線ベクトルの設定
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//頂点カラーを設定
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャの座標を設定
			pVtx[(nCutMeshWallH * MESH_WALL_W) + nCutMeshWallW].tex = D3DXVECTOR2(1.0f * nCutMeshWallW, 1.0f * nCutMeshWallH);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();

	int nData = ((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2));

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshWall,
		NULL);

	//インデックス情報のポインタ
	WORD *pldx;

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pldxBuffMeshWall->Lock(
		0,
		0,
		(void**)&pldx,
		0);

	//頂点番号データの設定
	for (nCutMeshWallH = 0; nCutMeshWallH < MESH_WALL_H - 1; nCutMeshWallH++)
	{
		for (nCutMeshWallW = 0; nCutMeshWallW < MESH_WALL_W; nCutMeshWallW++)
		{
			int nData1 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (nCutMeshWallW * 2),
				nData2 = (nCutMeshWallH * MESH_WALL_W) + (MESH_WALL_W + nCutMeshWallW);

			int nData11 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (nCutMeshWallW * 2) + 1,
				nData22 = (nCutMeshWallH * MESH_WALL_W) + (nCutMeshWallW);

			pldx[(nCutMeshWallH * (MESH_WALL_W * 2) + 2) + (nCutMeshWallW * 2)] = (nCutMeshWallH * MESH_WALL_W) + (MESH_WALL_W + nCutMeshWallW);
			pldx[(nCutMeshWallH * (MESH_WALL_W * 2) + 2) + (nCutMeshWallW * 2) + 1] = (nCutMeshWallH * MESH_WALL_W) + (nCutMeshWallW);

		}

		if (nCutMeshWallH > MESH_WALL_H - 2)
		{
			break;
		}

		int nData111 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2),
			nData221 = ((MESH_WALL_W) * (nCutMeshWallH + 1) - 1);

		int nData113 = (nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2) + 1,
			nData223 = (MESH_WALL_W) * (nCutMeshWallH + 2);

		pldx[(nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2)] = ((MESH_WALL_W) * (nCutMeshWallH + 1) - 1);
		pldx[(nCutMeshWallH * ((MESH_WALL_W * 2) + 2)) + (MESH_WALL_W * 2) + 1] = (MESH_WALL_W) * (nCutMeshWallH + 2);


	}

	//インデックスバッファをアンロックする
	g_pldxBuffMeshWall->Unlock();
}

//=====================================
//= メッシュウォールの終了処理
//=====================================
void UninitMeshWall(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < MESH_WALL_TEX; nCount++)
	{
		if (g_pTextureMeshWall[nCount] != NULL)
		{
			g_pTextureMeshWall[nCount]->Release();
			g_pTextureMeshWall[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pldxBuffMeshWall != NULL)
	{
		g_pldxBuffMeshWall->Release();
		g_pldxBuffMeshWall = NULL;
	}
}

//=====================================
//= メッシュウォールの更新処理
//=====================================
void UpdateMeshWall(void)
{

}

//=====================================
//= メッシュウォールの描画処理
//=====================================
void DrawMeshWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshWall.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshWall.rot.y, g_meshWall.rot.x, g_meshWall.rot.z);
	D3DXMatrixMultiply(&g_meshWall.mtxWorld, &g_meshWall.mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_meshWall.pos.x, g_meshWall.pos.y, g_meshWall.pos.z);
	D3DXMatrixMultiply(&g_meshWall.mtxWorld, &g_meshWall.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_meshWall.mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffMeshWall,
		0,
		sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pldxBuffMeshWall);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(
		0,
		g_pTextureMeshWall[0]);

	int nData = ((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2)) - 2;

	//メッシュウォールの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,														//プリミティブの種類
		0,																			//描画する最初の頂点インデックス
		0,
		(MESH_WALL_W * MESH_WALL_H),												//用意した頂点数
		0,
		((MESH_WALL_H - 1) * (MESH_WALL_W * 2) + ((MESH_WALL_H - 2) * 2)) - 2);		//プリミティブの（メッシュウォール）数

}


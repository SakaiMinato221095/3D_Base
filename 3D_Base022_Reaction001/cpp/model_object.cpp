
//=======================
//=
//= モデルオブジェクトの処理[model_object.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "model_object.h"

#include "input.h"

#include "camera.h"

#include "shadow.h"

#include "bullet.h"
#include "wall.h"

//マクロ
#define PLAYER_TEX			(8)								//モデルオブジェクトのテクスチャの数

//グローバル変数
LPD3DXMESH g_pMeshModelObject = NULL;						//メッシュの情報のポインタ
LPD3DXBUFFER g_pBuffMatModelObject = NULL;					//マテリアルのポインタ
DWORD g_dwNumMatModelObject = 0;							//マテリアルの数
LPDIRECT3DTEXTURE9 g_pTextureModelObject[PLAYER_TEX] = {};	//テクスチャのポインタ

ModelObject g_modelObject;									//モデルオブジェクトの情報
D3DXMATRIX g_mtxWorldModelObject;							//ワールドマトリックス

//====================================
//= モデルオブジェクトの初期化処理
//=====================================
void InitModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATERIAL *pMat;							//マテリアルへのポインタ

	//グローバル変数の初期化
	{
		g_modelObject.pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		g_modelObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_modelObject.size = D3DXVECTOR3(45.0f, 0.0f, 15.0f);

	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\Scarecrow000.x",		//モデルオブジェクト名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModelObject,				//マテリアルの情報
		NULL,
		&g_dwNumMatModelObject,				//マテリアルの数
		&g_pMeshModelObject);				//メッシュの情報

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModelObject->GetBufferPointer();

	//マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelObject; nCutMat++)
	{
		if (pMat[nCutMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile
			(pDevice,
				pMat[nCutMat].pTextureFilename,
				&g_pTextureModelObject[nCutMat]);
		}
	}
}

//=====================================
//= モデルオブジェクトの終了処理
//=====================================
void UninitModelObject(void)
{
	//メッシュの破棄
	if (g_pMeshModelObject != NULL)
	{
		g_pMeshModelObject->Release();
		g_pMeshModelObject = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModelObject != NULL)
	{
		g_pBuffMatModelObject->Release();
		g_pBuffMatModelObject = NULL;
	}
}

//=====================================
//= モデルオブジェクトの更新処理
//=====================================
void UpdateModelObject(void)
{

}

//=====================================
//= モデルオブジェクトの描画処理
//=====================================
void DrawModelObject(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModelObject);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_modelObject.rot.y, g_modelObject.rot.x, g_modelObject.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModelObject, &g_mtxWorldModelObject, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_modelObject.pos.x, g_modelObject.pos.y, g_modelObject.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModelObject, &g_mtxWorldModelObject, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldModelObject);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModelObject->GetBufferPointer();

	//マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelObject; nCutMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		//テクスチャの設定（仮）
		pDevice->SetTexture(0, g_pTextureModelObject[nCutMat]);

		//モデルオブジェクト（パーツ）の描画
		g_pMeshModelObject->DrawSubset(nCutMat);
	}

	//保存していたマテリアルに戻す
	pDevice->SetMaterial(&matDef);

}

//=====================================
//= オブジェクトモデルの当たり判定処理
//=====================================
bool CollisionModelObject(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelObject **pModelObject)
{
	//変数宣言
	bool bCollison = false;	//判定の有

	if (pos.x >= g_modelObject.pos.x - g_modelObject.size.x &&
		pos.x <= g_modelObject.pos.x + g_modelObject.size.x &&
		pos.z >= g_modelObject.pos.z - g_modelObject.size.z &&
		pos.z <= g_modelObject.pos.z + g_modelObject.size.z)
	{
		bCollison = true;

		//壁のアドレスを代入
		if (pModelObject != NULL)
		{//壁のアドレスを入れる場所がある
			*pModelObject = &g_modelObject;		//壁のアドレスを代入
		}
	}

	return bCollison;
}
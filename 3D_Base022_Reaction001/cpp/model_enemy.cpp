
//=======================
//=
//= モデルエネミーの処理[model_enemy.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "model_enemy.h"

#include "input.h"

#include "camera.h"

#include "shadow.h"

#include "bullet.h"
#include "wall.h"

//マクロ
#define MODEL_ENEMY_TEX			(8)								//モデルエネミーのテクスチャの数

//グローバル変数
LPD3DXMESH g_pMeshModelEnemy = NULL;							//メッシュの情報のポインタ
LPD3DXBUFFER g_pBuffMatModelEnemy = NULL;						//マテリアルのポインタ
DWORD g_dwNumMatModelEnemy = 0;									//マテリアルの数
LPDIRECT3DTEXTURE9 g_pTextureModelEnemy[MODEL_ENEMY_TEX] = {};	//テクスチャのポインタ

ModelEnemy g_modelObject;										//モデルエネミーの情報
D3DXMATRIX g_mtxWorldModelEnemy;								//ワールドマトリックス

//====================================
//= モデルエネミーの初期化処理
//=====================================
void InitModelEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATERIAL *pMat;							//マテリアルへのポインタ

	//グローバル変数の初期化
	{
		g_modelObject.pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		g_modelObject.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_modelObject.size = D3DXVECTOR3(25.0f, 0.0f, 15.0f);

	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\alien001.x",		//モデルエネミー名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModelEnemy,				//マテリアルの情報
		NULL,
		&g_dwNumMatModelEnemy,				//マテリアルの数
		&g_pMeshModelEnemy);				//メッシュの情報

											//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModelEnemy->GetBufferPointer();

	//マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelEnemy; nCutMat++)
	{
		if (pMat[nCutMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile
			(pDevice,
				pMat[nCutMat].pTextureFilename,
				&g_pTextureModelEnemy[nCutMat]);
		}
	}
}

//=====================================
//= モデルエネミーの終了処理
//=====================================
void UninitModelEnemy(void)
{
	//メッシュの破棄
	if (g_pMeshModelEnemy != NULL)
	{
		g_pMeshModelEnemy->Release();
		g_pMeshModelEnemy = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModelEnemy != NULL)
	{
		g_pBuffMatModelEnemy->Release();
		g_pBuffMatModelEnemy = NULL;
	}
}

//=====================================
//= モデルエネミーの更新処理
//=====================================
void UpdateModelEnemy(void)
{

}

//=====================================
//= モデルエネミーの描画処理
//=====================================
void DrawModelEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModelEnemy);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_modelObject.rot.y, g_modelObject.rot.x, g_modelObject.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModelEnemy, &g_mtxWorldModelEnemy, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_modelObject.pos.x, g_modelObject.pos.y, g_modelObject.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModelEnemy, &g_mtxWorldModelEnemy, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldModelEnemy);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModelEnemy->GetBufferPointer();

	//マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatModelEnemy; nCutMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		//テクスチャの設定（仮）
		pDevice->SetTexture(0, g_pTextureModelEnemy[nCutMat]);

		//モデルエネミー（パーツ）の描画
		g_pMeshModelEnemy->DrawSubset(nCutMat);
	}

	//保存していたマテリアルに戻す
	pDevice->SetMaterial(&matDef);

}

//=====================================
//= オブジェクトモデルの当たり判定処理
//=====================================
bool CollisionModelEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelEnemy **pModelEnemy)
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
		if (pModelEnemy != NULL)
		{//壁のアドレスを入れる場所がある
			*pModelEnemy = &g_modelObject;		//壁のアドレスを代入
		}
	}

	return bCollison;
}

//=======================
//=
//= 壁の処理[wall.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "wall.h"

#include "polygon.h"
#include "bullet.h"
#include "explosion.h"
#include "Particle.h"

//マクロ
#define WALL_TEX	(1)				//壁のテクスチャの数
#define WALL_MAX	(4)				//壁の最大数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall[WALL_TEX] = {};		//テクスチャのポインタ
Wall g_aWall[WALL_MAX];									//壁の情報

//====================================
//= 壁の初期化処理
//=====================================
void InitWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutWall;

	//グローバル変数の初期化
	for (nCutWall = 0;  nCutWall < WALL_MAX; nCutWall++)
	{
			g_aWall[nCutWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aWall[nCutWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aWall[nCutWall].size = D3DXVECTOR3(WALL_SIZE_X, WALL_SIZE_Y, WALL_SIZE_Z);
			g_aWall[nCutWall].bUse = false;
	}
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * WALL_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffWall->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutWall = 0; nCutWall < WALL_MAX; nCutWall++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCutWall].size.x,  g_aWall[nCutWall].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( g_aWall[nCutWall].size.x,  g_aWall[nCutWall].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCutWall].size.x, -g_aWall[nCutWall].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( g_aWall[nCutWall].size.x, -g_aWall[nCutWall].size.y, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

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
	g_pVtxBuffWall->Unlock();
}

//=====================================
//= 壁の終了処理
//=====================================
void UninitWall(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < WALL_TEX; nCount++)
	{
		if (g_pTextureWall[nCount] != NULL)
		{
			g_pTextureWall[nCount]->Release();
			g_pTextureWall[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=====================================
//= 壁の更新処理
//=====================================
void UpdateWall(void)
{

}

//=====================================
//= 壁の描画処理
//=====================================
void DrawWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	int nCutWall;

	for (nCutWall = 0; nCutWall < WALL_MAX; nCutWall++)
	{
		if (g_aWall[nCutWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCutWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCutWall].rot.y, g_aWall[nCutWall].rot.x, g_aWall[nCutWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCutWall].mtxWorld, &g_aWall[nCutWall].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCutWall].pos.x, g_aWall[nCutWall].pos.y, g_aWall[nCutWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCutWall].mtxWorld, &g_aWall[nCutWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aWall[nCutWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffWall,
				0,
				sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(
				0,
				g_pTextureWall[0]);

			//壁の描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCutWall,			//描画する最初の頂点インデックス
				2);						//プリミティブの（壁）数
		}

	}
}

//=====================================
//= 壁の設定処理
//=====================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//変数宣言
	int nCutWall;

	for (nCutWall = 0; nCutWall < WALL_MAX; nCutWall++)
	{
		if (g_aWall[nCutWall].bUse == false)
		{
			g_aWall[nCutWall].bUse = true;

			g_aWall[nCutWall].pos = pos;
			g_aWall[nCutWall].rot = rot;

			break;
		}

	}
}

//=====================================
//= 壁の当たり判定処理
//=====================================
bool CollisionWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, Wall **pWall)
{
	//変数宣言
	bool bCollison = false;	//判定の有無

	D3DXVECTOR3 pos0 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	D3DXVECTOR3 pos1 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	D3DXVECTOR3 pos2 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	D3DXVECTOR3 pos3 = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);

	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecToPos;
	
	pos0 = D3DXVECTOR3(-490.0f, 0.0f, 490.0f);
	pos1 = D3DXVECTOR3(490.0f, 0.0f, 490.0f);
	pos2 = D3DXVECTOR3(-490.0f, 0.0f, -490.0f);
	pos3 = D3DXVECTOR3(490.0f, 0.0f, -490.0f);

	vecLine = pos1 - pos0;
	vecToPos = pos - pos0;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	vecLine = pos3 - pos1;
	vecToPos = pos - pos1;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	vecLine = pos2 - pos3;
	vecToPos = pos - pos3;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	vecLine = pos0 - pos2;
	vecToPos = pos - pos2;

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0.0f)
	{
		bCollison = true;
	}

	//int nCutWall;
	//
	//for (nCutWall = 0; nCutWall < 1; nCutWall++)
	//{
	//	if (g_aWall[nCutWall].bUse == true)
	//	{
	//		if (g_aWall[nCutWall].rot.y == 0.0f ||
	//			g_aWall[nCutWall].rot.y == -D3DX_PI)
	//		{
	//			if (pos.x >= g_aWall[nCutWall].pos.x - g_aWall[nCutWall].size.x &&
	//				pos.x <= g_aWall[nCutWall].pos.x + g_aWall[nCutWall].size.x &&
	//				pos.z >= g_aWall[nCutWall].pos.z - 10.0f &&
	//				pos.z <= g_aWall[nCutWall].pos.z + 10.0f)
	//			{
	//				bCollison = true;

	//				//壁のアドレスを代入
	//				if (pWall != NULL)
	//				{//壁のアドレスを入れる場所がある
	//					*pWall = &g_aWall[nCutWall];		//壁のアドレスを代入
	//				}

	//				break;
	//			}
	//		}
	//		else if (g_aWall[nCutWall].rot.y == D3DX_PI * 0.5f ||
	//			   	 g_aWall[nCutWall].rot.y == -D3DX_PI * 0.5f)
	//		{
	//			if (pos.x >= g_aWall[nCutWall].pos.x - 10.0f &&
	//				pos.x <= g_aWall[nCutWall].pos.x + 10.0f &&
	//				pos.z >= g_aWall[nCutWall].pos.z - g_aWall[nCutWall].size.z &&
	//				pos.z <= g_aWall[nCutWall].pos.z + g_aWall[nCutWall].size.z)
	//			{
	//				bCollison = true;
	//				break;
	//			}
	//		}
	//	}
	//}
	return bCollison;
}

//=====================================
//= 壁の取得処理
//=====================================
Wall *GetWall(void)
{
	return &g_aWall[0];
}

//=======================
//=
//= 爆発の処理[explosion.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "explosion.h"

//マクロ
#define EXPLOSION_TEX		(1)			//テクスチャの数
#define EXPLOSION_MAX		(128)		//爆発の最大数

#define EXPLOSION_SIZE_X	(20.0f)		//爆発の大きさ（X）
#define EXPLOSION_SIZE_Y	(20.0f)		//爆発の大きさ（Y）

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;				//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureExplosion[EXPLOSION_TEX] = {};		//テクスチャのポインタ

//爆発の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nAnimaCut;			//アニメーションの進めるためのカウント
	int nAnimaPatternCut;	//アニメーションの現在の数
	bool bUse;				//使用しているかどうか
}Explosion;

Explosion g_aExplosion[EXPLOSION_MAX];	//爆発の情報


//====================================
//= 爆発の初期化処理
//=====================================
void InitExplosion(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutExplosion;

	//爆発の情報を初期化
	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		g_aExplosion[nCutExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCutExplosion].bUse = false;
		g_aExplosion[nCutExplosion].nAnimaCut = 0;
		g_aExplosion[nCutExplosion].nAnimaPatternCut = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * EXPLOSION_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_SIZE_X, -EXPLOSION_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EXPLOSION_SIZE_X, -EXPLOSION_SIZE_Y, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		//ポインタを頂点（４つ）分進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=====================================
//= 爆発の終了処理
//=====================================
void UninitExplosion(void)
{
	for (int nCount = 0; nCount < EXPLOSION_TEX; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureExplosion[nCount] != NULL)
		{
			g_pTextureExplosion[nCount]->Release();
			g_pTextureExplosion[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=====================================
//= 爆発の更新処理
//=====================================
void UpdateExplosion(void)
{
	//変数宣言
	int nCutExplosion;

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		if (g_aExplosion[nCutExplosion].bUse == true)
		{
			//アニメーションの処理
			g_aExplosion[nCutExplosion].nAnimaCut++;

			if (g_aExplosion[nCutExplosion].nAnimaCut >= 10)
			{
				g_aExplosion[nCutExplosion].nAnimaCut = 0;
				g_aExplosion[nCutExplosion].nAnimaPatternCut++;
				if (g_aExplosion[nCutExplosion].nAnimaPatternCut >= 9)
				{
					ReSetExplosion(nCutExplosion);
				}
			}

			//テクスチャの座標を設定
			pVtx[0].tex = D3DXVECTOR2((0.125f *  g_aExplosion[nCutExplosion].nAnimaPatternCut), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(((0.125f * g_aExplosion[nCutExplosion].nAnimaPatternCut) + 0.125f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((0.125f *  g_aExplosion[nCutExplosion].nAnimaPatternCut), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(((0.125f * g_aExplosion[nCutExplosion].nAnimaPatternCut) + 0.125f), 1.0f);
		}


		//ポインタを頂点（４つ）分進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=====================================
//= 爆発の描画処理
//=====================================
void DrawExplosion(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxView[EXPLOSION_MAX];	//ビューマトリックスの取得用
	int nCutExplosion;

	//Zテストを無効化
	pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_ALWAYS);

	pDevice->SetRenderState(
		D3DRS_ZWRITEENABLE,
		FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(
		D3DRS_ALPHATESTENABLE,
		TRUE);

	pDevice->SetRenderState(
		D3DRS_ALPHAFUNC,
		D3DCMP_GREATER);

	pDevice->SetRenderState(
		D3DRS_ALPHAREF,
		0);

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		if (g_aExplosion[nCutExplosion].bUse == true)
		{//爆発が使用されている

		 //ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCutExplosion].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutExplosion]);

			//ポリゴンをカメラの位置に向きを変更
			D3DXMatrixInverse(
				&g_aExplosion[nCutExplosion].mtxWorld,
				NULL,
				&mtxView[nCutExplosion]);

			g_aExplosion[nCutExplosion].mtxWorld._41 = 0.0f;
			g_aExplosion[nCutExplosion].mtxWorld._42 = 0.0f;
			g_aExplosion[nCutExplosion].mtxWorld._43 = 0.0f;

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCutExplosion].pos.x, g_aExplosion[nCutExplosion].pos.y, g_aExplosion[nCutExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCutExplosion].mtxWorld, &g_aExplosion[nCutExplosion].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aExplosion[nCutExplosion].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffExplosion,
				0,
				sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(
				0,
				g_pTextureExplosion[0]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCutExplosion * 4,			//描画する最初の頂点インデックス
				2);						//プリミティブの（ポリゴン）数
		}
	}

	//Zテストを有効にする
	pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(
		D3DRS_ZWRITEENABLE,
		TRUE);

	//アルファテストの無効化
	pDevice->SetRenderState(
		D3DRS_ALPHATESTENABLE,
		FALSE);

	pDevice->SetRenderState(
		D3DRS_ALPHAFUNC,
		D3DCMP_ALWAYS);

	pDevice->SetRenderState(
		D3DRS_ALPHAREF,
		0);
}

//=====================================
//= 爆発の設定処理
//=====================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//変数宣言
	int nCutExplosion;

	for (nCutExplosion = 0; nCutExplosion < EXPLOSION_MAX; nCutExplosion++)
	{
		if (g_aExplosion[nCutExplosion].bUse == false)
		{//爆発がない
			g_aExplosion[nCutExplosion].bUse = true;

			g_aExplosion[nCutExplosion].pos = pos;

			break;
		}

	}
}

//=====================================
//= 爆発の情報初期化処理
//=====================================
void ReSetExplosion(int nCutExplosion)
{
	g_aExplosion[nCutExplosion].bUse = false;
	g_aExplosion[nCutExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion[nCutExplosion].nAnimaCut = 0;
	g_aExplosion[nCutExplosion].nAnimaPatternCut = 0;
	
}
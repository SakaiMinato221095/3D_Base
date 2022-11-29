
//=======================
//=
//= エフェクトの処理[bullet.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "effect.h"

#include "player.h"
#include "wall.h"

//マクロ
#define EFFECT_TEX		(1)			//テクスチャの数
#define EFFECT_MAX		(1024)		//エフェクトの最大数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_TEX] = {};	//テクスチャのポインタ

Effect g_aEffect[EFFECT_MAX];							//エフェクトの情報

//====================================
//= エフェクトの初期化処理
//=====================================
void InitEffect(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutEffect;

	//エフェクトの情報を初期化
	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		g_aEffect[nCutEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].nLife = 0;
		g_aEffect[nCutEffect].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\EFFECT\\effect000.jpg",
		&g_pTextureEffect[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * EFFECT_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EFFECT_SIZE_X, -EFFECT_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_SIZE_X, -EFFECT_SIZE_Y, 0.0f);

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
	g_pVtxBuffEffect->Unlock();
}

//=====================================
//= エフェクトの終了処理
//=====================================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < EFFECT_TEX; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount]->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=====================================
//= エフェクトの更新処理
//=====================================
void UpdateEffect(void)
{
	int nCutEffect;


	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		if (g_aEffect[nCutEffect].bUse == true)
		{
			//透明度をあげていく
			g_aEffect[nCutEffect].col.a -= g_aEffect[nCutEffect].col.a / g_aEffect[nCutEffect].nLife;

			//頂点カラーを設定
			pVtx[0].col = g_aEffect[nCutEffect].col;
			pVtx[1].col = g_aEffect[nCutEffect].col;
			pVtx[2].col = g_aEffect[nCutEffect].col;
			pVtx[3].col = g_aEffect[nCutEffect].col;

			//移動量を加算
			g_aEffect[nCutEffect].pos += g_aEffect[nCutEffect].move;

			//寿命のカウントダウン
			g_aEffect[nCutEffect].nLife--;

			//寿命が尽きた
			if (g_aEffect[nCutEffect].nLife < 0)
			{
				ResetEffect(nCutEffect);
			}
		}
		//ポインタを頂点（４つ）分進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=====================================
//= エフェクトの描画処理
//=====================================
void DrawEffect(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxView[EFFECT_MAX];		//ビューマトリックスの取得用
	int nCutEffect;

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(
		D3DRS_BLENDOP,
		D3DBLENDOP_ADD);
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE);

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
		1);

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		if (g_aEffect[nCutEffect].bUse == true)
		{//エフェクトが使用されている

		 //ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCutEffect].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutEffect]);

			//ポリゴンをカメラの位置に向きを変更
			D3DXMatrixInverse(
				&g_aEffect[nCutEffect].mtxWorld,
				NULL,
				&mtxView[nCutEffect]);

			g_aEffect[nCutEffect].mtxWorld._41 = 0.0f;
			g_aEffect[nCutEffect].mtxWorld._42 = 0.0f;
			g_aEffect[nCutEffect].mtxWorld._43 = 0.0f;

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCutEffect].pos.x, g_aEffect[nCutEffect].pos.y, g_aEffect[nCutEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCutEffect].mtxWorld, &g_aEffect[nCutEffect].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aEffect[nCutEffect].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffEffect,
				0,
				sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(
				0,
				g_pTextureEffect[0]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCutEffect * 4,			//描画する最初の頂点インデックス
				2);						//プリミティブの（ポリゴン）数
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
		1);
}

//=====================================
//= エフェクトの設定処理
//=====================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	//変数宣言
	int nCutEffect;

	for (nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		if (g_aEffect[nCutEffect].bUse == false)
		{//エフェクトがない
			g_aEffect[nCutEffect].bUse = true;

			g_aEffect[nCutEffect].pos = pos;
			g_aEffect[nCutEffect].move = move;
			g_aEffect[nCutEffect].nLife = nLife;
			g_aEffect[nCutEffect].col = col;

			break;
		}

	}
}
//=====================================
//= エフェクトの情報を初期化
//=====================================
void ResetEffect(int nCutEffect)
{
	g_aEffect[nCutEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect[nCutEffect].nLife = 0;
	g_aEffect[nCutEffect].bUse = false;
}

//=====================================
//= エフェクトを全消滅
//=====================================
void ClearEffect(void)
{
	for (int nCutEffect = 0; nCutEffect < EFFECT_MAX; nCutEffect++)
	{
		g_aEffect[nCutEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCutEffect].nLife = 0;
		g_aEffect[nCutEffect].bUse = false;
	}
}
//=====================================
//= エフェクトの取得処理
//=====================================
Effect *GetEffect(void)
{
	return &g_aEffect[0];
}

//=======================
//=
//= ビルボードの処理[bullet.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "billboard.h"

#include "shadow.h"

#include "player.h"

//マクロ
#define BILLBOARD_MAX		(64)		//ビルボードの最大数
#define BILLBOARD_TEX		(1)			//テクスチャの数
#define BILLBOARD_SIZE_X	(30.0f)		//プレイヤーのビルボードの大きさ
#define BILLBOARD_SIZE_Y	(30.0f)		//プレイヤーのビルボードの大きさ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARD_TEX] = {};		//テクスチャのポインタ

Billboard g_aBillboard[BILLBOARD_MAX];							//ビルボードの情報

//====================================
//= ビルボードの初期化処理
//=====================================
void InitBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutBillboard;

	//ビルボードの情報を初期化
	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		g_aBillboard[nCutBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCutBillboard].nShadowNum = -1;
		g_aBillboard[nCutBillboard].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\tree000.png",
		&g_pTextureBillboard[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * BILLBOARD_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBillboard->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X, BILLBOARD_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE_X, BILLBOARD_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X, -BILLBOARD_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE_X, -BILLBOARD_SIZE_Y, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=====================================
//= ビルボードの終了処理
//=====================================
void UninitBillboard(void)
{
	for (int nCount = 0; nCount < BILLBOARD_TEX; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureBillboard[nCount] != NULL)
		{
			g_pTextureBillboard[nCount]->Release();
			g_pTextureBillboard[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=====================================
//= ビルボードの更新処理
//=====================================
void UpdateBillboard(void)
{
	//変数宣言
	int nCutBillboard;

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		if (g_aBillboard[nCutBillboard].bUse == true)
		{//ビルボードが使用されている
			//影の更新処理
			ShadowPositionShadow(g_aBillboard[nCutBillboard].nShadowNum, D3DXVECTOR3(g_aBillboard[nCutBillboard].pos.x, 0.0f, g_aBillboard[nCutBillboard].pos.z));
		}
	}
}

//=====================================
//= ビルボードの描画処理
//=====================================
void DrawBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxView[BILLBOARD_MAX];	//ビューマトリックスの取得用
	int nCutBillboard;

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

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		if (g_aBillboard[nCutBillboard].bUse == true)
		{//ビルボードが使用されている

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCutBillboard].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutBillboard]);

			//ポリゴンをカメラの位置に向きを変更
			D3DXMatrixInverse(
				&g_aBillboard[nCutBillboard].mtxWorld,
				NULL,
				&mtxView[nCutBillboard]);

			g_aBillboard[nCutBillboard].mtxWorld._41 = 0.0f;
			g_aBillboard[nCutBillboard].mtxWorld._42 = 0.0f;
			g_aBillboard[nCutBillboard].mtxWorld._43 = 0.0f;

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCutBillboard].pos.x, g_aBillboard[nCutBillboard].pos.y, g_aBillboard[nCutBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCutBillboard].mtxWorld, &g_aBillboard[nCutBillboard].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aBillboard[nCutBillboard].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffBillboard,
				0,
				sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(
				0,
				g_pTextureBillboard[0]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCutBillboard * 4,			//描画する最初の頂点インデックス
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
//= ビルボードの設定処理
//=====================================
void SetBillboard(D3DXVECTOR3 pos)
{
	//変数宣言
	int nCutBillboard;

	for (nCutBillboard = 0; nCutBillboard < BILLBOARD_MAX; nCutBillboard++)
	{
		if (g_aBillboard[nCutBillboard].bUse == false)
		{//ビルボードがない
			g_aBillboard[nCutBillboard].bUse = true;

			g_aBillboard[nCutBillboard].pos = pos;
			g_aBillboard[nCutBillboard].nShadowNum = SetShadow();

			break;
		}

	}
}


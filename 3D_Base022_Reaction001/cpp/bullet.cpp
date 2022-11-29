
//=======================
//=
//= 弾の処理[bullet.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "bullet.h"

#include "shadow.h"

#include "player.h"

#include "effect.h"
#include "Particle.h"

#include "explosion.h"

#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

//マクロ
#define BULLET_TEX		(1)			//テクスチャの数
#define BULLET_SIZE_X	(10.0f)		//プレイヤーの弾の大きさ
#define BULLET_SIZE_Y	(10.0f)		//プレイヤーの弾の大きさ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLET_TEX] = {};	//テクスチャのポインタ

Bullet g_aBullet[BULLET_MAX];							//弾の情報

//====================================
//= 弾の初期化処理
//=====================================
void InitBullet(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	int nCutBullet;

	//弾の情報を初期化
	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		g_aBullet[nCutBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].posOld = g_aBullet[nCutBullet].pos;
		g_aBullet[nCutBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].nLife = 0;
		g_aBullet[nCutBullet].nShadowNum = -1;
		g_aBullet[nCutBullet].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (4 * BULLET_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE_X,  BULLET_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( BULLET_SIZE_X,  BULLET_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE_X, -BULLET_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( BULLET_SIZE_X, -BULLET_SIZE_Y, 0.0f);
		
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
	g_pVtxBuffBullet->Unlock();
}

//=====================================
//= 弾の終了処理
//=====================================
void UninitBullet(void)
{
	for (int nCount = 0; nCount < BULLET_TEX; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCount] != NULL)
		{
			g_pTextureBullet[nCount]->Release();
			g_pTextureBullet[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=====================================
//= 弾の更新処理
//=====================================
void UpdateBullet(void)
{
	int nCutBullet;

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{
			//前回の位置に現在の位置を代入
			g_aBullet[nCutBullet].posOld = g_aBullet[nCutBullet].pos;

			//位置を更新
			g_aBullet[nCutBullet].pos += g_aBullet[nCutBullet].move;

			//エフェクトの設定処理
			SetEffect(g_aBullet[nCutBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.5f),30);

			//影の更新処理
			ShadowPositionShadow(g_aBullet[nCutBullet].nShadowNum, D3DXVECTOR3(g_aBullet[nCutBullet].pos.x, 0.0f, g_aBullet[nCutBullet].pos.z));

			//寿命のカウントダウン
			g_aBullet[nCutBullet].nLife--;

			//寿命が尽きた
			if (g_aBullet[nCutBullet].nLife < 0)
			{
	 			ResetBullet(nCutBullet);
				break;
			}

			//壁とモデルとの当たり判定
			if (CollisionWall(g_aBullet[nCutBullet].pos, g_aBullet[nCutBullet].size,&g_aBullet[nCutBullet].pWall) == true ||
				CollisionModelObject(g_aBullet[nCutBullet].pos, g_aBullet[nCutBullet].size, &g_aBullet[nCutBullet].pModelObject) == true ||
				CollisionModelEnemy(g_aBullet[nCutBullet].pos, g_aBullet[nCutBullet].size, &g_aBullet[nCutBullet].pModelEnemy) == true)
			{
				SetExplosion(g_aBullet[nCutBullet].pos);
				ResetBullet(nCutBullet);
			}
		}

	}
}

//=====================================
//= 弾の描画処理
//=====================================
void DrawBullet(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxView[BULLET_MAX];		//ビューマトリックスの取得用
	int nCutBullet;

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

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{//弾が使用されている

		 //ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCutBullet].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(
				D3DTS_VIEW,
				&mtxView[nCutBullet]);

			//ポリゴンをカメラの位置に向きを変更
			D3DXMatrixInverse(
				&g_aBullet[nCutBullet].mtxWorld,
				NULL,
				&mtxView[nCutBullet]);

			g_aBullet[nCutBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCutBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCutBullet].mtxWorld._43 = 0.0f;

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCutBullet].pos.x, g_aBullet[nCutBullet].pos.y, g_aBullet[nCutBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCutBullet].mtxWorld, &g_aBullet[nCutBullet].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(
				D3DTS_WORLD,
				&g_aBullet[nCutBullet].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffBullet,
				0,
				sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(
				0,
				g_pTextureBullet[0]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCutBullet * 4,			//描画する最初の頂点インデックス
				2);						//プリミティブの（ポリゴン）数
		}
	}

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
//= 弾の設定処理
//=====================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BulletType type)
{
	//変数宣言
	int nCutBullet;

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == false)
		{//弾がない
			g_aBullet[nCutBullet].bUse = true;

			g_aBullet[nCutBullet].pos = pos;
			g_aBullet[nCutBullet].move = move;
			g_aBullet[nCutBullet].nLife = nLife;
			g_aBullet[nCutBullet].nShadowNum = SetShadow();

			break;
		}

	}
}
//=====================================
//= 弾の情報を初期化
//=====================================
void ResetBullet(int nCutBullet)
{
	g_aBullet[nCutBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBullet[nCutBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBullet[nCutBullet].nLife = 0;
	ReSetShadow(g_aBullet[nCutBullet].nShadowNum);
	g_aBullet[nCutBullet].nShadowNum = -1;
	g_aBullet[nCutBullet].bUse = false;
}

//=====================================
//= 弾を全消滅
//=====================================
void ClearBullet(void)
{
	for (int nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++)
	{
		g_aBullet[nCutBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCutBullet].nLife = 0;
		g_aBullet[nCutBullet].bUse = false;
	}
}
//=====================================
//= 弾の取得処理
//=====================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//=======================
//=
//= プレイヤーの処理[player.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "player.h"

#include "input.h"

#include "camera.h"

#include "shadow.h"

#include "bullet.h"
#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

//マクロ
#define PLAYER_TEX			(8)			//プレイヤーのテクスチャの数

#define PLAYER_SPEED		(1.0f)		//プレイヤーの速度
#define PLAYER_DECREASE		(0.3f)		//減速の値
#define PLAYER_ROT_DECREASE	(0.1f)		//向きの減速の値

//グローバル変数
LPD3DXMESH g_pMeshPlayer = NULL;						//メッシュの情報のポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;					//マテリアルのポインタ
DWORD g_dwNumMatPlayer = 0;								//マテリアルの数
LPDIRECT3DTEXTURE9 g_pTexturePlayer[PLAYER_TEX] = {};	//テクスチャのポインタ

Player g_player;										//プレイヤーの情報
D3DXMATRIX g_mtxWorldPlayer;							//ワールドマトリックス

//====================================
//= プレイヤーの初期化処理
//=====================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATERIAL *pMat;							//マテリアルへのポインタ

	//グローバル変数の初期化
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.posOld = g_player.pos;
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.nShadowNum = SetShadow();
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\alien000.x",		//プレイヤー名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,				//マテリアルの情報
		NULL,
		&g_dwNumMatPlayer,				//マテリアルの数
		&g_pMeshPlayer);				//メッシュの情報

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	//マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatPlayer; nCutMat++)
	{
		if (pMat[nCutMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile
			(pDevice,
				pMat[nCutMat].pTextureFilename,
				&g_pTexturePlayer[nCutMat]);
		}
	}
}

//=====================================
//= プレイヤーの終了処理
//=====================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//=====================================
//= プレイヤーの更新処理
//=====================================
void UpdatePlayer(void)
{
	//カメラの情報を取得
	Camera *pCamera = GetCamera();

	//前回の移動に代入
	g_player.posOld = g_player.pos;

	//入力の処理
	{
		//移動
		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーが押されたとき
			if (GetKeyboardPress(DIK_A) == true)
			{//左上移動
			 //移動量
				g_player.move.x -= sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//右上移動
			 //移動量
				g_player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else
			{
				//移動量
				g_player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 1.0f) + pCamera->rot.y;

			}
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキーが押されたとき
			if (GetKeyboardPress(DIK_A) == true)
			{//左下移動
			 //移動量
				g_player.move.x -= sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//右下移動
			 //移動量
				g_player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else
			{
				//移動量
				g_player.move.x += sinf((D3DX_PI * 1.0f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 1.0f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.0f) + pCamera->rot.y;
			}
		}

		else if (GetKeyboardPress(DIK_A) == true)
		{//Aキーが押されたとき
			if (GetKeyboardPress(DIK_W) == true)
			{//左上移動
			 //移動量
				g_player.move.x -= sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//左下移動
			 //移動量
				g_player.move.x -= sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else
			{//左移動
			 //移動量
				g_player.move.x -= sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z -= cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = (D3DX_PI * 0.5f) + pCamera->rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーが押されたとき
			if (GetKeyboardPress(DIK_W) == true)
			{//右上移動
			 //移動量
				g_player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.75f) + pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//右下移動
			 //移動量
				g_player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.25f) + pCamera->rot.y;
			}
			else
			{
				//移動量
				g_player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;
				g_player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_SPEED;

				g_player.rotDest.y = -(D3DX_PI * 0.5f) + pCamera->rot.y;
			}
		}

		//プレイヤーの弾を発射
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 20.0f, g_player.pos.z), D3DXVECTOR3(sinf(g_player.rot.y) * -1.0f, 0.0f, cosf(g_player.rot.y) * -1.0f), 240, BULLET_TYPE_PLAYER);
		}

		//プレイヤーの位置を初期化
		if (GetKeyboardPress(DIK_RETURN) == true)
		{//[エンターキーが押されたとき]
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			ClearBullet();
		}
	}

	//移動方向の差分
	g_player.rotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//角度の修正
	if (g_player.rotDiff.y > D3DX_PI)
	{
		g_player.rotDiff.y = -D3DX_PI;
	}
	else if (g_player.rotDiff.y < -D3DX_PI)
	{
		g_player.rotDiff.y = D3DX_PI;
	}

	//移動方向（角度）の補正
	g_player.rot.y += g_player.rotDiff.y * 0.15f;

	//角度の修正
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = -D3DX_PI;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = D3DX_PI;
	}

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;

	//移動量を更新
	g_player.move.x += (0.0f - g_player.move.x) * PLAYER_DECREASE;
	g_player.move.z += (0.0f - g_player.move.z) * PLAYER_DECREASE;

	//プレイヤーと壁の当たり判定
	if (CollisionWall       (g_player.pos, D3DXVECTOR3(20.0f, 0.0f, 0.0f), &g_player.pWall) == true ||
		CollisionModelObject(g_player.pos, D3DXVECTOR3(30.0f, 0.0f, 30.0f), &g_player.pModelObject) == true ||
		CollisionModelEnemy(g_player.pos, D3DXVECTOR3(30.0f, 0.0f, 30.0f), &g_player.pModelEnemy) == true)
	{
		g_player.pos = g_player.posOld;
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//影の更新処理
	ShadowPositionShadow(g_player.nShadowNum, g_player.pos);
}

//=====================================
//= プレイヤーの描画処理
//=====================================
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&g_mtxWorldPlayer);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	//マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)g_dwNumMatPlayer; nCutMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		//テクスチャの設定（仮）
		pDevice->SetTexture(0, g_pTexturePlayer[nCutMat]);

		//プレイヤー（パーツ）の描画
		g_pMeshPlayer->DrawSubset(nCutMat);
	}

	//保存していたマテリアルに戻す
	pDevice->SetMaterial(&matDef);

}

//=====================================
//= プレイヤーの取得処理
//=====================================
Player *GetPlayer(void)
{
	return &g_player;
}
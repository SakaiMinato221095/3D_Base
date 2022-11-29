
//=======================
//=
//= デバックの処理[debug.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "camera.h"

#include "input.h"

#include "player.h"

//マクロ
#define CAMERA_TEX			(1)			//カメラのテクスチャの数

#define CAMERA_V_DECREASE	(0.3f)		//視点の減速
#define CAMERA_R_DECREASE	(0.3f)		//注視点の減速
#define CAMERA_ROT_DECREASE	(0.3f)		//向きの減速

#define CAMERA_PLAYER_RANGE	(20.0f)		//カメラとプレイヤーの距離
#define CAMERA_RESET_TIME	(120)		//カメラのリセットする時間

//グローバル変数
Camera g_camera;						//カメラの情報
int nResetTime;							//プレイヤーの操作のない時間

//====================================
//= カメラの初期化処理
//=====================================
void InitCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//グローバル変数の初期化
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 250.0f, -100.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.fLength = 300.0f;

		g_camera.mode = CAMERA_MODE_FOLLOWING;

		nResetTime = 0;

		//カメラの情報を取得
		Player *pPlayer = GetPlayer();

		//注視点とプレイヤーの距離
		D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(sinf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE, 0.0f, cosf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE);

		//視点の設定
		g_camera.posV.x = pPlayer->pos.x + (sinf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.x;
		g_camera.posV.z = pPlayer->pos.z + (cosf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.z;

		//注視点の設定
		g_camera.posR.x = pPlayer->pos.x + cameraPlayer.x;
		g_camera.posR.z = pPlayer->pos.z + cameraPlayer.z;
	}
}

//=====================================
//= カメラの終了処理
//=====================================
void UninitCamera(void)
{

}

//=====================================
//= カメラの更新処理
//=====================================
void UpdateCamera(void)
{
	switch (g_camera.mode)
	{
		//通常カメラ
	case CAMERA_MODE_NORMAL:
		//移動
		if (GetKeyboardPress(DIK_UP) == true)
		{//右の移動[上矢印キーが押されたとき]

			g_camera.posV.z += 2.0f;
			g_camera.posR.z += 2.0f;

		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//右の移動[下矢印キーが押されたとき]

			g_camera.posV.z -= 2.0f;
			g_camera.posR.z -= 2.0f;

		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{//左の移動[左矢印キーが押されたとき]
			g_camera.posV.x -= 2.0f;
			g_camera.posR.x -= 2.0f;

		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{//右の移動[右矢印キーが押されたとき]

			g_camera.posV.x += 2.0f;
			g_camera.posR.x += 2.0f;

		}

		//注視点の回転
		if (GetKeyboardPress(DIK_Q) == true)
		{//[Qキーが押されたとき]

			g_camera.rot.y -= 0.05f;

			//注視点の位置を更新
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
		}
		if (GetKeyboardPress(DIK_E) == true)
		{//[Eキーが押されたとき]

			g_camera.rot.y += 0.05f;

			//注視点の位置を更新
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

		}

		//視点の回転
		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rot.y -= 0.05f;

			//視点の位置を更新
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;
		}
		if (GetKeyboardPress(DIK_C) == true)
		{//[Eキーが押されたとき]
			g_camera.rot.y += 0.05f;

			//視点の位置を更新
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;
		}

		if (GetKeyboardPress(DIK_RETURN) == true)
		{//[エンターキーが押されたとき]
			g_camera.posV = D3DXVECTOR3(0.0f, 50.0f, -200.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
			g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//注視点の位置を更新
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;
		}
		break;
		//追従カメラ
	case CAMERA_MODE_FOLLOWING:

		//カメラの情報を取得
		Player *pPlayer = GetPlayer();

		//注視点とプレイヤーの距離
		D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(sinf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE, 0.0f, cosf(pPlayer->rot.y) * -CAMERA_PLAYER_RANGE);

		//nResetTime++;

		//リセットする入力を確認
		if (GetKeyboardPress(DIK_W) == true ||
			GetKeyboardPress(DIK_S) == true || 
			GetKeyboardPress(DIK_A) == true || 
			GetKeyboardPress(DIK_D) == true ||
			GetKeyboardPress(DIK_Z) == true ||
			GetKeyboardPress(DIK_C) == true)
		{
			//時間のリセット
			nResetTime = 0;
		}

		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rotDest.y += 0.03f;
		}
		if (GetKeyboardPress(DIK_C) == true)
		{//[Eキーが押されたとき]
			g_camera.rotDest.y -= 0.03f;
		}

		if (GetKeyboardPress(DIK_RETURN) == true)
		{//[エンターキーが押されたとき]
			g_camera.posV = D3DXVECTOR3(0.0f, 140.0f, -100.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
			g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.fLength = 200.0f;

			g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//視点の設定
			g_camera.posV.x = pPlayer->pos.x + (sinf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.x;
			g_camera.posV.z = pPlayer->pos.z + (cosf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.z;

			//注視点の設定
			g_camera.posR.x = pPlayer->pos.x + cameraPlayer.x;
			g_camera.posR.z = pPlayer->pos.z + cameraPlayer.z;
		}

		if (nResetTime >= CAMERA_RESET_TIME)
		{
			g_camera.rotDest.y = (pPlayer->rot.y - D3DX_PI);

			//時間のリセット
			nResetTime = 0;
		}

		//角度の修正
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
			g_camera.rotDest.y = -D3DX_PI + (g_camera.rotDest.y - D3DX_PI);
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
			g_camera.rotDest.y = D3DX_PI + (g_camera.rotDest.y + D3DX_PI);
		}

		//視点の位置を更新
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -g_camera.fLength;

		//目的の視点の位置
		g_camera.posVDest.x = pPlayer->pos.x + (sinf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.x;
		g_camera.posVDest.z = pPlayer->pos.z + (cosf(g_camera.rot.y) * -g_camera.fLength) + cameraPlayer.z;

		//目的の注視点の位置
		g_camera.posRDest.x = pPlayer->pos.x + cameraPlayer.x;
		g_camera.posRDest.z = pPlayer->pos.z + cameraPlayer.z;

		//視点の補正
		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_V_DECREASE;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_V_DECREASE;

		//注視点の補正
		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_R_DECREASE;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_R_DECREASE;

		//角度の補正
		g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * CAMERA_ROT_DECREASE;

		break;

	}


}

//=====================================
//= カメラの設定処理
//=====================================
void SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//プロジェションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjectien);

	//プロジェションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjectien,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(
		D3DTS_PROJECTION,
		&g_camera.mtxProjectien);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);
		
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,		//視点
		&g_camera.posR,		//注視点
		&g_camera.vecU);	//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(
		D3DTS_VIEW,
		&g_camera.mtxView);
}


//=====================================
//= カメラの取得処理
//=====================================
Camera *GetCamera(void)
{
	return &g_camera;
}
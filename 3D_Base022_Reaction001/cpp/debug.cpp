
//=======================
//=
//= デバック処理[debug.cpp]
//= Author Sakai Minato
//=
//=======================

#include <stdio.h>

#include "main.h"
#include "debug.h"

#include "camera.h"
#include "player.h"
#include "bullet.h"
#include "wall.h"

//プロトタイプ宣言
void DrawDebugPlayer(LPD3DXFONT pFont);
void DrawDebugCamera(LPD3DXFONT pFont);
void DrawDebugBullet(LPD3DXFONT pFont);
void DrawDebugWall(LPD3DXFONT pFont);

//グローバル変数宣言
int g_nDebugTextCount;



//=====================================
//= デバックの初期化処理
//=====================================
void InitDebug(void)
{
	//グローバル変数の初期化
	g_nDebugTextCount = 0;
}

//=====================================
//= デバックの終了処理
//=====================================
void UninitDebug(void)
{

}

//=====================================
//= デバックの更新処理
//=====================================
void UpdateDebug(void)
{

}

//=====================================
//= デバックの描画処理
//=====================================
void DrawDebug(LPD3DXFONT pFont)
{
	//プレイヤー
	DrawDebugPlayer(pFont);

	//カメラ
	DrawDebugCamera(pFont);

	//弾
	DrawDebugBullet(pFont);

	//壁
	DrawDebugWall(pFont);
}

//=====================================
//= デバックカウントの計算
//=====================================
int DebugCalTextCount(DebugTextCountCal Cal)
{
	//デバックテキストカウントの計算
	switch (Cal)
	{
	case DEBUG_TEXT_COUNT_CAL_ADD:
		g_nDebugTextCount++;
		break;
	case DEBUG_TEXT_COUNT_CAL_SUB:
		g_nDebugTextCount--;
		break;
	}
	
	return g_nDebugTextCount;

}

//=====================================
//= デバックカメラの情報を表示
//=====================================
void DrawDebugCamera(LPD3DXFONT pFont)
{
	//カメラの情報を取得
	Camera *pCamera = GetCamera();

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[5][256];

	//文字列を代入
	wsprintf(&aStr[0][0], "=========カメラ==========");
	wsprintf(&aStr[1][0], "\n＜視点＞	  X(%d) Y(%d) Z(%d)\n", (int)pCamera->posV.x, (int)pCamera->posV.y, (int)pCamera->posV.z);
	wsprintf(&aStr[2][0], "\n\n＜注視点＞ X(%d) Y(%d) Z(%d)\n", (int)pCamera->posR.x, (int)pCamera->posR.y, (int)pCamera->posR.z);
	sprintf(&aStr[3][0], "\n\n\n＜回転＞ Y(%2.2f) \n", pCamera->rot.y);
	sprintf(&aStr[4][0], "\n\n\n\n＜目的の向き＞ Y(%2.2f) \n", pCamera->rotDest.y);

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[4][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//=====================================
//= デバックプレイヤーの情報を表示
//=====================================
void DrawDebugPlayer(LPD3DXFONT pFont)
{
	//カメラの情報を取得
	Player *pPlayer = GetPlayer();

	RECT rect = { 0,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[6][256];

	//文字列を代入
	sprintf(&aStr[0][0], "=========プレイヤー==========");
	sprintf(&aStr[1][0], "\n＜位置＞ X(%3.1f) Y(%3.1f) Z(%3.1f)\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	sprintf(&aStr[2][0], "\n\n＜前回位置＞ X(%3.1f) Y(%3.1f) Z(%3.1f)\n", pPlayer->posOld.x, pPlayer->posOld.y, pPlayer->posOld.z);
	sprintf(&aStr[3][0], "\n\n\n＜移動量＞ X(%2.2f) Y(%2.2f) Z(%2.2f)\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);
	sprintf(&aStr[4][0], "\n\n\n\n＜向き＞ Y(%2.2f)", pPlayer->rot.y);
	sprintf(&aStr[5][0], "\n\n\n\n\n＜目的の向き＞ Y(%2.2f)", pPlayer->rotDest.y);

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[4][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[5][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//=====================================
//= デバックバレットの情報を表示
//=====================================
void DrawDebugBullet(LPD3DXFONT pFont)
{
	//カメラの情報を取得
	Bullet *pBullet = GetBullet();

	//変数宣言
	int nCutBullet;
	int BulletNumber = 0;

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			BulletNumber++;
		}
	}

	pBullet -= BULLET_MAX;

	RECT rect = { 0,250,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[5][256];

	//文字列を代入
	wsprintf(&aStr[0][0], "=========弾==========");
	wsprintf(&aStr[1][0], "\n＜発射数＞ %d", BulletNumber);
	wsprintf(&aStr[2][0], "\n\n＜位置＞ X(%d) Y(%d) Z(%d)\n", (int)pBullet->pos.x, (int)pBullet->pos.y, (int)pBullet->pos.z);
	wsprintf(&aStr[3][0], "\n\n\n＜移動量＞ X(%d) Y(%d) Z(%d)\n", (int)pBullet->move.x, (int)pBullet->move.y, (int)pBullet->move.z);
	wsprintf(&aStr[4][0], "\n\n\n\n＜寿命＞ LIFE(%d)\n", pBullet->nLife);

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[4][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//=====================================
//= デバックウォールの情報を表示
//=====================================
void DrawDebugWall(LPD3DXFONT pFont)
{
	//カメラの情報を取得
	Wall *pWall = GetWall();

	//変数宣言
	int WallNumber = 0;

	RECT rect = { 0,350,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[5][256];

	//文字列を代入
	wsprintf(&aStr[0][0], "=========壁==========");
	wsprintf(&aStr[1][0], "\n＜発射数＞ %d", WallNumber);
	wsprintf(&aStr[2][0], "\n\n＜位置＞ X(%d) Y(%d) Z(%d)\n", (int)pWall->pos.x, (int)pWall->pos.y, (int)pWall->pos.z);
	wsprintf(&aStr[3][0], "\n\n\n＜移動量＞ X(%d) Y(%d) Z(%d)\n", (int)pWall->size.x, (int)pWall->size.x, (int)pWall->size.x);

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
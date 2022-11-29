//=======================
//=
//= プレイヤーのヘッター[player.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _PLAYER_H_	//このマクロが定義されなかったら
#define _PLAYER_H_	//二重インクルード帽子のマクロを定義

#include "main.h"
#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotDest;		//目的の向き
	D3DXVECTOR3 rotDiff;		//角度の差分
	int nShadowNum = -1;		//影の番号
	Wall *pWall;				//対象の壁のポインタ
	ModelObject *pModelObject;	//対象のオブジェクトモデルのポインタ
	ModelEnemy *pModelEnemy;	//対象のエネミーモデルのポインタ
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif 
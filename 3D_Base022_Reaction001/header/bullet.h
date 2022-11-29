
//=======================
//=
//= 弾のヘッター[Bullet.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _BULLET_H_	//このマクロが定義されなかったら
#define _BULLET_H_	//二重インクルード帽子のマクロを定義

#include "main.h"
#include "wall.h"
#include "model_object.h"
#include "model_enemy.h"

#define BULLET_MAX		(128)		//弾の最大数

//弾の種類
typedef enum
{
	BULLET_TYPE_PLAYER = 0,		//プレイヤーの弾
	BULLET_TYPE_ENEMY = 0,		//敵の弾
	BULLET_TYPE_MAX,			//弾の種類の最大数
}BulletType;

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 size;			//位置
	D3DXVECTOR3 move;			//移動量
	int nLife;					//寿命
	int nShadowNum;				//影の番号
	bool bUse;					//使用しているかどうか
	Wall *pWall;				//対象の壁のポインタ
	ModelObject *pModelObject;	//対象のオブジェクトモデルのポインタ
	ModelEnemy *pModelEnemy;	//対象のエネミーモデルのポインタ
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nLife, BulletType type);
void ResetBullet(int nCutBullet);
void ClearBullet(void);
Bullet *GetBullet(void);

#endif 
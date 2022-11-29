
//=======================
//=
//= オブジェクトモデルのヘッター[model_object.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _MODEL_ENEMY_H_	//このマクロが定義されなかったら
#define _MODEL_ENEMY_H_	//二重インクルード帽子のマクロを定義

//オブジェクトモデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 size;		//大きさ
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
}ModelEnemy;

//プロトタイプ宣言
void InitModelEnemy(void);
void UninitModelEnemy(void);
void UpdateModelEnemy(void);
void DrawModelEnemy(void);
bool CollisionModelEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelEnemy **pModelEnemy);

#endif 

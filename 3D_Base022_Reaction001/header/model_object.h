
//=======================
//=
//= オブジェクトモデルのヘッター[model_object.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _MODEL_OBJECT_H_	//このマクロが定義されなかったら
#define _MODEL_OBJECT_H_	//二重インクルード帽子のマクロを定義

//オブジェクトモデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 size;		//大きさ
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
}ModelObject;

//プロトタイプ宣言
void InitModelObject(void);
void UninitModelObject(void);
void UpdateModelObject(void);
void DrawModelObject(void);
bool CollisionModelObject(D3DXVECTOR3 pos, D3DXVECTOR3 size, ModelObject **pModelObject);

#endif 
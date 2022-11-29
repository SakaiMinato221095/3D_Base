
//=======================
//=
//= モデルの処理[model.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "model_object.h"
#include "model_enemy.h"

//====================================
//= モデルの初期化処理
//=====================================
void InitModel(void)
{
	//オブジェクト
	InitModelObject();

	//エネミー
	InitModelEnemy();
}

//=====================================
//= モデルの終了処理
//=====================================
void UninitModel(void)
{
	//オブジェクト
	UninitModelObject();

	//エネミー
	UninitModelEnemy();
}

//=====================================
//= モデルの更新処理
//=====================================
void UpdateModel(void)
{
	//オブジェクト
	UpdateModelObject();

	//エネミー
	UpdateModelEnemy();
}

//=====================================
//= モデルの描画処理
//=====================================
void DrawModel(void)
{
	//オブジェクト
	DrawModelObject();

	//エネミー
	DrawModelEnemy();
}


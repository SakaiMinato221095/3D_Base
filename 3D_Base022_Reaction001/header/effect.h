
//=======================
//=
//= エフェクトのヘッター[Effect.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _EFFECT_H_	//このマクロが定義されなかったら
#define _EFFECT_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

#define EFFECT_SIZE_X	(10.0f)		//エフェクトの大きさ
#define EFFECT_SIZE_Y	(10.0f)		//エフェクトの大きさ

//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	float fRadins;			//大きさ
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nLife;				//寿命
	bool bUse;				//使用しているかどうか
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);
void ResetEffect(int nCutEffect);
void ClearEffect(void);
Effect *GetEffect(void);

#endif 
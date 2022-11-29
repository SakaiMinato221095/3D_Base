
//=======================
//=
//= ビルボードのヘッター[Billboard.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _BILLBOARD_H_	//このマクロが定義されなかったら
#define _BILLBOARD_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

//ビルボードの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nShadowNum;			//影の番号
	bool bUse;				//使用しているかどうか
}Billboard;

//プロトタイプ宣言
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos);

#endif 
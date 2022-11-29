
//=======================
//=
//= 影のヘッター[shadow.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _SHADOW_H_	//このマクロが定義されなかったら
#define _SHADOW_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void ShadowPositionShadow(int nldxShadow,D3DXVECTOR3 pos);
void ReSetShadow(int nldxShadow);


#endif 


//=======================
//=
//= DirectXの弾の爆発のヘッター[explosion.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _EXPLOSION_H_	//このマクロが定義されなかったら
#define _EXPLOSION_H_	//二重インクルード帽子のマクロを定義

#include "main.h"



//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void ReSetExplosion(int nCutExplosion);

#endif 

//=======================
//=
//= パーティクルのヘッター[particle.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _PARTICLE_H_	//このマクロが定義されなかったら
#define _PARTICLE_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

//マクロ
#define PARTICLE_HIT_NUMBER		(32)	//ヒット時のパーティクル量

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nEffectNumber);

#endif 



//=======================
//=
//= ポリゴンのヘッター[polygon.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _POLYGON_H_	//このマクロが定義されなかったら
#define _POLYGON_H_	//二重インクルード帽子のマクロを定義

#define POLYGON_SIZE_X	(500.0f)	//ポリゴンの大きさ（X軸）
#define POLYGON_SIZE_Y	(0.0f)		//ポリゴンの大きさ（Y軸）
#define POLYGON_SIZE_Z	(500.0f)	//ポリゴンの大きさ（Z軸）

//プロトタイプ宣言
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

#endif 

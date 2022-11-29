
//=======================
//=
//= フィールドのヘッター[polygon.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _FIELD_H_	//このマクロが定義されなかったら
#define _FIELD_H_	//二重インクルード帽子のマクロを定義

#define FIELD_SIZE_X	(500.0f)	//フィールドの大きさ（X軸）
#define FIELD_SIZE_Y	(0.0f)		//フィールドの大きさ（Y軸）
#define FIELD_SIZE_Z	(500.0f)	//フィールドの大きさ（Z軸）

//プロトタイプ宣言
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif 

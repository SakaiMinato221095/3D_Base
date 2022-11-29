
//=======================
//=
//= 壁のヘッター[polygon.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _WALL_H_	//このマクロが定義されなかったら
#define _WALL_H_	//二重インクルード帽子のマクロを定義

//マクロ
#define WALL_SIZE_X	(500.0f)	//ポリゴンの大きさ（X軸）
#define WALL_SIZE_Y	(110.0f)	//ポリゴンの大きさ（Y軸）
#define WALL_SIZE_Z	(500.0f)	//ポリゴンの大きさ（Z軸）

//壁の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 size;		//大きさ
	bool bUse;				//使用しているかどうか
}Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool CollisionWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, Wall **pWall);
Wall *GetWall(void);

#endif 
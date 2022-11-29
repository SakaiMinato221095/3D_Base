
//=======================
//=
//= カメラのヘッター[camera.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _CAMERA_H_	//このマクロが定義されなかったら
#define _CAMERA_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

//カメラモード選択の列挙型
typedef enum
{
	CAMERA_MODE_NORMAL = 0,
	CAMERA_MODE_FOLLOWING,
}CameraMode;

//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX mtxProjectien;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotDest;		//目的の向き
	float fLength;				//長さ
	CameraMode mode;			//モード
}Camera;



//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif 
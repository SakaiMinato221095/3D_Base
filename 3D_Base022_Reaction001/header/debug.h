
//=======================
//=
//= デバックのヘッター[camera.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _DEBUG_H_	//このマクロが定義されなかったら
#define _DEBUG_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

//デバックテキストカウントの計算の列挙型
typedef enum
{
	DEBUG_TEXT_COUNT_CAL_ADD = 0,
	DEBUG_TEXT_COUNT_CAL_SUB,
}DebugTextCountCal;

//プロトタイプ宣言
void InitDebug(void);
void UninitDebug(void);
void UpdateDebug(void);
void DrawDebug(LPD3DXFONT pFont);
int DebugCalTextCount(DebugTextCountCal Cal);

#endif 
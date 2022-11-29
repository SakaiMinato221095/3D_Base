
//=======================
//=
//= DirectXの入力のヘッター[Input.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _INPUT_H_	//このマクロが定義されなかったら
#define _INPUT_H_	//二重インクルード帽子のマクロを定義

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstanse,HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

#endif 
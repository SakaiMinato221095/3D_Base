
//=======================
//=
//= 入力の処理[Input.h]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "Input.h"

//マクロ定義
#define NUM_KEY_MAX	(256)	//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイス（キーボード）へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					//キーボードのブレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報

//=====================================
//= キーボードの初期化処理
//=====================================
HRESULT InitKeyboard(HINSTANCE hInstanse, HWND hWnd)
{
	//DivectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstanse,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pInput,NULL)))
	{
		return E_FAIL;
	}
	//入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}
	//データファーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	
	return S_OK;
}

//=====================================
//= キーボードの終了処理
//=====================================
void UninitKeyboard(void)
{
	//入力デバイス（キーボード）の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//キーボードへのアクセスを破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================
//= キーボードの更新処理
//=====================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//キーボードの入力情報
	int nCutKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (nCutKey = 0; nCutKey < NUM_KEY_MAX; nCutKey++)
		{
			g_aKeyStateTrigger[nCutKey] = (g_aKeyState[nCutKey] ^ aKeyState[nCutKey]) & aKeyState[nCutKey];		//キーボードのトリガー情報
			g_aKeyStateRelease[nCutKey] = (aKeyState[nCutKey] ^ g_aKeyState[nCutKey]) & g_aKeyState[nCutKey];	//キーボードのリリース情報
			g_aKeyState[nCutKey] = aKeyState[nCutKey];															//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//キーボードのアクセス権を獲得
	}
}

//=====================================
//= キーボードのブレスの情報を取得
//=====================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
//= キーボードのトリガーの情報を取得
//=====================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================
//= キーボードのリリースの情報を取得
//=====================================
bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=======================
//=
//= DirectXの基本処理[main.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"

#include "debug.h"
#include "Input.h"

#include "camera.h"
#include "light.h"

#include "polygon.h"
#include "field.h"
#include "wall.h"
#include "meshfield.h"
#include "meshwall.h"

#include "model.h"
#include "player.h"

#include "billboard.h"
#include "bullet.h"

#include "explosion.h"
#include "effect.h"

#include "particle.h"

#include "shadow.h"

//マクロ定義
#define CLASS_NAME			"Window class"				//ウィンドウクラスの名前
#define WINDOW_NAME			"3D"						//ウィンドウの名前

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;				//フォントへのポインタ
int g_nCountFPS = 0;					//FPSカウンタ		
bool g_bDsipDehug = false;				//デバック状態のON/OFF

//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=====================================
//=	メイン関数
//=====================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLime, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウィンドウのスタイル
		WindowProc,							//ウィンドウプロシージャ
		0,									//0にする（通常はしようしない）
		0,									//0にする（通常はしようしない）
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),		//ファイルアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//画面サイズの構造体

	//変数宣言
	HWND hWnd;						//ウィンドルハンドル（認別子）
	MSG msg;						//メッセージを格納する変数
	DWORD dwCurrentTime;			//現在時刻
	DWORD dwExecLastTime;			//最後に処理した時刻
	DWORD dwFrameCount;				//フレームカウント
	DWORD dwFPSLastTime;			//最後にFPSを計測した時刻
	dwFrameCount = 0;				//フレームカウントを初期化
	dwFPSLastTime = timeGetTime();	//現在時刻を取得

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上X座標
		CW_USEDEFAULT,				//ウィンドウの左上Y座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは子ウィンドウID
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;				//初期化する
	dwExecLastTime = timeGetTime();	//現在の時刻を取得（保存）

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);	//ウィンドウ表示状態を設定
	UpdateWindow(hWnd);			//クライアント領域を更新

	//メッセージをループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windosの処理
			if (msg.message == WM_QUIT)
			{//WM_メッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージを設定
				TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);	//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();	
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//FPSを計測した時刻を保存
				dwFrameCount = 0;				//フレームカウントを加算
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000/60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;	//処理開始の時刻[現在時刻]を保存
				//更新処理
				Update();
				//描画処理
				Draw();
				dwFrameCount++;					//フレームカウントを加算
			}

		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//リターン
	return(int)msg.wParam;
}

//=====================================
//=	ウィンドウプロシージャ
//=====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//変数宣言
	int nID;	//返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:	//ウィンドウ破棄のメッセージ
		//WM_QUIZメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:	//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:	//[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを破棄する（WN_DESTROYメッセージを送る）
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_LBUTTONDOWN:	//マウス右クリックのメッセージ
		//対象ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;
	case WM_CLOSE:	//閉じるボタンのメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウを破棄する（WN_DESTROYメッセージを送る）
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//0を返さないと終了してします
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//現在の処理を繰り返す
}

//=====================================
//=	初期化処理
//=====================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンラーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現存のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	
	//デバイスのプレゼンパラメーターを設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				//ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				//ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3dpp.BackBufferFormat;	//バックバッファの形式
	d3dpp.BackBufferCount = 1;							//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			//ダブルバッファを切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;				//デプスバッファとスランシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;			//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;							//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz =					//リフレッシュレート
		D3DPRESENT_RATE_DEFAULT;						
	d3dpp.PresentationInterval =						//インターバル
		D3DPRESENT_INTERVAL_DEFAULT;					

	//Dirext3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステート設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND ,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定				
	//テクスチャの縮小補間の設定
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_MINFILTER,
		D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_MAGFILTER,
		D3DTEXF_LINEAR);
	//テクスチャの繰り返し
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_ADDRESSU,
		D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_ADDRESSV,
		D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定		//テクスチャとポリゴンの透明度をブレンド
	g_pD3DDevice->SetTextureStageState(
		0,
		D3DTSS_ALPHAOP,
		D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(
		0,
		D3DTSS_ALPHAARG1,
		D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(
		0,
		D3DTSS_ALPHAARG2,
		D3DTA_CURRENT);

	//デバック表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "termial", &g_pFont);
	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ライトの初期化処理
	InitLight();

	//影の初期化処理
	InitShadow();

	//地面の初期化処理
	InitField();

	//壁の初期化処理
	InitWall();

	//メッシュフィールドの初期化
	InitMeshField();

	//メッシュウォールの初期化処理
	InitMeshWall();

	{
		SetWall(D3DXVECTOR3(0.0f,            100.0f,  POLYGON_SIZE_Z),D3DXVECTOR3(0.0f,  0.0f,           0.0f));
		SetWall(D3DXVECTOR3(0.0f,            100.0f, -POLYGON_SIZE_Z),D3DXVECTOR3(0.0f, -D3DX_PI,        0.0f));
		SetWall(D3DXVECTOR3( POLYGON_SIZE_X, 100.0f, 0.0f),           D3DXVECTOR3(0.0f,  D3DX_PI * 0.5f, 0.0f));
		SetWall(D3DXVECTOR3(-POLYGON_SIZE_X, 100.0f, 0.0f),           D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	}

	//モデルの初期化処理
	InitModel();

	//プレイヤーの初期化処理
	InitPlayer();

	//カメラの初期化処理
	InitCamera();

	//ビルボードの初期化処理
	InitBillboard();

	{
		//SetBillboard(D3DXVECTOR3(50.0f, 30.0f, 0.0f));
	}

	//弾の初期化処理
	InitBullet();

	//エフェクトの初期化処理
	InitEffect();

	//パーティクルの初期化処理
	InitParticle();

	//爆発の初期化処理
	InitExplosion();

	return S_OK;
}

//=====================================
//=	終了処理
//=====================================
void Uninit(void)
{
	//影の終了処理
	UninitShadow();

	//地面の終了処理
	UninitField();

	//壁の終了処理
	UninitWall();

	////メッシュフィールドの終了処理
	//UninitMeshField();

	////メッシュウォールの終了処理
	//UninitMeshWall();

	//モデルの終了処理
	UninitModel();

	//プレイヤーの終了処理
	UninitPlayer();

	//ビルボードの終了処理
	UninitBillboard();

	//弾の終了処理
	UninitBullet();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//爆発の終了処理
	UninitExplosion();

	//キーボードの終了処理
	UninitKeyboard();

	//デバック表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D -> Release();
		g_pD3D = NULL;
	}


}

//=====================================
//= 更新処理
//=====================================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//カメラの更新処理
	UpdateCamera();

	//地面の更新処理
	UpdateField();

	//壁の更新処理
	UpdateWall();

	////メッシュフィールドの更新処理
	//UpdateMeshField();

	////メッシュウォールの更新処理
	//UpdateMeshWall();

	//モデルの更新処理
	UpdateModel();

	//プレイヤーの更新処理
	UpdatePlayer();

	//ビルボードの更新処理
	UpdateBillboard();

	//エフェクトの更新処理
	UpdateEffect();

	//パーティクルの更新処理
	UpdateParticle();
	
	//弾の更新処理
	UpdateBullet();

	//爆発の更新処理
	UpdateExplosion();

	//影の更新処理
	UpdateShadow();

	//デバックメニューのON/OFF
	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		if (g_bDsipDehug == false)
		{
			g_bDsipDehug = true;
		}
		else if (g_bDsipDehug == true)
		{
			g_bDsipDehug = false;
		}
	}

}

//=====================================
//= 描画処理
//=====================================
void Draw(void)
{
	//画面クリア（バックバッファとZバッファをクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		{
			//カメラの設定処理
			SetCamera();

			//地面の描画処理
			DrawField();

			//壁の描画処理
			DrawWall();

			////メッシュフィールドの描画処理
			//DrawMeshField();

			////メッシュウォールの描画処理
			//DrawMeshWall();

			//ビルボードの描画処理
			DrawBillboard();

			//モデルの描画処理
			DrawModel();

			//プレイヤーの描画処理
			DrawPlayer();

			//弾の描画処理
			DrawBullet();
			
			//エフェクトの描画処理
			DrawEffect();

			//パーティクルの描画処理
			DrawParticle();

			//爆発の描画処理
			DrawExplosion();

			//影の描画処理
			DrawShadow();

#ifdef _DEBUG
			//デバックメニュー
			if (g_bDsipDehug == true)
			{
				//デバックの表示
				DrawDebug(g_pFont);

				//FPSの表示
				DrawFPS();
			}
#endif
		}

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);


}

//=====================================
//= FPSの情報をテキストで表示
//=====================================
void DrawFPS(void)
{
	RECT rect = { SCREEN_WIDTH - 75,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列を代入
	wsprintf(&aStr[0], "FPS：%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

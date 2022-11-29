
//=======================
//=
//= DirectX�̊�{����[main.cpp]
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

//�}�N����`
#define CLASS_NAME			"Window class"				//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME			"3D"						//�E�B���h�E�̖��O

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;				//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;					//FPS�J�E���^		
bool g_bDsipDehug = false;				//�f�o�b�N��Ԃ�ON/OFF

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=====================================
//=	���C���֐�
//=====================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLime, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�B���h�E�̃X�^�C��
		WindowProc,							//�E�B���h�E�v���V�[�W��
		0,									//0�ɂ���i�ʏ�͂��悤���Ȃ��j
		0,									//0�ɂ���i�ʏ�͂��悤���Ȃ��j
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),		//�t�@�C���A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����

	//�ϐ��錾
	HWND hWnd;						//�E�B���h���n���h���i�F�ʎq�j
	MSG msg;						//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;			//���ݎ���
	DWORD dwExecLastTime;			//�Ō�ɏ�����������
	DWORD dwFrameCount;				//�t���[���J�E���g
	DWORD dwFPSLastTime;			//�Ō��FPS���v����������
	dwFrameCount = 0;				//�t���[���J�E���g��������
	dwFPSLastTime = timeGetTime();	//���ݎ������擾

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,				//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),	//�E�B���h�E�̕�
		(rect.bottom - rect.top),	//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�B���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;				//����������
	dwExecLastTime = timeGetTime();	//���݂̎������擾�i�ۑ��j

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	//�E�B���h�E�\����Ԃ�ݒ�
	UpdateWindow(hWnd);			//�N���C�A���g�̈���X�V

	//���b�Z�[�W�����[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windos�̏���
			if (msg.message == WM_QUIT)
			{//WM_���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W��ݒ�
				TranslateMessage(&msg);	//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();	
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//FPS���v������������ۑ�
				dwFrameCount = 0;				//�t���[���J�E���g�����Z
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000/60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;	//�����J�n�̎���[���ݎ���]��ۑ�
				//�X�V����
				Update();
				//�`�揈��
				Draw();
				dwFrameCount++;					//�t���[���J�E���g�����Z
			}

		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//���^�[��
	return(int)msg.wParam;
}

//=====================================
//=	�E�B���h�E�v���V�[�W��
//=====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�ϐ��錾
	int nID;	//�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:	//�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIZ���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:	//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	//[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������iWN_DESTROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_LBUTTONDOWN:	//�}�E�X�E�N���b�N�̃��b�Z�[�W
		//�ΏۃE�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	case WM_CLOSE:	//����{�^���̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������iWN_DESTROY���b�Z�[�W�𑗂�j
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//���݂̏������J��Ԃ�
}

//=====================================
//=	����������
//=====================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[�����[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�����̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	
	//�f�o�C�X�̃v���[���p�����[�^�[��ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				//�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				//�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3dpp.BackBufferFormat;	//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;							//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			//�_�u���o�b�t�@��؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;				//�f�v�X�o�b�t�@�ƃX�����V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;			//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;							//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz =					//���t���b�V�����[�g
		D3DPRESENT_RATE_DEFAULT;						
	d3dpp.PresentationInterval =						//�C���^�[�o��
		D3DPRESENT_INTERVAL_DEFAULT;					

	//Dirext3D�f�o�C�X�̐���
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

	//�����_�[�X�e�[�g�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND ,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�				
	//�e�N�X�`���̏k����Ԃ̐ݒ�
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_MINFILTER,
		D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_MAGFILTER,
		D3DTEXF_LINEAR);
	//�e�N�X�`���̌J��Ԃ�
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_ADDRESSU,
		D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(
		0,
		D3DSAMP_ADDRESSV,
		D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�		//�e�N�X�`���ƃ|���S���̓����x���u�����h
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

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "termial", &g_pFont);
	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//���C�g�̏���������
	InitLight();

	//�e�̏���������
	InitShadow();

	//�n�ʂ̏���������
	InitField();

	//�ǂ̏���������
	InitWall();

	//���b�V���t�B�[���h�̏�����
	InitMeshField();

	//���b�V���E�H�[���̏���������
	InitMeshWall();

	{
		SetWall(D3DXVECTOR3(0.0f,            100.0f,  POLYGON_SIZE_Z),D3DXVECTOR3(0.0f,  0.0f,           0.0f));
		SetWall(D3DXVECTOR3(0.0f,            100.0f, -POLYGON_SIZE_Z),D3DXVECTOR3(0.0f, -D3DX_PI,        0.0f));
		SetWall(D3DXVECTOR3( POLYGON_SIZE_X, 100.0f, 0.0f),           D3DXVECTOR3(0.0f,  D3DX_PI * 0.5f, 0.0f));
		SetWall(D3DXVECTOR3(-POLYGON_SIZE_X, 100.0f, 0.0f),           D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	}

	//���f���̏���������
	InitModel();

	//�v���C���[�̏���������
	InitPlayer();

	//�J�����̏���������
	InitCamera();

	//�r���{�[�h�̏���������
	InitBillboard();

	{
		//SetBillboard(D3DXVECTOR3(50.0f, 30.0f, 0.0f));
	}

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�����̏���������
	InitExplosion();

	return S_OK;
}

//=====================================
//=	�I������
//=====================================
void Uninit(void)
{
	//�e�̏I������
	UninitShadow();

	//�n�ʂ̏I������
	UninitField();

	//�ǂ̏I������
	UninitWall();

	////���b�V���t�B�[���h�̏I������
	//UninitMeshField();

	////���b�V���E�H�[���̏I������
	//UninitMeshWall();

	//���f���̏I������
	UninitModel();

	//�v���C���[�̏I������
	UninitPlayer();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�����̏I������
	UninitExplosion();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D -> Release();
		g_pD3D = NULL;
	}


}

//=====================================
//= �X�V����
//=====================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�J�����̍X�V����
	UpdateCamera();

	//�n�ʂ̍X�V����
	UpdateField();

	//�ǂ̍X�V����
	UpdateWall();

	////���b�V���t�B�[���h�̍X�V����
	//UpdateMeshField();

	////���b�V���E�H�[���̍X�V����
	//UpdateMeshWall();

	//���f���̍X�V����
	UpdateModel();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�p�[�e�B�N���̍X�V����
	UpdateParticle();
	
	//�e�̍X�V����
	UpdateBullet();

	//�����̍X�V����
	UpdateExplosion();

	//�e�̍X�V����
	UpdateShadow();

	//�f�o�b�N���j���[��ON/OFF
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
//= �`�揈��
//=====================================
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@���N���A�j
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		{
			//�J�����̐ݒ菈��
			SetCamera();

			//�n�ʂ̕`�揈��
			DrawField();

			//�ǂ̕`�揈��
			DrawWall();

			////���b�V���t�B�[���h�̕`�揈��
			//DrawMeshField();

			////���b�V���E�H�[���̕`�揈��
			//DrawMeshWall();

			//�r���{�[�h�̕`�揈��
			DrawBillboard();

			//���f���̕`�揈��
			DrawModel();

			//�v���C���[�̕`�揈��
			DrawPlayer();

			//�e�̕`�揈��
			DrawBullet();
			
			//�G�t�F�N�g�̕`�揈��
			DrawEffect();

			//�p�[�e�B�N���̕`�揈��
			DrawParticle();

			//�����̕`�揈��
			DrawExplosion();

			//�e�̕`�揈��
			DrawShadow();

#ifdef _DEBUG
			//�f�o�b�N���j���[
			if (g_bDsipDehug == true)
			{
				//�f�o�b�N�̕\��
				DrawDebug(g_pFont);

				//FPS�̕\��
				DrawFPS();
			}
#endif
		}

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);


}

//=====================================
//= FPS�̏����e�L�X�g�ŕ\��
//=====================================
void DrawFPS(void)
{
	RECT rect = { SCREEN_WIDTH - 75,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//���������
	wsprintf(&aStr[0], "FPS�F%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

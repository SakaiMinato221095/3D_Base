
//=======================
//=
//= ���͂̏���[Input.h]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "Input.h"

//�}�N����`
#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃u���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���

//=====================================
//= �L�[�{�[�h�̏���������
//=====================================
HRESULT InitKeyboard(HINSTANCE hInstanse, HWND hWnd)
{
	//DivectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstanse,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pInput,NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�@�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	
	return S_OK;
}

//=====================================
//= �L�[�{�[�h�̏I������
//=====================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X��j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================
//= �L�[�{�[�h�̍X�V����
//=====================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	int nCutKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (nCutKey = 0; nCutKey < NUM_KEY_MAX; nCutKey++)
		{
			g_aKeyStateTrigger[nCutKey] = (g_aKeyState[nCutKey] ^ aKeyState[nCutKey]) & aKeyState[nCutKey];		//�L�[�{�[�h�̃g���K�[���
			g_aKeyStateRelease[nCutKey] = (aKeyState[nCutKey] ^ g_aKeyState[nCutKey]) & g_aKeyState[nCutKey];	//�L�[�{�[�h�̃����[�X���
			g_aKeyState[nCutKey] = aKeyState[nCutKey];															//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=====================================
//= �L�[�{�[�h�̃u���X�̏����擾
//=====================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
//= �L�[�{�[�h�̃g���K�[�̏����擾
//=====================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================
//= �L�[�{�[�h�̃����[�X�̏����擾
//=====================================
bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
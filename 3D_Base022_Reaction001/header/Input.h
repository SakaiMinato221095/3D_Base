
//=======================
//=
//= DirectX�̓��͂̃w�b�^�[[Input.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _INPUT_H_	//���̃}�N������`����Ȃ�������
#define _INPUT_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstanse,HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

#endif 
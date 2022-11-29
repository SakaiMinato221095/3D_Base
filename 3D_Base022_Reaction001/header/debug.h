
//=======================
//=
//= �f�o�b�N�̃w�b�^�[[camera.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _DEBUG_H_	//���̃}�N������`����Ȃ�������
#define _DEBUG_H_	//��d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//�f�o�b�N�e�L�X�g�J�E���g�̌v�Z�̗񋓌^
typedef enum
{
	DEBUG_TEXT_COUNT_CAL_ADD = 0,
	DEBUG_TEXT_COUNT_CAL_SUB,
}DebugTextCountCal;

//�v���g�^�C�v�錾
void InitDebug(void);
void UninitDebug(void);
void UpdateDebug(void);
void DrawDebug(LPD3DXFONT pFont);
int DebugCalTextCount(DebugTextCountCal Cal);

#endif 

//=======================
//=
//= �f�o�b�N����[debug.cpp]
//= Author Sakai Minato
//=
//=======================

#include <stdio.h>

#include "main.h"
#include "debug.h"

#include "camera.h"
#include "player.h"
#include "bullet.h"
#include "wall.h"

//�v���g�^�C�v�錾
void DrawDebugPlayer(LPD3DXFONT pFont);
void DrawDebugCamera(LPD3DXFONT pFont);
void DrawDebugBullet(LPD3DXFONT pFont);
void DrawDebugWall(LPD3DXFONT pFont);

//�O���[�o���ϐ��錾
int g_nDebugTextCount;



//=====================================
//= �f�o�b�N�̏���������
//=====================================
void InitDebug(void)
{
	//�O���[�o���ϐ��̏�����
	g_nDebugTextCount = 0;
}

//=====================================
//= �f�o�b�N�̏I������
//=====================================
void UninitDebug(void)
{

}

//=====================================
//= �f�o�b�N�̍X�V����
//=====================================
void UpdateDebug(void)
{

}

//=====================================
//= �f�o�b�N�̕`�揈��
//=====================================
void DrawDebug(LPD3DXFONT pFont)
{
	//�v���C���[
	DrawDebugPlayer(pFont);

	//�J����
	DrawDebugCamera(pFont);

	//�e
	DrawDebugBullet(pFont);

	//��
	DrawDebugWall(pFont);
}

//=====================================
//= �f�o�b�N�J�E���g�̌v�Z
//=====================================
int DebugCalTextCount(DebugTextCountCal Cal)
{
	//�f�o�b�N�e�L�X�g�J�E���g�̌v�Z
	switch (Cal)
	{
	case DEBUG_TEXT_COUNT_CAL_ADD:
		g_nDebugTextCount++;
		break;
	case DEBUG_TEXT_COUNT_CAL_SUB:
		g_nDebugTextCount--;
		break;
	}
	
	return g_nDebugTextCount;

}

//=====================================
//= �f�o�b�N�J�����̏���\��
//=====================================
void DrawDebugCamera(LPD3DXFONT pFont)
{
	//�J�����̏����擾
	Camera *pCamera = GetCamera();

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[5][256];

	//���������
	wsprintf(&aStr[0][0], "=========�J����==========");
	wsprintf(&aStr[1][0], "\n�����_��	  X(%d) Y(%d) Z(%d)\n", (int)pCamera->posV.x, (int)pCamera->posV.y, (int)pCamera->posV.z);
	wsprintf(&aStr[2][0], "\n\n�������_�� X(%d) Y(%d) Z(%d)\n", (int)pCamera->posR.x, (int)pCamera->posR.y, (int)pCamera->posR.z);
	sprintf(&aStr[3][0], "\n\n\n����]�� Y(%2.2f) \n", pCamera->rot.y);
	sprintf(&aStr[4][0], "\n\n\n\n���ړI�̌����� Y(%2.2f) \n", pCamera->rotDest.y);

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[4][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//=====================================
//= �f�o�b�N�v���C���[�̏���\��
//=====================================
void DrawDebugPlayer(LPD3DXFONT pFont)
{
	//�J�����̏����擾
	Player *pPlayer = GetPlayer();

	RECT rect = { 0,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[6][256];

	//���������
	sprintf(&aStr[0][0], "=========�v���C���[==========");
	sprintf(&aStr[1][0], "\n���ʒu�� X(%3.1f) Y(%3.1f) Z(%3.1f)\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	sprintf(&aStr[2][0], "\n\n���O��ʒu�� X(%3.1f) Y(%3.1f) Z(%3.1f)\n", pPlayer->posOld.x, pPlayer->posOld.y, pPlayer->posOld.z);
	sprintf(&aStr[3][0], "\n\n\n���ړ��ʁ� X(%2.2f) Y(%2.2f) Z(%2.2f)\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);
	sprintf(&aStr[4][0], "\n\n\n\n�������� Y(%2.2f)", pPlayer->rot.y);
	sprintf(&aStr[5][0], "\n\n\n\n\n���ړI�̌����� Y(%2.2f)", pPlayer->rotDest.y);

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[4][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[5][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//=====================================
//= �f�o�b�N�o���b�g�̏���\��
//=====================================
void DrawDebugBullet(LPD3DXFONT pFont)
{
	//�J�����̏����擾
	Bullet *pBullet = GetBullet();

	//�ϐ��錾
	int nCutBullet;
	int BulletNumber = 0;

	for (nCutBullet = 0; nCutBullet < BULLET_MAX; nCutBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			BulletNumber++;
		}
	}

	pBullet -= BULLET_MAX;

	RECT rect = { 0,250,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[5][256];

	//���������
	wsprintf(&aStr[0][0], "=========�e==========");
	wsprintf(&aStr[1][0], "\n�����ː��� %d", BulletNumber);
	wsprintf(&aStr[2][0], "\n\n���ʒu�� X(%d) Y(%d) Z(%d)\n", (int)pBullet->pos.x, (int)pBullet->pos.y, (int)pBullet->pos.z);
	wsprintf(&aStr[3][0], "\n\n\n���ړ��ʁ� X(%d) Y(%d) Z(%d)\n", (int)pBullet->move.x, (int)pBullet->move.y, (int)pBullet->move.z);
	wsprintf(&aStr[4][0], "\n\n\n\n�������� LIFE(%d)\n", pBullet->nLife);

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[4][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//=====================================
//= �f�o�b�N�E�H�[���̏���\��
//=====================================
void DrawDebugWall(LPD3DXFONT pFont)
{
	//�J�����̏����擾
	Wall *pWall = GetWall();

	//�ϐ��錾
	int WallNumber = 0;

	RECT rect = { 0,350,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[5][256];

	//���������
	wsprintf(&aStr[0][0], "=========��==========");
	wsprintf(&aStr[1][0], "\n�����ː��� %d", WallNumber);
	wsprintf(&aStr[2][0], "\n\n���ʒu�� X(%d) Y(%d) Z(%d)\n", (int)pWall->pos.x, (int)pWall->pos.y, (int)pWall->pos.z);
	wsprintf(&aStr[3][0], "\n\n\n���ړ��ʁ� X(%d) Y(%d) Z(%d)\n", (int)pWall->size.x, (int)pWall->size.x, (int)pWall->size.x);

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[1][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[2][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	pFont->DrawText(NULL, &aStr[3][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
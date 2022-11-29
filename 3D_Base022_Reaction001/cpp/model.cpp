
//=======================
//=
//= ���f���̏���[model.cpp]
//= Author Sakai Minato
//=
//=======================

#include "main.h"
#include "model_object.h"
#include "model_enemy.h"

//====================================
//= ���f���̏���������
//=====================================
void InitModel(void)
{
	//�I�u�W�F�N�g
	InitModelObject();

	//�G�l�~�[
	InitModelEnemy();
}

//=====================================
//= ���f���̏I������
//=====================================
void UninitModel(void)
{
	//�I�u�W�F�N�g
	UninitModelObject();

	//�G�l�~�[
	UninitModelEnemy();
}

//=====================================
//= ���f���̍X�V����
//=====================================
void UpdateModel(void)
{
	//�I�u�W�F�N�g
	UpdateModelObject();

	//�G�l�~�[
	UpdateModelEnemy();
}

//=====================================
//= ���f���̕`�揈��
//=====================================
void DrawModel(void)
{
	//�I�u�W�F�N�g
	DrawModelObject();

	//�G�l�~�[
	DrawModelEnemy();
}



//=======================
//=
//= �ǂ̃w�b�^�[[polygon.h]
//= Author Sakai Minato
//=
//=======================

#ifndef _WALL_H_	//���̃}�N������`����Ȃ�������
#define _WALL_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//�}�N��
#define WALL_SIZE_X	(500.0f)	//�|���S���̑傫���iX���j
#define WALL_SIZE_Y	(110.0f)	//�|���S���̑傫���iY���j
#define WALL_SIZE_Z	(500.0f)	//�|���S���̑傫���iZ���j

//�ǂ̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 size;		//�傫��
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool CollisionWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, Wall **pWall);
Wall *GetWall(void);

#endif 
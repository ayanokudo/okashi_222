//=============================================================================
//
// �O���b�h�w�b�_ [grid.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GRID_H_
#define _GRID_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
//�}�N����`
//*****************************
#define GRID_SIZE                   (60.0f)        // �O���b�h�̑傫��
#define MAX_GRID                    (800) // �O���b�h�̐�

//*****************************
//�N���X��`
//*****************************
class CGrid : public CScene3d
{
public:
	//���̃e�N�X�`���̎��
	typedef enum
	{
		FLOOR_FLOORING = 0,	//�t���[�����O
		FLOOR_MAT,			//�}�b�g
		FLOOR_KITCHEN,		//�L�b�`��
		FLOOR_MAX,			
	}FLOOR;

	//�����o�֐�
	CGrid();
	~CGrid();
	static CGrid * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//�����o�ϐ�
    static D3DXVECTOR2 m_UV[NUM_VERTEX];// �e�N�X�`�����W�̏��
	static LPDIRECT3DTEXTURE9 m_apTexture[FLOOR_MAX];//�e�N�X�`��
	FLOOR m_type;
};

#endif 
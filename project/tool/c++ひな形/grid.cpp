//===================================================
//
//    �O���b�h�̏���[grid.cpp]
//    Author:����@�r�H
//
//====================================================
//**********************************
//�C���N���[�h
//**********************************
#include "grid.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// �}�N����`
//*****************************
#define FLOOR_FLOORING_TEXTURE_PATH "./data/Textures/check.png"    //�t���[�����O�̃e�N�X�`���̃p�X
#define FLOOR_MAT_TEXTURE_PATH		"./data/Textures/check.png"	   //�܂��Ƃ̃e�N�X�`���̃p�X
#define FLOOR_KITCHEN_TEXTURE_PATH  "./data/Textures/check.png"    //�L�b�`���̏��̃e�N�X�`���̃p�X

//==================================
// �R���X�g���N�^
//==================================
LPDIRECT3DTEXTURE9 CGrid::m_apTexture[FLOOR_MAX] = {};
D3DXVECTOR2 CGrid::m_UV[NUM_VERTEX] = {
    { 0.0f * MAX_GRID / 2 ,0.0f * MAX_GRID / 2 },
    { 1.0f * MAX_GRID / 2 ,0.0f * MAX_GRID / 2 },
    { 0.0f * MAX_GRID / 2 ,1.0f * MAX_GRID / 2 },
    { 1.0f * MAX_GRID / 2 ,1.0f * MAX_GRID / 2 }
};
//==================================
// �R���X�g���N�^
//==================================
CGrid::CGrid()
{
	m_type = FLOOR_FLOORING;	//���̎�ނ̏�����
}

//==================================
// �f�X�g���N�^
//==================================
CGrid::~CGrid()
{
}

//==================================
// ��������
//==================================
CGrid * CGrid::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type)
{
	//CGrid�̃|�C���^�쐬
	CGrid *pFloor;
	//�C���X�^���X�𐶐�
	pFloor = new CGrid;
	//NULL�`�F�b�N
	if (pFloor != NULL)
	{
		//���ꂼ��̏���������
		pFloor->Init();
		pFloor->m_type = type;
		pFloor->SetPos(pos);
		pFloor->SetSize(size);
		pFloor->SetObjType(OBJTYPE_MAP);
	}
	//�|�C���^��Ԃ�
	return pFloor;
}

//==================================
// �e�N�X�`�����[�h����
//==================================
HRESULT CGrid::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, FLOOR_FLOORING_TEXTURE_PATH, &m_apTexture[FLOOR_FLOORING]);
	D3DXCreateTextureFromFile(pDevice, FLOOR_MAT_TEXTURE_PATH,		&m_apTexture[FLOOR_MAT]);
	D3DXCreateTextureFromFile(pDevice, FLOOR_KITCHEN_TEXTURE_PATH,  &m_apTexture[FLOOR_KITCHEN]);

	return S_OK;
}

//==================================
// �e�N�X�`���j��
//==================================
void CGrid::Unload(void)
{
	for (int nCntFloor = 0; nCntFloor < FLOOR_MAX; nCntFloor++)
	{
		// �e�N�X�`���̉������
		if (m_apTexture[nCntFloor] != NULL)
		{
			m_apTexture[nCntFloor]->Release();
			m_apTexture[nCntFloor] = NULL;
		}
	}
}

//==================================
// ����������
//==================================
HRESULT CGrid::Init(void)
{
	CScene3d::Init();
    SetTextureUV(m_UV);
	CScene3d::BindTexture(m_apTexture[m_type]);
	return S_OK;
}

//==================================
// �I������
//==================================
void CGrid::Uninit(void)
{
	CScene3d::Uninit();
}

//==================================
// �X�V����
//==================================
void CGrid::Update(void)
{
}

//==================================
// �`�揈��
//==================================
void CGrid::Draw(void)
{
	CScene3d::Draw();
}

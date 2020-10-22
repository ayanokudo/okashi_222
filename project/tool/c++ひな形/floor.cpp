//===================================================
//
//    ���̏���[floor.cpp]
//    Author:����@�r�H
//
//====================================================
//**********************************
//�C���N���[�h
//**********************************
#include "floor.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// �}�N����`
//*****************************
#define FLOOR_FLOORING_TEXTURE_PATH "./data/Textures/particle001.png"    //�t���[�����O�̃e�N�X�`���̃p�X
#define FLOOR_MAT_TEXTURE_PATH		"./data/Textures/particle001.png"	 //�܂��Ƃ̃e�N�X�`���̃p�X
#define FLOOR_KITCHEN_TEXTURE_PATH  "./data/Textures/particle001.png"    //�L�b�`���̏��̃e�N�X�`���̃p�X

//==================================
// �R���X�g���N�^
//==================================
LPDIRECT3DTEXTURE9 CFloor::m_apTexture[FLOOR_MAX] = {};

//==================================
// �R���X�g���N�^
//==================================
CFloor::CFloor()
{
	m_type = FLOOR_FLOORING;	//���̎�ނ̏�����
}

//==================================
// �f�X�g���N�^
//==================================
CFloor::~CFloor()
{
}

//==================================
// ��������
//==================================
CFloor * CFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type)
{
	//CFloor�̃|�C���^�쐬
	CFloor *pFloor;
	//�C���X�^���X�𐶐�
	pFloor = new CFloor;
	//NULL�`�F�b�N
	if (pFloor != NULL)
	{
		//���ꂼ��̏���������
		pFloor->Init();
		pFloor->m_type = type;
		pFloor->SetPos(pos);
		pFloor->SetSize(size);
		pFloor->SetObjType(OBJTYPE_FLOOR);
	}
	//�|�C���^��Ԃ�
	return pFloor;
}

//==================================
// �e�N�X�`�����[�h����
//==================================
HRESULT CFloor::Load(void)
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
void CFloor::Unload(void)
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
HRESULT CFloor::Init(void)
{
	CScene3d::Init();
	CScene3d::BindTexture(m_apTexture[m_type]);
	return S_OK;
}

//==================================
// �I������
//==================================
void CFloor::Uninit(void)
{
	CScene3d::Uninit();
}

//==================================
// �X�V����
//==================================
void CFloor::Update(void)
{
}

//==================================
// �`�揈��
//==================================
void CFloor::Draw(void)
{
	CScene3d::Draw();
}

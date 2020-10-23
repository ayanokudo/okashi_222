//===================================================
//
//    �ǂ̏���[wall.cpp]
//    Author:����@�r�H
//
//====================================================
//**********************************
//�C���N���[�h
//**********************************
#include "wall.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// �}�N����`
//*****************************
#define WALL_1_TEXTURE_PATH		"./data/Textures/floor000.png"		 // �t���[�����O�̃e�N�X�`���̃p�X
#define WALL_2_TEXTURE_PATH		"./data/Textures/particle001.png"	 // �܂��Ƃ̃e�N�X�`���̃p�X
#define WALL_3_TEXTURE_PATH		"./data/Textures/particle001.png"    // �L�b�`���̏��̃e�N�X�`���̃p�X

//==================================
// �R���X�g���N�^
//==================================
LPDIRECT3DTEXTURE9 CWall::m_apTexture[WALL_MAX] = {};

//==================================
// �R���X�g���N�^
//==================================
CWall::CWall():CScene3d(OBJTYPE_WALL)
{
	m_type   =   WALL_1;			// ���̎�ނ̏�����
	m_pos    =	{ 0.0f,0.0f,0.0f };	// pos�̏�����
	m_posold =	{ 0.0f,0.0f,0.0f };	// �O�̈ʒu�̏�����
	m_size   =	{ 0.0f,0.0f,0.0f };	// size�̏�����
}

//==================================
// �f�X�g���N�^
//==================================
CWall::~CWall()
{
}

//==================================
// ��������
//==================================
CWall * CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, WALL type)
{
	//�C���X�^���X�𐶐�
	CWall *pWall = new CWall;
	//NULL�`�F�b�N
	if (pWall != NULL)
	{
		//���ꂼ��̏���������
		pWall->Init();
		pWall->m_type = type;
		pWall->m_pos = pos;
		pWall->SetPos(pos);
		pWall->m_size = size;
		pWall->SetSize(size);
		pWall->SetObjType(OBJTYPE_WALL);
	}
	//�|�C���^��Ԃ�
	return pWall;
}

//==================================
// �e�N�X�`�����[�h����
//==================================
HRESULT CWall::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, WALL_1_TEXTURE_PATH, &m_apTexture[WALL_1]);
	D3DXCreateTextureFromFile(pDevice, WALL_2_TEXTURE_PATH, &m_apTexture[WALL_2]);
	D3DXCreateTextureFromFile(pDevice, WALL_3_TEXTURE_PATH, &m_apTexture[WALL_3]);

	return S_OK;
}

//==================================
// �e�N�X�`���j��
//==================================
void CWall::Unload(void)
{
	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		// �e�N�X�`���̉������
		if (m_apTexture[nCntWall] != NULL)
		{
			m_apTexture[nCntWall]->Release();
			m_apTexture[nCntWall] = NULL;
		}
	}
}

//==================================
// ����������
//==================================
HRESULT CWall::Init(void)
{
	CScene3d::Init();
	CScene3d::BindTexture(m_apTexture[m_type]);
	return S_OK;
}

//==================================
// �I������
//==================================
void CWall::Uninit(void)
{
	CScene3d::Uninit();
}

//==================================
// �X�V����
//==================================
void CWall::Update(void)
{
	Colision(CScene::OBJTYPE_PLAYER, m_pos, m_posold, m_size);
}

//==================================
// �`�揈��
//==================================
void CWall::Draw(void)
{
	CScene3d::Draw();
}

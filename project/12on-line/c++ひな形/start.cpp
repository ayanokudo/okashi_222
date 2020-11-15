//===================================================
//
//    start�̏���[Start.cpp]
//    Author:���V ����
//
//====================================================
//**********************************
//�C���N���[�h
//**********************************
#include "start.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//*****************************
// �}�N����`
//*****************************
#define TEXTURE_PATH "./data/Textures/Start_Text.png"    //�t���[�����O�̃e�N�X�`���̃p�X
#define LOST_COUNT 50
#define SIZE D3DXVECTOR3(1313.0f, 394.0f, 0.0f)/4

//==================================
// �R���X�g���N�^
//==================================
LPDIRECT3DTEXTURE9 CStart::m_pTexture = {};

//==================================
// �R���X�g���N�^
//==================================
CStart::CStart() :CScene2d(OBJTYPE_UI)
{
	m_nCntLost = 0;
}

//==================================
// �f�X�g���N�^
//==================================
CStart::~CStart()
{
}

//==================================
// ��������
//==================================
CStart * CStart::Create(void)
{
	//CStart�̃|�C���^�쐬
	CStart *pStart;
	//�C���X�^���X�𐶐�
	pStart = new CStart;
	//NULL�`�F�b�N
	if (pStart != NULL)
	{
		//���ꂼ��̏���������
		pStart->Init();
	}
	//�|�C���^��Ԃ�
	return pStart;
}

//==================================
// �e�N�X�`�����[�h����
//==================================
HRESULT CStart::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//==================================
// �e�N�X�`���j��
//==================================
void CStart::Unload(void)
{

	// �e�N�X�`���̉������
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================
// ����������
//==================================
HRESULT CStart::Init(void)
{
	CScene2d::Init();
	m_nCntLost = 0;
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	SetSize(SIZE);
	BindTexture(m_pTexture);

	
	return S_OK;
}

//==================================
// �I������
//==================================
void CStart::Uninit(void)
{
	CScene2d::Uninit();
}

//==================================
// �X�V����
//==================================
void CStart::Update(void)
{
	// �J�E���g��i�߂�
	m_nCntLost++;
	if (m_nCntLost > LOST_COUNT)
	{// ���J�E���g�ŏ���
		Uninit();
	}
	else
	{
		if (m_nCntLost == 10)
		{// SE
			CManager::GetSound()->Play(CSound::SOUND_SE_START);
		}
		if (m_nCntLost >= 20)
		{
			D3DXCOLOR minasCol =D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f);
			SetColor(GetColor() - minasCol);
		}
	}
}

//==================================
// �`�揈��
//==================================
void CStart::Draw(void)
{
	CScene2d::Draw();
}

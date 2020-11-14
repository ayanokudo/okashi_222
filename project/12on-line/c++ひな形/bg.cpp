//===================================================
//
//    �w�i�N���X�̏���[bg.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "camera.h"
#include "game.h"

//*****************************
// �}�N����`
//*****************************

// �e�N�X�`���̃p�X
#define BG_TEXTURE_PATH1 "./data/Textures/shibahu.png"
#define BG_TEXTURE_PATH2 "./data/Textures/sky.png"

#define SKY_SIZE D3DXVECTOR3(1200.0f,464.0f,0.0f)*30
#define SKY_POS D3DXVECTOR3(-15000.0f, 5000.0f, -55000.0f)

//**********************************
//�ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[BG_TEXTURE_NUM] = {};

//==================================
// �R���X�g���N�^
//==================================
CBg::CBg()
{
	// O�N���A
	memset(m_afTexMoveU, 0, sizeof(m_afTexMoveU));
	memset(m_afTexMoveV, 0, sizeof(m_afTexMoveV));
	memset(m_apScene3d, 0, sizeof(m_apScene3d));
}

//==================================
// �f�X�g���N�^
//==================================
CBg::~CBg()
{
}

//==================================
// �N���G�C�g
//==================================
CBg * CBg::Create(void)
{
	// �������̊m��
	CBg *pBg = new CBg;
	if (pBg != NULL)
	{
		// ����������
		pBg->Init();
	}

	return pBg;
}

//==================================
// ���[�h
//==================================
HRESULT CBg::Load(void)
{

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_PATH1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_PATH2, &m_apTexture[1]);
	return S_OK;
}

//==================================
// �A�����[�h
//==================================
void CBg::Unload(void)
{
	// �e�N�X�`�������A�e�N�X�`���̊J������
	for (int nCntTex = 0; nCntTex < BG_TEXTURE_NUM; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==================================
// ����������
//==================================
HRESULT CBg::Init(void)
{


	if (m_apScene3d[0] == NULL)
	{
		// �|���S������
		m_apScene3d[0] = CScene3d::Create(D3DXVECTOR3(-5900, -10, -8000), D3DXVECTOR3(800000, -10, 800000));
		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene3d[0]->SetObjType(OBJTYPE_BG);
		// �e�N�X�`�����蓖��
		m_apScene3d[0]->BindTexture(m_apTexture[0]);

		D3DXVECTOR2 UV[NUM_VERTEX];
		UV[0] = D3DXVECTOR2(0.0f, 0.0f);
		UV[1] = D3DXVECTOR2(8000.0f, 0.0f);
		UV[2] = D3DXVECTOR2(0.0f, 8000.0f);
		UV[3] = D3DXVECTOR2(8000.0f, 8000.0f);

		m_apScene3d[0]->SetTextureUV(UV);
	}
	else
	{
		return E_FAIL;
	}

	if (m_apScene3d[1] == NULL)
	{
		// �|���S������
		m_apScene3d[1] = CScene3d::Create(SKY_POS, SKY_SIZE);
		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene3d[1]->SetObjType(OBJTYPE_BG);
		// �e�N�X�`�����蓖��
		m_apScene3d[1]->BindTexture(m_apTexture[1]);

		D3DXVECTOR2 UV[NUM_VERTEX];
		UV[0] = D3DXVECTOR2(0.0f, 0.0f);
		UV[1] = D3DXVECTOR2(1.0f, 0.0f);
		UV[2] = D3DXVECTOR2(0.0f, 1.0f);
		UV[3] = D3DXVECTOR2(1.0f, 1.0f);

		m_apScene3d[1]->SetTextureUV(UV);
	}
	else
	{
		return E_FAIL;
	}



	return S_OK;
}

//==================================
// �I������
//==================================
void CBg::Uninit(void)
{
	// �w�i�̃p�[�c�����J������
	for (int nCntBg = 0; nCntBg < BG_PARTS_NUM; nCntBg++)
	{
		if (m_apScene3d[nCntBg] != NULL)
		{
			m_apScene3d[nCntBg]->Uninit();
			m_apScene3d[nCntBg] = NULL;
		}
	}

	// �J������
	Release();
}

//==================================
// �X�V����
//==================================
void CBg::Update(void)
{
}

//==================================
// �`�揈��
//==================================
void CBg::Draw(void)
{

}

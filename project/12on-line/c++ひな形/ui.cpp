//===================================================
//
//    UI�N���X�̏���[ui.cpp]
//    Author:����@�r�H
//
//====================================================

//**********************************
// �C���N���[�h
//**********************************
#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

//**********************************
// �}�N����`
//**********************************
#define UI_TIME_TEXTURE_PATH		"./data/Textures/TIME.png"			// �^�C���̃p�X
#define UI_TITLE_TEXTURE_PATH		"./data/Textures/title000.png"		// �^�C�g���̃p�X
#define UI_ENTER_TEXTURE_PATH		"./data/Textures/title000.png"		// �G���^�[�̃p�X
#define UI_WARNING_TEXTURE_PATH		"./data/Textures/TIME.png"			// ���[�j���O�̃p�X
#define UI_ATTACK_NAIL_TEXTURE_PATH	"./data/Textures/Attack.png"		// �A�^�b�N�̃p�X
#define UI_ATTACK_CRY_TEXTURE_PATH	"./data/Textures/Voice.png"			// �����̃p�X
#define UI_DASH_TEXTURE_PATH		"./data/Textures/Dash.png"			// �_�b�V���̃p�X
#define UI_CHOCO_TEXTURE_PATH		"./data/Textures/chocolate_HPicon.png"	// �`���R�̃p�X
#define UI_MILK_TEXTURE_PATH		"./data/Textures/Milk_HPicon.png"		// �~���N�̃p�X

#define UI_SIZE 100
//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CUi::m_apTexture[UI_MAX] = {};

//==================================
// �R���X�g���N�^
//==================================
CUi::CUi()
{
	m_pVtxBuff = NULL;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3();
	m_move = D3DXVECTOR3();
	m_type = UI_TIME;
}

//==================================
// �f�X�g���N�^
//==================================
CUi::~CUi()
{

}

//==================================
// �N���G�C�g
//==================================
CUi * CUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type)
{
	// �������̊m��
	CUi * pUi = new CUi;

	if (pUi != NULL)
	{
		// ����������
		pUi->Init(pos, size, col, type);
	}

	return pUi;
}

//==================================
// ���[�h
//==================================
HRESULT CUi::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, UI_TIME_TEXTURE_PATH, &m_apTexture[UI_TIME]);
	D3DXCreateTextureFromFile(pDevice, UI_TITLE_TEXTURE_PATH, &m_apTexture[UI_TITLE]);
	D3DXCreateTextureFromFile(pDevice, UI_ENTER_TEXTURE_PATH, &m_apTexture[UI_ENTER]);
	D3DXCreateTextureFromFile(pDevice, UI_WARNING_TEXTURE_PATH, &m_apTexture[UI_WARNING]);
	D3DXCreateTextureFromFile(pDevice, UI_ATTACK_CRY_TEXTURE_PATH, &m_apTexture[UI_ATTACK_NAIL]);
	D3DXCreateTextureFromFile(pDevice, UI_ATTACK_NAIL_TEXTURE_PATH, &m_apTexture[UI_ATTACK_CRY]);
	D3DXCreateTextureFromFile(pDevice, UI_DASH_TEXTURE_PATH, &m_apTexture[UI_DASH]);
	D3DXCreateTextureFromFile(pDevice, UI_CHOCO_TEXTURE_PATH, &m_apTexture[UI_CHOCO]);
	D3DXCreateTextureFromFile(pDevice, UI_MILK_TEXTURE_PATH, &m_apTexture[UI_MILK]);

	return S_OK;
}

//==================================
// �A�����[�h
//==================================
void CUi::Unload(void)
{
	for (int nCount = UI_TIME; nCount < UI_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//==================================
// ����������
//==================================
HRESULT CUi::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type)
{
	VERTEX_2D *pVtx;// ���_���|�C���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0);

	// �e�N�X�`��UV���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_col = col;
	m_type = type;
	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = m_col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================
// �I������
//==================================
void CUi::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==================================
// �X�V����
//==================================
void CUi::Update(void)
{

}

//==================================
// �`�揈��
//==================================
void CUi::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �A���t�@�e�X�g�̂������l�̕ύX
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);


	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_apTexture[m_type] != NULL)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_apTexture[m_type]);
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetTexture(0, 0);

	// �A���t�@�e�X�g�̂������l�����ǂ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}

//==================================
// �J���[�̃Z�b�g
//==================================
void CUi::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// ���_���|�C���^

	m_col = col;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
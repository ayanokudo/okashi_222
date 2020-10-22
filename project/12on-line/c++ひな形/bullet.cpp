////////////////////////////////////////////////////
//
//    bullet�N���X�̏���[bullet.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"

//*****************************
// �}�N����`
//*****************************
#define BULLET_TEXTURE_PATH "./data/Textures/" //�e�N�X�`���̃p�X

//******************************
// �ÓI�����o�ϐ��錾
//******************************
LPDIRECT3DTEXTURE9  CBullet::m_pTexture = NULL; // �e�N�X�`���|�C���^

//******************************
// �R���X�g���N�^
//******************************
CBullet::CBullet()
{
	// �ϐ��̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_user = BULLETUSER_PLAYER;
}

//******************************
// �f�X�g���N�^
//******************************
CBullet::~CBullet()
{
}

//******************************
// �N���G�C�g
//******************************
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user)
{
	// �������̊m��
	CBullet *pBullet;
	pBullet = new CBullet;
	// ������
	pBullet->Init();

	// �e�l�̑���E�Z�b�g
	pBullet->SetPos(pos);                // ���W
	pBullet->SetObjType(OBJTYPE_BULLET); // �I�u�W�F�N�g�^�C�v
	pBullet->m_move = move;              // �ړ���
	pBullet->m_nLife = nLife;            // ����
	pBullet->m_user = user;              // �o���b�g���[�U�[

	return pBullet;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CBullet::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_PATH, &m_pTexture);


	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CBullet::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//******************************
// ����������
//******************************
HRESULT CBullet::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindTexture(m_pTexture);
	// �T�C�Y�̐ݒ�
	SetSize(D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f));

	return S_OK;
}

//******************************
// �I������
//******************************
void CBullet::Uninit(void)
{
	CBillboard::Uninit();
}

//******************************
// �X�V����
//******************************
void CBullet::Update(void)
{
	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();
	// �ړ��ʂ̃v���X
	pos += m_move;
	// ���W�̃Z�b�g
	SetPos(pos);

	// ���������炷
	m_nLife--;
	if (m_nLife <= 0)
	{// ������0�ȉ��ɂȂ����Ƃ�
		// ����
		Uninit();
	}

	// �����蔻��
	CollisionBullet(m_user);
}

//******************************
// �`�揈��
//******************************
void CBullet::Draw(void)
{
	CBillboard::Draw();
}


//******************************
// �����蔻��
//******************************
void CBullet::CollisionBullet(BULLETUSER user)
{
}

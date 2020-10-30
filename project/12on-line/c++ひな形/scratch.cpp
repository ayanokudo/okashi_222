////////////////////////////////////////////////////
//
//    scratch�N���X�̏���[scratch.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "scratch.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "enemy.h"

//*****************************
// �}�N����`
//*****************************
#define SCRATCH_TEXTURE_PATH "./data/Textures/scratch.png" //�e�N�X�`���̃p�X
#define SCRATCH_COLOR D3DXCOLOR(1.0f,1.0f,0.3f,1.0f)       // �A�j���[�V�������x
#define SCRATCH_ANIM_SPEED 4                               // �A�j���[�V�������x
#define SCRATCH_MAX_ANIMATION_X 5                          // �A�j���[�V������ ��
#define SCRATCH_MAX_ANIMATION_Y 2                          // �A�j���[�V������ �c
#define SCRATCH_ANIM_PATTERN 8                             // �A�j���[�V�����̃p�^�[����

//******************************
// �ÓI�����o�ϐ��錾
//******************************
LPDIRECT3DTEXTURE9  CScratch::m_pTexture = NULL; // �e�N�X�`���|�C���^

//******************************
// �R���X�g���N�^
//******************************
CScratch::CScratch() :CScene3d(OBJTYPE_ATTACK)
{
	// �ϐ��̃N���A
	m_user = SCRATCHUSER_PLAYER;
	m_pCollision = NULL;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
}

//******************************
// �f�X�g���N�^
//******************************
CScratch::~CScratch()
{
}

//******************************
// �N���G�C�g
//******************************
CScratch * CScratch::Create(const D3DXVECTOR3 pos, const float fAngle,  const  SCRATCHUSER user,const int nPlayerNum)
{
	// �������̊m��
	CScratch *pScratch;
	pScratch = new CScratch;
	// ������
	pScratch->Init();

	// �e�l�̑���E�Z�b�g
	pScratch->SetPos(pos);                             // ���W
	pScratch->SetRot(D3DXVECTOR3(0.0f, fAngle, 0.0f)); // �p�x
	pScratch->SetObjType(OBJTYPE_ATTACK);              // �I�u�W�F�N�g�^�C�v
	pScratch->m_user = user;                           // �o���b�g���[�U�[
	pScratch->m_nPlayerNum = nPlayerNum;
	// �����蔻��̐���
	pScratch->m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(pos.x, pos.y-SCRATCH_HEIGHT, pos.z), SCRATCH_COLLISION_SIZE);

	return pScratch;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CScratch::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, SCRATCH_TEXTURE_PATH, &m_pTexture);


	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CScratch::Unload(void)
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
HRESULT CScratch::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindTexture(m_pTexture);
	// �T�C�Y�̐ݒ�
	SetSize(D3DXVECTOR3(SCRATCH_SIZE, 0.0f, SCRATCH_SIZE));

	// UV���W�̐ݒ�
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
	float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV���W�Z�b�g
	SetTextureUV(uv);
	// ���Z�����ɂ���
	//SetAddMode(true);
	// �J���[�̐ݒ�
	SetColor(SCRATCH_COLOR);
	return S_OK;
}

//******************************
// �I������
//******************************
void CScratch::Uninit(void)
{
	// �R���W�����̏I������
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}

	CScene3d::Uninit();
}

//******************************
// �X�V����
//******************************
void CScratch::Update(void)
{
	// �����蔻��
	CollisionScratch(m_user);
	switch (m_user)
	{
	case SCRATCHUSER_ENEMY:
	{
		// �v���C���[�̎擾
		CEnemy*pEnemy = CGame::GetEnemy();
		if (pEnemy != NULL)
		{
			// ���W�̐ݒ�
			D3DXVECTOR3 pos;
			float fRotY = pEnemy->GetRot().y - D3DXToRadian(90);
			pos.x = pEnemy->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE;
			pos.y = pEnemy->GetPos().y + SCRATCH_HEIGHT;
			pos.z = pEnemy->GetPos().z + sinf(fRotY) * SCRATCH_SIZE;
			SetPos(pos);

			// �p�x
			SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
			m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
		}
	}
		break;
	case SCRATCHUSER_PLAYER:
	{
		// �v���C���[�̎擾
		CPlayer*pPlayer = CGame::GetPlayer(m_nPlayerNum);
		if (pPlayer != NULL)
		{
			// ���W�̐ݒ�
			D3DXVECTOR3 pos;
			float fRotY = pPlayer->GetRot().y - D3DXToRadian(90);
			pos.x = pPlayer->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE;
			pos.y = pPlayer->GetPos().y + SCRATCH_HEIGHT;
			pos.z = pPlayer->GetPos().z + sinf(fRotY) * SCRATCH_SIZE;
			SetPos(pos);

			// �p�x
			SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
			m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
		}
	}
	default:
		break;
	}
	// �A�j���[�V����*�A�j���[�V�������I�������������
	Animation();
}

//******************************
// �`�揈��
//******************************
void CScratch::Draw(void)
{
	CScene3d::Draw();
}


//******************************
// �����蔻��
//******************************
void CScratch::CollisionScratch(SCRATCHUSER user)
{
	switch (user)
	{
	case SCRATCHUSER_ENEMY:
		break;
	case SCRATCHUSER_PLAYER:
	{
		CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
		while (pEnemy != NULL)
		{

			if (CCollision::CollisionSphere(m_pCollision, pEnemy->GetCollision()))
			{
				pEnemy->Uninit();
				//Uninit();
				break;
			}
			pEnemy = (CEnemy*)pEnemy->GetNext();
		}
	}
	default:
		break;
	}
}

//******************************
// �A�j���[�V����
//******************************
void CScratch::Animation(void)
{
	// �A�j���[�V�����J�E���g��i�߂�
	m_nCntAnim++;

	// �A�j���[�V�����������̃J�E���g
	if (m_nCntAnim % SCRATCH_ANIM_SPEED == 0)
	{

		if (m_nCntAnim >= SCRATCH_ANIM_PATTERN*SCRATCH_ANIM_SPEED)
		{
			Uninit();
			return;
		}

		// �A�j���[�V����X���̉��Z
		m_nAnimX++;

		if (m_nAnimX >= SCRATCH_MAX_ANIMATION_X)
		{
			// �A�j���[�V����X���̏�����
			m_nAnimX = 0;
			m_nAnimY++;
		}

		// UV���W�̐ݒ�
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
		float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV���W�Z�b�g
		SetTextureUV(uv);
	}
}

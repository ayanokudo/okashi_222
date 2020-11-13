////////////////////////////////////////////////////
//
//    ���X�g�|�C���g�̏���[LostPoint.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "LostPoint.h"
#include "manager.h"
#include "keyboard.h"
#include "collision.h"
#include "player.h"
#include "game.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define POINT_TEXT "data/Texts/LostPoint.txt" // �|�C���g�L���p�e�L�X�g�t�@�C��
#define POINT_TEXT_ROUTE "data/Texts/RoutePoint.txt" // �|�C���g�L���p�e�L�X�g�t�@�C��
#define COLLISION_RADIUS 120                  // �����蔻��̔��a
#define MODE_EDIT false                        // �G�f�B�b�g���[�h��


//=============================
// �R���X�g���N�^
//=============================
CLostPoint::CLostPoint()
{
	memset(m_pCollisionLost, 0, sizeof(m_pCollisionLost));
	m_pointPos = NULL;
	m_nPointNum = 0;

	memset(m_pCollisionRoute, 0, sizeof(m_pCollisionRoute));
	m_routePos = NULL;
	m_nRouteNum = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CLostPoint::~CLostPoint()
{
}

//=============================
// �N���G�C�g
//=============================
CLostPoint * CLostPoint::Create(void)
{
	// �������̊m��
	CLostPoint *pLostPoint = new CLostPoint;

	if (pLostPoint != NULL)
	{
		// ������
		pLostPoint->Init();
	}
	return pLostPoint;
}

//=============================
// ����������
//=============================
HRESULT CLostPoint::Init(void)
{
	// �|�C���g���̏�����
	m_nPointNum = 0;

#if MODE_EDIT
	// �G�f�B�b�g���[�h

	// �������̊m��
	m_pointPos = new D3DXVECTOR3[MAX_LOSTPOINT];
	m_routePos = new D3DXVECTOR3[MAX_ROUTEPOINT];

#else

	// �e�L�X�g�̓ǂݍ���
	LoadText();

#endif

	return S_OK;
}

//=============================
// �I������
//=============================
void CLostPoint::Uninit(void)
{
	if (m_pointPos != NULL)
	{
		delete[] m_pointPos;
		m_pointPos = NULL;
	}

	if (m_routePos != NULL)
	{
		delete[] m_routePos;
		m_routePos = NULL;
	}

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CLostPoint::Update(void)
{
#if MODE_EDIT
	// �G�f�B�b�g���[�h

	// ���X�g�|�C���g
	// ���W�̕ۑ�
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		m_pointPos[m_nPointNum] = CGame::GetPlayer(1)->GetPos();
		m_pCollisionLost[m_nPointNum] = CCollision::CreateSphere(m_pointPos[m_nPointNum], COLLISION_RADIUS);
		m_nPointNum++;
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_NUMPADENTER))
	{
		SaveText(0);
	}

	// ���[�g�|�C���g

	// ���W�̕ۑ�
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RSHIFT))
	{
		m_routePos[m_nRouteNum] = CGame::GetPlayer(1)->GetPos();
		m_pCollisionRoute[m_nPointNum] = CCollision::CreateSphere(m_routePos[m_nRouteNum], COLLISION_RADIUS);
		m_nRouteNum++;
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_NUMPADPLUS))
	{
		SaveText(1);
	}



#else


#endif
}


//=============================
// �`�揈��
//=============================
void CLostPoint::Draw(void)
{
	
}

//=============================
// �\�[�g
//=============================
void CLostPoint::sort(D3DXVECTOR3 pos)
{
	// �����̋߂����ɕ��ёւ�

	// ���X�g�|�C���g
	for (int nCntSort = 0; nCntSort < m_nPointNum; nCntSort++)
	{
		for (int nCnt = nCntSort + 1; nCnt < m_nPointNum; nCnt++)
		{
			// �����𑪂�
			float fDist = GetDistance(pos, m_pointPos[nCntSort]);
			
			// �������ׂ�
			if (fDist > GetDistance(pos, m_pointPos[nCnt]))
			{// �߂�������
				// �ۑ�
				D3DXVECTOR3 save = m_pointPos[nCntSort];

				// ���ёւ�
				m_pointPos[nCntSort] = m_pointPos[nCnt];
				m_pointPos[nCnt] = save;

				m_pCollisionLost[nCntSort]->SetPos(m_pointPos[nCntSort]);
				m_pCollisionLost[nCnt]->SetPos(m_pointPos[nCnt]);
			}

		}
	}

	// ���[�g�|�C���g
	for (int nCntSort = 0; nCntSort < m_nRouteNum; nCntSort++)
	{
		for (int nCnt = nCntSort + 1; nCnt < m_nRouteNum; nCnt++)
		{
			// �����𑪂�
			float fDist = GetDistance(pos, m_routePos[nCntSort]);

			// �������ׂ�
			if (fDist > GetDistance(pos, m_routePos[nCnt]))
			{// �߂�������
			 // �ۑ�
				D3DXVECTOR3 save = m_routePos[nCntSort];

				// ���ёւ�
				m_routePos[nCntSort] = m_routePos[nCnt];
				m_routePos[nCnt] = save;

				m_pCollisionRoute[nCntSort]->SetPos(m_routePos[nCntSort]);
				m_pCollisionRoute[nCnt]->SetPos(m_routePos[nCnt]);
			}

		}
	}
}

#if MODE_EDIT
//=============================
// �e�L�X�g�t�@�C���̃Z�[�u
//=============================
void CLostPoint::SaveText(int nMode)
{
	FILE*pFile = NULL;

	if (nMode == 0)
	{// ���X�g�|�C���g
		// �t�@�C���I�[�v��
		pFile = fopen(POINT_TEXT, "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", m_nPointNum);
			for (int nCnt = 0; nCnt < m_nPointNum; nCnt++)
			{
				fprintf(pFile, "%f %f %f\n", m_pointPos[nCnt].x, m_pointPos[nCnt].y, m_pointPos[nCnt].z);
			}

			fclose(pFile);
		}
	}
	else
	{// ���[�g�|�C���g
		// �t�@�C���I�[�v��
		pFile = fopen(POINT_TEXT_ROUTE, "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", m_nRouteNum);
			for (int nCnt = 0; nCnt < m_nRouteNum; nCnt++)
			{
				fprintf(pFile, "%f %f %f\n", m_routePos[nCnt].x, m_routePos[nCnt].y, m_routePos[nCnt].z);
			}

			fclose(pFile);
		}
	}
}
#else
//=============================
// �e�L�X�g�t�@�C���̃��[�h
//=============================
void CLostPoint::LoadText(void)
{
	
	FILE*pFile = NULL;

	// ���X�g�|�C���g

	// �t�@�C���I�[�v��
	pFile = fopen(POINT_TEXT, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nPointNum);

		m_pointPos = new D3DXVECTOR3[m_nPointNum];

		for (int nCnt = 0; nCnt < m_nPointNum; nCnt++)
		{
			fscanf(pFile, "%f %f %f", &m_pointPos[nCnt].x, &m_pointPos[nCnt].y, &m_pointPos[nCnt].z);

			m_pCollisionLost[nCnt] = CCollision::CreateSphere(m_pointPos[nCnt], COLLISION_RADIUS);
		}

		fclose(pFile);
	}

	// ���[�g�|�C���g

	pFile = fopen(POINT_TEXT_ROUTE, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nRouteNum);

		m_routePos = new D3DXVECTOR3[m_nRouteNum];

		for (int nCnt = 0; nCnt < m_nRouteNum; nCnt++)
		{
			fscanf(pFile, "%f %f %f", &m_routePos[nCnt].x, &m_routePos[nCnt].y, &m_routePos[nCnt].z);

			m_pCollisionRoute[nCnt] = CCollision::CreateSphere(m_routePos[nCnt], COLLISION_RADIUS);
		}

		fclose(pFile);
	}

}
#endif
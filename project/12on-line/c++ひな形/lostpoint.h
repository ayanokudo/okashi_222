//=============================================================================
//
// loastpoint�w�b�_ [loastpoint.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _LOST_POINT_H_
#define _LOST_POINT_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CCollision;

//=============================
// �}�N����`
//=============================
#define MAX_LOSTPOINT 20   // �|�C���g�̍ő吔
#define MAX_ROUTEPOINT 5   // �|�C���g�̍ő吔
//*****************************
//�N���X��`
//*****************************

//���X�g�|�C���g�̃N���X
class CLostPoint : public CScene
{
public:

	// �����o�֐�
	CLostPoint();
	~CLostPoint();
	static CLostPoint *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void sort(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetLostPos(int nNum) { return m_pointPos[nNum]; }
	D3DXVECTOR3 GetRoutePos(int nNum) { return m_routePos[nNum]; }

	CCollision* GetLostCollision(int nNum) { return m_pCollisionLost[nNum]; }
	CCollision* GetRouteCollision(int nNum) { return m_pCollisionRoute[nNum]; }

	int GetNumLostPoint(void) { return m_nPointNum; }
	int GetNumRoutePoint(void) { return m_nRouteNum; }
private:
	void SaveText(int nMode);
	void LoadText(void);
	// �����o�ϐ�
	CCollision*m_pCollisionLost[MAX_LOSTPOINT];  // �����蔻��
	D3DXVECTOR3 *m_pointPos; // �|�C���g�̃|�X
	int m_nPointNum;         // �|�C���g��
	 
	CCollision*m_pCollisionRoute[MAX_ROUTEPOINT];  // �����蔻��
	D3DXVECTOR3 *m_routePos; // �|�C���g�̃|�X
	int m_nRouteNum;         // �|�C���g��
	

};

#endif
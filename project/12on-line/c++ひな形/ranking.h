//------------------------------------------
//
//	�����L���O�̏���[ranking.h]
//	Author : ���V ����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _RANKING_H_
#define _RANKING_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CNumber;

#define MAX_RANKING_DIGIT 5		// �X�R�A�̍ő包��
#define MAX_NUMBER_DIGIT 6		// 
//------------------------------------------
//	�����L���O�N���X
//------------------------------------------
class CRanking : public CScene
{
public:
	CRanking();
	~CRanking();

	static CRanking *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber *m_apNumber[MAX_RANKING_DIGIT][MAX_NUMBER_DIGIT];//�i���o�[���
	int m_anRankingDate[MAX_RANKING_DIGIT];	//�����L���O���
	int m_nCount;						//
	int m_nRank;						//
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif // !_RANKING_H_

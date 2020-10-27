//=============================================================================
//
// time�w�b�_ [time.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TIME_H_
#define _TIME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CNumber;

//*****************************
//�}�N����`
//*****************************
#define MAX_TIME_DIGIT 3  // �X�R�A�̍ő包��

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CTime : public CScene
{
public:
	// �����o�֐�
	CTime();
	~CTime();
	static CTime *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SubtractTime(int nTime);
	static int GetTime(void) { return m_nTime; }
private:
	// �����o�ϐ�
	CNumber* m_apNumber[MAX_TIME_DIGIT];
	static int m_nTime;
	DWORD m_start;
	DWORD m_end;

};

#endif
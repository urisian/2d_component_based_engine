#ifndef FRC_H
#define FRC_H

class CFRC
{
public:
	static				CFRC*			GetInstance			(void);
	static				void			DestroyInstance		(void);

						void			Initialize			(void);
						void			Update				(void);

						bool			FrameLock			(void);
						float			GetDelta			(void);

private:
	explicit							CFRC				(void);
									   ~CFRC				(void);

private:
						//cpu�� �ʴ� ������
						LARGE_INTEGER	m_cpuTick;
						//���� ������������ ������
						LARGE_INTEGER	m_beginTime;
						//���� ������� ������
						LARGE_INTEGER	m_endTime;

						//�����Ӱ� ������ ���̿� �ɸ� �ð�
						float			m_deltaTime;
						//�� �������� �ӵ� ����Ʈ. second per frame limit.
						float			m_spfLimit;
						//1�ʿ� �� �������� �귯������.
						float			m_fps;

	static				CFRC*			m_s_pInstance;
};

#endif
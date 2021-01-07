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
						//cpu의 초당 진동수
						LARGE_INTEGER	m_cpuTick;
						//측정 시작했을때의 진동수
						LARGE_INTEGER	m_beginTime;
						//측정 종료시의 진동수
						LARGE_INTEGER	m_endTime;

						//프레임과 프레임 사이에 걸린 시간
						float			m_deltaTime;
						//한 프레임의 속도 리미트. second per frame limit.
						float			m_spfLimit;
						//1초에 몇 프레임이 흘러가는지.
						float			m_fps;

	static				CFRC*			m_s_pInstance;
};

#endif
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "DataStore.h"

class CObject;
class CObjectState;

class CStateMachine
{
public:
	explicit							CStateMachine			(CObject* pOwner);
								   	   ~CStateMachine			(void);

					void				Initialize				(void);
					void				Update					(void);
					void				LateUpdate				(void);
					void				Release					(void);


	GETTOR_SETTOR	(CObjectState*,		m_pCurState,			CurState);
	GETTOR_SETTOR	(CObjectState*,		m_pPrevState,			PrevState);
	GETTOR_SETTOR	(CObjectState*,		m_pNextState,			NextState);
	GETTOR_SETTOR	(CObject*,			m_pOwner,				Owner); 

};

#endif

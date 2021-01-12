#ifndef MYMACROS_H
#define MYMACROS_H

#define GETTOR_SETTOR(varType, varName, funcName)\
protected: varType varName; public: virtual inline varType& Get##funcName(void) { return varName; } virtual inline void Set##funcName(varType var){ varName = var; }

#define GETTOR(varType, varName, funcName)\
protected: varType varName; public: virtual inline varType& Get##funcName(void) { return varName; }

#define SAFE_DELETE(something) if( (something) != nullptr ) delete (something); (something) = nullptr;

#define GET_VALUE(dataID, objectKey, varKey, result) CDataStore::GetInstance()->GetValue(dataID, objectKey, varKey, result)
#define GET_TEXTURE(OBJID, objectKey) CTextureStore::GetInstance()->GetTexture(OBJID, objectKey)
#define GET_WND_HANDLE() CApplication::GetInstance()->GetHandle()

#define GET_DT() CFRC::GetInstance()->GetDelta()
#define GET_MOUSE_POS() CInputManager::GetInstance()->GetMousePos()

#define IMKEY_DOWN(key) CInputManager::GetInstance()->KeyDown(key)
#define IMKEY_PRESS(key) CInputManager::GetInstance()->KeyPress(key)
#define IMKEY_UP(key) CInputManager::GetInstance()->KeyUp(key)


#define ADD_DEBUG_INFO(debugID, key, info) CDebugger::GetInstance()->AddInfo(debugID, key, info)


#endif // !MYMACROS_H

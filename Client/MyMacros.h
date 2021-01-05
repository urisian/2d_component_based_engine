#ifndef MYMACROS_H
#define MYMACROS_H

#define SAFE_DELETE(something) if( (something) != nullptr ) delete (something); (something) = nullptr;
#define GET_VALUE(dataID, objectKey, varKey, result) CDataStore::GetInstance()->GetValue(dataID, objectKey, varKey, result)


#endif // !MYMACROS_H

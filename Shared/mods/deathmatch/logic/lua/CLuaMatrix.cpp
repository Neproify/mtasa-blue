/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Shared/mods/logic/lua/CLuaMatrix.cpp
 *  PURPOSE:     Lua matrix class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include <StdInc.h>

CLuaMatrix::CLuaMatrix(void) : CMatrix()
{
    m_uiScriptID = CIdArray::PopUniqueId(this, EIdClass::MATRIX);
}

CLuaMatrix::CLuaMatrix(const CMatrix& matrix) : CMatrix(matrix)
{
    m_uiScriptID = CIdArray::PopUniqueId(this, EIdClass::MATRIX);
}

CLuaMatrix::~CLuaMatrix(void)
{
    CIdArray::PushUniqueId(this, EIdClass::MATRIX, m_uiScriptID);
    m_uiScriptID = INVALID_ARRAY_ID;
}

CLuaMatrix* CLuaMatrix::GetFromScriptID(unsigned int uiScriptID)
{
    CLuaMatrix* pLuaMatrix = (CLuaMatrix*)CIdArray::FindEntry(uiScriptID, EIdClass::MATRIX);
    return pLuaMatrix;
}

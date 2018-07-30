/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/CAnimBlendAssocGroupSA.h
 *  PURPOSE:     Header file for animation blend association group class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#ifndef __CAnimBlendAssocGroupSA_H
#define __CAnimBlendAssocGroupSA_H

#include <game/CAnimBlendAssocGroup.h>
#include "CAnimBlendStaticAssociationSA.h"
#include "Common.h"

#define FUNC_CAnimBlendAssocGroup_InitEmptyAssociations 0x4cdfb0
#define FUNC_CAnimBlendAssocGroup_CopyAnimation         0x4ce130
#define FUNC_CAnimBlendAssocGroup_IsCreated             0x4d37a0
#define FUNC_CAnimBlendAssocGroup_GetNumAnimations      0x45b050
#define FUNC_CAnimBlendAssocGroup_GetAnimBlock          0x45b060
#define FUNC_CAnimBlendAssocGroup_GetAnimation          0x4ce090
#define FUNC_CAnimBlendAssocGroup_CreateAssociations    0x4ce220

class CAnimBlockSA;
class CAnimBlockSAInterface;
class CAnimManagerSA;

class CAnimBlendAssocGroupSAInterface
{
public:
    CAnimBlockSAInterface*                  pAnimBlock;
    CAnimBlendStaticAssociationSAInterface* pAssociationsArray;
    int                                     iNumAnimations;
    int                                     iIDOffset;
    AssocGroupId                            groupID;
};

class CAnimBlendAssocGroupSA : public CAnimBlendAssocGroup
{
    friend class CAnimManagerSA;

public:
    CAnimBlendAssocGroupSA(CAnimBlendAssocGroupSAInterface* pInterface);

    CAnimBlendAssociationSAInterface* CopyAnimation(unsigned int AnimID);
    void                              InitEmptyAssociations(RpClump* pClump);
    bool                              IsCreated(void);
    int                               GetNumAnimations(void);
    CAnimBlock*                       GetAnimBlock(void);
    CAnimBlendStaticAssociation*      GetAnimation(unsigned int ID);
    AssocGroupId                      GetGroupID(void) { return m_pInterface->groupID; };
    void                              CreateAssociations(const char* szBlockName);

    bool IsLoaded(void);
    void SetIDOffset(int iOffset) { m_pInterface->iIDOffset = iOffset; }

protected:
    void SetupAnimBlock(void);

    CAnimBlendAssocGroupSAInterface* m_pInterface;
    CAnimBlockSA*                    m_pAnimBlock;
};

#endif

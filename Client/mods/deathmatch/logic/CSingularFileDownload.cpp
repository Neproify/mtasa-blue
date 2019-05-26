/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CSingularFileDownloadManager.cpp
 *  PURPOSE:     Singular file download manager interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include <StdInc.h>

CSingularFileDownload::CSingularFileDownload(CResource* pResource, const char* szName, const char* szNameShort, SString strHTTPURL, CChecksum serverChecksum)
{
    // Store the name
    m_strName = szName;

    // Store the name (short)
    m_strNameShort = szNameShort;

    // store the resource
    m_pResource = pResource;

    // Store the server checksum
    m_ServerChecksum = serverChecksum;

    m_bBeingDeleted = false;

    GenerateClientChecksum();

    if (!DoesClientAndServerChecksumMatch())
    {
        SHttpRequestOptions options;
        options.bCheckContents = true;
        CNetHTTPDownloadManagerInterface* pHTTP = g_pCore->GetNetwork()->GetHTTPDownloadManager(EDownloadMode::RESOURCE_SINGULAR_FILES);
        pHTTP->QueueFile(strHTTPURL.c_str(), szName, this, DownloadFinishedCallBack, options);
        m_bComplete = false;
        g_pClientGame->SetTransferringSingularFiles(true);
    }
    else
    {
        CallFinished(true);
    }
}

CSingularFileDownload::~CSingularFileDownload()
{
}

void CSingularFileDownload::DownloadFinishedCallBack(const SHttpDownloadResult& result)
{
    CSingularFileDownload* pFile = (CSingularFileDownload*)result.pObj;
    pFile->CallFinished(result.bSuccess);
}

void CSingularFileDownload::CallFinished(bool bSuccess)
{
    // Flag file as loadable
    g_pClientGame->GetResourceManager()->OnDownloadedResourceFile(GetName());

    if (!m_bBeingDeleted && m_pResource)
    {
        // Call the onClientbFileDownloadComplete event
        CLuaArguments Arguments;
        Arguments.PushString(GetShortName());            // file name
        Arguments.PushBoolean(bSuccess);                 // Completed successfully?
        m_pResource->GetResourceEntity()->CallEvent("onClientFileDownloadComplete", Arguments, false);
    }
    SetComplete();
}

void CSingularFileDownload::Cancel()
{
    m_bBeingDeleted = true;
    m_pResource = NULL;

    // TODO: Cancel also in Net
}

bool CSingularFileDownload::DoesClientAndServerChecksumMatch()
{
    return (m_LastClientChecksum == m_ServerChecksum);
}

CChecksum CSingularFileDownload::GenerateClientChecksum()
{
    m_LastClientChecksum = CChecksum::GenerateChecksumFromFile(m_strName);
    return m_LastClientChecksum;
}

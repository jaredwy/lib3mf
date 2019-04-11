/*++

Copyright (C) 2019 3MF Consortium (Original Author)

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.5.0.

Abstract: This is an autogenerated C++ implementation file in order to allow easy
development of the 3MF Library. It needs to be generated only once.

Interface version: 2.0.0

*/

#include "lib3mf_abi.hpp"
#include "lib3mf_interfaces.hpp"
#include "lib3mf_interfaceexception.hpp"

#include "lib3mf_model.hpp"

#include "NMR_Spec_Version.h"
#include "Model/Classes/NMR_ModelConstants.h" 
#include "Common/3MF_ProgressMonitor.h"
#include <cmath>
#include <algorithm>

using namespace Lib3MF::Impl;

void CWrapper::GetLibraryVersion(Lib3MF_uint32 & nMajor, Lib3MF_uint32 & nMinor, Lib3MF_uint32 & nMicro)
{
	nMajor = LIB3MF_VERSION_MAJOR;
	nMinor = LIB3MF_VERSION_MINOR;
	nMicro = LIB3MF_VERSION_MICRO;
}

bool CWrapper::GetPrereleaseInformation(std::string & sPrereleaseInfo)
{
	sPrereleaseInfo = LIB3MF_VERSION_PRERELEASEINFO;
	return !sPrereleaseInfo.empty();
}

bool CWrapper::GetBuildInformation(std::string & sBuildInformation)
{
	sBuildInformation = LIB3MF_VERSION_BUILDINFO;
	return !sBuildInformation.empty();
}


void CWrapper::GetSpecificationVersion (const std::string & sSpecificationURL, bool & bIsSupported, Lib3MF_uint32 & nMajor, Lib3MF_uint32 & nMinor, Lib3MF_uint32 & nMicro)
{
	if (!sSpecificationURL.compare(std::string(XML_3MF_NAMESPACE_CORESPEC100))) {
		nMajor = NMR_SPECVERSION_MAJOR;
		nMinor = NMR_SPECVERSION_MINOR;
		nMicro = NMR_SPECVERSION_MICRO;
		bIsSupported = true;
	} else if (!sSpecificationURL.compare( std::string(XML_3MF_NAMESPACE_MATERIALSPEC) )) {
		nMajor = NMR_SPECVERSION_MATERIAL_MAJOR;
		nMinor = NMR_SPECVERSION_MATERIAL_MINOR;
		nMicro = NMR_SPECVERSION_MATERIAL_MICRO;
		bIsSupported = true;
	} else if (!sSpecificationURL.compare( std::string(XML_3MF_NAMESPACE_PRODUCTIONSPEC) )) {
		nMajor = NMR_SPECVERSION_PRODUCTION_MAJOR;
		nMinor = NMR_SPECVERSION_PRODUCTION_MINOR;
		nMicro = NMR_SPECVERSION_PRODUCTION_MICRO;
		bIsSupported = true;
	} else if (!sSpecificationURL.compare( std::string(XML_3MF_NAMESPACE_BEAMLATTICESPEC) )) {
		nMajor = NMR_SPECVERSION_BEAMLATTICE_MAJOR;
		nMinor = NMR_SPECVERSION_BEAMLATTICE_MINOR;
		nMicro = NMR_SPECVERSION_BEAMLATTICE_MICRO;
		bIsSupported = true;
	} else if (!sSpecificationURL.compare(std::string(XML_3MF_NAMESPACE_SLICESPEC) )) {
		nMajor = NMR_SPECVERSION_SLICE_MAJOR;
		nMinor = NMR_SPECVERSION_SLICE_MINOR;
		nMicro = NMR_SPECVERSION_SLICE_MICRO;
		bIsSupported = true;
	}
	else {
		bIsSupported = false;
	}
}

IModel * CWrapper::CreateModel ()
{
	return new CModel();
}

void CWrapper::Release (IBase* pInstance)
{
	delete pInstance;
}


NMR::ProgressIdentifier convertProgressIdentifier(const eLib3MFProgressIdentifier progressIdentifier) {
	return NMR::ProgressIdentifier(progressIdentifier);
	//switch (progressIdentifier) {
	//	case eLib3MFProgressIdentifier::eProgressIdentifierQUERYCANCELED: return NMR::PROGRESS_QUERYCANCELED;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierDONE: return NMR::PROGRESS_DONE;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierCLEANUP: return NMR::PROGRESS_CLEANUP;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADSTREAM: return NMR::PROGRESS_READSTREAM;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierEXTRACTOPCPACKAGE: return NMR::PROGRESS_EXTRACTOPCPACKAGE;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADNONROOTMODELS: return NMR::PROGRESS_READNONROOTMODELS;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADROOTMODEL: return NMR::PROGRESS_READROOTMODEL;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADRESOURCES: return NMR::PROGRESS_READRESOURCES;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADMESH: return NMR::PROGRESS_READMESH;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADSLICES: return NMR::PROGRESS_READSLICES;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierREADBUILD: return NMR::PROGRESS_READBUILD;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierCREATEOPCPACKAGE: return NMR::PROGRESS_CREATEOPCPACKAGE;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITEMODELSTOSTREAM: return NMR::PROGRESS_WRITEMODELSTOSTREAM;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITEROOTMODEL: return NMR::PROGRESS_WRITEROOTMODEL;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITENONROOTMODELS: return NMR::PROGRESS_WRITENONROOTMODELS;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITEATTACHMENTS: return NMR::PROGRESS_WRITEATTACHMENTS;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITECONTENTTYPES: return NMR::PROGRESS_WRITECONTENTTYPES;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITENOBJECTS: return NMR::PROGRESS_WRITENOBJECTS;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITENODES: return NMR::PROGRESS_WRITENODES;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITETRIANGLES: return NMR::PROGRESS_WRITETRIANGLES;
	//	case eLib3MFProgressIdentifier::eProgressIdentifierWRITESLICES: return NMR::PROGRESS_WRITESLICES;
	//	default: throw ELib3MFInterfaceException(LIB3MF_ERROR_UNKOWNPROGRESSIDENTIFIER);
	//}
}

bool CWrapper::GetLastError (IBase* pInstance, std::string & sLastErrorString)
{
	if (pInstance != nullptr)
		return pInstance->GetLastErrorMessage(sLastErrorString);

	return false;
}

void CWrapper::RetrieveProgressMessage (const eLib3MFProgressIdentifier eProrgessIdentifier, std::string & sProgressMessage)
{
	NMR::CProgressMonitor::GetProgressMessage(convertProgressIdentifier(eProrgessIdentifier), sProgressMessage);
}

sLib3MFColor CWrapper::RGBAToColor (const Lib3MF_uint8 nRed, const Lib3MF_uint8 nGreen, const Lib3MF_uint8 nBlue, const Lib3MF_uint8 nAlpha)
{
	sLib3MFColor s;
	s.m_Red = nRed;
	s.m_Green = nGreen;
	s.m_Blue = nBlue;
	s.m_Alpha = nAlpha;
	return s;
}

sLib3MFColor CWrapper::FloatRGBAToColor (const Lib3MF_single fRed, const Lib3MF_single fGreen, const Lib3MF_single fBlue, const Lib3MF_single fAlpha)
{
	sLib3MFColor s;
	s.m_Red = (Lib3MF_uint8)std::round(std::max(std::min(fRed, 1.f), 0.f) * 255.0f);
	s.m_Green = (Lib3MF_uint8)std::round(std::max(std::min(fGreen, 1.f), 0.f) * 255.0f);
	s.m_Blue = (Lib3MF_uint8)std::round(std::max(std::min(fBlue, 1.f), 0.f) * 255.0f);
	s.m_Alpha = (Lib3MF_uint8)std::round(std::max(std::min(fAlpha, 1.f), 0.f) * 255.0f);
	return s;
}

void CWrapper::ColorToRGBA (const sLib3MFColor TheColor, Lib3MF_uint8 & nRed, Lib3MF_uint8 & nGreen, Lib3MF_uint8 & nBlue, Lib3MF_uint8 & nAlpha)
{
	nRed = TheColor.m_Red;
	nGreen = TheColor.m_Green;
	nBlue = TheColor.m_Blue;
	nAlpha = TheColor.m_Alpha;
}

void CWrapper::ColorToFloatRGBA (const sLib3MFColor TheColor, Lib3MF_single & fRed, Lib3MF_single & fGreen, Lib3MF_single & fBlue, Lib3MF_single & fAlpha)
{
	fRed = TheColor.m_Red / 255.f;
	fGreen = TheColor.m_Green / 255.f;
	fBlue = TheColor.m_Blue / 255.f;
	fAlpha = TheColor.m_Alpha / 255.f;
}

sLib3MFTransform CWrapper::GetIdentityTransform ()
{
	int i, j;
	sLib3MFTransform Transform;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			Transform.m_Fields[i][j] = (i == j) ? 1.0f : 0.0f;

	return Transform;

}

sLib3MFTransform CWrapper::GetUniformScaleTransform (const Lib3MF_single fFactor)
{
	int i, j;
	sLib3MFTransform Transform;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			Transform.m_Fields[i][j] = (i == j) ? fFactor : 0.0f;

	return Transform;
}

sLib3MFTransform CWrapper::GetScaleTransform (const Lib3MF_single fFactorX, const Lib3MF_single fFactorY, const Lib3MF_single fFactorZ)
{
	int i, j;
	sLib3MFTransform Transform;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			Transform.m_Fields[i][j] = (i == j) ? 1.0f : 0.0f;

	Transform.m_Fields[0][0] = fFactorX;
	Transform.m_Fields[1][1] = fFactorY;
	Transform.m_Fields[2][2] = fFactorZ;

	return Transform;

}

sLib3MFTransform CWrapper::GetTranslationTransform(const Lib3MF_single fVectorX, const Lib3MF_single fVectorY, const Lib3MF_single fVectorZ)
{
	int i, j;
	sLib3MFTransform Transform;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			Transform.m_Fields[i][j] = (i == j) ? 1.0f : 0.0f;

	Transform.m_Fields[3][0] = fVectorX;
	Transform.m_Fields[3][1] = fVectorY;
	Transform.m_Fields[3][2] = fVectorZ;

	return Transform;
}

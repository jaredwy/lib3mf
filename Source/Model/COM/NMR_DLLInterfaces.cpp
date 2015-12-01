/*++

Copyright (C) 2015 Microsoft Corporation (Original Author)
Copyright (C) 2015 netfabb GmbH

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

Abstract: COM Interface Exports for plain C DLLs

--*/

#include "Model/COM/NMR_DLLInterfaces.h"
#include "Model/COM/NMR_COMInterfaces.h"
#include "Model/COM/NMR_COMInterface_Model.h"

#ifndef __GCC
#include "Common/NMR_Exception_Windows.h"
#endif // __GCC

namespace NMR {

	extern "C" {

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_getspecversion(_Out_ DWORD * pMajorVersion, _Out_ DWORD * pMinorVersion)
		{
			if (!pMajorVersion)
				return LIB3MF_POINTER;
			if (!pMinorVersion)
				return LIB3MF_POINTER;

			*pMajorVersion = NMR_APIVERSION_MAJOR;
			*pMinorVersion = NMR_APIVERSION_MINOR;

			return LIB3MF_OK;
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_getinterfaceversion(_Out_ DWORD * pInterfaceVersion)
		{
			if (!pInterfaceVersion)
				return LIB3MF_POINTER;

			*pInterfaceVersion = NMR_APIVERSION_INTERFACE;

			return LIB3MF_OK;
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_createmodel(_Outptr_ PLib3MFModel ** ppModel, _In_ BOOL bInitialize)
		{
			if (ppModel == nullptr)
				return LIB3MF_POINTER;

			try {
#ifndef __GCC
				if (bInitialize) {
					HRESULT hResult = CoInitialize(NULL);
					if (hResult != LIB3MF_OK) {
						if (hResult != S_FALSE)
							throw CNMRException_Windows(NMR_ERROR_COULDNOTINITITALIZECOM, hResult);
						else
							throw CNMRException(NMR_ERROR_COULDNOTINITITALIZECOM);
					}
				}
#endif

				CCOMObject<CCOMModel> * pNewModel = new CCOMObject<CCOMModel>();
				pNewModel->AddRef();
				*ppModel = (PLib3MFModel *)pNewModel;

				return LIB3MF_OK;
			}
			catch (...) {
				return LIB3MF_FAIL;
			}
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_release(_In_ PLib3MFBase * pInstance)
		{
			if (pInstance) {
				ILib3MFBase * pBaseInstance = (ILib3MFBase *)pInstance;
#ifndef __GCC
				pBaseInstance->Release();
#else
				delete pBaseInstance;
#endif
			}

			return LIB3MF_OK;
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_getlasterror(_In_ PLib3MFBase * pInstance, _Out_ DWORD * pErrorCode, _Outptr_opt_ LPCSTR * pErrorMessage)
		{
			if (!pInstance)
				return LIB3MF_POINTER;

			return ((ILib3MFBase *)pInstance)->GetLastError(pErrorCode, pErrorMessage);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_writer_writetofile(_In_ PLib3MFModelWriter * pWriter, _In_z_ LPCWSTR pwszFilename)
		{
			if (!pWriter)
				return LIB3MF_POINTER;

			return ((ILib3MFModelWriter *)pWriter)->WriteToFile(pwszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_writer_writetocallback(_In_ PLib3MFModelWriter * pWriter, _In_ void * pWriteCallback, _In_opt_ void * pSeekCallback, _In_opt_ void * pUserData)
		{
			if (!pWriter)
				return LIB3MF_POINTER;

			return ((ILib3MFModelWriter *)pWriter)->WriteToCallback(pWriteCallback, pSeekCallback, pUserData);

		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_writer_writetofileutf8(_In_ PLib3MFModelWriter * pWriter, _In_z_ LPCSTR pwszFilename)
		{
			if (!pWriter)
				return LIB3MF_POINTER;

			return ((ILib3MFModelWriter *)pWriter)->WriteToFileUTF8(pwszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_reader_readfromfile(_In_ PLib3MFModelReader * pReader, _In_z_ LPCWSTR pwszFilename)
		{
			if (!pReader)
				return LIB3MF_POINTER;

			return ((ILib3MFModelReader *)pReader)->ReadFromFile(pwszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_reader_readfromfileutf8(_In_ PLib3MFModelReader * pReader, _In_z_ LPCSTR pwszFilename)
		{
			if (!pReader)
				return LIB3MF_POINTER;

			return ((ILib3MFModelReader *)pReader)->ReadFromFileUTF8(pwszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_reader_getwarningcount(_In_ PLib3MFModelReader * pReader, _Out_ DWORD * pnWarningCount)
		{
			if (!pReader)
				return LIB3MF_POINTER;

			return ((ILib3MFModelReader *)pReader)->GetWarningCount(pnWarningCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_reader_getwarning(_In_ PLib3MFModelReader * pReader, _In_ DWORD nIndex, _Out_ DWORD * pErrorCode, _Out_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pReader)
				return LIB3MF_POINTER;

			return ((ILib3MFModelReader *)pReader)->GetWarning(nIndex, pErrorCode, pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_resource_getresourceid(_In_ PLib3MFModelResource * pResource, _Out_ DWORD * pnResourceID)
		{
			if (!pResource)
				return LIB3MF_POINTER;

			return ((ILib3MFModelResource *)pResource)->GetResourceID(pnResourceID);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_resourceiterator_movenext(_In_ PLib3MFModelResourceIterator * pIterator, _Out_ BOOL * pbHasNext)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelResourceIterator *)pIterator)->MoveNext(pbHasNext);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_resourceiterator_moveprevious(_In_ PLib3MFModelResourceIterator * pIterator, _Out_ BOOL * pbHasPrevious)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelResourceIterator *)pIterator)->MovePrevious(pbHasPrevious);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_resourceiterator_getcurrent(_In_ PLib3MFModelResourceIterator * pIterator, _Outptr_ PLib3MFModelResource ** ppResultResource)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelResourceIterator *)pIterator)->GetCurrent((ILib3MFModelResource **)ppResultResource);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_resourceiterator_clone(_In_ PLib3MFModelResourceIterator * pIterator, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelResourceIterator *)pIterator)->Clone((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_thumbnailiterator_movenext(_In_ PLib3MFModelThumbnailIterator * pIterator, _Out_ BOOL * pbHasNext)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelThumbnailIterator *)pIterator)->MoveNext(pbHasNext);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_thumbnailiterator_moveprevious(_In_ PLib3MFModelThumbnailIterator * pIterator, _Out_ BOOL * pbHasPrevious)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelThumbnailIterator *)pIterator)->MovePrevious(pbHasPrevious);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_thumbnailiterator_getcurrent(_In_ PLib3MFModelThumbnailIterator * pIterator, _Outptr_ PLib3MFModelThumbnail ** ppThumbnailInstance)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelThumbnailIterator *)pIterator)->GetCurrent((ILib3MFModelThumbnail **)ppThumbnailInstance);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_thumbnailiterator_clone(_In_ PLib3MFModelThumbnailIterator * pIterator, _Outptr_ PLib3MFModelThumbnailIterator ** ppIterator)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelThumbnailIterator *)pIterator)->Clone((ILib3MFModelThumbnailIterator **)ppIterator);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_removeproperty(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->RemoveProperty(nIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_removeallproperties(_In_ PLib3MFPropertyHandler * pPropertyHandler)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->RemoveAllProperties();
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_getpropertytype(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _Out_ eModelPropertyType * pnPropertyType)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetPropertyType(nIndex, pnPropertyType);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_getbasematerial(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _Out_ DWORD * pnMaterialGroupID, _Out_ DWORD * pnMaterialIndex)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetBaseMaterial(nIndex, pnMaterialGroupID, pnMaterialIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_getbasematerialarray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _Out_ DWORD * pnMaterialGroupIDs, _Out_ DWORD * pnMaterialIndices)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetBaseMaterialArray(pnMaterialGroupIDs, pnMaterialIndices);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setbasematerial(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ ModelResourceID nMaterialGroupID, _In_ DWORD nMaterialIndex)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetBaseMaterial(nIndex, nMaterialGroupID, nMaterialIndex);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setbasematerialarray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ ModelResourceID * pnMaterialGroupIDs, _In_ DWORD * pnMaterialIndices)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetBaseMaterialArray(pnMaterialGroupIDs, pnMaterialIndices);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_getcolor(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _Out_ MODELMESH_TRIANGLECOLOR_SRGB * pColor)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetColor(nIndex, pColor);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_getcolorarray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _Out_ MODELMESH_TRIANGLECOLOR_SRGB * pColors)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetColorArray(pColors);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setsinglecolor(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ MODELMESHCOLOR_SRGB * pColor)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetSingleColor(nIndex, pColor);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setsinglecolorrgb(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetSingleColorRGB(nIndex, bRed, bGreen, bBlue);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setsinglecolorrgba(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue, _In_ BYTE bAlpha)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetSingleColorRGBA(nIndex, bRed, bGreen, bBlue, bAlpha);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setsinglecolorfloatrgb(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ FLOAT fRed, _In_ FLOAT fGreen, _In_ FLOAT fBlue)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetSingleColorFloatRGB(nIndex, fRed, fGreen, fBlue);
		}



		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setsinglecolorfloatrgba(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ FLOAT fRed, _In_ FLOAT fGreen, _In_ FLOAT fBlue, _In_ FLOAT fAlpha)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetSingleColorFloatRGBA(nIndex, fRed, fGreen, fBlue, fAlpha);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setsinglecolorarray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _Out_ MODELMESHCOLOR_SRGB * pColors)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetSingleColorArray(pColors);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setgradientcolor(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _Out_ MODELMESH_TRIANGLECOLOR_SRGB * pColor)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetGradientColor(nIndex, pColor);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_setgradientcolorarray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _Out_ MODELMESH_TRIANGLECOLOR_SRGB * pColors)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetGradientColorArray(pColors);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_gettexture(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _Out_ MODELMESHTEXTURE2D * pTexture)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetTexture(nIndex, pTexture);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_gettexturearray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _Out_ MODELMESHTEXTURE2D * pTextures)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->GetTextureArray(pTextures);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_settexture(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _In_ MODELMESHTEXTURE2D * pTexture)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetTexture(nIndex, pTexture);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_propertyhandler_settexturearray(_In_ PLib3MFPropertyHandler * pPropertyHandler, _In_ MODELMESHTEXTURE2D * pTextures)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFPropertyHandler *)pPropertyHandler)->SetTextureArray(pTextures);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_removeproperty(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->RemoveProperty();
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_getpropertytype(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _Out_ eModelPropertyType * pnPropertyType)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->GetPropertyType(pnPropertyType);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_getbasematerial(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _Out_ DWORD * pnMaterialGroupID, _Out_ DWORD * pnMaterialIndex)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->GetBaseMaterial(pnMaterialGroupID, pnMaterialIndex);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_setbasematerial(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ DWORD nMaterialGroupID, _In_ DWORD nMaterialIndex)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetBaseMaterial(nMaterialGroupID, nMaterialIndex);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_getcolor(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ DWORD nIndex, _Out_ MODELMESHCOLOR_SRGB * pColor)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->GetColor(nIndex, pColor);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_setcolor(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ MODELMESHCOLOR_SRGB * pColor)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetColor(pColor);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_setcolorrgb(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetColorRGB(bRed, bGreen, bBlue);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_setcolorrgba(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue, _In_ BYTE bAlpha)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetColorRGBA(bRed, bGreen, bBlue, bAlpha);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_setfloatcolorrgb(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ FLOAT fRed, _In_ FLOAT fGreen, _In_ FLOAT fBlue)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetFloatColorRGB(fRed, fGreen, fBlue);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_setfloatcolorrgba(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ FLOAT fRed, _In_ FLOAT fGreen, _In_ FLOAT fBlue, _In_ FLOAT fAlpha)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetFloatColorRGBA(fRed, fGreen, fBlue, fAlpha);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_gettexture(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _Out_ ModelResourceID * pnTextureID, _Out_ FLOAT * pfU, _Out_ FLOAT * pfV)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->GetTexture(pnTextureID, pfU, pfV);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_defaultpropertyhandler_settexture(_In_ PLib3MFDefaultPropertyHandler * pPropertyHandler, _In_ ModelResourceID nTextureID, _In_ FLOAT fU, _In_ FLOAT fV)
		{
			if (!pPropertyHandler)
				return LIB3MF_POINTER;

			return ((ILib3MFDefaultPropertyHandler *)pPropertyHandler)->SetTexture(nTextureID, fU, fV);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_ismeshobject(_In_ PLib3MFModelObjectResource * pObject, _Out_ BOOL * pbIsMeshObject)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->IsMeshObject(pbIsMeshObject);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_iscomponentsobject(_In_ PLib3MFModelObjectResource * pObject, _Out_ BOOL * pbIsComponentObject)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->IsComponentsObject(pbIsComponentObject);

		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_gettype(_In_ PLib3MFModelObjectResource * pObject, _Out_ DWORD * pObjectType)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->GetType(pObjectType);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_settype(_In_ PLib3MFModelObjectResource * pObject, _In_ DWORD ObjectType)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->SetType(ObjectType);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_getname(_In_ PLib3MFModelObjectResource * pObject, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->GetName(pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_getnameutf8(_In_ PLib3MFModelObjectResource * pObject, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->GetNameUTF8(pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_setname(_In_ PLib3MFModelObjectResource * pObject, _In_z_ LPCWSTR pwszPartNumber)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->SetName(pwszPartNumber);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_setnameutf8(_In_ PLib3MFModelObjectResource * pObject, _In_z_ LPCSTR pszPartNumber)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->SetNameUTF8(pszPartNumber);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_getpartnumber(_In_ PLib3MFModelObjectResource * pObject, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->GetPartNumber(pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_getpartnumberutf8(_In_ PLib3MFModelObjectResource * pObject, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->GetPartNumberUTF8(pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_setpartnumber(_In_ PLib3MFModelObjectResource * pObject, _In_z_ LPCWSTR pwszPartNumber)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->SetPartNumber(pwszPartNumber);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_setpartnumberutf8(_In_ PLib3MFModelObjectResource * pObject, _In_z_ LPCSTR pszPartNumber)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->SetPartNumberUTF8(pszPartNumber);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_isvalidobject(_In_ PLib3MFModelObjectResource * pObject, _Out_ BOOL * pbIsValid)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->IsValidObject(pbIsValid);

		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_createdefaultpropertyhandler(_In_ PLib3MFModelObjectResource * pObject, _Out_ PLib3MFDefaultPropertyHandler ** ppPropertyHandler)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->CreateDefaultPropertyHandler((ILib3MFDefaultPropertyHandler**)ppPropertyHandler);
		}



		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_object_createdefaultmultipropertyhandler(_In_ PLib3MFModelObjectResource * pObject, _In_ DWORD nChannel, _Out_ PLib3MFDefaultPropertyHandler ** ppPropertyHandler)
		{
			if (!pObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelObjectResource *)pObject)->CreateDefaultMultiPropertyHandler(nChannel, (ILib3MFDefaultPropertyHandler**)ppPropertyHandler);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_getcount(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _Out_ DWORD * pcbCount)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->GetCount(pcbCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_addmaterial(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_z_ LPCWSTR pwszName, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue, _In_ DWORD * pnResourceIndex)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->AddMaterial(pwszName, bRed, bGreen, bBlue, pnResourceIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_addmaterialutf8(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_z_ LPCSTR pszName, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue, _In_ DWORD * pnResourceIndex)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->AddMaterialUTF8(pszName, bRed, bGreen, bBlue, pnResourceIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_removematerial(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->RemoveMaterial(nIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_getname(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->GetName(nIndex, pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_getnameutf8(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->GetNameUTF8(nIndex, pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_setname(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _In_z_ LPCWSTR pwszName)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->SetName(nIndex, pwszName);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_setnameutf8(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _In_z_ LPCSTR pszName)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->SetNameUTF8(nIndex, pszName);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_setdisplaycolorrgb(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->SetDisplayColorRGB(nIndex, bRed, bGreen, bBlue);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_setdisplaycolorrgba(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _In_ BYTE bRed, _In_ BYTE bGreen, _In_ BYTE bBlue, _In_ BYTE bAlpha)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->SetDisplayColorRGBA(nIndex, bRed, bGreen, bBlue, bAlpha);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_setdisplaycolorfloatrgb(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _In_ FLOAT fRed, _In_ FLOAT fGreen, _In_ FLOAT fBlue)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->SetDisplayColorFloatRGB(nIndex, fRed, fGreen, fBlue);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_setdisplaycolorfloatrgba(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _In_ FLOAT fRed, _In_ FLOAT fGreen, _In_ FLOAT fBlue, _In_ FLOAT fAlpha)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->SetDisplayColorFloatRGBA(nIndex, fRed, fGreen, fBlue, fAlpha);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_basematerial_getdisplaycolor(_In_ PLib3MFModelBaseMaterial * pBaseMaterial, _In_ DWORD nIndex, _Out_ BYTE* pbRed, _Out_ BYTE* pbGreen, _Out_ BYTE* pbBlue, _Out_ BYTE* pbAlpha)
		{
			if (!pBaseMaterial)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBaseMaterial *)pBaseMaterial)->GetDisplayColor(nIndex, pbRed, pbGreen, pbBlue, pbAlpha);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_getpath(_In_ PLib3MFModelTexture2D * pTexture2D, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->GetPath(pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_getpathutf8(_In_ PLib3MFModelTexture2D * pTexture2D, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->GetPathUTF8(pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_setpath(_In_ PLib3MFModelTexture2D * pTexture2D, _In_z_ LPCWSTR pwszPath)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->SetPath(pwszPath);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_setpathutf8(_In_ PLib3MFModelTexture2D * pTexture2D, _In_z_ LPCSTR pszPath)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->SetPathUTF8(pszPath);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_getcontenttype(_In_ PLib3MFModelTexture2D * pTexture2D, _Out_ eModelTexture2DType * peContentType)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->GetContentType(peContentType);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_setcontenttype(_In_ PLib3MFModelTexture2D * pTexture2D, _In_ eModelTexture2DType eContentType)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->SetContentType(eContentType);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_getbox2d(_In_ PLib3MFModelTexture2D * pTexture2D, _Out_ FLOAT * pfU, _Out_ FLOAT * pfV, _Out_ FLOAT * pfWidth, _Out_ FLOAT * pfHeight)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->GetBox2D(pfU, pfV, pfWidth, pfHeight);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_setbox2d(_In_ PLib3MFModelTexture2D * pTexture2D, _In_ FLOAT fU, _In_ FLOAT fV, _In_ FLOAT fWidth, _In_ FLOAT fHeight)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->SetBox2D(fU, fV, fWidth, fHeight);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_clearbox2d(_In_ PLib3MFModelTexture2D * pTexture2D)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->ClearBox2D();
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_getstreamsize(_In_ PLib3MFModelTexture2D * pTexture2D, _Out_ ULONG64 * pcbStreamSize)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->GetStreamSize(pcbStreamSize);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_writetofile(_In_ PLib3MFModelTexture2D * pTexture2D, _In_z_ LPCWSTR pwszFilename)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->WriteToFile(pwszFilename);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_writetofileutf8(_In_ PLib3MFModelTexture2D * pTexture2D, _In_z_ LPCSTR pszFilename)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->WriteToFileUTF8(pszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_writetobuffer(_In_ PLib3MFModelTexture2D * pTexture2D, _Out_ BYTE * pBuffer, _In_ ULONG64 cbBufferSize)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->WriteToBuffer(pBuffer, cbBufferSize);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_writetocallback(_In_ PLib3MFModelTexture2D * pTexture2D, _In_ void * pWriteCallback, _In_opt_ void * pUserData)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->WriteToCallback(pWriteCallback, pUserData);

		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_readfromfile(_In_ PLib3MFModelTexture2D * pTexture2D, _In_z_ LPCWSTR pwszFilename)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->ReadFromFile(pwszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_readfromfileutf8(_In_ PLib3MFModelTexture2D * pTexture2D, _In_z_ LPCSTR pszFilename)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->ReadFromFileUTF8(pszFilename);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_texture2d_readfrombuffer(_In_ PLib3MFModelTexture2D * pTexture2D, _In_ BYTE * pBuffer, _In_ ULONG64 cbBufferSize)
		{
			if (!pTexture2D)
				return LIB3MF_POINTER;

			return ((ILib3MFModelTexture2D *)pTexture2D)->ReadFromBuffer(pBuffer, cbBufferSize);
		}




		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_getvertexcount(_In_ PLib3MFModelMeshObject * pMeshObject, _Out_ DWORD * pnVertexCount)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->GetVertexCount(pnVertexCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_gettrianglecount(_In_ PLib3MFModelMeshObject * pMeshObject, _Out_ DWORD * pnTriangleCount)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->GetTriangleCount(pnTriangleCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_getvertex(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ DWORD nIndex, _Out_ MODELMESHVERTEX * pVertex)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->GetVertex(nIndex, pVertex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_setvertex(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ DWORD nIndex, _In_ MODELMESHVERTEX * pVertex)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->SetVertex(nIndex, pVertex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_addvertex(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ MODELMESHVERTEX * pVertex, _Out_opt_ DWORD * pnIndex)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->AddVertex(pVertex, pnIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_gettriangle(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ DWORD nIndex, _Out_ MODELMESHTRIANGLE * pTriangle)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->GetTriangle(nIndex, pTriangle);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_settriangle(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ DWORD nIndex, _In_ MODELMESHTRIANGLE * pTriangle)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->SetTriangle(nIndex, pTriangle);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_addtriangle(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ MODELMESHTRIANGLE * pTriangle, _Out_opt_ DWORD * pnIndex)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->AddTriangle(pTriangle, pnIndex);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_getvertices(_In_ PLib3MFModelMeshObject * pMeshObject, _Out_ MODELMESHVERTEX * pVertices, _In_ DWORD nBufferSize, _Out_opt_ DWORD * pnVertexCount)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->GetVertices(pVertices, nBufferSize, pnVertexCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_gettriangleindices(_In_ PLib3MFModelMeshObject * pMeshObject, _Out_ MODELMESHTRIANGLE * pIndices, _In_ DWORD nBufferSize, _Out_opt_ DWORD * pnTriangleCount)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->GetTriangleIndices(pIndices, nBufferSize, pnTriangleCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_setgeometry(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ MODELMESHVERTEX * pVertices, _In_ DWORD nVertexCount, _In_ MODELMESHTRIANGLE * pTriangles, _In_ DWORD nTriangleCount)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->SetGeometry(pVertices, nVertexCount, pTriangles, nTriangleCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_createpropertyhandler(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ PLib3MFPropertyHandler ** ppPropertyHandler)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->CreatePropertyHandler((ILib3MFPropertyHandler **)ppPropertyHandler);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_createmultipropertyhandler(_In_ PLib3MFModelMeshObject * pMeshObject, _In_ DWORD nChannel, _In_ PLib3MFPropertyHandler ** ppPropertyHandler)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->CreateMultiPropertyHandler(nChannel, (ILib3MFPropertyHandler **)ppPropertyHandler);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_meshobject_ismanifoldandoriented(_In_ PLib3MFModelMeshObject * pMeshObject, _Out_ BOOL * pbIsOrientedAndManifold)
		{
			if (!pMeshObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelMeshObject *)pMeshObject)->IsManifoldAndOriented(pbIsOrientedAndManifold);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_component_getobjectresource(_In_ PLib3MFModelComponent * pComponent, _Outptr_ PLib3MFModelObjectResource ** ppObjectResource)
		{
			if (!pComponent)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponent *)pComponent)->GetObjectResource((ILib3MFModelObjectResource**)ppObjectResource);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_component_gettransform(_In_ PLib3MFModelComponent * pComponent, _Out_ MODELTRANSFORM * pTransformation)
		{
			if (!pComponent)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponent *)pComponent)->GetTransform(pTransformation);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_component_settransform(_In_ PLib3MFModelComponent * pComponent, _In_ MODELTRANSFORM * pTransformation)
		{
			if (!pComponent)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponent *)pComponent)->SetTransform(pTransformation);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_component_getobjectresourceid(_In_ PLib3MFModelComponent * pComponent, _Out_ DWORD * pnResourceID)
		{
			if (!pComponent)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponent *)pComponent)->GetObjectResourceID(pnResourceID);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_component_hastransform(_In_ PLib3MFModelComponent * pComponent, _Out_ BOOL * pbHasTransform)
		{
			if (!pComponent)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponent *)pComponent)->HasTransform(pbHasTransform);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_componentsobject_addcomponent(_In_ PLib3MFModelComponentsObject * pComponentsObject, _In_ PLib3MFModelObjectResource * pObject, _In_opt_ MODELTRANSFORM * pmTransform, _Outptr_ PLib3MFModelComponent ** ppComponent)
		{
			if (!pComponentsObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponentsObject *)pComponentsObject)->AddComponent((ILib3MFModelObjectResource*)pObject, pmTransform, (ILib3MFModelComponent**)ppComponent);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_componentsobject_getcomponent(_In_ PLib3MFModelComponentsObject * pComponentsObject, _In_ DWORD nIndex, _Outptr_ PLib3MFModelComponent ** ppComponent)
		{
			if (!pComponentsObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponentsObject *)pComponentsObject)->GetComponent(nIndex, (ILib3MFModelComponent**)ppComponent);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_componentsobject_getcomponentcount(_In_ PLib3MFModelComponentsObject * pComponentsObject, _Out_ DWORD * pComponentCount)
		{
			if (!pComponentsObject)
				return LIB3MF_POINTER;

			return ((ILib3MFModelComponentsObject *)pComponentsObject)->GetComponentCount(pComponentCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_getobjectresource(_In_ PLib3MFModelBuildItem * pBuildItem, _Outptr_ PLib3MFModelObjectResource ** ppObject)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->GetObjectResource((ILib3MFModelObjectResource **)ppObject);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_getobjectresourceid(_In_ PLib3MFModelBuildItem * pBuildItem, _Out_ DWORD * pnID)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->GetObjectResourceID(pnID);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_hasobjecttransform(_In_ PLib3MFModelBuildItem * pBuildItem, _Out_ BOOL * pbHasTransform)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->HasObjectTransform(pbHasTransform);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_getobjecttransform(_In_ PLib3MFModelBuildItem * pBuildItem, _Out_ MODELTRANSFORM * pmTransform)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->GetObjectTransform(pmTransform);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_setobjecttransform(_In_ PLib3MFModelBuildItem * pBuildItem, _In_ MODELTRANSFORM * pmTransform)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->SetObjectTransform(pmTransform);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_getpartnumber(_In_ PLib3MFModelBuildItem * pBuildItem, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_opt_ ULONG * pcbNeededChars)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->GetPartNumber(pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_getpartnumberutf8(_In_ PLib3MFModelBuildItem * pBuildItem, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_opt_ ULONG * pcbNeededChars)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->GetPartNumberUTF8(pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_setpartnumber(_In_ PLib3MFModelBuildItem * pBuildItem, _In_z_ LPCWSTR pwszPartNumber)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->SetPartNumber(pwszPartNumber);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_setpartnumberutf8(_In_ PLib3MFModelBuildItem * pBuildItem, _In_z_ LPCSTR pszPartNumber)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->SetPartNumberUTF8(pszPartNumber);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditem_gethandle(_In_ PLib3MFModelBuildItem * pBuildItem, _Out_ DWORD * pHandle)
		{
			if (!pBuildItem)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItem *)pBuildItem)->GetHandle(pHandle);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditemiterator_movenext(_In_ PLib3MFModelBuildItemIterator * pIterator, _Out_ BOOL * pbHasNext)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItemIterator *)pIterator)->MoveNext(pbHasNext);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditemiterator_moveprevious(_In_ PLib3MFModelBuildItemIterator * pIterator, _Out_ BOOL * pbHasPrevious)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItemIterator *)pIterator)->MovePrevious(pbHasPrevious);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditemiterator_getcurrent(_In_ PLib3MFModelBuildItemIterator * pIterator, _Outptr_ PLib3MFModelBuildItem ** ppResultBuildItem)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItemIterator *)pIterator)->GetCurrent((ILib3MFModelBuildItem **)ppResultBuildItem);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_builditemiterator_clone(_In_ PLib3MFModelBuildItemIterator * pIterator, _Outptr_ PLib3MFModelBuildItemIterator ** ppIterator)
		{
			if (!pIterator)
				return LIB3MF_POINTER;

			return ((ILib3MFModelBuildItemIterator *)pIterator)->Clone((ILib3MFModelBuildItemIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_setunit(_In_ PLib3MFModel * pModel, _In_ DWORD Unit)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->SetUnit(Unit);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getunit(_In_ PLib3MFModel * pModel, _Out_ DWORD * pUnit)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetUnit(pUnit);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_setlanguage(_In_ PLib3MFModel * pModel, _In_z_ LPCWSTR pwszLanguage)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->SetLanguage(pwszLanguage);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_setlanguageutf8(_In_ PLib3MFModel * pModel, _In_z_ LPCSTR pszLanguage)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->SetLanguageUTF8(pszLanguage);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getlanguage(_In_ PLib3MFModel * pModel, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_opt_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetLanguage(pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getlanguageutf8(_In_ PLib3MFModel * pModel, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_opt_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetLanguageUTF8(pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_querywriter(_In_ PLib3MFModel * pModel, _In_z_ LPCSTR pszWriterClass, _Outptr_ PLib3MFModelWriter ** ppWriter)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->QueryWriter(pszWriterClass, (ILib3MFModelWriter **)ppWriter);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_queryreader(_In_ PLib3MFModel * pModel, _In_z_ LPCSTR pszReaderClass, _Outptr_ PLib3MFModelReader ** ppReader)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->QueryReader(pszReaderClass, (ILib3MFModelReader **)ppReader);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getresourcebyid(_In_ PLib3MFModel * pModel, _In_ DWORD nResourceID, _Outptr_ PLib3MFModelResource ** ppResource)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetResourceByID(nResourceID, (ILib3MFModelResource **)ppResource);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_gettexture2dbyid(_In_ PLib3MFModel * pModel, _In_ DWORD nResourceID, _Outptr_ PLib3MFModelTexture2D ** ppTexture)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetTexture2DByID(nResourceID, (ILib3MFModelTexture2D **)ppTexture);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getbasematerialbyid(_In_ PLib3MFModel * pModel, _In_ DWORD nResourceID, _Outptr_ PLib3MFModelBaseMaterial ** ppMaterial)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetBaseMaterialByID(nResourceID, (ILib3MFModelBaseMaterial **)ppMaterial);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmeshobjectbyid(_In_ PLib3MFModel * pModel, _In_ DWORD nResourceID, _Outptr_ PLib3MFModelMeshObject ** ppMeshObject)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMeshObjectByID(nResourceID, (ILib3MFModelMeshObject **)ppMeshObject);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getcomponentsobjectbyid(_In_ PLib3MFModel * pModel, _In_ DWORD nResourceID, _Outptr_ PLib3MFModelComponentsObject ** ppComponentsObject)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetComponentsObjectByID(nResourceID, (ILib3MFModelComponentsObject **)ppComponentsObject);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getbuilditems(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelBuildItemIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetBuildItems((ILib3MFModelBuildItemIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_resources(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetResources((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getobjects(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetObjects((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmeshobjects(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMeshObjects((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getcomponentsobjects(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetComponentsObjects((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_get2dtextures(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->Get2DTextures((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getbasematerials(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelResourceIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->Get2DTextures((ILib3MFModelResourceIterator **)ppIterator);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getthumbnails(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelThumbnailIterator ** ppIterator)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetThumbnails((ILib3MFModelThumbnailIterator **)ppIterator);
		}


		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_mergetomodel(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModel ** ppMergedModel)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->MergeToModel((ILib3MFModel **)ppMergedModel);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addmeshobject(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelMeshObject ** ppMeshObject)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddMeshObject((ILib3MFModelMeshObject **)ppMeshObject);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addcomponentsobject(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelComponentsObject ** ppComponentsObject)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddComponentsObject((ILib3MFModelComponentsObject **)ppComponentsObject);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addtexture2d(_In_ PLib3MFModel * pModel, _In_z_ LPCWSTR pwszPath, _Outptr_ PLib3MFModelTexture2D ** ppTextureInstance)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddTexture2D(pwszPath, (ILib3MFModelTexture2D **)ppTextureInstance);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addtexture2dutf8(_In_ PLib3MFModel * pModel, _In_z_ LPCSTR pszPath, _Outptr_ PLib3MFModelTexture2D ** ppTextureInstance)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddTexture2DUTF8(pszPath, (ILib3MFModelTexture2D **)ppTextureInstance);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addbasematerialgroup(_In_ PLib3MFModel * pModel, _Outptr_ PLib3MFModelBaseMaterial ** ppBaseMaterialInstance)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddBaseMaterialGroup((ILib3MFModelBaseMaterial **)ppBaseMaterialInstance);
		}



		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addbuilditem(_In_ PLib3MFModel * pModel, _In_ PLib3MFModelObjectResource * pObject, _In_opt_ MODELTRANSFORM * pTransform, _Outptr_ PLib3MFModelBuildItem ** ppBuildItem)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddBuildItem((ILib3MFModelObjectResource *)pObject, pTransform, (ILib3MFModelBuildItem **)ppBuildItem);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_removebuilditem(_In_ PLib3MFModel * pModel, _In_ PLib3MFModelBuildItem * pBuildItem)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->RemoveBuildItem((ILib3MFModelBuildItem *)pBuildItem);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_gettexturestreamcount(_In_ PLib3MFModel * pModel, _Out_ DWORD * pnCount)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetTextureStreamCount(pnCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_gettexturestreamsize(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_ UINT64 * pnSize)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetTextureStreamSize(nIndex, pnSize);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_gettexturestreampath(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetTextureStreamPath(nIndex, pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_gettexturestreampathutf8(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetTextureStreamPathUTF8(nIndex, pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmetadatacount(_In_ PLib3MFModel * pModel, _Out_ DWORD * pnCount)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMetaDataCount(pnCount);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmetadatakey(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMetaDataKey(nIndex, pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmetadatakeyutf8(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMetaDataKeyUTF8(nIndex, pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmetadatavalue(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_opt_ LPWSTR pwszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMetaDataValue(nIndex, pwszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_getmetadatavalueutf8(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex, _Out_opt_ LPSTR pszBuffer, _In_ ULONG cbBufferSize, _Out_ ULONG * pcbNeededChars)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->GetMetaDataValueUTF8(nIndex, pszBuffer, cbBufferSize, pcbNeededChars);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addmetadata(_In_ PLib3MFModel * pModel, _In_ LPCWSTR pszwKey, _In_ LPCWSTR pszwValue)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddMetaData(pszwKey, pszwValue);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_addmetadatautf8(_In_ PLib3MFModel * pModel, _In_ LPCSTR pszKey, _In_ LPCSTR pszValue)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->AddMetaDataUTF8(pszKey, pszValue);
		}

		LIB3MF_DECLSPEC LIB3MFRESULT lib3mf_model_removemetadata(_In_ PLib3MFModel * pModel, _In_ DWORD nIndex)
		{
			if (!pModel)
				return LIB3MF_POINTER;

			return ((ILib3MFModel *)pModel)->RemoveMetaData(nIndex);
		}





	};

};

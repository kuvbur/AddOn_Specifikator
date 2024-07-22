//------------ kuvbur 2022 ------------
#include "DataReader.hpp"
#include "DGModule.hpp"
#include "ResourceIds.hpp"
#include "Specifikator.hpp"

static GSErrCode MenuCommandHandler (const API_MenuParams* menuParams)
{
    switch (menuParams->menuItemRef.menuResID) {
        case AddOnMenuID:
            switch (menuParams->menuItemRef.itemIndex) {
                case AddOnCommandID:
                    {
                        test ();
                    }
                    break;
            }
    }
    return NoError;
}

API_AddonType __ACDLL_CALL CheckEnvironment (API_EnvirParams* envir)
{
    RSGetIndString (&envir->addOnInfo.name, AddOnInfoID, AddOnNameID, ACAPI_GetOwnResModule ());
    RSGetIndString (&envir->addOnInfo.description, AddOnInfoID, AddOnDescriptionID, ACAPI_GetOwnResModule ());
    return APIAddon_Normal;
}

GSErrCode __ACDLL_CALL RegisterInterface (void)
{
    return ACAPI_Register_Menu (AddOnMenuID, AddOnPromtID, MenuCode_Tools, MenuFlag_Default);
}

GSErrCode __ACENV_CALL Initialize (void)
{
    return ACAPI_Install_MenuHandler (AddOnMenuID, MenuCommandHandler);
}

GSErrCode __ACENV_CALL FreeData (void)
{
    return NoError;
}
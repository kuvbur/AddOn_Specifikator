//------------ kuvbur 2022 ------------
// Файл с функциями пакетного чтения элементов, обработки критериев и записи в таблицу
#include    "ACAPinc.h"
#include    "APICommon25.h"
#include    "APIEnvir.h"
#include    "CommonFunction.hpp"
#include    "DataReader.hpp"

void test ()
{
    GS::Array<API_Guid> el;
    GS::Array<SpecTable::SpecTable> specs;
    el = GetSelectedElements2 (false, false);
    for (UInt32 i = 0; i < el.GetSize (); ++i) {
        SpecTable::SpecTable spec;
        if (GetSpecTable (el[i], spec)) specs.Push (spec);
    }
}

bool GetSpecTable (const API_Guid& elemGuid, SpecTable::SpecTable& spec)
{
    API_AddParType** addPars = NULL;
    GSErrCode err = GetGDLParameters (API_ObjectID, elemGuid, addPars);
    if (err != NoError) {
        ACAPI_DisposeAddParHdl (&addPars);
        return false;
    }
    bool flagFind = false;

    Int32	addParNum = BMGetHandleSize ((GSHandle) addPars) / sizeof (API_AddParType);
    for (Int32 i = 0; i < addParNum; ++i) {
        API_AddParType& actualParam = (*addPars)[i];
        if (CHCompareCStrings (actualParam.name, "specifikator_table_version", CS_CaseInsensitive) == 1) {
            flagFind = true;
            spec.version = (int) actualParam.value.real;
            break;
        }
    }
    if (!flagFind) {
        ACAPI_DisposeAddParHdl (&addPars);
        return false;
    }
    for (Int32 i = 0; i < addParNum; ++i) {
        API_AddParType& actualParam = (*addPars)[i];
        if (CHCompareCStrings (actualParam.name, "spec_filter_izd", CS_CaseSensitive) == 1) {
            spec.filter_izd = !is_equal (0, actualParam.value.real);
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_subpos", CS_CaseSensitive) == 1) {
            spec.filter_subpos = !is_equal (0, actualParam.value.real);
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_mat", CS_CaseSensitive) == 1) {
            spec.filter_mat = !is_equal (0, actualParam.value.real);
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_prokat", CS_CaseSensitive) == 1) {
            spec.filter_prokat = !is_equal (0, actualParam.value.real);
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_arm", CS_CaseSensitive) == 1) {
            spec.filter_arm = !is_equal (0, actualParam.value.real);
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_layercomb", CS_CaseSensitive) == 1) {
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_subposname_add", CS_CaseSensitive) == 1) {
        }
        if (CHCompareCStrings (actualParam.name, "spec_filter_subposname_ignore", CS_CaseSensitive) == 1) {
        }
        if (CHCompareCStrings (actualParam.name, "spec_type", CS_CaseSensitive) == 1) {
            spec.type = (int) actualParam.value.real;
        }
    }

    return true;
}

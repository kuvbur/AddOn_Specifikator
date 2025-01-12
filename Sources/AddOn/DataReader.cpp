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
        API_AddParType** addPars = NULL;
        if (GetGDLParameters (API_ObjectID, el[i], addPars) == NoError) {
            Int32 spectable_version = SpecTable::GetSpecTableVersion (addPars);
            if (spectable_version > 0) {
                SpecTable::SpecTable spec;
                spec.version = spectable_version;
                if (SpecTable::GetSpecTable (addPars, spec)) specs.Push (spec);
            }
        }
        ACAPI_DisposeAddParHdl (&addPars);
    }
}

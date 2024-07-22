//------------ kuvbur 2022 ------------
#include	"ACAPinc.h"
#include	"APICommon25.h"
#include	"APIEnvir.h"

#include "DataWriter.hpp"
#include "ResourceIds.hpp"

namespace TableElement
{
bool GetClassification (API_Guid& system, API_Guid& classif)
{
    GSErrCode err = NoError;
    GS::Array<API_ClassificationSystem> systems;
    err = ACAPI_Classification_GetClassificationSystems (systems);
    if (err != NoError) return false;
    for (UIndex i = 0; i < systems.GetSize (); ++i) {
        GS::UniString systemname = systems[i].name.ToLowerCase ();
        if (systemname.Contains ("specifikator")) {
            system = systems[i].guid;
            GS::Array<API_ClassificationItem> rootItems;
            err = ACAPI_Classification_GetClassificationSystemRootItems (systems[i].guid, rootItems);
            if (err != NoError) return false;
            for (UIndex j = 0; j < rootItems.GetSize (); ++j) {
                GS::UniString classname = rootItems[j].id.ToLowerCase ();
                if (classname.Contains ("data")) {
                    classif = rootItems[j].guid;
                    return true;
                }
            }
        }
    }
    return false;
}

bool GetTableDataDict (TableDataDict& tabledefinitions)
{
    GS::Array<API_PropertyDefinition> alldefinitions;
    if (ACAPI_Property_GetPropertyDefinitions (APINULLGuid, alldefinitions) != NoError) return false;
    for (UInt32 j = 0; j < alldefinitions.GetSize (); j++) {
        GS::UniString alldefinitions[j].description
            if (alldefinitions[j].description.Contains ())
    }
}
void PlaceElement ()
{
    API_Guid system, classif;
    TableDataDict tabledefinitions;
    if (!GetClassification (system, classif)) return;

    int hh = 1;
}
}


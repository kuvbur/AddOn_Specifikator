//------------ kuvbur 2022 ------------
#include	"APIEnvir.h"
#include	"ACAPinc.h"
#include	"APICommon25.h"

#include "ResourceIds.hpp"
#include "DataReader.hpp"
#include "Common_func.hpp"

//static const GSCharCode GChCode = CC_Cyrillic;

typedef struct
{
    GS::UniString code = "";
    GS::UniString keycode = "";
    GS::UniString dbset = "";
    GS::UniString name = "";
    double qty = 0;
} Component_old;


void test() {
	GS::Array<API_Guid> el;
	el = GetSelectedElements();
	for (UInt32 i = 0; i < el.GetSize(); ++i) {
		API_Guid elemGuid = el[i];
		Get_Qty(elemGuid);
	}
}


ElementReader::ElementReader(API_Guid elemGuid)
{
    API_Elem_Head elemHead = {};
    BNZeroMemory(&elemHead, sizeof(API_Elem_Head));
    elemHead.guid = elemGuid;
}

ElementReader::~ElementReader()
{
}



GSErrCode GetDescritors(const API_Elem_Head& elemHead, GS::Array<Component_old> &comps) {
    GSErrCode err = NoError;
    API_DescriptorRefType** descRefs;
    Int32 nDesc;
    err = ACAPI_Element_GetDescriptors(&elemHead, &descRefs, &nDesc);
    if (err == NoError) {
        for (Int32 i = 0; i < nDesc; i++) {
            if ((*descRefs)[i].status != APIDBRef_Deleted) {
                API_ListData listdata;
                BNZeroMemory(&listdata, sizeof(API_ListData));
                listdata.header.typeID = API_DescriptorID;
                listdata.header.index = (*descRefs)[i].index;
                listdata.header.setIndex = (*descRefs)[i].setIndex;
                switch ((*descRefs)[i].status) {
                case APIDBRef_Normal:
                    err = ACAPI_ListData_Get(&listdata);
                    break;
                case APIDBRef_Local:
                    err = ACAPI_ListData_GetLocal((*descRefs)[i].libIndex, &elemHead, &listdata);
                    break;
                }
                if (err != NoError)
                    break;
                if (err == NoError) {
                    Component_old comp;
                    char tcode[API_DBCodeLen];
                    CHTruncate(listdata.descriptor.code, tcode, API_DBCodeLen);
                    comp.code = GS::UniString(tcode);

                    char tkeycode[API_DBCodeLen];
                    CHTruncate(listdata.descriptor.keycode, tkeycode, API_DBCodeLen);
                    comp.keycode = GS::UniString(tkeycode);

                    char tname[API_UAddParNumDescLen];
                    CHTruncate(*listdata.descriptor.name, tname, API_DBNameLen);
                    comp.name = GS::UniString(tname);

                    char tdbSetName[API_DBCodeLen];
                    CHTruncate(listdata.descriptor.dbSetName, tdbSetName, API_DBCodeLen);
                    comp.dbset = GS::UniString(tdbSetName);

                    comp.qty = 0;
                    comps.Push(comp);
                }
            }
        }
    }
    BMKillHandle((GSHandle*)&descRefs);
    return err;
}

GSErrCode GetObsoleteComponents(const API_Elem_Head& elemHead, GS::Array<Component_old> &comps) {
    GSErrCode err = NoError;
    API_Obsolete_ComponentRefType** compRefs;
    Int32 nComp;
    err = ACAPI_Element_GetComponents_Obsolete(&elemHead, &compRefs, &nComp);
    if (err == NoError) {
        for (Int32 i = 0; i < nComp; i++) {
            if ((*compRefs)[i].status != APIDBRef_Deleted) {
                API_ListData listdata;
                BNZeroMemory(&listdata, sizeof(API_ListData));
                listdata.header.typeID = API_Obsolete_ComponentID;
                listdata.header.index = (*compRefs)[i].index;
                listdata.header.setIndex = (*compRefs)[i].setIndex;
                switch ((*compRefs)[i].status) {
                case APIDBRef_Normal:
                    err = ACAPI_ListData_Get(&listdata);
                    break;
                case APIDBRef_Local:
                    err = ACAPI_ListData_GetLocal((*compRefs)[i].libIndex, &elemHead, &listdata);
                    break;
                }
                if (err != NoError)
                    break;
                if (err == NoError) {
                    Component_old comp;

                    char tcode[API_DBCodeLen];
                    CHTruncate(listdata.component.code, tcode, API_DBCodeLen);
                    comp.code = GS::UniString(tcode);

                    char tkeycode[API_DBCodeLen];
                    CHTruncate(listdata.component.keycode, tkeycode, API_DBCodeLen);
                    comp.keycode = GS::UniString(tkeycode);

                    char tname[API_DBNameLen];
                    CHTruncate(listdata.component.name, tname, API_DBNameLen);
                    comp.name = GS::UniString(tname);

                    char tdbSetName[API_DBCodeLen];
                    CHTruncate(listdata.component.dbSetName, tdbSetName, API_DBCodeLen);
                    comp.dbset = GS::UniString(tdbSetName);

                    comp.qty = listdata.component.quantity;
                    comps.Push(comp);
                }
            }
        }
    }
    BMKillHandle((GSHandle*)&compRefs);
    return err;
}


void Get_Qty(API_Guid elemGuid) {
    GSErrCode err = NoError;

	API_Elem_Head elemHead = {};
	BNZeroMemory(&elemHead, sizeof(API_Elem_Head));
    elemHead.guid = elemGuid;

    GS::Array<Component_old> desc;
    err = GetDescritors(elemHead, desc);

    GS::Array<Component_old> comps;
    err = GetObsoleteComponents(elemHead, comps);
    int hh = 1;
}
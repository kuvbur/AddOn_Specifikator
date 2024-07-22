#include "ElementReader.hpp"

// ���� ��� ������ ������ ������ ��������

namespace ReaderData
{
ElementReader::ElementReader (API_Guid elemGuid)
{
    BNZeroMemory (&this->elemHead, sizeof (API_Elem_Head));
    this->elemGuid = elemGuid;
    this->elemHead.guid = elemGuid;
    if (ACAPI_Element_GetHeader (&this->elemHead) != NoError) {
        this->is_Ok = false;
    } else {
        SetPossibleDataByType ();
    }
}

ElementReader::~ElementReader ()
{
}

void ElementReader::SetPossibleDataByType ()
{
    API_ElemTypeID eltype = this->elemHead.typeID;
    // ����������� �� ��������� ����
    if (eltype == API_DimensionID ||
        eltype == API_RadialDimensionID ||
        eltype == API_LevelDimensionID ||
        eltype == API_AngleDimensionID ||
        eltype == API_TextID ||
        eltype == API_LabelID ||
        eltype == API_HotspotID ||
        eltype == API_CutPlaneID ||
        eltype == API_CameraID ||
        eltype == API_CamSetID ||
        eltype == API_GroupID ||
        eltype == API_SectElemID ||
        eltype == API_DrawingID ||
        eltype == API_PictureID ||
        eltype == API_DetailID ||
        eltype == API_ElevationID ||
        eltype == API_InteriorElevationID ||
        eltype == API_WorksheetID ||
        eltype == API_HotlinkID ||
        eltype == API_ZombieElemID ||
        eltype == API_AnalyticalSupportID ||
        eltype == API_AnalyticalLinkID ||
        eltype == API_AnalyticalPointLoadID ||
        eltype == API_AnalyticalEdgeLoadID ||
        eltype == API_AnalyticalSurfaceLoadID ||
        eltype == API_ChangeMarkerID) {
        this->is_Ignore = true;
        this->statusObsoleteComponents = DataNotNeed;
        this->statusDescriptors = DataNotNeed;
        return;
    }
    // ��������� ���������, ������������ � ���������� GDL
    if (eltype == API_ObjectID ||
       eltype == API_WindowID ||
       eltype == API_DoorID ||
       eltype == API_LampID ||
       eltype == API_ZoneID ||
       eltype == API_CurtainWallPanelID) {
        this->statusObsoleteComponents = DataUndefined;
        this->statusDescriptors = DataUndefined;
    }
}

bool ElementReader::Read ()
{
    bool bdescriptorsStatus = GetDescriptorsStatus ();
    bool bobsoleteComponentsStatus = GetObsoleteComponentsStatus ();
    return bdescriptorsStatus && bobsoleteComponentsStatus;
}

bool ElementReader::GetDescriptorsStatus ()
{
    if (this->is_Ok == false) return false;
    if (this->statusDescriptors == DataUndefined) {
        this->statusDescriptors = this->ReadDescriptors (this->descriptors);
    }
    return (this->statusDescriptors == DataRead);
}
bool ElementReader::GetObsoleteComponentsStatus ()
{
    if (this->is_Ok == false) return false;
    if (this->statusObsoleteComponents == DataUndefined) {
        this->statusObsoleteComponents = this->ReadObsoleteComponents (this->obsoleteComponents);
    }
    return (this->statusObsoleteComponents == DataRead);
}

DataStatus ElementReader::ReadDescriptors (ComponentObsoleteDict& comps)
{
    GSErrCode err = NoError;
    API_DescriptorRefType** descRefs;
    Int32 nDesc;
    err = ACAPI_Element_GetDescriptors (&this->elemHead, &descRefs, &nDesc);
    if (err == NoError) {
        for (Int32 i = 0; i < nDesc; i++) {
            if ((*descRefs)[i].status != APIDBRef_Deleted) {
                API_ListData listdata;
                BNZeroMemory (&listdata, sizeof (API_ListData));
                listdata.header.typeID = API_DescriptorID;
                listdata.header.index = (*descRefs)[i].index;
                listdata.header.setIndex = (*descRefs)[i].setIndex;
                switch ((*descRefs)[i].status) {
                    case APIDBRef_Normal:
                        err = ACAPI_ListData_Get (&listdata);
                        break;
                    case APIDBRef_Local:
                        err = ACAPI_ListData_GetLocal ((*descRefs)[i].libIndex, &this->elemHead, &listdata);
                        break;
                }
                if (err != NoError)
                    break;
                if (err == NoError) {
                    ComponentObsolete comp;
                    char tcode[API_DBCodeLen];
                    CHTruncate (listdata.descriptor.code, tcode, API_DBCodeLen);
                    comp.code = GS::UniString (tcode);

                    char tkeycode[API_DBCodeLen];
                    CHTruncate (listdata.descriptor.keycode, tkeycode, API_DBCodeLen);
                    comp.keycode = GS::UniString (tkeycode);

                    char tname[API_UAddParNumDescLen];
                    CHTruncate (*listdata.descriptor.name, tname, API_DBNameLen);
                    comp.name = GS::UniString (tname);

                    comp.qty = 0;
                    GS::UniString key = comp.code + "@" + comp.keycode;
                    if (!comps.ContainsKey (key)) comps.Add (key, comp);
                }
            }
        }
    }
    BMKillHandle ((GSHandle*) &descRefs);
    return (err == NoError && !comps.IsEmpty ()) ? DataRead : DataUnavailable;
}

DataStatus ElementReader::ReadObsoleteComponents (ComponentObsoleteDict& comps)
{
    GSErrCode err = NoError;
    API_Obsolete_ComponentRefType** compRefs;
    Int32 nComp;
    err = ACAPI_Element_GetComponents_Obsolete (&this->elemHead, &compRefs, &nComp);
    if (err == NoError) {
        for (Int32 i = 0; i < nComp; i++) {
            if ((*compRefs)[i].status != APIDBRef_Deleted) {
                API_ListData listdata;
                BNZeroMemory (&listdata, sizeof (API_ListData));
                listdata.header.typeID = API_Obsolete_ComponentID;
                listdata.header.index = (*compRefs)[i].index;
                listdata.header.setIndex = (*compRefs)[i].setIndex;
                switch ((*compRefs)[i].status) {
                    case APIDBRef_Normal:
                        err = ACAPI_ListData_Get (&listdata);
                        break;
                    case APIDBRef_Local:
                        err = ACAPI_ListData_GetLocal ((*compRefs)[i].libIndex, &this->elemHead, &listdata);
                        break;
                }
                if (err != NoError)
                    break;
                if (err == NoError) {
                    ComponentObsolete comp;

                    char tcode[API_DBCodeLen];
                    CHTruncate (listdata.component.code, tcode, API_DBCodeLen);
                    comp.code = GS::UniString (tcode);

                    char tkeycode[API_DBCodeLen];
                    CHTruncate (listdata.component.keycode, tkeycode, API_DBCodeLen);
                    comp.keycode = GS::UniString (tkeycode);

                    char tname[API_DBNameLen];
                    CHTruncate (listdata.component.name, tname, API_DBNameLen);
                    comp.name = GS::UniString (tname);

                    comp.qty = listdata.component.quantity;
                    GS::UniString key = comp.code + "@" + comp.keycode + "@" + comp.name;
                    if (!comps.ContainsKey (key)) {
                        comps.Add (key, comp);
                    } else {
                        comps.Get (key).qty += comp.qty;
                    }
                }
            }
        }
    }
    return (err == NoError && !comps.IsEmpty ()) ? DataRead : DataUnavailable;
}
}
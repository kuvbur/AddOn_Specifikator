#pragma once
#if !defined (ELEMENTREADER_HPP)
#define	ELEMENTREADER_HPP

#include	"ACAPinc.h"
#include	"APICommon25.h"
#include	"APIEnvir.h"
#include	"DataTypes.hpp"
#include	"ResourceIds.hpp"

namespace ReaderData
{
class ElementReader
{
private:
    // ���������� ��������� ����������� ������ �� ��������� ����
    void SetPossibleDataByType ();
    // ������ ���������� ���������
    DataStatus statusObsoleteComponents = DataUndefined;
    // ��������� ����������
    ComponentObsoleteDict obsoleteComponents;
    // ������ ���������
    DataStatus ElementReader::ReadObsoleteComponents (ComponentObsoleteDict& comps);
    // ��������� ������� ���������� ���������
    // ���� ������� �� ��������� � ������ �� ������� - ��������� ��
    bool GetObsoleteComponentsStatus ();
    // ������ ��������� ������������
    DataStatus statusDescriptors = DataUndefined;
    // ��������� �����������
    ComponentObsoleteDict descriptors;
    DataStatus ElementReader::ReadDescriptors (ComponentObsoleteDict& comps);
    // ��������� ������� ���������� ������������
    // ���� ������� �� ��������� � ������ �� ������� - ��������� ��
    bool GetDescriptorsStatus ();

protected:

    API_Guid elemGuid = APINULLGuid;
    API_Elem_Head elemHead = {};
public:
    virtual ~ElementReader ();
    bool Read ();
    ElementReader (API_Guid elemGuid);
    bool is_Ignore = false; // ������������ ������� �� ���������
    bool is_Ok = true; // ������������ ������� �� ������
};
}

#endif


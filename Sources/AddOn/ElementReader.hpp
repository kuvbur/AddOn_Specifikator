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
    API_Guid elemGuid = APINULLGuid;
    API_Elem_Head elemHead = {};
    ValuesDict data;
    // Назначение возможных считываемых данных на основании типа
    void SetPossibleDataByType ();
    // Статус считывания компонент
    DataStatus statusObsoleteComponents = DataUndefined;
    // Чтение компонент
    DataStatus ElementReader::ReadObsoleteComponents ();
    // Получение статуса считывания компонент
    // Если элемент не ошибочный и данные не считаны - считывает их
    bool GetObsoleteComponentsStatus ();
    // Статус считанных дескрипторов
    DataStatus statusDescriptors = DataUndefined;
    // Считанные дескрипторы
    DataStatus ElementReader::ReadDescriptors ();
    // Получение статуса считывания дескрипторов
    // Если элемент не ошибочный и данные не считаны - считывает их
    bool GetDescriptorsStatus ();

    DataStatus ReadGDLParameters ();
    DataStatus statusGDLParameters = DataUndefined;
    Values GetValues (API_Obsolete_ComponentType& component);
    Values GetValues (API_DescriptorType& descriptor);

public:

    virtual ~ElementReader ();
    bool Read ();
    ElementReader (API_Guid elemGuid);
    bool is_Ignore = false; // Игнорировать элемент по критериям
    bool is_Ok = true; // Игнорировать элемент по ошибке
};
}

#endif


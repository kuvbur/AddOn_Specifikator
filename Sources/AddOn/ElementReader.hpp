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
    // Назначение возможных считываемых данных на основании типа
    void SetPossibleDataByType ();
    // Статус считывания компонент
    DataStatus statusObsoleteComponents = DataUndefined;
    // Считанные компоненты
    ComponentObsoleteDict obsoleteComponents;
    // Чтение компонент
    DataStatus ElementReader::ReadObsoleteComponents (ComponentObsoleteDict& comps);
    // Получение статуса считывания компонент
    // Если элемент не ошибочный и данные не считаны - считывает их
    bool GetObsoleteComponentsStatus ();
    // Статус считанных дескрипторов
    DataStatus statusDescriptors = DataUndefined;
    // Считанные дескрипторы
    ComponentObsoleteDict descriptors;
    DataStatus ElementReader::ReadDescriptors (ComponentObsoleteDict& comps);
    // Получение статуса считывания дескрипторов
    // Если элемент не ошибочный и данные не считаны - считывает их
    bool GetDescriptorsStatus ();

protected:

    API_Guid elemGuid = APINULLGuid;
    API_Elem_Head elemHead = {};
public:
    virtual ~ElementReader ();
    bool Read ();
    ElementReader (API_Guid elemGuid);
    bool is_Ignore = false; // Игнорировать элемент по критериям
    bool is_Ok = true; // Игнорировать элемент по ошибке
};
}

#endif


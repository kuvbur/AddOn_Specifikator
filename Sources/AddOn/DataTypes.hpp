#pragma once
#if !defined (DATATYPE_HPP)
#define	DATATYPE_HPP

// Заголовочный файл для общих структур
#include    "ACAPinc.h"
#include    "APICommon25.h"
#include    "APIEnvir.h"
#include    "DGModule.hpp"
#include    "ResourceIds.hpp"

namespace ReaderData
{
typedef enum
{
    DataUndefined = 0, // Данные не считаны
    DataUnavailable = 1, // Данные недоступны
    DataRead = 2, // Данные успешно считаны
    DataNotNeed = 3, // Считывание данных не требуется
} DataStatus; // Статус считанных данных

typedef struct
{
    GS::UniString code = "";
    GS::UniString keycode = "";
    GS::UniString name = "";
    double qty = 0;
} ComponentObsolete; // Данные компонентов и дескрипторов

// Словарь с дескрипторами и компонентами
// Формат ключа - code + "@" + keycode + "@" + name
typedef GS::HashTable<GS::UniString, ComponentObsolete> ComponentObsoleteDict;
}

namespace TableElement
{
typedef struct
{
    API_PropertyDefinition text;
    API_PropertyDefinition num;
    short inx = 0;
} TableData;
typedef GS::HashTable<short, TableData> TableDataDict;
}

#endif

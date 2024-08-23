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
typedef struct
{
    GS::UniString unit = ""; // Единица измерения
    FormatString stringformat; //Формат вывода
    double qtyraw = 0; //Неокруглённое значение
    double qtyrounded = 0; //Округлённое значение
} QTY; // Структура для хранения данных о количестве

typedef enum
{
    DataUndefined = 0, // Данные не считаны
    DataUnavailable = 1, // Данные недоступны
    DataRead = 2, // Данные успешно считаны
    DataNotNeed = 3, // Считывание данных не требуется
} DataStatus; // Статус считанных данных

typedef struct
{
    GS::UniString key = ""; // Имя переменной
    GS::UniString code = ""; // Имя переменной
    GS::UniString keycode = ""; // Тип выводимых данных
    GS::UniString value = ""; // Значение переменной
    QTY qty;
} Values; // Данные

// Формат ключа - code + "@" + keycode + "@" + unit
typedef GS::HashTable<GS::UniString, Values> ValuesDict;

QTY operator+ (const QTY& lhs, const QTY& rhs);
QTY operator+= (const QTY& lhs, const QTY& rhs);
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

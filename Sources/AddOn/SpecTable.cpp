#include "CommonFunction.hpp"
#include "SpecTable.hpp"

// Файл для класса таблицы спецификации
namespace SpecTable
{
// Получение версии таблицы. Если переменная с версией не найдена - возвращает 0
Int32 GetSpecTableVersion (API_AddParType**& addPars)
{
    Int32 addParNum = BMGetHandleSize ((GSHandle) addPars) / sizeof (API_AddParType);
    for (Int32 i = 0; i < addParNum; ++i) {
        if (CHEqualCStrings ((*addPars)[i].name, "specifikator_table_version", CS_CaseInsensitive) == 1) {
            return (Int32) (*addPars)[i].value.real;
        }
    }
    return 0;
}

bool GetSpecTable (API_AddParType**& addPars, SpecTable& spec)
{
    Int32 addParNum = BMGetHandleSize ((GSHandle) addPars) / sizeof (API_AddParType);
    for (Int32 i = 0; i < addParNum; ++i) {
        API_AddParType& actualParam = (*addPars)[i];
        if (CHEqualCStrings (actualParam.name, "spec_filter_izd", CS_CaseSensitive) == 1) {
            spec.filter_izd = !is_equal (0, actualParam.value.real);
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_subpos", CS_CaseSensitive) == 1) {
            spec.filter_subpos = !is_equal (0, actualParam.value.real);
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_mat", CS_CaseSensitive) == 1) {
            spec.filter_mat = !is_equal (0, actualParam.value.real);
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_prokat", CS_CaseSensitive) == 1) {
            spec.filter_prokat = !is_equal (0, actualParam.value.real);
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_arm", CS_CaseSensitive) == 1) {
            spec.filter_arm = !is_equal (0, actualParam.value.real);
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_layercomb", CS_CaseSensitive) == 1) {
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_subposname_add", CS_CaseSensitive) == 1) {
        }
        if (CHEqualCStrings (actualParam.name, "spec_filter_subposname_ignore", CS_CaseSensitive) == 1) {
        }
        if (CHEqualCStrings (actualParam.name, "spec_type", CS_CaseSensitive) == 1) {
            spec.type = (int) actualParam.value.real;
        }
    }
    return true;
}



SpecTable::SpecTable ()
{
}

SpecTable::~SpecTable ()
{
}
}
#pragma once
#if !defined (SPECTABLE_HPP)
#define	SPECTABLE_HPP

#include    "ACAPinc.h"
#include    "APICommon25.h"
#include    "APIEnvir.h"
#include    "DataTypes.hpp"
#include    "DataTypes.hpp"
#include    "ResourceIds.hpp"

namespace SpecTable
{
class SpecTable
{
private:

public:
    virtual ~SpecTable ();
    SpecTable ();
    int version = 0;
    bool filter_izd = true;
    bool filter_subpos = true;
    bool filter_mat = true;
    bool filter_prokat = true;
    bool filter_arm = true;
    int type = 0;
    GS::Array<GS::UniString> filter_subposname_add;
    GS::Array<GS::UniString> filter_subposname_ignore;
};

// ѕолучение версии таблицы. ≈сли переменна€ с версией не найдена - возвращает 0
Int32 GetSpecTableVersion (API_AddParType**& addPars);
bool GetSpecTable (API_AddParType**& addPars, SpecTable& spec);

}
#endif


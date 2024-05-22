#pragma once
#if !defined (DATATYPE_HPP)
#define	DATATYPE_HPP

#include	"APIEnvir.h"
#include	"ACAPinc.h"
#include	"APICommon25.h"
#include	"ResourceIds.hpp"

static const GSCharCode GChCode = CC_Cyrillic;

namespace ReaderData
{
    typedef enum {
        DataUndefined = 0,
        DataUnavailable = 1,
        DataRead = 2,
        DataNotNeed = 3,
    } DataStatus;

    typedef struct
    {
        GS::UniString code = "";
        GS::UniString keycode = "";
        GS::UniString name = "";
        double qty = 0;
    } ComponentObsolete;

    typedef GS::HashTable<GS::UniString, ComponentObsolete> ComponentObsoleteDict;
}

#endif

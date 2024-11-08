//------------ kuvbur 2022 ------------
#pragma once

#ifndef DATAREADER_HPP
#define	DATAREADER_HPP
#include	"ACAPinc.h"
#include	"APIEnvir.h"
#ifdef AC_25
#include	"APICommon25.h"
#endif // AC_25
#ifdef AC_26
#include	"APICommon26.h"
#endif // AC_26
#include	"DG.h"
#include	"StringConversion.hpp"
#include	"ResourceIds.hpp"
#include	"CommonFunction.hpp"
#include    "DataTypes.hpp"
#include    "SpecTable.hpp"

void test ();

bool GetSpecTable (const API_Guid& elemGuid, SpecTable::SpecTable& spec);

#endif



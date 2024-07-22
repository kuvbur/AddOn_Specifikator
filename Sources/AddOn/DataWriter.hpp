//------------ kuvbur 2022 ------------
#pragma once

#ifndef DATAWRITER_HPP
#define	DATAWRITER_HPP
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

namespace TableElement
{
bool GetClassification (API_Guid& system, API_Guid& classif);
void PlaceElement ();
}
#endif



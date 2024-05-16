//------------ kuvbur 2022 ------------
#pragma once

#ifndef DATAREADER_HPP
#define	DATAREADER_HPP
#include	"APIEnvir.h"
#include	"ACAPinc.h"
#ifdef AC_25
#include	"APICommon25.h"
#endif // AC_25
#ifdef AC_26
#include	"APICommon26.h"
#endif // AC_26
#include	"DG.h"
#include	"StringConversion.hpp"
#include	"ResourceIds.hpp"

void test();

void Get_Qty(API_Guid elemGuid);

class ElementReader
{
protected:
	const API_Guid elemGuid = APINULLGuid;
	API_Elem_Head elemHead = {};
public:
	ElementReader(API_Guid elemGuid);
	virtual ~ElementReader();

};

#endif



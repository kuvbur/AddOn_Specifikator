#pragma once
#if !defined (COMMON_HPP)
#define	COMMON_HPP
#ifdef AC_25
#include	"APICommon25.h"
#endif // AC_25
#ifdef AC_26
#include	"APICommon26.h"
#endif // AC_26
#include	"ResourceIds.hpp"

GS::Array<API_Guid> GetSelectedElements(bool assertIfNoSel, bool onlyEditable);

#endif



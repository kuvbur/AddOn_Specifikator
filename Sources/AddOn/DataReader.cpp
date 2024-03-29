//------------ kuvbur 2022 ------------
#include	"APIEnvir.h"
#include	"ACAPinc.h"
#include	"APICommon25.h"

#include "ResourceIds.hpp"
#include "DataReader.hpp"
#include "Common_func.hpp"
void test() {
	GS::Array<API_Guid> el;
	el = GetSelectedElements();
	for (UInt32 i = 0; i < el.GetSize(); ++i) {
		API_Guid elemGuid = el[i];
		Get_Qty(elemGuid);
	}
}

void Get_Qty(API_Guid elemGuid) {
}
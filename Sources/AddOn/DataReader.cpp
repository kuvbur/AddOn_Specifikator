//------------ kuvbur 2022 ------------
#include	"APIEnvir.h"
#include	"ACAPinc.h"
#include	"APICommon25.h"

#include "ResourceIds.hpp"
#include "DataReader.hpp"
#include "ElementReader.hpp"

void test() {
	GS::Array<API_Guid> el;
    GS::Array<ReaderData::ElementReader> els;
	el = GetSelectedElements();
	for (UInt32 i = 0; i < el.GetSize(); ++i) {
		API_Guid elemGuid = el[i];
        ReaderData::ElementReader ell = ReaderData::ElementReader(elemGuid);
        if (ell.is_Ok && !ell.is_Ignore) els.Push(ell);
	}
	for (UInt32 i = 0; i < els.GetSize(); ++i) {
		els[i].Read();
	}
}

namespace ReaderData {
	namespace ReaderData {
		class ElementReader {
		private:
			void SetPossibleDataByType();
			// Работа с компонентами
			DataStatus statusObsoleteComponents = DataUndefined;
			ComponentObsoleteDict obsoleteComponents;
			DataStatus ElementReader::ReadObsoleteComponents(ComponentObsoleteDict& comps);
			bool GetObsoleteComponentsStatus();
			// Работа с дескрипторами
			DataStatus statusDescriptors = DataUndefined;
			ComponentObsoleteDict descriptors;
			DataStatus ElementReader::ReadDescriptors(ComponentObsoleteDict& comps);
			bool GetDescriptorsStatus();

		protected:

			API_Guid elemGuid = APINULLGuid;
			API_Elem_Head elemHead = {};
		public:
			virtual ~ElementReader();
			bool Read();
			ElementReader(API_Guid elemGuid);
			bool is_Ignore = false;
			bool is_Ok = true;
		};
	}
}
//------------ kuvbur 2022 ------------
#include "ResourceIds.hpp"
#include "DataReader.hpp"
#include "Common_func.hpp"
#ifdef AC_25
#include	"APICommon25.h"
#endif // AC_25
#ifdef AC_26
#include	"APICommon26.h"
#endif // AC_26
void test() {
	GS::Array<API_Guid> el;
	el = GetSelectedElements(false, false);
	for (UInt32 i = 0; i < el.GetSize(); ++i) {
		API_Guid elemGuid = el[i];

		GS::Array<API_ElemComponentID> elemComponents;
		if (ACAPI_Element_GetComponents(elemGuid, elemComponents) != NoError) {
			WriteReport_Alert("Failed to get components of element");
			return;
		}

		for (const auto& elemComponent : elemComponents) {
			const GS::UniString componentGuid = APIGuid2GSGuid(elemComponent.componentID.componentGuid).ToUniString();
			WriteReport_Alert("Properties of component with guid %s", componentGuid.ToCStr().Get());

			GS::Array<API_PropertyDefinition> propertyDefinitions;
			if (ACAPI_ElemComponent_GetPropertyDefinitions(elemComponent, API_PropertyDefinitionFilter_All, propertyDefinitions) != NoError) {
				WriteReport_Alert("Failed to get property definitions for component with guid %s", componentGuid.ToCStr().Get());
				return;
			}

			GS::Array<API_Property> properties;
			if (ACAPI_ElemComponent_GetPropertyValues(elemComponent, propertyDefinitions, properties) != NoError) {
				WriteReport_Alert("Failed to get property values for component with guid %s", componentGuid.ToCStr().Get());
				return;
			}

			for (const API_Property& property : properties) {
				API_PropertyGroup group = {};
				group.guid = property.definition.groupGuid;
				if (ACAPI_Property_GetPropertyGroup(group) != NoError) {
					continue;
				}

				GS::UniString propertyValue;
				ACAPI_Property_GetPropertyValueString(property, &propertyValue);
				WriteReport_Alert("(%s) %s: %s", group.name.ToCStr().Get(), property.definition.name.ToCStr().Get(), propertyValue.ToCStr().Get());
			}
		}
	}
}
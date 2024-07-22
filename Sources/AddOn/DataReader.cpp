//------------ kuvbur 2022 ------------
// Файл с функциями пакетного чтения элементов, обработки критериев и записи в таблицу
#include	"ACAPinc.h"
#include	"APICommon25.h"
#include	"APIEnvir.h"

#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "ElementReader.hpp"
#include "ResourceIds.hpp"

void test ()
{
    GS::Array<API_Guid> el;
    GS::Array<ReaderData::ElementReader> els;
    el = GetSelectedElements ();
    for (UInt32 i = 0; i < el.GetSize (); ++i) {
        API_Guid elemGuid = el[i];
        ReaderData::ElementReader ell = ReaderData::ElementReader (elemGuid);
        if (ell.is_Ok && !ell.is_Ignore) els.Push (ell);
    }
    for (UInt32 i = 0; i < els.GetSize (); ++i) {
        els[i].Read ();
    }
    TableElement::PlaceElement ();
}
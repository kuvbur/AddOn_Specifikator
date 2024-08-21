//------------ kuvbur 2022 ------------
#pragma once

#ifndef JSONPARSE_HPP
#define	JSONPARSE_HPP
#include    "ACAPinc.h"
#include    "APIEnvir.h"
#ifdef AC_25
#include    "APICommon25.h"
#endif // AC_25
#ifdef AC_26
#include    "APICommon26.h"
#endif // AC_26
#include    "DG.h"
#include    "StringConversion.hpp"
#include    "ResourceIds.hpp"
#include    "CommonFunction.hpp"
#include    "FileSystem.hpp"
#include    "json.h"
#include    <fstream>
#include    "DGFileDialog.hpp"

static GSErrCode GetJSONFileLocation (DG::FileDialog::Type type, const GS::UniString& title, IO::Location& JSONFilePath);
GSErrCode ParseJSON ();

#endif



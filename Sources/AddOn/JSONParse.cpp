//------------ kuvbur 2022 ------------
#include    "ACAPinc.h"
#include    "APICommon25.h"
#include    "APIEnvir.h"
#include    "CommonFunction.hpp"
#include    "JSONParse.hpp"


static GSErrCode GetJSONFileLocation (DG::FileDialog::Type type, const GS::UniString& title, IO::Location& JSONFilePath)
{
    DG::FileDialog fileDialog (type);
    IO::fileSystem.GetSpecialLocation (IO::FileSystem::CurrentFolder, &JSONFilePath);
    fileDialog.SetTitle (title);
    fileDialog.SetFolder (JSONFilePath);
    if (!fileDialog.Invoke ())
        return Cancel;
    JSONFilePath = fileDialog.GetSelectedFile ();
    return NoError;
}

static GSErrCode ParseJSON ()
{
    IO::Location JSONFilePath;
    GS::UniString JSONFilePath_txt = "";
    GSErrCode err = GetJSONFileLocation (DG::FileDialog::OpenFile, "Open JSON", JSONFilePath);
    err = JSONFilePath.ToPath (&JSONFilePath_txt);
    using json = nlohmann::json;
    std::ifstream f (JSONFilePath_txt.ToCStr ());
    json data = json::parse (f);
}

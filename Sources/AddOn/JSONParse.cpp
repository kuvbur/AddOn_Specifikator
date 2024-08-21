//------------ kuvbur 2022 ------------
#include    "ACAPinc.h"
#include    "APICommon25.h"
#include    "APIEnvir.h"
#include    "CommonFunction.hpp"
#include    "JSONParse.hpp"


static GSErrCode GetJSONFileLocation (DG::FileDialog::Type type, const GS::UniString& title, GS::UniString& JSONFilePath)
{
    IO::Location JSONFilePath_;
    DG::FileDialog fileDialog (type);
    IO::fileSystem.GetSpecialLocation (IO::FileSystem::CurrentFolder, &JSONFilePath_);
    fileDialog.SetTitle (title);
    fileDialog.SetFolder (JSONFilePath_);
    if (!fileDialog.Invoke ())
        return Cancel;
    JSONFilePath_ = fileDialog.GetSelectedFile ();
    return JSONFilePath_.ToPath (&JSONFilePath);
}

GSErrCode ParseJSON ()
{
    GSErrCode err = NoError;
    GS::UniString JSONFilePath = "";
    err = GetJSONFileLocation (DG::FileDialog::OpenFile, "Open JSON", JSONFilePath);
    if (err != NoError) {
        return err;
    }
    using json = nlohmann::json;
    std::ifstream f (JSONFilePath.ToCStr ());
    json data = json::parse (f);
    auto h = data["Data"];
    return err;
}

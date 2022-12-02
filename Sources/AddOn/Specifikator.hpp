#pragma once
#if !defined (ADDON_HPP)
#define	ADDON_HPP
#include	"APIEnvir.h"
#include	"ACAPinc.h"
#ifdef AC_25
#include	"APICommon25.h"
#endif // AC_25
#ifdef AC_26
#include	"APICommon26.h"
#endif // AC_26
#include	"ResourceIds.hpp"

#define	 Menu_MonAll		1
#define	 Menu_SyncAll		2
#define	 Menu_SyncSelect	3
#define	 Menu_wallS			4
#define	 Menu_widoS			5
#define	 Menu_objS			6
#define	 Menu_cwallS		7
#define	 Menu_ReNum			8
#define	 Menu_Sum			9
#define	 Menu_Log			10
#define	 Menu_LogShow		11

static const GSResID AddOnInfoID = ID_ADDON_INFO;
static const short AddOnMenuID = ID_ADDON_MENU;
static const short AddOnPromtID = ID_ADDON_PROMT;
static const GSResID AddOnStringsID = ID_ADDON_STRINGS;

static const Int32 AddOnNameID = 1;
static const Int32 AddOnDescriptionID = 2;

static const Int32 AddOnCommandID = 1;
static const Int32 MonAll_CommandID = 2;


static GSErrCode MenuCommandHandler(const API_MenuParams* menuParams);

#endif

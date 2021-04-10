//this file is part of eMule
//Copyright (C)2002-2008 Merkur ( strEmail.Format("%s@%s", "devteam", "emule-project.net") / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#pragma once

#include <Singletons.h>

static LPCTSTR const strDefaultToolbar = _T("0099010203040506070899091011");

enum EViewSharedFilesAccess
{
	vsfaEverybody,
	vsfaFriends,
	vsfaNobody
};

enum ENotifierSoundType
{
	ntfstNoSound,
	ntfstSoundFile,
	ntfstSpeech
};

enum TLSmode: byte
{
	MODE_NONE,
	MODE_SSL_TLS,
	MODE_STARTTLS
};

enum SMTPauth: byte
{
	AUTH_NONE,
	AUTH_PLAIN,
	AUTH_LOGIN
	/* AUTH_GSSAPI,
	AUTH_DIGEST,
	AUTH_MD5,
	AUTH_CRAM,
	AUTH_OAUTH1,
	AUTH_OAUTH2	*/
};


enum EDefaultDirectory
{
	EMULE_CONFIGDIR = 0,
	EMULE_TEMPDIR = 1,
	EMULE_INCOMINGDIR = 2,
	EMULE_LOGDIR = 3,
	EMULE_ADDLANGDIR = 4, // directories with languages installed by the eMule (parent: EMULE_EXPANSIONDIR)
	EMULE_INSTLANGDIR = 5, // directories with languages installed by the user or installer (parent: EMULE_EXECUTABLEDIR)
	EMULE_WEBSERVERDIR = 6,
	EMULE_SKINDIR = 7,
	EMULE_DATABASEDIR = 8, // the parent directory of the incoming/temp folder
	EMULE_CONFIGBASEDIR = 9, // the parent directory of the config folder
	EMULE_EXECUTABLEDIR = 10, // assumed to be non-writable (!)
	EMULE_TOOLBARDIR = 11,
	EMULE_EXPANSIONDIR = 12 // this is a base directory accessible to all users for things eMule installs
};

enum EToolbarLabelType : uint8;
enum ELogFileFormat : uint8;

// DO NOT EDIT VALUES like changing uint16 to uint32, or insert any value. ONLY append new vars
#pragma pack(push, 1)
struct Preferences_Ext_Struct
{
	uint8	version;
	uchar	userhash[16];
	WINDOWPLACEMENT EmuleWindowPlacement;
};
#pragma pack(pop)

//email notifier
struct EmailSettings
{
	CString	sServer;
	CString	sFrom;
	CString	sTo;
	CString	sUser;
	CString	sPass;
	CString	sEncryptCertName;
	uint16	uPort;
	SMTPauth uAuth;
	TLSmode uTLS;
	bool	bSendMail;
};


// deadlake PROXYSUPPORT
struct ProxySettings
{
	CString	host;
	CString	user;
	CString	password;
	uint16	type;
	uint16	port;
	bool	bEnablePassword;
	bool	bUseProxy;
};

struct Category_Struct
{
	CString	strIncomingPath;
	CString	strTitle;
	CString	strComment;
	COLORREF color;
	UINT	prio;
	CString autocat;
	CString	regexp;
	int		filter;
	bool	filterNeg;
	bool	care4all;
	bool	ac_regexpeval;
	bool	downloadInAlphabeticalOrder; // ZZ:DownloadManager
};

class CPreferences
{

	static SingletonConstruct<CPreferences> m_sc;
	friend class SingletonConstruct<CPreferences>;

public:


	static CPreferences& Instance()
	{
		return m_sc.Instance();
	}


public:
	 CString	strNick;
	// ZZ:UploadSpeedSense -->
	 uint32	m_minupload;
	// ZZ:UploadSpeedSense <--
	 uint32	m_maxupload;
	 uint32	m_maxdownload;
	 LPCSTR	m_pszBindAddrA;
	 CStringA m_strBindAddrA;
	 LPCWSTR	m_pszBindAddrW;
	 CStringW m_strBindAddrW;
	 uint16	port;
	 uint16	udpport;
	 uint16	nServerUDPPort;
	 UINT		maxconnections;
	 UINT		maxhalfconnections;
	 bool		m_bConditionalTCPAccept;
	 bool		reconnect;
	 bool		m_bUseServerPriorities;
	 bool		m_bUseUserSortedServerList;
	 CString	m_strIncomingDir;
	 CStringArray	tempdir;
	 bool		ICH;
	 bool		m_bAutoUpdateServerList;
	 bool		updatenotify;
	 bool		mintotray;
	 bool		autoconnect;
	 bool		m_bAutoConnectToStaticServersOnly; // Barry
	 bool		autotakeed2klinks;	   // Barry
	 bool		addnewfilespaused;	   // Barry
	 UINT		depth3D;			   // Barry
	 bool		m_bEnableMiniMule;
	 int		m_iStraightWindowStyles;
	 bool		m_bUseSystemFontForMainControls;
	 bool		m_bRTLWindowsLayout;
	 CString	m_strSkinProfile;
	 CString	m_strSkinProfileDir;
	 bool		m_bAddServersFromServer;
	 bool		m_bAddServersFromClients;
	 UINT		maxsourceperfile;
	 UINT		trafficOMeterInterval;
	 UINT		statsInterval;
	 bool		m_bFillGraphs;
	 uchar	userhash[16];
	 WINDOWPLACEMENT EmuleWindowPlacement;
	 int		maxGraphDownloadRate;
	 int		maxGraphUploadRate;
	 uint32	maxGraphUploadRateEstimated;
	 bool		beepOnError;
	 bool		confirmExit;
	 DWORD	m_adwStatsColors[15];
	 bool		bHasCustomTaskIconColor;
	 bool		m_bIconflashOnNewMessage;
		   
	 bool		splashscreen;
	 bool		filterLANIPs;
	 bool		m_bAllocLocalHostIP;
	 bool		onlineSig;

	// -khaos--+++> Struct Members for Storing Statistics

	// Saved stats for cumulative downline overhead...
	 uint64	cumDownOverheadTotal;
	 uint64	cumDownOverheadFileReq;
	 uint64	cumDownOverheadSrcEx;
	 uint64	cumDownOverheadServer;
	 uint64	cumDownOverheadKad;
	 uint64	cumDownOverheadTotalPackets;
	 uint64	cumDownOverheadFileReqPackets;
	 uint64	cumDownOverheadSrcExPackets;
	 uint64	cumDownOverheadServerPackets;
	 uint64	cumDownOverheadKadPackets;

	// Saved stats for cumulative upline overhead...
	 uint64	cumUpOverheadTotal;
	 uint64	cumUpOverheadFileReq;
	 uint64	cumUpOverheadSrcEx;
	 uint64	cumUpOverheadServer;
	 uint64	cumUpOverheadKad;
	 uint64	cumUpOverheadTotalPackets;
	 uint64	cumUpOverheadFileReqPackets;
	 uint64	cumUpOverheadSrcExPackets;
	 uint64	cumUpOverheadServerPackets;
	 uint64	cumUpOverheadKadPackets;

	// Saved stats for cumulative upline data...
	 uint32	cumUpSuccessfulSessions;
	 uint32	cumUpFailedSessions;
	 uint32	cumUpAvgTime;
	// Cumulative client breakdown stats for sent bytes...
	 uint64	cumUpData_EDONKEY;
	 uint64	cumUpData_EDONKEYHYBRID;
	 uint64	cumUpData_EMULE;
	 uint64	cumUpData_MLDONKEY;
	 uint64	cumUpData_AMULE;
	 uint64	cumUpData_EMULECOMPAT;
	 uint64	cumUpData_SHAREAZA;
	// Session client breakdown stats for sent bytes...
	 uint64	sesUpData_EDONKEY;
	 uint64	sesUpData_EDONKEYHYBRID;
	 uint64	sesUpData_EMULE;
	 uint64	sesUpData_MLDONKEY;
	 uint64	sesUpData_AMULE;
	 uint64	sesUpData_EMULECOMPAT;
	 uint64	sesUpData_SHAREAZA;

	// Cumulative port breakdown stats for sent bytes...
	 uint64	cumUpDataPort_4662;
	 uint64	cumUpDataPort_OTHER;
	 uint64	cumUpDataPort_PeerCache;
	// Session port breakdown stats for sent bytes...
	 uint64	sesUpDataPort_4662;
	 uint64	sesUpDataPort_OTHER;
	 uint64	sesUpDataPort_PeerCache;

	// Cumulative source breakdown stats for sent bytes...
	 uint64	cumUpData_File;
	 uint64	cumUpData_Partfile;
	// Session source breakdown stats for sent bytes...
	 uint64	sesUpData_File;
	 uint64	sesUpData_Partfile;

	// Saved stats for cumulative downline data...
	 uint32	cumDownCompletedFiles;
	 uint32	cumDownSuccessfulSessions;
	 uint32	cumDownFailedSessions;
	 uint32	cumDownAvgTime;

	// Cumulative statistics for saved due to compression/lost due to corruption
	 uint64	cumLostFromCorruption;
	 uint64	cumSavedFromCompression;
	 uint32	cumPartsSavedByICH;

	// Session statistics for download sessions
	 uint32	sesDownSuccessfulSessions;
	 uint32	sesDownFailedSessions;
	 uint32	sesDownAvgTime;
	 uint32	sesDownCompletedFiles;
	 uint64	sesLostFromCorruption;
	 uint64	sesSavedFromCompression;
	 uint32	sesPartsSavedByICH;

	// Cumulative client breakdown stats for received bytes...
	 uint64	cumDownData_EDONKEY;
	 uint64	cumDownData_EDONKEYHYBRID;
	 uint64	cumDownData_EMULE;
	 uint64	cumDownData_MLDONKEY;
	 uint64	cumDownData_AMULE;
	 uint64	cumDownData_EMULECOMPAT;
	 uint64	cumDownData_SHAREAZA;
	 uint64	cumDownData_URL;
	// Session client breakdown stats for received bytes...
	 uint64	sesDownData_EDONKEY;
	 uint64	sesDownData_EDONKEYHYBRID;
	 uint64	sesDownData_EMULE;
	 uint64	sesDownData_MLDONKEY;
	 uint64	sesDownData_AMULE;
	 uint64	sesDownData_EMULECOMPAT;
	 uint64	sesDownData_SHAREAZA;
	 uint64	sesDownData_URL;

	// Cumulative port breakdown stats for received bytes...
	 uint64	cumDownDataPort_4662;
	 uint64	cumDownDataPort_OTHER;
	 uint64	cumDownDataPort_PeerCache;
	// Session port breakdown stats for received bytes...
	 uint64	sesDownDataPort_4662;
	 uint64	sesDownDataPort_OTHER;
	 uint64	sesDownDataPort_PeerCache;

	// Saved stats for cumulative connection data...
	 float	cumConnAvgDownRate;
	 float	cumConnMaxAvgDownRate;
	 float	cumConnMaxDownRate;
	 float	cumConnAvgUpRate;
	 float	cumConnMaxAvgUpRate;
	 float	cumConnMaxUpRate;
	 time_t	cumConnRunTime;
	 uint32	cumConnNumReconnects;
	 uint32	cumConnAvgConnections;
	 uint32	cumConnMaxConnLimitReached;
	 uint32	cumConnPeakConnections;
	 uint32	cumConnTransferTime;
	 uint32	cumConnDownloadTime;
	 uint32	cumConnUploadTime;
	 uint32	cumConnServerDuration;

	// Saved records for servers / network...
	 uint32	cumSrvrsMostWorkingServers;
	 uint32	cumSrvrsMostUsersOnline;
	 uint32	cumSrvrsMostFilesAvail;

	// Saved records for shared files...
	 uint32	cumSharedMostFilesShared;
	 uint64	cumSharedLargestShareSize;
	 uint64	cumSharedLargestAvgFileSize;
	 uint64	cumSharedLargestFileSize;

	// Save the date when the statistics were last reset...
	 time_t	stat_datetimeLastReset;

	// Save new preferences for PPgStats
	 UINT		statsConnectionsGraphRatio; // This will store the divisor, i.e. for 1:3 it will be 3, for 1:20 it will be 20.
	// Save the expanded branches of the stats tree
	 CString	m_strStatsExpandedTreeItems;

	 bool		m_bShowVerticalHourMarkers;
	 UINT		statsSaveInterval;
	// <-----khaos- End Statistics Members


	// Original Stats Stuff
	 uint64	totalDownloadedBytes;
	 uint64	totalUploadedBytes;
	// End Original Stats Stuff
	 WORD		m_wLanguageID;
	 bool		transferDoubleclick;
	 EViewSharedFilesAccess m_iSeeShares;
	 UINT		m_iToolDelayTime;	// tooltip delay time in seconds
	 bool		bringtoforeground;
	 UINT		splitterbarPosition;
	 UINT		splitterbarPositionSvr;

	 UINT		m_uTransferWnd1;
	 UINT		m_uTransferWnd2;
	//MORPH START - Added by SiRoB, Splitting Bar [O²]
	 UINT		splitterbarPositionStat;
	 UINT		splitterbarPositionStat_HL;
	 UINT		splitterbarPositionStat_HR;
	 UINT		splitterbarPositionFriend;
	 UINT		splitterbarPositionIRC;
	 UINT		splitterbarPositionShared;
	//MORPH END - Added by SiRoB, Splitting Bar [O²]
	 UINT		m_uDeadServerRetries;
	 DWORD	m_dwServerKeepAliveTimeout;
	// -khaos--+++> Changed data type to avoid overflows
	 UINT		statsMax;
	// <-----khaos-
	 UINT		statsAverageMinutes;

	 CString	notifierConfiguration;
	 bool		notifierOnDownloadFinished;
	 bool		notifierOnNewDownload;
	 bool		notifierOnChat;
	 bool		notifierOnLog;
	 bool		notifierOnImportantError;
	 bool		notifierOnEveryChatMsg;
	 bool		notifierOnNewVersion;
	 ENotifierSoundType notifierSoundType;
	 CString	notifierSoundFile;

	 CString	m_strIRCServer;
	 CString	m_strIRCNick;
	 CString	m_strIRCChannelFilter;
	 bool		m_bIRCAddTimeStamp;
	 bool		m_bIRCUseChannelFilter;
	 UINT		m_uIRCChannelUserFilter;
	 CString	m_strIRCPerformString;
	 bool		m_bIRCUsePerform;
	 bool		m_bIRCGetChannelsOnConnect;
	 bool		m_bIRCAcceptLinks;
	 bool		m_bIRCAcceptLinksFriendsOnly;
	 bool		m_bIRCPlaySoundEvents;
	 bool		m_bIRCIgnoreMiscMessages;
	 bool		m_bIRCIgnoreJoinMessages;
	 bool		m_bIRCIgnorePartMessages;
	 bool		m_bIRCIgnoreQuitMessages;
	 bool		m_bIRCIgnorePingPongMessages;
	 bool		m_bIRCIgnoreEmuleAddFriendMsgs;
	 bool		m_bIRCAllowEmuleAddFriend;
	 bool		m_bIRCIgnoreEmuleSendLinkMsgs;
	 bool		m_bIRCJoinHelpChannel;
	 bool		m_bIRCEnableSmileys;
	 bool		m_bMessageEnableSmileys;
	 bool		m_bIRCEnableUTF8;

	 bool		m_bRemove2bin;
	 bool		m_bShowCopyEd2kLinkCmd;
	 bool		m_bpreviewprio;
	 bool		m_bSmartServerIdCheck;
	 uint8	smartidstate;
	 bool		m_bSafeServerConnect;
	 bool		startMinimized;
	 bool		m_bAutoStart;
	 bool		m_bRestoreLastMainWndDlg;
	 int		m_iLastMainWndDlgID;
	 bool		m_bRestoreLastLogPane;
	 int		m_iLastLogPaneID;
	 UINT		MaxConperFive;
	 bool		checkDiskspace;
	 UINT		m_uMinFreeDiskSpace;
	 bool		m_bSparsePartFiles;
	 bool		m_bImportParts;
	 CString	m_strYourHostname;
	 bool		m_bEnableVerboseOptions;
	 bool		m_bVerbose;
	 bool		m_bFullVerbose;
	 int		m_byLogLevel;
	 bool		m_bDebugSourceExchange; // Sony April 23. 2003, button to keep source exchange msg out of verbose log
	 bool		m_bLogBannedClients;
	 bool		m_bLogRatingDescReceived;
	 bool		m_bLogSecureIdent;
	 bool		m_bLogFilteredIPs;
	 bool		m_bLogFileSaving;
	 bool		m_bLogA4AF; // ZZ:DownloadManager
	 bool		m_bLogUlDlEvents;
	 bool		m_bUseDebugDevice;
	 int		m_iDebugServerTCPLevel;
	 int		m_iDebugServerUDPLevel;
	 int		m_iDebugServerSourcesLevel;
	 int		m_iDebugServerSearchesLevel;
	 int		m_iDebugClientTCPLevel;
	 int		m_iDebugClientUDPLevel;
	 int		m_iDebugClientKadUDPLevel;
	 int		m_iDebugSearchResultDetailLevel;
	 bool		m_bupdatequeuelist;
	 bool		m_bManualAddedServersHighPriority;
	 bool		m_btransferfullchunks;
	 int		m_istartnextfile;
	 bool		m_bshowoverhead;
	 bool		m_bDAP;
	 bool		m_bUAP;
	 bool		m_bDisableKnownClientList;
	 bool		m_bDisableQueueList;
	 bool		m_bExtControls;
	 bool		m_bTransflstRemain;

	 UINT		versioncheckdays;
	 bool		showRatesInTitle;
		   
	 CString	m_strTxtEditor;
	 CString	m_strVideoPlayer;
	 CString	m_strVideoPlayerArgs;
	 bool		moviePreviewBackup;
	 int		m_iPreviewSmallBlocks;
	 bool		m_bPreviewCopiedArchives;
	 int		m_iInspectAllFileTypes;
	 bool		m_bPreviewOnIconDblClk;
	 bool		m_bCheckFileOpen;
	 bool		indicateratings;
	 bool		watchclipboard;
	 bool		filterserverbyip;
	 bool		m_bFirstStart;
	 bool		m_bBetaNaggingDone;
	 bool		m_bCreditSystem;
		   
	 bool		log2disk;
	 bool		debug2disk;
	 int		iMaxLogBuff;
	 UINT		uMaxLogFileSize;
	 ELogFileFormat m_iLogFileFormat;
	 bool		scheduler;
	 bool		dontcompressavi;
	 bool		msgonlyfriends;
	 bool		msgsecure;
	 bool		m_bUseChatCaptchas;
		   
	 UINT		filterlevel;
	 UINT		m_uFileBufferSize;
	 INT_PTR	m_iQueueSize;
	 int		m_iCommitFiles;
	 DWORD	m_uFileBufferTimeLimit;
		   
	 UINT		maxmsgsessions;
	 time_t	versioncheckLastAutomatic;
	 CString	messageFilter;
	 CString	commentFilter;
	 CString	filenameCleanups;
	 CString	m_strDateTimeFormat;
	 CString	m_strDateTimeFormat4Log;
	 CString	m_strDateTimeFormat4Lists;
	 LOGFONT	m_lfHyperText;
	 LOGFONT	m_lfLogText;
	 COLORREF m_crLogError;
	 COLORREF m_crLogWarning;
	 COLORREF m_crLogSuccess;
	 int		m_iExtractMetaData;
	 bool		m_bAdjustNTFSDaylightFileTime;
	 bool		m_bRearrangeKadSearchKeywords;
	 bool		m_bAllocFull;
	 bool		m_bShowSharedFilesDetails;
	 bool		m_bShowWin7TaskbarGoodies;
	 bool		m_bShowUpDownIconInTaskbar;
	 bool		m_bForceSpeedsToKB;
	 bool		m_bAutoShowLookups;
	 bool		m_bExtraPreviewWithMenu;

	// Web Server [kuchin]
	 CString	m_strWebPassword;
	 CString	m_strWebLowPassword;
	 uint16	m_nWebPort;
	 bool		m_bWebUseUPnP;
	 bool		m_bWebEnabled;
	 bool		m_bWebUseGzip;
	 int		m_nWebPageRefresh;
	 bool		m_bWebLowEnabled;
	 int		m_iWebTimeoutMins;
	 int		m_iWebFileUploadSizeLimitMB;
	 CString	m_strTemplateFile;
	 ProxySettings proxy; // deadlake PROXYSUPPORT
	 bool		m_bAllowAdminHiLevFunc;
	 CUIntArray m_aAllowedRemoteAccessIPs;
	 bool		m_bWebUseHttps;
	 CString	m_sWebHttpsCertificate;
	 CString	m_sWebHttpsKey;

	 bool		showCatTabInfos;
	 bool		resumeSameCat;
	 bool		dontRecreateGraphs;
	 bool		autofilenamecleanup;
	// int	allcatType;
	// bool	allcatTypeNeg;
	 bool		m_bUseAutocompl;
	 bool		m_bShowDwlPercentage;
	 bool		m_bRemoveFinishedDownloads;
	 INT_PTR	m_iMaxChatHistory;
	 bool		m_bShowActiveDownloadsBold;
		   
	 int		m_iSearchMethod;
	 bool		m_bAdvancedSpamfilter;
	 bool		m_bUseSecureIdent;
		   
	 bool		networkkademlia;
	 bool		networked2k;

	// toolbar
	 EToolbarLabelType m_nToolbarLabels;
	 CString	m_sToolbarBitmap;
	 CString	m_sToolbarBitmapFolder;
	 CString	m_sToolbarSettings;
	 bool		m_bReBarToolbar;
	 CSize	m_sizToolbarIconSize;
		   
	 bool		m_bWinaTransToolbar;
	 bool		m_bShowDownloadToolbar;

	//preview
	 bool		m_bPreviewEnabled;
	 bool		m_bAutomaticArcPreviewStart;

	// ZZ:UploadSpeedSense -->
	 bool		m_bDynUpEnabled;
	 int		m_iDynUpPingTolerance;
	 int		m_iDynUpGoingUpDivider;
	 int		m_iDynUpGoingDownDivider;
	 int		m_iDynUpNumberOfPings;
	 int		m_iDynUpPingToleranceMilliseconds;
	 bool		m_bDynUpUseMillisecondPingTolerance;
	// ZZ:UploadSpeedSense <--

	 bool		m_bA4AFSaveCpu; // ZZ:DownloadManager

	 bool		m_bHighresTimer;

	 bool		m_bResolveSharedShellLinks;
	 CStringList shareddir_list;
	 CStringList addresses_list;
	 bool		m_bKeepUnavailableFixedSharedDirs;

	 int		m_iDbgHeap;
	 UINT		m_nWebMirrorAlertLevel;
	 bool		m_bRunAsUser;
	 bool		m_bPreferRestrictedOverUser;
		   
	 bool		m_bUseOldTimeRemaining;

	// PeerCache
	 time_t	m_uPeerCacheLastSearch;
	 uint16	m_nPeerCachePort;
	 bool		m_bPeerCacheWasFound;
	 bool		m_bPeerCacheEnabled;
	 bool		m_bPeerCacheShow;

	// Firewall settings
	 bool		m_bOpenPortsOnStartUp;

	//AICH Options
	 bool		m_bTrustEveryHash;

	// files
	 bool		m_bRememberCancelledFiles;
	 bool		m_bRememberDownloadedFiles;
	 bool		m_bPartiallyPurgeOldKnownFiles;

	//email notifier
	 EmailSettings m_email;

	// encryption / obfuscation / verification
	 bool		m_bCryptLayerRequested;
	 bool		m_bCryptLayerSupported;
	 bool		m_bCryptLayerRequired;
	 uint8	m_byCryptTCPPaddingLength;
	 uint32   m_dwKadUDPKey;

	// UPnP
	 bool		m_bSkipWANIPSetup;
	 bool		m_bSkipWANPPPSetup;
	 bool		m_bEnableUPnP;
	 bool		m_bCloseUPnPOnExit;
	 bool		m_bIsWinServImplDisabled;
	 bool		m_bIsMinilibImplDisabled;
	 int		m_nLastWorkingImpl;

	// Spam
	 bool		m_bEnableSearchResultFilter;

	 BOOL		m_bIsRunningAeroGlass;
	 bool		m_bPreventStandby;
	 bool		m_bStoreSearches;


	enum Table
	{
		tableDownload,
		tableUpload,
		tableQueue,
		tableSearch,
		tableShared,
		tableServer,
		tableClientList,
		tableFilenames,
		tableIrcMain,
		tableIrcChannels,
		tableDownloadClients
	};

	CPreferences();
	~CPreferences();

	 void	Init();
	 void	Uninit();

	 LPCTSTR	GetTempDir(INT_PTR id = 0)			{ return (LPCTSTR)tempdir[(id < tempdir.GetCount()) ? id : 0]; }
	 INT_PTR	GetTempDirCount()					{ return tempdir.GetCount(); }
	 bool		CanFSHandleLargeFiles(int nForCat);
	 LPCTSTR	GetConfigFile();
	 const CString& GetFileCommentsFilePath()		{ return m_strFileCommentsFilePath; }
	 CString	GetMuleDirectory(EDefaultDirectory eDirectory, bool bCreate = true);
	 void		SetMuleDirectory(EDefaultDirectory eDirectory, const CString &strNewDir);
	 void		ChangeUserDirMode(int nNewMode);

	 bool		IsTempFile(const CString &rstrDirectory, const CString &rstrName);
	 bool		IsShareableDirectory(const CString &rstrDir);
	 bool		IsInstallationDirectory(const CString &rstrDir);

	 bool		Save();
	 void		SaveCats();

	 bool		GetUseServerPriorities()			{ return m_bUseServerPriorities; }
	 bool		GetUseUserSortedServerList()		{ return m_bUseUserSortedServerList; }
	 bool		Reconnect()							{ return reconnect; }
	 const CString& GetUserNick()					{ return strNick; }
	 void		SetUserNick(LPCTSTR pszNick);
	 int		GetMaxUserNickLength()				{ return 50; }

	 LPCSTR	GetBindAddrA()						{ return m_pszBindAddrA; }
	 LPCWSTR	GetBindAddrW()						{ return m_pszBindAddrW; }
#ifdef UNICODE
#define GetBindAddr  GetBindAddrW
#else
#define GetBindAddr  GetBindAddrA
#endif // !UNICODE

	 uint16	GetPort()							{ return port; }
	 uint16	GetUDPPort()						{ return udpport; }
	 uint16	GetServerUDPPort()					{ return nServerUDPPort; }
	 uchar*	GetUserHash()						{ return userhash; }
	// ZZ:UploadSpeedSense -->
	 uint32	GetMinUpload()						{ return m_minupload; }
	// ZZ:UploadSpeedSense <--
	 uint32	GetMaxUpload()						{ return m_maxupload; }
	 bool		IsICHEnabled()						{ return ICH; }
	 bool		GetAutoUpdateServerList()			{ return m_bAutoUpdateServerList; }
	 bool		UpdateNotify()						{ return updatenotify; }
	 bool		GetMinToTray()						{ return mintotray; }
	 bool		DoAutoConnect()						{ return autoconnect; }
	 void		SetAutoConnect(bool inautoconnect)	{ autoconnect = inautoconnect; }
	 bool		GetAddServersFromServer()			{ return m_bAddServersFromServer; }
	 bool		GetAddServersFromClients()			{ return m_bAddServersFromClients; }
	 bool*	GetMinTrayPTR()						{ return &mintotray; }
	 UINT		GetTrafficOMeterInterval()			{ return trafficOMeterInterval; }
	 void		SetTrafficOMeterInterval(UINT in)	{ trafficOMeterInterval = in; }
	 UINT		GetStatsInterval()					{ return statsInterval; }
	 void		SetStatsInterval(UINT in)			{ statsInterval = in; }
	 bool		GetFillGraphs()						{ return m_bFillGraphs; }
	 void		SetFillGraphs(bool bFill)			{ m_bFillGraphs = bFill; }

	// -khaos--+++> Many, many, many, many methods.
	 void		SaveStats(int bBackUp = 0);
	 void		SetRecordStructMembers();
	 void		SaveCompletedDownloadsStat();
	 bool		LoadStats(int loadBackUp = 0);
	 void		ResetCumulativeStatistics();

	 void		Add2DownCompletedFiles()			{ ++cumDownCompletedFiles; }
	 void		SetConnMaxAvgDownRate(float in)		{ cumConnMaxAvgDownRate = in; }
	 void		SetConnMaxDownRate(float in)		{ cumConnMaxDownRate = in; }
	 void		SetConnAvgUpRate(float in)			{ cumConnAvgUpRate = in; }
	 void		SetConnMaxAvgUpRate(float in)		{ cumConnMaxAvgUpRate = in; }
	 void		SetConnMaxUpRate(float in)			{ cumConnMaxUpRate = in; }
	 void		SetConnPeakConnections(int in)		{ cumConnPeakConnections = in; }
	 void		SetUpAvgTime(int in)				{ cumUpAvgTime = in; }
	 void		Add2DownSAvgTime(int in)			{ sesDownAvgTime += in; }
	 void		SetDownCAvgTime(int in)				{ cumDownAvgTime = in; }
	 void		Add2ConnTransferTime(int in)		{ cumConnTransferTime += in; }
	 void		Add2ConnDownloadTime(int in)		{ cumConnDownloadTime += in; }
	 void		Add2ConnUploadTime(int in)			{ cumConnUploadTime += in; }
	 void		Add2DownSessionCompletedFiles()		{ ++sesDownCompletedFiles; }
	 void		Add2SessionTransferData(UINT uClientID, UINT uClientPort, BOOL bFromPF, BOOL bUpDown, uint32 bytes, bool sentToFriend = false);
	 void		Add2DownSuccessfulSessions()		{ ++sesDownSuccessfulSessions;
														  ++cumDownSuccessfulSessions; }
	 void		Add2DownFailedSessions()			{ ++sesDownFailedSessions;
														  ++cumDownFailedSessions; }
	 void		Add2LostFromCorruption(uint64 in)	{ sesLostFromCorruption += in; }
	 void		Add2SavedFromCompression(uint64 in)	{ sesSavedFromCompression += in; }
	 void		Add2SessionPartsSavedByICH(int in)	{ sesPartsSavedByICH += in; }

	// Saved stats for cumulative downline overhead
	 uint64	GetDownOverheadTotal()				{ return cumDownOverheadTotal; }
	 uint64	GetDownOverheadFileReq()			{ return cumDownOverheadFileReq; }
	 uint64	GetDownOverheadSrcEx()				{ return cumDownOverheadSrcEx; }
	 uint64	GetDownOverheadServer()				{ return cumDownOverheadServer; }
	 uint64	GetDownOverheadKad()				{ return cumDownOverheadKad; }
	 uint64	GetDownOverheadTotalPackets()		{ return cumDownOverheadTotalPackets; }
	 uint64	GetDownOverheadFileReqPackets()		{ return cumDownOverheadFileReqPackets; }
	 uint64	GetDownOverheadSrcExPackets()		{ return cumDownOverheadSrcExPackets; }
	 uint64	GetDownOverheadServerPackets()		{ return cumDownOverheadServerPackets; }
	 uint64	GetDownOverheadKadPackets()			{ return cumDownOverheadKadPackets; }

	// Saved stats for cumulative upline overhead
	 uint64	GetUpOverheadTotal()				{ return cumUpOverheadTotal; }
	 uint64	GetUpOverheadFileReq()				{ return cumUpOverheadFileReq; }
	 uint64	GetUpOverheadSrcEx()				{ return cumUpOverheadSrcEx; }
	 uint64	GetUpOverheadServer()				{ return cumUpOverheadServer; }
	 uint64	GetUpOverheadKad()					{ return cumUpOverheadKad; }
	 uint64	GetUpOverheadTotalPackets()			{ return cumUpOverheadTotalPackets; }
	 uint64	GetUpOverheadFileReqPackets()		{ return cumUpOverheadFileReqPackets; }
	 uint64	GetUpOverheadSrcExPackets()			{ return cumUpOverheadSrcExPackets; }
	 uint64	GetUpOverheadServerPackets()		{ return cumUpOverheadServerPackets; }
	 uint64	GetUpOverheadKadPackets()			{ return cumUpOverheadKadPackets; }

	// Saved stats for cumulative upline data
	 uint32	GetUpSuccessfulSessions()			{ return cumUpSuccessfulSessions; }
	 uint32	GetUpFailedSessions()				{ return cumUpFailedSessions; }
	 uint32	GetUpAvgTime()						{ return cumUpAvgTime; }

	// Saved stats for cumulative downline data
	 uint32	GetDownCompletedFiles()				{ return cumDownCompletedFiles; }
	 uint32	GetDownC_SuccessfulSessions()		{ return cumDownSuccessfulSessions; }
	 uint32	GetDownC_FailedSessions()			{ return cumDownFailedSessions; }
	 uint32	GetDownC_AvgTime()					{ return cumDownAvgTime; }

	// Session download stats
	 uint32	GetDownSessionCompletedFiles()		{ return sesDownCompletedFiles; }
	 uint32	GetDownS_SuccessfulSessions()		{ return sesDownSuccessfulSessions; }
	 uint32	GetDownS_FailedSessions()			{ return sesDownFailedSessions; }
	 uint32	GetDownS_AvgTime()					{ return GetDownS_SuccessfulSessions() ? sesDownAvgTime / GetDownS_SuccessfulSessions() : 0; }

	// Saved stats for corruption/compression
	 uint64	GetCumLostFromCorruption()			{ return cumLostFromCorruption; }
	 uint64	GetCumSavedFromCompression()		{ return cumSavedFromCompression; }
	 uint64	GetSesLostFromCorruption()			{ return sesLostFromCorruption; }
	 uint64	GetSesSavedFromCompression()		{ return sesSavedFromCompression; }
	 uint32	GetCumPartsSavedByICH()				{ return cumPartsSavedByICH; }
	 uint32	GetSesPartsSavedByICH()				{ return sesPartsSavedByICH; }

	// Cumulative client breakdown stats for sent bytes
	 uint64	GetUpTotalClientData()				{ return  GetCumUpData_EDONKEY()
																+ GetCumUpData_EDONKEYHYBRID()
																+ GetCumUpData_EMULE()
																+ GetCumUpData_MLDONKEY()
																+ GetCumUpData_AMULE()
																+ GetCumUpData_EMULECOMPAT()
																+ GetCumUpData_SHAREAZA(); }
	 uint64	GetCumUpData_EDONKEY()				{ return cumUpData_EDONKEY +		sesUpData_EDONKEY; }
	 uint64	GetCumUpData_EDONKEYHYBRID()		{ return cumUpData_EDONKEYHYBRID +	sesUpData_EDONKEYHYBRID; }
	 uint64	GetCumUpData_EMULE()				{ return cumUpData_EMULE +			sesUpData_EMULE; }
	 uint64	GetCumUpData_MLDONKEY()				{ return cumUpData_MLDONKEY +		sesUpData_MLDONKEY; }
	 uint64	GetCumUpData_AMULE()				{ return cumUpData_AMULE +			sesUpData_AMULE; }
	 uint64	GetCumUpData_EMULECOMPAT()			{ return cumUpData_EMULECOMPAT +	sesUpData_EMULECOMPAT; }
	 uint64	GetCumUpData_SHAREAZA()				{ return cumUpData_SHAREAZA +		sesUpData_SHAREAZA; }

	// Session client breakdown stats for sent bytes
	 uint64	GetUpSessionClientData()			{ return  sesUpData_EDONKEY
																+ sesUpData_EDONKEYHYBRID
																+ sesUpData_EMULE
																+ sesUpData_MLDONKEY
																+ sesUpData_AMULE
																+ sesUpData_EMULECOMPAT
																+ sesUpData_SHAREAZA; }
	 uint64	GetUpData_EDONKEY()					{ return sesUpData_EDONKEY; }
	 uint64	GetUpData_EDONKEYHYBRID()			{ return sesUpData_EDONKEYHYBRID; }
	 uint64	GetUpData_EMULE()					{ return sesUpData_EMULE; }
	 uint64	GetUpData_MLDONKEY()				{ return sesUpData_MLDONKEY; }
	 uint64	GetUpData_AMULE()					{ return sesUpData_AMULE; }
	 uint64	GetUpData_EMULECOMPAT()				{ return sesUpData_EMULECOMPAT; }
	 uint64	GetUpData_SHAREAZA()				{ return sesUpData_SHAREAZA; }

	// Cumulative port breakdown stats for sent bytes...
	 uint64	GetUpTotalPortData()				{ return  GetCumUpDataPort_4662()
																+ GetCumUpDataPort_OTHER()
																+ GetCumUpDataPort_PeerCache(); }
	 uint64	GetCumUpDataPort_4662()				{ return cumUpDataPort_4662 +		sesUpDataPort_4662; }
	 uint64	GetCumUpDataPort_OTHER()			{ return cumUpDataPort_OTHER +		sesUpDataPort_OTHER; }
	 uint64	GetCumUpDataPort_PeerCache()		{ return cumUpDataPort_PeerCache +	sesUpDataPort_PeerCache; }

	// Session port breakdown stats for sent bytes...
	 uint64	GetUpSessionPortData()				{ return  sesUpDataPort_4662
																+ sesUpDataPort_OTHER
																+ sesUpDataPort_PeerCache; }
	 uint64	GetUpDataPort_4662()				{ return sesUpDataPort_4662; }
	 uint64	GetUpDataPort_OTHER()				{ return sesUpDataPort_OTHER; }
	 uint64	GetUpDataPort_PeerCache()			{ return sesUpDataPort_PeerCache; }

	// Cumulative DS breakdown stats for sent bytes...
	 uint64	GetUpTotalDataFile()				{ return GetCumUpData_File() +	GetCumUpData_Partfile(); }
	 uint64	GetCumUpData_File()					{ return cumUpData_File +		sesUpData_File; }
	 uint64	GetCumUpData_Partfile()				{ return cumUpData_Partfile +	sesUpData_Partfile; }
	// Session DS breakdown stats for sent bytes...
	 uint64	GetUpSessionDataFile()				{ return sesUpData_File +		sesUpData_Partfile; }
	 uint64	GetUpData_File()					{ return sesUpData_File; }
	 uint64	GetUpData_Partfile()				{ return sesUpData_Partfile; }

	// Cumulative client breakdown stats for received bytes
	 uint64	GetDownTotalClientData()			{ return  GetCumDownData_EDONKEY()
																+ GetCumDownData_EDONKEYHYBRID()
																+ GetCumDownData_EMULE()
																+ GetCumDownData_MLDONKEY()
																+ GetCumDownData_AMULE()
																+ GetCumDownData_EMULECOMPAT()
																+ GetCumDownData_SHAREAZA()
																+ GetCumDownData_URL(); }
	 uint64	GetCumDownData_EDONKEY()			{ return cumDownData_EDONKEY +		sesDownData_EDONKEY; }
	 uint64	GetCumDownData_EDONKEYHYBRID()		{ return cumDownData_EDONKEYHYBRID + sesDownData_EDONKEYHYBRID; }
	 uint64	GetCumDownData_EMULE()				{ return cumDownData_EMULE +		sesDownData_EMULE; }
	 uint64	GetCumDownData_MLDONKEY()			{ return cumDownData_MLDONKEY +		sesDownData_MLDONKEY; }
	 uint64	GetCumDownData_AMULE()				{ return cumDownData_AMULE +		sesDownData_AMULE; }
	 uint64	GetCumDownData_EMULECOMPAT()		{ return cumDownData_EMULECOMPAT +	sesDownData_EMULECOMPAT; }
	 uint64	GetCumDownData_SHAREAZA()			{ return cumDownData_SHAREAZA +		sesDownData_SHAREAZA; }
	 uint64	GetCumDownData_URL()				{ return cumDownData_URL +			sesDownData_URL; }

	// Session client breakdown stats for received bytes
	 uint64	GetDownSessionClientData()			{ return  sesDownData_EDONKEY
																+ sesDownData_EDONKEYHYBRID
																+ sesDownData_EMULE
																+ sesDownData_MLDONKEY
																+ sesDownData_AMULE
																+ sesDownData_EMULECOMPAT
																+ sesDownData_SHAREAZA
																+ sesDownData_URL; }
	 uint64	GetDownData_EDONKEY()				{ return sesDownData_EDONKEY; }
	 uint64	GetDownData_EDONKEYHYBRID()			{ return sesDownData_EDONKEYHYBRID; }
	 uint64	GetDownData_EMULE()					{ return sesDownData_EMULE; }
	 uint64	GetDownData_MLDONKEY()				{ return sesDownData_MLDONKEY; }
	 uint64	GetDownData_AMULE()					{ return sesDownData_AMULE; }
	 uint64	GetDownData_EMULECOMPAT()			{ return sesDownData_EMULECOMPAT; }
	 uint64	GetDownData_SHAREAZA()				{ return sesDownData_SHAREAZA; }
	 uint64	GetDownData_URL()					{ return sesDownData_URL; }

	// Cumulative port breakdown stats for received bytes...
	 uint64	GetDownTotalPortData()				{ return  GetCumDownDataPort_4662()
																+ GetCumDownDataPort_OTHER()
																+ GetCumDownDataPort_PeerCache(); }
	 uint64	GetCumDownDataPort_4662()			{ return cumDownDataPort_4662		+ sesDownDataPort_4662; }
	 uint64	GetCumDownDataPort_OTHER()			{ return cumDownDataPort_OTHER		+ sesDownDataPort_OTHER; }
	 uint64	GetCumDownDataPort_PeerCache()		{ return cumDownDataPort_PeerCache	+ sesDownDataPort_PeerCache; }

	// Session port breakdown stats for received bytes...
	 uint64	GetDownSessionDataPort()			{ return   sesDownDataPort_4662
																+ sesDownDataPort_OTHER
																+ sesDownDataPort_PeerCache; }
	 uint64	GetDownDataPort_4662()				{ return sesDownDataPort_4662; }
	 uint64	GetDownDataPort_OTHER()				{ return sesDownDataPort_OTHER; }
	 uint64	GetDownDataPort_PeerCache()			{ return sesDownDataPort_PeerCache; }

	// Saved stats for cumulative connection data
	 float	GetConnAvgDownRate()				{ return cumConnAvgDownRate; }
	 float	GetConnMaxAvgDownRate()				{ return cumConnMaxAvgDownRate; }
	 float	GetConnMaxDownRate()				{ return cumConnMaxDownRate; }
	 float	GetConnAvgUpRate()					{ return cumConnAvgUpRate; }
	 float	GetConnMaxAvgUpRate()				{ return cumConnMaxAvgUpRate; }
	 float	GetConnMaxUpRate()					{ return cumConnMaxUpRate; }
	 time_t	GetConnRunTime()					{ return cumConnRunTime; }
	 uint32	GetConnNumReconnects()				{ return cumConnNumReconnects; }
	 uint32	GetConnAvgConnections()				{ return cumConnAvgConnections; }
	 uint32	GetConnMaxConnLimitReached()		{ return cumConnMaxConnLimitReached; }
	 uint32	GetConnPeakConnections()			{ return cumConnPeakConnections; }
	 uint32	GetConnTransferTime()				{ return cumConnTransferTime; }
	 uint32	GetConnDownloadTime()				{ return cumConnDownloadTime; }
	 uint32	GetConnUploadTime()					{ return cumConnUploadTime; }
	 uint32	GetConnServerDuration()				{ return cumConnServerDuration; }

	// Saved records for servers / network
	 uint32	GetSrvrsMostWorkingServers()		{ return cumSrvrsMostWorkingServers; }
	 uint32	GetSrvrsMostUsersOnline()			{ return cumSrvrsMostUsersOnline; }
	 uint32	GetSrvrsMostFilesAvail()			{ return cumSrvrsMostFilesAvail; }

	// Saved records for shared files
	 uint32	GetSharedMostFilesShared()			{ return cumSharedMostFilesShared; }
	 uint64	GetSharedLargestShareSize()			{ return cumSharedLargestShareSize; }
	 uint64	GetSharedLargestAvgFileSize()		{ return cumSharedLargestAvgFileSize; }
	 uint64	GetSharedLargestFileSize()			{ return cumSharedLargestFileSize; }

	// Get the long date/time when the stats were last reset
	 time_t	GetStatsLastResetLng()				{ return stat_datetimeLastReset; }
	 CString	GetStatsLastResetStr(bool formatLong = true);
	 UINT		GetStatsSaveInterval()				{ return statsSaveInterval; }

	// Get and Set our new preferences
	 void		SetStatsMax(UINT in)				{ statsMax = in; }
	 void		SetStatsConnectionsGraphRatio(UINT in) { statsConnectionsGraphRatio = in; }
	 UINT		GetStatsConnectionsGraphRatio()		{ return statsConnectionsGraphRatio; }
	 void		SetExpandedTreeItems(const CString &in)	{ m_strStatsExpandedTreeItems = in; }
	 const CString& GetExpandedTreeItems()		{ return m_strStatsExpandedTreeItems; }

	 uint64	GetTotalDownloaded()				{ return totalDownloadedBytes; }
	 uint64	GetTotalUploaded()					{ return totalUploadedBytes; }

	 bool		IsErrorBeepEnabled()				{ return beepOnError; }
	 bool		IsConfirmExitEnabled()				{ return confirmExit; }
	 void		SetConfirmExit(bool bVal)			{ confirmExit = bVal; }
	 bool		UseSplashScreen()					{ return splashscreen; }
	 bool		FilterLANIPs()						{ return filterLANIPs; }
	 bool		GetAllowLocalHostIP()				{ return m_bAllocLocalHostIP; }
	 bool		IsOnlineSignatureEnabled()			{ return onlineSig; }
	 int		GetMaxGraphUploadRate(bool bEstimateIfUnlimited);
	 int		GetMaxGraphDownloadRate()			{ return maxGraphDownloadRate; }
	 void		SetMaxGraphUploadRate(int in);
	 void		SetMaxGraphDownloadRate(int in)		{ maxGraphDownloadRate = (in ? in : 96); }

	 uint32	GetMaxDownload();
	 uint64	GetMaxDownloadInBytesPerSec(bool dynamic = false);
	 UINT		GetMaxConnections()					{ return maxconnections; }
	 UINT		GetMaxHalfConnections()				{ return maxhalfconnections; }
	 UINT		GetMaxSourcePerFileDefault()		{ return maxsourceperfile; }
	 UINT		GetDeadServerRetries()				{ return m_uDeadServerRetries; }
	 DWORD	GetServerKeepAliveTimeout()			{ return m_dwServerKeepAliveTimeout; }
	 bool		GetConditionalTCPAccept()			{ return m_bConditionalTCPAccept; }

	 LANGID	GetLanguageID();
	 void		SetLanguageID(LANGID lid);
	 void		GetLanguages(CWordArray &aLanguageIDs);
	 void		SetLanguage();
	 bool		IsLanguageSupported(LANGID lidSelected);
	 CString	GetLangDLLNameByID(LANGID lidSelected);
	 void		InitThreadLocale();
	 void		SetRtlLocale(LCID lcid);
	 CString GetHtmlCharset();

	 bool		IsDoubleClickEnabled()				{ return transferDoubleclick; }
	 EViewSharedFilesAccess CanSeeShares()		{ return m_iSeeShares; }
	 UINT		GetToolTipDelay()					{ return m_iToolDelayTime; }
	 bool		IsBringToFront()					{ return bringtoforeground; }

	 UINT		GetSplitterbarPosition()			{ return splitterbarPosition; }
	 void		SetSplitterbarPosition(UINT pos)	{ splitterbarPosition = pos; }
	 UINT		GetSplitterbarPositionServer()		{ return splitterbarPositionSvr; }
	 void		SetSplitterbarPositionServer(UINT pos) { splitterbarPositionSvr = pos; }
	 UINT		GetTransferWnd1()					{ return m_uTransferWnd1; }
	 void		SetTransferWnd1(UINT uWnd1)			{ m_uTransferWnd1 = uWnd1; }
	 UINT		GetTransferWnd2()					{ return m_uTransferWnd2; }
	 void		SetTransferWnd2(UINT uWnd2)			{ m_uTransferWnd2 = uWnd2; }
	//MORPH START - Added by SiRoB, Splitting Bar [O²]
	 UINT		GetSplitterbarPositionStat()		{ return splitterbarPositionStat; }
	 void		SetSplitterbarPositionStat(UINT pos) { splitterbarPositionStat = pos; }
	 UINT		GetSplitterbarPositionStat_HL()		{ return splitterbarPositionStat_HL; }
	 void		SetSplitterbarPositionStat_HL(UINT pos)	{ splitterbarPositionStat_HL = pos; }
	 UINT		GetSplitterbarPositionStat_HR()		{ return splitterbarPositionStat_HR; }
	 void		SetSplitterbarPositionStat_HR(UINT pos)	{ splitterbarPositionStat_HR = pos; }
	 UINT		GetSplitterbarPositionFriend()		{ return splitterbarPositionFriend; }
	 void		SetSplitterbarPositionFriend(UINT pos)	{ splitterbarPositionFriend = pos; }
	 UINT		GetSplitterbarPositionIRC()			{ return splitterbarPositionIRC; }
	 void		SetSplitterbarPositionIRC(UINT pos)	{ splitterbarPositionIRC = pos; }
	 UINT		GetSplitterbarPositionShared()		{ return splitterbarPositionShared; }
	 void		SetSplitterbarPositionShared(UINT pos)	{ splitterbarPositionShared = pos; }
	//MORPH END   - Added by SiRoB, Splitting Bar [O²]
	// -khaos--+++> Changed datatype to avoid overflows
	 UINT		GetStatsMax()						{ return statsMax; }
	// <-----khaos-
	 bool		UseFlatBar()						{ return !depth3D; }
	 int		GetStraightWindowStyles()			{ return m_iStraightWindowStyles; }
	 bool		GetUseSystemFontForMainControls()	{ return m_bUseSystemFontForMainControls; }

	 const CString& GetSkinProfile()				{ return m_strSkinProfile; }
	 void		SetSkinProfile(LPCTSTR pszProfile)	{ m_strSkinProfile = pszProfile; }

	 UINT		GetStatsAverageMinutes()			{ return statsAverageMinutes; }
	 void		SetStatsAverageMinutes(UINT in)		{ statsAverageMinutes = in; }

	 const CString& GetNotifierConfiguration()	{ return notifierConfiguration; }
	 void		SetNotifierConfiguration(LPCTSTR pszConfigPath)	{ notifierConfiguration = pszConfigPath; }
	 bool		GetNotifierOnDownloadFinished()		{ return notifierOnDownloadFinished; }
	 bool		GetNotifierOnNewDownload()			{ return notifierOnNewDownload; }
	 bool		GetNotifierOnChat()					{ return notifierOnChat; }
	 bool		GetNotifierOnLog()					{ return notifierOnLog; }
	 bool		GetNotifierOnImportantError()		{ return notifierOnImportantError; }
	 bool		GetNotifierOnEveryChatMsg()			{ return notifierOnEveryChatMsg; }
	 bool		GetNotifierOnNewVersion()			{ return notifierOnNewVersion; }
	 ENotifierSoundType GetNotifierSoundType()	{ return notifierSoundType; }
	 const CString& GetNotifierSoundFile()		{ return notifierSoundFile; }

	 bool		GetEnableMiniMule()					{ return m_bEnableMiniMule; }
	 bool		GetRTLWindowsLayout()				{ return m_bRTLWindowsLayout; }

	 const CString& GetIRCNick()					{ return m_strIRCNick; }
	 void		SetIRCNick(LPCTSTR pszNick)			{ m_strIRCNick = pszNick; }
	 const CString& GetIRCServer()				{ return m_strIRCServer; }
	 bool		GetIRCAddTimeStamp()				{ return m_bIRCAddTimeStamp; }
	 bool		GetIRCUseChannelFilter()			{ return m_bIRCUseChannelFilter; }
	 const CString& GetIRCChannelFilter()			{ return m_strIRCChannelFilter; }
	 UINT		GetIRCChannelUserFilter()			{ return m_uIRCChannelUserFilter; }
	 bool		GetIRCUsePerform()					{ return m_bIRCUsePerform; }
	 const CString& GetIRCPerformString()			{ return m_strIRCPerformString; }
	 bool		GetIRCJoinHelpChannel()				{ return m_bIRCJoinHelpChannel; }
	 bool		GetIRCGetChannelsOnConnect()		{ return m_bIRCGetChannelsOnConnect; }
	 bool		GetIRCPlaySoundEvents()				{ return m_bIRCPlaySoundEvents; }
	 bool		GetIRCIgnoreMiscMessages()			{ return m_bIRCIgnoreMiscMessages; }
	 bool		GetIRCIgnoreJoinMessages()			{ return m_bIRCIgnoreJoinMessages; }
	 bool		GetIRCIgnorePartMessages()			{ return m_bIRCIgnorePartMessages; }
	 bool		GetIRCIgnoreQuitMessages()			{ return m_bIRCIgnoreQuitMessages; }
	 bool		GetIRCIgnorePingPongMessages()		{ return m_bIRCIgnorePingPongMessages; }
	 bool		GetIRCIgnoreEmuleAddFriendMsgs()	{ return m_bIRCIgnoreEmuleAddFriendMsgs; }
	 bool		GetIRCIgnoreEmuleSendLinkMsgs()		{ return m_bIRCIgnoreEmuleSendLinkMsgs; }
	 bool		GetIRCAllowEmuleAddFriend()			{ return m_bIRCAllowEmuleAddFriend; }
	 bool		GetIRCAcceptLinks()					{ return m_bIRCAcceptLinks; }
	 bool		GetIRCAcceptLinksFriendsOnly()		{ return m_bIRCAcceptLinksFriendsOnly; }
	 bool		GetIRCEnableSmileys()				{ return m_bIRCEnableSmileys; }
	 bool		GetMessageEnableSmileys()			{ return m_bMessageEnableSmileys; }
	 bool		GetIRCEnableUTF8()					{ return m_bIRCEnableUTF8; }

	 WORD		GetWindowsVersion();
	 bool		IsRunningAeroGlassTheme();
	 bool		GetStartMinimized()					{ return startMinimized; }
	 void		SetStartMinimized( bool instartMinimized) { startMinimized = instartMinimized; }
	 bool		GetAutoStart()						{ return m_bAutoStart; }
	 void		SetAutoStart( bool val)				{ m_bAutoStart = val; }

	 bool		GetRestoreLastMainWndDlg()			{ return m_bRestoreLastMainWndDlg; }
	 int		GetLastMainWndDlgID()				{ return m_iLastMainWndDlgID; }
	 void		SetLastMainWndDlgID(int iID)		{ m_iLastMainWndDlgID = iID; }

	 bool		GetRestoreLastLogPane()				{ return m_bRestoreLastLogPane; }
	 int		GetLastLogPaneID()					{ return m_iLastLogPaneID; }
	 void		SetLastLogPaneID(int iID)			{ m_iLastLogPaneID = iID; }

	 bool		GetSmartIdCheck()					{ return m_bSmartServerIdCheck; }
	 void		SetSmartIdCheck(bool in_smartidcheck) { m_bSmartServerIdCheck = in_smartidcheck; }
	 uint8	GetSmartIdState()					{ return smartidstate; }
	 void		SetSmartIdState(uint8 in_smartidstate) { smartidstate = in_smartidstate; }
	 bool		GetPreviewPrio()					{ return m_bpreviewprio; }
	 void		SetPreviewPrio(bool in)				{ m_bpreviewprio = in; }
	 bool		GetUpdateQueueList()				{ return m_bupdatequeuelist; }
	 bool		GetManualAddedServersHighPriority()	{ return m_bManualAddedServersHighPriority; }
	 bool		TransferFullChunks()				{ return m_btransferfullchunks; }
	 void		SetTransferFullChunks( bool m_bintransferfullchunks ) { m_btransferfullchunks = m_bintransferfullchunks; }
	 int		StartNextFile()						{ return m_istartnextfile; }
	 bool		ShowOverhead()						{ return m_bshowoverhead; }
	 void		SetNewAutoUp(bool m_bInUAP)			{ m_bUAP = m_bInUAP; }
	 bool		GetNewAutoUp()						{ return m_bUAP; }
	 void		SetNewAutoDown(bool m_bInDAP)		{ m_bDAP = m_bInDAP; }
	 bool		GetNewAutoDown()					{ return m_bDAP; }
	 bool		IsKnownClientListDisabled()			{ return m_bDisableKnownClientList; }
	 bool		IsQueueListDisabled()				{ return m_bDisableQueueList; }
	 bool		IsFirstStart()						{ return m_bFirstStart; }
	 bool		UseCreditSystem()					{ return m_bCreditSystem; }
	 void		SetCreditSystem(bool m_bInCreditSystem) { m_bCreditSystem = m_bInCreditSystem; }

	 const CString& GetTxtEditor()				{ return m_strTxtEditor; }
	 const CString& GetVideoPlayer()				{ return m_strVideoPlayer; }
	 const CString& GetVideoPlayerArgs()			{ return m_strVideoPlayerArgs; }

	 UINT		GetFileBufferSize()					{ return m_uFileBufferSize; }
	 DWORD	GetFileBufferTimeLimit()			{ return m_uFileBufferTimeLimit; }
	 INT_PTR	GetQueueSize()						{ return m_iQueueSize; }
	 int		GetCommitFiles()					{ return m_iCommitFiles; }
	 bool		GetShowCopyEd2kLinkCmd()			{ return m_bShowCopyEd2kLinkCmd; }

	// Barry
	 UINT		Get3DDepth()						{ return depth3D; }
	 bool		AutoTakeED2KLinks()					{ return autotakeed2klinks; }
	 bool		AddNewFilesPaused()					{ return addnewfilespaused; }

	 bool		TransferlistRemainSortStyle()		{ return m_bTransflstRemain; }
	 void		TransferlistRemainSortStyle(bool in){ m_bTransflstRemain = in; }

	 DWORD	GetStatsColor(int index)			{ return m_adwStatsColors[index]; }
	 void		SetStatsColor(int index, DWORD value) { m_adwStatsColors[index] = value; }
	 int		GetNumStatsColors()					{ return _countof(m_adwStatsColors); }
	 void		GetAllStatsColors(int iCount, LPDWORD pdwColors);
	 bool		SetAllStatsColors(int iCount, const LPDWORD pdwColors);
	 void		ResetStatsColor(int index);
	 bool		HasCustomTaskIconColor()			{ return bHasCustomTaskIconColor; }

	 void		SetMaxConsPerFive(UINT in)			{ MaxConperFive = in; }
	 LPLOGFONT GetHyperTextLogFont()				{ return &m_lfHyperText; }
	 void		SetHyperTextFont(LPLOGFONT plf)		{ m_lfHyperText = *plf; }
	 LPLOGFONT GetLogFont()						{ return &m_lfLogText; }
	 void		SetLogFont(LPLOGFONT plf)			{ m_lfLogText = *plf; }
	 COLORREF GetLogErrorColor()					{ return m_crLogError; }
	 COLORREF GetLogWarningColor()				{ return m_crLogWarning; }
	 COLORREF GetLogSuccessColor()				{ return m_crLogSuccess; }

	 UINT		GetMaxConperFive()					{ return MaxConperFive; }
	 UINT		GetDefaultMaxConperFive();

	 bool		IsSafeServerConnectEnabled()		{ return m_bSafeServerConnect; }
	 void		SetSafeServerConnectEnabled(bool in) { m_bSafeServerConnect = in; }
	 bool		IsMoviePreviewBackup()				{ return moviePreviewBackup; }
	 int		GetPreviewSmallBlocks()				{ return m_iPreviewSmallBlocks; }
	 bool		GetPreviewCopiedArchives()			{ return m_bPreviewCopiedArchives; }
	 int		GetInspectAllFileTypes()			{ return m_iInspectAllFileTypes; }
	 int		GetExtractMetaData()				{ return m_iExtractMetaData; }
	 bool		GetAdjustNTFSDaylightFileTime()		{ return m_bAdjustNTFSDaylightFileTime; }
	 bool		GetRearrangeKadSearchKeywords()		{ return m_bRearrangeKadSearchKeywords; }

	 const CString& GetYourHostname()				{ return m_strYourHostname; }
	 void		SetYourHostname(LPCTSTR pszHostname){ m_strYourHostname = pszHostname; }
	 bool		IsCheckDiskspaceEnabled()			{ return checkDiskspace; }
	 UINT		GetMinFreeDiskSpace()				{ return m_uMinFreeDiskSpace; }
	 bool		GetSparsePartFiles();
	 void		SetSparsePartFiles(bool bEnable)	{ m_bSparsePartFiles = bEnable; }
	 bool		GetResolveSharedShellLinks()		{ return m_bResolveSharedShellLinks; }
	 bool		IsShowUpDownIconInTaskbar()			{ return m_bShowUpDownIconInTaskbar; }
	 bool		IsWin7TaskbarGoodiesEnabled()		{ return m_bShowWin7TaskbarGoodies; }
	 void		SetWin7TaskbarGoodiesEnabled(bool flag)	{ m_bShowWin7TaskbarGoodies = flag; }

	 void		SetMaxUpload(uint32 val);
	 void		SetMaxDownload(uint32 val);

	 WINDOWPLACEMENT GetEmuleWindowPlacement()	{ return EmuleWindowPlacement; }
	 void		SetWindowLayout(const WINDOWPLACEMENT &in) { EmuleWindowPlacement = in; }

	 bool		GetAutoConnectToStaticServersOnly()	{ return m_bAutoConnectToStaticServersOnly; }
	 UINT		GetUpdateDays()						{ return versioncheckdays; }
	 time_t	GetLastVC()							{ return versioncheckLastAutomatic; }
	 void		UpdateLastVC();
	 int		GetIPFilterLevel()					{ return filterlevel; }
	 const CString& GetMessageFilter()			{ return messageFilter; }
	 const CString& GetCommentFilter()			{ return commentFilter; }
	 void		SetCommentFilter(const CString &strFilter) { commentFilter = strFilter; }
	 const CString& GetFilenameCleanups()			{ return filenameCleanups; }

	 bool		ShowRatesOnTitle()					{ return showRatesInTitle; }
	 void		LoadCats();
	 const CString& GetDateTimeFormat()			{ return m_strDateTimeFormat; }
	 const CString& GetDateTimeFormat4Log()		{ return m_strDateTimeFormat4Log; }
	 const CString& GetDateTimeFormat4Lists()		{ return m_strDateTimeFormat4Lists; }

	// Download Categories (Ornis)
	 INT_PTR	AddCat(Category_Struct *cat)		{ catMap.Add(cat); return catMap.GetCount() - 1; }
	 bool		MoveCat(INT_PTR from, INT_PTR to);
	 void		RemoveCat(INT_PTR index);
	 INT_PTR	GetCatCount()						{ return catMap.GetCount(); }
	 bool		SetCatFilter(INT_PTR index, int filter);
	 int		GetCatFilter(INT_PTR index);
	 bool		GetCatFilterNeg(INT_PTR index);
	 void		SetCatFilterNeg(INT_PTR index, bool val);
	 Category_Struct* GetCategory(INT_PTR index)	{ return (index >= 0 && index<catMap.GetCount()) ? catMap[index] : NULL; }
	 const CString& GetCatPath(INT_PTR index)		{ return catMap[index]->strIncomingPath; }
	 DWORD	GetCatColor(INT_PTR index, int nDefault = COLOR_BTNTEXT);

	 bool		GetPreviewOnIconDblClk()			{ return m_bPreviewOnIconDblClk; }
	 bool		GetCheckFileOpen()					{ return m_bCheckFileOpen; }
	 bool		ShowRatingIndicator()				{ return indicateratings; }
	 bool		WatchClipboard4ED2KLinks()			{ return watchclipboard; }
	 bool		GetRemoveToBin()					{ return m_bRemove2bin; }
	 bool		GetFilterServerByIP()				{ return filterserverbyip; }

	 bool		GetLog2Disk()						{ return log2disk; }
	 bool		GetDebug2Disk()						{ return m_bVerbose && debug2disk; }
	 int		GetMaxLogBuff()						{ return iMaxLogBuff; }
	 UINT		GetMaxLogFileSize()					{ return uMaxLogFileSize; }
	 ELogFileFormat GetLogFileFormat()			{ return m_iLogFileFormat; }

	// Web Server
	 uint16	GetWSPort()							{ return m_nWebPort; }
	 bool		GetWSUseUPnP()						{ return m_bWebUseUPnP && GetWSIsEnabled(); }
	 void		SetWSPort(uint16 uPort)				{ m_nWebPort = uPort; }
	 const CString& GetWSPass()					{ return m_strWebPassword; }
	 void		SetWSPass(const CString &strNewPass);
	 bool		GetWSIsEnabled()					{ return m_bWebEnabled; }
	 void		SetWSIsEnabled(bool bEnable)		{ m_bWebEnabled = bEnable; }
	 bool		GetWebUseGzip()						{ return m_bWebUseGzip; }
	 void		SetWebUseGzip(bool bUse)			{ m_bWebUseGzip = bUse; }
	 int		GetWebPageRefresh()					{ return m_nWebPageRefresh; }
	 void		SetWebPageRefresh(int nRefresh)		{ m_nWebPageRefresh = nRefresh; }
	 bool		GetWSIsLowUserEnabled()				{ return m_bWebLowEnabled; }
	 void		SetWSIsLowUserEnabled(bool in)		{ m_bWebLowEnabled = in; }
	 const CString& GetWSLowPass()				{ return m_strWebLowPassword; }
	 int		GetWebTimeoutMins()					{ return m_iWebTimeoutMins; }
	 bool		GetWebAdminAllowedHiLevFunc()		{ return m_bAllowAdminHiLevFunc; }
	 void		SetWSLowPass(const CString &strNewPass);
	 const CUIntArray& GetAllowedRemoteAccessIPs() { return m_aAllowedRemoteAccessIPs; }
	 uint32	GetMaxWebUploadFileSizeMB()			{ return m_iWebFileUploadSizeLimitMB; }
	 bool		GetWebUseHttps()					{ return m_bWebUseHttps; }
	 void		SetWebUseHttps(bool bUse)			{ m_bWebUseHttps = bUse; }
	 const CString& GetWebCertPath()				{ return m_sWebHttpsCertificate; }
	 void		SetWebCertPath(const CString &path)		{ m_sWebHttpsCertificate = path; };
	 const CString& GetWebKeyPath()				{ return m_sWebHttpsKey; }
	 void		SetWebKeyPath(const CString &path)	{ m_sWebHttpsKey = path; };

	 void		SetMaxSourcesPerFile(UINT in)		{ maxsourceperfile = in; }
	 void		SetMaxConnections(UINT in)			{ maxconnections = in; }
	 void		SetMaxHalfConnections(UINT in)		{ maxhalfconnections = in; }
	 bool		IsSchedulerEnabled()				{ return scheduler; }
	 void		SetSchedulerEnabled(bool in)		{ scheduler = in; }
	 bool		GetDontCompressAvi()				{ return dontcompressavi; }

	 bool		MsgOnlyFriends()					{ return msgonlyfriends; }
	 bool		MsgOnlySecure()						{ return msgsecure; }
	 UINT		GetMsgSessionsMax()					{ return maxmsgsessions; }
	 bool		IsSecureIdentEnabled()				{ return m_bUseSecureIdent; } // use client credits->CryptoAvailable() to check if encryption is really available and not this function
	 bool		IsAdvSpamfilterEnabled()			{ return m_bAdvancedSpamfilter; }
	 bool		IsChatCaptchaEnabled()				{ return IsAdvSpamfilterEnabled() && m_bUseChatCaptchas; }
	 const CString& GetTemplate()					{ return m_strTemplateFile; }
	 void		SetTemplate(const CString &in)		{ m_strTemplateFile = in; }
	 bool		GetNetworkKademlia()				{ return networkkademlia && udpport > 0; }
	 void		SetNetworkKademlia(bool val);
	 bool		GetNetworkED2K()					{ return networked2k; }
	 void		SetNetworkED2K(bool val)			{ networked2k = val; }

	// deadlake PROXYSUPPORT
	 const ProxySettings& GetProxySettings()		{ return proxy; }
	 void		SetProxySettings(const ProxySettings &proxysettings) { proxy = proxysettings; }

	 bool		ShowCatTabInfos()					{ return showCatTabInfos; }
	 void		ShowCatTabInfos(bool in)			{ showCatTabInfos = in; }

	 bool		AutoFilenameCleanup()				{ return autofilenamecleanup; }
	 void		AutoFilenameCleanup(bool in)		{ autofilenamecleanup = in; }
	 void		SetFilenameCleanups(const CString &in) { filenameCleanups = in; }

	 bool		GetResumeSameCat()					{ return resumeSameCat; }
	 bool		IsGraphRecreateDisabled()			{ return dontRecreateGraphs; }
	 bool		IsExtControlsEnabled()				{ return m_bExtControls; }
	 void		SetExtControls(bool in)				{ m_bExtControls = in; }
	 bool		GetRemoveFinishedDownloads()		{ return m_bRemoveFinishedDownloads; }

	 INT_PTR	GetMaxChatHistoryLines()			{ return m_iMaxChatHistory; }
	 bool		GetUseAutocompletion()				{ return m_bUseAutocompl; }
	 bool		GetUseDwlPercentage()				{ return m_bShowDwlPercentage; }
	 void		SetUseDwlPercentage(bool in)		{ m_bShowDwlPercentage = in; }
	 bool		GetShowActiveDownloadsBold()		{ return m_bShowActiveDownloadsBold; }
	 bool		GetShowSharedFilesDetails()			{ return m_bShowSharedFilesDetails; }
	 void		SetShowSharedFilesDetails(bool bIn)	{ m_bShowSharedFilesDetails = bIn; }
	 bool		GetAutoShowLookups()				{ return m_bAutoShowLookups; }
	 void		SetAutoShowLookups(bool bIn)		{ m_bAutoShowLookups = bIn; }
	 bool		GetForceSpeedsToKB()				{ return m_bForceSpeedsToKB; }
	 bool		GetExtraPreviewWithMenu()			{ return m_bExtraPreviewWithMenu; }

	//Toolbar
	 const CString& GetToolbarSettings()			{ return m_sToolbarSettings; }
	 void		SetToolbarSettings(const CString &in) { m_sToolbarSettings = in; }
	 const CString& GetToolbarBitmapSettings()	{ return m_sToolbarBitmap; }
	 void		SetToolbarBitmapSettings(const CString &path) { m_sToolbarBitmap = path; }
	 EToolbarLabelType GetToolbarLabelSettings()	{ return m_nToolbarLabels; }
	 void		SetToolbarLabelSettings(EToolbarLabelType eLabelType)	{ m_nToolbarLabels = eLabelType; }
	 bool		GetReBarToolbar()					{ return m_bReBarToolbar; }
	 bool		GetUseReBarToolbar();
	 CSize	GetToolbarIconSize()				{ return m_sizToolbarIconSize; }
	 void		SetToolbarIconSize(CSize siz)		{ m_sizToolbarIconSize = siz; }

	 bool		IsTransToolbarEnabled()				{ return m_bWinaTransToolbar; }
	 bool		IsDownloadToolbarEnabled()			{ return m_bShowDownloadToolbar; }
	 void		SetDownloadToolbar(bool bShow)		{ m_bShowDownloadToolbar = bShow; }

	 int		GetSearchMethod()					{ return m_iSearchMethod; }
	 void		SetSearchMethod(int iMethod)		{ m_iSearchMethod = iMethod; }

	// ZZ:UploadSpeedSense -->
	 bool		IsDynUpEnabled();
	 void		SetDynUpEnabled(bool newValue)		{ m_bDynUpEnabled = newValue; }
	 int		GetDynUpPingTolerance()				{ return m_iDynUpPingTolerance; }
	 int		GetDynUpGoingUpDivider()			{ return m_iDynUpGoingUpDivider; }
	 int		GetDynUpGoingDownDivider()			{ return m_iDynUpGoingDownDivider; }
	 int		GetDynUpNumberOfPings()				{ return m_iDynUpNumberOfPings; }
	 bool		IsDynUpUseMillisecondPingTolerance() { return m_bDynUpUseMillisecondPingTolerance; } // EastShare - Added by TAHO, USS limit
	 int		GetDynUpPingToleranceMilliseconds()	{ return m_iDynUpPingToleranceMilliseconds; } // EastShare - Added by TAHO, USS limit
	 void		SetDynUpPingToleranceMilliseconds(int in) { m_iDynUpPingToleranceMilliseconds = in; }
	// ZZ:UploadSpeedSense <--

	 bool		GetA4AFSaveCpu()					{ return m_bA4AFSaveCpu; } // ZZ:DownloadManager

	 bool		GetHighresTimer()					{ return m_bHighresTimer; }

	 CString	GetHomepageBaseURL()				{ return GetHomepageBaseURLForLevel(GetWebMirrorAlertLevel()); }
	 CString	GetVersionCheckBaseURL();
	 CString	GetVersionCheckURL();
	 void		SetWebMirrorAlertLevel(uint8 newValue) { m_nWebMirrorAlertLevel = newValue; }
	 bool		IsDefaultNick(const CString &strCheck);
	 UINT		GetWebMirrorAlertLevel();
	 bool		UseSimpleTimeRemainingComputation()	{ return m_bUseOldTimeRemaining; }

	 bool		IsRunAsUserEnabled();
	 bool		IsPreferingRestrictedOverUser()		{ return m_bPreferRestrictedOverUser; }

	// PeerCache
	 bool		IsPeerCacheDownloadEnabled()		{ return (m_bPeerCacheEnabled && !IsClientCryptLayerRequested()); }
	 time_t	GetPeerCacheLastSearch()			{ return m_uPeerCacheLastSearch; }
	 bool		WasPeerCacheFound()					{ return m_bPeerCacheWasFound; }
	 void		SetPeerCacheLastSearch(time_t dwLastSearch) { m_uPeerCacheLastSearch = dwLastSearch; }
	 void		SetPeerCacheWasFound(bool bFound)	{ m_bPeerCacheWasFound = bFound; }
	 uint16	GetPeerCachePort()					{ return m_nPeerCachePort; }
	 void		SetPeerCachePort(uint16 nPort)		{ m_nPeerCachePort = nPort; }
	 bool		GetPeerCacheShow()					{ return m_bPeerCacheShow; }

	// Verbose log options
	 bool		GetEnableVerboseOptions()			{ return m_bEnableVerboseOptions; }
	 bool		GetVerbose()						{ return m_bVerbose; }
	 bool		GetFullVerbose()					{ return m_bVerbose && m_bFullVerbose; }
	 bool		GetDebugSourceExchange()			{ return m_bVerbose && m_bDebugSourceExchange; }
	 bool		GetLogBannedClients()				{ return m_bVerbose && m_bLogBannedClients; }
	 bool		GetLogRatingDescReceived()			{ return m_bVerbose && m_bLogRatingDescReceived; }
	 bool		GetLogSecureIdent()					{ return m_bVerbose && m_bLogSecureIdent; }
	 bool		GetLogFilteredIPs()					{ return m_bVerbose && m_bLogFilteredIPs; }
	 bool		GetLogFileSaving()					{ return m_bVerbose && m_bLogFileSaving; }
	 bool		GetLogA4AF()						{ return m_bVerbose && m_bLogA4AF; } // ZZ:DownloadManager
	 bool		GetLogUlDlEvents()					{ return m_bVerbose && m_bLogUlDlEvents; }
	 bool		GetLogKadSecurityEvents()			{ return m_bVerbose && true; }
	 bool		GetUseDebugDevice()					{ return m_bUseDebugDevice; }
	 int		GetDebugServerTCPLevel()			{ return m_iDebugServerTCPLevel; }
	 int		GetDebugServerUDPLevel()			{ return m_iDebugServerUDPLevel; }
	 int		GetDebugServerSourcesLevel()		{ return m_iDebugServerSourcesLevel; }
	 int		GetDebugServerSearchesLevel()		{ return m_iDebugServerSearchesLevel; }
	 int		GetDebugClientTCPLevel()			{ return m_iDebugClientTCPLevel; }
	 int		GetDebugClientUDPLevel()			{ return m_iDebugClientUDPLevel; }
	 int		GetDebugClientKadUDPLevel()			{ return m_iDebugClientKadUDPLevel; }
	 int		GetDebugSearchResultDetailLevel()	{ return m_iDebugSearchResultDetailLevel; }
	 int		GetVerboseLogPriority()				{ return	m_byLogLevel; }

	// Firewall settings
	 bool		IsOpenPortsOnStartupEnabled()		{ return m_bOpenPortsOnStartUp; }

	//AICH Hash
	 bool		IsTrustingEveryHash()				{ return m_bTrustEveryHash; } // this is a debug option

	 bool		IsRememberingDownloadedFiles()		{ return m_bRememberDownloadedFiles; }
	 bool		IsRememberingCancelledFiles()		{ return m_bRememberCancelledFiles; }
	 bool		DoPartiallyPurgeOldKnownFiles()		{ return m_bPartiallyPurgeOldKnownFiles; }
	 void		SetRememberDownloadedFiles(bool nv)	{ m_bRememberDownloadedFiles = nv; }
	 void		SetRememberCancelledFiles(bool nv)	{ m_bRememberCancelledFiles = nv; }
	// mail notifier
	 const EmailSettings &GetEmailSettings()		{ return m_email; };
	 void		SetEmailSettings(const EmailSettings &settings) { m_email = settings; }

	 bool		IsNotifierSendMailEnabled()			{ return m_email.bSendMail; }

	 void		SetNotifierSendMail(bool nv)		{ m_email.bSendMail = nv; }
	 bool		DoFlashOnNewMessage()				{ return m_bIconflashOnNewMessage; }
	 void		IniCopy(const CString &si, const CString &di);

	 void		EstimateMaxUploadCap(uint32 nCurrentUpload);
	 bool		GetAllocCompleteMode()				{ return m_bAllocFull; }
	 void		SetAllocCompleteMode(bool in)		{ m_bAllocFull = in; }

	// encryption
	 bool		IsClientCryptLayerSupported()		{ return m_bCryptLayerSupported; }
	 bool		IsClientCryptLayerRequested()		{ return IsClientCryptLayerSupported() && m_bCryptLayerRequested; }
	 bool		IsClientCryptLayerRequired()		{ return IsClientCryptLayerRequested() && m_bCryptLayerRequired; }
	 bool		IsClientCryptLayerRequiredStrict()	{ return false; } // not even incoming test connections will be answered
	 bool		IsServerCryptLayerUDPEnabled()		{ return IsClientCryptLayerSupported(); }
	 bool		IsServerCryptLayerTCPRequested()	{ return IsClientCryptLayerRequested(); }
	 uint32	GetKadUDPKey()						{ return m_dwKadUDPKey; }
	 uint8	GetCryptTCPPaddingLength()			{ return m_byCryptTCPPaddingLength; }

	// UPnP
	 bool		GetSkipWANIPSetup()					{ return m_bSkipWANIPSetup; }
	 bool		GetSkipWANPPPSetup()				{ return m_bSkipWANPPPSetup; }
	 bool		IsUPnPEnabled()						{ return m_bEnableUPnP; }
	 void		SetSkipWANIPSetup(bool nv)			{ m_bSkipWANIPSetup = nv; }
	 void		SetSkipWANPPPSetup(bool nv)			{ m_bSkipWANPPPSetup = nv; }
	 bool		CloseUPnPOnExit()					{ return m_bCloseUPnPOnExit; }
	 bool		IsWinServUPnPImplDisabled()			{ return m_bIsWinServImplDisabled; }
	 bool		IsMinilibUPnPImplDisabled()			{ return m_bIsMinilibImplDisabled; }
	 int		GetLastWorkingUPnPImpl()			{ return m_nLastWorkingImpl; }
	 void		SetLastWorkingUPnPImpl(int val)		{ m_nLastWorkingImpl = val; }

	// Spam filter
	 bool		IsSearchSpamFilterEnabled()			{ return m_bEnableSearchResultFilter; }

	 bool		IsStoringSearchesEnabled()			{ return m_bStoreSearches; }
	 bool		GetPreventStandby()					{ return m_bPreventStandby; }
	 uint16	GetRandomTCPPort();
	 uint16	GetRandomUDPPort();
	 int		GetRecommendedMaxConnections();

	// Beta related
#ifdef _BETA
	 bool		ShouldBetaNag()						{ return !m_bBetaNaggingDone; }
	 void		SetDidBetaNagging()					{ m_bBetaNaggingDone = true; }
#endif
public:
	 CString	m_strFileCommentsFilePath;
	 Preferences_Ext_Struct *prefsExt;
	 WORD		m_wWinVer;
	 CArray<Category_Struct*,Category_Struct*> catMap;
	 CString	m_astrDefaultDirs[13];
	 bool		m_abDefaultDirsCreated[13];
	 int		m_nCurrentUserDirMode; // Only for PPgTweaks

	 void		CreateUserHash();
	 void		SetStandardValues();
	 void		LoadPreferences();
	 void		SavePreferences();
	 CString	GetHomepageBaseURLForLevel(int nLevel);
	 CString	GetDefaultDirectory(EDefaultDirectory eDirectory, bool bCreate = true);
};

extern bool g_bLowColorDesktop;
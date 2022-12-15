#ifndef _TR064_ERRORS_H_
#define _TR064_ERRORS_H_

/* Tr064 error code */
typedef enum{
	Invalid_Action=401,
	Invalid_Args=402,
	Out_Of_Sync=403,
	Action_Failed=501,
        Auth_Failed=503, 
        SSL_Needed=504 , 
	Argument_Value_Invalid=600,
	Argument_Value_Out_Of_Range=601,
	Optional_Action_Not_Implemented=602,
	Out_Of_Memory=603,
	Human_Intervention_Required=604,
	String_Argument_Too_Long=605,
	Action_Not_Authorized=606,
	ValueAlreadySpecified=701,
	ValueSpecifiedisInvalid=702,
	InactiveConnectionStateRequired=703,
	ConnectionSetupFailed=704,
	ConnectionSetupInProgress=705,
	ConnectionNotConfigured=706,
	DiscconectInProgress=707,
	InvalidLayer2Address=708,
	InternetAccessDisabled=709,
	InvalidConnectionType=710,
	ConnectionAlreadyTerminated=711,
	NullValueAtSpecifiedArrayIndex=712,
	SpecifiedArrayIndexInvalid=713,
	NoSuchEntryInArray=714,
	WildCardNotPermittedInSrcIP=715,
	WildCardNotPermittedInExtPort=716,
	ConflictInMappingEntry=718,
	ActionDisallowedWhenAutoConfigEnabled=719,
	InvalidDeviceUUID=720,
	InvalidServiceID=721,
	InvalidConnServiceSelection=723,
	SamePortValuesRequired=724,
	OnlyPermanentLeasesSupported=725,
	RemoteHostOnlySupportsWildcard=726,
	ExternalPortOnlySupportsWildcard=727,
	InvalidChannel=728,
	InvalidMACAddress=729,
	InvalidDataTransmissionRates=730,
	InvalidWEPKey=731,
	NoWEPKeyIsSet=732,
	NoPSKKeyIsSet=733,
	NoEAPServer=734,
	SetMACAddressNotPermitted=897,
	WriteAccessDisabled=898,
	SessionIDExpired=899,
/* Specified by vendor,TBD means To Be Determined */
	ActionDisallowedWhenWebUIConfigIsActive=800,
	String_Argument_too_short=801,
        String_Argument_too_long=802,
        Argument_contains_invalid_characters=803,
        ActionDisallowedWhenTR069ConfigIsActive=804,
        ActionDisallowedWhenOtherTR064ConfigIsActive=805,
	AlreadyConnected=806,
	TBD807=807,
	TBD808=808,
	TBD809=809,
	TBD810=810,
	TBD811=811,
	TBD812=812,
	TBD813=813,
	TBD814=814,
	TBD815=815,
	TBD816=816,
	TBD817=817,
	TBD818=818,
	TBD819=819,
	TBD820=820,
	TBD821=821,
	TBD822=822,
	TBD823=823,
	TBD824=824,
	TBD825=825,
	TBD826=826,
	TBD827=827,
	TBD828=828,
	TBD829=829,
	TBD830=830,
	TBD831=831,
	TBD832=832,
	TBD833=833,
	TBD834=834,
	TBD835=835,
	TBD836=836,
	TBD837=837,
	TBD838=838,
	TBD839=839,
	TBD840=840,
	TBD841=841,
	TBD842=842,
	TBD843=843,
	TBD844=844,
	TBD845=845,
	TBD846=846,
	TBD847=847,
	TBD848=848,
	TBD849=849,
	TBD850=850,
	TBD851=851,
	TBD852=852,
	TBD853=853,
	TBD854=854,
	TBD855=855,
	TBD856=856,
	TBD857=857,
	TBD858=858,
	TBD859=859,
	TBD860=860,
	TBD861=861,
	TBD862=862,
	TBD863=863,
	TBD864=864,
	TBD865=865,
	TBD866=866,
	TBD867=867,
	TBD868=868,
	TBD869=869,
	TBD870=870,
	TBD871=871,
	TBD872=872,
	TBD873=873,
	TBD874=874,
	TBD875=875,
	TBD876=876,
	TBD877=877,
	TBD878=878,
	TBD879=879,
	TBD880=880,
	TBD881=881,
	TBD882=882,
	TBD883=883,
	TBD884=884,
	TBD885=885,
	TBD886=886,
	TBD887=887,
	TBD888=888,
	TBD889=889,
	TBD890=890,
	TBD891=891,
	TBD892=892,
	TBD893=893,
	TBD894=894,
	TBD895=895,
	TBD896=896
}TR064_ERRORCODE;


typedef struct{
	TR064_ERRORCODE lsdcc_errorCode;
	char *lsdcc_errorDesc;
}LSDCC_ERROR;

extern LSDCC_ERROR lsdcc_error_entry[];

#if 0
LSDCC_ERROR lsdcc_error_entry[]={
	{Invalid_Action,"Invalid Action"},
	{Invalid_Args,"Invalid Args"},
	{Out_Of_Sync,"Out of sync"},
	{Invalid_Variable,"Invalid Variable"},
	{Action_Failed,"Action Failed"},
	{Argument_Value_Invalid,"Argument Value Invalid"},
	{Argument_Value_Out_Of_Range,"Argument Value Out of Range"},
	{Optional_Action_Not_Implemented,"Optional Action Not Implemented"},
	{Out_Of_Memory,"Out of Memory"},
	{Human_Intervention_Required,"Human Intervention Required"},
	{String_Argument_Too_Long,"String Argument Too Long"},
	{Action_Not_Authorized,"Action Not Authorized"},
	{ValueAlreadySpecified,"ValueAlreadySpecified"},
	{ValueSpecifiedisInvalid,"ValueSpecifiedIsInvalid"},
	{InactiveConnectionStateRequired,"InactiveConnectionStateRequired"},
	{ConnectionSetupFailed,"ConnectionSetupFailed"},
	{ConnectionSetupInProgress,"ConnectionSetupInProgress"},
	{ConnectionNotConfigured,"ConnectionNotConfigured"},
	{DiscconectInProgress,"DiscconectInProgress"},
	{InvalidLayer2Address,"InvalidLayer2Address"},
	{InternetAccessDisabled,"InternetAccessDisabled"},
	{InvalidConnectionType,"InvalidConnectionType"},
	{ConnectionAlreadyTerminated,"ConnectionAlreadyTerminated"},
	{NullValueAtSpecifiedArrayIndex,"NullValueAtSpecifiedArrayIndex"},
	{SpecifiedArrayIndexInvalid,"SpecifiedArrayIndexInvalid"},
	{NoSuchEntryInArray,"NoSuchEntryInArray"},
	{WildCardNotPermittedInSrcIP,"WildCardNotPermittedInSrcIP"},
	{WildCardNotPermittedInExtPort,"WildCardNotPermittedInExtPort"},
	{ConflictInMappingEntry,"ConflictInMappingEntry"},
	{ActionDisallowedWhenAutoConfigEnabled,"ActionDisallowedWhenAutoConfigEnabled"},
	{InvalidDeviceUUID,"InvalidDeviceUUID"},
	{InvalidServiceID,"InvalidServiceID"},
	{InvalidConnServiceSelection,"InvalidConnServiceSelection"},
	{SamePortValuesRequired,"SamePortValuesRequired"},
	{OnlyPermanentLeasesSupported,"OnlyPermanentLeasesSupported"},
	{RemoteHostOnlySupportsWildcard,"RemoteHostOnlySupportsWildcard"},
	{ExternalPortOnlySupportsWildcard,"ExternalPortOnlySupportsWildcard"},
	{InvalidChannel,"InvalidChannel"},
	{InvalidMACAddress,"InvalidMACAddress"},
	{InvalidDataTransmissionRates,"InvalidDataTransmissionRates"},
	{InvalidWEPKey,"InvalidWEPKey"},
	{NoWEPKeyIsSet,"NoWEPKeyIsSet"},
	{NoPSKKeyIsSet,"NoPSKKeyIsSet"},
	{NoEAPServer,"NoEAPServer"},
	{SetMACAddressNotPermitted,"SetMACAddressNotPermitted"},
	{WriteAccessDisabled,"WriteAccessDisabled"},
	{SessionIDExpired,"SessionIDExpired"},
	{TBD800_DigestAuthfailed,"Unauthorized"},//Defined for http degist authorization, Jeff Sun - Jul.19.2005
	{TBD801_B64Authfailed,"Unauthorized"},//Defined for http base64 authorization, Jeff Sun - Jul.19.2005
	{TBD802,"TBD802"},
	{TBD803,"TBD803"},
	{TBD804,"TBD804"},
	{TBD805,"TBD805"},
	{TBD806,"TBD806"},
	{TBD807,"TBD807"},
	{TBD808,"TBD808"},
	{TBD809,"TBD809"},
	{TBD810,"TBD810"},
	{TBD811,"TBD811"},
	{TBD812,"TBD812"},
	{TBD813,"TBD813"},
	{TBD814,"TBD814"},
	{TBD815,"TBD815"},
	{TBD816,"TBD816"},
	{TBD817,"TBD817"},
	{TBD818,"TBD818"},
	{TBD819,"TBD819"},
	{TBD820,"TBD820"},
	{TBD821,"TBD821"},
	{TBD822,"TBD822"},
	{TBD823,"TBD823"},
	{TBD824,"TBD824"},
	{TBD825,"TBD825"},
	{TBD826,"TBD826"},
	{TBD827,"TBD827"},
	{TBD828,"TBD828"},
	{TBD829,"TBD829"},
	{TBD830,"TBD830"},
	{TBD831,"TBD831"},
	{TBD832,"TBD832"},
	{TBD833,"TBD833"},
	{TBD834,"TBD834"},
	{TBD835,"TBD835"},
	{TBD836,"TBD836"},
	{TBD837,"TBD837"},
	{TBD838,"TBD838"},
	{TBD839,"TBD839"},
	{TBD840,"TBD840"},
	{TBD841,"TBD841"},
	{TBD842,"TBD842"},
	{TBD843,"TBD843"},
	{TBD844,"TBD844"},
	{TBD845,"TBD845"},
	{TBD846,"TBD846"},
	{TBD847,"TBD847"},
	{TBD848,"TBD848"},
	{TBD849,"TBD849"},
	{TBD850,"TBD850"},
	{TBD851,"TBD851"},
	{TBD852,"TBD852"},
	{TBD853,"TBD853"},
	{TBD854,"TBD854"},
	{TBD855,"TBD855"},
	{TBD856,"TBD856"},
	{TBD857,"TBD857"},
	{TBD858,"TBD858"},
	{TBD859,"TBD859"},
	{TBD860,"TBD860"},
	{TBD861,"TBD861"},
	{TBD862,"TBD862"},
	{TBD863,"TBD863"},
	{TBD864,"TBD864"},
	{TBD865,"TBD865"},
	{TBD866,"TBD866"},
	{TBD867,"TBD867"},
	{TBD868,"TBD868"},
	{TBD869,"TBD869"},
	{TBD870,"TBD870"},
	{TBD871,"TBD871"},
	{TBD872,"TBD872"},
	{TBD873,"TBD873"},
	{TBD874,"TBD874"},
	{TBD875,"TBD875"},
	{TBD876,"TBD876"},
	{TBD877,"TBD877"},
	{TBD878,"TBD878"},
	{TBD879,"TBD879"},
	{TBD880,"TBD880"},
	{TBD881,"TBD881"},
	{TBD882,"TBD882"},
	{TBD883,"TBD883"},
	{TBD884,"TBD884"},
	{TBD885,"TBD885"},
	{TBD886,"TBD886"},
	{TBD887,"TBD887"},
	{TBD888,"TBD888"},
	{TBD889,"TBD889"},
	{TBD890,"TBD890"},
	{TBD891,"TBD891"},
	{TBD892,"TBD892"},
	{TBD893,"TBD893"},
	{TBD894,"TBD894"},
	{TBD895,"TBD895"},
	{TBD896,"TBD896"}
};
#endif

/* Get errorDescription throught errorCode */
char *Lsdcc_ErrorCode2ErrorDesc(int errCode);

#endif
/**
 * @file   
 * @author 
 * @date   2012-06-20
 * @brief  
 *
 * Copyright - 2009 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
/**
 * @file log_errcode_de.h
 * @author andy_wang
 * @date   2012-06-20
 * @brief  LOG message format   
 *
 * Copyright - 2009 SerComm Corporation. All Rights Reserved. 
 * SerComm Corporation reserves the right to make changes to this document without notice. 
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability 
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising 
 * out of the application or use of any product or circuit. SerComm Corporation specifically 
 * disclaims any and all liability, including without limitation consequential or incidental damages; 
 * neither does it convey any license under its patent rights, nor the rights of others. 
 */

#ifndef __LOG_ERRFORMAT_DE_H__
#define __LOG_ERRFORMAT_DE_H__

/* 1.5 Format of caller list (incoming) */
#define LOG_ERRCODE_CL00 " %s"
#define LOG_ERRCODE_CL01 " %s"


/*2.1 Messages regarding Internet and DSL*/  

#define LOG_ERRCODE_INTDSL_R001 " Anmeldung beim Internetanbieter ist fehlgeschlagen. (R001)"
#define LOG_ERRCODE_INTDSL_R001_REASON "Anmeldung beim Internetanbieter ist fehlgeschlagen."
	/*PPPoE connection could not be established. Login failed.*/
#define LOG_ERRCODE_INTDSL_R001_56_0001 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0001)"
#define LOG_ERRCODE_INTDSL_R001_56_0001_REASON "Radius Fehlermeldung"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0022 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0022)"
#define LOG_ERRCODE_INTDSL_R001_56_0022_REASON "Der Mitbenutzer-Zugang wurde vom Hauptnutzer gesperrt"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0023 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0023)"
#define LOG_ERRCODE_INTDSL_R001_56_0023_REASON "Ihre Zugangsdaten wurden gesperrt"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0025 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0025)"
#define LOG_ERRCODE_INTDSL_R001_56_0025_REASON "Mit diesen Zugangsdaten ist an diesem Anschluss kein Verbindungsaufbau möglich"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0026 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0026)"
#define LOG_ERRCODE_INTDSL_R001_56_0026_REASON "Es ist ein Fehler bei der Identifizierung Ihrer Zugangsdaten aufgetreten"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/	
#define LOG_ERRCODE_INTDSL_R001_56_0028 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0028)"
#define LOG_ERRCODE_INTDSL_R001_56_0028_REASON "Ihr T-Online Zugang wurde gesperrt"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0030 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0030)"
#define LOG_ERRCODE_INTDSL_R001_56_0030_REASON "Mit den verwendeten Zugangsdaten besteht bereits eine Verbindung"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0034 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0034)"
#define LOG_ERRCODE_INTDSL_R001_56_0034_REASON "Der Zugang ins Internet ist nicht möglich, da der genutzte T-Online Tarif nicht zu dem bestehenden T-DSL Anschluss passt"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0002 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0002)"
#define LOG_ERRCODE_INTDSL_R001_56_0002_REASON "access over this NAS not allowed"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0003 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0003)"
#define LOG_ERRCODE_INTDSL_R001_56_0003_REASON "no free ip address"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0004 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0004)"
#define LOG_ERRCODE_INTDSL_R001_56_0004_REASON "wrong access attributes"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0005 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0005)"
#define LOG_ERRCODE_INTDSL_R001_56_0005_REASON "VIP not available"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0006 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0006)"
#define LOG_ERRCODE_INTDSL_R001_56_0006_REASON "radius server not responding"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0007 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0007)"
#define LOG_ERRCODE_INTDSL_R001_56_0007_REASON "service not supported"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0008 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0008)"
#define LOG_ERRCODE_INTDSL_R001_56_0008_REASON "class to long"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0009 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0009)"
#define LOG_ERRCODE_INTDSL_R001_56_0009_REASON "no domain"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0012 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0012)"
#define LOG_ERRCODE_INTDSL_R001_56_0012_REASON "test user"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0013 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0013)"
#define LOG_ERRCODE_INTDSL_R001_56_0013_REASON "user wrong domain"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0014 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0014)"
#define LOG_ERRCODE_INTDSL_R001_56_0014_REASON "bad form"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0015 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0015)"
#define LOG_ERRCODE_INTDSL_R001_56_0015_REASON "not in session"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0016 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0016)"
#define LOG_ERRCODE_INTDSL_R001_56_0016_REASON "domain access disabled"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0017 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0017)"
#define LOG_ERRCODE_INTDSL_R001_56_0017_REASON "authorization disabled"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0018 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0018)"
#define LOG_ERRCODE_INTDSL_R001_56_0018_REASON "port limit exceeded"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0019 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0019)"
#define LOG_ERRCODE_INTDSL_R001_56_0019_REASON "you are not allowed to connect"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0020 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0020)"
#define LOG_ERRCODE_INTDSL_R001_56_0020_REASON "unknown dynamic ip address"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0021 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0021)"
#define LOG_ERRCODE_INTDSL_R001_56_0021_REASON "no valid ip address"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0024 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0024)"
#define LOG_ERRCODE_INTDSL_R001_56_0024_REASON "no valid service level"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0027 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0027)"
#define LOG_ERRCODE_INTDSL_R001_56_0027_REASON "you are not allowed to connect right now"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0029 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0029)"
#define LOG_ERRCODE_INTDSL_R001_56_0029_REASON "authorization not available"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0031 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0031)"
#define LOG_ERRCODE_INTDSL_R001_56_0031_REASON "user name bad form"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0032 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0032)"
#define LOG_ERRCODE_INTDSL_R001_56_0032_REASON "concurrent dial in/out"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_INTDSL_R001_56_0033 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0033)"
#define LOG_ERRCODE_INTDSL_R001_56_0033_REASON "link limit exceeded"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/	
#define LOG_ERRCODE_INTDSL_R001_56_0035 " Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich:%s (R001-56-0035)"
#define LOG_ERRCODE_INTDSL_R001_56_0035_REASON "domain access revoked"
	/*PPPoE connection could not be established. Login failed due to the message provided by radius server*/
	
#define LOG_ERRCODE_INTDSL_R002 " Die Internetverbindung kann nicht aufgebaut werden, da die Tarifprüfung aktiviert ist und das aktuelle Datum nicht bekannt ist. (R002)"
	/*Could not establish internet- connection, because of activated rate-check and not known date.*/
#define LOG_ERRCODE_INTDSL_R003 " Die Internetverbindung wird abgebaut, da die Tarifprüfung aktiviert ist und das aktuelle Datum nicht bekannt ist. (R003)"
	/*The internet-connection will be terminated, because of activated rate-check and not known date.*/
#define LOG_ERRCODE_INTDSL_R004 " Die Internetverbindung wird kurz unterbrochen, um der Zwangstrennung durch den Anbieter zuvorzukommen. (R004)"
	/*The internet-connection will be terminated shortly for preventing the provider to necessary-disconnect first.*/
#define LOG_ERRCODE_INTDSL_R005 " Die maximale Anzahl der Portfreigabe- Regeln wurde erreicht. (R005)"
	/*The maximum amount of rules regarding the port handling has been achieved.*/
#define LOG_ERRCODE_INTDSL_R006 " DSL antwortet nicht (keine DSL- Synchronisierung). (R006)"
	/*DSL is not responding (DSL synchronisation failed )*/
#define LOG_ERRCODE_INTDSL_R007 " DSL ist verfügbar (DSL- Synchronisierung besteht). (R007)"
    /*DSL is available (DSL successfully synchronized) */
#define LOG_ERRCODE_INTDSL_R008 " DSL-Synchronisation beginnt(Training). (R008)"
	/*DSL synchronization running*/
#define LOG_ERRCODE_INTDSL_R009 " Internetverbindung wurde <%s> getrennt. (R009)"
    /*Connection to the Internet has been terminated*/
#define LOG_ERRCODE_INTDSL_R0010 " Internetverbindung wurde hergestellt. (R010)"
    /*Internet connection successfully established */
	
#define LOG_ERRCODE_INTDSL_R0010_1 " Internetverbindung für die Automatische Konfiguration hergestellt. (R010-1)"
	/*Internet connection successfully established with default credentials. (R10-1)*/
#define LOG_ERRCODE_INTDSL_R0010_2 " Internetverbindung für die Automatische Konfiguration hergestellt. (R010-2)"
    /*Internet connection successfully established with setup credentials.*/
#define LOG_ERRCODE_INTDSL_R0011 " PPP-Aushandlung ist fehlgeschlagen. (R011)"
	/*PPP initialization failed.*/
#define LOG_ERRCODE_INTDSL_R0012 " PPP-Aushandlung fehlgeschlagen: Testschleife gefunden. (R012) "
	/*PPP initialization failed: Loopback found.*/	
#define LOG_ERRCODE_INTDSL_R0013 " PPPoE-Fehler: DSL-Synchronisierung verloren. (R013)"
	/* PPPoE error: DSL synchronization lost.*/
#define LOG_ERRCODE_INTDSL_R0014 " PPPoE-Fehler: Falscher Parameter. (%s) (R014)"
	/*PPPoE error: false parameter(<error message>)*/
#define LOG_ERRCODE_INTDSL_R0015 " PPPoE-Fehler: Falscher Dienst-Name. (%s) (R015)"
	/*PPPoE error: wrong servicename (<error message>)*/
#define LOG_ERRCODE_INTDSL_R0016 " PPPoE-Fehler: Illegales Paket vom PPPoE-Server. (%s) (R016)" 
	/*PPPoE error: illegal paket from PPPoE server (<error message>) */
#define LOG_ERRCODE_INTDSL_R0017 " PPPoE-Fehler: PPPoE-Server meldet einen Systemfehler: (%s) (R017)"
	/*PPPoE error: PPPoE server signals a system error (<error message>)*/
#define LOG_ERRCODE_INTDSL_R0018 " PPPoE-Fehler: PPPoE-Server meldet ein Problem. (%s) (R018)"
	/*PPPoE error: PPPoE server signals that a problem occurred (<error message>)*/
#define LOG_ERRCODE_INTDSL_R0019 " PPPoE-Fehler: Unbekannter Fehler. (%s) (R019)" 
	/*PPPoE error: unknown error(<error message>)*/
#define LOG_ERRCODE_INTDSL_R0020 " PPPoE-Fehler: Zeitüberschreitung. (%s) (R020)"
	/*PPPoE error: timeout (<error message>)*/
#define LOG_ERRCODE_INTDSL_R0021 " Verbindung getrennt: Die Gegenstelle beantwortet keine LCP-Echo-Anfragen. (R021)"
	/*Connection has been terminated: Remote station is not answering to LCP Echo requests.*/
#define LOG_ERRCODE_INTDSL_R0022 " Die vom Internetanbieter zugewiesene Gateway-IP-Adresse: %s (R022)"
	/*From internet service provider transferred Gateway IP address :<IP-address>*/
#define LOG_ERRCODE_INTDSL_R0023 " Zeitüberschreitung bei der PPP-Aushandlung. (%s) (R023)"
	/*Timeout during PPP initialization (<protocol name>) */
#define LOG_ERRCODE_INTDSL_R101 " Info: PADI Paket wurde vom HG gesendet. (R101)"
    /*Info: PADI packet sent by the HG */
#define LOG_ERRCODE_INTDSL_R102 " Info: PADO Paket wurde vom HG empfangen. (R102)"
    /*Info: PADO packet received by the HG */
#define LOG_ERRCODE_INTDSL_R103 " Info: PADR Paket wurde vom HG gesendet. (R103)"
    /*Info: PADR packet sent by the HG */
#define LOG_ERRCODE_INTDSL_R104 " Info: PADS Paket wurde vom HG empfangen. (R104)"
    /*Info: PADS packet received by the HG */
#define LOG_ERRCODE_INTDSL_R105 " Info: PADT Paket wurde vom HG empfangen. (R105)"
    /*Info: PADT packet received by the HG */
#define LOG_ERRCODE_INTDSL_R106 " Info: PADT Paket wurde vom HG gesendet. (R106)"
    /*Info: PADT packet sent by the HG */
		
/*2.3 Messages regarding LAN/Link Port*/
#define LOG_ERRCODE_LI001 " HG Anschluss LAN/Link umgeschaltet als ,LAN'lokaler Ethernet LAN Anschluss (LI001)"
	/*Port #1 of HG built-in Ethernet switch configured by Web-UI for usage as standard LAN Ethernet switch port*/
#define LOG_ERRCODE_LI002 " HG Anschluss LAN/Link umgeschaltet als ,Link' zum Anschluss von externen WAN Modems (z.B. DSL- Modem) (LI002)"
	/*Port #1 of HG built-in Ethernet switch configured by Web-UI for usage as WAN access port for connection of external modem devices.*/

/*2.4 Messages regarding Internet and UMTS	*/
#define LOG_ERRCODE_UM101 " USB-Gerät ,xxx' angesteckt. (UM101)"
	/*UMTS device attached to USB	*/
#define LOG_ERRCODE_UM102 " UMTS-Modem wurde initialisiert (UM102)"
	/*UMTS modem initialized*/
#define LOG_ERRCODE_UM103 " UMTS Internetverbindung wurde erfolgreich hergestellt. IP-Adresse: %s DNS-Server: %s Gateway: %s Breitband-PoP: %s (UM103)"
	/*UMTS connection established*/
#define LOG_ERRCODE_UM104 " UMTS Internetverbindung wurde getrennt. (UM104)"
	/*UMTS connection terminated*/
#define LOG_ERRCODE_UP001 " UMTS-Modem-Fehler Abbruch: ,kein Trägersignal' (UP001)"
	/*UMTS Modem Error*/

/*2.5 Messages regarding SIP Telephony	*/
#define LOG_ERR_TIMEOUT  "Gegenstelle antwortet nicht. Zeitüberschreitung."
/* no answer from remote station received (For V005), Melinda, 2013/10/18 */
#define LOG_ERR_TIMEOUT  "Gegenstelle antwortet nicht. Zeitüberschreitung."
/* no answer from remote station received (For V005), Melinda, 2013/10/18 */
#define LOG_ERRCODE_V001 " Anmeldung der DSL-Telefonnummer (%s) war nicht erfolgreich. Ursache: DNS-Fehler (V001)"
	/*Registering with VoIP number (<RufNr>) failed: Reason: DNS error*/	
#define LOG_ERRCODE_V002 " Anmeldung der DSL-Telefonnummer (%s) war nicht erfolgreich. Gegenstelle meldet Ursache: %s (V002)"
	/*Registering with VoIP number (<RufNr>) failed: Reason: <platform message>*/
#define LOG_ERRCODE_V003 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Diese Aktion ist nicht erlaubt (SIP Fehlercode 488) (V003)"
	/*A general error regarding SIP telephony occurred: This action is not allowed <SIP error code 488> */
#define LOG_ERRCODE_V004 " Anmeldung der DSL-Telefonnummer (%s) war nicht erfolgreich. Ursache: Gegenstelle antwortet nicht. Zeitüberschreitung. (V004)"
	/*Registering with VoIP number (<RufNr>) failed: Reason: no answer from remote station received */
#define LOG_ERRCODE_V005 " Abmeldung der DSL-Telefonnummer (%s) war nicht erfolgreich. Gegenstelle meldet Ursache: %s (V005)"
	/*UnRegister with VoIP number (<RufNr>) failed: Reason: <platform message>*/
#define LOG_ERRCODE_V006 " IP-Telefonie mit %s war nicht erfolgreich. Ursache: %s (V006)"
	/*VoIP Call with VoIP number (<RufNr>) failed: Reason: <platform message>*/
#define LOG_ERRCODE_V007 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Diese Aktion ist nicht möglich. (SIP Fehlercode 403) (V007)"
	/*A general error regarding SIP telephony occurred: This action is not possible <SIP error code 403> */
#define LOG_ERRCODE_V008 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Der angerufene Teilnehmer wurde nicht gefunden (SIP Fehlercode 404) (V008)"
	/*A general error regarding SIP telephony occurred: The called party could no be found <SIP error code 404>*/
#define LOG_ERRCODE_V009 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Die gewünschte SIP Funktionalität wird nicht unterstützt (SIP Fehlercode 405) (V009)"
	/*A general error regarding SIP telephony occurred: The demanded function is not supported <SIP error code 405>*/
#define LOG_ERRCODE_V010 " Die angerufene Nummer ist unvollständig (SIP Fehlercode 484) (V010)"
    /*A general error regarding SIP telephony occurred: The called number is incomplete <SIP error code 484>*/
#define LOG_ERRCODE_V011 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Diese Aktion ist nicht möglich (SIP Fehlercode 491) (V011)"
	/*A general error regarding SIP telephony occurred: This action is not possible <SIP error code 491>*/
#define LOG_ERRCODE_V012 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Es ist ein Serverfehler aufgetreten (SIP Fehlercode 500) (V012)"
	/*A general error regarding SIP telephony occurred:<SIP server error code 500>*/
#define LOG_ERRCODE_V013 " Es ist ein allgemeiner Fehler bei der IP-Telefonie aufgetreten: Es ist ein Serverfehler aufgetreten (SIP Fehlercode 503) (V013)"
	/*general error regarding SIP telephony occurred:<SIP server error code 503>*/
#define LOG_ERRCODE_V018 " PPP-Anmeldung beim IP-Telefonie-Anbieter ist fehlgeschlagen. (V018)"
	/*PPP-login to VoIP registrar has failed*/
#define LOG_ERRCODE_V019 " PPP-Aushandlung für IP-Telefonie ist fehlgeschlagen. (V019)"
	/*PPP initialization regarding VoIP telephony has failed*/
#define LOG_ERRCODE_V020 " PPP-Aushandlung für IP-Telefonie ist fehlgeschlagen: Testschleife gefunden. (V020)"
	/*PPP initialization regarding VoIP telephony has failed: Loopback found*/
#define LOG_ERRCODE_V021 " Zeitüberschreitung bei der PPP-Aushandlung für IP-Telefonie. (%s) (V021)"
	/*Timeout occurred during PPP initialization regarding VoIP telephony (<protocol name>)*/
#define LOG_ERRCODE_V100 " Der Speeddial Speicher wurde durch den Nutzer geleert. (V100)"
	/*Speed dialing memory was successful deleted*/
#define LOG_ERRCODE_V101 " Die Internet Telefonie Verbindung (%s) wurde erfolgreich hergestellt: IP-Adresse: %s, Internet-Rufnummer: %s (V101)"
    /*Internet Telephonie connection (RufNr) has successfully been established: IP-Adresse: <IP-address>, Internet-Rufnummer: <RufNr> is filled with the telefone number that responded by the server, if available.*/
	
/*2.6 Messages regarding DynDNS*/
#define LOG_ERRCODE_D001 " DynDNS-Fehler: Der angegebene Domainname kann nicht aufgelöst werden. (D001)"
	/*DynDNS-error: The given domain name could not be resolved.*/
#define LOG_ERRCODE_D002 " DynDNS-Fehler: Der DynDNS-Anbieter meldet Fehler %s (D002)"
	/*DynDNS-error: The DynDNS provider replies <error message>*/
#define LOG_ERRCODE_D003 " DynDNS-Erfolg: Der DynDNS-Anbieter meldet %s (D003)"
	/*DynDNS successful: The DynDNS provider  replies <successful>*/
	

/*2.7 Messages regarding Save and Restore of Properties*/
#define LOG_ERRCODE_S101 " Die Konfiguration des Gerätes wurde erfolgreich gespeichert. (S101)"
	/*Properties are successfully saved into a file*/
#define LOG_ERRCODE_S102 " Die Konfiguration des Gerätes wurde erfolgreich eingelesen. (S102)"
	/*Properties are successfully restored from a file*/
#define LOG_ERRCODE_S001 " Das Import-Kennwort ist falsch. (S001)"
	/*The given password is not correct*/
#define LOG_ERRCODE_S002 " Die angegebene Datei ist keine gültige Import-Datei. (S002)"
	/*The given file is not of a valid structure*/
#define LOG_ERRCODE_S003 " Die Import-Datei enthält eine Landeseinstellung, die auf diesem Speedport nicht importiert werden kann. (S003)"
	/*The given import file contains a country selection that fits not to this type of speedport*/
#define LOG_ERRCODE_S004 " Die Import-Datei ist nicht vorhanden oder zu klein. (S004)"
	/*The given file is not existing or may is too small.*/
#define LOG_ERRCODE_S005 " Die Import-Datei passt nicht zu der aktuellen Firmware-Version. (S005)"
	/*The given file does not fit to the firmware which is running on that speedport */
#define LOG_ERRCODE_S006 " Die Import-Datei passt nicht zu diesem Gerätetyp dem Speedport. (S006)"
	/*The given file does not fit to the device typ of the speedport series.*/
#define LOG_ERRCODE_S007 " Die Import-Datei passt nicht zu dieser Geräte-Variante dem Speedport. (S007)"
	/*The given file does not fit to the device model of the speedport series.*/
#define LOG_ERRCODE_S008 " Es ist ein nicht näher spezifizierter Fehler aufgetreten. (S008)"
	/*The occurred error could not be specified in more detail.*/
#define LOG_ERRCODE_S009 " Schwerwiegender Fehler beim Import. Das Speedport wurde auf Werkseinstellungen zurückgesetzt. (S009)"
	/*A grave error occurred during import. The speedport has been set to factory default.*/
#define LOG_ERRCODE_S010 " Die angegebene Datei ist zu groß.(S010)"
	/*The given file is too big.*/
	
/*2.8 Messages regarding WLAN*/

#define LOG_ERRCODE_W201 " WPS wurde gestartet mit %s (W201)"
	/*Methode 
		1. PushButton
		2. PIN Methode vom Router gesteuert
		3. PIN Methode vom Client gesteuert
	WPS has been started <wps method>*/
#define LOG_PUSHBUTTON "PushButton"
#define LOG_AP_PIN "PIN Methode vom Router gesteuert"
#define LOG_CLINET_PIN "PIN Methode vom Client gesteuert"
	
#define LOG_ERRCODE_W202 " WPS Aktion %s (W202)"
	/*WPS action <result>*/

#define LOG_ERRCODE_W001 " WLAN-Station abgemeldet: Rechnername:%s, Mac-Adresse: %s (W001)"
	/*WLAN station not connected:    Computer name <computer name>, MAC-address: <MAC-address>*/
#define LOG_ERRCODE_W003 " WLAN Anmeldung ist gescheitert: Association-Fehler. Datenrate nicht kompatibel. Rechnername: %s, Mac-Adresse: %s (W003)"
	/*WLAN station connection establishment failed: association error. Data rate not compatible:  Computer name <computer name>, MAC-address: <MAC-address>*/
#define LOG_ERRCODE_W004 " WLAN-Anmeldung ist gescheitert: Association-Fehler. Mac-Adresse wird nicht zugelassen. Rechnername: %s, Mac-Adresse: %s (W004)"
	/*WLAN station connection establishment failed: association error. MAC address is not allowed:       Computer name <computer name>, MAC-address: <MAC-address>*/
#define LOG_ERRCODE_W005 " WLAN-Anmeldung ist gescheitert: Autorisierung fehlgeschlagen. Rechnername: %s, Mac- Adresse: %s (W005)"
	/*WLAN station connection establishment failed: Authorisation failed.        Computer name <computer name>, MAC-address: <MAC-address>*/
#define LOG_ERRCODE_W019 " WLAN-Anmeldung an 2.4 GHz Frequenzband erfolgreich:  Rechnername:%s, Mac-Adresse: %s (W019)"
	/*WLAN station successfully connected to 2.4 GHz band.      Computer name: <computer name>, MAC-address: <MAC-address>*/
#define LOG_ERRCODE_W020 " WLAN-Anmeldung an 5 GHz Frequenzband erfolgreich:  Rechnername: %s, Mac-Adresse: %s (W020)"
	/*WLAN station successfully connected to 5 GHz band.       Computer name <computer name>, MAC-address: <MAC-address>*/
#define LOG_ERRCODE_W021 " WLAN `Geräte hinzufügen' über WSC(WPS) wurde wegen zu hoher PIN-Fehlerrate abgeschaltet. (W021)"
    /*Wi-Fi Simple Configuration (WSC) detected up to 10 consecutive failed PIN verifications and entered `lockeddown' state.*/
#define LOG_ERRCODE_W006 " WLAN %s wurde auf dem Speedport aktiviert (W006)"
	/*WLAN <WLAN_radio> has been activated*/
#define LOG_ERRCODE_W007 " WLAN %s wurde auf dem Speedport deaktiviert (W007)"
	/*WLAN <WLAN_radio> has been deactivated*/
#define LOG_ERRCODE_W008 " WLAN SSID wurde geändert: %s (W008)"
	/*WLAN SSID has been changed: <WLAN SSID>*/
#define LOG_ERRCODE_W009 " WLAN Sicherheits-Modus wurde geändert: %s (W009)"
	/*WLAN security mode has been changed: <mode>
		Mode:
			. None
			. WEP
			. WPA
			. WPA/WPA2
			. WPA2
	*/		
#define LOG_ERRCODE_W010 " WLAN Passwort für die Verschlüsselung wurde geändert (W010)"
	/*WLAN password has been changed*/
#define LOG_ERRCODE_W011 " WLAN-Kanal wurde geändert: %s, %s (W011)"
	/*WLAN channel has been changed: <band, channel>
		Band: 2.4 GHz
		Channel: 1-13, Auto
		Band: 5 GHz
		Channel: 36-140, Auto
	*/
#define LOG_ERRCODE_W012 " WLAN Übertragungsmodus wurde geändert: %s (W012)"
	/*WLAN standard has been changed: <WLAN_radio>. WLAN standard has been changed in WebUI:
     * <WLAN _radio>:
		. 802.11b/g
		. 802.11g/n
		. 802.11b/g/n
        . 802.11ac
		. etc.
	*/
#define WLAN_STANDARD_BG     "802.11b/g"
#define WLAN_STANDARD_GN     "802.11g/n"
#define WLAN_STANDARD_BGN    "802.11b/g/n"
#define WLAN_STANDARD_N      "802.11n"
#define WLAN_STANDARD_AC     "802.11ac"

#define LOG_ERRCODE_W013 " WLAN Zeitschaltung aktiviert (W013)"
	/*WLAN Hibernation activated*/	
#define LOG_ERRCODE_W014 " WLAN Zeitschaltung deaktiviert (W014)"
	/*WLAN Hibernation deactivated*/
#define LOG_ERRCODE_W015 " WLAN durch Zeitschaltung aktiviert (W015)"
	/*WLAN activated by Hibernation trigger*/
#define LOG_ERRCODE_W016 " WLAN durch Zeitschaltung deaktiviert (W016)"
	/*WLAN deactivated by Hibernation trigger*/
#define LOG_ERRCODE_W017 " Der WLAN Kanal wird aufgrund notwendiger Anpassungen zur  Übertragungsverbesserung gewechselt (bisher Kanal %d) (W017)"
	/*The WLAN channel is being dynamically switched from channel x*/
#define LOG_ERRCODE_W018 " Der WLAN Kanal wurde aufgrund notwendiger Anpassungen zur  Übertragungsverbesserung auf den Kanal %d gewechselt (W018)"
	/*The WLAN channel has been dynamically switched to channel y.*/
	
/*2.11Messages regarding DHCP	*/
#define LOG_ERRCODE_H001 " DHCP ist aktiv: %s %s %s %s %s %s %s %s %s %s (H001)"
	/*"DHCP is active: <date> <time> <network> <computer name> <MAC address> <IP-address> <subnet mask> <DNS-server> <gateway> <lease time>*/
#define LOG_ERRCODE_H002 " DHCP wurde deaktiviert (H002)"
	/*DHCP has been deactivated */
#define LOG_ERRCODE_H003 " DHCP IP-Address-Vergabe gescheitert: (H003)"
	/*Providing DHCP information to a requesting station has failed.*/

/*2.12Messages regarding NTP*/	
#define LOG_ERRCODE_T101 " Die Systemzeit wurde erfolgreich aktualisiert (T101)"
	/*Time Server successfully connected and time synchronisation achieved.*/
#define LOG_ERRCODE_T102 " Die Systemzeit konnte nicht aktualisiert werden. (T102)"
	/*Time Server connected but Server responded with Error.*/
#define LOG_ERRCODE_T103 " Keine Antwort vom Timeserver. (T103)"
	/*No Time Servers reachable.*/

/*2.13Messages regarding the ACS - System*/
/*2.13.1Messages regarding the ACS - System relevant for HGs*/
#define LOG_ERRCODE_A101 " EasySupport wurde aktiviert. (A101)"
	/*EasySupport activated*/
#define LOG_ERRCODE_A102 " EasySupport wurde deaktiviert. (A102)"
	/*EasySupport deactivated*/
#define LOG_ERRCODE_A103 " Konfigurations-Service wird kontaktiert. (A103)"
	/*The HG tries to contact the ACS*/
#define LOG_ERRCODE_A104 " Zugangsdaten wurden vom Konfigurations-Service übermittelt. (A104)"
	/*The HG has received access data from the ACS*/
#define LOG_ERRCODE_A105 " Internet-Telefonie Daten wurden vom Konfigurations-Service übermittelt. (A105)"
	/*The HG has received VoIP configuration data from the ACS*/
#define LOG_ERRCODE_A106 " Firmware Update auf Version %s wurde erfolgreich durchgeführt. (A106)"
	/*The HG has successfully loaded/flashed a new firmware image*/
#define LOG_ERRCODE_A107 " Konfiguration fehlgeschlagen. (A107)"
	/*HG could not be configured*/
#define LOG_ERRCODE_A001 " Der Konfigurations-Service konnte nicht erreicht werden. (A001)"
	/*Configuration Server could not be reached*/
#define LOG_ERRCODE_A002 " Der Konfigurations-Service verweigert den Zugriff. (A002)"
	/*Access denied*/
#define LOG_ERRCODE_A003 " Ungültiges Zertifikat am Konfigurations-Service. (A003)"
	/*Invalid server certificate*/
#define LOG_ERRCODE_A004 " Fehlermeldung des Konfigurations- Services. (A004)"
	/*Configuration Server reported an error*/
#define LOG_ERRCODE_A005 " Ungültige Meldung des Konfigurations- Services. (A005)"
	/*Invalid request/response from ACS.*/
#define LOG_ERRCODE_A006 " Die Verbindung zum Konfigurations- Server ist abgebrochen. (A006)"
	/*Connection breakdown*/
#define LOG_ERRCODE_A007 " Der Konfigurations-Server antwortet nicht. (A007)"
	/*Communication timeout*/
#define LOG_ERRCODE_A008 " DSL-Telefonie Daten können nicht ermittelt werden. (A008)"
	/*VoIP data retrieval error */
#define LOG_ERRCODE_A009 " DSL-Telefonie ist nicht gebucht. (A009)"
	/*VoIP not booked*/
#define LOG_ERRCODE_A010 " Firmware Download fehlgeschlagen.(A010)"
	/*Could not download firmware update*/
#define LOG_ERRCODE_A011 " Firmware Datei beschädigt. (A011)"
	/*Firmware check failed.*/
#define LOG_ERRCODE_A012 " Die persönlichen Zugangsdaten konnten nicht ermittelt werden. (A012)"
	/*Access data retrieval error*/

	
/*2.13.2Messages regarding the ACS - System relevant for SIP Phones */	
#define LOG_ERRCODE_AS101 " Konfigurations-Service wird kontaktiert (AS101)"
	/*The SIP Phone tries to contact the ACS*/
#define LOG_ERRCODE_AS102 " Zugangsdaten wurden vom Konfigurations-Service übermittelt (AS102)"
	/*The SIP Phone has received access data from the ACS*/
#define LOG_ERRCODE_AS103 " Internet-Telefonie Daten wurden vom Konfigurations-Service übermittelt (AS102)"
	/*he SIP Phone has received VoIPconfiguration data from the ACS*/
	
#define LOG_ERRCODE_AS001 " Der Konfigurations-Service konnte nicht erreicht werden. (AS001)"	
	/*Configuration Server could not be reached*/
#define LOG_ERRCODE_AS002 " Der Konfigurations-Service verweigert den Zugriff. (AS002)"
 	/*Access denied*/
#define LOG_ERRCODE_AS003 " Ungültiges Zertifikat am Konfiguratons-Service. (AS003)"	
	/*Invalid server certificate*/
#define LOG_ERRCODE_AS004 " Fehlermeldung des Konfigurations-Service. (AS004)"
	/*Configuration Server reported an error*/
#define LOG_ERRCODE_AS005 " Ungültige Meldung des Konfigurations-Service. (AS005)"	
	/*ACS reported an error*/
#define LOG_ERRCODE_AS006 " Die Verbindung zum Konfigurations-Server ist abgebrochen. (AS006)"
	/*Connection breakdown*/
#define LOG_ERRCODE_AS007 " Der Konfigurations-Server antwortet nicht. (AS007)"
	/*Communication timeout*/
#define LOG_ERRCODE_AS008 " Internet-Telefonie Daten konnen nicht ermittelt werden. (AS008)"
	/*VoIP data retrieval error*/
#define LOG_ERRCODE_AS009 " Internet-Telefonie ist nicht gebucht. (AS009)"
	/*VoIP Service not booked*/
#define LOG_ERRCODE_AS010 " Firmware Download fehlgeschlagen. (AS010)"
	/*Could not download firmware update*/
#define LOG_ERRCODE_AS011 " Firmware Datei beschädigt. (AS011)"
	/*Firmware check failed.*/
	
/*2.14 Messages regarding DECT*/
#define LOG_ERRCODE_IVA101 " %s prüft FW Update (IVA101)"
	/*[SUOTA]  Update triggered by PP <SpeedphoneXXX>*/
#define LOG_ERRCODE_IVA102 " Neue Firmware für %s verfügbar: Version %s (IVA102)"
	/*[SUOTA] New FW version available for <SpeedphoneXXX>*/
#define LOG_ERRCODE_IVA103 " Keine neue Firmware für %s verfügbar (IVA103)"
	/*[SUOTA] No new FW version available for <SpeedphoneXXX>*/
#define LOG_ERRCODE_IVA104 " Firmware download an %s wurde gestartet. (IVA104)"
	/*[SUOTA] Firmwqare downloading initiated by <SpeedphoneXXX> at <timestamp>*/
#define LOG_ERRCODE_IVA105 " Neue Firmware erfolgreich auf %s installiert (IVA105)"
	/*[SUOTA] New FW successfully installed on <SpeedphoneXXX>*/

#define LOG_ERRCODE_ADDITION_IVA101 " Firmware Installation auf %s nicht erfolgreich (IVA101)"
#define LOG_ERRCODE_IVA001 " Firmware Installation auf %s nicht erfolgreich (IVA001)"
	/*[SUOTA] New FW installation not successful on <SpeedphoneXXX>*/

#define LOG_ERRCODE_DEC001 " Das DECT Mobilteil %s wurde mit der DECT Basis verbunden (DEC001)"
	/*PP <Speedphonexxx> was successful paired with the FP*/ 
#define LOG_ERRCODE_DEC002 " Die Verbindung des DECT Mobilteil %s zur DECT Basis wurde aufgehoben (DEC002)"
	/*PP <Speedphonexxx> was Successful unpaired to FP"*/
#define LOG_ERRCODE_DEC003 " Das DECT Mobilteil %s hat die Verbindung zur DECT Basis verloren (DEC003)"
	/*PP <Speedphonexxx> lost connecting to FP*/
#define LOG_ERRCODE_DEC004 " Das DECT Mobilteil %s hat die Verbindung zur DECT Basis hergestellt (DEC004)"
	/*PP <Speedphonexxx> connected to FP*/

/*2.15 Messages regarding USB host controller*/
#define LOG_ERRCODE_U101 " USB Gerät %s wurde angeschlossen. (U101)"
	/*USB device was mounted successfully.*/
#define LOG_ERRCODE_U102 " USB Gerät %s wurde entfernt. (U102)"
	/*USB device was dismounted successfully.*/

#define LOG_ERRCODE_U001 " Der USB-Massenspeicher %s enthält kein unterstütztes Dateisystem oder hat eine ungültige Partitionstabelle. (U001)"
	/*The USB mass storage device <devicename> is not using a supported file system or is having an invalid partition table.*/

#define LOG_ERRCODE_U002 " Der angeschlossene USB-Massenspeicher %s,%d kann leider nicht verwendet werden %s. (U002)"
	/*The attached USB mass storage device <devicename, port> is not working at all <reason>*/

#define LOG_ERRCODE_U003 " Auf dem angeschlossenen USB_Massenspeicher %s ist ein Hardware Schreibschutz aktiviert, daher kann das Medium nicht genutzt werden. Deaktivieren Sie bitte den Schreibschutz, falls Sie den USB-Massenspeicher mit lhrem Speedport benutzen wollen. (U003)"
    /*The connected USB mass storage <devicename> has an active hardware write-lock, hence the device can not be used. Please deactive the write-lock if you want to use the device with your speedport.*/

	
/*2.16 Messages regarding access to attached Mass-Storage*/
#define LOG_ERRCODE_F101 " Benutzerkonto %s wurde erfolgreich eingerichtet. (F101)"
	/*User account creation successful*/
#define LOG_ERRCODE_F102 " Benutzerkonto %s wurde bzgl. %s geändert. (F102)"
	/*Eigenschaft:	
		. Username
		. Passwort
		. Benutzergruppe
		. .
		"	"User profile successfully changed regarding <property>
	*/
#define LOG_ERRINFO_USERNAME "Username"
#define LOG_ERRINFO_USERPSW "Passwort"
#define LOG_ERRINFO_USER_GROUP "Benutzergruppe"
	
#define LOG_ERRCODE_F103 " Benutzerkonto %s wurde erfolgreich entsperrt (nach 60 Minuten-Sperre). (F103)"
	/*User access for reactivated (after60 min timeout expired)*/
#define LOG_ERRCODE_F104 " Benutzer %s, %s erfolgreich über %s angemeldet (F104)"
	/*User with IP-address successfully logged in with protocol <protocol>*/
#define LOG_ERRCODE_F105 " Lokaler Benutzer %s,%s erfolgreich abgemeldet (F105)"
	/*User with <username, IP-adresse> successfully logged out.*/	
#define LOG_ERRCODE_F106 " Benutzerkonto %s wurde erfolgreich gelöscht. (F106)"
	/*User successfully deleted.*/
#define LOG_ERRCODE_F107 " Hauptordner %s auf Gerät %s am Port %s wurde angelegt. (F107)"
	/*Port: USB, eSATA
		Top level folder  <foldername> created on device <devicename, port>
	*/
#define LOG_ERRCODE_F108 " Hauptordner %s auf Gerät %s am Port %s wurde gelöscht. (F108)"
	/*Port: USB, eSATA
		Top level folder  <foldername> deleted on device <devicename, port>
	*/
#define LOG_ERRCODE_F109 " Hauptordner %s auf Gerät %s am Port %s wurde umbenannt. (F109)"
	/*Port: USB, eSATA
		Top level folder  <foldername> renamed on device <devicename, port>
	*/
#define LOG_ERRCODE_F110 " Das angeschlossene Speichermedium %s ist zu 95%% voll (F110)"
	/* Storage device <devicename> 95% full */
#define LOG_ERRCODE_F111 " Das angeschlossene Speichermedium %s ist zu 100%% voll (F111)"
	/*Storage device <devicename> 100% full */
#define LOG_ERRCODE_F112 " Die Datei-Synch./Backup des Ordners %s auf dem Gerät %s am Port %s mit dem Ziel %s auf dem Gerät %s am Port %s wurde gestartet. (F112)"
	/*Sync/Backup job on device <devicename, port, folder> to device <devicename, port, folder> has been started.*/
#define LOG_ERRCODE_F113 " Die Datei-Synch./Backup des Ordners %s auf dem Gerät %s am Port %s mit dem Ziel %s auf dem Gerät %s am Port %s wurde erfolgreich beendet (F113)"
	/*Sync/Backup job on device <devicename, port> to device <devicename, port> successfully finished*/
#define LOG_ERRCODE_F114 " Die Datei-Synch./Backup des Ordners %s auf dem Gerät %s am Port %s mit dem Ziel %s auf dem Gerät %s am Port %s ist gescheitert %s. (F114)"
	/*Sync/Backup job on device <devicename, port> to device <devicename, port> has failed <reason>*/

#define LOG_ERRCODE_F001 " Benutzerkonto %s wurde nach mehr als 5 erfolglosen lokalen Anmeldeversuchen für 60 Minuten gesperrt. (F001)"
	/*Local user login failed after >5 unsuccessful attempts (account 'x' blocked for 60 minutes */
#define LOG_ERRCODE_F002 " Benutzerkonto %s wurde nach mehr als 5 erfolglosen externen Anmeldeversuchen für 60 Minuten gesperrt. (F002)"
	/*Remote user login failed after >5 unsuccessful attempts attempts (account 'x' blocked for 60 minutes) */
#define LOG_ERRCODE_F003 " Anmeldung des Benutzers %s, %s über %s nicht erfolgreich (%s). (F003)"
	/*User <username, IP-address> login failed with protocol*/
    /*
     * User login failed due to following <reason>:
        . Unknow user
        . Invalid password
        . Internal error
     * Protocol: SMB,FTP,sFTP
     */

	
/*2.17 Messages regarding additional services*/
/*2.17.1 Local FTP server*/	
#define LOG_ERRCODE_AS200 " Der lokale FTP-Server wurde gestartet. (AS200)"
	/*FTP server started*/
#define LOG_ERRCODE_AS201 " Der lokale FTP-Server wurde gestoppt. (AS201)"
	/*FTP server stopped*/
#define LOG_ERRCODE_AS202 " %s verwendete falsche ftp/ftps Zugangsdaten. (AS202)"
    /*User has entered incorrect ftp/ftps account credentials*/

	
/*2.17.2 Local SAMBA server*/	
#define LOG_ERRCODE_AS300 " Der lokale SMB/CIFS Dienst wurde gestartet. (AS300)"
	/*Smb/cifs started and running*/
#define LOG_ERRCODE_AS301 " Der lokale SMB/CIFS Dienst wurde gestoppt. (AS301)"
	/*Smb/cifs stopped*/

	
/*2.17.3 Local UPnP AV Mediaserver*/	
#define LOG_ERRCODE_AS400 " Der lokale Medienserver wurde gestartet. (AS400)"
	/*UPnP AV server started*/
#define LOG_ERRCODE_AS401 " Der lokale Medienserver wurde gestoppt. (AS401)"
    /*UPnP AV server stopped*/

	
/*2.19 Messages regarding the update mechanism	*/		
#define LOG_ERRCODE_UD101 " Der Update Vorgang wurde gestartet. (UD101)" 
	/*Update process has been started (UD101)*/
#define LOG_ERRCODE_UD102 " Der Update Vorgang auf Version %s war erfolgreich. (UD102)"
	/*Update to version <xxxxx> was successful.*/
#define LOG_ERRCODE_UD103 " Der Update Vorgang auf Version %s war nicht erfolgreich: %s (UD103)"
	/* Update to version <xxxxx> was not successful: <reason>
		<Fehlermeldung>
			Ungültiges Format
			Zeitüberschreitung
			Interner Fehler
			Datei-Transfer fehlgeschlagen
			Unvollständige Firmware-Datei
			Beschädigte Firmware-Datei
			Abbruch durch Notruf
	*/
#define LOG_ERRINFO_INVAILD_FORMAT "Ungültiges Format"
#define LOG_ERRINFO_TIMEOUT "Zeitüberschreitung"
#define LOG_ERRINFO_INTERNAL_ERR "Interner Fehler"
#define LOG_ERRINFO_TRANSFER_FAILED "Datei-Transfer fehlgeschlagen"
#define LOG_ERRINFO_INCOMPLETE_FILE "Unvollständige Firmware-Datei"
#define LOG_ERRINFO_CORRUPT_FILE "Beschädigte Firmware-Datei"
#define LOG_ERRINFO_CANCELLED_BY_EMERGENCY_CALL "Abbruch durch Notruf"
	
/*2.20 Messages regarding device startup*/	
#define LOG_ERRCODE_B101 " Das Gerät ist neu eingeschaltet worden. (B101)"
	/*Device is powered up (cold restart)*/
#define LOG_ERRCODE_B103 " Es wurde ein Reboot ausgelöst. (B103)"
	/*Reboot has been triggered by web-ui or device-button (if device button for reboot is applicable) on purpose.*/

/*2.21 Messages regarding general maintenance events*/
#define LOG_ERRCODE_M101 " Das Gerät wurde auf Werkseinstellungen zurückgesetzt. (M101)"
	/*The device has been reset to factory defaults.*/
#define LOG_ERRCODE_M102 " Der Zugang zum Internet wurde gesperrt. (M102)"
	/*Internet access has been disabled*/
#define LOG_ERRCODE_M103 " Der Zugang zum Internet wurde freigeschaltet. (M103)"
	/*Internet access has been enabled*/

/*2.22 Messages regarding the Web-UI*/
#define LOG_ERRCODE_G101 " %s Anmeldung erfolgreich. (G101)"
	/*User has successfully logged into web-ui*/
#define LOG_ERRCODE_G102 " %s Abmeldung erfolgreich. (G102)"
	/*User has logged out of the web-ui*/
#define LOG_ERRCODE_G103 " Konfigurator Sitzung abgelaufen. (G103)"
	/*Web-ui session has timed out*/
#define LOG_ERRCODE_G104 " UI Login Versuch von %s mit falschem Passwort. (G104)"
	/*User has entered incorrect password*/
	
/*2.23 Messages regarding TR-064*/	
#define LOG_ERRCODE_TR101 " %s TR-064 Sitzung gestartet. (TR101)"
	/*TR-064 session has been started from <ip-address>*/
#define LOG_ERRCODE_TR102 " %s TR-064 Sitzung beendet. (TR102)"
	/*TR-064 session has been closed by <ip-address>*/
	
/*2.25Messages regarding Telekom_FON*/	
#define LOG_ERRCODE_FO001 " Verbindung zum FON System (HB) wurde erfolgreich hergestellt // Hotspot Telekom_FON öffentlich nutzbar (FO001)"
	/*Valid Heartbeat Server response reached HG*/
#define LOG_ERRCODE_FO002 " Verbindung zum FON System (HB) wurde verloren. // Hotspot Telekom_FON öffentlich nicht nutzbar (FO002)"
	/*No Heartbeat Server Response for the defined number TR-069 Data model */
#define LOG_ERRCODE_FO003 " Der Hotspot Telekom_FON wurde aktiviert (FO003)"
	/*The device was activate for the possible broadcast of the public SSID Telekom_FON. This status is the basic status to start the check of parameters to bring the SSID online */
#define LOG_ERRCODE_FO004 " Der Hotspot Telekom_FON wurde deaktiviert (FO004)"
    /*The device was deactivate for the possible broadcast of the public SSID Telekom_FON.*/

/*2.26 Messages regarding Abuse*/
#define LOG_ERRCODE_E001 " Doppelter URL-Eintrag in `Liste der erlaubten E-Mail-Server' (E001)"
    /*duplicate entries of FQDN for `Liste der erlaubten E-Mail-Server'*/
#define LOG_ERRCODE_E002 " Doppelter Eintrag einer IP-Adresse in `Liste der erlaubten E-Mail-Server' (E002)"
    /*duplicate entries of IP-address for `Liste der erlaubten E-Mail-Server'*/
#define LOG_ERRCODE_E003 " Das Hinzufügen eines weiteren Eintrages %s war erfolgreich (E003)"
    /*Addition of the entry <FQDN or IP-Address> was successful*/
#define LOG_ERRCODE_E004 " Das löschen eines bestehenden Eintrages %s war erfolgreich (E004)"
    /*Deletion of the entry <FQDN or IP-Address> was successful*/
#define LOG_ERRCODE_E005 " Unerlaubter Verbindungsversuch laut `Liste der erlaubten E-Mail-Server' von %s nach %s (E005)"
    /*Session aborted due to `Liste der erlaubten E-Mail-Server' from <client-IP-address> to <destination FQDN or IP> */
#define LOG_ERRCODE_E006 " `Liste der erlaubten E-Mail-Server' wurde aktualisiert auf die Version %s (E006)"
    /*The Intial WA was updated to version <IWAVersion>*/
#define LOG_ERRCODE_E007 " Überprüfung der Aktualität der `Liste der erlaubten E-Mail-Server'. Es ist keine Aktualisierung notwendig. Die verwendete Liste %s ist aktuell. (E007)"
    /*No Update of the Initial WA list available or necessary*/

/*2.27 Messages regarding Online Address Book*/
#define LOG_ERRCODE_ZAB001 " Authentifizierung des Online-Adressbuchs: %s ist fehlgeschlagen. Request-Header-Element konnte nicht übermittelt werden. (ZAB001)"
    /*Registering of the online address book <name of the address book> was not successful. Request-Header-Element is missing.*/
#define LOG_ERRCODE_ZAB002 " Anmeldung des Online-Adressbuchs %s ist fehlgeschlagen. Benutzername oder Passwort ist nicht korrekt. (ZAB002)"
    /*Login to online address book <name of the address book> was not successful. Username and/or password is incorrect.*/
#define LOG_ERRCODE_ZAB003 " Anmeldung des Online-Adressbuchs mit den verwendeten Zugangsdaten für Telefonbuch: %s nicht möglich. Keine Berechtigung. (ZAB003)"
    /*Login to online address book <name of address book> was not successful. User has no permission to use the service.*/
#define LOG_ERRCODE_ZAB004 " Verbindung zum Online-Adressbuch konnte nicht aufgebaut werden. Server nicht erreichbar. (ZAB004)"
    /*Connection to online address book could not be established. Server is not available.*/
#define LOG_ERRCODE_ZAB005 " Verbindung zum zentralen Adressbuch: %s wurde erfolgreich aufgebaut. (ZAB005)"
    /*Connection to online address book: <name of address book> successfully established.*/
#define LOG_ERRCODE_ZAB006 " Max. Anzahl an Kontakten erreicht. Es konnten nicht alle Kontakte synchronisiert werden. (%s) (ZAB006)"
    /*Syncronization of contact data not completed. Unable to snycronize all contact data of the central address book. Reason; too many contacts. <name of the address book>*/
#define LOG_ERRCODE_ZAB007 " Die Synchronisation von %s Kontaktdaten in: %s war erfolgreich. (ZAB007)"
    /*Syncronization of < XXXX> contact data in <name of address book> was successfull.*/
#define LOG_ERRCODE_ZAB008 " Verbindung zum zentralen Adressbuch: %s wurde getrennt. (ZAB008)"
    /*Connection to central adress book was interrupted.*/
#define LOG_ERRCODE_ZAB009 " Anzahl der Telefonbücher wurde erfolgreich auf %s geändert. (ZAB009)"
    /*Number of address books was changed by user to <1|3|5>.*/


/*2.28 Messages regarding Ethernet OAM*/
#define LOG_ERRCODE_OAM001 " OAM Modus wurde eingeschaltet. (OAM001)"
    /*The device has entered the OAM state*/
#define LOG_ERRCODE_OAM002 " OAM Modus wurde beendet. (OAM002)"
    /*The device left the OAM state*/
#define LOG_ERRCODE_OAM003 " OAM remote loopback wurde gestartet. (OAM003)"
    /*OAM remote loopback initiated*/
#define LOG_ERRCODE_OAM004 " OAM remote loopback wurde beendet. (OAM004)"
    /*OAM remote loopback exited*/
#define LOG_ERRCODE_OAM101 " OAM Link fault. (OAM101)"
    /*The PHY has determined a fault has occurred in the receive direction of the local DTE*/
#define LOG_ERRCODE_OAM102 " OAM Dying gasp. (OAM102)"
    /*An unrecoverable local failure condition has occurred*/
#define LOG_ERRCODE_OAM103 " OAM Critical event. (OAM103)"
    /*An unspecified critical event has occurred*/


/*2.29 Messages First Call Initiation(if applicable)*/
#define LOG_ERRCODE_FCI001 " Die Funktion zur Migrationsunterstützung des Telefonie-Service wurde gestartet. (FCI001)"
        /*First Call Initiation functionality is started*/
#define LOG_ERRCODE_FCI002 " Die Funktion zur Migrationsunterstützung des Telefonie-Service wurde erfolgreich beendet. (FCI002)"
        /*The conduction of the First Call Initiation functionality is successfully completed.*/
#define LOG_ERRCODE_FCI003 " Die Funktion zur Migrationsunterstützung des Telefonie-Service konnte nicht erfolgreich ausgeführt werden. (FCI003)"
        /*The conduction of the First Call Initiation functionality failed because the establishment of an outgoing call to a predefined number failed.*/
#define LOG_ERRCODE_FCI004 " Die Funktion zur Migrationsunterstützung des Telefonie-Service konnte nicht erfolgreich ausgeführt werden. (FCI004)"
        /*The conduction of the First Call Initiation functionality failed because the established outgoing call to a predefined number is terminated with a call duration less than 5.0 seconds.*/
#define LOG_ERRCODE_FCI005 " Die Funktion zur Migrationsunterstützung des Telefonie-Service konnte nicht erfolgreich ausgeführt werden. (FCI005)"
        /*In case the First Call Initiation functionality was not successful after completeing the number of defined retries the First Call Initiation functionality is finally considered as failed*/
#define LOG_ERRCODE_FCI006 " Die Funktion zur Migrationsunterstützung des Telefonie-Service wurde deaktiviert. (FCI006)"
        /*The First Call Initiation functionality is deactived until next reset to manufacturing default*/
	

/*3.1 Messages regarding WAN Interface IPv6*/
#define LOG_ERRCODE_P001 " Vom Internetanbieter zugewiesene WAN IPv6-Adresse: %s (P001)"
	/*From internet service provider transferred WAN IPv6 address <IPv6-address>*/
#define LOG_ERRCODE_P002 " Vom Internetanbieter zugewiesene Gateway-IPv6-Adresse: %s (P002)"
	/*From internet service provider transferred Gateway IPv6 address: <IPv6-address>*/
#define LOG_ERRCODE_P003 " IPv6 Anmeldung beim Internetanbieter ist mit den verwendeten Zugangsdaten nicht möglich: IPv6: %s (P003)"
	/*IPv6 Login failed due to the message provided by radius server*/
#define LOG_ERRCODE_P004 " IPv6 Anmeldung beim Internetanbieter ist fehlgeschlagen. (P004)"
	/*IPv6 Login failed.*/
#define LOG_ERRCODE_P005 " Einwahl Router hat Präfix %s von ISP zugewiesen bekommen. (P005)"
	/*IPv6 connection could be established. IPv6 Prefix received */
#define LOG_ERRCODE_P006 " Router hat kein Präfix von ISP erhalten. Fehler: %s (P006)"
	/*IPv6 connection could be established. IPv6 Prefix not received*/
#define LOG_ERRCODE_P007 " DNSv6 Server %s wurden erfolgreich aktualisiert (P007)"
	/*Router configures DNSv6 Server Address */
#define LOG_ERRCODE_P008 " DNSv6-Ereignis: Der DNSv6 Server %s meldet ein Ereignis: %s (P008)"
    /*DNSv6-event: The DNSv6 Server <DNSv6 Server> replies <reply code>.*/

	
	
/*3.2 Messages regarding IPv6 LAN*/		
#define LOG_ERRCODE_ME104 " Router sendet Präfix %s ins LAN (ME104)"
	/*IPv6 Address sent to LAN */

	
/*3.3 Messages regarding external IPv6 NTP*/
#define LOG_ERRCODE_NT101 " Die IPv6 Systemzeit wurde erfolgreich aktualisiert (NT101)"
	/*Time Server v6 successfully connected and time synchronisation achieved.*/
#define LOG_ERRCODE_NT102 " Die IPv6 Systemzeit konnte nicht aktualisiert werden. (NT102)"
	/*Time Server v6 connected but Server responded with Error.*/
#define LOG_ERRCODE_NT103 " Keine Antwort vom IPv6 Timeserver. (NT103)"
	/*No Time Servers v6 reachable.*/

	
/*3.4 Messages regarding internal DHCPv6*/
#define LOG_ERRCODE_DH101 " DHCP ist aktiv: %s %s  (DH101)"
	/*DHCPv6 server is active:<date> <time> <mini-DNSv6- server>*/

	
#endif /*__LOG_FORCOE_de_H__*/

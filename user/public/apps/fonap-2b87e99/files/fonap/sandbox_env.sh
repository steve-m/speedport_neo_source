#! /bin/sh

# 
# FON Keys
#
# VD168 W724V FON Keys
#00-C0-02-12-35-88	262fd0f32a8e118c21b745d85bc76b4efb89671f21dd18c1df1c62477ca95a87
#00-C0-02-FF-BE-BC	efff85a1a7bdced2348220a5de2074d7b3a1b9e999e7abfa297b164a3b1bcb1e
#00-C0-02-FF-BE-BD	817af7aca1c8b398da2becf362485a80ad2ae52d5552f3f6cff0141151835b3e
#00-C0-02-FF-BE-BE	9aaad72c5cef47313b138f63ca83293ca77a483926a680a6a41a277e7d50c43b
#00-C0-02-FF-BE-BF	7ec5c011621d33f2d0e6a0ef87b62d926ae67cfaaa08b97c27ecf2a037ad06ee
#00-C0-02-12-35-A0      47313b138f1d33f2d0e6a0ef87b62d90c43bcfaaa08b97c27ecf2a037ad06ee4 
#00-C0-02-12-35-B0      313b138fa1c8b398da2b8f63ca83293ca72ae52d5552f3f6cff0147e7d50c43b
#
# F1 NEO FON Keys
#00-C0-02-BE-FA-80	39d203ed6d9f9a645c9e4ad8e0d04918fb9099881c52003e23c58c5058d76312
#00-C0-02-BE-FA-90	d153a3d46d84ce02bfdc61e970f2da57206fc9f5f51fde6222d7807a81ad62d3
#00-C0-02-BE-FA-A0	361acc5c2d3411c228578214db0c4399b8e0e08c5d0f14a62e7ad485c62647ac
#00-C0-02-BE-FA-B0	d539c23ed880679047f04ac02e5a89fee12ef5c943850bbfa3c424bcd72aecfd

#
# srcdta01: VD168(W724V)
# srcdta02: F1(NEO)
#

/usr/sbin/cmld_client set Device.ManagementServer.EnableCWMP=1
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.Enable=1
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.Key=361acc5c2d3411c228578214db0c4399b8e0e08c5d0f14a62e7ad485c62647ac
#/usr/sbin/cmld_client set Device.WiFi.Radio.1.Enable=1
#/usr/sbin/cmld_client set Device.WiFi.Radio.2.Enable=1
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.RadiusServer1=a.srcdta02.rc.sandbox.fon.com
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.RadiusServer2=b.srcdta02.rc.sandbox.fon.com
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.RadiusSecret=secret
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.Host=a.srcdta02.hb.sandbox.fon.com
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.LNSServer1=a.srcdta02.lns.sandbox.fon.com
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.LNSServer2=b.srcdta02.lns.sandbox.fon.com
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.Uamsecret=garrafon
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.PeriodOnline=60
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.PeriodOffline=60
/usr/sbin/cmld_client set Device.Services.X_T-ONLINE-DE_Fon.SSID=FON_FAA0

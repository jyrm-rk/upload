<?xml version="1.0"?>
<!--
  ~
  ~   Copyright (c) 1999 - 2011 my-Channels Ltd
  ~   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
  ~
  ~   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
  ~
  -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html"/>

  <xsl:template match="/">
    <html>
      <head>
        <title>my-channels.com - Technologies Working Together</title>
        <LINK REL="SHORTCUT ICON" HREF="/images/icons/favicon.ico"/>
        <link href="/style/my-channels.css" rel="stylesheet" type="text/css"/>
        <meta name="keywords"
          content="Middleware Java peer to peer C++ EAI MOM XML JMS Benchmarking Linux Windows WIN32 fastest JMS Examples JMS vendors"/>
        <meta name="description"
          content="Nirvana and Matrix are products provided by my-channels. see http://www.my-channels.com/ for more information."/>
        <meta name="keywords" content="middleware eai MOM message oriented java"/>
        <meta http-equiv="refresh" content="30"/>
      </head>
      <body bgcolor="#FFFFFF" text="#666699" leftmargin="0" topmargin="0" marginwidth="0"
        marginheight="0" link="#990000" vlink="#003399" alink="#666699">
        <table width="100%" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="176" bordercolor="#ffffff" bgcolor="#FFFFFF">
              <a href="http://www.my-channels.com/index.html">
                <img src="http://www.my-channels.com//images/logo/logo.jpg" alt="Home"
                  name="logo_image" width="176" height="45" border="0" align="left"
                  id="logo_image"/>
              </a>
            </td>
            <td width="315">
              <a href="http://www.my-channels.com/index.html">
                <img src="http://www.my-channels.com/images/banners/technologiesworking.jpg"
                  alt="Technology working together" name="banner_image" width="720" height="45"
                  border="0" id="banner_image"/>
              </a>
            </td>
            <td width="420" background="/images/backgrounds/header_back-new-flattened.png"></td>
            <td width="*"
              background="http://www.my-channels.com/images/backgrounds/header_back-new-flattened.png"></td>
          </tr>
        </table>
        <p></p>

        <xsl:apply-templates/>

        <table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td align="left" valign="top">
              <table width="100%" border="0" cellpadding="0" cellspacing="0">
                <tr>
                  <td width="896" bordercolor="#ffffff" bgcolor="#FFFFFF">
                    <img src="http://www.my-channels.com/images/backgrounds/basebar.jpg" width="896"
                      height="27"/>
                  </td>
                  <td width="420"
                    background="http://www.my-channels.com/images/backgrounds/bottom_header.gif"></td>
                  <td width="*"
                    background="http://www.my-channels.com/images/backgrounds/bottom_header.gif"></td>
                </tr>
              </table>
            </td>
          </tr>
          <tr>
            <td align="left" valign="top" bgcolor="#CCCCCC" colspan="2">
              <div align="center">
                <font face="Verdana, Arial, Helvetica, sans-serif" size="-2">
                  <xsl:text disable-output-escaping="yes">2001-2008 my-channels.com.</xsl:text>
                  <a href="http://www.my-channels.com/terms-of-use.htm">(Terms of use)</a>
                </font>
              </div>
            </td>
          </tr>
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="Nirvana-RealmServer-ChannelList">
    <xsl:apply-templates select="RealmStatus"/>
    <H3>Channel Listing</H3>
    <div align="center">
      <table width="80%" border="1">
        <tr>
          <td>Channel Name</td>
          <td>Number of Events</td>
          <td>Last Event Id</td>
        </tr>
        <xsl:apply-templates select="Channel">
          <xsl:sort select="@Name"/>
        </xsl:apply-templates>
      </table>
    </div>
  </xsl:template>

  <xsl:template match="Channel">
    <tr>
      <td>
        <a href="{@fqn}">
          <xsl:value-of select="@Name"/>
        </a>
      </td>
      <td>
        <xsl:value-of select="@NumberEvents"/>
      </td>
      <td>
        <xsl:value-of select="@LastEventID"/>
      </td>
    </tr>
  </xsl:template>


  <xsl:template match="Nirvana-RealmServer-EventList">
    <H3>Event Listing</H3>
    <div align="center">
      <table width="80%" border="1">
        <tr>
          <td>EId</td>
          <td>Size</td>
          <td>Data</td>
        </tr>
        <xsl:apply-templates select="Event"/>
      </table>
    </div>
    <xsl:apply-templates select="Details"/>
  </xsl:template>

  <xsl:template match="Event">
    <tr>
      <td>
        <xsl:value-of select="@EID"/>
      </td>
      <td>
        <xsl:value-of select="@DataSize"/>
      </td>
      <td>
        <xsl:if test="@ByteLink">
          <a href="{@ByteLink}">Data</a>
          <xsl:text>  </xsl:text>
        </xsl:if>
        <xsl:if test="@DictionaryLink">
          <a href="{@DictionaryLink}">Dictionary</a>
          <xsl:text>  </xsl:text>
        </xsl:if>
        <xsl:if test="@XMLLink">
          <a href="{@XMLLink}">XML</a>
          <xsl:text>  </xsl:text>
        </xsl:if>
      </td>
    </tr>
  </xsl:template>

  <xsl:template match="Details">
    <div align="center">
      <table width="80%" border="0">
        <td>
          <a href="{@NextLink}">Next</a>
        </td>
        <td>
          <a href="{@FirstEvent}">First</a>
        </td>
        <td>
          <a href="{@LastEvent}">Last</a>
        </td>
      </table>
    </div>
  </xsl:template>

  <xsl:template match="Nirvana-RealmServer-Dictionary">
    <H3>Dictionary Listing</H3>
    <div align="center">
      <table width="80%" border="1">
        <tr>
          <td>Key</td>
          <td>Value</td>
        </tr>
        <xsl:apply-templates select="DictionaryData"/>
      </table>
    </div>
  </xsl:template>

  <xsl:template match="DictionaryData">
    <xsl:apply-templates select="Dictionary"/>
  </xsl:template>

  <xsl:template match="Dictionary">
    <xsl:apply-templates select="Data"/>
  </xsl:template>

  <xsl:template match="Data">
    <tr>
      <td>
        <xsl:value-of select="@Key"/>
      </td>
      <td>
        <xsl:value-of select="@Value"/>
      </td>
    </tr>
  </xsl:template>

  <xsl:template match="EventData">
    <H3>Event Data Table</H3>
    <div align="center">
      <table width="80%" border="1">
        <tr>
          <td>Eid</td>
          <td>Event Data</td>
        </tr>
        <tr>
          <td>
            <xsl:value-of select="@EID"/>
          </td>
          <td>
            <xsl:value-of select="@Data"/>
          </td>
        </tr>
      </table>
    </div>
  </xsl:template>

  <xsl:template match="RealmStatus">
    <H3>Realm Status for
      <xsl:value-of select="@RealmName"/>
    </H3>
    <div align="center">
      <table width="80%" border="1">
        <tr>
          <td>Total Memory</td>
          <td>
            <xsl:value-of select="@TotalMemory"/>
          </td>
        </tr>
        <tr>
          <td>Free Memory</td>
          <td>
            <xsl:value-of select="@FreeMemory"/>
          </td>
        </tr>
        <tr>
          <td>Current Threads</td>
          <td>
            <xsl:value-of select="@Threads"/>
          </td>
        </tr>
        <tr>
          <td>Total Connections</td>
          <td>
            <xsl:value-of select="@TotalConnections"/>
          </td>
        </tr>
        <tr>
          <td>Events Published</td>
          <td>
            <xsl:value-of select="@TotalPublished"/>
          </td>
        </tr>
        <tr>
          <td>Events Consumed</td>
          <td>
            <xsl:value-of select="@TotalConsumed"/>
          </td>
        </tr>
      </table>
    </div>
  </xsl:template>

</xsl:stylesheet>


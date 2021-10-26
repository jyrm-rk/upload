<?xml version="1.0"?>
<!--
  ~
  ~   Copyright (c) 1999 - 2011 my-Channels Ltd
  ~   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
  ~
  ~   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
  ~
  -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:output method="wml" indent="yes" encoding="UTF-8"/>
  <xsl:output doctype-system="http://www.wapforum.org/DTD/wml13.dtd"
    doctype-public="-//WAPFORUM//DTD WML 1.3//EN"/>


  <xsl:template match="Nirvana-RealmServer-ChannelList">
    <wml>
      <head>
        <meta forua="true" http-equiv="Pragma" content="no-cache"/>
        <meta forua="true" http-equiv="Cache-Control" content="no-cache, must-revalidate"/>
      </head>
      <card id="ChannelList" title="ChannelList">
        <p>
          <table columns="1" title="Event Data" align="C">
            <xsl:apply-templates/>
          </table>
        </p>
      </card>
    </wml>
  </xsl:template>

  <xsl:template match="Channel">
    <tr>
      <td>
        <a href="{@fqn}">
          <xsl:value-of select="@Name"/>
        </a>
      </td>
    </tr>
    <xsl:apply-templates select="Channel"/>
  </xsl:template>

  <xsl:template match="Nirvana-RealmServer-EventList">
    <wml>
      <head>
        <meta forua="true" http-equiv="Pragma" content="no-cache"/>
        <meta forua="true" http-equiv="Cache-Control" content="no-cache, must-revalidate"/>
      </head>
      <card id="EventList" title="Event List">
        <p>
          <table columns="1" title="Event Data" align="C">
            <xsl:apply-templates select="Event"/>
          </table>
        </p>
      </card>
    </wml>
  </xsl:template>

  <xsl:template match="Event">
    <tr>
      <td>
        <a href="{@ByteLink}">Event Id :
          <xsl:value-of select="@ID"/>
        </a>
      </td>
    </tr>
  </xsl:template>


  <xsl:template match="Nirvana-RealmServer-Dictionary">
    <wml>
      <head>
        <meta forua="true" http-equiv="Pragma" content="no-cache"/>
        <meta forua="true" http-equiv="Cache-Control" content="no-cache, must-revalidate"/>
      </head>
      <card id="Dictionary">
        <p>
          <table columns="2" title="Dictionary" align="C">
            <tr>
              <td>Key</td>
              <td>Value</td>
            </tr>
            <xsl:apply-templates select="DictionaryData"/>
          </table>
        </p>
      </card>
    </wml>
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


  <xsl:template match="Nirvana-RealmServer-Status">
    <wml>
      <head>
        <meta forua="true" http-equiv="Pragma" content="no-cache"/>
        <meta forua="true" http-equiv="Cache-Control" content="no-cache, must-revalidate"/>
      </head>
      <card id="Status">
        <xsl:apply-templates select="RealmStatus"/>
      </card>
    </wml>
  </xsl:template>

  <xsl:template match="RealmStatus">
    <xsl:value-of select="@RealmName"/>
    <p>
      <table columns="1" title="Realm Status" align="C">
        <tr>
          <td>Total
            <xsl:value-of select="@TotalMemory"/>
          </td>
        </tr>
        <tr>
          <td>Free
            <xsl:value-of select="@FreeMemory"/>
          </td>
        </tr>
        <tr>
          <td>Threads
            <xsl:value-of select="@Threads"/>
          </td>
        </tr>
        <tr>
          <td>Connections
            <xsl:value-of select="@TotalConnections"/>
          </td>
        </tr>
        <tr>
          <td>Published
            <xsl:value-of select="@TotalPublished"/>
          </td>
        </tr>
        <tr>
          <td>Consumed
            <xsl:value-of select="@TotalConsumed"/>
          </td>
        </tr>
      </table>
    </p>
  </xsl:template>

</xsl:stylesheet>


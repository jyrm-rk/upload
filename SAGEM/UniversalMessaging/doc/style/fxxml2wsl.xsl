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
      <card id="Currencies" title="Currencies">
        <p>
          <table columns="1" title="Event Data" align="C">
            <xsl:apply-templates select="Channel">
              <xsl:sort select="@Name"/>
            </xsl:apply-templates>
          </table>
        </p>
      </card>
    </wml>
  </xsl:template>


  <xsl:template match="Channel">
    <tr>
      <td>
        <a href="{@fqn}?Data=Dictionary">
          <xsl:value-of select="@Name"/>
        </a>
      </td>
    </tr>
    <xsl:apply-templates select="Channel"/>
  </xsl:template>

  <xsl:template match="Nirvana-RealmServer-Dictionary">
    <wml>
      <head>
        <meta forua="true" http-equiv="Pragma" content="no-cache"/>
        <meta forua="true" http-equiv="Cache-Control" content="no-cache, must-revalidate"/>
      </head>
      <card id="Dictionary">
        <p>
          <table columns="1" title="Data" align="C">
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
    <xsl:if test="@Key = 'CCY' ">
      <tr>
        <td>
          <xsl:text>Currency </xsl:text><xsl:value-of select="@Value"/>
        </td>
      </tr>
    </xsl:if>
    <xsl:if test="@Key = 'Bid' ">
      <tr>
        <td>
          <xsl:text>Bid </xsl:text><xsl:value-of select="@Value"/>
        </td>
      </tr>
    </xsl:if>
    <xsl:if test="@Key = 'Offer' ">
      <tr>
        <td>
          <xsl:text>Offer </xsl:text><xsl:value-of select="@Value"/>
        </td>
      </tr>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>


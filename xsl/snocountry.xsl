<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
  <h2>Report For: <xsl:value-of select="skidata/resortName"/></h2>
  <table border="1">
    <tr bgcolor="#e3e3e3"><td>rid</td><td><xsl:value-of select="skidata/rid"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Date</td><td><xsl:value-of select="skidata/reportDateTime"/></td></tr>
    <tr bgcolor="#e3e3e3"><td>Status</td><td><xsl:value-of select="skidata/operatingStatus"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Type</td><td><xsl:value-of select="skidata/resortType"/></td></tr>
    <tr bgcolor="#e3e3e3"><td>New Snow Min</td><td><xsl:value-of select="skidata/newSnowMin"/>"</td></tr>
    <tr bgcolor="#c6c6c6"><td>New Snow Max</td><td><xsl:value-of select="skidata/newSnowMax"/>"</td></tr>
    <tr bgcolor="#e3e3e3"><td>Primary Surface Condition</td><td><xsl:value-of select="skidata/primarySurfaceCondition"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Ave. Base Min</td><td><xsl:value-of select="skidata/avgBaseDepthMin"/>"</td></tr>
    <tr bgcolor="#e3e3e3"><td>Ave. Base Max</td><td><xsl:value-of select="skidata/avgBaseDepthMin"/>"</td></tr>
    <tr bgcolor="#c6c6c6"><td>Open Trials</td><td><xsl:value-of select="skidata/openDownHillTrails"/></td></tr>
    <tr bgcolor="#e3e3e3"><td>Open Lifts</td><td><xsl:value-of select="skidata/openDownHillLifts"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Open Miles</td><td><xsl:value-of select="skidata/openDownHillMiles"/></td></tr>
    <tr bgcolor="#e3e3e3"><td>Open Acres</td><td><xsl:value-of select="skidata/openDownHillAcres"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Open Percent</td><td><xsl:value-of select="skidata/openDownHillPercent"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Night Skiing</td><td><xsl:value-of select="skidata/nightSkiing"/></td></tr>
    <tr bgcolor="#c6c6c6"><td>Weekend Hours</td><td><xsl:value-of select="skidata/weekendHours"/></td></tr>     
    <tr bgcolor="#c6c6c6"><td>Weekday Hours</td><td><xsl:value-of select="skidata/weekdayHours"/></td></tr>    
    <tr bgcolor="#c6c6c6"><td>Comments</td><td><xsl:value-of select="skidata/snowComments"/></td></tr>
		<tr bgcolor="#c6c6c6"><td>Secondary Surface Condition</td><td><xsl:value-of select="skidata/secondarySurfaceCondition"/></td></tr>
		<tr bgcolor="#c6c6c6"><td>Parks and Pipes</td><td><xsl:value-of select="skidata/parksNPipes"/></td></tr>     
    <tr bgcolor="#c6c6c6"><td>Report Logged TS</td><td><xsl:value-of select="skidata/ts"/></td></tr>     
    
		<xsl:for-each select="skidata/cumulativesnowfall/daily">
    <tr><td>Snow Fall</td><td><xsl:value-of select="min"/><xsl:value-of select="max"/></td></tr>
    </xsl:for-each>
  </table>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>
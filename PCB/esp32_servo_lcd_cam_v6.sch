<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.7.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="LAYER_100" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="Undefined" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Resistor" urn="urn:adsk.eagle:library:16378527">
<description>&lt;B&gt;Resistors, Potentiometers, TrimPot</description>
<packages>
<package name="RESC1005X40" urn="urn:adsk.eagle:footprint:16378540/5" library_version="20">
<description>Chip, 1.05 X 0.54 X 0.40 mm body
&lt;p&gt;Chip package with body size 1.05 X 0.54 X 0.40 mm&lt;/p&gt;</description>
<wire x1="0.55" y1="0.636" x2="-0.55" y2="0.636" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.636" x2="-0.55" y2="-0.636" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.3" x2="-0.55" y2="-0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="-0.3" x2="-0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="0.3" x2="0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="0.55" y1="0.3" x2="0.55" y2="-0.3" width="0.12" layer="51"/>
<smd name="1" x="-0.5075" y="0" dx="0.5351" dy="0.644" layer="1"/>
<smd name="2" x="0.5075" y="0" dx="0.5351" dy="0.644" layer="1"/>
<text x="0" y="1.271" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.271" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC1608X60" urn="urn:adsk.eagle:footprint:16378537/5" library_version="20">
<description>Chip, 1.60 X 0.82 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.82 X 0.60 mm&lt;/p&gt;</description>
<wire x1="0.85" y1="0.8009" x2="-0.85" y2="0.8009" width="0.127" layer="21"/>
<wire x1="0.85" y1="-0.8009" x2="-0.85" y2="-0.8009" width="0.127" layer="21"/>
<wire x1="0.85" y1="-0.475" x2="-0.85" y2="-0.475" width="0.12" layer="51"/>
<wire x1="-0.85" y1="-0.475" x2="-0.85" y2="0.475" width="0.12" layer="51"/>
<wire x1="-0.85" y1="0.475" x2="0.85" y2="0.475" width="0.12" layer="51"/>
<wire x1="0.85" y1="0.475" x2="0.85" y2="-0.475" width="0.12" layer="51"/>
<smd name="1" x="-0.8152" y="0" dx="0.7987" dy="0.9739" layer="1"/>
<smd name="2" x="0.8152" y="0" dx="0.7987" dy="0.9739" layer="1"/>
<text x="0" y="1.4359" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.4359" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC2012X65" urn="urn:adsk.eagle:footprint:16378532/5" library_version="20">
<description>Chip, 2.00 X 1.25 X 0.65 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 0.65 mm&lt;/p&gt;</description>
<wire x1="1.075" y1="1.0241" x2="-1.075" y2="1.0241" width="0.127" layer="21"/>
<wire x1="1.075" y1="-1.0241" x2="-1.075" y2="-1.0241" width="0.127" layer="21"/>
<wire x1="1.075" y1="-0.7" x2="-1.075" y2="-0.7" width="0.12" layer="51"/>
<wire x1="-1.075" y1="-0.7" x2="-1.075" y2="0.7" width="0.12" layer="51"/>
<wire x1="-1.075" y1="0.7" x2="1.075" y2="0.7" width="0.12" layer="51"/>
<wire x1="1.075" y1="0.7" x2="1.075" y2="-0.7" width="0.12" layer="51"/>
<smd name="1" x="-0.9195" y="0" dx="1.0312" dy="1.4202" layer="1"/>
<smd name="2" x="0.9195" y="0" dx="1.0312" dy="1.4202" layer="1"/>
<text x="0" y="1.6591" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.6591" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC3216X70" urn="urn:adsk.eagle:footprint:16378539/5" library_version="20">
<description>Chip, 3.20 X 1.60 X 0.70 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 0.70 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.2217" x2="-1.7" y2="1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-1.2217" x2="-1.7" y2="-1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<text x="0" y="1.8567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC3224X71" urn="urn:adsk.eagle:footprint:16378536/5" library_version="20">
<description>Chip, 3.20 X 2.49 X 0.71 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.49 X 0.71 mm&lt;/p&gt;</description>
<wire x1="1.675" y1="1.6441" x2="-1.675" y2="1.6441" width="0.127" layer="21"/>
<wire x1="1.675" y1="-1.6441" x2="-1.675" y2="-1.6441" width="0.127" layer="21"/>
<wire x1="1.675" y1="-1.32" x2="-1.675" y2="-1.32" width="0.12" layer="51"/>
<wire x1="-1.675" y1="-1.32" x2="-1.675" y2="1.32" width="0.12" layer="51"/>
<wire x1="-1.675" y1="1.32" x2="1.675" y2="1.32" width="0.12" layer="51"/>
<wire x1="1.675" y1="1.32" x2="1.675" y2="-1.32" width="0.12" layer="51"/>
<smd name="1" x="-1.4695" y="0" dx="1.1312" dy="2.6602" layer="1"/>
<smd name="2" x="1.4695" y="0" dx="1.1312" dy="2.6602" layer="1"/>
<text x="0" y="2.2791" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2791" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC5025X71" urn="urn:adsk.eagle:footprint:16378538/5" library_version="20">
<description>Chip, 5.00 X 2.50 X 0.71 mm body
&lt;p&gt;Chip package with body size 5.00 X 2.50 X 0.71 mm&lt;/p&gt;</description>
<wire x1="2.575" y1="1.6491" x2="-2.575" y2="1.6491" width="0.127" layer="21"/>
<wire x1="2.575" y1="-1.6491" x2="-2.575" y2="-1.6491" width="0.127" layer="21"/>
<wire x1="2.575" y1="-1.325" x2="-2.575" y2="-1.325" width="0.12" layer="51"/>
<wire x1="-2.575" y1="-1.325" x2="-2.575" y2="1.325" width="0.12" layer="51"/>
<wire x1="-2.575" y1="1.325" x2="2.575" y2="1.325" width="0.12" layer="51"/>
<wire x1="2.575" y1="1.325" x2="2.575" y2="-1.325" width="0.12" layer="51"/>
<smd name="1" x="-2.3195" y="0" dx="1.2312" dy="2.6702" layer="1"/>
<smd name="2" x="2.3195" y="0" dx="1.2312" dy="2.6702" layer="1"/>
<text x="0" y="2.2841" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2841" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC6332X71" urn="urn:adsk.eagle:footprint:16378533/5" library_version="20">
<description>Chip, 6.30 X 3.20 X 0.71 mm body
&lt;p&gt;Chip package with body size 6.30 X 3.20 X 0.71 mm&lt;/p&gt;</description>
<wire x1="3.225" y1="1.9991" x2="-3.225" y2="1.9991" width="0.127" layer="21"/>
<wire x1="3.225" y1="-1.9991" x2="-3.225" y2="-1.9991" width="0.127" layer="21"/>
<wire x1="3.225" y1="-1.675" x2="-3.225" y2="-1.675" width="0.12" layer="51"/>
<wire x1="-3.225" y1="-1.675" x2="-3.225" y2="1.675" width="0.12" layer="51"/>
<wire x1="-3.225" y1="1.675" x2="3.225" y2="1.675" width="0.12" layer="51"/>
<wire x1="3.225" y1="1.675" x2="3.225" y2="-1.675" width="0.12" layer="51"/>
<smd name="1" x="-2.9695" y="0" dx="1.2312" dy="3.3702" layer="1"/>
<smd name="2" x="2.9695" y="0" dx="1.2312" dy="3.3702" layer="1"/>
<text x="0" y="2.6341" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.6341" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESAD1176W63L850D250B" urn="urn:adsk.eagle:footprint:16378542/5" library_version="20">
<description>AXIAL Resistor, 11.76 mm pitch, 8.5 mm body length, 2.5 mm body diameter
&lt;p&gt;AXIAL Resistor package with 11.76 mm pitch, 0.63 mm lead diameter, 8.5 mm body length and 2.5 mm body diameter&lt;/p&gt;</description>
<wire x1="-4.25" y1="1.25" x2="-4.25" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-4.25" y1="-1.25" x2="4.25" y2="-1.25" width="0.127" layer="21"/>
<wire x1="4.25" y1="-1.25" x2="4.25" y2="1.25" width="0.127" layer="21"/>
<wire x1="4.25" y1="1.25" x2="-4.25" y2="1.25" width="0.127" layer="21"/>
<wire x1="-4.25" y1="0" x2="-4.911" y2="0" width="0.127" layer="21"/>
<wire x1="4.25" y1="0" x2="4.911" y2="0" width="0.127" layer="21"/>
<wire x1="4.25" y1="-1.25" x2="-4.25" y2="-1.25" width="0.12" layer="51"/>
<wire x1="-4.25" y1="-1.25" x2="-4.25" y2="1.25" width="0.12" layer="51"/>
<wire x1="-4.25" y1="1.25" x2="4.25" y2="1.25" width="0.12" layer="51"/>
<wire x1="4.25" y1="1.25" x2="4.25" y2="-1.25" width="0.12" layer="51"/>
<pad name="1" x="-5.88" y="0" drill="0.83" diameter="1.43"/>
<pad name="2" x="5.88" y="0" drill="0.83" diameter="1.43"/>
<text x="0" y="1.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF3515" urn="urn:adsk.eagle:footprint:16378534/5" library_version="20">
<description>MELF, 3.50 mm length, 1.52 mm diameter
&lt;p&gt;MELF Resistor package with 3.50 mm length and 1.52 mm diameter&lt;/p&gt;</description>
<wire x1="1.105" y1="1.1825" x2="-1.105" y2="1.1825" width="0.127" layer="21"/>
<wire x1="-1.105" y1="-1.1825" x2="1.105" y2="-1.1825" width="0.127" layer="21"/>
<wire x1="1.85" y1="-0.8" x2="-1.85" y2="-0.8" width="0.12" layer="51"/>
<wire x1="-1.85" y1="-0.8" x2="-1.85" y2="0.8" width="0.12" layer="51"/>
<wire x1="-1.85" y1="0.8" x2="1.85" y2="0.8" width="0.12" layer="51"/>
<wire x1="1.85" y1="0.8" x2="1.85" y2="-0.8" width="0.12" layer="51"/>
<smd name="1" x="-1.6813" y="0" dx="1.1527" dy="1.7371" layer="1"/>
<smd name="2" x="1.6813" y="0" dx="1.1527" dy="1.7371" layer="1"/>
<text x="0" y="1.8175" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8175" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF2014" urn="urn:adsk.eagle:footprint:16378535/5" library_version="20">
<description>MELF, 2.00 mm length, 1.40 mm diameter
&lt;p&gt;MELF Resistor package with 2.00 mm length and 1.40 mm diameter&lt;/p&gt;</description>
<wire x1="0.5189" y1="1.114" x2="-0.5189" y2="1.114" width="0.127" layer="21"/>
<wire x1="-0.5189" y1="-1.114" x2="0.5189" y2="-1.114" width="0.127" layer="21"/>
<wire x1="1.05" y1="-0.725" x2="-1.05" y2="-0.725" width="0.12" layer="51"/>
<wire x1="-1.05" y1="-0.725" x2="-1.05" y2="0.725" width="0.12" layer="51"/>
<wire x1="-1.05" y1="0.725" x2="1.05" y2="0.725" width="0.12" layer="51"/>
<wire x1="1.05" y1="0.725" x2="1.05" y2="-0.725" width="0.12" layer="51"/>
<smd name="1" x="-0.9918" y="0" dx="0.9456" dy="1.6" layer="1"/>
<smd name="2" x="0.9918" y="0" dx="0.9456" dy="1.6" layer="1"/>
<text x="0" y="1.749" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.749" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF5924" urn="urn:adsk.eagle:footprint:16378541/5" library_version="20">
<description>MELF, 5.90 mm length, 2.45 mm diameter
&lt;p&gt;MELF Resistor package with 5.90 mm length and 2.45 mm diameter&lt;/p&gt;</description>
<wire x1="2.1315" y1="1.639" x2="-2.1315" y2="1.639" width="0.127" layer="21"/>
<wire x1="-2.1315" y1="-1.639" x2="2.1315" y2="-1.639" width="0.127" layer="21"/>
<wire x1="3.05" y1="-1.25" x2="-3.05" y2="-1.25" width="0.12" layer="51"/>
<wire x1="-3.05" y1="-1.25" x2="-3.05" y2="1.25" width="0.12" layer="51"/>
<wire x1="-3.05" y1="1.25" x2="3.05" y2="1.25" width="0.12" layer="51"/>
<wire x1="3.05" y1="1.25" x2="3.05" y2="-1.25" width="0.12" layer="51"/>
<smd name="1" x="-2.7946" y="0" dx="1.3261" dy="2.65" layer="1"/>
<smd name="2" x="2.7946" y="0" dx="1.3261" dy="2.65" layer="1"/>
<text x="0" y="2.274" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.274" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF3218" urn="urn:adsk.eagle:footprint:16378531/5" library_version="20">
<description>MELF, 3.20 mm length, 1.80 mm diameter
&lt;p&gt;MELF Resistor package with 3.20 mm length and 1.80 mm diameter&lt;/p&gt;</description>
<wire x1="0.8815" y1="1.314" x2="-0.8815" y2="1.314" width="0.127" layer="21"/>
<wire x1="-0.8815" y1="-1.314" x2="0.8815" y2="-1.314" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.925" x2="-1.7" y2="-0.925" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.925" x2="-1.7" y2="0.925" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.925" x2="1.7" y2="0.925" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.925" x2="1.7" y2="-0.925" width="0.12" layer="51"/>
<smd name="1" x="-1.4946" y="0" dx="1.2261" dy="2" layer="1"/>
<smd name="2" x="1.4946" y="0" dx="1.2261" dy="2" layer="1"/>
<text x="0" y="1.949" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.949" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESAD724W46L381D178B" urn="urn:adsk.eagle:footprint:16378530/5" library_version="20">
<description>Axial Resistor, 7.24 mm pitch, 3.81 mm body length, 1.78 mm body diameter
&lt;p&gt;Axial Resistor package with 7.24 mm pitch (lead spacing), 0.46 mm lead diameter, 3.81 mm body length and 1.78 mm body diameter&lt;/p&gt;</description>
<wire x1="-2.16" y1="1.015" x2="-2.16" y2="-1.015" width="0.127" layer="21"/>
<wire x1="-2.16" y1="-1.015" x2="2.16" y2="-1.015" width="0.127" layer="21"/>
<wire x1="2.16" y1="-1.015" x2="2.16" y2="1.015" width="0.127" layer="21"/>
<wire x1="2.16" y1="1.015" x2="-2.16" y2="1.015" width="0.127" layer="21"/>
<wire x1="-2.16" y1="0" x2="-2.736" y2="0" width="0.127" layer="21"/>
<wire x1="2.16" y1="0" x2="2.736" y2="0" width="0.127" layer="21"/>
<wire x1="2.16" y1="-1.015" x2="-2.16" y2="-1.015" width="0.12" layer="51"/>
<wire x1="-2.16" y1="-1.015" x2="-2.16" y2="1.015" width="0.12" layer="51"/>
<wire x1="-2.16" y1="1.015" x2="2.16" y2="1.015" width="0.12" layer="51"/>
<wire x1="2.16" y1="1.015" x2="2.16" y2="-1.015" width="0.12" layer="51"/>
<pad name="1" x="-3.62" y="0" drill="0.66" diameter="1.26"/>
<pad name="2" x="3.62" y="0" drill="0.66" diameter="1.26"/>
<text x="0" y="1.65" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.65" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="RESC1005X40" urn="urn:adsk.eagle:package:16378568/5" type="model">
<description>Chip, 1.05 X 0.54 X 0.40 mm body
&lt;p&gt;Chip package with body size 1.05 X 0.54 X 0.40 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC1005X40"/>
</packageinstances>
</package3d>
<package3d name="RESC1608X60" urn="urn:adsk.eagle:package:16378565/5" type="model">
<description>Chip, 1.60 X 0.82 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.82 X 0.60 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC1608X60"/>
</packageinstances>
</package3d>
<package3d name="RESC2012X65" urn="urn:adsk.eagle:package:16378559/5" type="model">
<description>Chip, 2.00 X 1.25 X 0.65 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 0.65 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC2012X65"/>
</packageinstances>
</package3d>
<package3d name="RESC3216X70" urn="urn:adsk.eagle:package:16378566/5" type="model">
<description>Chip, 3.20 X 1.60 X 0.70 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 0.70 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC3216X70"/>
</packageinstances>
</package3d>
<package3d name="RESC3224X71" urn="urn:adsk.eagle:package:16378563/7" type="model">
<description>Chip, 3.20 X 2.49 X 0.71 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.49 X 0.71 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC3224X71"/>
</packageinstances>
</package3d>
<package3d name="RESC5025X71" urn="urn:adsk.eagle:package:16378564/5" type="model">
<description>Chip, 5.00 X 2.50 X 0.71 mm body
&lt;p&gt;Chip package with body size 5.00 X 2.50 X 0.71 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC5025X71"/>
</packageinstances>
</package3d>
<package3d name="RESC6332X71L" urn="urn:adsk.eagle:package:16378557/6" type="model">
<description>Chip, 6.30 X 3.20 X 0.71 mm body
&lt;p&gt;Chip package with body size 6.30 X 3.20 X 0.71 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC6332X71"/>
</packageinstances>
</package3d>
<package3d name="RESAD1176W63L850D250B" urn="urn:adsk.eagle:package:16378560/5" type="model">
<description>AXIAL Resistor, 11.76 mm pitch, 8.5 mm body length, 2.5 mm body diameter
&lt;p&gt;AXIAL Resistor package with 11.76 mm pitch, 0.63 mm lead diameter, 8.5 mm body length and 2.5 mm body diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESAD1176W63L850D250B"/>
</packageinstances>
</package3d>
<package3d name="RESMELF3515" urn="urn:adsk.eagle:package:16378562/5" type="model">
<description>MELF, 3.50 mm length, 1.52 mm diameter
&lt;p&gt;MELF Resistor package with 3.50 mm length and 1.52 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF3515"/>
</packageinstances>
</package3d>
<package3d name="RESMELF2014" urn="urn:adsk.eagle:package:16378558/5" type="model">
<description>MELF, 2.00 mm length, 1.40 mm diameter
&lt;p&gt;MELF Resistor package with 2.00 mm length and 1.40 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF2014"/>
</packageinstances>
</package3d>
<package3d name="RESMELF5924" urn="urn:adsk.eagle:package:16378567/6" type="model">
<description>MELF, 5.90 mm length, 2.45 mm diameter
&lt;p&gt;MELF Resistor package with 5.90 mm length and 2.45 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF5924"/>
</packageinstances>
</package3d>
<package3d name="RESMELF3218" urn="urn:adsk.eagle:package:16378556/5" type="model">
<description>MELF, 3.20 mm length, 1.80 mm diameter
&lt;p&gt;MELF Resistor package with 3.20 mm length and 1.80 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF3218"/>
</packageinstances>
</package3d>
<package3d name="RESAD724W46L381D178B" urn="urn:adsk.eagle:package:16378561/5" type="model">
<description>Axial Resistor, 7.24 mm pitch, 3.81 mm body length, 1.78 mm body diameter
&lt;p&gt;Axial Resistor package with 7.24 mm pitch (lead spacing), 0.46 mm lead diameter, 3.81 mm body length and 1.78 mm body diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESAD724W46L381D178B"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="R" urn="urn:adsk.eagle:symbol:16378529/3" library_version="20">
<description>RESISTOR</description>
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="0" y="2.54" size="1.778" layer="95" align="center">&gt;NAME</text>
<text x="0" y="-5.08" size="1.778" layer="95" align="center">&gt;SPICEMODEL</text>
<text x="0" y="-2.54" size="1.778" layer="96" align="center">&gt;VALUE</text>
<text x="0" y="-7.62" size="1.778" layer="95" align="center">&gt;SPICEEXTRA</text>
</symbol>
<symbol name="R-US" urn="urn:adsk.eagle:symbol:16378528/2" library_version="20">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.2032" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.2032" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.2032" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.2032" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.2032" layer="94"/>
<text x="0" y="2.7686" size="1.778" layer="95" align="center">&gt;NAME</text>
<text x="0" y="-3.302" size="1.778" layer="96" align="center">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" urn="urn:adsk.eagle:component:16378570/11" prefix="R" uservalue="yes" library_version="20">
<description>&lt;b&gt;Resistor Fixed - Generic</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="CHIP-0402(1005-METRIC)" package="RESC1005X40">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378568/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0603(1608-METRIC)" package="RESC1608X60">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378565/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0805(2012-METRIC)" package="RESC2012X65">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378559/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1206(3216-METRIC)" package="RESC3216X70">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378566/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1210(3225-METRIC)" package="RESC3224X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378563/7"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-2010(5025-METRIC)" package="RESC5025X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378564/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-2512(6332-METRIC)" package="RESC6332X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378557/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-11.7MM-PITCH" package="RESAD1176W63L850D250B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378560/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(3515-METRIC)" package="RESMELF3515">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378562/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(2014-METRIC)" package="RESMELF2014">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378558/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(5924-METRIC)" package="RESMELF5924">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378567/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(3218-METRIC)" package="RESMELF3218">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378556/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-7.2MM-PITCH" package="RESAD724W46L381D178B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378561/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="R-US" urn="urn:adsk.eagle:component:16378569/12" prefix="R" uservalue="yes" library_version="20">
<description>&lt;B&gt;Resistor Fixed - ANSI</description>
<gates>
<gate name="G$1" symbol="R-US" x="0" y="0"/>
</gates>
<devices>
<device name="CHIP-0402(1005-METRIC)" package="RESC1005X40">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378568/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0603(1608-METRIC)" package="RESC1608X60">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378565/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0805(2012-METRIC)" package="RESC2012X65">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378559/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1206(3216-METRIC)" package="RESC3216X70">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378566/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1210(3225-METRIC)" package="RESC3224X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378563/7"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-2010(5025-METRIC)" package="RESC5025X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378564/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-2512(6332-METRIC)" package="RESC6332X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378557/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-11.7MM-PITCH" package="RESAD1176W63L850D250B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378560/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(3515-METRIC)" package="RESMELF3515">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378562/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(2014-METRIC)" package="RESMELF2014">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378558/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(5924-METRIC)" package="RESMELF5924">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378567/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(3218-METRIC)" package="RESMELF3218">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378556/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-7.2MM-PITCH" package="RESAD724W46L381D178B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378561/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="R">
<pinmap gate="G$1" pin="1" pinorder="1"/>
<pinmap gate="G$1" pin="2" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
</devicesets>
</library>
<library name="Power_Symbols" urn="urn:adsk.eagle:library:16502351">
<description>&lt;B&gt;Supply &amp; Ground symbols</description>
<packages>
</packages>
<symbols>
<symbol name="GND-BAR" urn="urn:adsk.eagle:symbol:16502372/2" library_version="21">
<description>Ground (GND) Bar</description>
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="0" y="-1.905" size="1.778" layer="96" align="center">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND-BAR" urn="urn:adsk.eagle:component:16502419/5" prefix="SUPPLY" uservalue="yes" library_version="21">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt; - Ground (GND) Bar</description>
<gates>
<gate name="G$1" symbol="GND-BAR" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Supply" constant="no"/>
<attribute name="VALUE" value="GND" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Tinkercad" urn="urn:adsk.eagle:library:30890021">
<packages>
<package name="1X03" urn="urn:adsk.eagle:footprint:22340/1" library_version="100">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-3.8862" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.81" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
</package>
<package name="CAPC1005X60" urn="urn:adsk.eagle:footprint:16290849/5" library_version="100">
<description>Chip, 1.00 X 0.50 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.00 X 0.50 X 0.60 mm&lt;/p&gt;</description>
<wire x1="0.55" y1="0.6286" x2="-0.55" y2="0.6286" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.6286" x2="-0.55" y2="-0.6286" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.3" x2="-0.55" y2="-0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="-0.3" x2="-0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="0.3" x2="0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="0.55" y1="0.3" x2="0.55" y2="-0.3" width="0.12" layer="51"/>
<smd name="1" x="-0.4846" y="0" dx="0.56" dy="0.6291" layer="1"/>
<smd name="2" x="0.4846" y="0" dx="0.56" dy="0.6291" layer="1"/>
<text x="0" y="1.2636" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.2636" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC1110X102" urn="urn:adsk.eagle:footprint:16290845/5" library_version="100">
<description>Chip, 1.17 X 1.02 X 1.02 mm body
&lt;p&gt;Chip package with body size 1.17 X 1.02 X 1.02 mm&lt;/p&gt;</description>
<wire x1="0.66" y1="0.9552" x2="-0.66" y2="0.9552" width="0.127" layer="21"/>
<wire x1="0.66" y1="-0.9552" x2="-0.66" y2="-0.9552" width="0.127" layer="21"/>
<wire x1="0.66" y1="-0.635" x2="-0.66" y2="-0.635" width="0.12" layer="51"/>
<wire x1="-0.66" y1="-0.635" x2="-0.66" y2="0.635" width="0.12" layer="51"/>
<wire x1="-0.66" y1="0.635" x2="0.66" y2="0.635" width="0.12" layer="51"/>
<wire x1="0.66" y1="0.635" x2="0.66" y2="-0.635" width="0.12" layer="51"/>
<smd name="1" x="-0.5388" y="0" dx="0.6626" dy="1.2823" layer="1"/>
<smd name="2" x="0.5388" y="0" dx="0.6626" dy="1.2823" layer="1"/>
<text x="0" y="1.5902" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.5902" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC1608X85" urn="urn:adsk.eagle:footprint:16290847/5" library_version="100">
<description>Chip, 1.60 X 0.80 X 0.85 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.80 X 0.85 mm&lt;/p&gt;</description>
<wire x1="0.875" y1="0.7991" x2="-0.875" y2="0.7991" width="0.127" layer="21"/>
<wire x1="0.875" y1="-0.7991" x2="-0.875" y2="-0.7991" width="0.127" layer="21"/>
<wire x1="0.875" y1="-0.475" x2="-0.875" y2="-0.475" width="0.12" layer="51"/>
<wire x1="-0.875" y1="-0.475" x2="-0.875" y2="0.475" width="0.12" layer="51"/>
<wire x1="-0.875" y1="0.475" x2="0.875" y2="0.475" width="0.12" layer="51"/>
<wire x1="0.875" y1="0.475" x2="0.875" y2="-0.475" width="0.12" layer="51"/>
<smd name="1" x="-0.7746" y="0" dx="0.9209" dy="0.9702" layer="1"/>
<smd name="2" x="0.7746" y="0" dx="0.9209" dy="0.9702" layer="1"/>
<text x="0" y="1.4341" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.4341" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC2012X110" urn="urn:adsk.eagle:footprint:16290848/5" library_version="100">
<description>Chip, 2.00 X 1.25 X 1.10 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 1.10 mm&lt;/p&gt;</description>
<wire x1="1.1" y1="1.0467" x2="-1.1" y2="1.0467" width="0.127" layer="21"/>
<wire x1="1.1" y1="-1.0467" x2="-1.1" y2="-1.0467" width="0.127" layer="21"/>
<wire x1="1.1" y1="-0.725" x2="-1.1" y2="-0.725" width="0.12" layer="51"/>
<wire x1="-1.1" y1="-0.725" x2="-1.1" y2="0.725" width="0.12" layer="51"/>
<wire x1="-1.1" y1="0.725" x2="1.1" y2="0.725" width="0.12" layer="51"/>
<wire x1="1.1" y1="0.725" x2="1.1" y2="-0.725" width="0.12" layer="51"/>
<smd name="1" x="-0.8754" y="0" dx="1.1646" dy="1.4653" layer="1"/>
<smd name="2" x="0.8754" y="0" dx="1.1646" dy="1.4653" layer="1"/>
<text x="0" y="1.6817" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.6817" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC3216X135" urn="urn:adsk.eagle:footprint:16290836/5" library_version="100">
<description>Chip, 3.20 X 1.60 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 1.35 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.2217" x2="-1.7" y2="1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-1.2217" x2="-1.7" y2="-1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<text x="0" y="1.8567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC3225X135" urn="urn:adsk.eagle:footprint:16290843/5" library_version="100">
<description>Chip, 3.20 X 2.50 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.50 X 1.35 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.6717" x2="-1.7" y2="1.6717" width="0.127" layer="21"/>
<wire x1="1.7" y1="-1.6717" x2="-1.7" y2="-1.6717" width="0.12" layer="21"/>
<wire x1="1.7" y1="-1.35" x2="-1.7" y2="-1.35" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-1.35" x2="-1.7" y2="1.35" width="0.12" layer="51"/>
<wire x1="-1.7" y1="1.35" x2="1.7" y2="1.35" width="0.12" layer="51"/>
<wire x1="1.7" y1="1.35" x2="1.7" y2="-1.35" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="2.7153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="2.7153" layer="1"/>
<text x="0" y="2.3067" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.3067" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC4532X135" urn="urn:adsk.eagle:footprint:16290841/5" library_version="100">
<description>Chip, 4.50 X 3.20 X 1.35 mm body
&lt;p&gt;Chip package with body size 4.50 X 3.20 X 1.35 mm&lt;/p&gt;</description>
<wire x1="2.4" y1="2.0217" x2="-2.4" y2="2.0217" width="0.127" layer="21"/>
<wire x1="2.4" y1="-2.0217" x2="-2.4" y2="-2.0217" width="0.127" layer="21"/>
<wire x1="2.4" y1="-1.7" x2="-2.4" y2="-1.7" width="0.12" layer="51"/>
<wire x1="-2.4" y1="-1.7" x2="-2.4" y2="1.7" width="0.12" layer="51"/>
<wire x1="-2.4" y1="1.7" x2="2.4" y2="1.7" width="0.12" layer="51"/>
<wire x1="2.4" y1="1.7" x2="2.4" y2="-1.7" width="0.12" layer="51"/>
<smd name="1" x="-2.0565" y="0" dx="1.3973" dy="3.4153" layer="1"/>
<smd name="2" x="2.0565" y="0" dx="1.3973" dy="3.4153" layer="1"/>
<text x="0" y="2.6567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.6567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM3216X180" urn="urn:adsk.eagle:footprint:16290835/5" library_version="100">
<description>Molded Body, 3.20 X 1.60 X 1.80 mm body
&lt;p&gt;Molded Body package with body size 3.20 X 1.60 X 1.80 mm&lt;/p&gt;</description>
<wire x1="-1.7" y1="0.9084" x2="1.7" y2="0.9084" width="0.127" layer="21"/>
<wire x1="-1.7" y1="-0.9084" x2="1.7" y2="-0.9084" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.3099" y="0" dx="1.7955" dy="1.1887" layer="1"/>
<smd name="2" x="1.3099" y="0" dx="1.7955" dy="1.1887" layer="1"/>
<text x="0" y="1.5434" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.5434" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM3528X210" urn="urn:adsk.eagle:footprint:16290844/5" library_version="100">
<description>Molded Body, 3.50 X 2.80 X 2.10 mm body
&lt;p&gt;Molded Body package with body size 3.50 X 2.80 X 2.10 mm&lt;/p&gt;</description>
<wire x1="-1.85" y1="1.5" x2="1.85" y2="1.5" width="0.127" layer="21"/>
<wire x1="-1.85" y1="-1.5" x2="1.85" y2="-1.5" width="0.127" layer="21"/>
<wire x1="1.85" y1="-1.5" x2="-1.85" y2="-1.5" width="0.12" layer="51"/>
<wire x1="-1.85" y1="-1.5" x2="-1.85" y2="1.5" width="0.12" layer="51"/>
<wire x1="-1.85" y1="1.5" x2="1.85" y2="1.5" width="0.12" layer="51"/>
<wire x1="1.85" y1="1.5" x2="1.85" y2="-1.5" width="0.12" layer="51"/>
<smd name="1" x="-1.4599" y="0" dx="1.7955" dy="2.2036" layer="1"/>
<smd name="2" x="1.4599" y="0" dx="1.7955" dy="2.2036" layer="1"/>
<text x="0" y="2.135" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.135" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM6032X280" urn="urn:adsk.eagle:footprint:16290839/5" library_version="100">
<description>Molded Body, 6.00 X 3.20 X 2.80 mm body
&lt;p&gt;Molded Body package with body size 6.00 X 3.20 X 2.80 mm&lt;/p&gt;</description>
<wire x1="-3.15" y1="1.75" x2="3.15" y2="1.75" width="0.127" layer="21"/>
<wire x1="-3.15" y1="-1.75" x2="3.15" y2="-1.75" width="0.127" layer="21"/>
<wire x1="3.15" y1="-1.75" x2="-3.15" y2="-1.75" width="0.12" layer="51"/>
<wire x1="-3.15" y1="-1.75" x2="-3.15" y2="1.75" width="0.12" layer="51"/>
<wire x1="-3.15" y1="1.75" x2="3.15" y2="1.75" width="0.12" layer="51"/>
<wire x1="3.15" y1="1.75" x2="3.15" y2="-1.75" width="0.12" layer="51"/>
<smd name="1" x="-2.4712" y="0" dx="2.368" dy="2.2036" layer="1"/>
<smd name="2" x="2.4712" y="0" dx="2.368" dy="2.2036" layer="1"/>
<text x="0" y="2.385" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.385" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM7343X310" urn="urn:adsk.eagle:footprint:16290840/5" library_version="100">
<description>Molded Body, 7.30 X 4.30 X 3.10 mm body
&lt;p&gt;Molded Body package with body size 7.30 X 4.30 X 3.10 mm&lt;/p&gt;</description>
<wire x1="-3.8" y1="2.3" x2="3.8" y2="2.3" width="0.127" layer="21"/>
<wire x1="-3.8" y1="-2.3" x2="3.8" y2="-2.3" width="0.127" layer="21"/>
<wire x1="3.8" y1="-2.3" x2="-3.8" y2="-2.3" width="0.12" layer="51"/>
<wire x1="-3.8" y1="-2.3" x2="-3.8" y2="2.3" width="0.12" layer="51"/>
<wire x1="-3.8" y1="2.3" x2="3.8" y2="2.3" width="0.12" layer="51"/>
<wire x1="3.8" y1="2.3" x2="3.8" y2="-2.3" width="0.12" layer="51"/>
<smd name="1" x="-3.1212" y="0" dx="2.368" dy="2.4036" layer="1"/>
<smd name="2" x="3.1212" y="0" dx="2.368" dy="2.4036" layer="1"/>
<text x="0" y="2.935" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.935" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC4564X110" urn="urn:adsk.eagle:footprint:16290837/5" library_version="100">
<description>Chip, 4.50 X 6.40 X 1.10 mm body
&lt;p&gt;Chip package with body size 4.50 X 6.40 X 1.10 mm&lt;/p&gt;</description>
<wire x1="2.4" y1="3.7179" x2="-2.4" y2="3.7179" width="0.127" layer="21"/>
<wire x1="2.4" y1="-3.7179" x2="-2.4" y2="-3.7179" width="0.127" layer="21"/>
<wire x1="2.4" y1="-3.4" x2="-2.4" y2="-3.4" width="0.12" layer="51"/>
<wire x1="-2.4" y1="-3.4" x2="-2.4" y2="3.4" width="0.12" layer="51"/>
<wire x1="-2.4" y1="3.4" x2="2.4" y2="3.4" width="0.12" layer="51"/>
<wire x1="2.4" y1="3.4" x2="2.4" y2="-3.4" width="0.12" layer="51"/>
<smd name="1" x="-2.0565" y="0" dx="1.3973" dy="6.8078" layer="1"/>
<smd name="2" x="2.0565" y="0" dx="1.3973" dy="6.8078" layer="1"/>
<text x="0" y="4.3529" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-4.3529" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPRD550W60D1025H1250B" urn="urn:adsk.eagle:footprint:16290829/5" library_version="100">
<description>Radial Non-Polarized Capacitor, 5.50 mm pitch, 10.25 mm body diameter, 12.50 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 5.50 mm pitch (lead spacing), 0.60 mm lead diameter, 10.25 mm body diameter and 12.50 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="5.25" width="0.127" layer="21"/>
<circle x="0" y="0" radius="5.25" width="0.12" layer="51"/>
<pad name="1" x="-2.75" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="2.75" y="0" drill="0.8" diameter="1.4"/>
<text x="0" y="5.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-5.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPRD2261W240D5080H5555B" urn="urn:adsk.eagle:footprint:16290850/5" library_version="100">
<description>Radial Non-Polarized Capacitor, 22.61 mm pitch, 50.80 mm body diameter, 55.55 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 22.61 mm pitch (lead spacing), 2.40 mm lead diameter, 50.80 mm body diameter and 55.55 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="25.79" width="0.127" layer="21"/>
<circle x="0" y="0" radius="25.79" width="0.12" layer="51"/>
<pad name="1" x="-11.305" y="0" drill="2.6" diameter="3.9"/>
<pad name="2" x="11.305" y="0" drill="2.6" diameter="3.9"/>
<text x="0" y="26.425" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-26.425" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAP-THRU-2.54MM" urn="urn:adsk.eagle:footprint:32248318/2" library_version="100">
<pad name="1" x="-1.27" y="0" drill="1.016" diameter="1.8796"/>
<pad name="2" x="1.27" y="0" drill="1.016" diameter="1.8796"/>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-1.27" width="0.1524" layer="21" curve="-180"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="1.27" width="0.1524" layer="21" curve="-180"/>
<text x="0" y="1.524" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.524" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="1X03" urn="urn:adsk.eagle:package:22458/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X03"/>
</packageinstances>
</package3d>
<package3d name="CAPC1005X60" urn="urn:adsk.eagle:package:16290895/5" type="model">
<description>Chip, 1.00 X 0.50 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.00 X 0.50 X 0.60 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC1005X60"/>
</packageinstances>
</package3d>
<package3d name="CAPC1110X102" urn="urn:adsk.eagle:package:16290904/5" type="model">
<description>Chip, 1.17 X 1.02 X 1.02 mm body
&lt;p&gt;Chip package with body size 1.17 X 1.02 X 1.02 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC1110X102"/>
</packageinstances>
</package3d>
<package3d name="CAPC1608X85" urn="urn:adsk.eagle:package:16290898/5" type="model">
<description>Chip, 1.60 X 0.80 X 0.85 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.80 X 0.85 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC1608X85"/>
</packageinstances>
</package3d>
<package3d name="CAPC2012X110" urn="urn:adsk.eagle:package:16290897/5" type="model">
<description>Chip, 2.00 X 1.25 X 1.10 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 1.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC2012X110"/>
</packageinstances>
</package3d>
<package3d name="CAPC3216X135" urn="urn:adsk.eagle:package:16290893/5" type="model">
<description>Chip, 3.20 X 1.60 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 1.35 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC3216X135"/>
</packageinstances>
</package3d>
<package3d name="CAPC3225X135" urn="urn:adsk.eagle:package:16290903/5" type="model">
<description>Chip, 3.20 X 2.50 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.50 X 1.35 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC3225X135"/>
</packageinstances>
</package3d>
<package3d name="CAPC4532X135" urn="urn:adsk.eagle:package:16290900/5" type="model">
<description>Chip, 4.50 X 3.20 X 1.35 mm body
&lt;p&gt;Chip package with body size 4.50 X 3.20 X 1.35 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC4532X135"/>
</packageinstances>
</package3d>
<package3d name="CAPM3216X180" urn="urn:adsk.eagle:package:16290894/5" type="model">
<description>Molded Body, 3.20 X 1.60 X 1.80 mm body
&lt;p&gt;Molded Body package with body size 3.20 X 1.60 X 1.80 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM3216X180"/>
</packageinstances>
</package3d>
<package3d name="CAPM3528X210" urn="urn:adsk.eagle:package:16290902/5" type="model">
<description>Molded Body, 3.50 X 2.80 X 2.10 mm body
&lt;p&gt;Molded Body package with body size 3.50 X 2.80 X 2.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM3528X210"/>
</packageinstances>
</package3d>
<package3d name="CAPM6032X280" urn="urn:adsk.eagle:package:16290896/5" type="model">
<description>Molded Body, 6.00 X 3.20 X 2.80 mm body
&lt;p&gt;Molded Body package with body size 6.00 X 3.20 X 2.80 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM6032X280"/>
</packageinstances>
</package3d>
<package3d name="CAPM7343X310" urn="urn:adsk.eagle:package:16290891/5" type="model">
<description>Molded Body, 7.30 X 4.30 X 3.10 mm body
&lt;p&gt;Molded Body package with body size 7.30 X 4.30 X 3.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM7343X310"/>
</packageinstances>
</package3d>
<package3d name="CAPC4564X110L" urn="urn:adsk.eagle:package:16290887/6" type="model">
<description>Chip, 4.50 X 6.40 X 1.10 mm body
&lt;p&gt;Chip package with body size 4.50 X 6.40 X 1.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC4564X110"/>
</packageinstances>
</package3d>
<package3d name="CAPRD550W60D1025H1250B" urn="urn:adsk.eagle:package:16290858/5" type="model">
<description>Radial Non-Polarized Capacitor, 5.50 mm pitch, 10.25 mm body diameter, 12.50 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 5.50 mm pitch (lead spacing), 0.60 mm lead diameter, 10.25 mm body diameter and 12.50 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPRD550W60D1025H1250B"/>
</packageinstances>
</package3d>
<package3d name="CAPRD2261W240D5080H5555B" urn="urn:adsk.eagle:package:16290864/5" type="model">
<description>Radial Non-Polarized Capacitor, 22.61 mm pitch, 50.80 mm body diameter, 55.55 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 22.61 mm pitch (lead spacing), 2.40 mm lead diameter, 50.80 mm body diameter and 55.55 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPRD2261W240D5080H5555B"/>
</packageinstances>
</package3d>
<package3d name="CAP-THRU-2.54MM" urn="urn:adsk.eagle:package:32248319/2" type="model">
<packageinstances>
<packageinstance name="CAP-THRU-2.54MM"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PINHD-1X03" urn="urn:adsk.eagle:symbol:31968519/1" library_version="100">
<pin name="1" x="-2.54" y="2.54" visible="pin" length="short"/>
<pin name="2" x="-2.54" y="0" visible="pin" length="short"/>
<pin name="3" x="-2.54" y="-2.54" visible="pin" length="short"/>
<circle x="1.016" y="2.54" radius="1.016" width="0.1524" layer="94"/>
<circle x="1.016" y="0" radius="1.016" width="0.1524" layer="94"/>
<circle x="1.016" y="-2.54" radius="1.016" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-5.08" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="C" urn="urn:adsk.eagle:symbol:30890049/2" library_version="100">
<description>Capacitor</description>
<rectangle x1="-2.032" y1="-2.032" x2="-1.524" y2="2.032" layer="94"/>
<rectangle x1="-1.016" y1="-2.032" x2="-0.508" y2="2.032" layer="94"/>
<wire x1="0" y1="0" x2="-0.508" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.032" y2="0" width="0.1524" layer="94"/>
<pin name="1" x="2.54" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<text x="-2.54" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-6.35" size="1.778" layer="97">&gt;SPICEMODEL</text>
<text x="-2.54" y="-4.064" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="-8.89" size="1.778" layer="97">&gt;SPICEEXTRA</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-1X03" urn="urn:adsk.eagle:component:31968534/2" library_version="100">
<gates>
<gate name="G$1" symbol="PINHD-1X03" x="0" y="0"/>
</gates>
<devices>
<device name="_1X03M" package="1X03">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22458/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAPACITOR" urn="urn:adsk.eagle:component:30890073/6" prefix="C" uservalue="yes" library_version="100">
<description>&lt;B&gt;Capacitor - Generic</description>
<gates>
<gate name="G$1" symbol="C" x="0" y="0"/>
</gates>
<devices>
<device name="CHIP-0402(1005-METRIC)" package="CAPC1005X60">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290895/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0504(1310-METRIC)" package="CAPC1110X102">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290904/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0603(1608-METRIC)" package="CAPC1608X85">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290898/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0805(2012-METRIC)" package="CAPC2012X110">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290897/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1206(3216-METRIC)" package="CAPC3216X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290893/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1210(3225-METRIC)" package="CAPC3225X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290903/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1812(4532-METRIC)" package="CAPC4532X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290900/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1206(3216-METRIC)" package="CAPM3216X180">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290894/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1411(3528-METRIC)" package="CAPM3528X210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290902/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2412(6032-METRIC)" package="CAPM6032X280">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290896/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2917(7343-METRIC)" package="CAPM7343X310">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290891/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1825(4564-METRIC)" package="CAPC4564X110">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290887/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-12.5MM-DIA" package="CAPRD550W60D1025H1250B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290858/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-55.5MM-DIA" package="CAPRD2261W240D5080H5555B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290864/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CERAMIC-2.54MM" package="CAP-THRU-2.54MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:32248319/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Tutorial - Fusion 360" urn="urn:adsk.eagle:library:16997205">
<description>Library of several components used in the Getting Started With Fusion Electronics tutorial.</description>
<packages>
</packages>
<symbols>
<symbol name="VCC-CIRCLE" urn="urn:adsk.eagle:symbol:16997212/1" library_version="24">
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
<text x="-0.127" y="3.175" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="VCC" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="VCC-CIRCLE" urn="urn:adsk.eagle:component:16997234/4" prefix="SUPPLY" uservalue="yes" library_version="24">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt; VCC Circle</description>
<gates>
<gate name="G$1" symbol="VCC-CIRCLE" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Supply" constant="no"/>
<attribute name="VALUE" value="VCC" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Connector" urn="urn:adsk.eagle:library:16378166">
<description>&lt;b&gt;Pin Headers,Terminal blocks, D-Sub, Backplane, FFC/FPC, Socket</description>
<packages>
<package name="TERMBLK_508-2N" urn="urn:adsk.eagle:footprint:24957600/1" library_version="50">
<pad name="1" x="0" y="0" drill="1.2"/>
<pad name="2" x="5.08" y="0" drill="1.2"/>
<wire x1="7.745" y1="4.25" x2="7.745" y2="-4.25" width="0.1524" layer="21"/>
<wire x1="7.745" y1="-4.25" x2="-2.665" y2="-4.25" width="0.1524" layer="21"/>
<wire x1="-2.665" y1="-4.25" x2="-2.665" y2="4.25" width="0.1524" layer="21"/>
<wire x1="-2.665" y1="4.25" x2="7.745" y2="4.25" width="0.1524" layer="21"/>
<text x="2.54" y="-6.1" size="1.778" layer="25" align="bottom-center">&gt;NAME</text>
<text x="2.54" y="4.6" size="1.778" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="TERMBLK_254-2N" urn="urn:adsk.eagle:footprint:24957601/1" library_version="50">
<pad name="1" x="0" y="0" drill="1.2"/>
<pad name="2" x="2.54" y="0" drill="1.2"/>
<wire x1="4.165" y1="3.4" x2="4.165" y2="-3.4" width="0.1524" layer="21"/>
<wire x1="4.165" y1="-3.4" x2="-1.625" y2="-3.4" width="0.1524" layer="21"/>
<wire x1="-1.625" y1="-3.4" x2="-1.625" y2="3.4" width="0.1524" layer="21"/>
<wire x1="-1.625" y1="3.4" x2="4.165" y2="3.4" width="0.1524" layer="21"/>
<text x="1.27" y="-5.4" size="1.778" layer="25" align="bottom-center">&gt;NAME</text>
<text x="1.27" y="3.9" size="1.778" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="1X02" urn="urn:adsk.eagle:footprint:22309/1" library_version="50">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-2.6162" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
</package>
<package name="1X02/90" urn="urn:adsk.eagle:footprint:22310/1" library_version="50">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-3.175" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.445" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
</package>
<package name="1X04" urn="urn:adsk.eagle:footprint:22258/1" library_version="50">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-5.1562" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
</package>
<package name="1X04/90" urn="urn:adsk.eagle:footprint:22259/1" library_version="50">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-5.715" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="6.985" y="-4.445" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="TERMBLK_508-2N" urn="urn:adsk.eagle:package:24957621/2" type="model">
<packageinstances>
<packageinstance name="TERMBLK_508-2N"/>
</packageinstances>
</package3d>
<package3d name="TERMBLK_254-2N" urn="urn:adsk.eagle:package:24957623/2" type="model">
<packageinstances>
<packageinstance name="TERMBLK_254-2N"/>
</packageinstances>
</package3d>
<package3d name="1X02" urn="urn:adsk.eagle:package:22435/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X02"/>
</packageinstances>
</package3d>
<package3d name="1X02/90" urn="urn:adsk.eagle:package:22437/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X02/90"/>
</packageinstances>
</package3d>
<package3d name="1X04" urn="urn:adsk.eagle:package:22407/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X04"/>
</packageinstances>
</package3d>
<package3d name="1X04/90" urn="urn:adsk.eagle:package:22404/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X04/90"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="TERMBLK_2" urn="urn:adsk.eagle:symbol:24957587/3" library_version="50">
<pin name="1" x="-5.08" y="2.54" length="short"/>
<pin name="2" x="-5.08" y="0" length="short"/>
<text x="0" y="-2.794" size="1.778" layer="96" align="top-center">&gt;VALUE</text>
<text x="0" y="5.334" size="1.778" layer="95" align="bottom-center">&gt;NAME</text>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
</symbol>
<symbol name="PINHD2" urn="urn:adsk.eagle:symbol:22308/1" library_version="50">
<wire x1="-6.35" y1="-2.54" x2="1.27" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="5.08" x2="-6.35" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="5.08" x2="-6.35" y2="-2.54" width="0.4064" layer="94"/>
<text x="-6.35" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
<symbol name="PINHD4" urn="urn:adsk.eagle:symbol:22257/1" library_version="50">
<wire x1="-6.35" y1="-5.08" x2="1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="1.27" y2="7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="7.62" x2="-6.35" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="7.62" x2="-6.35" y2="-5.08" width="0.4064" layer="94"/>
<text x="-6.35" y="8.255" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="2828XX-2" urn="urn:adsk.eagle:component:24957692/7" prefix="J" library_version="50">
<description>2 Position Wire to Board Terminal Block Horizontal with Board
&lt;br&gt;&lt;a href="https://www.te.com.cn/commerce/DocumentDelivery/DDEController?Action=showdoc&amp;DocId=Catalog+Section%7F1308389_EUROSTYLE_TERMINAL_BLOCKS%7F0607%7Fpdf%7FEnglish%7FENG_CS_1308389_EUROSTYLE_TERMINAL_BLOCKS_0607.pdf%7F2-282837-5"&gt;Datasheet&lt;/a&gt;&lt;br&gt;</description>
<gates>
<gate name="G$1" symbol="TERMBLK_2" x="0" y="0"/>
</gates>
<devices>
<device name="282837-2" package="TERMBLK_508-2N">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:24957621/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Fixed Terminal Blocks" constant="no"/>
<attribute name="DESCRIPTION" value="Fixed Terminal Blocks 5.08MM PCB MOUNT 2P" constant="no"/>
<attribute name="MANUFACTURER" value="TE Connectivity AMP Connectors" constant="no"/>
<attribute name="MPN" value="282837-2" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="-40°C to +105°C" constant="no"/>
<attribute name="PART_STATUS" value="ACTIVE" constant="no"/>
<attribute name="PITCH" value="0.200&quot; (5.08mm)" constant="no"/>
<attribute name="ROHS_COMPLIANCE" value="RoHS Compliant" constant="no"/>
<attribute name="SERIES" value="Buchanan" constant="no"/>
<attribute name="SUBCATEGORY" value="Terminal Blocks" constant="no"/>
<attribute name="TYPE" value="Through Hole; Screw - Rising Cage Clamp; Side wire entry, Horizontal with Board" constant="no"/>
<attribute name="VALUE" value="TERM-BLK-2P" constant="no"/>
</technology>
</technologies>
</device>
<device name="282834-2" package="TERMBLK_254-2N">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:24957623/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Fixed Terminal Blocks" constant="no"/>
<attribute name="DESCRIPTION" value="Fixed Terminal Blocks 2P SIDE ENTRY 2.54mm" constant="no"/>
<attribute name="MANUFACTURER" value="TE Connectivity AMP Connectors" constant="no"/>
<attribute name="MPN" value="282834-2 " constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="-40°C ~ 105°C " constant="no"/>
<attribute name="PART_STATUS" value="Active " constant="no"/>
<attribute name="PITCH" value="0.100&quot; (2.54mm) " constant="no"/>
<attribute name="ROHS_COMPLIANCE" value="RoHS Compliant " constant="no"/>
<attribute name="SERIES" value="Buchanan" constant="no"/>
<attribute name="SUBCATEGORY" value="Terminal Blocks " constant="no"/>
<attribute name="TYPE" value="Through Hole; Screw - Rising Cage Clamp; Side wire entry, Horizontal with Board " constant="no"/>
<attribute name="VALUE" value="TERM-BLK-2P" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X2" urn="urn:adsk.eagle:component:16494866/5" prefix="JP" library_version="50">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="PINHD2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X02">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22435/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Headers" constant="no"/>
<attribute name="DESCRIPTION" value="Header, Straight, 2 Position" constant="no"/>
<attribute name="MANUFACTURER" value="Generic" constant="no"/>
<attribute name="MPN" value="Generic" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="Generic" constant="no"/>
<attribute name="PART_STATUS" value="Active" constant="no"/>
<attribute name="PITCH" value="0.100&quot; (2.54mm)" constant="no"/>
<attribute name="ROHS_COMPLIANCE" value="Generic" constant="no"/>
<attribute name="SERIES" value="Generic" constant="no"/>
<attribute name="TYPE" value="Board to Board or Cable, Unshrouded, Through Hole, Straight" constant="no"/>
<attribute name="VALUE" value="PINHD-1X2" constant="no"/>
<attribute name="SUB-CATEGORY" value="Headers, Male Pins" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="1X02/90">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22437/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Headers" constant="no"/>
<attribute name="DESCRIPTION" value="Header, Right Angle, 2 Position" constant="no"/>
<attribute name="MANUFACTURER" value="Generic" constant="no"/>
<attribute name="MPN" value="Generic" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="Generic" constant="no"/>
<attribute name="PART_STATUS" value="Active" constant="no"/>
<attribute name="PITCH" value="0.100&quot; (2.54mm)" constant="no"/>
<attribute name="ROHS_COMPLIANCE" value="Generic" constant="no"/>
<attribute name="SERIES" value="Generic" constant="no"/>
<attribute name="TYPE" value="Board to Board or Cable, Unshrouded, Through Hole, Right Angle" constant="no"/>
<attribute name="VALUE" value="PINHD-1X2/90" constant="no"/>
<attribute name="SUB-CATEGORY" value="Headers, Male Pins" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X4" urn="urn:adsk.eagle:component:16494870/5" prefix="JP" library_version="50">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINHD4" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X04">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22407/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Headers" constant="no"/>
<attribute name="DESCRIPTION" value="Header, Straight, 4 Position" constant="no"/>
<attribute name="MANUFACTURER" value="Generic" constant="no"/>
<attribute name="MPN" value="Generic" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="Generic" constant="no"/>
<attribute name="PART_STATUS" value="Active" constant="no"/>
<attribute name="PITCH" value="0.100&quot; (2.54mm)" constant="no"/>
<attribute name="ROHS_COMPLIANCE" value="Generic" constant="no"/>
<attribute name="SERIES" value="Generic" constant="no"/>
<attribute name="TYPE" value="Board to Board or Cable, Unshrouded, Through Hole, Straight" constant="no"/>
<attribute name="VALUE" value="PINHD-1X4" constant="no"/>
<attribute name="SUB-CATEGORY" value="Headers, Male Pins" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="1X04/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22404/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Headers" constant="no"/>
<attribute name="DESCRIPTION" value="Header, Right Angle, 4 Position" constant="no"/>
<attribute name="MANUFACTURER" value="Generic" constant="no"/>
<attribute name="MPN" value="Generic" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="Generic" constant="no"/>
<attribute name="PART_STATUS" value="Active" constant="no"/>
<attribute name="PITCH" value="0.100&quot; (2.54mm)" constant="no"/>
<attribute name="ROHS_COMPLIANCE" value="Generic" constant="no"/>
<attribute name="SERIES" value="Generic" constant="no"/>
<attribute name="TYPE" value="Board to Board or Cable, Unshrouded, Through Hole, Right Angle" constant="no"/>
<attribute name="VALUE" value="PINHD-1X4/90" constant="no"/>
<attribute name="SUB-CATEGORY" value="Headers, Male Pins" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="B3U-1000P" urn="urn:adsk.wipprod:fs.file:vf.XJbiwRhKSp-iOlNm4yOdNw">
<description>&lt;OMRON ELECTRONIC COMPONENTS - B3U-1000P - SWITCH, SPST-NO, 0.05A, 12V, SMD&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="B3U-1000P" library_version="2">
<description>&lt;b&gt;B3U-1000P(M)&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="1.7" y="0" dx="1.7" dy="0.8" layer="1" rot="R90"/>
<smd name="2" x="-1.7" y="0" dx="1.7" dy="0.8" layer="1" rot="R90"/>
<text x="-0.461" y="-0.206" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="-0.461" y="-0.206" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.5" y1="1.25" x2="1.5" y2="1.25" width="0.2" layer="51"/>
<wire x1="1.5" y1="1.25" x2="1.5" y2="-1.25" width="0.2" layer="51"/>
<wire x1="1.5" y1="-1.25" x2="-1.5" y2="-1.25" width="0.2" layer="51"/>
<wire x1="-1.5" y1="-1.25" x2="-1.5" y2="1.25" width="0.2" layer="51"/>
<circle x="2.395" y="0.971" radius="0.1" width="0.2" layer="25"/>
<wire x1="-1.5" y1="1.25" x2="1.5" y2="1.25" width="0.2" layer="21"/>
<wire x1="-1.5" y1="-1.25" x2="1.5" y2="-1.25" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="B3U-1000P" library_version="2">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="16.51" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="16.51" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="K" x="0" y="-2.54" length="middle"/>
<pin name="A" x="0" y="0" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="B3U-1000P" prefix="S" library_version="2">
<description>&lt;b&gt;OMRON ELECTRONIC COMPONENTS - B3U-1000P - SWITCH, SPST-NO, 0.05A, 12V, SMD&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.omron.com/ecb/products/pdf/en-b3u.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="B3U-1000P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="B3U-1000P">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$1" pin="K" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="OMRON ELECTRONIC COMPONENTS - B3U-1000P - SWITCH, SPST-NO, 0.05A, 12V, SMD" constant="no"/>
<attribute name="HEIGHT" value="mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="OMRON Electronics" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="B3U-1000P" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="653-B3U-1000P" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3U-1000P?qs=AO7BQMcsEu4ip80xyf2FwA%3D%3D" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="TL1963A-33DCYR" urn="urn:adsk.wipprod:fs.file:vf.nukNfVCiQSiYwS2wA_aO-Q">
<description>&lt;1.5-A Low-Noise Fast-Transient-Response Low-Dropout Regulator&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="SOT230P700X180-4N" library_version="1">
<description>&lt;b&gt;SOT-223-4&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-3.1" y="2.3" dx="1.8" dy="0.95" layer="1"/>
<smd name="2" x="-3.1" y="0" dx="1.8" dy="0.95" layer="1"/>
<smd name="3" x="-3.1" y="-2.3" dx="1.8" dy="0.95" layer="1"/>
<smd name="4" x="3.1" y="0" dx="3.2" dy="1.8" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-4.25" y1="3.6" x2="4.25" y2="3.6" width="0.05" layer="51"/>
<wire x1="4.25" y1="3.6" x2="4.25" y2="-3.6" width="0.05" layer="51"/>
<wire x1="4.25" y1="-3.6" x2="-4.25" y2="-3.6" width="0.05" layer="51"/>
<wire x1="-4.25" y1="-3.6" x2="-4.25" y2="3.6" width="0.05" layer="51"/>
<wire x1="-1.75" y1="3.25" x2="1.75" y2="3.25" width="0.1" layer="51"/>
<wire x1="1.75" y1="3.25" x2="1.75" y2="-3.25" width="0.1" layer="51"/>
<wire x1="1.75" y1="-3.25" x2="-1.75" y2="-3.25" width="0.1" layer="51"/>
<wire x1="-1.75" y1="-3.25" x2="-1.75" y2="3.25" width="0.1" layer="51"/>
<wire x1="-1.75" y1="0.95" x2="0.55" y2="3.25" width="0.1" layer="51"/>
<wire x1="-1.75" y1="3.25" x2="1.75" y2="3.25" width="0.2" layer="21"/>
<wire x1="1.75" y1="3.25" x2="1.75" y2="-3.25" width="0.2" layer="21"/>
<wire x1="1.75" y1="-3.25" x2="-1.75" y2="-3.25" width="0.2" layer="21"/>
<wire x1="-1.75" y1="-3.25" x2="-1.75" y2="3.25" width="0.2" layer="21"/>
<wire x1="-4" y1="3.125" x2="-2.2" y2="3.125" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="TL1963A-33DCYR" library_version="1">
<wire x1="5.08" y1="2.54" x2="25.4" y2="2.54" width="0.254" layer="94"/>
<wire x1="25.4" y1="-7.62" x2="25.4" y2="2.54" width="0.254" layer="94"/>
<wire x1="25.4" y1="-7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<text x="26.67" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="26.67" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="IN" x="0" y="0" length="middle" direction="in"/>
<pin name="GND_1" x="0" y="-2.54" length="middle" direction="pwr"/>
<pin name="OUT" x="0" y="-5.08" length="middle" direction="out"/>
<pin name="GND_2" x="30.48" y="0" length="middle" direction="pwr" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TL1963A-33DCYR" prefix="PS" library_version="1">
<description>&lt;b&gt;1.5-A Low-Noise Fast-Transient-Response Low-Dropout Regulator&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://www.ti.com/lit/gpn/tl1963a"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="TL1963A-33DCYR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT230P700X180-4N">
<connects>
<connect gate="G$1" pin="GND_1" pad="2"/>
<connect gate="G$1" pin="GND_2" pad="4"/>
<connect gate="G$1" pin="IN" pad="1"/>
<connect gate="G$1" pin="OUT" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="595-TL1963A-33DCYR" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Texas-Instruments/TL1963A-33DCYR?qs=IK5e5L0zOXhRu%2FNTAfJNEA%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Texas Instruments" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="TL1963A-33DCYR" constant="no"/>
<attribute name="DESCRIPTION" value="1.5-A Low-Noise Fast-Transient-Response Low-Dropout Regulator" constant="no"/>
<attribute name="HEIGHT" value="1.8mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="XC6206P122MR-G" urn="urn:adsk.wipprod:fs.file:vf.NEs_bSMgQmembkkqPoqipw">
<description>&lt;LDO Voltage Regulators 1uA Low Quiescent 3 Terminal, Low ESR Cap. Compatible, Voltage Regulator&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="SOT95P280X130-3N" library_version="1">
<description>&lt;b&gt;SOT-23&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-1.4" y="0.95" dx="0.9" dy="0.6" layer="1"/>
<smd name="2" x="-1.4" y="-0.95" dx="0.9" dy="0.6" layer="1"/>
<smd name="3" x="1.4" y="0" dx="0.9" dy="0.6" layer="1"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-2.1" y1="1.8" x2="2.1" y2="1.8" width="0.05" layer="51"/>
<wire x1="2.1" y1="1.8" x2="2.1" y2="-1.8" width="0.05" layer="51"/>
<wire x1="2.1" y1="-1.8" x2="-2.1" y2="-1.8" width="0.05" layer="51"/>
<wire x1="-2.1" y1="-1.8" x2="-2.1" y2="1.8" width="0.05" layer="51"/>
<wire x1="-0.825" y1="1.45" x2="0.825" y2="1.45" width="0.1" layer="51"/>
<wire x1="0.825" y1="1.45" x2="0.825" y2="-1.45" width="0.1" layer="51"/>
<wire x1="0.825" y1="-1.45" x2="-0.825" y2="-1.45" width="0.1" layer="51"/>
<wire x1="-0.825" y1="-1.45" x2="-0.825" y2="1.45" width="0.1" layer="51"/>
<wire x1="-0.825" y1="0.5" x2="0.125" y2="1.45" width="0.1" layer="51"/>
<wire x1="-0.6" y1="1.45" x2="0.6" y2="1.45" width="0.2" layer="21"/>
<wire x1="0.6" y1="1.45" x2="0.6" y2="-1.45" width="0.2" layer="21"/>
<wire x1="0.6" y1="-1.45" x2="-0.6" y2="-1.45" width="0.2" layer="21"/>
<wire x1="-0.6" y1="-1.45" x2="-0.6" y2="1.45" width="0.2" layer="21"/>
<wire x1="-1.85" y1="1.5" x2="-0.95" y2="1.5" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="XC6206P122MR-G" library_version="1">
<wire x1="5.08" y1="2.54" x2="22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="-5.08" x2="22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="24.13" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="24.13" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="VSS" x="0" y="0" length="middle"/>
<pin name="VOUT" x="0" y="-2.54" length="middle"/>
<pin name="VIN" x="27.94" y="0" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="XC6206P122MR-G" prefix="IC" library_version="1">
<description>&lt;b&gt;LDO Voltage Regulators 1uA Low Quiescent 3 Terminal, Low ESR Cap. Compatible, Voltage Regulator&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.torexsemi.com/file/xc6206/XC6206.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="XC6206P122MR-G" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT95P280X130-3N">
<connects>
<connect gate="G$1" pin="VIN" pad="3"/>
<connect gate="G$1" pin="VOUT" pad="2"/>
<connect gate="G$1" pin="VSS" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="865-XC6206P122MR-G" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Torex-Semiconductor/XC6206P122MR-G?qs=AsjdqWjXhJ%2F35%2FU%2FZk2JYg%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Torex" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="XC6206P122MR-G" constant="no"/>
<attribute name="DESCRIPTION" value="LDO Voltage Regulators 1uA Low Quiescent 3 Terminal, Low ESR Cap. Compatible, Voltage Regulator" constant="no"/>
<attribute name="HEIGHT" value="1.3mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="XC6206P282MR-G" urn="urn:adsk.wipprod:fs.file:vf.dxXTFAhhT2yqCCWQlP4POQ">
<description>&lt;LDO Voltage Regulators 1uA Low Quiescent 3 Terminal, Low ESR Cap. Compatible, Voltage Regulator&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="SOT95P280X130-3N" library_version="1">
<description>&lt;b&gt;XC6206P282MR-G&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-1.4" y="0.95" dx="0.9" dy="0.6" layer="1"/>
<smd name="2" x="-1.4" y="-0.95" dx="0.9" dy="0.6" layer="1"/>
<smd name="3" x="1.4" y="0" dx="0.9" dy="0.6" layer="1"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-2.1" y1="1.8" x2="2.1" y2="1.8" width="0.05" layer="51"/>
<wire x1="2.1" y1="1.8" x2="2.1" y2="-1.8" width="0.05" layer="51"/>
<wire x1="2.1" y1="-1.8" x2="-2.1" y2="-1.8" width="0.05" layer="51"/>
<wire x1="-2.1" y1="-1.8" x2="-2.1" y2="1.8" width="0.05" layer="51"/>
<wire x1="-0.825" y1="1.45" x2="0.825" y2="1.45" width="0.1" layer="51"/>
<wire x1="0.825" y1="1.45" x2="0.825" y2="-1.45" width="0.1" layer="51"/>
<wire x1="0.825" y1="-1.45" x2="-0.825" y2="-1.45" width="0.1" layer="51"/>
<wire x1="-0.825" y1="-1.45" x2="-0.825" y2="1.45" width="0.1" layer="51"/>
<wire x1="-0.825" y1="0.5" x2="0.125" y2="1.45" width="0.1" layer="51"/>
<wire x1="-0.6" y1="1.45" x2="0.6" y2="1.45" width="0.2" layer="21"/>
<wire x1="0.6" y1="1.45" x2="0.6" y2="-1.45" width="0.2" layer="21"/>
<wire x1="0.6" y1="-1.45" x2="-0.6" y2="-1.45" width="0.2" layer="21"/>
<wire x1="-0.6" y1="-1.45" x2="-0.6" y2="1.45" width="0.2" layer="21"/>
<wire x1="-1.85" y1="1.5" x2="-0.95" y2="1.5" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="XC6206P282MR-G" library_version="1">
<wire x1="5.08" y1="2.54" x2="22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="-5.08" x2="22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="24.13" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="24.13" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="VSS" x="0" y="0" length="middle"/>
<pin name="VOUT" x="0" y="-2.54" length="middle"/>
<pin name="VIN" x="27.94" y="0" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="XC6206P282MR-G" prefix="IC" library_version="1">
<description>&lt;b&gt;LDO Voltage Regulators 1uA Low Quiescent 3 Terminal, Low ESR Cap. Compatible, Voltage Regulator&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.torexsemi.com/file/xc6206/XC6206.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="XC6206P282MR-G" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT95P280X130-3N">
<connects>
<connect gate="G$1" pin="VIN" pad="3"/>
<connect gate="G$1" pin="VOUT" pad="2"/>
<connect gate="G$1" pin="VSS" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="865-XC6206P282MR-G" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Torex-Semiconductor/XC6206P282MR-G?qs=AsjdqWjXhJ%2Fpd3DOBopSeA%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Torex" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="XC6206P282MR-G" constant="no"/>
<attribute name="DESCRIPTION" value="LDO Voltage Regulators 1uA Low Quiescent 3 Terminal, Low ESR Cap. Compatible, Voltage Regulator" constant="no"/>
<attribute name="HEIGHT" value="1.3mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Capacitor" urn="urn:adsk.eagle:library:16290819">
<description>&lt;B&gt;Capacitors - Fixed, Variable, Trimmers</description>
<packages>
<package name="CAPC1005X60" urn="urn:adsk.eagle:footprint:16290849/5" library_version="19">
<description>Chip, 1.00 X 0.50 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.00 X 0.50 X 0.60 mm&lt;/p&gt;</description>
<wire x1="0.55" y1="0.6286" x2="-0.55" y2="0.6286" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.6286" x2="-0.55" y2="-0.6286" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.3" x2="-0.55" y2="-0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="-0.3" x2="-0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="0.3" x2="0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="0.55" y1="0.3" x2="0.55" y2="-0.3" width="0.12" layer="51"/>
<smd name="1" x="-0.4846" y="0" dx="0.56" dy="0.6291" layer="1"/>
<smd name="2" x="0.4846" y="0" dx="0.56" dy="0.6291" layer="1"/>
<text x="0" y="1.2636" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.2636" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC1110X102" urn="urn:adsk.eagle:footprint:16290845/5" library_version="19">
<description>Chip, 1.17 X 1.02 X 1.02 mm body
&lt;p&gt;Chip package with body size 1.17 X 1.02 X 1.02 mm&lt;/p&gt;</description>
<wire x1="0.66" y1="0.9552" x2="-0.66" y2="0.9552" width="0.127" layer="21"/>
<wire x1="0.66" y1="-0.9552" x2="-0.66" y2="-0.9552" width="0.127" layer="21"/>
<wire x1="0.66" y1="-0.635" x2="-0.66" y2="-0.635" width="0.12" layer="51"/>
<wire x1="-0.66" y1="-0.635" x2="-0.66" y2="0.635" width="0.12" layer="51"/>
<wire x1="-0.66" y1="0.635" x2="0.66" y2="0.635" width="0.12" layer="51"/>
<wire x1="0.66" y1="0.635" x2="0.66" y2="-0.635" width="0.12" layer="51"/>
<smd name="1" x="-0.5388" y="0" dx="0.6626" dy="1.2823" layer="1"/>
<smd name="2" x="0.5388" y="0" dx="0.6626" dy="1.2823" layer="1"/>
<text x="0" y="1.5902" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.5902" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC1608X85" urn="urn:adsk.eagle:footprint:16290847/5" library_version="19">
<description>Chip, 1.60 X 0.80 X 0.85 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.80 X 0.85 mm&lt;/p&gt;</description>
<wire x1="0.875" y1="0.7991" x2="-0.875" y2="0.7991" width="0.127" layer="21"/>
<wire x1="0.875" y1="-0.7991" x2="-0.875" y2="-0.7991" width="0.127" layer="21"/>
<wire x1="0.875" y1="-0.475" x2="-0.875" y2="-0.475" width="0.12" layer="51"/>
<wire x1="-0.875" y1="-0.475" x2="-0.875" y2="0.475" width="0.12" layer="51"/>
<wire x1="-0.875" y1="0.475" x2="0.875" y2="0.475" width="0.12" layer="51"/>
<wire x1="0.875" y1="0.475" x2="0.875" y2="-0.475" width="0.12" layer="51"/>
<smd name="1" x="-0.7746" y="0" dx="0.9209" dy="0.9702" layer="1"/>
<smd name="2" x="0.7746" y="0" dx="0.9209" dy="0.9702" layer="1"/>
<text x="0" y="1.4341" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.4341" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC2012X110" urn="urn:adsk.eagle:footprint:16290848/5" library_version="19">
<description>Chip, 2.00 X 1.25 X 1.10 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 1.10 mm&lt;/p&gt;</description>
<wire x1="1.1" y1="1.0467" x2="-1.1" y2="1.0467" width="0.127" layer="21"/>
<wire x1="1.1" y1="-1.0467" x2="-1.1" y2="-1.0467" width="0.127" layer="21"/>
<wire x1="1.1" y1="-0.725" x2="-1.1" y2="-0.725" width="0.12" layer="51"/>
<wire x1="-1.1" y1="-0.725" x2="-1.1" y2="0.725" width="0.12" layer="51"/>
<wire x1="-1.1" y1="0.725" x2="1.1" y2="0.725" width="0.12" layer="51"/>
<wire x1="1.1" y1="0.725" x2="1.1" y2="-0.725" width="0.12" layer="51"/>
<smd name="1" x="-0.8754" y="0" dx="1.1646" dy="1.4653" layer="1"/>
<smd name="2" x="0.8754" y="0" dx="1.1646" dy="1.4653" layer="1"/>
<text x="0" y="1.6817" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.6817" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC3216X135" urn="urn:adsk.eagle:footprint:16290836/5" library_version="19">
<description>Chip, 3.20 X 1.60 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 1.35 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.2217" x2="-1.7" y2="1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-1.2217" x2="-1.7" y2="-1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<text x="0" y="1.8567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC3225X135" urn="urn:adsk.eagle:footprint:16290843/5" library_version="19">
<description>Chip, 3.20 X 2.50 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.50 X 1.35 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.6717" x2="-1.7" y2="1.6717" width="0.127" layer="21"/>
<wire x1="1.7" y1="-1.6717" x2="-1.7" y2="-1.6717" width="0.12" layer="21"/>
<wire x1="1.7" y1="-1.35" x2="-1.7" y2="-1.35" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-1.35" x2="-1.7" y2="1.35" width="0.12" layer="51"/>
<wire x1="-1.7" y1="1.35" x2="1.7" y2="1.35" width="0.12" layer="51"/>
<wire x1="1.7" y1="1.35" x2="1.7" y2="-1.35" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="2.7153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="2.7153" layer="1"/>
<text x="0" y="2.3067" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.3067" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC4532X135" urn="urn:adsk.eagle:footprint:16290841/5" library_version="19">
<description>Chip, 4.50 X 3.20 X 1.35 mm body
&lt;p&gt;Chip package with body size 4.50 X 3.20 X 1.35 mm&lt;/p&gt;</description>
<wire x1="2.4" y1="2.0217" x2="-2.4" y2="2.0217" width="0.127" layer="21"/>
<wire x1="2.4" y1="-2.0217" x2="-2.4" y2="-2.0217" width="0.127" layer="21"/>
<wire x1="2.4" y1="-1.7" x2="-2.4" y2="-1.7" width="0.12" layer="51"/>
<wire x1="-2.4" y1="-1.7" x2="-2.4" y2="1.7" width="0.12" layer="51"/>
<wire x1="-2.4" y1="1.7" x2="2.4" y2="1.7" width="0.12" layer="51"/>
<wire x1="2.4" y1="1.7" x2="2.4" y2="-1.7" width="0.12" layer="51"/>
<smd name="1" x="-2.0565" y="0" dx="1.3973" dy="3.4153" layer="1"/>
<smd name="2" x="2.0565" y="0" dx="1.3973" dy="3.4153" layer="1"/>
<text x="0" y="2.6567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.6567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM3216X180" urn="urn:adsk.eagle:footprint:16290835/5" library_version="19">
<description>Molded Body, 3.20 X 1.60 X 1.80 mm body
&lt;p&gt;Molded Body package with body size 3.20 X 1.60 X 1.80 mm&lt;/p&gt;</description>
<wire x1="-1.7" y1="0.9084" x2="1.7" y2="0.9084" width="0.127" layer="21"/>
<wire x1="-1.7" y1="-0.9084" x2="1.7" y2="-0.9084" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.3099" y="0" dx="1.7955" dy="1.1887" layer="1"/>
<smd name="2" x="1.3099" y="0" dx="1.7955" dy="1.1887" layer="1"/>
<text x="0" y="1.5434" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.5434" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM3528X210" urn="urn:adsk.eagle:footprint:16290844/5" library_version="19">
<description>Molded Body, 3.50 X 2.80 X 2.10 mm body
&lt;p&gt;Molded Body package with body size 3.50 X 2.80 X 2.10 mm&lt;/p&gt;</description>
<wire x1="-1.85" y1="1.5" x2="1.85" y2="1.5" width="0.127" layer="21"/>
<wire x1="-1.85" y1="-1.5" x2="1.85" y2="-1.5" width="0.127" layer="21"/>
<wire x1="1.85" y1="-1.5" x2="-1.85" y2="-1.5" width="0.12" layer="51"/>
<wire x1="-1.85" y1="-1.5" x2="-1.85" y2="1.5" width="0.12" layer="51"/>
<wire x1="-1.85" y1="1.5" x2="1.85" y2="1.5" width="0.12" layer="51"/>
<wire x1="1.85" y1="1.5" x2="1.85" y2="-1.5" width="0.12" layer="51"/>
<smd name="1" x="-1.4599" y="0" dx="1.7955" dy="2.2036" layer="1"/>
<smd name="2" x="1.4599" y="0" dx="1.7955" dy="2.2036" layer="1"/>
<text x="0" y="2.135" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.135" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM6032X280" urn="urn:adsk.eagle:footprint:16290839/5" library_version="19">
<description>Molded Body, 6.00 X 3.20 X 2.80 mm body
&lt;p&gt;Molded Body package with body size 6.00 X 3.20 X 2.80 mm&lt;/p&gt;</description>
<wire x1="-3.15" y1="1.75" x2="3.15" y2="1.75" width="0.127" layer="21"/>
<wire x1="-3.15" y1="-1.75" x2="3.15" y2="-1.75" width="0.127" layer="21"/>
<wire x1="3.15" y1="-1.75" x2="-3.15" y2="-1.75" width="0.12" layer="51"/>
<wire x1="-3.15" y1="-1.75" x2="-3.15" y2="1.75" width="0.12" layer="51"/>
<wire x1="-3.15" y1="1.75" x2="3.15" y2="1.75" width="0.12" layer="51"/>
<wire x1="3.15" y1="1.75" x2="3.15" y2="-1.75" width="0.12" layer="51"/>
<smd name="1" x="-2.4712" y="0" dx="2.368" dy="2.2036" layer="1"/>
<smd name="2" x="2.4712" y="0" dx="2.368" dy="2.2036" layer="1"/>
<text x="0" y="2.385" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.385" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPM7343X310" urn="urn:adsk.eagle:footprint:16290840/5" library_version="19">
<description>Molded Body, 7.30 X 4.30 X 3.10 mm body
&lt;p&gt;Molded Body package with body size 7.30 X 4.30 X 3.10 mm&lt;/p&gt;</description>
<wire x1="-3.8" y1="2.3" x2="3.8" y2="2.3" width="0.127" layer="21"/>
<wire x1="-3.8" y1="-2.3" x2="3.8" y2="-2.3" width="0.127" layer="21"/>
<wire x1="3.8" y1="-2.3" x2="-3.8" y2="-2.3" width="0.12" layer="51"/>
<wire x1="-3.8" y1="-2.3" x2="-3.8" y2="2.3" width="0.12" layer="51"/>
<wire x1="-3.8" y1="2.3" x2="3.8" y2="2.3" width="0.12" layer="51"/>
<wire x1="3.8" y1="2.3" x2="3.8" y2="-2.3" width="0.12" layer="51"/>
<smd name="1" x="-3.1212" y="0" dx="2.368" dy="2.4036" layer="1"/>
<smd name="2" x="3.1212" y="0" dx="2.368" dy="2.4036" layer="1"/>
<text x="0" y="2.935" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.935" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPC4564X110" urn="urn:adsk.eagle:footprint:16290837/5" library_version="19">
<description>Chip, 4.50 X 6.40 X 1.10 mm body
&lt;p&gt;Chip package with body size 4.50 X 6.40 X 1.10 mm&lt;/p&gt;</description>
<wire x1="2.4" y1="3.7179" x2="-2.4" y2="3.7179" width="0.127" layer="21"/>
<wire x1="2.4" y1="-3.7179" x2="-2.4" y2="-3.7179" width="0.127" layer="21"/>
<wire x1="2.4" y1="-3.4" x2="-2.4" y2="-3.4" width="0.12" layer="51"/>
<wire x1="-2.4" y1="-3.4" x2="-2.4" y2="3.4" width="0.12" layer="51"/>
<wire x1="-2.4" y1="3.4" x2="2.4" y2="3.4" width="0.12" layer="51"/>
<wire x1="2.4" y1="3.4" x2="2.4" y2="-3.4" width="0.12" layer="51"/>
<smd name="1" x="-2.0565" y="0" dx="1.3973" dy="6.8078" layer="1"/>
<smd name="2" x="2.0565" y="0" dx="1.3973" dy="6.8078" layer="1"/>
<text x="0" y="4.3529" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-4.3529" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPRD550W60D1025H1250B" urn="urn:adsk.eagle:footprint:16290829/5" library_version="19">
<description>Radial Non-Polarized Capacitor, 5.50 mm pitch, 10.25 mm body diameter, 12.50 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 5.50 mm pitch (lead spacing), 0.60 mm lead diameter, 10.25 mm body diameter and 12.50 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="5.25" width="0.127" layer="21"/>
<circle x="0" y="0" radius="5.25" width="0.12" layer="51"/>
<pad name="1" x="-2.75" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="2.75" y="0" drill="0.8" diameter="1.4"/>
<text x="0" y="5.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-5.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPRD2261W240D5080H5555B" urn="urn:adsk.eagle:footprint:16290850/5" library_version="19">
<description>Radial Non-Polarized Capacitor, 22.61 mm pitch, 50.80 mm body diameter, 55.55 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 22.61 mm pitch (lead spacing), 2.40 mm lead diameter, 50.80 mm body diameter and 55.55 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="25.79" width="0.127" layer="21"/>
<circle x="0" y="0" radius="25.79" width="0.12" layer="51"/>
<pad name="1" x="-11.305" y="0" drill="2.6" diameter="3.9"/>
<pad name="2" x="11.305" y="0" drill="2.6" diameter="3.9"/>
<text x="0" y="26.425" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-26.425" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="CAPC1005X60" urn="urn:adsk.eagle:package:16290895/5" type="model">
<description>Chip, 1.00 X 0.50 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.00 X 0.50 X 0.60 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC1005X60"/>
</packageinstances>
</package3d>
<package3d name="CAPC1110X102" urn="urn:adsk.eagle:package:16290904/5" type="model">
<description>Chip, 1.17 X 1.02 X 1.02 mm body
&lt;p&gt;Chip package with body size 1.17 X 1.02 X 1.02 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC1110X102"/>
</packageinstances>
</package3d>
<package3d name="CAPC1608X85" urn="urn:adsk.eagle:package:16290898/5" type="model">
<description>Chip, 1.60 X 0.80 X 0.85 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.80 X 0.85 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC1608X85"/>
</packageinstances>
</package3d>
<package3d name="CAPC2012X110" urn="urn:adsk.eagle:package:16290897/5" type="model">
<description>Chip, 2.00 X 1.25 X 1.10 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 1.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC2012X110"/>
</packageinstances>
</package3d>
<package3d name="CAPC3216X135" urn="urn:adsk.eagle:package:16290893/5" type="model">
<description>Chip, 3.20 X 1.60 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 1.35 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC3216X135"/>
</packageinstances>
</package3d>
<package3d name="CAPC3225X135" urn="urn:adsk.eagle:package:16290903/5" type="model">
<description>Chip, 3.20 X 2.50 X 1.35 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.50 X 1.35 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC3225X135"/>
</packageinstances>
</package3d>
<package3d name="CAPC4532X135" urn="urn:adsk.eagle:package:16290900/5" type="model">
<description>Chip, 4.50 X 3.20 X 1.35 mm body
&lt;p&gt;Chip package with body size 4.50 X 3.20 X 1.35 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC4532X135"/>
</packageinstances>
</package3d>
<package3d name="CAPM3216X180" urn="urn:adsk.eagle:package:16290894/5" type="model">
<description>Molded Body, 3.20 X 1.60 X 1.80 mm body
&lt;p&gt;Molded Body package with body size 3.20 X 1.60 X 1.80 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM3216X180"/>
</packageinstances>
</package3d>
<package3d name="CAPM3528X210" urn="urn:adsk.eagle:package:16290902/5" type="model">
<description>Molded Body, 3.50 X 2.80 X 2.10 mm body
&lt;p&gt;Molded Body package with body size 3.50 X 2.80 X 2.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM3528X210"/>
</packageinstances>
</package3d>
<package3d name="CAPM6032X280" urn="urn:adsk.eagle:package:16290896/5" type="model">
<description>Molded Body, 6.00 X 3.20 X 2.80 mm body
&lt;p&gt;Molded Body package with body size 6.00 X 3.20 X 2.80 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM6032X280"/>
</packageinstances>
</package3d>
<package3d name="CAPM7343X310" urn="urn:adsk.eagle:package:16290891/5" type="model">
<description>Molded Body, 7.30 X 4.30 X 3.10 mm body
&lt;p&gt;Molded Body package with body size 7.30 X 4.30 X 3.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPM7343X310"/>
</packageinstances>
</package3d>
<package3d name="CAPC4564X110L" urn="urn:adsk.eagle:package:16290887/6" type="model">
<description>Chip, 4.50 X 6.40 X 1.10 mm body
&lt;p&gt;Chip package with body size 4.50 X 6.40 X 1.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPC4564X110"/>
</packageinstances>
</package3d>
<package3d name="CAPRD550W60D1025H1250B" urn="urn:adsk.eagle:package:16290858/5" type="model">
<description>Radial Non-Polarized Capacitor, 5.50 mm pitch, 10.25 mm body diameter, 12.50 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 5.50 mm pitch (lead spacing), 0.60 mm lead diameter, 10.25 mm body diameter and 12.50 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPRD550W60D1025H1250B"/>
</packageinstances>
</package3d>
<package3d name="CAPRD2261W240D5080H5555B" urn="urn:adsk.eagle:package:16290864/5" type="model">
<description>Radial Non-Polarized Capacitor, 22.61 mm pitch, 50.80 mm body diameter, 55.55 mm body height
&lt;p&gt;Radial Non-Polarized Capacitor package with 22.61 mm pitch (lead spacing), 2.40 mm lead diameter, 50.80 mm body diameter and 55.55 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPRD2261W240D5080H5555B"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="C-US" urn="urn:adsk.eagle:symbol:16290822/1" library_version="19">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202"/>
<wire x1="-2.4668" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.373024"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="C" urn="urn:adsk.eagle:symbol:16290820/1" library_version="19">
<description>Capacitor</description>
<rectangle x1="-2.032" y1="-2.032" x2="2.032" y2="-1.524" layer="94"/>
<rectangle x1="-2.032" y1="-1.016" x2="2.032" y2="-0.508" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-2.032" width="0.1524" layer="94"/>
<pin name="1" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
<text x="2.54" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="97">&gt;SPICEMODEL</text>
<text x="2.54" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="2.54" y="-5.08" size="1.778" layer="97">&gt;SPICEEXTRA</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="C-US" urn="urn:adsk.eagle:component:16290907/8" prefix="C" uservalue="yes" library_version="19">
<description>&lt;B&gt;Capacitor - ANSI</description>
<gates>
<gate name="G$1" symbol="C-US" x="0" y="0"/>
</gates>
<devices>
<device name="CHIP-0402(1005-METRIC)" package="CAPC1005X60">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290895/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0504(1310-METRIC)" package="CAPC1110X102">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290904/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0603(1608-METRIC)" package="CAPC1608X85">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290898/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0805(2012-METRIC)" package="CAPC2012X110">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290897/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1206(3216-METRIC)" package="CAPC3216X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290893/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1210(3225-METRIC)" package="CAPC3225X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290903/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1812(4532-METRIC)" package="CAPC4532X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290900/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1206(3216-METRIC)" package="CAPM3216X180">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290894/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1411(3528-METRIC)" package="CAPM3528X210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290902/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2412(6032-METRIC)" package="CAPM6032X280">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290896/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2917(7343-METRIC)" package="CAPM7343X310">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290891/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1825(4564-METRIC)" package="CAPC4564X110">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290887/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-12.5MM-DIA" package="CAPRD550W60D1025H1250B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290858/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-55.5MM-DIA" package="CAPRD2261W240D5080H5555B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290864/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="C">
<pinmap gate="G$1" pin="1" pinorder="1"/>
<pinmap gate="G$1" pin="2" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
<deviceset name="C" urn="urn:adsk.eagle:component:16290909/9" prefix="C" uservalue="yes" library_version="19">
<description>&lt;B&gt;Capacitor - Generic</description>
<gates>
<gate name="G$1" symbol="C" x="0" y="0"/>
</gates>
<devices>
<device name="CHIP-0402(1005-METRIC)" package="CAPC1005X60">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290895/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0504(1310-METRIC)" package="CAPC1110X102">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290904/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0603(1608-METRIC)" package="CAPC1608X85">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290898/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0805(2012-METRIC)" package="CAPC2012X110">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290897/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1206(3216-METRIC)" package="CAPC3216X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290893/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1210(3225-METRIC)" package="CAPC3225X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290903/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1812(4532-METRIC)" package="CAPC4532X135">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290900/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1206(3216-METRIC)" package="CAPM3216X180">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290894/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1411(3528-METRIC)" package="CAPM3528X210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290902/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2412(6032-METRIC)" package="CAPM6032X280">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290896/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2917(7343-METRIC)" package="CAPM7343X310">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290891/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1825(4564-METRIC)" package="CAPC4564X110">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290887/6"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-12.5MM-DIA" package="CAPRD550W60D1025H1250B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290858/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-55.5MM-DIA" package="CAPRD2261W240D5080H5555B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290864/5"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="C">
<pinmap gate="G$1" pin="1" pinorder="1"/>
<pinmap gate="G$1" pin="2" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
</devicesets>
</library>
<library name="ESP32-S3-WROOM-1U-N16R8" urn="urn:adsk.wipprod:fs.file:vf.cnL6V3VESOau68oAUQhTdg">
<description>&lt;WiFi Modules - 802.11 [Engineering Samples] SMD Module, ESP32-S3R8, 8 MB Octal PSRAM Die, 16 MB Quad SPI Flash, IPEX Antenna Connector&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="ESP32S3WROOM1UN16R8" library_version="1">
<description>&lt;b&gt;ESP32-S3-WROOM-1U-N16R8&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-8.75" y="8.41" dx="1.5" dy="0.9" layer="1"/>
<smd name="2" x="-8.75" y="7.14" dx="1.5" dy="0.9" layer="1"/>
<smd name="3" x="-8.75" y="5.87" dx="1.5" dy="0.9" layer="1"/>
<smd name="4" x="-8.75" y="4.6" dx="1.5" dy="0.9" layer="1"/>
<smd name="5" x="-8.75" y="3.33" dx="1.5" dy="0.9" layer="1"/>
<smd name="6" x="-8.75" y="2.06" dx="1.5" dy="0.9" layer="1"/>
<smd name="7" x="-8.75" y="0.79" dx="1.5" dy="0.9" layer="1"/>
<smd name="8" x="-8.75" y="-0.48" dx="1.5" dy="0.9" layer="1"/>
<smd name="9" x="-8.75" y="-1.75" dx="1.5" dy="0.9" layer="1"/>
<smd name="10" x="-8.75" y="-3.02" dx="1.5" dy="0.9" layer="1"/>
<smd name="11" x="-8.75" y="-4.29" dx="1.5" dy="0.9" layer="1"/>
<smd name="12" x="-8.75" y="-5.56" dx="1.5" dy="0.9" layer="1"/>
<smd name="13" x="-8.75" y="-6.83" dx="1.5" dy="0.9" layer="1"/>
<smd name="14" x="-8.75" y="-8.1" dx="1.5" dy="0.9" layer="1"/>
<smd name="15" x="-6.985" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="16" x="-5.715" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="17" x="-4.445" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="18" x="-3.175" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="19" x="-1.905" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="20" x="-0.635" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="21" x="0.635" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="22" x="1.905" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="23" x="3.175" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="24" x="4.445" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="25" x="5.715" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="26" x="6.985" y="-9.35" dx="1.5" dy="0.9" layer="1" rot="R90"/>
<smd name="27" x="8.75" y="-8.1" dx="1.5" dy="0.9" layer="1"/>
<smd name="28" x="8.75" y="-6.83" dx="1.5" dy="0.9" layer="1"/>
<smd name="29" x="8.75" y="-5.56" dx="1.5" dy="0.9" layer="1"/>
<smd name="30" x="8.75" y="-4.29" dx="1.5" dy="0.9" layer="1"/>
<smd name="31" x="8.75" y="-3.02" dx="1.5" dy="0.9" layer="1"/>
<smd name="32" x="8.75" y="-1.75" dx="1.5" dy="0.9" layer="1"/>
<smd name="33" x="8.75" y="-0.48" dx="1.5" dy="0.9" layer="1"/>
<smd name="34" x="8.75" y="0.79" dx="1.5" dy="0.9" layer="1"/>
<smd name="35" x="8.75" y="2.06" dx="1.5" dy="0.9" layer="1"/>
<smd name="36" x="8.75" y="3.33" dx="1.5" dy="0.9" layer="1"/>
<smd name="37" x="8.75" y="4.6" dx="1.5" dy="0.9" layer="1"/>
<smd name="38" x="8.75" y="5.87" dx="1.5" dy="0.9" layer="1"/>
<smd name="39" x="8.75" y="7.14" dx="1.5" dy="0.9" layer="1"/>
<smd name="40" x="8.75" y="8.41" dx="1.5" dy="0.9" layer="1"/>
<smd name="41" x="-1.5" y="0.69" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="42" x="-1.5" y="2.09" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="43" x="-2.9" y="2.09" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="44" x="-2.9" y="0.69" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="45" x="-2.9" y="-0.71" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="46" x="-1.5" y="-0.71" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="47" x="-0.1" y="-0.71" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="48" x="-0.1" y="0.69" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<smd name="49" x="-0.1" y="2.09" dx="0.9" dy="0.9" layer="1" rot="R90"/>
<text x="0" y="-0.25" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="-0.25" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-9" y1="9.6" x2="9" y2="9.6" width="0.1" layer="51"/>
<wire x1="9" y1="9.6" x2="9" y2="-9.6" width="0.1" layer="51"/>
<wire x1="9" y1="-9.6" x2="-9" y2="-9.6" width="0.1" layer="51"/>
<wire x1="-9" y1="-9.6" x2="-9" y2="9.6" width="0.1" layer="51"/>
<wire x1="-10.5" y1="10.6" x2="10.5" y2="10.6" width="0.1" layer="51"/>
<wire x1="10.5" y1="10.6" x2="10.5" y2="-11.1" width="0.1" layer="51"/>
<wire x1="10.5" y1="-11.1" x2="-10.5" y2="-11.1" width="0.1" layer="51"/>
<wire x1="-10.5" y1="-11.1" x2="-10.5" y2="10.6" width="0.1" layer="51"/>
<wire x1="-10" y1="8.4" x2="-9.9" y2="8.4" width="0.1" layer="21" curve="180"/>
<wire x1="-9.9" y1="8.4" x2="-10" y2="8.4" width="0.1" layer="21" curve="180"/>
<wire x1="-9" y1="9.6" x2="9" y2="9.6" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="ESP32-S3-WROOM-1U-N16R8" library_version="1">
<wire x1="5.08" y1="2.54" x2="27.94" y2="2.54" width="0.254" layer="94"/>
<wire x1="27.94" y1="-63.5" x2="27.94" y2="2.54" width="0.254" layer="94"/>
<wire x1="27.94" y1="-63.5" x2="5.08" y2="-63.5" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-63.5" width="0.254" layer="94"/>
<text x="29.21" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="29.21" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="GND_1" x="0" y="0" length="middle"/>
<pin name="3V3" x="0" y="-2.54" length="middle"/>
<pin name="EN" x="0" y="-5.08" length="middle"/>
<pin name="IO4" x="0" y="-7.62" length="middle"/>
<pin name="IO5" x="0" y="-10.16" length="middle"/>
<pin name="IO6" x="0" y="-12.7" length="middle"/>
<pin name="IO7" x="0" y="-15.24" length="middle"/>
<pin name="IO15" x="0" y="-17.78" length="middle"/>
<pin name="IO16" x="0" y="-20.32" length="middle"/>
<pin name="IO17" x="0" y="-22.86" length="middle"/>
<pin name="IO18" x="0" y="-25.4" length="middle"/>
<pin name="IO8" x="0" y="-27.94" length="middle"/>
<pin name="IO19" x="0" y="-30.48" length="middle"/>
<pin name="IO20" x="0" y="-33.02" length="middle"/>
<pin name="IO3" x="0" y="-35.56" length="middle"/>
<pin name="IO46" x="0" y="-38.1" length="middle"/>
<pin name="IO9" x="0" y="-40.64" length="middle"/>
<pin name="IO10" x="0" y="-43.18" length="middle"/>
<pin name="IO11" x="0" y="-45.72" length="middle"/>
<pin name="IO12" x="0" y="-48.26" length="middle"/>
<pin name="IO13" x="0" y="-50.8" length="middle"/>
<pin name="IO14" x="0" y="-53.34" length="middle"/>
<pin name="IO21" x="0" y="-55.88" length="middle"/>
<pin name="IO47" x="0" y="-58.42" length="middle"/>
<pin name="IO48" x="0" y="-60.96" length="middle"/>
<pin name="IO45" x="33.02" y="0" length="middle" rot="R180"/>
<pin name="IO0" x="33.02" y="-2.54" length="middle" rot="R180"/>
<pin name="IO35" x="33.02" y="-5.08" length="middle" rot="R180"/>
<pin name="IO36" x="33.02" y="-7.62" length="middle" rot="R180"/>
<pin name="IO37" x="33.02" y="-10.16" length="middle" rot="R180"/>
<pin name="IO38" x="33.02" y="-12.7" length="middle" rot="R180"/>
<pin name="IO39" x="33.02" y="-15.24" length="middle" rot="R180"/>
<pin name="IO40" x="33.02" y="-17.78" length="middle" rot="R180"/>
<pin name="IO41" x="33.02" y="-20.32" length="middle" rot="R180"/>
<pin name="IO42" x="33.02" y="-22.86" length="middle" rot="R180"/>
<pin name="RXD0" x="33.02" y="-25.4" length="middle" rot="R180"/>
<pin name="TXD0" x="33.02" y="-27.94" length="middle" rot="R180"/>
<pin name="IO2" x="33.02" y="-30.48" length="middle" rot="R180"/>
<pin name="IO1" x="33.02" y="-33.02" length="middle" rot="R180"/>
<pin name="GND_2" x="33.02" y="-35.56" length="middle" rot="R180"/>
<pin name="GND_3" x="33.02" y="-38.1" length="middle" rot="R180"/>
<pin name="GND_4" x="33.02" y="-40.64" length="middle" rot="R180"/>
<pin name="GND_5" x="33.02" y="-43.18" length="middle" rot="R180"/>
<pin name="GND_6" x="33.02" y="-45.72" length="middle" rot="R180"/>
<pin name="GND_7" x="33.02" y="-48.26" length="middle" rot="R180"/>
<pin name="GND_8" x="33.02" y="-50.8" length="middle" rot="R180"/>
<pin name="GND_9" x="33.02" y="-53.34" length="middle" rot="R180"/>
<pin name="GND_10" x="33.02" y="-55.88" length="middle" rot="R180"/>
<pin name="GND_11" x="33.02" y="-58.42" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32-S3-WROOM-1U-N16R8" prefix="IC" library_version="1">
<description>&lt;b&gt;WiFi Modules - 802.11 [Engineering Samples] SMD Module, ESP32-S3R8, 8 MB Octal PSRAM Die, 16 MB Quad SPI Flash, IPEX Antenna Connector&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="ESP32-S3-WROOM-1U-N16R8" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP32S3WROOM1UN16R8">
<connects>
<connect gate="G$1" pin="3V3" pad="2"/>
<connect gate="G$1" pin="EN" pad="3"/>
<connect gate="G$1" pin="GND_1" pad="1"/>
<connect gate="G$1" pin="GND_10" pad="48"/>
<connect gate="G$1" pin="GND_11" pad="49"/>
<connect gate="G$1" pin="GND_2" pad="40"/>
<connect gate="G$1" pin="GND_3" pad="41"/>
<connect gate="G$1" pin="GND_4" pad="42"/>
<connect gate="G$1" pin="GND_5" pad="43"/>
<connect gate="G$1" pin="GND_6" pad="44"/>
<connect gate="G$1" pin="GND_7" pad="45"/>
<connect gate="G$1" pin="GND_8" pad="46"/>
<connect gate="G$1" pin="GND_9" pad="47"/>
<connect gate="G$1" pin="IO0" pad="27"/>
<connect gate="G$1" pin="IO1" pad="39"/>
<connect gate="G$1" pin="IO10" pad="18"/>
<connect gate="G$1" pin="IO11" pad="19"/>
<connect gate="G$1" pin="IO12" pad="20"/>
<connect gate="G$1" pin="IO13" pad="21"/>
<connect gate="G$1" pin="IO14" pad="22"/>
<connect gate="G$1" pin="IO15" pad="8"/>
<connect gate="G$1" pin="IO16" pad="9"/>
<connect gate="G$1" pin="IO17" pad="10"/>
<connect gate="G$1" pin="IO18" pad="11"/>
<connect gate="G$1" pin="IO19" pad="13"/>
<connect gate="G$1" pin="IO2" pad="38"/>
<connect gate="G$1" pin="IO20" pad="14"/>
<connect gate="G$1" pin="IO21" pad="23"/>
<connect gate="G$1" pin="IO3" pad="15"/>
<connect gate="G$1" pin="IO35" pad="28"/>
<connect gate="G$1" pin="IO36" pad="29"/>
<connect gate="G$1" pin="IO37" pad="30"/>
<connect gate="G$1" pin="IO38" pad="31"/>
<connect gate="G$1" pin="IO39" pad="32"/>
<connect gate="G$1" pin="IO4" pad="4"/>
<connect gate="G$1" pin="IO40" pad="33"/>
<connect gate="G$1" pin="IO41" pad="34"/>
<connect gate="G$1" pin="IO42" pad="35"/>
<connect gate="G$1" pin="IO45" pad="26"/>
<connect gate="G$1" pin="IO46" pad="16"/>
<connect gate="G$1" pin="IO47" pad="24"/>
<connect gate="G$1" pin="IO48" pad="25"/>
<connect gate="G$1" pin="IO5" pad="5"/>
<connect gate="G$1" pin="IO6" pad="6"/>
<connect gate="G$1" pin="IO7" pad="7"/>
<connect gate="G$1" pin="IO8" pad="12"/>
<connect gate="G$1" pin="IO9" pad="17"/>
<connect gate="G$1" pin="RXD0" pad="36"/>
<connect gate="G$1" pin="TXD0" pad="37"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="356-ESP32S3WM1UN16R8" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Espressif-Systems/ESP32-S3-WROOM-1U-N16R8?qs=Li%252BoUPsLEns6V0Pr5KRJtw%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Espressif Systems" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="ESP32-S3-WROOM-1U-N16R8" constant="no"/>
<attribute name="DESCRIPTION" value="WiFi Modules - 802.11 [Engineering Samples] SMD Module, ESP32-S3R8, 8 MB Octal PSRAM Die, 16 MB Quad SPI Flash, IPEX Antenna Connector" constant="no"/>
<attribute name="HEIGHT" value="3.35mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="frames" urn="urn:adsk.eagle:library:42976481">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="DOCFIELD" urn="urn:adsk.eagle:symbol:42979731/1" library_version="4">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94">&gt;DRAWING_NAME</text>
</symbol>
<symbol name="FRAME_B_L" urn="urn:adsk.eagle:symbol:42979709/1" library_version="4">
<frame x1="0" y1="0" x2="431.8" y2="279.4" columns="9" rows="6" layer="94" border-bottom="no"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_B_L" urn="urn:adsk.eagle:component:42979764/1" prefix="FRAME" uservalue="yes" library_version="4">
<description>&lt;b&gt;FRAME&lt;/b&gt; B Size , 11 x 17 INCH, Landscape&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="FRAME_B_L" x="0" y="0" addlevel="always"/>
<gate name="G$2" symbol="DOCFIELD" x="325.12" y="0" addlevel="always"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="132135RP" urn="urn:adsk.wipprod:fs.file:vf.O64LxLIyT4Kzl4f1uo6jAg">
<description>&lt;CONN RP-SMA PLUG R/A 50 OHM PCB&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="132135RP" library_version="6">
<description>&lt;b&gt;132135RP-1&lt;/b&gt;&lt;br&gt;
</description>
<pad name="2" x="2.54" y="2.54" drill="1.7" diameter="2.55"/>
<pad name="3" x="-2.54" y="2.54" drill="1.7" diameter="2.55"/>
<pad name="4" x="-2.54" y="-2.54" drill="1.7" diameter="2.55"/>
<pad name="5" x="2.54" y="-2.54" drill="1.7" diameter="2.55"/>
<text x="0" y="4.642" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="4.642" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-3.5" y1="-3.5" x2="3.5" y2="-3.5" width="0.2" layer="51"/>
<wire x1="3.5" y1="-3.5" x2="3.5" y2="3.5" width="0.2" layer="51"/>
<wire x1="3.5" y1="3.5" x2="-3.5" y2="3.5" width="0.2" layer="51"/>
<wire x1="-3.5" y1="3.5" x2="-3.5" y2="-3.5" width="0.2" layer="51"/>
<wire x1="-4" y1="3.5" x2="4" y2="3.5" width="0.2" layer="51"/>
<wire x1="4" y1="3.5" x2="4" y2="13.1" width="0.2" layer="51"/>
<wire x1="4" y1="13.1" x2="-4" y2="13.1" width="0.2" layer="51"/>
<wire x1="-4" y1="13.1" x2="-4" y2="3.5" width="0.2" layer="51"/>
<wire x1="-3.5" y1="1" x2="-3.5" y2="-1" width="0.1" layer="21"/>
<wire x1="-3.5" y1="-1" x2="-3.5" y2="1" width="0.1" layer="21"/>
<wire x1="-1" y1="-3.5" x2="1" y2="-3.5" width="0.1" layer="21"/>
<wire x1="1" y1="-3.5" x2="-1" y2="-3.5" width="0.1" layer="21"/>
<wire x1="3.5" y1="-0.75" x2="3.5" y2="0.75" width="0.1" layer="21"/>
<wire x1="3.5" y1="0.75" x2="3.5" y2="-0.75" width="0.1" layer="21"/>
<wire x1="0.75" y1="3.5" x2="-0.75" y2="3.5" width="0.1" layer="21"/>
<wire x1="-0.75" y1="3.5" x2="0.75" y2="3.5" width="0.1" layer="21"/>
<wire x1="-4" y1="4" x2="-4" y2="13.1" width="0.1" layer="21"/>
<wire x1="-4" y1="13.1" x2="-4" y2="4" width="0.1" layer="21"/>
<wire x1="-4" y1="13.1" x2="4" y2="13.1" width="0.1" layer="21"/>
<wire x1="4" y1="13.1" x2="-4" y2="13.1" width="0.1" layer="21"/>
<wire x1="4" y1="13.1" x2="4" y2="4.25" width="0.1" layer="21"/>
<wire x1="4" y1="4.25" x2="4" y2="13.1" width="0.1" layer="21"/>
<wire x1="-5" y1="14.1" x2="5" y2="14.1" width="0.1" layer="51"/>
<wire x1="5" y1="14.1" x2="5" y2="-4.815" width="0.1" layer="51"/>
<wire x1="5" y1="-4.815" x2="-5" y2="-4.815" width="0.1" layer="51"/>
<wire x1="4.3" y1="0" x2="4.2" y2="0" width="0.2" layer="21" curve="180"/>
<wire x1="4.2" y1="0" x2="4.3" y2="0" width="0.2" layer="21" curve="180"/>
<wire x1="4.3" y1="0" x2="4.2" y2="0" width="0.2" layer="21" curve="180"/>
</package>
</packages>
<symbols>
<symbol name="132135RP" library_version="6">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="16.51" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="16.51" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="2" x="0" y="0" length="middle"/>
<pin name="3" x="0" y="-2.54" length="middle"/>
<pin name="4" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="5" x="20.32" y="-2.54" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="132135RP" prefix="J" library_version="6">
<description>&lt;b&gt;CONN RP-SMA PLUG R/A 50 OHM PCB&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-DGA15/760984.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="132135RP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="132135RP">
<connects>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="523-132135RP" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Amphenol-RF/132135RP?qs=Ld4zsxSTIA5ZJk%2F2qgahKQ%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Amphenol" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="132135RP" constant="no"/>
<attribute name="DESCRIPTION" value="CONN RP-SMA PLUG R/A 50 OHM PCB" constant="no"/>
<attribute name="HEIGHT" value="9.86mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="2026-07-14_02-46-40_Library" urn="urn:adsk.wipprod:fs.file:vf.Erw2bw45Sma41euQclXpnw">
<packages>
<package name="CONN_SM04B-SRSS-TB_JST" library_version="1">
<smd name="1" x="1.5" y="-2.0985" dx="0.6604" dy="1.5494" layer="1"/>
<smd name="2" x="0.5" y="-2.0985" dx="0.6604" dy="1.5494" layer="1"/>
<smd name="3" x="-0.5" y="-2.0985" dx="0.6604" dy="1.5494" layer="1"/>
<smd name="4" x="-1.5" y="-2.0985" dx="0.6604" dy="1.5494" layer="1"/>
<smd name="5" x="-2.8" y="1.7765" dx="1.905" dy="1.2954" layer="1" rot="R90"/>
<smd name="6" x="2.8" y="1.7765" dx="1.905" dy="1.2954" layer="1" rot="R90"/>
<wire x1="0.5" y1="-2.0985" x2="0.5" y2="5.0165" width="0.1524" layer="48"/>
<wire x1="1.5" y1="-2.0985" x2="1.5" y2="5.0165" width="0.1524" layer="48"/>
<wire x1="0.5" y1="4.6355" x2="-0.77" y2="4.6355" width="0.1524" layer="48"/>
<wire x1="1.5" y1="4.6355" x2="2.77" y2="4.6355" width="0.1524" layer="48"/>
<wire x1="0.5" y1="4.6355" x2="0.246" y2="4.7625" width="0.1524" layer="48"/>
<wire x1="0.5" y1="4.6355" x2="0.246" y2="4.5085" width="0.1524" layer="48"/>
<wire x1="0.246" y1="4.7625" x2="0.246" y2="4.5085" width="0.1524" layer="48"/>
<wire x1="1.5" y1="4.6355" x2="1.754" y2="4.7625" width="0.1524" layer="48"/>
<wire x1="1.5" y1="4.6355" x2="1.754" y2="4.5085" width="0.1524" layer="48"/>
<wire x1="1.754" y1="4.7625" x2="1.754" y2="4.5085" width="0.1524" layer="48"/>
<wire x1="-2.8" y1="1.7765" x2="-2.8" y2="10.7315" width="0.1524" layer="48"/>
<wire x1="2.8" y1="1.7765" x2="2.8" y2="10.7315" width="0.1524" layer="48"/>
<wire x1="-2.8" y1="10.3505" x2="2.8" y2="10.3505" width="0.1524" layer="48"/>
<wire x1="-2.8" y1="10.3505" x2="-2.546" y2="10.4775" width="0.1524" layer="48"/>
<wire x1="-2.8" y1="10.3505" x2="-2.546" y2="10.2235" width="0.1524" layer="48"/>
<wire x1="-2.546" y1="10.4775" x2="-2.546" y2="10.2235" width="0.1524" layer="48"/>
<wire x1="2.8" y1="10.3505" x2="2.546" y2="10.4775" width="0.1524" layer="48"/>
<wire x1="2.8" y1="10.3505" x2="2.546" y2="10.2235" width="0.1524" layer="48"/>
<wire x1="2.546" y1="10.4775" x2="2.546" y2="10.2235" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="2.4765" x2="-2.9972" y2="13.2715" width="0.1524" layer="48"/>
<wire x1="2.9972" y1="2.4765" x2="2.9972" y2="13.2715" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="12.8905" x2="2.9972" y2="12.8905" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="12.8905" x2="-2.7432" y2="13.0175" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="12.8905" x2="-2.7432" y2="12.7635" width="0.1524" layer="48"/>
<wire x1="-2.7432" y1="13.0175" x2="-2.7432" y2="12.7635" width="0.1524" layer="48"/>
<wire x1="2.9972" y1="12.8905" x2="2.7432" y2="13.0175" width="0.1524" layer="48"/>
<wire x1="2.9972" y1="12.8905" x2="2.7432" y2="12.7635" width="0.1524" layer="48"/>
<wire x1="2.7432" y1="13.0175" x2="2.7432" y2="12.7635" width="0.1524" layer="48"/>
<wire x1="1.5" y1="-2.0985" x2="5.9182" y2="-2.0985" width="0.1524" layer="48"/>
<wire x1="1.5" y1="-2.0985" x2="5.9182" y2="-2.0985" width="0.1524" layer="48"/>
<wire x1="5.5372" y1="-2.0985" x2="5.5372" y2="-0.8285" width="0.1524" layer="48"/>
<wire x1="5.5372" y1="-2.0985" x2="5.5372" y2="-3.3685" width="0.1524" layer="48"/>
<wire x1="5.5372" y1="-2.0985" x2="5.4102" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="5.5372" y1="-2.0985" x2="5.6642" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="5.4102" y1="-1.8445" x2="5.6642" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="5.5372" y1="-2.0985" x2="5.4102" y2="-2.3525" width="0.1524" layer="48"/>
<wire x1="5.5372" y1="-2.0985" x2="5.6642" y2="-2.3525" width="0.1524" layer="48"/>
<wire x1="5.4102" y1="-2.3525" x2="5.6642" y2="-2.3525" width="0.1524" layer="48"/>
<wire x1="2.8" y1="1.7765" x2="-6.2925" y2="1.7765" width="0.1524" layer="48"/>
<wire x1="0" y1="-2.0985" x2="-6.2925" y2="-2.0985" width="0.1524" layer="48"/>
<wire x1="-5.9115" y1="1.7765" x2="-5.9115" y2="-2.0985" width="0.1524" layer="48"/>
<wire x1="-5.9115" y1="1.7765" x2="-6.0385" y2="1.5225" width="0.1524" layer="48"/>
<wire x1="-5.9115" y1="1.7765" x2="-5.7845" y2="1.5225" width="0.1524" layer="48"/>
<wire x1="-6.0385" y1="1.5225" x2="-5.7845" y2="1.5225" width="0.1524" layer="48"/>
<wire x1="-5.9115" y1="-2.0985" x2="-6.0385" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="-5.9115" y1="-2.0985" x2="-5.7845" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="-6.0385" y1="-1.8445" x2="-5.7845" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="2.4765" x2="-14.5475" y2="2.4765" width="0.1524" layer="48"/>
<wire x1="0" y1="-2.0985" x2="-14.5475" y2="-2.0985" width="0.1524" layer="48"/>
<wire x1="-14.1665" y1="2.4765" x2="-14.1665" y2="-2.0985" width="0.1524" layer="48"/>
<wire x1="-14.1665" y1="2.4765" x2="-14.2935" y2="2.2225" width="0.1524" layer="48"/>
<wire x1="-14.1665" y1="2.4765" x2="-14.0395" y2="2.2225" width="0.1524" layer="48"/>
<wire x1="-14.2935" y1="2.2225" x2="-14.0395" y2="2.2225" width="0.1524" layer="48"/>
<wire x1="-14.1665" y1="-2.0985" x2="-14.2935" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="-14.1665" y1="-2.0985" x2="-14.0395" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="-14.2935" y1="-1.8445" x2="-14.0395" y2="-1.8445" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="2.4765" x2="-13.2775" y2="2.4765" width="0.1524" layer="48"/>
<wire x1="-2.9972" y1="-2.4765" x2="-13.2775" y2="-2.4765" width="0.1524" layer="48"/>
<wire x1="-12.8965" y1="2.4765" x2="-12.8965" y2="-2.4765" width="0.1524" layer="48"/>
<wire x1="-12.8965" y1="2.4765" x2="-13.0235" y2="2.2225" width="0.1524" layer="48"/>
<wire x1="-12.8965" y1="2.4765" x2="-12.7695" y2="2.2225" width="0.1524" layer="48"/>
<wire x1="-13.0235" y1="2.2225" x2="-12.7695" y2="2.2225" width="0.1524" layer="48"/>
<wire x1="-12.8965" y1="-2.4765" x2="-13.0235" y2="-2.2225" width="0.1524" layer="48"/>
<wire x1="-12.8965" y1="-2.4765" x2="-12.7695" y2="-2.2225" width="0.1524" layer="48"/>
<wire x1="-13.0235" y1="-2.2225" x2="-12.7695" y2="-2.2225" width="0.1524" layer="48"/>
<text x="-15.2035" y="-6.9372" size="1.27" layer="48" ratio="6">Default Padstyle: RX26Y61D0T</text>
<text x="-15.3899" y="-8.8422" size="1.27" layer="48" ratio="6">1st Mtg Padstyle: RX75Y51D0T</text>
<text x="-16.1525" y="-10.7472" size="1.27" layer="48" ratio="6">2nd Mtg Padstyle: EX70Y70D70P</text>
<text x="-16.1525" y="-12.6522" size="1.27" layer="48" ratio="6">3rd Mtg Padstyle: EX70Y70D70P</text>
<text x="-16.356" y="-14.5572" size="1.27" layer="48" ratio="6">Left Mtg Padstyle: EX60Y60D30P</text>
<text x="-16.9323" y="-16.4622" size="1.27" layer="48" ratio="6">Right Mtg Padstyle: EX60Y60D30P</text>
<text x="-14.8136" y="-18.3672" size="1.27" layer="48" ratio="6">Alt Padstyle 1: OX60Y90D30P</text>
<text x="-14.8136" y="-20.2722" size="1.27" layer="48" ratio="6">Alt Padstyle 2: OX90Y60D30P</text>
<text x="-1.7331" y="5.1435" size="0.635" layer="48" ratio="4">0.039in/1mm</text>
<text x="-3.178" y="10.8585" size="0.635" layer="48" ratio="4">0.22in/5.6mm</text>
<text x="-4.0424" y="13.3985" size="0.635" layer="48" ratio="4">0.236in/5.994mm</text>
<text x="6.0452" y="-2.416" size="0.635" layer="48" ratio="4">0in/0mm</text>
<text x="-14.5043" y="-0.4785" size="0.635" layer="48" ratio="4">0.153in/3.875mm</text>
<text x="-22.1831" y="-0.1285" size="0.635" layer="48" ratio="4">0.18in/4.575mm</text>
<text x="-21.4893" y="-0.3175" size="0.635" layer="48" ratio="4">0.195in/4.953mm</text>
<wire x1="-3.1242" y1="-2.6035" x2="-2.1629" y2="-2.6035" width="0.1524" layer="21"/>
<wire x1="3.1242" y1="-2.6035" x2="3.1242" y2="0.4913" width="0.1524" layer="21"/>
<wire x1="1.8196" y1="2.6035" x2="-1.8196" y2="2.6035" width="0.1524" layer="21"/>
<wire x1="-3.1242" y1="0.4913" x2="-3.1242" y2="-2.6035" width="0.1524" layer="21"/>
<wire x1="2.1629" y1="-2.6035" x2="3.1242" y2="-2.6035" width="0.1524" layer="21"/>
<wire x1="4.1402" y1="-2.0985" x2="3.3782" y2="-2.0985" width="0.508" layer="21" curve="-180"/>
<wire x1="3.3782" y1="-2.0985" x2="4.1402" y2="-2.0985" width="0.508" layer="21" curve="-180"/>
<wire x1="-2.9972" y1="-2.4765" x2="2.9972" y2="-2.4765" width="0.1524" layer="51"/>
<wire x1="2.9972" y1="-2.4765" x2="2.9972" y2="2.4765" width="0.1524" layer="51"/>
<wire x1="2.9972" y1="2.4765" x2="-2.9972" y2="2.4765" width="0.1524" layer="51"/>
<wire x1="-2.9972" y1="2.4765" x2="-2.9972" y2="-2.4765" width="0.1524" layer="51"/>
<wire x1="1.881" y1="-4.0035" x2="1.119" y2="-4.0035" width="0.508" layer="51" curve="-180"/>
<wire x1="1.119" y1="-4.0035" x2="1.881" y2="-4.0035" width="0.508" layer="51" curve="-180"/>
<wire x1="4.1402" y1="-2.0985" x2="3.3782" y2="-2.0985" width="0.508" layer="22" curve="-180"/>
<wire x1="3.3782" y1="-2.0985" x2="4.1402" y2="-2.0985" width="0.508" layer="22" curve="-180"/>
<text x="-3.2712" y="-2.7335" size="1.27" layer="27" ratio="6">&gt;Name</text>
<text x="-1.7288" y="-2.7335" size="1.27" layer="27" ratio="6">&gt;Value</text>
</package>
</packages>
<symbols>
<symbol name="CONN_04P_00C_1" library_version="1">
<pin name="1" x="0" y="0" visible="pad" length="middle" direction="pas"/>
<pin name="2" x="0" y="-2.54" visible="pad" length="middle" direction="pas"/>
<pin name="3" x="0" y="-5.08" visible="pad" length="middle" direction="pas"/>
<pin name="4" x="0" y="-7.62" visible="pad" length="middle" direction="pas"/>
<wire x1="10.16" y1="0" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="5.08" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="5.08" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="5.08" y2="-7.62" width="0.1524" layer="94"/>
<wire x1="10.16" y1="0" x2="8.89" y2="0.8467" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="8.89" y2="-1.6933" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="8.89" y2="-4.2333" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="8.89" y2="-6.7733" width="0.1524" layer="94"/>
<wire x1="10.16" y1="0" x2="8.89" y2="-0.8467" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="8.89" y2="-3.3867" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="8.89" y2="-5.9267" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="8.89" y2="-8.4667" width="0.1524" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-10.16" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-10.16" x2="12.7" y2="-10.16" width="0.1524" layer="94"/>
<wire x1="12.7" y1="-10.16" x2="12.7" y2="2.54" width="0.1524" layer="94"/>
<wire x1="12.7" y1="2.54" x2="5.08" y2="2.54" width="0.1524" layer="94"/>
<text x="4.1646" y="5.3086" size="2.083" layer="95" ratio="6">&gt;Name</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="SM04B-SRSS-TB" prefix="J" library_version="1">
<gates>
<gate name="A" symbol="CONN_04P_00C_1" x="0" y="0"/>
</gates>
<devices>
<device name="CONN_SM04B-SRSS-TB_JST" package="CONN_SM04B-SRSS-TB_JST">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="COPYRIGHT" value="Copyright (C) 2026 Ultra Librarian. All rights reserved." constant="no"/>
<attribute name="MANUFACTURER_NAME" value="JST" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="SM04B-SRSS-TB" constant="no"/>
<attribute name="DIGI-KEY_PART_NUMBER_1" value="455-1422-2-ND" constant="no"/>
<attribute name="DIGI-KEY_PART_NUMBER_2" value="455-1422-1-ND" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="MEM2085-00-115-00-A" urn="urn:adsk.wipprod:fs.file:vf.nF0OIkYKTUugXdX2XtAhqA">
<description>&lt;Memory Card Connectors Micro SD Push Pull SMT 1.15mm No Peg&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="MEM20850011500A" library_version="2">
<description>&lt;b&gt;MEM2085-00-115-00-A-3&lt;/b&gt;&lt;br&gt;
</description>
<smd name="G1" x="5.3" y="-3.53" dx="1.4" dy="1.3" layer="1" rot="R90"/>
<smd name="G2" x="-5.475" y="-3.53" dx="1.4" dy="0.95" layer="1" rot="R90"/>
<smd name="G3" x="5.75" y="-1.23" dx="1.2" dy="0.4" layer="1" rot="R90"/>
<smd name="G4" x="-5.75" y="-1.23" dx="1.2" dy="0.4" layer="1" rot="R90"/>
<smd name="G5" x="5.75" y="1.37" dx="1.2" dy="0.4" layer="1" rot="R90"/>
<smd name="G6" x="-5.75" y="1.37" dx="1.2" dy="0.4" layer="1" rot="R90"/>
<smd name="G7" x="5.3" y="3.73" dx="1.3" dy="1" layer="1"/>
<smd name="G8" x="2.11" y="4.03" dx="1.4" dy="0.4" layer="1"/>
<smd name="G9" x="-2.14" y="4.03" dx="1.4" dy="0.4" layer="1"/>
<smd name="G10" x="-5.3" y="3.73" dx="1.3" dy="1" layer="1"/>
<smd name="P1" x="3.18" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P2" x="2.48" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P3" x="1.78" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P4" x="1.08" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P5" x="-0.62" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P6" x="-1.32" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P7" x="-2.72" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="P8" x="-3.42" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<smd name="CD1" x="-2.02" y="-2.99" dx="0.7" dy="0.45" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-5.76" y1="-4.03" x2="5.76" y2="-4.03" width="0.1" layer="51"/>
<wire x1="5.76" y1="-4.03" x2="5.76" y2="4.03" width="0.1" layer="51"/>
<wire x1="5.76" y1="4.03" x2="-5.76" y2="4.03" width="0.1" layer="51"/>
<wire x1="-5.76" y1="4.03" x2="-5.76" y2="-4.03" width="0.1" layer="51"/>
<wire x1="-6.96" y1="5.23" x2="6.96" y2="5.23" width="0.1" layer="51"/>
<wire x1="6.96" y1="5.23" x2="6.96" y2="-5.23" width="0.1" layer="51"/>
<wire x1="6.96" y1="-5.23" x2="-6.96" y2="-5.23" width="0.1" layer="51"/>
<wire x1="-6.96" y1="-5.23" x2="-6.96" y2="5.23" width="0.1" layer="51"/>
<wire x1="-4.4" y1="4.03" x2="-3.2" y2="4.03" width="0.2" layer="21"/>
<wire x1="-5.76" y1="3" x2="-5.76" y2="2.2" width="0.2" layer="21"/>
<wire x1="-5.76" y1="0.4" x2="-5.76" y2="-0.4" width="0.2" layer="21"/>
<wire x1="-5.76" y1="-2.2" x2="-5.76" y2="-2.6" width="0.2" layer="21"/>
<wire x1="-4.6" y1="-4.03" x2="4.4" y2="-4.03" width="0.2" layer="21"/>
<wire x1="5.76" y1="-2.6" x2="5.76" y2="-2.2" width="0.2" layer="21"/>
<wire x1="5.76" y1="-0.4" x2="5.76" y2="0.4" width="0.2" layer="21"/>
<wire x1="5.76" y1="3" x2="5.76" y2="2.2" width="0.2" layer="21"/>
<wire x1="3.2" y1="4.03" x2="4.4" y2="4.03" width="0.2" layer="21"/>
<wire x1="-1.2" y1="4.03" x2="1" y2="4.03" width="0.2" layer="21"/>
<wire x1="3.18" y1="-4.7" x2="3.18" y2="-4.6" width="0.1" layer="21" curve="180"/>
<wire x1="3.18" y1="-4.6" x2="3.18" y2="-4.7" width="0.1" layer="21" curve="180"/>
</package>
</packages>
<symbols>
<symbol name="MEM2085-00-115-00-A" library_version="2">
<wire x1="5.08" y1="2.54" x2="30.48" y2="2.54" width="0.254" layer="94"/>
<wire x1="30.48" y1="-25.4" x2="30.48" y2="2.54" width="0.254" layer="94"/>
<wire x1="30.48" y1="-25.4" x2="5.08" y2="-25.4" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-25.4" width="0.254" layer="94"/>
<text x="31.75" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="31.75" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="GND_1" x="0" y="0" length="middle"/>
<pin name="GND_2" x="0" y="-2.54" length="middle"/>
<pin name="GND_3" x="0" y="-5.08" length="middle"/>
<pin name="GND_4" x="0" y="-7.62" length="middle"/>
<pin name="GND_5" x="0" y="-10.16" length="middle"/>
<pin name="GND_6" x="0" y="-12.7" length="middle"/>
<pin name="GND_7" x="0" y="-15.24" length="middle"/>
<pin name="GND_8" x="0" y="-17.78" length="middle"/>
<pin name="GND_9" x="0" y="-20.32" length="middle"/>
<pin name="GND_10" x="0" y="-22.86" length="middle"/>
<pin name="DAT2" x="35.56" y="0" length="middle" rot="R180"/>
<pin name="CD/DAT3" x="35.56" y="-2.54" length="middle" rot="R180"/>
<pin name="CMD" x="35.56" y="-5.08" length="middle" rot="R180"/>
<pin name="VDD" x="35.56" y="-7.62" length="middle" rot="R180"/>
<pin name="CLK" x="35.56" y="-10.16" length="middle" rot="R180"/>
<pin name="VSS" x="35.56" y="-12.7" length="middle" rot="R180"/>
<pin name="DAT0" x="35.56" y="-15.24" length="middle" rot="R180"/>
<pin name="DAT1" x="35.56" y="-17.78" length="middle" rot="R180"/>
<pin name="CD1" x="35.56" y="-20.32" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MEM2085-00-115-00-A" prefix="J" library_version="2">
<description>&lt;b&gt;Memory Card Connectors Micro SD Push Pull SMT 1.15mm No Peg&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://gct.co/files/drawings/mem2085.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="MEM2085-00-115-00-A" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MEM20850011500A">
<connects>
<connect gate="G$1" pin="CD/DAT3" pad="P2"/>
<connect gate="G$1" pin="CD1" pad="CD1"/>
<connect gate="G$1" pin="CLK" pad="P5"/>
<connect gate="G$1" pin="CMD" pad="P3"/>
<connect gate="G$1" pin="DAT0" pad="P7"/>
<connect gate="G$1" pin="DAT1" pad="P8"/>
<connect gate="G$1" pin="DAT2" pad="P1"/>
<connect gate="G$1" pin="GND_1" pad="G1"/>
<connect gate="G$1" pin="GND_10" pad="G10"/>
<connect gate="G$1" pin="GND_2" pad="G2"/>
<connect gate="G$1" pin="GND_3" pad="G3"/>
<connect gate="G$1" pin="GND_4" pad="G4"/>
<connect gate="G$1" pin="GND_5" pad="G5"/>
<connect gate="G$1" pin="GND_6" pad="G6"/>
<connect gate="G$1" pin="GND_7" pad="G7"/>
<connect gate="G$1" pin="GND_8" pad="G8"/>
<connect gate="G$1" pin="GND_9" pad="G9"/>
<connect gate="G$1" pin="VDD" pad="P4"/>
<connect gate="G$1" pin="VSS" pad="P6"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="640-MEM20850011500A" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/GCT/MEM2085-00-115-00-A?qs=rQFj71Wb1eWNkFUhuuvVIA%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="GCT (GLOBAL CONNECTOR TECHNOLOGY)" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="MEM2085-00-115-00-A" constant="no"/>
<attribute name="DESCRIPTION" value="Memory Card Connectors Micro SD Push Pull SMT 1.15mm No Peg" constant="no"/>
<attribute name="HEIGHT" value="1.35mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="UJ20-C-H-G-SMT-1-P16-TR" urn="urn:adsk.wipprod:fs.file:vf.VgEXy_XXReqS1Zb8YyEAgA">
<packages>
<package name="SAMESKY_UJ20-C-H-G-SMT-1-P16-TR" library_version="2">
<wire x1="-4.62" y1="7.33" x2="-4.32" y2="7.63" width="0" layer="46" curve="-90"/>
<wire x1="-4.32" y1="7.63" x2="-4.02" y2="7.33" width="0" layer="46" curve="-90"/>
<wire x1="-4.02" y1="7.33" x2="-4.02" y2="6.23" width="0" layer="46"/>
<wire x1="-4.02" y1="6.23" x2="-4.32" y2="5.93" width="0" layer="46" curve="-90"/>
<wire x1="-4.32" y1="5.93" x2="-4.62" y2="6.23" width="0" layer="46" curve="-90"/>
<wire x1="-4.62" y1="6.23" x2="-4.62" y2="7.33" width="0" layer="46"/>
<polygon width="0.01" layer="1" pour="solid">
<vertex x="-4.4312625" y="5.7425375"/>
<vertex x="-4.32" y="5.73"/>
<vertex x="-4.2087375" y="5.7425375"/>
<vertex x="-4.103053125" y="5.779515625"/>
<vertex x="-4.0082625" y="5.839078125"/>
<vertex x="-3.929078125" y="5.9182625"/>
<vertex x="-3.869515625" y="6.013053125"/>
<vertex x="-3.8325375" y="6.1187375"/>
<vertex x="-3.82" y="6.23000625"/>
<vertex x="-3.82" y="7.32999375"/>
<vertex x="-3.8325375" y="7.4412625"/>
<vertex x="-3.869515625" y="7.546946875"/>
<vertex x="-3.929078125" y="7.6417375"/>
<vertex x="-4.0082625" y="7.720921875"/>
<vertex x="-4.103053125" y="7.780484375"/>
<vertex x="-4.2087375" y="7.8174625"/>
<vertex x="-4.32" y="7.83"/>
<vertex x="-4.4312625" y="7.8174625"/>
<vertex x="-4.536946875" y="7.780484375"/>
<vertex x="-4.6317375" y="7.720921875"/>
<vertex x="-4.710921875" y="7.6417375"/>
<vertex x="-4.770484375" y="7.546946875"/>
<vertex x="-4.8074625" y="7.4412625"/>
<vertex x="-4.82" y="7.32999375"/>
<vertex x="-4.82" y="6.23000625"/>
<vertex x="-4.8074625" y="6.1187375"/>
<vertex x="-4.770484375" y="6.013053125"/>
<vertex x="-4.710921875" y="5.9182625"/>
<vertex x="-4.6317375" y="5.839078125"/>
<vertex x="-4.536946875" y="5.779515625"/>
</polygon>
<polygon width="0.01" layer="16" pour="solid">
<vertex x="-4.4312625" y="5.7425375"/>
<vertex x="-4.32" y="5.73"/>
<vertex x="-4.2087375" y="5.7425375"/>
<vertex x="-4.103053125" y="5.779515625"/>
<vertex x="-4.0082625" y="5.839078125"/>
<vertex x="-3.929078125" y="5.9182625"/>
<vertex x="-3.869515625" y="6.013053125"/>
<vertex x="-3.8325375" y="6.1187375"/>
<vertex x="-3.82" y="6.23000625"/>
<vertex x="-3.82" y="7.32999375"/>
<vertex x="-3.8325375" y="7.4412625"/>
<vertex x="-3.869515625" y="7.546946875"/>
<vertex x="-3.929078125" y="7.6417375"/>
<vertex x="-4.0082625" y="7.720921875"/>
<vertex x="-4.103053125" y="7.780484375"/>
<vertex x="-4.2087375" y="7.8174625"/>
<vertex x="-4.32" y="7.83"/>
<vertex x="-4.4312625" y="7.8174625"/>
<vertex x="-4.536946875" y="7.780484375"/>
<vertex x="-4.6317375" y="7.720921875"/>
<vertex x="-4.710921875" y="7.6417375"/>
<vertex x="-4.770484375" y="7.546946875"/>
<vertex x="-4.8074625" y="7.4412625"/>
<vertex x="-4.82" y="7.32999375"/>
<vertex x="-4.82" y="6.23000625"/>
<vertex x="-4.8074625" y="6.1187375"/>
<vertex x="-4.770484375" y="6.013053125"/>
<vertex x="-4.710921875" y="5.9182625"/>
<vertex x="-4.6317375" y="5.839078125"/>
<vertex x="-4.536946875" y="5.779515625"/>
</polygon>
<polygon width="0.01" layer="30" pour="solid">
<vertex x="-4.43704375" y="5.641525"/>
<vertex x="-4.32" y="5.629996875"/>
<vertex x="-4.20295625" y="5.641525"/>
<vertex x="-4.09040625" y="5.675665625"/>
<vertex x="-3.98665625" y="5.73111875"/>
<vertex x="-3.895734375" y="5.805734375"/>
<vertex x="-3.82111875" y="5.89665625"/>
<vertex x="-3.765665625" y="6.00040625"/>
<vertex x="-3.731525" y="6.11295625"/>
<vertex x="-3.72" y="6.2299875"/>
<vertex x="-3.72" y="7.3300125"/>
<vertex x="-3.731525" y="7.44704375"/>
<vertex x="-3.765665625" y="7.55959375"/>
<vertex x="-3.82111875" y="7.66334375"/>
<vertex x="-3.895734375" y="7.754265625"/>
<vertex x="-3.98665625" y="7.82888125"/>
<vertex x="-4.09040625" y="7.884334375"/>
<vertex x="-4.20295625" y="7.918475"/>
<vertex x="-4.32" y="7.930003125"/>
<vertex x="-4.43704375" y="7.918475"/>
<vertex x="-4.54959375" y="7.884334375"/>
<vertex x="-4.65334375" y="7.82888125"/>
<vertex x="-4.744265625" y="7.754265625"/>
<vertex x="-4.81888125" y="7.66334375"/>
<vertex x="-4.874334375" y="7.55959375"/>
<vertex x="-4.908475" y="7.44704375"/>
<vertex x="-4.92" y="7.3300125"/>
<vertex x="-4.92" y="6.2299875"/>
<vertex x="-4.908475" y="6.11295625"/>
<vertex x="-4.874334375" y="6.00040625"/>
<vertex x="-4.81888125" y="5.89665625"/>
<vertex x="-4.744265625" y="5.805734375"/>
<vertex x="-4.65334375" y="5.73111875"/>
<vertex x="-4.54959375" y="5.675665625"/>
</polygon>
<polygon width="0.01" layer="29" pour="solid">
<vertex x="-4.43704375" y="5.641525"/>
<vertex x="-4.32" y="5.629996875"/>
<vertex x="-4.20295625" y="5.641525"/>
<vertex x="-4.09040625" y="5.675665625"/>
<vertex x="-3.98665625" y="5.73111875"/>
<vertex x="-3.895734375" y="5.805734375"/>
<vertex x="-3.82111875" y="5.89665625"/>
<vertex x="-3.765665625" y="6.00040625"/>
<vertex x="-3.731525" y="6.11295625"/>
<vertex x="-3.72" y="6.2299875"/>
<vertex x="-3.72" y="7.3300125"/>
<vertex x="-3.731525" y="7.44704375"/>
<vertex x="-3.765665625" y="7.55959375"/>
<vertex x="-3.82111875" y="7.66334375"/>
<vertex x="-3.895734375" y="7.754265625"/>
<vertex x="-3.98665625" y="7.82888125"/>
<vertex x="-4.09040625" y="7.884334375"/>
<vertex x="-4.20295625" y="7.918475"/>
<vertex x="-4.32" y="7.930003125"/>
<vertex x="-4.43704375" y="7.918475"/>
<vertex x="-4.54959375" y="7.884334375"/>
<vertex x="-4.65334375" y="7.82888125"/>
<vertex x="-4.744265625" y="7.754265625"/>
<vertex x="-4.81888125" y="7.66334375"/>
<vertex x="-4.874334375" y="7.55959375"/>
<vertex x="-4.908475" y="7.44704375"/>
<vertex x="-4.92" y="7.3300125"/>
<vertex x="-4.92" y="6.2299875"/>
<vertex x="-4.908475" y="6.11295625"/>
<vertex x="-4.874334375" y="6.00040625"/>
<vertex x="-4.81888125" y="5.89665625"/>
<vertex x="-4.744265625" y="5.805734375"/>
<vertex x="-4.65334375" y="5.73111875"/>
<vertex x="-4.54959375" y="5.675665625"/>
</polygon>
<wire x1="4.02" y1="7.33" x2="4.32" y2="7.63" width="0" layer="46" curve="-90"/>
<wire x1="4.32" y1="7.63" x2="4.62" y2="7.33" width="0" layer="46" curve="-90"/>
<wire x1="4.62" y1="7.33" x2="4.62" y2="6.23" width="0" layer="46"/>
<wire x1="4.62" y1="6.23" x2="4.32" y2="5.93" width="0" layer="46" curve="-90"/>
<wire x1="4.32" y1="5.93" x2="4.02" y2="6.23" width="0" layer="46" curve="-90"/>
<wire x1="4.02" y1="6.23" x2="4.02" y2="7.33" width="0" layer="46"/>
<polygon width="0.01" layer="1" pour="solid">
<vertex x="4.2087375" y="5.7425375"/>
<vertex x="4.32" y="5.73"/>
<vertex x="4.4312625" y="5.7425375"/>
<vertex x="4.536946875" y="5.779515625"/>
<vertex x="4.6317375" y="5.839078125"/>
<vertex x="4.710921875" y="5.9182625"/>
<vertex x="4.770484375" y="6.013053125"/>
<vertex x="4.8074625" y="6.1187375"/>
<vertex x="4.82" y="6.23000625"/>
<vertex x="4.82" y="7.32999375"/>
<vertex x="4.8074625" y="7.4412625"/>
<vertex x="4.770484375" y="7.546946875"/>
<vertex x="4.710921875" y="7.6417375"/>
<vertex x="4.6317375" y="7.720921875"/>
<vertex x="4.536946875" y="7.780484375"/>
<vertex x="4.4312625" y="7.8174625"/>
<vertex x="4.32" y="7.83"/>
<vertex x="4.2087375" y="7.8174625"/>
<vertex x="4.103053125" y="7.780484375"/>
<vertex x="4.0082625" y="7.720921875"/>
<vertex x="3.929078125" y="7.6417375"/>
<vertex x="3.869515625" y="7.546946875"/>
<vertex x="3.8325375" y="7.4412625"/>
<vertex x="3.82" y="7.32999375"/>
<vertex x="3.82" y="6.23000625"/>
<vertex x="3.8325375" y="6.1187375"/>
<vertex x="3.869515625" y="6.013053125"/>
<vertex x="3.929078125" y="5.9182625"/>
<vertex x="4.0082625" y="5.839078125"/>
<vertex x="4.103053125" y="5.779515625"/>
</polygon>
<polygon width="0.01" layer="16" pour="solid">
<vertex x="4.2087375" y="5.7425375"/>
<vertex x="4.32" y="5.73"/>
<vertex x="4.4312625" y="5.7425375"/>
<vertex x="4.536946875" y="5.779515625"/>
<vertex x="4.6317375" y="5.839078125"/>
<vertex x="4.710921875" y="5.9182625"/>
<vertex x="4.770484375" y="6.013053125"/>
<vertex x="4.8074625" y="6.1187375"/>
<vertex x="4.82" y="6.23000625"/>
<vertex x="4.82" y="7.32999375"/>
<vertex x="4.8074625" y="7.4412625"/>
<vertex x="4.770484375" y="7.546946875"/>
<vertex x="4.710921875" y="7.6417375"/>
<vertex x="4.6317375" y="7.720921875"/>
<vertex x="4.536946875" y="7.780484375"/>
<vertex x="4.4312625" y="7.8174625"/>
<vertex x="4.32" y="7.83"/>
<vertex x="4.2087375" y="7.8174625"/>
<vertex x="4.103053125" y="7.780484375"/>
<vertex x="4.0082625" y="7.720921875"/>
<vertex x="3.929078125" y="7.6417375"/>
<vertex x="3.869515625" y="7.546946875"/>
<vertex x="3.8325375" y="7.4412625"/>
<vertex x="3.82" y="7.32999375"/>
<vertex x="3.82" y="6.23000625"/>
<vertex x="3.8325375" y="6.1187375"/>
<vertex x="3.869515625" y="6.013053125"/>
<vertex x="3.929078125" y="5.9182625"/>
<vertex x="4.0082625" y="5.839078125"/>
<vertex x="4.103053125" y="5.779515625"/>
</polygon>
<polygon width="0.01" layer="30" pour="solid">
<vertex x="4.20295625" y="5.641525"/>
<vertex x="4.32" y="5.629996875"/>
<vertex x="4.43704375" y="5.641525"/>
<vertex x="4.54959375" y="5.675665625"/>
<vertex x="4.65334375" y="5.73111875"/>
<vertex x="4.744265625" y="5.805734375"/>
<vertex x="4.81888125" y="5.89665625"/>
<vertex x="4.874334375" y="6.00040625"/>
<vertex x="4.908475" y="6.11295625"/>
<vertex x="4.92" y="6.2299875"/>
<vertex x="4.92" y="7.3300125"/>
<vertex x="4.908475" y="7.44704375"/>
<vertex x="4.874334375" y="7.55959375"/>
<vertex x="4.81888125" y="7.66334375"/>
<vertex x="4.744265625" y="7.754265625"/>
<vertex x="4.65334375" y="7.82888125"/>
<vertex x="4.54959375" y="7.884334375"/>
<vertex x="4.43704375" y="7.918475"/>
<vertex x="4.32" y="7.930003125"/>
<vertex x="4.20295625" y="7.918475"/>
<vertex x="4.09040625" y="7.884334375"/>
<vertex x="3.98665625" y="7.82888125"/>
<vertex x="3.895734375" y="7.754265625"/>
<vertex x="3.82111875" y="7.66334375"/>
<vertex x="3.765665625" y="7.55959375"/>
<vertex x="3.731525" y="7.44704375"/>
<vertex x="3.72" y="7.3300125"/>
<vertex x="3.72" y="6.2299875"/>
<vertex x="3.731525" y="6.11295625"/>
<vertex x="3.765665625" y="6.00040625"/>
<vertex x="3.82111875" y="5.89665625"/>
<vertex x="3.895734375" y="5.805734375"/>
<vertex x="3.98665625" y="5.73111875"/>
<vertex x="4.09040625" y="5.675665625"/>
</polygon>
<polygon width="0.01" layer="29" pour="solid">
<vertex x="4.20295625" y="5.641525"/>
<vertex x="4.32" y="5.629996875"/>
<vertex x="4.43704375" y="5.641525"/>
<vertex x="4.54959375" y="5.675665625"/>
<vertex x="4.65334375" y="5.73111875"/>
<vertex x="4.744265625" y="5.805734375"/>
<vertex x="4.81888125" y="5.89665625"/>
<vertex x="4.874334375" y="6.00040625"/>
<vertex x="4.908475" y="6.11295625"/>
<vertex x="4.92" y="6.2299875"/>
<vertex x="4.92" y="7.3300125"/>
<vertex x="4.908475" y="7.44704375"/>
<vertex x="4.874334375" y="7.55959375"/>
<vertex x="4.81888125" y="7.66334375"/>
<vertex x="4.744265625" y="7.754265625"/>
<vertex x="4.65334375" y="7.82888125"/>
<vertex x="4.54959375" y="7.884334375"/>
<vertex x="4.43704375" y="7.918475"/>
<vertex x="4.32" y="7.930003125"/>
<vertex x="4.20295625" y="7.918475"/>
<vertex x="4.09040625" y="7.884334375"/>
<vertex x="3.98665625" y="7.82888125"/>
<vertex x="3.895734375" y="7.754265625"/>
<vertex x="3.82111875" y="7.66334375"/>
<vertex x="3.765665625" y="7.55959375"/>
<vertex x="3.731525" y="7.44704375"/>
<vertex x="3.72" y="7.3300125"/>
<vertex x="3.72" y="6.2299875"/>
<vertex x="3.731525" y="6.11295625"/>
<vertex x="3.765665625" y="6.00040625"/>
<vertex x="3.82111875" y="5.89665625"/>
<vertex x="3.895734375" y="5.805734375"/>
<vertex x="3.98665625" y="5.73111875"/>
<vertex x="4.09040625" y="5.675665625"/>
</polygon>
<wire x1="-4.62" y1="3" x2="-4.32" y2="3.3" width="0" layer="46" curve="-90"/>
<wire x1="-4.32" y1="3.3" x2="-4.02" y2="3" width="0" layer="46" curve="-90"/>
<wire x1="-4.02" y1="3" x2="-4.02" y2="2.2" width="0" layer="46"/>
<wire x1="-4.02" y1="2.2" x2="-4.32" y2="1.9" width="0" layer="46" curve="-90"/>
<wire x1="-4.32" y1="1.9" x2="-4.62" y2="2.2" width="0" layer="46" curve="-90"/>
<wire x1="-4.62" y1="2.2" x2="-4.62" y2="3" width="0" layer="46"/>
<polygon width="0.01" layer="1" pour="solid">
<vertex x="-4.4312625" y="1.7125375"/>
<vertex x="-4.32" y="1.7"/>
<vertex x="-4.2087375" y="1.7125375"/>
<vertex x="-4.103053125" y="1.749515625"/>
<vertex x="-4.0082625" y="1.809078125"/>
<vertex x="-3.929078125" y="1.8882625"/>
<vertex x="-3.869515625" y="1.983053125"/>
<vertex x="-3.8325375" y="2.0887375"/>
<vertex x="-3.82" y="2.20000625"/>
<vertex x="-3.82" y="2.99999375"/>
<vertex x="-3.8325375" y="3.1112625"/>
<vertex x="-3.869515625" y="3.216946875"/>
<vertex x="-3.929078125" y="3.3117375"/>
<vertex x="-4.0082625" y="3.390921875"/>
<vertex x="-4.103053125" y="3.450484375"/>
<vertex x="-4.2087375" y="3.4874625"/>
<vertex x="-4.32" y="3.5"/>
<vertex x="-4.4312625" y="3.4874625"/>
<vertex x="-4.536946875" y="3.450484375"/>
<vertex x="-4.6317375" y="3.390921875"/>
<vertex x="-4.710921875" y="3.3117375"/>
<vertex x="-4.770484375" y="3.216946875"/>
<vertex x="-4.8074625" y="3.1112625"/>
<vertex x="-4.82" y="2.99999375"/>
<vertex x="-4.82" y="2.20000625"/>
<vertex x="-4.8074625" y="2.0887375"/>
<vertex x="-4.770484375" y="1.983053125"/>
<vertex x="-4.710921875" y="1.8882625"/>
<vertex x="-4.6317375" y="1.809078125"/>
<vertex x="-4.536946875" y="1.749515625"/>
</polygon>
<polygon width="0.01" layer="16" pour="solid">
<vertex x="-4.4312625" y="1.7125375"/>
<vertex x="-4.32" y="1.7"/>
<vertex x="-4.2087375" y="1.7125375"/>
<vertex x="-4.103053125" y="1.749515625"/>
<vertex x="-4.0082625" y="1.809078125"/>
<vertex x="-3.929078125" y="1.8882625"/>
<vertex x="-3.869515625" y="1.983053125"/>
<vertex x="-3.8325375" y="2.0887375"/>
<vertex x="-3.82" y="2.20000625"/>
<vertex x="-3.82" y="2.99999375"/>
<vertex x="-3.8325375" y="3.1112625"/>
<vertex x="-3.869515625" y="3.216946875"/>
<vertex x="-3.929078125" y="3.3117375"/>
<vertex x="-4.0082625" y="3.390921875"/>
<vertex x="-4.103053125" y="3.450484375"/>
<vertex x="-4.2087375" y="3.4874625"/>
<vertex x="-4.32" y="3.5"/>
<vertex x="-4.4312625" y="3.4874625"/>
<vertex x="-4.536946875" y="3.450484375"/>
<vertex x="-4.6317375" y="3.390921875"/>
<vertex x="-4.710921875" y="3.3117375"/>
<vertex x="-4.770484375" y="3.216946875"/>
<vertex x="-4.8074625" y="3.1112625"/>
<vertex x="-4.82" y="2.99999375"/>
<vertex x="-4.82" y="2.20000625"/>
<vertex x="-4.8074625" y="2.0887375"/>
<vertex x="-4.770484375" y="1.983053125"/>
<vertex x="-4.710921875" y="1.8882625"/>
<vertex x="-4.6317375" y="1.809078125"/>
<vertex x="-4.536946875" y="1.749515625"/>
</polygon>
<polygon width="0.01" layer="29" pour="solid">
<vertex x="-4.43704375" y="1.611525"/>
<vertex x="-4.32" y="1.599996875"/>
<vertex x="-4.20295625" y="1.611525"/>
<vertex x="-4.09040625" y="1.645665625"/>
<vertex x="-3.98665625" y="1.70111875"/>
<vertex x="-3.895734375" y="1.775734375"/>
<vertex x="-3.82111875" y="1.86665625"/>
<vertex x="-3.765665625" y="1.97040625"/>
<vertex x="-3.731525" y="2.08295625"/>
<vertex x="-3.72" y="2.1999875"/>
<vertex x="-3.72" y="3.0000125"/>
<vertex x="-3.731525" y="3.11704375"/>
<vertex x="-3.765665625" y="3.22959375"/>
<vertex x="-3.82111875" y="3.33334375"/>
<vertex x="-3.895734375" y="3.424265625"/>
<vertex x="-3.98665625" y="3.49888125"/>
<vertex x="-4.09040625" y="3.554334375"/>
<vertex x="-4.20295625" y="3.588475"/>
<vertex x="-4.32" y="3.600003125"/>
<vertex x="-4.43704375" y="3.588475"/>
<vertex x="-4.54959375" y="3.554334375"/>
<vertex x="-4.65334375" y="3.49888125"/>
<vertex x="-4.744265625" y="3.424265625"/>
<vertex x="-4.81888125" y="3.33334375"/>
<vertex x="-4.874334375" y="3.22959375"/>
<vertex x="-4.908475" y="3.11704375"/>
<vertex x="-4.92" y="3.0000125"/>
<vertex x="-4.92" y="2.1999875"/>
<vertex x="-4.908475" y="2.08295625"/>
<vertex x="-4.874334375" y="1.97040625"/>
<vertex x="-4.81888125" y="1.86665625"/>
<vertex x="-4.744265625" y="1.775734375"/>
<vertex x="-4.65334375" y="1.70111875"/>
<vertex x="-4.54959375" y="1.645665625"/>
</polygon>
<polygon width="0.01" layer="30" pour="solid">
<vertex x="-4.43704375" y="1.611525"/>
<vertex x="-4.32" y="1.599996875"/>
<vertex x="-4.20295625" y="1.611525"/>
<vertex x="-4.09040625" y="1.645665625"/>
<vertex x="-3.98665625" y="1.70111875"/>
<vertex x="-3.895734375" y="1.775734375"/>
<vertex x="-3.82111875" y="1.86665625"/>
<vertex x="-3.765665625" y="1.97040625"/>
<vertex x="-3.731525" y="2.08295625"/>
<vertex x="-3.72" y="2.1999875"/>
<vertex x="-3.72" y="3.0000125"/>
<vertex x="-3.731525" y="3.11704375"/>
<vertex x="-3.765665625" y="3.22959375"/>
<vertex x="-3.82111875" y="3.33334375"/>
<vertex x="-3.895734375" y="3.424265625"/>
<vertex x="-3.98665625" y="3.49888125"/>
<vertex x="-4.09040625" y="3.554334375"/>
<vertex x="-4.20295625" y="3.588475"/>
<vertex x="-4.32" y="3.600003125"/>
<vertex x="-4.43704375" y="3.588475"/>
<vertex x="-4.54959375" y="3.554334375"/>
<vertex x="-4.65334375" y="3.49888125"/>
<vertex x="-4.744265625" y="3.424265625"/>
<vertex x="-4.81888125" y="3.33334375"/>
<vertex x="-4.874334375" y="3.22959375"/>
<vertex x="-4.908475" y="3.11704375"/>
<vertex x="-4.92" y="3.0000125"/>
<vertex x="-4.92" y="2.1999875"/>
<vertex x="-4.908475" y="2.08295625"/>
<vertex x="-4.874334375" y="1.97040625"/>
<vertex x="-4.81888125" y="1.86665625"/>
<vertex x="-4.744265625" y="1.775734375"/>
<vertex x="-4.65334375" y="1.70111875"/>
<vertex x="-4.54959375" y="1.645665625"/>
</polygon>
<wire x1="4.02" y1="3" x2="4.32" y2="3.3" width="0" layer="46" curve="-90"/>
<wire x1="4.32" y1="3.3" x2="4.62" y2="3" width="0" layer="46" curve="-90"/>
<wire x1="4.62" y1="3" x2="4.62" y2="2.2" width="0" layer="46"/>
<wire x1="4.62" y1="2.2" x2="4.32" y2="1.9" width="0" layer="46" curve="-90"/>
<wire x1="4.32" y1="1.9" x2="4.02" y2="2.2" width="0" layer="46" curve="-90"/>
<wire x1="4.02" y1="2.2" x2="4.02" y2="3" width="0" layer="46"/>
<polygon width="0.01" layer="1" pour="solid">
<vertex x="4.2087375" y="1.7125375"/>
<vertex x="4.32" y="1.7"/>
<vertex x="4.4312625" y="1.7125375"/>
<vertex x="4.536946875" y="1.749515625"/>
<vertex x="4.6317375" y="1.809078125"/>
<vertex x="4.710921875" y="1.8882625"/>
<vertex x="4.770484375" y="1.983053125"/>
<vertex x="4.8074625" y="2.0887375"/>
<vertex x="4.82" y="2.20000625"/>
<vertex x="4.82" y="2.99999375"/>
<vertex x="4.8074625" y="3.1112625"/>
<vertex x="4.770484375" y="3.216946875"/>
<vertex x="4.710921875" y="3.3117375"/>
<vertex x="4.6317375" y="3.390921875"/>
<vertex x="4.536946875" y="3.450484375"/>
<vertex x="4.4312625" y="3.4874625"/>
<vertex x="4.32" y="3.5"/>
<vertex x="4.2087375" y="3.4874625"/>
<vertex x="4.103053125" y="3.450484375"/>
<vertex x="4.0082625" y="3.390921875"/>
<vertex x="3.929078125" y="3.3117375"/>
<vertex x="3.869515625" y="3.216946875"/>
<vertex x="3.8325375" y="3.1112625"/>
<vertex x="3.82" y="2.99999375"/>
<vertex x="3.82" y="2.20000625"/>
<vertex x="3.8325375" y="2.0887375"/>
<vertex x="3.869515625" y="1.983053125"/>
<vertex x="3.929078125" y="1.8882625"/>
<vertex x="4.0082625" y="1.809078125"/>
<vertex x="4.103053125" y="1.749515625"/>
</polygon>
<polygon width="0.01" layer="16" pour="solid">
<vertex x="4.2087375" y="1.7125375"/>
<vertex x="4.32" y="1.7"/>
<vertex x="4.4312625" y="1.7125375"/>
<vertex x="4.536946875" y="1.749515625"/>
<vertex x="4.6317375" y="1.809078125"/>
<vertex x="4.710921875" y="1.8882625"/>
<vertex x="4.770484375" y="1.983053125"/>
<vertex x="4.8074625" y="2.0887375"/>
<vertex x="4.82" y="2.20000625"/>
<vertex x="4.82" y="2.99999375"/>
<vertex x="4.8074625" y="3.1112625"/>
<vertex x="4.770484375" y="3.216946875"/>
<vertex x="4.710921875" y="3.3117375"/>
<vertex x="4.6317375" y="3.390921875"/>
<vertex x="4.536946875" y="3.450484375"/>
<vertex x="4.4312625" y="3.4874625"/>
<vertex x="4.32" y="3.5"/>
<vertex x="4.2087375" y="3.4874625"/>
<vertex x="4.103053125" y="3.450484375"/>
<vertex x="4.0082625" y="3.390921875"/>
<vertex x="3.929078125" y="3.3117375"/>
<vertex x="3.869515625" y="3.216946875"/>
<vertex x="3.8325375" y="3.1112625"/>
<vertex x="3.82" y="2.99999375"/>
<vertex x="3.82" y="2.20000625"/>
<vertex x="3.8325375" y="2.0887375"/>
<vertex x="3.869515625" y="1.983053125"/>
<vertex x="3.929078125" y="1.8882625"/>
<vertex x="4.0082625" y="1.809078125"/>
<vertex x="4.103053125" y="1.749515625"/>
</polygon>
<polygon width="0.01" layer="29" pour="solid">
<vertex x="4.20295625" y="1.611525"/>
<vertex x="4.32" y="1.599996875"/>
<vertex x="4.43704375" y="1.611525"/>
<vertex x="4.54959375" y="1.645665625"/>
<vertex x="4.65334375" y="1.70111875"/>
<vertex x="4.744265625" y="1.775734375"/>
<vertex x="4.81888125" y="1.86665625"/>
<vertex x="4.874334375" y="1.97040625"/>
<vertex x="4.908475" y="2.08295625"/>
<vertex x="4.92" y="2.1999875"/>
<vertex x="4.92" y="3.0000125"/>
<vertex x="4.908475" y="3.11704375"/>
<vertex x="4.874334375" y="3.22959375"/>
<vertex x="4.81888125" y="3.33334375"/>
<vertex x="4.744265625" y="3.424265625"/>
<vertex x="4.65334375" y="3.49888125"/>
<vertex x="4.54959375" y="3.554334375"/>
<vertex x="4.43704375" y="3.588475"/>
<vertex x="4.32" y="3.600003125"/>
<vertex x="4.20295625" y="3.588475"/>
<vertex x="4.09040625" y="3.554334375"/>
<vertex x="3.98665625" y="3.49888125"/>
<vertex x="3.895734375" y="3.424265625"/>
<vertex x="3.82111875" y="3.33334375"/>
<vertex x="3.765665625" y="3.22959375"/>
<vertex x="3.731525" y="3.11704375"/>
<vertex x="3.72" y="3.0000125"/>
<vertex x="3.72" y="2.1999875"/>
<vertex x="3.731525" y="2.08295625"/>
<vertex x="3.765665625" y="1.97040625"/>
<vertex x="3.82111875" y="1.86665625"/>
<vertex x="3.895734375" y="1.775734375"/>
<vertex x="3.98665625" y="1.70111875"/>
<vertex x="4.09040625" y="1.645665625"/>
</polygon>
<polygon width="0.01" layer="30" pour="solid">
<vertex x="4.20295625" y="1.611525"/>
<vertex x="4.32" y="1.599996875"/>
<vertex x="4.43704375" y="1.611525"/>
<vertex x="4.54959375" y="1.645665625"/>
<vertex x="4.65334375" y="1.70111875"/>
<vertex x="4.744265625" y="1.775734375"/>
<vertex x="4.81888125" y="1.86665625"/>
<vertex x="4.874334375" y="1.97040625"/>
<vertex x="4.908475" y="2.08295625"/>
<vertex x="4.92" y="2.1999875"/>
<vertex x="4.92" y="3.0000125"/>
<vertex x="4.908475" y="3.11704375"/>
<vertex x="4.874334375" y="3.22959375"/>
<vertex x="4.81888125" y="3.33334375"/>
<vertex x="4.744265625" y="3.424265625"/>
<vertex x="4.65334375" y="3.49888125"/>
<vertex x="4.54959375" y="3.554334375"/>
<vertex x="4.43704375" y="3.588475"/>
<vertex x="4.32" y="3.600003125"/>
<vertex x="4.20295625" y="3.588475"/>
<vertex x="4.09040625" y="3.554334375"/>
<vertex x="3.98665625" y="3.49888125"/>
<vertex x="3.895734375" y="3.424265625"/>
<vertex x="3.82111875" y="3.33334375"/>
<vertex x="3.765665625" y="3.22959375"/>
<vertex x="3.731525" y="3.11704375"/>
<vertex x="3.72" y="3.0000125"/>
<vertex x="3.72" y="2.1999875"/>
<vertex x="3.731525" y="2.08295625"/>
<vertex x="3.765665625" y="1.97040625"/>
<vertex x="3.82111875" y="1.86665625"/>
<vertex x="3.895734375" y="1.775734375"/>
<vertex x="3.98665625" y="1.70111875"/>
<vertex x="4.09040625" y="1.645665625"/>
</polygon>
<wire x1="-4.47" y1="7.35" x2="-4.47" y2="0" width="0.127" layer="51"/>
<wire x1="-4.47" y1="0" x2="4.47" y2="0" width="0.127" layer="51"/>
<wire x1="4.47" y1="0" x2="4.47" y2="7.35" width="0.127" layer="51"/>
<wire x1="4.47" y1="7.35" x2="-4.47" y2="7.35" width="0.127" layer="51"/>
<wire x1="4.47" y1="0" x2="9.25" y2="0" width="0.127" layer="51"/>
<wire x1="-4.47" y1="5.35" x2="-4.47" y2="3.85" width="0.127" layer="21"/>
<wire x1="4.47" y1="5.35" x2="4.47" y2="3.85" width="0.127" layer="21"/>
<wire x1="4.47" y1="1.35" x2="4.47" y2="0" width="0.127" layer="21"/>
<wire x1="-4.47" y1="1.35" x2="-4.47" y2="0" width="0.127" layer="21"/>
<wire x1="-5.07" y1="8.17" x2="-5.07" y2="-0.25" width="0.05" layer="39"/>
<wire x1="-5.07" y1="-0.25" x2="5.07" y2="-0.25" width="0.05" layer="39"/>
<wire x1="5.07" y1="-0.25" x2="5.07" y2="8.17" width="0.05" layer="39"/>
<wire x1="5.07" y1="8.17" x2="-5.07" y2="8.17" width="0.05" layer="39"/>
<circle x="-3.2" y="8.5" radius="0.1" width="0.2" layer="21"/>
<circle x="-3.2" y="8.5" radius="0.1" width="0.2" layer="51"/>
<text x="5.2" y="0.2" size="1" layer="51">PCB EDGE</text>
<text x="-5.25" y="10.39" size="1.27" layer="25">&gt;NAME</text>
<text x="-5.25" y="9.1" size="1.27" layer="27">&gt;VALUE</text>
<pad name="SH1" x="-4.32" y="6.78" drill="0.6" diameter="1" stop="no"/>
<pad name="SH2" x="4.32" y="6.78" drill="0.6" diameter="1" stop="no"/>
<pad name="SH3" x="-4.32" y="2.6" drill="0.6" diameter="1" stop="no"/>
<pad name="SH4" x="4.32" y="2.6" drill="0.6" diameter="1" stop="no"/>
<smd name="A6" x="-0.25" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="B7" x="-0.75" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="A5" x="-1.25" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="B8" x="-1.75" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="A7" x="0.25" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="B6" x="0.75" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="A8" x="1.25" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="B5" x="1.75" y="7.345" dx="0.3" dy="1.15" layer="1"/>
<smd name="A4_B9" x="-2.4" y="7.345" dx="0.6" dy="1.15" layer="1"/>
<smd name="A1_B12" x="-3.2" y="7.345" dx="0.6" dy="1.15" layer="1"/>
<smd name="B4_A9" x="2.4" y="7.345" dx="0.6" dy="1.15" layer="1"/>
<smd name="B1_A12" x="3.2" y="7.345" dx="0.6" dy="1.15" layer="1"/>
<hole x="-2.89" y="6.28" drill="0.65"/>
<hole x="2.89" y="6.28" drill="0.65"/>
</package>
</packages>
<symbols>
<symbol name="UJ20-C-H-G-SMT-1-P16-TR" library_version="2">
<wire x1="7.62" y1="22.86" x2="7.62" y2="-22.86" width="0.254" layer="94"/>
<wire x1="7.62" y1="-22.86" x2="-7.62" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-22.86" x2="-7.62" y2="22.86" width="0.254" layer="94"/>
<wire x1="-7.62" y1="22.86" x2="7.62" y2="22.86" width="0.254" layer="94"/>
<text x="-7.62" y="23.622" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-23.622" size="1.778" layer="96" align="top-left">&gt;VALUE</text>
<pin name="VBUS" x="12.7" y="20.32" length="middle" direction="pas" rot="R180"/>
<pin name="SHIELD" x="12.7" y="-20.32" length="middle" direction="pas" rot="R180"/>
<pin name="DN1" x="12.7" y="15.24" length="middle" direction="pas" rot="R180"/>
<pin name="DP1" x="12.7" y="12.7" length="middle" direction="pas" rot="R180"/>
<pin name="DN2" x="12.7" y="7.62" length="middle" direction="pas" rot="R180"/>
<pin name="DP2" x="12.7" y="5.08" length="middle" direction="pas" rot="R180"/>
<pin name="GND" x="12.7" y="-15.24" length="middle" direction="pas" rot="R180"/>
<pin name="CC1" x="12.7" y="0" length="middle" direction="pas" rot="R180"/>
<pin name="SBU1" x="12.7" y="-2.54" length="middle" direction="pas" rot="R180"/>
<pin name="CC2" x="12.7" y="-7.62" length="middle" direction="pas" rot="R180"/>
<pin name="SBU2" x="12.7" y="-10.16" length="middle" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="UJ20-C-H-G-SMT-1-P16-TR" prefix="J" library_version="2">
<gates>
<gate name="G$1" symbol="UJ20-C-H-G-SMT-1-P16-TR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SAMESKY_UJ20-C-H-G-SMT-1-P16-TR">
<connects>
<connect gate="G$1" pin="CC1" pad="A5"/>
<connect gate="G$1" pin="CC2" pad="B5"/>
<connect gate="G$1" pin="DN1" pad="A7"/>
<connect gate="G$1" pin="DN2" pad="B7"/>
<connect gate="G$1" pin="DP1" pad="A6"/>
<connect gate="G$1" pin="DP2" pad="B6"/>
<connect gate="G$1" pin="GND" pad="A1_B12 B1_A12"/>
<connect gate="G$1" pin="SBU1" pad="A8"/>
<connect gate="G$1" pin="SBU2" pad="B8"/>
<connect gate="G$1" pin="SHIELD" pad="SH1 SH2 SH3 SH4"/>
<connect gate="G$1" pin="VBUS" pad="A4_B9 B4_A9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MANUFACTURER" value="Same Sky"/>
<attribute name="MAXIMUM_PACKAGE_HEIGHT" value="3.46mm"/>
<attribute name="PARTREV" value="1.0"/>
<attribute name="STANDARD" value="Manufacturer Recommendations"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="PCF8574RGYR" urn="urn:adsk.wipprod:fs.file:vf.lcGkz4doQpyc2bgh-QTqqA">
<description>&lt;Texas Instruments PCF8574RGYR, 8-channel 8bit I/O Expander 100kHz, I2C, 20-Pin VQFN&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="SN74CB3Q3244RGYR" library_version="4">
<description>&lt;b&gt;RGY0020A&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-0.75" y="2.15" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="2" x="-1.65" y="1.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="3" x="-1.65" y="1.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="4" x="-1.65" y="0.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="5" x="-1.65" y="0.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="6" x="-1.65" y="-0.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="7" x="-1.65" y="-0.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="8" x="-1.65" y="-1.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="9" x="-1.65" y="-1.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="10" x="-0.75" y="-2.15" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="11" x="0.75" y="-2.15" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="12" x="1.65" y="-1.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="13" x="1.65" y="-1.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="14" x="1.65" y="-0.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="15" x="1.65" y="-0.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="16" x="1.65" y="0.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="17" x="1.65" y="0.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="18" x="1.65" y="1.25" dx="0.6" dy="0.25" layer="1"/>
<smd name="19" x="1.65" y="1.75" dx="0.6" dy="0.25" layer="1"/>
<smd name="20" x="0.75" y="2.15" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.75" y1="2.25" x2="1.75" y2="2.25" width="0.2" layer="51"/>
<wire x1="1.75" y1="2.25" x2="1.75" y2="-2.25" width="0.2" layer="51"/>
<wire x1="1.75" y1="-2.25" x2="-1.75" y2="-2.25" width="0.2" layer="51"/>
<wire x1="-1.75" y1="-2.25" x2="-1.75" y2="2.25" width="0.2" layer="51"/>
<wire x1="-2.95" y1="3.45" x2="2.95" y2="3.45" width="0.1" layer="51"/>
<wire x1="2.95" y1="3.45" x2="2.95" y2="-3.45" width="0.1" layer="51"/>
<wire x1="2.95" y1="-3.45" x2="-2.95" y2="-3.45" width="0.1" layer="51"/>
<wire x1="-2.95" y1="-3.45" x2="-2.95" y2="3.45" width="0.1" layer="51"/>
<wire x1="-1.75" y1="2.25" x2="-1.2" y2="2.25" width="0.1" layer="21"/>
<wire x1="1.75" y1="2.25" x2="1.2" y2="2.25" width="0.1" layer="21"/>
<wire x1="-0.3" y1="2.25" x2="0.3" y2="2.25" width="0.1" layer="21"/>
<wire x1="-1.75" y1="-2.25" x2="-1.2" y2="-2.25" width="0.1" layer="21"/>
<wire x1="-0.3" y1="-2.25" x2="0.3" y2="-2.25" width="0.1" layer="21"/>
<wire x1="1.75" y1="-2.25" x2="1.2" y2="-2.25" width="0.1" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="PCF8574RGYR" library_version="4">
<wire x1="5.08" y1="10.16" x2="25.4" y2="10.16" width="0.254" layer="94"/>
<wire x1="25.4" y1="-25.4" x2="25.4" y2="10.16" width="0.254" layer="94"/>
<wire x1="25.4" y1="-25.4" x2="5.08" y2="-25.4" width="0.254" layer="94"/>
<wire x1="5.08" y1="10.16" x2="5.08" y2="-25.4" width="0.254" layer="94"/>
<text x="26.67" y="15.24" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="26.67" y="12.7" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="!INT" x="12.7" y="15.24" length="middle" rot="R270"/>
<pin name="SCL" x="0" y="0" length="middle"/>
<pin name="NC_1" x="0" y="-2.54" length="middle"/>
<pin name="SDA" x="0" y="-5.08" length="middle"/>
<pin name="VDD" x="0" y="-7.62" length="middle"/>
<pin name="A0" x="0" y="-10.16" length="middle"/>
<pin name="A1" x="0" y="-12.7" length="middle"/>
<pin name="NC_2" x="0" y="-15.24" length="middle"/>
<pin name="A2" x="0" y="-17.78" length="middle"/>
<pin name="P0" x="12.7" y="-30.48" length="middle" rot="R90"/>
<pin name="P1" x="15.24" y="-30.48" length="middle" rot="R90"/>
<pin name="P2" x="30.48" y="-17.78" length="middle" rot="R180"/>
<pin name="NC_3" x="30.48" y="-15.24" length="middle" rot="R180"/>
<pin name="P3" x="30.48" y="-12.7" length="middle" rot="R180"/>
<pin name="GND" x="30.48" y="-10.16" length="middle" rot="R180"/>
<pin name="P4" x="30.48" y="-7.62" length="middle" rot="R180"/>
<pin name="P5" x="30.48" y="-5.08" length="middle" rot="R180"/>
<pin name="NC_4" x="30.48" y="-2.54" length="middle" rot="R180"/>
<pin name="P6" x="30.48" y="0" length="middle" rot="R180"/>
<pin name="P7" x="17.78" y="15.24" length="middle" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PCF8574RGYR" prefix="IC" library_version="4">
<description>&lt;b&gt;Texas Instruments PCF8574RGYR, 8-channel 8bit I/O Expander 100kHz, I2C, 20-Pin VQFN&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://www.ti.com/lit/gpn/pcf8574"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="PCF8574RGYR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SN74CB3Q3244RGYR">
<connects>
<connect gate="G$1" pin="!INT" pad="1"/>
<connect gate="G$1" pin="A0" pad="6"/>
<connect gate="G$1" pin="A1" pad="7"/>
<connect gate="G$1" pin="A2" pad="9"/>
<connect gate="G$1" pin="GND" pad="15"/>
<connect gate="G$1" pin="NC_1" pad="3"/>
<connect gate="G$1" pin="NC_2" pad="8"/>
<connect gate="G$1" pin="NC_3" pad="13"/>
<connect gate="G$1" pin="NC_4" pad="18"/>
<connect gate="G$1" pin="P0" pad="10"/>
<connect gate="G$1" pin="P1" pad="11"/>
<connect gate="G$1" pin="P2" pad="12"/>
<connect gate="G$1" pin="P3" pad="14"/>
<connect gate="G$1" pin="P4" pad="16"/>
<connect gate="G$1" pin="P5" pad="17"/>
<connect gate="G$1" pin="P6" pad="19"/>
<connect gate="G$1" pin="P7" pad="20"/>
<connect gate="G$1" pin="SCL" pad="2"/>
<connect gate="G$1" pin="SDA" pad="4"/>
<connect gate="G$1" pin="VDD" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="595-PCF8574RGYR" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Texas-Instruments/PCF8574RGYR?qs=wgAEGBTxy7kR2T7hhFxD0g%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Texas Instruments" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="PCF8574RGYR" constant="no"/>
<attribute name="DESCRIPTION" value="Texas Instruments PCF8574RGYR, 8-channel 8bit I/O Expander 100kHz, I2C, 20-Pin VQFN" constant="no"/>
<attribute name="HEIGHT" value="1mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="BNO085" urn="urn:adsk.wipprod:fs.file:vf.KeicR6v6QYquMuzG2LVDPw">
<description>&lt;Board Mount Motion &amp; Position Sensors 9-axis IMU&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="BNO085" library_version="1">
<description>&lt;b&gt;BNO085-3&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="1.563" y="2.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="2" x="0.75" y="2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="3" x="0.25" y="2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="4" x="-0.25" y="2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="5" x="-0.75" y="2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="6" x="-1.563" y="2.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="7" x="-1.563" y="1.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="8" x="-1.563" y="1.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="9" x="-1.563" y="0.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="10" x="-1.563" y="0.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="11" x="-1.563" y="-0.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="12" x="-1.563" y="-0.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="13" x="-1.563" y="-1.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="14" x="-1.563" y="-1.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="15" x="-1.563" y="-2.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="16" x="-0.75" y="-2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="17" x="-0.25" y="-2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="18" x="0.25" y="-2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="19" x="0.75" y="-2.313" dx="0.575" dy="0.25" layer="1" rot="R90"/>
<smd name="20" x="1.563" y="-2.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="21" x="1.563" y="-1.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="22" x="1.563" y="-1.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="23" x="1.563" y="-0.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="24" x="1.563" y="-0.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="25" x="1.563" y="0.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="26" x="1.563" y="0.75" dx="0.675" dy="0.25" layer="1"/>
<smd name="27" x="1.563" y="1.25" dx="0.675" dy="0.25" layer="1"/>
<smd name="28" x="1.563" y="1.75" dx="0.675" dy="0.25" layer="1"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.9" y1="-2.6" x2="1.9" y2="-2.6" width="0.1" layer="51"/>
<wire x1="1.9" y1="-2.6" x2="1.9" y2="2.6" width="0.1" layer="51"/>
<wire x1="1.9" y1="2.6" x2="-1.9" y2="2.6" width="0.1" layer="51"/>
<wire x1="-1.9" y1="2.6" x2="-1.9" y2="-2.6" width="0.1" layer="51"/>
<wire x1="-2.9" y1="3.6" x2="2.9" y2="3.6" width="0.1" layer="51"/>
<wire x1="2.9" y1="3.6" x2="2.9" y2="-3.601" width="0.1" layer="51"/>
<wire x1="2.9" y1="-3.601" x2="-2.9" y2="-3.601" width="0.1" layer="51"/>
<wire x1="-2.9" y1="-3.601" x2="-2.9" y2="3.6" width="0.1" layer="51"/>
<wire x1="2.4" y1="2.25" x2="2.5" y2="2.25" width="0.2" layer="21" curve="180"/>
<wire x1="2.5" y1="2.25" x2="2.4" y2="2.25" width="0.2" layer="21" curve="180"/>
<wire x1="2.4" y1="2.25" x2="2.5" y2="2.25" width="0.2" layer="21" curve="180"/>
</package>
</packages>
<symbols>
<symbol name="BNO085" library_version="1">
<wire x1="5.08" y1="12.7" x2="45.72" y2="12.7" width="0.254" layer="94"/>
<wire x1="45.72" y1="-43.18" x2="45.72" y2="12.7" width="0.254" layer="94"/>
<wire x1="45.72" y1="-43.18" x2="5.08" y2="-43.18" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="5.08" y2="-43.18" width="0.254" layer="94"/>
<text x="46.99" y="17.78" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="46.99" y="15.24" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="RESV_NC_1" x="50.8" y="0" length="middle" rot="R180"/>
<pin name="GND_1" x="27.94" y="17.78" length="middle" rot="R270"/>
<pin name="VDD" x="25.4" y="17.78" length="middle" rot="R270"/>
<pin name="BOOTN" x="22.86" y="17.78" length="middle" rot="R270"/>
<pin name="PS1" x="20.32" y="17.78" length="middle" rot="R270"/>
<pin name="PS0/WAKE" x="0" y="0" length="middle"/>
<pin name="RESV_NC_2" x="0" y="-2.54" length="middle"/>
<pin name="RESV_NC_3" x="0" y="-5.08" length="middle"/>
<pin name="CAP" x="0" y="-7.62" length="middle"/>
<pin name="CLKSEL0" x="0" y="-10.16" length="middle"/>
<pin name="NRST" x="0" y="-12.7" length="middle"/>
<pin name="RESV_NC_4" x="0" y="-15.24" length="middle"/>
<pin name="RESV_NC_5" x="0" y="-17.78" length="middle"/>
<pin name="H_INTN" x="0" y="-20.32" length="middle"/>
<pin name="ENV_SCL_" x="0" y="-22.86" length="middle"/>
<pin name="ENV_SDA" x="20.32" y="-48.26" length="middle" rot="R90"/>
<pin name="SA0/H_MOSI_" x="22.86" y="-48.26" length="middle" rot="R90"/>
<pin name="H_CSN" x="25.4" y="-48.26" length="middle" rot="R90"/>
<pin name="H_SCL/SCK/RX" x="27.94" y="-48.26" length="middle" rot="R90"/>
<pin name="H_SDA/H_MISO/TX_" x="50.8" y="-22.86" length="middle" rot="R180"/>
<pin name="RESV_NC_6" x="50.8" y="-20.32" length="middle" rot="R180"/>
<pin name="RESV_NC_7" x="50.8" y="-17.78" length="middle" rot="R180"/>
<pin name="RESV_NC_8" x="50.8" y="-15.24" length="middle" rot="R180"/>
<pin name="RESV_NC_9" x="50.8" y="-12.7" length="middle" rot="R180"/>
<pin name="GND_2" x="50.8" y="-10.16" length="middle" rot="R180"/>
<pin name="XOUT32/CLKSEL1" x="50.8" y="-7.62" length="middle" rot="R180"/>
<pin name="XIN32" x="50.8" y="-5.08" length="middle" rot="R180"/>
<pin name="VDDIO" x="50.8" y="-2.54" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="BNO085" prefix="IC" library_version="1">
<description>&lt;b&gt;Board Mount Motion &amp; Position Sensors 9-axis IMU&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.ceva-dsp.com/wp-content/uploads/2019/10/BNO080_085-Datasheet.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="BNO085" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BNO085">
<connects>
<connect gate="G$1" pin="BOOTN" pad="4"/>
<connect gate="G$1" pin="CAP" pad="9"/>
<connect gate="G$1" pin="CLKSEL0" pad="10"/>
<connect gate="G$1" pin="ENV_SCL_" pad="15"/>
<connect gate="G$1" pin="ENV_SDA" pad="16"/>
<connect gate="G$1" pin="GND_1" pad="2"/>
<connect gate="G$1" pin="GND_2" pad="25"/>
<connect gate="G$1" pin="H_CSN" pad="18"/>
<connect gate="G$1" pin="H_INTN" pad="14"/>
<connect gate="G$1" pin="H_SCL/SCK/RX" pad="19"/>
<connect gate="G$1" pin="H_SDA/H_MISO/TX_" pad="20"/>
<connect gate="G$1" pin="NRST" pad="11"/>
<connect gate="G$1" pin="PS0/WAKE" pad="6"/>
<connect gate="G$1" pin="PS1" pad="5"/>
<connect gate="G$1" pin="RESV_NC_1" pad="1"/>
<connect gate="G$1" pin="RESV_NC_2" pad="7"/>
<connect gate="G$1" pin="RESV_NC_3" pad="8"/>
<connect gate="G$1" pin="RESV_NC_4" pad="12"/>
<connect gate="G$1" pin="RESV_NC_5" pad="13"/>
<connect gate="G$1" pin="RESV_NC_6" pad="21"/>
<connect gate="G$1" pin="RESV_NC_7" pad="22"/>
<connect gate="G$1" pin="RESV_NC_8" pad="23"/>
<connect gate="G$1" pin="RESV_NC_9" pad="24"/>
<connect gate="G$1" pin="SA0/H_MOSI_" pad="17"/>
<connect gate="G$1" pin="VDD" pad="3"/>
<connect gate="G$1" pin="VDDIO" pad="28"/>
<connect gate="G$1" pin="XIN32" pad="27"/>
<connect gate="G$1" pin="XOUT32/CLKSEL1" pad="26"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="526-BNO085" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/CEVA/BNO085?qs=ulEaXIWI0c9BFVeZDQCmmQ%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="CEVA" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="BNO085" constant="no"/>
<attribute name="DESCRIPTION" value="Board Mount Motion &amp; Position Sensors 9-axis IMU" constant="no"/>
<attribute name="HEIGHT" value="1.18mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="830009706" urn="urn:adsk.wipprod:fs.file:vf.M16k7mWdQ5aB1VZZsRisGQ">
<description>&lt;WE-XTAL Quartz Crystal CFPX-217; 3.2 x 1.5mm; 32.7680 kHz; Tol = +/-20 ppm; Stab = +/-- ppm Load Cap = 9 pF;&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="830009706" library_version="2">
<description>&lt;b&gt;830009706-2&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-1.25" y="0" dx="1.9" dy="1.1" layer="1" rot="R90"/>
<smd name="2" x="1.25" y="0" dx="1.9" dy="1.1" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.6" y1="0.75" x2="1.6" y2="0.75" width="0.1" layer="51"/>
<wire x1="1.6" y1="0.75" x2="1.6" y2="-0.75" width="0.1" layer="51"/>
<wire x1="1.6" y1="-0.75" x2="-1.6" y2="-0.75" width="0.1" layer="51"/>
<wire x1="-1.6" y1="-0.75" x2="-1.6" y2="0.75" width="0.1" layer="51"/>
<wire x1="-2.8" y1="1.95" x2="2.8" y2="1.95" width="0.1" layer="51"/>
<wire x1="2.8" y1="1.95" x2="2.8" y2="-1.95" width="0.1" layer="51"/>
<wire x1="2.8" y1="-1.95" x2="-2.8" y2="-1.95" width="0.1" layer="51"/>
<wire x1="-2.8" y1="-1.95" x2="-2.8" y2="1.95" width="0.1" layer="51"/>
<wire x1="-2.3" y1="0" x2="-2.4" y2="0" width="0.1" layer="21" curve="180"/>
<wire x1="-2.4" y1="0" x2="-2.3" y2="0" width="0.1" layer="21" curve="180"/>
<wire x1="-0.4" y1="0.75" x2="0.4" y2="0.75" width="0.2" layer="21"/>
<wire x1="-0.4" y1="-0.75" x2="0.4" y2="-0.75" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="830009706" library_version="2">
<wire x1="5.588" y1="2.54" x2="5.588" y2="-2.54" width="0.254" layer="94"/>
<wire x1="7.112" y1="2.54" x2="7.112" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="5.588" y2="0" width="0.254" layer="94"/>
<wire x1="7.112" y1="0" x2="7.62" y2="0" width="0.254" layer="94"/>
<text x="8.89" y="6.35" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="8.89" y="3.81" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" visible="pad" length="middle"/>
<pin name="2" x="12.7" y="0" visible="pad" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="830009706" prefix="C" library_version="2">
<description>&lt;b&gt;WE-XTAL Quartz Crystal CFPX-217; 3.2 x 1.5mm; 32.7680 kHz; Tol = +/-20 ppm; Stab = +/-- ppm Load Cap = 9 pF;&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.we-online.com/catalog/datasheet/830009706.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="830009706" x="0" y="0"/>
</gates>
<devices>
<device name="" package="830009706">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="710-830009706" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Wurth-Elektronik/830009706?qs=2WXlatMagcFmeMIz1Bq3%2Fg%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Wurth Elektronik" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="830009706" constant="no"/>
<attribute name="DESCRIPTION" value="WE-XTAL Quartz Crystal CFPX-217; 3.2 x 1.5mm; 32.7680 kHz; Tol = +/-20 ppm; Stab = +/-- ppm Load Cap = 9 pF;" constant="no"/>
<attribute name="HEIGHT" value="0.9mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="TFT_Library" urn="urn:adsk.wipprod:fs.file:vf.OMwaF8U3QfOV1ezvEUx29w">
<packages>
<package name="1.47_IN_TFT_172_320_ST7789P3" library_version="13">
<wire x1="0" y1="0" x2="0" y2="20.955" width="0.127" layer="21"/>
<wire x1="0" y1="0" x2="43.9928" y2="0" width="0.127" layer="21"/>
<wire x1="0" y1="20.955" x2="43.9928" y2="20.955" width="0.127" layer="21"/>
<wire x1="43.9928" y1="0" x2="43.9928" y2="20.955" width="0.127" layer="21"/>
<pad name="P$1" x="1.27" y="19.05" drill="1.05"/>
<pad name="P$2" x="1.27" y="16.51" drill="1.05"/>
<pad name="P$3" x="1.27" y="13.97" drill="1.05"/>
<pad name="P$4" x="1.27" y="11.43" drill="1.05"/>
<pad name="P$5" x="1.27" y="8.89" drill="1.05"/>
<pad name="P$6" x="1.27" y="6.35" drill="1.05"/>
<pad name="P$7" x="1.27" y="3.81" drill="1.05"/>
<pad name="P$8" x="1.27" y="1.27" drill="1.05"/>
</package>
</packages>
<symbols>
<symbol name="1.47_IN_TFT_172_320_ST7789P3" library_version="13">
<pin name="BL" x="-15.24" y="15.24" length="middle"/>
<pin name="CS" x="-15.24" y="12.7" length="middle"/>
<pin name="DC" x="-15.24" y="10.16" length="middle"/>
<pin name="RES" x="-15.24" y="7.62" length="middle"/>
<pin name="SDA" x="-15.24" y="5.08" length="middle"/>
<pin name="SCL" x="-15.24" y="2.54" length="middle"/>
<pin name="VDD" x="-15.24" y="0" length="middle"/>
<pin name="GND" x="-15.24" y="-2.54" length="middle"/>
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="-5.933440625" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-5.933440625" x2="12.345471875" y2="-5.933440625" width="0.254" layer="94"/>
<wire x1="12.345471875" y1="-5.933440625" x2="12.345471875" y2="17.78" width="0.254" layer="94"/>
<wire x1="12.345471875" y1="17.78" x2="-10.16" y2="17.78" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1.47_IN_TFT_172_320_ST7789P3" library_version="13">
<gates>
<gate name="G$1" symbol="1.47_IN_TFT_172_320_ST7789P3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1.47_IN_TFT_172_320_ST7789P3">
<connects>
<connect gate="G$1" pin="BL" pad="P$1"/>
<connect gate="G$1" pin="CS" pad="P$2"/>
<connect gate="G$1" pin="DC" pad="P$3"/>
<connect gate="G$1" pin="GND" pad="P$8"/>
<connect gate="G$1" pin="RES" pad="P$4"/>
<connect gate="G$1" pin="SCL" pad="P$6"/>
<connect gate="G$1" pin="SDA" pad="P$5"/>
<connect gate="G$1" pin="VDD" pad="P$7"/>
</connects>
<technologies>
<technology name="">
<attribute name="CATEGORY_L1" value="" constant="no"/>
<attribute name="DATASHEET" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="CATEGORY_L2" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="" constant="no"/>
<attribute name="VENDOR" value="" constant="no"/>
<attribute name="VPN" value="" constant="no"/>
<attribute name="PACKAGE" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="JS1300AQ" urn="urn:adsk.wipprod:fs.file:vf.CcEUDwFHTFK9mms8L6KdfA">
<description>&lt;ANTI-VANDAL, No Internal Switch Contacts, Pilot Indicator Panel Mount, Front&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="JS1300" library_version="1">
<description>&lt;b&gt;JS1300&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-4.813" y="-1.06" dx="1" dy="1" layer="1"/>
<smd name="2" x="4.987" y="-1.06" dx="1" dy="1" layer="1"/>
<smd name="3" x="4.987" y="1.14" dx="1" dy="1" layer="1"/>
<smd name="4" x="-4.813" y="1.14" dx="1" dy="1" layer="1"/>
<smd name="5" x="-1.813" y="4.94" dx="1" dy="1" layer="1"/>
<smd name="6" x="0.087" y="4.94" dx="1" dy="1" layer="1"/>
<smd name="7" x="1.987" y="4.94" dx="1" dy="1" layer="1"/>
<smd name="8" x="-1.813" y="-4.86" dx="1" dy="1" layer="1"/>
<smd name="9" x="0.087" y="-4.86" dx="1" dy="1" layer="1"/>
<smd name="10" x="1.987" y="-4.86" dx="1" dy="1" layer="1"/>
<smd name="11" x="4.22356875" y="-4.09656875" dx="1" dy="1" layer="1" rot="R135"/>
<smd name="12" x="4.22356875" y="4.17656875" dx="1" dy="1" layer="1" rot="R45"/>
<smd name="13" x="-4.04956875" y="4.17656875" dx="1" dy="1" layer="1" rot="R135"/>
<smd name="14" x="-4.04956875" y="-4.09656875" dx="1" dy="1" layer="1" rot="R45"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-4.9" y1="4.9" x2="4.9" y2="4.9" width="0.2" layer="51"/>
<wire x1="4.9" y1="4.9" x2="4.9" y2="-4.9" width="0.2" layer="51"/>
<wire x1="4.9" y1="-4.9" x2="-4.9" y2="-4.9" width="0.2" layer="51"/>
<wire x1="-4.9" y1="-4.9" x2="-4.9" y2="4.9" width="0.2" layer="51"/>
<circle x="-6.498" y="-0.996" radius="0.18125" width="0.4" layer="25"/>
</package>
</packages>
<symbols>
<symbol name="JS1300AQ" library_version="1">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-12.7" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-12.7" x2="5.08" y2="-12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-12.7" width="0.254" layer="94"/>
<text x="16.51" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="16.51" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="A" x="0" y="0" length="middle"/>
<pin name="B" x="0" y="-2.54" length="middle"/>
<pin name="C" x="0" y="-5.08" length="middle"/>
<pin name="D" x="0" y="-7.62" length="middle"/>
<pin name="E" x="0" y="-10.16" length="middle"/>
<pin name="F" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="G" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="H" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="J" x="20.32" y="-7.62" length="middle" rot="R180"/>
<pin name="K" x="20.32" y="-10.16" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="JS1300AQ" prefix="S" library_version="1">
<description>&lt;b&gt;ANTI-VANDAL, No Internal Switch Contacts, Pilot Indicator Panel Mount, Front&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://configured-product-images.s3.amazonaws.com/2D/specs/5501M21.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="JS1300AQ" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JS1300">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$1" pin="B" pad="2"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="D" pad="4"/>
<connect gate="G$1" pin="E" pad="5"/>
<connect gate="G$1" pin="F" pad="6"/>
<connect gate="G$1" pin="G" pad="7"/>
<connect gate="G$1" pin="H" pad="8"/>
<connect gate="G$1" pin="J" pad="9"/>
<connect gate="G$1" pin="K" pad="10"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="612-JS1300AQ" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/E-Switch/JS1300AQ?qs=cyOInwlKnRNRSQbl9aaldA%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="E-Switch" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="JS1300AQ" constant="no"/>
<attribute name="DESCRIPTION" value="ANTI-VANDAL, No Internal Switch Contacts, Pilot Indicator Panel Mount, Front" constant="no"/>
<attribute name="HEIGHT" value="mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="F31L-1A7H1-11024" urn="urn:adsk.wipprod:fs.file:vf.R1_jZztcQ9au8PnQwM-Qyw">
<description>&lt;Flex Connector, 0.50mm Pitch, Height 2.55mm, Right angle, Flip type, ZIF, 24 position , With MYLAR&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="F31L1A7H111024" library_version="1">
<description>&lt;b&gt;F31L-1A7H1-11024-4&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-5.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="2" x="-5.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="3" x="-4.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="4" x="-4.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="5" x="-3.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="6" x="-3.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="7" x="-2.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="8" x="-2.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="9" x="-1.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="10" x="-1.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="11" x="-0.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="12" x="-0.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="13" x="0.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="14" x="0.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="15" x="1.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="16" x="1.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="17" x="2.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="18" x="2.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="19" x="3.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="20" x="3.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="21" x="4.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="22" x="4.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="23" x="5.25" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="24" x="5.75" y="3.135" dx="1.3" dy="0.3" layer="1" rot="R90"/>
<smd name="MP1" x="-7.9" y="-2.515" dx="2.2" dy="1.8" layer="1" rot="R90"/>
<smd name="MP2" x="7.9" y="-2.515" dx="2.2" dy="1.8" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-9.8" y1="4.785" x2="9.8" y2="4.785" width="0.1" layer="51"/>
<wire x1="9.8" y1="4.785" x2="9.8" y2="-4.785" width="0.1" layer="51"/>
<wire x1="9.8" y1="-4.785" x2="-9.8" y2="-4.785" width="0.1" layer="51"/>
<wire x1="-9.8" y1="-4.785" x2="-9.8" y2="4.785" width="0.1" layer="51"/>
<wire x1="0" y1="2.485" x2="-8.65" y2="2.485" width="0.1" layer="51"/>
<wire x1="-8.65" y1="2.485" x2="-8.65" y2="-3.115" width="0.1" layer="51"/>
<wire x1="-8.65" y1="-3.115" x2="-6" y2="-3.115" width="0.1" layer="51"/>
<wire x1="-6" y1="-3.115" x2="-5.5" y2="-3.785" width="0.1" layer="51"/>
<wire x1="-5.5" y1="-3.785" x2="5.5" y2="-3.785" width="0.1" layer="51"/>
<wire x1="5.5" y1="-3.785" x2="6" y2="-3.115" width="0.1" layer="51"/>
<wire x1="6" y1="-3.115" x2="8.65" y2="-3.115" width="0.1" layer="51"/>
<wire x1="8.65" y1="-3.115" x2="8.65" y2="2.485" width="0.1" layer="51"/>
<wire x1="8.65" y1="2.485" x2="0" y2="2.485" width="0.1" layer="51"/>
<wire x1="-5.75" y1="4.175" x2="-5.75" y2="4.275" width="0.1" layer="21" curve="180"/>
<wire x1="-5.75" y1="4.275" x2="-5.75" y2="4.175" width="0.1" layer="21" curve="180"/>
<wire x1="-6.3" y1="2.485" x2="-8.65" y2="2.485" width="0.2" layer="21"/>
<wire x1="-8.65" y1="2.485" x2="-8.65" y2="-0.925" width="0.2" layer="21"/>
<wire x1="-6.6" y1="-3.115" x2="-6" y2="-3.115" width="0.2" layer="21"/>
<wire x1="-6" y1="-3.115" x2="-5.5" y2="-3.785" width="0.2" layer="21"/>
<wire x1="-5.5" y1="-3.785" x2="5.5" y2="-3.785" width="0.2" layer="21"/>
<wire x1="5.5" y1="-3.785" x2="6" y2="-3.115" width="0.2" layer="21"/>
<wire x1="6" y1="-3.115" x2="6.6" y2="-3.115" width="0.2" layer="21"/>
<wire x1="8.65" y1="-0.925" x2="8.65" y2="2.485" width="0.2" layer="21"/>
<wire x1="8.65" y1="2.485" x2="6.3" y2="2.485" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="F31L-1A7H1-11024" library_version="1">
<wire x1="5.08" y1="2.54" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="-60.96" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="-60.96" x2="5.08" y2="-60.96" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-60.96" width="0.254" layer="94"/>
<text x="21.59" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="21.59" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="2" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="3" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="4" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="5" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="6" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="7" x="25.4" y="-15.24" length="middle" rot="R180"/>
<pin name="8" x="25.4" y="-17.78" length="middle" rot="R180"/>
<pin name="9" x="25.4" y="-20.32" length="middle" rot="R180"/>
<pin name="10" x="25.4" y="-22.86" length="middle" rot="R180"/>
<pin name="11" x="25.4" y="-25.4" length="middle" rot="R180"/>
<pin name="12" x="25.4" y="-27.94" length="middle" rot="R180"/>
<pin name="13" x="25.4" y="-30.48" length="middle" rot="R180"/>
<pin name="14" x="25.4" y="-33.02" length="middle" rot="R180"/>
<pin name="15" x="25.4" y="-35.56" length="middle" rot="R180"/>
<pin name="16" x="25.4" y="-38.1" length="middle" rot="R180"/>
<pin name="17" x="25.4" y="-40.64" length="middle" rot="R180"/>
<pin name="18" x="25.4" y="-43.18" length="middle" rot="R180"/>
<pin name="19" x="25.4" y="-45.72" length="middle" rot="R180"/>
<pin name="20" x="25.4" y="-48.26" length="middle" rot="R180"/>
<pin name="21" x="25.4" y="-50.8" length="middle" rot="R180"/>
<pin name="22" x="25.4" y="-53.34" length="middle" rot="R180"/>
<pin name="23" x="25.4" y="-55.88" length="middle" rot="R180"/>
<pin name="24" x="25.4" y="-58.42" length="middle" rot="R180"/>
<pin name="MP1" x="0" y="0" length="middle"/>
<pin name="MP2" x="0" y="-2.54" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="F31L-1A7H1-11024" prefix="J" library_version="1">
<description>&lt;b&gt;Flex Connector, 0.50mm Pitch, Height 2.55mm, Right angle, Flip type, ZIF, 24 position , With MYLAR&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://cdn.amphenol-cs.com/media/wysiwyg/files/drawing/a-s0099-lf31l.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="F31L-1A7H1-11024" x="0" y="0"/>
</gates>
<devices>
<device name="" package="F31L1A7H111024">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="MP1" pad="MP1"/>
<connect gate="G$1" pin="MP2" pad="MP2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="649-F31L-1A7H1-11024" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Amphenol-Aorora/F31L-1A7H1-11024?qs=xZ%2FP%252Ba9zWqYLk4%2F4aeCtBg%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Amphenol" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="F31L-1A7H1-11024" constant="no"/>
<attribute name="DESCRIPTION" value="Flex Connector, 0.50mm Pitch, Height 2.55mm, Right angle, Flip type, ZIF, 24 position , With MYLAR" constant="no"/>
<attribute name="HEIGHT" value="2.75mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="CAY16-103J4LF" urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g">
<description>&lt;4-array convex 0603 LF resistor,10K Bourns CAY16 Series 10k +/-5% Isolated SMT Resistor Array, 4 Resistors, 0.25W total 1206 package Convex&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="CAY16151J4LF" library_version="1">
<description>&lt;b&gt;CAY16-151J4LF-2&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-1.2" y="-0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="2" x="-0.4" y="-0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="3" x="0.4" y="-0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="4" x="1.2" y="-0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="5" x="1.2" y="0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="6" x="0.4" y="0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="7" x="-0.4" y="0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<smd name="8" x="-1.2" y="0.85" dx="0.9" dy="0.425" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.6" y1="0.8" x2="1.6" y2="0.8" width="0.2" layer="51"/>
<wire x1="1.6" y1="0.8" x2="1.6" y2="-0.8" width="0.2" layer="51"/>
<wire x1="1.6" y1="-0.8" x2="-1.6" y2="-0.8" width="0.2" layer="51"/>
<wire x1="-1.6" y1="-0.8" x2="-1.6" y2="0.8" width="0.2" layer="51"/>
<wire x1="-2.3" y1="2" x2="2.3" y2="2" width="0.1" layer="51"/>
<wire x1="2.3" y1="2" x2="2.3" y2="-2" width="0.1" layer="51"/>
<wire x1="2.3" y1="-2" x2="-2.3" y2="-2" width="0.1" layer="51"/>
<wire x1="-2.3" y1="-2" x2="-2.3" y2="2" width="0.1" layer="51"/>
<wire x1="-1.6" y1="0.8" x2="-1.6" y2="-0.8" width="0.1" layer="21"/>
<wire x1="1.6" y1="0.8" x2="1.6" y2="-0.8" width="0.1" layer="21"/>
<wire x1="-1.2" y1="-1.6" x2="-1.2" y2="-1.7" width="0.1" layer="21" curve="180"/>
<wire x1="-1.2" y1="-1.7" x2="-1.2" y2="-1.6" width="0.1" layer="21" curve="180"/>
</package>
</packages>
<symbols>
<symbol name="CAY16-103J4LF" library_version="1">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-10.16" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<text x="16.51" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="16.51" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" visible="pad" length="middle"/>
<pin name="2" x="0" y="-2.54" visible="pad" length="middle"/>
<pin name="3" x="0" y="-5.08" visible="pad" length="middle"/>
<pin name="4" x="0" y="-7.62" visible="pad" length="middle"/>
<pin name="5" x="20.32" y="-7.62" visible="pad" length="middle" rot="R180"/>
<pin name="6" x="20.32" y="-5.08" visible="pad" length="middle" rot="R180"/>
<pin name="7" x="20.32" y="-2.54" visible="pad" length="middle" rot="R180"/>
<pin name="8" x="20.32" y="0" visible="pad" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CAY16-103J4LF" prefix="RN" library_version="1">
<description>&lt;b&gt;4-array convex 0603 LF resistor,10K Bourns CAY16 Series 10k +/-5% Isolated SMT Resistor Array, 4 Resistors, 0.25W total 1206 package Convex&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://componentsearchengine.com/Datasheets/2/CAY16-103J4LF.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="CAY16-103J4LF" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAY16151J4LF">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="652-CAY16-103J4LF" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Bourns/CAY16-103J4LF?qs=6yLoizYthp5P0DFw3TvYqA%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Bourns" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="CAY16-103J4LF" constant="no"/>
<attribute name="DESCRIPTION" value="4-array convex 0603 LF resistor,10K Bourns CAY16 Series 10k +/-5% Isolated SMT Resistor Array, 4 Resistors, 0.25W total 1206 package Convex" constant="no"/>
<attribute name="HEIGHT" value="0.6mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="STM32G071C8U6TR" urn="urn:adsk.wipprod:fs.file:vf.njSnwR1zRQ-aCaWkX6R64g">
<description>&lt;Arm Cortex-M0+ 32-bit MCU, up to 128 KB Flash, 36 KB RAM, 4x USART, timers, ADC, DAC, comm. I/Fs, 1.7-3.6V&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="QFN50P700X700X65-49N" library_version="2">
<description>&lt;b&gt;. UFQFPN48 - 48-lead+-&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-3.45" y="2.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="2" x="-3.45" y="2.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="3" x="-3.45" y="1.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="4" x="-3.45" y="1.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="5" x="-3.45" y="0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="6" x="-3.45" y="0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="7" x="-3.45" y="-0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="8" x="-3.45" y="-0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="9" x="-3.45" y="-1.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="10" x="-3.45" y="-1.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="11" x="-3.45" y="-2.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="12" x="-3.45" y="-2.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="13" x="-2.75" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="14" x="-2.25" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="15" x="-1.75" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="16" x="-1.25" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="17" x="-0.75" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="18" x="-0.25" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="19" x="0.25" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="20" x="0.75" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="21" x="1.25" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="22" x="1.75" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="23" x="2.25" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="24" x="2.75" y="-3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="25" x="3.45" y="-2.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="26" x="3.45" y="-2.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="27" x="3.45" y="-1.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="28" x="3.45" y="-1.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="29" x="3.45" y="-0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="30" x="3.45" y="-0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="31" x="3.45" y="0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="32" x="3.45" y="0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="33" x="3.45" y="1.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="34" x="3.45" y="1.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="35" x="3.45" y="2.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="36" x="3.45" y="2.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="37" x="2.75" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="38" x="2.25" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="39" x="1.75" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="40" x="1.25" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="41" x="0.75" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="42" x="0.25" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="43" x="-0.25" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="44" x="-0.75" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="45" x="-1.25" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="46" x="-1.75" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="47" x="-2.25" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="48" x="-2.75" y="3.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-4.125" y1="4.125" x2="4.125" y2="4.125" width="0.05" layer="51"/>
<wire x1="4.125" y1="4.125" x2="4.125" y2="-4.125" width="0.05" layer="51"/>
<wire x1="4.125" y1="-4.125" x2="-4.125" y2="-4.125" width="0.05" layer="51"/>
<wire x1="-4.125" y1="-4.125" x2="-4.125" y2="4.125" width="0.05" layer="51"/>
<wire x1="-3.5" y1="3.5" x2="3.5" y2="3.5" width="0.1" layer="51"/>
<wire x1="3.5" y1="3.5" x2="3.5" y2="-3.5" width="0.1" layer="51"/>
<wire x1="3.5" y1="-3.5" x2="-3.5" y2="-3.5" width="0.1" layer="51"/>
<wire x1="-3.5" y1="-3.5" x2="-3.5" y2="3.5" width="0.1" layer="51"/>
<wire x1="-3.5" y1="3" x2="-3" y2="3.5" width="0.1" layer="51"/>
<circle x="-3.875" y="3.5" radius="0.125" width="0.25" layer="25"/>
</package>
</packages>
<symbols>
<symbol name="STM32G071C8U6TR" library_version="2">
<wire x1="5.08" y1="10.16" x2="45.72" y2="10.16" width="0.254" layer="94"/>
<wire x1="45.72" y1="-38.1" x2="45.72" y2="10.16" width="0.254" layer="94"/>
<wire x1="45.72" y1="-38.1" x2="5.08" y2="-38.1" width="0.254" layer="94"/>
<wire x1="5.08" y1="10.16" x2="5.08" y2="-38.1" width="0.254" layer="94"/>
<text x="46.99" y="15.24" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="46.99" y="12.7" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="PC13" x="0" y="0" length="middle"/>
<pin name="PC14-OSC32_IN" x="0" y="-2.54" length="middle"/>
<pin name="PC15-OSC32_OUT" x="0" y="-5.08" length="middle"/>
<pin name="VBAT" x="0" y="-7.62" length="middle"/>
<pin name="VREF+" x="0" y="-10.16" length="middle"/>
<pin name="VDD/VDDA" x="0" y="-12.7" length="middle"/>
<pin name="VSS/VSSA" x="0" y="-15.24" length="middle"/>
<pin name="PF0-OSC_IN" x="0" y="-17.78" length="middle"/>
<pin name="PF1-OSC_OUT" x="0" y="-20.32" length="middle"/>
<pin name="PF2-NRST" x="0" y="-22.86" length="middle"/>
<pin name="PA0" x="0" y="-25.4" length="middle"/>
<pin name="PA1" x="0" y="-27.94" length="middle"/>
<pin name="PA2" x="10.16" y="-43.18" length="middle" rot="R90"/>
<pin name="PA3" x="12.7" y="-43.18" length="middle" rot="R90"/>
<pin name="PA4" x="15.24" y="-43.18" length="middle" rot="R90"/>
<pin name="PA5" x="17.78" y="-43.18" length="middle" rot="R90"/>
<pin name="PA6" x="20.32" y="-43.18" length="middle" rot="R90"/>
<pin name="PA7" x="22.86" y="-43.18" length="middle" rot="R90"/>
<pin name="PB0" x="25.4" y="-43.18" length="middle" rot="R90"/>
<pin name="PB1" x="27.94" y="-43.18" length="middle" rot="R90"/>
<pin name="PB2" x="30.48" y="-43.18" length="middle" rot="R90"/>
<pin name="PB10" x="33.02" y="-43.18" length="middle" rot="R90"/>
<pin name="PB11" x="35.56" y="-43.18" length="middle" rot="R90"/>
<pin name="PB12" x="38.1" y="-43.18" length="middle" rot="R90"/>
<pin name="PA14-BOOT0" x="50.8" y="0" length="middle" rot="R180"/>
<pin name="PA13" x="50.8" y="-2.54" length="middle" rot="R180"/>
<pin name="PA12_[PA10]" x="50.8" y="-5.08" length="middle" rot="R180"/>
<pin name="PA11_[PA9]" x="50.8" y="-7.62" length="middle" rot="R180"/>
<pin name="PA10" x="50.8" y="-10.16" length="middle" rot="R180"/>
<pin name="PC7" x="50.8" y="-12.7" length="middle" rot="R180"/>
<pin name="PC6" x="50.8" y="-15.24" length="middle" rot="R180"/>
<pin name="PA9" x="50.8" y="-17.78" length="middle" rot="R180"/>
<pin name="PA8" x="50.8" y="-20.32" length="middle" rot="R180"/>
<pin name="PB15" x="50.8" y="-22.86" length="middle" rot="R180"/>
<pin name="PB14" x="50.8" y="-25.4" length="middle" rot="R180"/>
<pin name="PB13" x="50.8" y="-27.94" length="middle" rot="R180"/>
<pin name="PB9" x="12.7" y="15.24" length="middle" rot="R270"/>
<pin name="PB8" x="15.24" y="15.24" length="middle" rot="R270"/>
<pin name="PB7" x="17.78" y="15.24" length="middle" rot="R270"/>
<pin name="PB6" x="20.32" y="15.24" length="middle" rot="R270"/>
<pin name="PB5" x="22.86" y="15.24" length="middle" rot="R270"/>
<pin name="PB4" x="25.4" y="15.24" length="middle" rot="R270"/>
<pin name="PB3" x="27.94" y="15.24" length="middle" rot="R270"/>
<pin name="PD3" x="30.48" y="15.24" length="middle" rot="R270"/>
<pin name="PD2" x="33.02" y="15.24" length="middle" rot="R270"/>
<pin name="PD1" x="35.56" y="15.24" length="middle" rot="R270"/>
<pin name="PD0" x="38.1" y="15.24" length="middle" rot="R270"/>
<pin name="PA15" x="40.64" y="15.24" length="middle" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="STM32G071C8U6TR" prefix="IC" library_version="2">
<description>&lt;b&gt;Arm Cortex-M0+ 32-bit MCU, up to 128 KB Flash, 36 KB RAM, 4x USART, timers, ADC, DAC, comm. I/Fs, 1.7-3.6V&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.st.com/resource/en/datasheet/stm32g071c8.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="STM32G071C8U6TR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN50P700X700X65-49N">
<connects>
<connect gate="G$1" pin="PA0" pad="11"/>
<connect gate="G$1" pin="PA1" pad="12"/>
<connect gate="G$1" pin="PA10" pad="32"/>
<connect gate="G$1" pin="PA11_[PA9]" pad="33"/>
<connect gate="G$1" pin="PA12_[PA10]" pad="34"/>
<connect gate="G$1" pin="PA13" pad="35"/>
<connect gate="G$1" pin="PA14-BOOT0" pad="36"/>
<connect gate="G$1" pin="PA15" pad="37"/>
<connect gate="G$1" pin="PA2" pad="13"/>
<connect gate="G$1" pin="PA3" pad="14"/>
<connect gate="G$1" pin="PA4" pad="15"/>
<connect gate="G$1" pin="PA5" pad="16"/>
<connect gate="G$1" pin="PA6" pad="17"/>
<connect gate="G$1" pin="PA7" pad="18"/>
<connect gate="G$1" pin="PA8" pad="28"/>
<connect gate="G$1" pin="PA9" pad="29"/>
<connect gate="G$1" pin="PB0" pad="19"/>
<connect gate="G$1" pin="PB1" pad="20"/>
<connect gate="G$1" pin="PB10" pad="22"/>
<connect gate="G$1" pin="PB11" pad="23"/>
<connect gate="G$1" pin="PB12" pad="24"/>
<connect gate="G$1" pin="PB13" pad="25"/>
<connect gate="G$1" pin="PB14" pad="26"/>
<connect gate="G$1" pin="PB15" pad="27"/>
<connect gate="G$1" pin="PB2" pad="21"/>
<connect gate="G$1" pin="PB3" pad="42"/>
<connect gate="G$1" pin="PB4" pad="43"/>
<connect gate="G$1" pin="PB5" pad="44"/>
<connect gate="G$1" pin="PB6" pad="45"/>
<connect gate="G$1" pin="PB7" pad="46"/>
<connect gate="G$1" pin="PB8" pad="47"/>
<connect gate="G$1" pin="PB9" pad="48"/>
<connect gate="G$1" pin="PC13" pad="1"/>
<connect gate="G$1" pin="PC14-OSC32_IN" pad="2"/>
<connect gate="G$1" pin="PC15-OSC32_OUT" pad="3"/>
<connect gate="G$1" pin="PC6" pad="30"/>
<connect gate="G$1" pin="PC7" pad="31"/>
<connect gate="G$1" pin="PD0" pad="38"/>
<connect gate="G$1" pin="PD1" pad="39"/>
<connect gate="G$1" pin="PD2" pad="40"/>
<connect gate="G$1" pin="PD3" pad="41"/>
<connect gate="G$1" pin="PF0-OSC_IN" pad="8"/>
<connect gate="G$1" pin="PF1-OSC_OUT" pad="9"/>
<connect gate="G$1" pin="PF2-NRST" pad="10"/>
<connect gate="G$1" pin="VBAT" pad="4"/>
<connect gate="G$1" pin="VDD/VDDA" pad="6"/>
<connect gate="G$1" pin="VREF+" pad="5"/>
<connect gate="G$1" pin="VSS/VSSA" pad="7"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="511-STM32G071C8U6TR" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/STMicroelectronics/STM32G071C8U6TR?qs=l7cgNqFNU1jLAVhkp9RJiw%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="STMicroelectronics" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="STM32G071C8U6TR" constant="no"/>
<attribute name="DESCRIPTION" value="Arm Cortex-M0+ 32-bit MCU, up to 128 KB Flash, 36 KB RAM, 4x USART, timers, ADC, DAC, comm. I/Fs, 1.7-3.6V" constant="no"/>
<attribute name="HEIGHT" value="0.65mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="CAM-M8Q-0" urn="urn:adsk.wipprod:fs.file:vf.0LPKsAaDRqKDEJUuXZtcBg">
<description>&lt;CAM-M8 RF Receiver BeiDou, GLONASS, GNSS, GPS, QZSS 1.575GHz -167dBm On-Board, Chip Module&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="CAMM8Q0" library_version="1">
<description>&lt;b&gt;31-SMD Module_2025-1&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-6.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="2" x="-5.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="3" x="-4.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="4" x="-3.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="5" x="-2.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="6" x="-1.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="7" x="-0.2" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="8" x="0.8" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="9" x="1.8" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="10" x="2.8" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="11" x="3.8" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="12" x="4.8" y="-4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="13" x="5.95" y="-4.4" dx="1.5" dy="1" layer="1" rot="R90"/>
<smd name="14" x="5.95" y="4.4" dx="1.5" dy="1" layer="1" rot="R90"/>
<smd name="15" x="4.8" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="16" x="3.8" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="17" x="2.8" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="18" x="1.8" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="19" x="0.8" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="20" x="-0.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="21" x="-1.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="22" x="-2.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="23" x="-3.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="24" x="-4.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="25" x="-5.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="26" x="-6.2" y="4.4" dx="1.5" dy="0.7" layer="1" rot="R90"/>
<smd name="27" x="-6.6" y="2" dx="1.5" dy="0.7" layer="1"/>
<smd name="28" x="-6.6" y="1" dx="1.5" dy="0.7" layer="1"/>
<smd name="29" x="-6.6" y="0" dx="1.5" dy="0.7" layer="1"/>
<smd name="30" x="-6.6" y="-1" dx="1.5" dy="0.7" layer="1"/>
<smd name="31" x="-6.6" y="-2" dx="1.5" dy="0.7" layer="1"/>
<text x="-0.175" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="-0.175" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-7" y1="4.8" x2="7" y2="4.8" width="0.1" layer="51"/>
<wire x1="7" y1="4.8" x2="7" y2="-4.8" width="0.1" layer="51"/>
<wire x1="7" y1="-4.8" x2="-7" y2="-4.8" width="0.1" layer="51"/>
<wire x1="-7" y1="-4.8" x2="-7" y2="4.8" width="0.1" layer="51"/>
<wire x1="-8.35" y1="6.15" x2="8" y2="6.15" width="0.1" layer="51"/>
<wire x1="8" y1="6.15" x2="8" y2="-6.15" width="0.1" layer="51"/>
<wire x1="8" y1="-6.15" x2="-8.35" y2="-6.15" width="0.1" layer="51"/>
<wire x1="-8.35" y1="-6.15" x2="-8.35" y2="6.15" width="0.1" layer="51"/>
<wire x1="-6.2" y1="-5.6" x2="-6.2" y2="-5.7" width="0.1" layer="21" curve="180"/>
<wire x1="-6.2" y1="-5.7" x2="-6.2" y2="-5.6" width="0.1" layer="21" curve="180"/>
<wire x1="6.8" y1="4.8" x2="7" y2="4.8" width="0.2" layer="21"/>
<wire x1="7" y1="4.8" x2="7" y2="-4.8" width="0.2" layer="21"/>
<wire x1="7" y1="-4.8" x2="6.8" y2="-4.8" width="0.2" layer="21"/>
<wire x1="-7" y1="-2.6" x2="-7" y2="-4.8" width="0.2" layer="21"/>
<wire x1="-7" y1="-4.8" x2="-6.8" y2="-4.8" width="0.2" layer="21"/>
<wire x1="-6.8" y1="4.8" x2="-7" y2="4.8" width="0.2" layer="21"/>
<wire x1="-7" y1="4.8" x2="-7" y2="2.6" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="CAM-M8Q-0" library_version="1">
<wire x1="5.08" y1="2.54" x2="48.26" y2="2.54" width="0.254" layer="94"/>
<wire x1="48.26" y1="-40.64" x2="48.26" y2="2.54" width="0.254" layer="94"/>
<wire x1="48.26" y1="-40.64" x2="5.08" y2="-40.64" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-40.64" width="0.254" layer="94"/>
<text x="49.53" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="49.53" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="VCC_IO" x="0" y="0" length="middle"/>
<pin name="RESERVED_1" x="0" y="-2.54" length="middle"/>
<pin name="SDA_/_SPI_CS_N" x="0" y="-5.08" length="middle"/>
<pin name="GND_1" x="0" y="-7.62" length="middle"/>
<pin name="GND_2" x="0" y="-10.16" length="middle"/>
<pin name="SCL_/_SPI_CLK" x="0" y="-12.7" length="middle"/>
<pin name="EXTINT" x="0" y="-15.24" length="middle"/>
<pin name="V_BCKP" x="0" y="-17.78" length="middle"/>
<pin name="VCC" x="0" y="-20.32" length="middle"/>
<pin name="GND_3" x="0" y="-22.86" length="middle"/>
<pin name="GND_4" x="0" y="-25.4" length="middle"/>
<pin name="GND_5" x="0" y="-27.94" length="middle"/>
<pin name="GND_6" x="0" y="-30.48" length="middle"/>
<pin name="GND_7" x="0" y="-33.02" length="middle"/>
<pin name="GND_8" x="0" y="-35.56" length="middle"/>
<pin name="RF_OUT" x="0" y="-38.1" length="middle"/>
<pin name="RF_IN" x="53.34" y="0" length="middle" rot="R180"/>
<pin name="GND_9" x="53.34" y="-2.54" length="middle" rot="R180"/>
<pin name="GND_10" x="53.34" y="-5.08" length="middle" rot="R180"/>
<pin name="D_SEL" x="53.34" y="-7.62" length="middle" rot="R180"/>
<pin name="GND_11" x="53.34" y="-10.16" length="middle" rot="R180"/>
<pin name="GND_12" x="53.34" y="-12.7" length="middle" rot="R180"/>
<pin name="RESET_N" x="53.34" y="-15.24" length="middle" rot="R180"/>
<pin name="SAFEBOOT_N" x="53.34" y="-17.78" length="middle" rot="R180"/>
<pin name="TXD_/_SPI_MISO" x="53.34" y="-20.32" length="middle" rot="R180"/>
<pin name="RXD_/_SPI_MOSI" x="53.34" y="-22.86" length="middle" rot="R180"/>
<pin name="GND_13" x="53.34" y="-25.4" length="middle" rot="R180"/>
<pin name="RESERVED_2" x="53.34" y="-27.94" length="middle" rot="R180"/>
<pin name="TIMEPULSE" x="53.34" y="-30.48" length="middle" rot="R180"/>
<pin name="LNA_EN" x="53.34" y="-33.02" length="middle" rot="R180"/>
<pin name="GND_14" x="53.34" y="-35.56" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CAM-M8Q-0" prefix="IC" library_version="1">
<description>&lt;b&gt;CAM-M8 RF Receiver BeiDou, GLONASS, GNSS, GPS, QZSS 1.575GHz -167dBm On-Board, Chip Module&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://content.u-blox.com/sites/default/files/CAM-M8-FW3_DataSheet_(UBX-15031574).pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="CAM-M8Q-0" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAMM8Q0">
<connects>
<connect gate="G$1" pin="D_SEL" pad="20"/>
<connect gate="G$1" pin="EXTINT" pad="7"/>
<connect gate="G$1" pin="GND_1" pad="4"/>
<connect gate="G$1" pin="GND_10" pad="19"/>
<connect gate="G$1" pin="GND_11" pad="21"/>
<connect gate="G$1" pin="GND_12" pad="22"/>
<connect gate="G$1" pin="GND_13" pad="27"/>
<connect gate="G$1" pin="GND_14" pad="31"/>
<connect gate="G$1" pin="GND_2" pad="5"/>
<connect gate="G$1" pin="GND_3" pad="10"/>
<connect gate="G$1" pin="GND_4" pad="11"/>
<connect gate="G$1" pin="GND_5" pad="12"/>
<connect gate="G$1" pin="GND_6" pad="13"/>
<connect gate="G$1" pin="GND_7" pad="14"/>
<connect gate="G$1" pin="GND_8" pad="15"/>
<connect gate="G$1" pin="GND_9" pad="18"/>
<connect gate="G$1" pin="LNA_EN" pad="30"/>
<connect gate="G$1" pin="RESERVED_1" pad="2"/>
<connect gate="G$1" pin="RESERVED_2" pad="28"/>
<connect gate="G$1" pin="RESET_N" pad="23"/>
<connect gate="G$1" pin="RF_IN" pad="17"/>
<connect gate="G$1" pin="RF_OUT" pad="16"/>
<connect gate="G$1" pin="RXD_/_SPI_MOSI" pad="26"/>
<connect gate="G$1" pin="SAFEBOOT_N" pad="24"/>
<connect gate="G$1" pin="SCL_/_SPI_CLK" pad="6"/>
<connect gate="G$1" pin="SDA_/_SPI_CS_N" pad="3"/>
<connect gate="G$1" pin="TIMEPULSE" pad="29"/>
<connect gate="G$1" pin="TXD_/_SPI_MISO" pad="25"/>
<connect gate="G$1" pin="VCC" pad="9"/>
<connect gate="G$1" pin="VCC_IO" pad="1"/>
<connect gate="G$1" pin="V_BCKP" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="377-CAM-M8Q-0" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/u-blox/CAM-M8Q-0?qs=vEM7xhTegWgOVMjXYnonQA%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="u-blox" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="CAM-M8Q-0" constant="no"/>
<attribute name="DESCRIPTION" value="CAM-M8 RF Receiver BeiDou, GLONASS, GNSS, GPS, QZSS 1.575GHz -167dBm On-Board, Chip Module" constant="no"/>
<attribute name="HEIGHT" value="2.3mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="MAX98357AETE+T" urn="urn:adsk.wipprod:fs.file:vf._VMllKDRSi61WhmqObQNgQ">
<description>&lt;Audio Amplifiers Digital Input Class D Amplifier&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="QFN50P300X300X80-17N" library_version="3">
<description>&lt;b&gt;Max 21-0136_T1633-4&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-1.45" y="0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="2" x="-1.45" y="0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="3" x="-1.45" y="-0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="4" x="-1.45" y="-0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="5" x="-0.75" y="-1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="6" x="-0.25" y="-1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="7" x="0.25" y="-1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="8" x="0.75" y="-1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="9" x="1.45" y="-0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="10" x="1.45" y="-0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="11" x="1.45" y="0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="12" x="1.45" y="0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="13" x="0.75" y="1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="14" x="0.25" y="1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="15" x="-0.25" y="1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="16" x="-0.75" y="1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-2.125" y1="2.125" x2="2.125" y2="2.125" width="0.05" layer="51"/>
<wire x1="2.125" y1="2.125" x2="2.125" y2="-2.125" width="0.05" layer="51"/>
<wire x1="2.125" y1="-2.125" x2="-2.125" y2="-2.125" width="0.05" layer="51"/>
<wire x1="-2.125" y1="-2.125" x2="-2.125" y2="2.125" width="0.05" layer="51"/>
<wire x1="-1.5" y1="1.5" x2="1.5" y2="1.5" width="0.1" layer="51"/>
<wire x1="1.5" y1="1.5" x2="1.5" y2="-1.5" width="0.1" layer="51"/>
<wire x1="1.5" y1="-1.5" x2="-1.5" y2="-1.5" width="0.1" layer="51"/>
<wire x1="-1.5" y1="-1.5" x2="-1.5" y2="1.5" width="0.1" layer="51"/>
<wire x1="-1.5" y1="1" x2="-1" y2="1.5" width="0.1" layer="51"/>
<circle x="-1.875" y="1.5" radius="0.125" width="0.25" layer="25"/>
</package>
</packages>
<symbols>
<symbol name="MAX98357AETE+T" library_version="3">
<wire x1="5.08" y1="20.32" x2="35.56" y2="20.32" width="0.254" layer="94"/>
<wire x1="35.56" y1="-20.32" x2="35.56" y2="20.32" width="0.254" layer="94"/>
<wire x1="35.56" y1="-20.32" x2="5.08" y2="-20.32" width="0.254" layer="94"/>
<wire x1="5.08" y1="20.32" x2="5.08" y2="-20.32" width="0.254" layer="94"/>
<text x="36.83" y="25.4" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="36.83" y="22.86" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="DIN" x="0" y="0" length="middle"/>
<pin name="GAIN_SLOT" x="0" y="-2.54" length="middle"/>
<pin name="GND_1" x="0" y="-5.08" length="middle"/>
<pin name="!SD_MODE" x="0" y="-7.62" length="middle"/>
<pin name="N.C._1" x="15.24" y="-25.4" length="middle" rot="R90"/>
<pin name="N.C._2" x="17.78" y="-25.4" length="middle" rot="R90"/>
<pin name="VDD_1" x="20.32" y="-25.4" length="middle" rot="R90"/>
<pin name="VDD_2" x="22.86" y="-25.4" length="middle" rot="R90"/>
<pin name="N.C._3" x="40.64" y="0" length="middle" rot="R180"/>
<pin name="GND_2" x="40.64" y="-2.54" length="middle" rot="R180"/>
<pin name="OUTN" x="40.64" y="-5.08" length="middle" rot="R180"/>
<pin name="OUTP" x="40.64" y="-7.62" length="middle" rot="R180"/>
<pin name="BCLK" x="17.78" y="25.4" length="middle" rot="R270"/>
<pin name="GND_3" x="20.32" y="25.4" length="middle" rot="R270"/>
<pin name="LRCLK" x="22.86" y="25.4" length="middle" rot="R270"/>
<pin name="N.C._4" x="25.4" y="25.4" length="middle" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MAX98357AETE+T" prefix="IC" library_version="3">
<description>&lt;b&gt;Audio Amplifiers Digital Input Class D Amplifier&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://datasheets.maximintegrated.com/en/ds/MAX98357A-MAX98357B.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="MAX98357AETE+T" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN50P300X300X80-17N">
<connects>
<connect gate="G$1" pin="!SD_MODE" pad="4"/>
<connect gate="G$1" pin="BCLK" pad="16"/>
<connect gate="G$1" pin="DIN" pad="1"/>
<connect gate="G$1" pin="GAIN_SLOT" pad="2"/>
<connect gate="G$1" pin="GND_1" pad="3"/>
<connect gate="G$1" pin="GND_2" pad="11"/>
<connect gate="G$1" pin="GND_3" pad="15"/>
<connect gate="G$1" pin="LRCLK" pad="14"/>
<connect gate="G$1" pin="N.C._1" pad="5"/>
<connect gate="G$1" pin="N.C._2" pad="6"/>
<connect gate="G$1" pin="N.C._3" pad="12"/>
<connect gate="G$1" pin="N.C._4" pad="13"/>
<connect gate="G$1" pin="OUTN" pad="10"/>
<connect gate="G$1" pin="OUTP" pad="9"/>
<connect gate="G$1" pin="VDD_1" pad="7"/>
<connect gate="G$1" pin="VDD_2" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MOUSER_PART_NUMBER" value="700-MAX98357AETE+T" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/Analog-Devices-Maxim-Integrated/MAX98357AETE%2bT?qs=AAveGqk956HhNpoJjF5x2g%3D%3D" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Analog Devices" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="MAX98357AETE+T" constant="no"/>
<attribute name="DESCRIPTION" value="Audio Amplifiers Digital Input Class D Amplifier" constant="no"/>
<attribute name="HEIGHT" value="0.8mm" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="S4B-PH-SM4-TB" urn="urn:adsk.wipprod:fs.file:vf.LdgZlENWRX-5uo8bxX-GBQ">
<packages>
<package name="JST_S4B-PH-SM4-TB" library_version="1">
<wire x1="5.95" y1="3.3" x2="-5.95" y2="3.3" width="0.127" layer="51"/>
<wire x1="-5.95" y1="3.3" x2="-5.95" y2="-4.3" width="0.127" layer="51"/>
<wire x1="-5.95" y1="-4.3" x2="5.95" y2="-4.3" width="0.127" layer="51"/>
<wire x1="5.95" y1="-4.3" x2="5.95" y2="3.3" width="0.127" layer="51"/>
<wire x1="6.35" y1="-4.75" x2="-6.35" y2="-4.75" width="0.05" layer="39"/>
<wire x1="-6.35" y1="-4.75" x2="-6.35" y2="4.75" width="0.05" layer="39"/>
<wire x1="-6.35" y1="4.75" x2="6.35" y2="4.75" width="0.05" layer="39"/>
<wire x1="6.35" y1="4.75" x2="6.35" y2="-4.75" width="0.05" layer="39"/>
<wire x1="-5.95" y1="-0.4" x2="-5.95" y2="3.3" width="0.127" layer="21"/>
<wire x1="-5.95" y1="3.3" x2="-4.2" y2="3.3" width="0.127" layer="21"/>
<wire x1="4.2" y1="3.3" x2="5.95" y2="3.3" width="0.127" layer="21"/>
<wire x1="5.95" y1="3.3" x2="5.95" y2="-0.4" width="0.127" layer="21"/>
<wire x1="-4" y1="-4.3" x2="4" y2="-4.3" width="0.127" layer="21"/>
<circle x="-3" y="5.3" radius="0.1" width="0.2" layer="21"/>
<circle x="-3" y="5.3" radius="0.1" width="0.2" layer="51"/>
<text x="-6.7" y="7.14" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.7" y="5.7" size="1.27" layer="27">&gt;VALUE</text>
<smd name="3" x="1" y="2.75" dx="1" dy="3.5" layer="1"/>
<smd name="4" x="3" y="2.75" dx="1" dy="3.5" layer="1"/>
<smd name="2" x="-1" y="2.75" dx="1" dy="3.5" layer="1"/>
<smd name="1" x="-3" y="2.75" dx="1" dy="3.5" layer="1"/>
<smd name="SH2" x="5.35" y="-2.8" dx="1.5" dy="3.4" layer="1"/>
<smd name="SH1" x="-5.35" y="-2.8" dx="1.5" dy="3.4" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="S4B-PH-SM4-TB" library_version="1">
<wire x1="5.08" y1="5.08" x2="-3.81" y2="5.08" width="0.254" layer="94"/>
<wire x1="-3.81" y1="5.08" x2="-3.81" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-3.81" y="6.35" size="1.778" layer="95">&gt;NAME</text>
<text x="-4.064" y="-10.414" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-3.175" y1="2.2225" x2="-1.5875" y2="2.8575" layer="94"/>
<rectangle x1="-3.175" y1="-0.3175" x2="-1.5875" y2="0.3175" layer="94"/>
<rectangle x1="-3.175" y1="-2.8575" x2="-1.5875" y2="-2.2225" layer="94"/>
<rectangle x1="-3.175" y1="-5.3975" x2="-1.5875" y2="-4.7625" layer="94"/>
<pin name="1" x="-7.62" y="2.54" length="middle" direction="pas"/>
<pin name="2" x="-7.62" y="0" length="middle" direction="pas"/>
<pin name="3" x="-7.62" y="-2.54" length="middle" direction="pas"/>
<pin name="4" x="-7.62" y="-5.08" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="S4B-PH-SM4-TB" prefix="J" library_version="1">
<description> &lt;a href="https://pricing.snapeda.com/parts/S4B-PH-SM4-TB/JST%20Sales/view-part?ref=eda"&gt;Check availability&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="S4B-PH-SM4-TB" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JST_S4B-PH-SM4-TB">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="JST Sales"/>
<attribute name="DESCRIPTION" value="                                                      Connector Header Surface Mount, Right Angle 4 position 0.079 (2.00mm)                                              "/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
<attribute name="SNAPEDA_LINK" value="https://www.snapeda.com/parts/S4B-PH-SM4-TB/JST/view-part/?ref=snap"/>
<attribute name="MP" value="S4B-PH-SM4-TB"/>
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="CHECK_PRICES" value="https://www.snapeda.com/parts/S4B-PH-SM4-TB/JST/view-part/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Filter" urn="urn:adsk.eagle:library:16378195">
<description>&lt;b&gt;Ferrite Bead, Common mode chokes, EMI/RFI, Power</description>
<packages>
<package name="BEADC1608X95N" urn="urn:adsk.eagle:footprint:16378197/1" library_version="16">
<description>Chip, 1.60 X 0.80 X 0.95 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.80 X 0.95 mm&lt;/p&gt;</description>
<wire x1="0.875" y1="0.7991" x2="-0.875" y2="0.7991" width="0.12" layer="21"/>
<wire x1="0.875" y1="-0.7991" x2="-0.875" y2="-0.7991" width="0.12" layer="21"/>
<wire x1="0.875" y1="-0.475" x2="-0.875" y2="-0.475" width="0.12" layer="51"/>
<wire x1="-0.875" y1="-0.475" x2="-0.875" y2="0.475" width="0.12" layer="51"/>
<wire x1="-0.875" y1="0.475" x2="0.875" y2="0.475" width="0.12" layer="51"/>
<wire x1="0.875" y1="0.475" x2="0.875" y2="-0.475" width="0.12" layer="51"/>
<smd name="1" x="-0.7851" y="0" dx="0.9" dy="0.9702" layer="1"/>
<smd name="2" x="0.7688" y="0" dx="0.9326" dy="0.9702" layer="1"/>
<text x="0" y="1.4341" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.4341" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="BEADC3216X130N" urn="urn:adsk.eagle:footprint:16315383/1" library_version="16">
<description>Chip, 3.20 X 1.60 X 1.30 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 1.30 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.2217" x2="-1.7" y2="1.2217" width="0.12" layer="21"/>
<wire x1="1.7" y1="-1.2217" x2="-1.7" y2="-1.2217" width="0.12" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<text x="0" y="1.8567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="BEADC2012X105N" urn="urn:adsk.eagle:footprint:16315427/1" library_version="16">
<description>Chip, 2.00 X 1.25 X 1.05 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 1.05 mm&lt;/p&gt;</description>
<wire x1="1.1" y1="1.0467" x2="-1.1" y2="1.0467" width="0.12" layer="21"/>
<wire x1="1.1" y1="-1.0467" x2="-1.1" y2="-1.0467" width="0.12" layer="21"/>
<wire x1="1.1" y1="-0.725" x2="-1.1" y2="-0.725" width="0.12" layer="51"/>
<wire x1="-1.1" y1="-0.725" x2="-1.1" y2="0.725" width="0.12" layer="51"/>
<wire x1="-1.1" y1="0.725" x2="1.1" y2="0.725" width="0.12" layer="51"/>
<wire x1="1.1" y1="0.725" x2="1.1" y2="-0.725" width="0.12" layer="51"/>
<smd name="1" x="-0.8754" y="0" dx="1.1646" dy="1.4653" layer="1"/>
<smd name="2" x="0.8754" y="0" dx="1.1646" dy="1.4653" layer="1"/>
<text x="0" y="1.6817" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.6817" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="BEADC1608X95N" urn="urn:adsk.eagle:package:16378199/1" type="model">
<description>Chip, 1.60 X 0.80 X 0.95 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.80 X 0.95 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="BEADC1608X95N"/>
</packageinstances>
</package3d>
<package3d name="BEADC3216X130N" urn="urn:adsk.eagle:package:16315278/1" type="model">
<description>Chip, 3.20 X 1.60 X 1.30 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 1.30 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="BEADC3216X130N"/>
</packageinstances>
</package3d>
<package3d name="BEADC2012X105N" urn="urn:adsk.eagle:package:16315423/1" type="model">
<description>Chip, 2.00 X 1.25 X 1.05 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 1.05 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="BEADC2012X105N"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="FB" urn="urn:adsk.eagle:symbol:16378196/2" library_version="16">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="1.5" y2="0" width="0.254" layer="94"/>
<text x="0" y="2.7686" size="1.778" layer="95" align="center">&gt;NAME</text>
<text x="0" y="-3.302" size="1.778" layer="96" align="center">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FB_" urn="urn:adsk.eagle:component:16378200/7" prefix="FB" library_version="16">
<description>&lt;B&gt;Ferrite Bead - Popular parts</description>
<gates>
<gate name="G$1" symbol="FB" x="0" y="0"/>
</gates>
<devices>
<device name="_0603(1608)" package="BEADC1608X95N">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378199/1"/>
</package3dinstances>
<technologies>
<technology name="BLM18AG601SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 600 OHM 0603 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="FILTER_TYPE" value="" constant="no"/>
<attribute name="IMPEDANCE_FREQ" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="LM18AG601" constant="no"/>
</technology>
<technology name="BLM18EG221SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 220 OHM 0603 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="FILTER_TYPE" value="" constant="no"/>
<attribute name="IMPEDANCE_FREQ" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM18EG221" constant="no"/>
</technology>
<technology name="BLM18PG121SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 120 OHM 0603 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="FILTER_TYPE" value="" constant="no"/>
<attribute name="IMPEDANCE_FREQ" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM18PG121" constant="no"/>
</technology>
</technologies>
</device>
<device name="_1206(3216)" package="BEADC3216X130N">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16315278/1"/>
</package3dinstances>
<technologies>
<technology name="BLM31PG500SN1L">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 50 OHM 1206 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM31PG500" constant="no"/>
</technology>
<technology name="BLM31PG601SN1L">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 600 OHM 1206 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM31PG601" constant="no"/>
</technology>
</technologies>
</device>
<device name="_0805(2012)" package="BEADC2012X105N">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16315423/1"/>
</package3dinstances>
<technologies>
<technology name="BLM21AG102SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 1 KOHM 0805 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM21AG102" constant="no"/>
</technology>
<technology name="BLM21AG121SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 120 OHM 0805 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM21AG121" constant="no"/>
</technology>
<technology name="BLM21PG221SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 220 OHM 0805 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM21PG221" constant="no"/>
</technology>
<technology name="BLM21PG331SN1D">
<attribute name="CATEGORY" value="Filter" constant="no"/>
<attribute name="DESCRIPTION" value="FERRITE BEAD 330 OHM 0805 1LN" constant="no"/>
<attribute name="MANUFACTURER" value="Murata Electronics" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Ferrite bead" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="VALUE" value="BLM21PG331" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="DMM-4026-B-I2S-R" urn="urn:adsk.wipprod:fs.file:vf.YdAovc1lTsGKKiX495LWbQ">
<packages>
<package name="MIC_DMM-4026-B-I2S-R" library_version="1">
<wire x1="-1.695" y1="2.1" x2="1.695" y2="2.1" width="0.127" layer="21"/>
<wire x1="1.695" y1="2.1" x2="1.695" y2="-2.145" width="0.127" layer="21"/>
<wire x1="1.695" y1="-2.145" x2="-1.695" y2="-2.145" width="0.127" layer="21"/>
<wire x1="-1.695" y1="-2.145" x2="-1.695" y2="2.1" width="0.127" layer="21"/>
<wire x1="-1.5" y1="2" x2="1.5" y2="2" width="0.127" layer="51"/>
<wire x1="1.5" y1="2" x2="1.5" y2="-2" width="0.127" layer="51"/>
<wire x1="1.5" y1="-2" x2="-1.5" y2="-2" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-2" x2="-1.5" y2="2" width="0.127" layer="51"/>
<text x="-2.5" y="2.38" size="1.016" layer="25">&gt;NAME</text>
<text x="-2.5" y="-2.38" size="1.016" layer="27" align="top-left">&gt;VALUE</text>
<circle x="-2.16" y="1.597" radius="0.1" width="0.2" layer="21"/>
<circle x="-2.16" y="1.597" radius="0.1" width="0.2" layer="51"/>
<wire x1="-1.75" y1="2.25" x2="1.75" y2="2.25" width="0.05" layer="39"/>
<wire x1="1.75" y1="2.25" x2="1.75" y2="-2.25" width="0.05" layer="39"/>
<wire x1="1.75" y1="-2.25" x2="-1.75" y2="-2.25" width="0.05" layer="39"/>
<wire x1="-1.75" y1="-2.25" x2="-1.75" y2="2.25" width="0.05" layer="39"/>
<polygon width="0.01" layer="1" pour="solid">
<vertex x="0" y="-1.525"/>
<vertex x="0" y="-1.825"/>
<vertex x="0.160940625" y="-1.80915"/>
<vertex x="0.315696875" y="-1.76220625"/>
<vertex x="0.45835" y="-1.6859625"/>
<vertex x="0.5833625" y="-1.5833625"/>
<vertex x="0.6859625" y="-1.45835"/>
<vertex x="0.76220625" y="-1.315696875"/>
<vertex x="0.80915" y="-1.160940625"/>
<vertex x="0.825003125" y="-1"/>
<vertex x="0.80915" y="-0.839059375"/>
<vertex x="0.76220625" y="-0.684303125"/>
<vertex x="0.6859625" y="-0.54165"/>
<vertex x="0.5833625" y="-0.4166375"/>
<vertex x="0.45835" y="-0.3140375"/>
<vertex x="0.315696875" y="-0.23779375"/>
<vertex x="0.160940625" y="-0.19085"/>
<vertex x="0" y="-0.175"/>
<vertex x="0" y="-0.475"/>
<vertex x="0.114840625" y="-0.4879375"/>
<vertex x="0.11540625" y="-0.487665625"/>
<vertex x="0.116825" y="-0.4881625"/>
<vertex x="0.118328125" y="-0.48833125"/>
<vertex x="0.118721875" y="-0.488825"/>
<vertex x="0.225890625" y="-0.526328125"/>
<vertex x="0.22650625" y="-0.5261875"/>
<vertex x="0.22778125" y="-0.526990625"/>
<vertex x="0.22920625" y="-0.5274875"/>
<vertex x="0.22948125" y="-0.52805625"/>
<vertex x="0.3256375" y="-0.588475"/>
<vertex x="0.326271875" y="-0.588475"/>
<vertex x="0.32734375" y="-0.589546875"/>
<vertex x="0.3286125" y="-0.59034375"/>
<vertex x="0.328753125" y="-0.59095625"/>
<vertex x="0.40904375" y="-0.671246875"/>
<vertex x="0.40965625" y="-0.6713875"/>
<vertex x="0.410453125" y="-0.67265625"/>
<vertex x="0.411525" y="-0.673728125"/>
<vertex x="0.411525" y="-0.6743625"/>
<vertex x="0.47194375" y="-0.77051875"/>
<vertex x="0.4725125" y="-0.77079375"/>
<vertex x="0.473009375" y="-0.77221875"/>
<vertex x="0.4738125" y="-0.77349375"/>
<vertex x="0.473671875" y="-0.774109375"/>
<vertex x="0.511175" y="-0.881278125"/>
<vertex x="0.51166875" y="-0.881671875"/>
<vertex x="0.5118375" y="-0.883175"/>
<vertex x="0.512334375" y="-0.88459375"/>
<vertex x="0.5120625" y="-0.885159375"/>
<vertex x="0.524775" y="-0.998009375"/>
<vertex x="0.52516875" y="-0.998503125"/>
<vertex x="0.525" y="-1"/>
<vertex x="0.52516875" y="-1.001496875"/>
<vertex x="0.524775" y="-1.001990625"/>
<vertex x="0.5120625" y="-1.114840625"/>
<vertex x="0.512334375" y="-1.11540625"/>
<vertex x="0.5118375" y="-1.116825"/>
<vertex x="0.51166875" y="-1.118328125"/>
<vertex x="0.511175" y="-1.118721875"/>
<vertex x="0.473671875" y="-1.225890625"/>
<vertex x="0.4738125" y="-1.22650625"/>
<vertex x="0.473009375" y="-1.22778125"/>
<vertex x="0.4725125" y="-1.22920625"/>
<vertex x="0.47194375" y="-1.22948125"/>
<vertex x="0.411525" y="-1.3256375"/>
<vertex x="0.411525" y="-1.326271875"/>
<vertex x="0.410453125" y="-1.32734375"/>
<vertex x="0.40965625" y="-1.3286125"/>
<vertex x="0.40904375" y="-1.328753125"/>
<vertex x="0.328753125" y="-1.40904375"/>
<vertex x="0.3286125" y="-1.40965625"/>
<vertex x="0.32734375" y="-1.410453125"/>
<vertex x="0.326271875" y="-1.411525"/>
<vertex x="0.3256375" y="-1.411525"/>
<vertex x="0.22948125" y="-1.47194375"/>
<vertex x="0.22920625" y="-1.4725125"/>
<vertex x="0.22778125" y="-1.473009375"/>
<vertex x="0.22650625" y="-1.4738125"/>
<vertex x="0.225890625" y="-1.473671875"/>
<vertex x="0.118721875" y="-1.511175"/>
<vertex x="0.118328125" y="-1.51166875"/>
<vertex x="0.116825" y="-1.5118375"/>
<vertex x="0.11540625" y="-1.512334375"/>
<vertex x="0.114840625" y="-1.5120625"/>
</polygon>
<polygon width="0.01" layer="1" pour="solid">
<vertex x="-0.160940625" y="-1.80915"/>
<vertex x="0" y="-1.825"/>
<vertex x="0" y="-1.525"/>
<vertex x="-0.114840625" y="-1.5120625"/>
<vertex x="-0.11540625" y="-1.512334375"/>
<vertex x="-0.116825" y="-1.5118375"/>
<vertex x="-0.118328125" y="-1.51166875"/>
<vertex x="-0.118721875" y="-1.511175"/>
<vertex x="-0.225890625" y="-1.473671875"/>
<vertex x="-0.22650625" y="-1.4738125"/>
<vertex x="-0.22778125" y="-1.473009375"/>
<vertex x="-0.22920625" y="-1.4725125"/>
<vertex x="-0.22948125" y="-1.47194375"/>
<vertex x="-0.3256375" y="-1.411525"/>
<vertex x="-0.326271875" y="-1.411525"/>
<vertex x="-0.32734375" y="-1.410453125"/>
<vertex x="-0.3286125" y="-1.40965625"/>
<vertex x="-0.328753125" y="-1.40904375"/>
<vertex x="-0.40904375" y="-1.328753125"/>
<vertex x="-0.40965625" y="-1.3286125"/>
<vertex x="-0.410453125" y="-1.32734375"/>
<vertex x="-0.411525" y="-1.326271875"/>
<vertex x="-0.411525" y="-1.3256375"/>
<vertex x="-0.47194375" y="-1.22948125"/>
<vertex x="-0.4725125" y="-1.22920625"/>
<vertex x="-0.473009375" y="-1.22778125"/>
<vertex x="-0.4738125" y="-1.22650625"/>
<vertex x="-0.473671875" y="-1.225890625"/>
<vertex x="-0.511175" y="-1.118721875"/>
<vertex x="-0.51166875" y="-1.118328125"/>
<vertex x="-0.5118375" y="-1.116825"/>
<vertex x="-0.512334375" y="-1.11540625"/>
<vertex x="-0.5120625" y="-1.114840625"/>
<vertex x="-0.524775" y="-1.001990625"/>
<vertex x="-0.52516875" y="-1.001496875"/>
<vertex x="-0.525" y="-1"/>
<vertex x="-0.52516875" y="-0.998503125"/>
<vertex x="-0.524775" y="-0.998009375"/>
<vertex x="-0.5120625" y="-0.885159375"/>
<vertex x="-0.512334375" y="-0.88459375"/>
<vertex x="-0.5118375" y="-0.883175"/>
<vertex x="-0.51166875" y="-0.881671875"/>
<vertex x="-0.511175" y="-0.881278125"/>
<vertex x="-0.473671875" y="-0.774109375"/>
<vertex x="-0.4738125" y="-0.77349375"/>
<vertex x="-0.473009375" y="-0.77221875"/>
<vertex x="-0.4725125" y="-0.77079375"/>
<vertex x="-0.47194375" y="-0.77051875"/>
<vertex x="-0.411525" y="-0.6743625"/>
<vertex x="-0.411525" y="-0.673728125"/>
<vertex x="-0.410453125" y="-0.67265625"/>
<vertex x="-0.40965625" y="-0.6713875"/>
<vertex x="-0.40904375" y="-0.671246875"/>
<vertex x="-0.328753125" y="-0.59095625"/>
<vertex x="-0.3286125" y="-0.59034375"/>
<vertex x="-0.32734375" y="-0.589546875"/>
<vertex x="-0.326271875" y="-0.588475"/>
<vertex x="-0.3256375" y="-0.588475"/>
<vertex x="-0.22948125" y="-0.52805625"/>
<vertex x="-0.22920625" y="-0.5274875"/>
<vertex x="-0.22778125" y="-0.526990625"/>
<vertex x="-0.22650625" y="-0.5261875"/>
<vertex x="-0.225890625" y="-0.526328125"/>
<vertex x="-0.118721875" y="-0.488825"/>
<vertex x="-0.118328125" y="-0.48833125"/>
<vertex x="-0.116825" y="-0.4881625"/>
<vertex x="-0.11540625" y="-0.487665625"/>
<vertex x="-0.114840625" y="-0.4879375"/>
<vertex x="0" y="-0.475"/>
<vertex x="0" y="-0.175"/>
<vertex x="-0.160940625" y="-0.19085"/>
<vertex x="-0.315696875" y="-0.23779375"/>
<vertex x="-0.45835" y="-0.3140375"/>
<vertex x="-0.5833625" y="-0.4166375"/>
<vertex x="-0.6859625" y="-0.54165"/>
<vertex x="-0.76220625" y="-0.684303125"/>
<vertex x="-0.80915" y="-0.839059375"/>
<vertex x="-0.825003125" y="-1"/>
<vertex x="-0.80915" y="-1.160940625"/>
<vertex x="-0.76220625" y="-1.315696875"/>
<vertex x="-0.6859625" y="-1.45835"/>
<vertex x="-0.5833625" y="-1.5833625"/>
<vertex x="-0.45835" y="-1.6859625"/>
<vertex x="-0.315696875" y="-1.76220625"/>
</polygon>
<polygon width="0.01" layer="29" pour="solid">
<vertex x="0" y="-1.425"/>
<vertex x="0" y="-1.925"/>
<vertex x="0.18045" y="-1.907228125"/>
<vertex x="0.353965625" y="-1.85459375"/>
<vertex x="0.51390625" y="-1.769109375"/>
<vertex x="0.654075" y="-1.654075"/>
<vertex x="0.769109375" y="-1.51390625"/>
<vertex x="0.85459375" y="-1.353965625"/>
<vertex x="0.907228125" y="-1.18045"/>
<vertex x="0.925003125" y="-1"/>
<vertex x="0.907228125" y="-0.81955"/>
<vertex x="0.85459375" y="-0.646034375"/>
<vertex x="0.769109375" y="-0.48609375"/>
<vertex x="0.654075" y="-0.345925"/>
<vertex x="0.51390625" y="-0.230890625"/>
<vertex x="0.353965625" y="-0.14540625"/>
<vertex x="0.18045" y="-0.092771875"/>
<vertex x="0" y="-0.075"/>
<vertex x="0" y="-0.575"/>
<vertex x="0.0925875" y="-0.58543125"/>
<vertex x="0.093153125" y="-0.585159375"/>
<vertex x="0.094571875" y="-0.58565625"/>
<vertex x="0.096075" y="-0.585825"/>
<vertex x="0.09646875" y="-0.58631875"/>
<vertex x="0.182503125" y="-0.616425"/>
<vertex x="0.18311875" y="-0.616284375"/>
<vertex x="0.18439375" y="-0.6170875"/>
<vertex x="0.18581875" y="-0.617584375"/>
<vertex x="0.18609375" y="-0.618153125"/>
<vertex x="0.263290625" y="-0.666659375"/>
<vertex x="0.263925" y="-0.666659375"/>
<vertex x="0.264996875" y="-0.66773125"/>
<vertex x="0.266265625" y="-0.668528125"/>
<vertex x="0.26640625" y="-0.669140625"/>
<vertex x="0.330859375" y="-0.73359375"/>
<vertex x="0.331471875" y="-0.733734375"/>
<vertex x="0.33226875" y="-0.735003125"/>
<vertex x="0.333340625" y="-0.736075"/>
<vertex x="0.333340625" y="-0.736709375"/>
<vertex x="0.381846875" y="-0.81390625"/>
<vertex x="0.382415625" y="-0.81418125"/>
<vertex x="0.3829125" y="-0.81560625"/>
<vertex x="0.383715625" y="-0.81688125"/>
<vertex x="0.383575" y="-0.817496875"/>
<vertex x="0.41368125" y="-0.90353125"/>
<vertex x="0.414175" y="-0.903925"/>
<vertex x="0.41434375" y="-0.905428125"/>
<vertex x="0.414840625" y="-0.906846875"/>
<vertex x="0.41456875" y="-0.9074125"/>
<vertex x="0.424775" y="-0.998009375"/>
<vertex x="0.42516875" y="-0.998503125"/>
<vertex x="0.425" y="-1"/>
<vertex x="0.42516875" y="-1.001496875"/>
<vertex x="0.424775" y="-1.001990625"/>
<vertex x="0.41456875" y="-1.0925875"/>
<vertex x="0.414840625" y="-1.093153125"/>
<vertex x="0.41434375" y="-1.094571875"/>
<vertex x="0.414175" y="-1.096075"/>
<vertex x="0.41368125" y="-1.09646875"/>
<vertex x="0.383575" y="-1.182503125"/>
<vertex x="0.383715625" y="-1.18311875"/>
<vertex x="0.3829125" y="-1.18439375"/>
<vertex x="0.382415625" y="-1.18581875"/>
<vertex x="0.381846875" y="-1.18609375"/>
<vertex x="0.333340625" y="-1.263290625"/>
<vertex x="0.333340625" y="-1.263925"/>
<vertex x="0.33226875" y="-1.264996875"/>
<vertex x="0.331471875" y="-1.266265625"/>
<vertex x="0.330859375" y="-1.26640625"/>
<vertex x="0.26640625" y="-1.330859375"/>
<vertex x="0.266265625" y="-1.331471875"/>
<vertex x="0.264996875" y="-1.33226875"/>
<vertex x="0.263925" y="-1.333340625"/>
<vertex x="0.263290625" y="-1.333340625"/>
<vertex x="0.18609375" y="-1.381846875"/>
<vertex x="0.18581875" y="-1.382415625"/>
<vertex x="0.18439375" y="-1.3829125"/>
<vertex x="0.18311875" y="-1.383715625"/>
<vertex x="0.182503125" y="-1.383575"/>
<vertex x="0.09646875" y="-1.41368125"/>
<vertex x="0.096075" y="-1.414175"/>
<vertex x="0.094571875" y="-1.41434375"/>
<vertex x="0.093153125" y="-1.414840625"/>
<vertex x="0.0925875" y="-1.41456875"/>
</polygon>
<polygon width="0.01" layer="29" pour="solid">
<vertex x="-0.18045" y="-1.907228125"/>
<vertex x="0" y="-1.925"/>
<vertex x="0" y="-1.425"/>
<vertex x="-0.0925875" y="-1.41456875"/>
<vertex x="-0.093153125" y="-1.414840625"/>
<vertex x="-0.094571875" y="-1.41434375"/>
<vertex x="-0.096075" y="-1.414175"/>
<vertex x="-0.09646875" y="-1.41368125"/>
<vertex x="-0.182503125" y="-1.383575"/>
<vertex x="-0.18311875" y="-1.383715625"/>
<vertex x="-0.18439375" y="-1.3829125"/>
<vertex x="-0.18581875" y="-1.382415625"/>
<vertex x="-0.18609375" y="-1.381846875"/>
<vertex x="-0.263290625" y="-1.333340625"/>
<vertex x="-0.263925" y="-1.333340625"/>
<vertex x="-0.264996875" y="-1.33226875"/>
<vertex x="-0.266265625" y="-1.331471875"/>
<vertex x="-0.26640625" y="-1.330859375"/>
<vertex x="-0.330859375" y="-1.26640625"/>
<vertex x="-0.331471875" y="-1.266265625"/>
<vertex x="-0.33226875" y="-1.264996875"/>
<vertex x="-0.333340625" y="-1.263925"/>
<vertex x="-0.333340625" y="-1.263290625"/>
<vertex x="-0.381846875" y="-1.18609375"/>
<vertex x="-0.382415625" y="-1.18581875"/>
<vertex x="-0.3829125" y="-1.18439375"/>
<vertex x="-0.383715625" y="-1.18311875"/>
<vertex x="-0.383575" y="-1.182503125"/>
<vertex x="-0.41368125" y="-1.09646875"/>
<vertex x="-0.414175" y="-1.096075"/>
<vertex x="-0.41434375" y="-1.094571875"/>
<vertex x="-0.414840625" y="-1.093153125"/>
<vertex x="-0.41456875" y="-1.0925875"/>
<vertex x="-0.424775" y="-1.001990625"/>
<vertex x="-0.42516875" y="-1.001496875"/>
<vertex x="-0.425" y="-1"/>
<vertex x="-0.42516875" y="-0.998503125"/>
<vertex x="-0.424775" y="-0.998009375"/>
<vertex x="-0.41456875" y="-0.9074125"/>
<vertex x="-0.414840625" y="-0.906846875"/>
<vertex x="-0.41434375" y="-0.905428125"/>
<vertex x="-0.414175" y="-0.903925"/>
<vertex x="-0.41368125" y="-0.90353125"/>
<vertex x="-0.383575" y="-0.817496875"/>
<vertex x="-0.383715625" y="-0.81688125"/>
<vertex x="-0.3829125" y="-0.81560625"/>
<vertex x="-0.382415625" y="-0.81418125"/>
<vertex x="-0.381846875" y="-0.81390625"/>
<vertex x="-0.333340625" y="-0.736709375"/>
<vertex x="-0.333340625" y="-0.736075"/>
<vertex x="-0.33226875" y="-0.735003125"/>
<vertex x="-0.331471875" y="-0.733734375"/>
<vertex x="-0.330859375" y="-0.73359375"/>
<vertex x="-0.26640625" y="-0.669140625"/>
<vertex x="-0.266265625" y="-0.668528125"/>
<vertex x="-0.264996875" y="-0.66773125"/>
<vertex x="-0.263925" y="-0.666659375"/>
<vertex x="-0.263290625" y="-0.666659375"/>
<vertex x="-0.18609375" y="-0.618153125"/>
<vertex x="-0.18581875" y="-0.617584375"/>
<vertex x="-0.18439375" y="-0.6170875"/>
<vertex x="-0.18311875" y="-0.616284375"/>
<vertex x="-0.182503125" y="-0.616425"/>
<vertex x="-0.09646875" y="-0.58631875"/>
<vertex x="-0.096075" y="-0.585825"/>
<vertex x="-0.094571875" y="-0.58565625"/>
<vertex x="-0.093153125" y="-0.585159375"/>
<vertex x="-0.0925875" y="-0.58543125"/>
<vertex x="0" y="-0.575"/>
<vertex x="0" y="-0.075"/>
<vertex x="-0.18045" y="-0.092771875"/>
<vertex x="-0.353965625" y="-0.14540625"/>
<vertex x="-0.51390625" y="-0.230890625"/>
<vertex x="-0.654075" y="-0.345925"/>
<vertex x="-0.769109375" y="-0.48609375"/>
<vertex x="-0.85459375" y="-0.646034375"/>
<vertex x="-0.907228125" y="-0.81955"/>
<vertex x="-0.925003125" y="-1"/>
<vertex x="-0.907228125" y="-1.18045"/>
<vertex x="-0.85459375" y="-1.353965625"/>
<vertex x="-0.769109375" y="-1.51390625"/>
<vertex x="-0.654075" y="-1.654075"/>
<vertex x="-0.51390625" y="-1.769109375"/>
<vertex x="-0.353965625" y="-1.85459375"/>
</polygon>
<polygon width="0.01" layer="31" pour="solid">
<vertex x="0.20418125" y="-0.51659375"/>
<vertex x="0.2937" y="-0.5649"/>
<vertex x="0.508396875" y="-0.3502"/>
<vertex x="0.3767625" y="-0.266"/>
<vertex x="0.23159375" y="-0.208125"/>
<vertex x="0.0781375" y="-0.1786625"/>
<vertex x="-0.0781375" y="-0.1786625"/>
<vertex x="-0.23159375" y="-0.208125"/>
<vertex x="-0.3767625" y="-0.266"/>
<vertex x="-0.508396875" y="-0.3502"/>
<vertex x="-0.2937" y="-0.5649"/>
<vertex x="-0.20418125" y="-0.51659375"/>
<vertex x="-0.20391875" y="-0.516103125"/>
<vertex x="-0.20241875" y="-0.51564375"/>
<vertex x="-0.201028125" y="-0.51489375"/>
<vertex x="-0.200490625" y="-0.515053125"/>
<vertex x="-0.10514375" y="-0.4858875"/>
<vertex x="-0.1047875" y="-0.485453125"/>
<vertex x="-0.103215625" y="-0.485296875"/>
<vertex x="-0.1017125" y="-0.4848375"/>
<vertex x="-0.101221875" y="-0.4851"/>
<vertex x="-0.001996875" y="-0.47525"/>
<vertex x="-0.001565625" y="-0.474896875"/>
<vertex x="0" y="-0.475053125"/>
<vertex x="0.001565625" y="-0.474896875"/>
<vertex x="0.001996875" y="-0.47525"/>
<vertex x="0.101221875" y="-0.4851"/>
<vertex x="0.1017125" y="-0.4848375"/>
<vertex x="0.103215625" y="-0.485296875"/>
<vertex x="0.1047875" y="-0.485453125"/>
<vertex x="0.10514375" y="-0.4858875"/>
<vertex x="0.200490625" y="-0.515053125"/>
<vertex x="0.201028125" y="-0.51489375"/>
<vertex x="0.20241875" y="-0.51564375"/>
<vertex x="0.20391875" y="-0.516103125"/>
</polygon>
<polygon width="0.01" layer="31" pour="solid">
<vertex x="-0.734" y="-1.3767625"/>
<vertex x="-0.6498" y="-1.508396875"/>
<vertex x="-0.4351" y="-1.2937"/>
<vertex x="-0.48340625" y="-1.20418125"/>
<vertex x="-0.483896875" y="-1.20391875"/>
<vertex x="-0.48435625" y="-1.20241875"/>
<vertex x="-0.48510625" y="-1.201028125"/>
<vertex x="-0.484946875" y="-1.200490625"/>
<vertex x="-0.5141125" y="-1.10514375"/>
<vertex x="-0.514546875" y="-1.1047875"/>
<vertex x="-0.514703125" y="-1.103215625"/>
<vertex x="-0.5151625" y="-1.1017125"/>
<vertex x="-0.5149" y="-1.101221875"/>
<vertex x="-0.52475" y="-1.001996875"/>
<vertex x="-0.525103125" y="-1.001565625"/>
<vertex x="-0.524946875" y="-1"/>
<vertex x="-0.525103125" y="-0.998434375"/>
<vertex x="-0.52475" y="-0.998003125"/>
<vertex x="-0.5149" y="-0.898778125"/>
<vertex x="-0.5151625" y="-0.8982875"/>
<vertex x="-0.514703125" y="-0.896784375"/>
<vertex x="-0.514546875" y="-0.8952125"/>
<vertex x="-0.5141125" y="-0.89485625"/>
<vertex x="-0.484946875" y="-0.799509375"/>
<vertex x="-0.48510625" y="-0.798971875"/>
<vertex x="-0.48435625" y="-0.79758125"/>
<vertex x="-0.483896875" y="-0.79608125"/>
<vertex x="-0.48340625" y="-0.79581875"/>
<vertex x="-0.4351" y="-0.7063"/>
<vertex x="-0.6498" y="-0.491603125"/>
<vertex x="-0.734" y="-0.6232375"/>
<vertex x="-0.791875" y="-0.76840625"/>
<vertex x="-0.8213375" y="-0.9218625"/>
<vertex x="-0.8213375" y="-1.0781375"/>
<vertex x="-0.791875" y="-1.23159375"/>
</polygon>
<polygon width="0.01" layer="31" pour="solid">
<vertex x="-0.0781375" y="-1.8213375"/>
<vertex x="0.0781375" y="-1.8213375"/>
<vertex x="0.23159375" y="-1.791875"/>
<vertex x="0.3767625" y="-1.734"/>
<vertex x="0.508396875" y="-1.6498"/>
<vertex x="0.2937" y="-1.4351"/>
<vertex x="0.20418125" y="-1.48340625"/>
<vertex x="0.20391875" y="-1.483896875"/>
<vertex x="0.20241875" y="-1.48435625"/>
<vertex x="0.201028125" y="-1.48510625"/>
<vertex x="0.200490625" y="-1.484946875"/>
<vertex x="0.10514375" y="-1.5141125"/>
<vertex x="0.1047875" y="-1.514546875"/>
<vertex x="0.103215625" y="-1.514703125"/>
<vertex x="0.1017125" y="-1.5151625"/>
<vertex x="0.101221875" y="-1.5149"/>
<vertex x="0.001996875" y="-1.52475"/>
<vertex x="0.001565625" y="-1.525103125"/>
<vertex x="0" y="-1.524946875"/>
<vertex x="-0.001565625" y="-1.525103125"/>
<vertex x="-0.001996875" y="-1.52475"/>
<vertex x="-0.101221875" y="-1.5149"/>
<vertex x="-0.1017125" y="-1.5151625"/>
<vertex x="-0.103215625" y="-1.514703125"/>
<vertex x="-0.1047875" y="-1.514546875"/>
<vertex x="-0.10514375" y="-1.5141125"/>
<vertex x="-0.200490625" y="-1.484946875"/>
<vertex x="-0.201028125" y="-1.48510625"/>
<vertex x="-0.20241875" y="-1.48435625"/>
<vertex x="-0.20391875" y="-1.483896875"/>
<vertex x="-0.20418125" y="-1.48340625"/>
<vertex x="-0.2937" y="-1.4351"/>
<vertex x="-0.508396875" y="-1.6498"/>
<vertex x="-0.3767625" y="-1.734"/>
<vertex x="-0.23159375" y="-1.791875"/>
</polygon>
<polygon width="0.01" layer="31" pour="solid">
<vertex x="0.4351" y="-1.2937"/>
<vertex x="0.6498" y="-1.508396875"/>
<vertex x="0.734" y="-1.3767625"/>
<vertex x="0.791875" y="-1.23159375"/>
<vertex x="0.8213375" y="-1.0781375"/>
<vertex x="0.8213375" y="-0.9218625"/>
<vertex x="0.791875" y="-0.76840625"/>
<vertex x="0.734" y="-0.6232375"/>
<vertex x="0.6498" y="-0.491603125"/>
<vertex x="0.4351" y="-0.7063"/>
<vertex x="0.48340625" y="-0.79581875"/>
<vertex x="0.483896875" y="-0.79608125"/>
<vertex x="0.48435625" y="-0.79758125"/>
<vertex x="0.48510625" y="-0.798971875"/>
<vertex x="0.484946875" y="-0.799509375"/>
<vertex x="0.5141125" y="-0.89485625"/>
<vertex x="0.514546875" y="-0.8952125"/>
<vertex x="0.514703125" y="-0.896784375"/>
<vertex x="0.5151625" y="-0.8982875"/>
<vertex x="0.5149" y="-0.898778125"/>
<vertex x="0.52475" y="-0.998003125"/>
<vertex x="0.525103125" y="-0.998434375"/>
<vertex x="0.524946875" y="-1"/>
<vertex x="0.525103125" y="-1.001565625"/>
<vertex x="0.52475" y="-1.001996875"/>
<vertex x="0.5149" y="-1.101221875"/>
<vertex x="0.5151625" y="-1.1017125"/>
<vertex x="0.514703125" y="-1.103215625"/>
<vertex x="0.514546875" y="-1.1047875"/>
<vertex x="0.5141125" y="-1.10514375"/>
<vertex x="0.484946875" y="-1.200490625"/>
<vertex x="0.48510625" y="-1.201028125"/>
<vertex x="0.48435625" y="-1.20241875"/>
<vertex x="0.483896875" y="-1.20391875"/>
<vertex x="0.48340625" y="-1.20418125"/>
</polygon>
<smd name="4_1" x="-0.675" y="-1" dx="0.15" dy="0.15" layer="1" stop="no" thermals="no" cream="no"/>
<smd name="4_2" x="0.675" y="-1" dx="0.15" dy="0.15" layer="1" stop="no" thermals="no" cream="no"/>
<hole x="0" y="-1" drill="0.25"/>
<smd name="3" x="-1.075" y="0.28" dx="0.6" dy="0.4" layer="1"/>
<smd name="5" x="1.075" y="0.28" dx="0.6" dy="0.4" layer="1"/>
<smd name="2" x="-1.075" y="0.93" dx="0.6" dy="0.4" layer="1"/>
<smd name="6" x="1.075" y="0.93" dx="0.6" dy="0.4" layer="1"/>
<smd name="1" x="-1.075" y="1.58" dx="0.6" dy="0.4" layer="1"/>
<smd name="7" x="1.075" y="1.58" dx="0.6" dy="0.4" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="DMM-4026-B-I2S-R" library_version="1">
<wire x1="-12.7" y1="10.16" x2="-12.7" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-10.16" x2="12.7" y2="-10.16" width="0.254" layer="94"/>
<wire x1="12.7" y1="-10.16" x2="12.7" y2="10.16" width="0.254" layer="94"/>
<wire x1="12.7" y1="10.16" x2="-12.7" y2="10.16" width="0.254" layer="94"/>
<text x="-12.7" y="11.43" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="-11.43" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<pin name="GND" x="17.78" y="-7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="SD" x="17.78" y="0" length="middle" direction="out" rot="R180"/>
<pin name="VDD" x="17.78" y="7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="LR" x="-17.78" y="2.54" length="middle" direction="in"/>
<pin name="CONFIG" x="-17.78" y="-2.54" length="middle" direction="in"/>
<pin name="WS" x="17.78" y="2.54" length="middle" direction="in" rot="R180"/>
<pin name="SCK" x="17.78" y="-2.54" length="middle" direction="in" function="clk" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DMM-4026-B-I2S-R" prefix="MK" library_version="1">
<gates>
<gate name="G$1" symbol="DMM-4026-B-I2S-R" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MIC_DMM-4026-B-I2S-R">
<connects>
<connect gate="G$1" pin="CONFIG" pad="2"/>
<connect gate="G$1" pin="GND" pad="4_1 4_2"/>
<connect gate="G$1" pin="LR" pad="1"/>
<connect gate="G$1" pin="SCK" pad="6"/>
<connect gate="G$1" pin="SD" pad="7"/>
<connect gate="G$1" pin="VDD" pad="3"/>
<connect gate="G$1" pin="WS" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="MANUFACTURER" value="PUI Audio"/>
<attribute name="MAXIMUM_PACKAGE_HEIGHT" value="1 mm"/>
<attribute name="CREATOR" value="KARTHIK"/>
<attribute name="NOTES" value=""/>
<attribute name="STANDARD" value="Manufacturer Recommendations"/>
<attribute name="PARTREV" value="A"/>
<attribute name="UNIT" value="mm"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<groups>
<schematic_group name="CAMERA"/>
<schematic_group name="POWER"/>
<schematic_group name="SERVO_CONNECTORS"/>
<schematic_group name="IMU"/>
<schematic_group name="BUTTONS"/>
<schematic_group name="MICRO_SD"/>
<schematic_group name="TFT_DISPLAY"/>
<schematic_group name="ESP32"/>
<schematic_group name="CONNECTORS"/>
<schematic_group name="SERVO_DRIVER"/>
<schematic_group name="RESISTORS"/>
<schematic_group name="GNSS"/>
<schematic_group name="AMP_SOUND"/>
<schematic_group name="MIC"/>
</groups>
<parts>
<part name="U$1" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 6"/>
<part name="U$2" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 7"/>
<part name="U$3" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 8"/>
<part name="U$4" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 9"/>
<part name="U$5" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 10"/>
<part name="U$6" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 11"/>
<part name="U$7" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 12"/>
<part name="U$8" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 13"/>
<part name="U$9" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 14"/>
<part name="U$11" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 4"/>
<part name="U$12" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 5"/>
<part name="U$13" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 1"/>
<part name="U$15" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 2"/>
<part name="U$16" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 16"/>
<part name="U$17" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 17"/>
<part name="U$18" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 18"/>
<part name="U$19" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 19"/>
<part name="U$20" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 21"/>
<part name="U$21" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 20"/>
<part name="U$22" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 22"/>
<part name="U$23" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 23"/>
<part name="U$24" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 24"/>
<part name="U$25" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 25"/>
<part name="SUPPLY7" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY12" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY13" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY14" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY15" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY16" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY17" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY18" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY19" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY20" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY21" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY22" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY23" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY24" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY25" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY26" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY27" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY28" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY29" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY30" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY31" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY32" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY33" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY34" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY35" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="U$14" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 3"/>
<part name="U$10" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 15"/>
<part name="SUPPLY4" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY6" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY9" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY10" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY47" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY48" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY49" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY50" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY51" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY52" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY53" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY54" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY55" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY56" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY57" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY59" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY60" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY61" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY62" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY63" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY64" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY65" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY66" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY67" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY58" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="J1" library="Connector" library_urn="urn:adsk.eagle:library:16378166" deviceset="2828XX-2" device="282837-2" package3d_urn="urn:adsk.eagle:package:24957621/2" value="TERM-BLK-2P"/>
<part name="SUPPLY11" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY3" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY1" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY36" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY37" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="U$26" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 26"/>
<part name="U$27" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 27"/>
<part name="U$28" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 28"/>
<part name="U$29" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 29"/>
<part name="U$30" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 30"/>
<part name="U$31" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 31"/>
<part name="U$32" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="PINHD-1X03" device="_1X03M" package3d_urn="urn:adsk.eagle:package:22458/2" value="Servo 32"/>
<part name="SUPPLY40" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY41" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY42" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY43" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY44" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY45" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY46" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY69" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY70" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY71" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY72" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY73" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY74" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY76" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="SUPPLY90" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY98" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C7" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="SUPPLY2" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C1" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="C2" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="C4" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="PS1" library="TL1963A-33DCYR" library_urn="urn:adsk.wipprod:fs.file:vf.nukNfVCiQSiYwS2wA_aO-Q" deviceset="TL1963A-33DCYR" device=""/>
<part name="IC4" library="XC6206P122MR-G" library_urn="urn:adsk.wipprod:fs.file:vf.NEs_bSMgQmembkkqPoqipw" deviceset="XC6206P122MR-G" device=""/>
<part name="C6" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="C8" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="SUPPLY81" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY82" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C9" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="C10" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="IC6" library="XC6206P282MR-G" library_urn="urn:adsk.wipprod:fs.file:vf.dxXTFAhhT2yqCCWQlP4POQ" deviceset="XC6206P282MR-G" device=""/>
<part name="SUPPLY84" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C13" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="SUPPLY87" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C14" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="IC5" library="ESP32-S3-WROOM-1U-N16R8" library_urn="urn:adsk.wipprod:fs.file:vf.cnL6V3VESOau68oAUQhTdg" deviceset="ESP32-S3-WROOM-1U-N16R8" device=""/>
<part name="FRAME2" library="frames" library_urn="urn:adsk.eagle:library:42976481" deviceset="FRAME_B_L" device="">
<attribute name="32_SERVO_CONTROLLER" value="1"/>
<attribute name="ENDURANCE_RC_LLC" value="ENDURANCE R/C LLC"/>
</part>
<part name="JP1" library="Connector" library_urn="urn:adsk.eagle:library:16378166" deviceset="PINHD-1X2" device="" package3d_urn="urn:adsk.eagle:package:22435/2" value="PINHD-1X2"/>
<part name="SUPPLY91" library="Tutorial - Fusion 360" library_urn="urn:adsk.eagle:library:16997205" deviceset="VCC-CIRCLE" device="" value="VCC"/>
<part name="J3" library="132135RP" library_urn="urn:adsk.wipprod:fs.file:vf.O64LxLIyT4Kzl4f1uo6jAg" deviceset="132135RP" device=""/>
<part name="J5" library="2026-07-14_02-46-40_Library" library_urn="urn:adsk.wipprod:fs.file:vf.Erw2bw45Sma41euQclXpnw" deviceset="SM04B-SRSS-TB" device="CONN_SM04B-SRSS-TB_JST"/>
<part name="C12" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="SUPPLY80" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY94" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY95" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY101" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="J6" library="MEM2085-00-115-00-A" library_urn="urn:adsk.wipprod:fs.file:vf.nF0OIkYKTUugXdX2XtAhqA" deviceset="MEM2085-00-115-00-A" device=""/>
<part name="J2" library="UJ20-C-H-G-SMT-1-P16-TR" library_urn="urn:adsk.wipprod:fs.file:vf.VgEXy_XXReqS1Zb8YyEAgA" deviceset="UJ20-C-H-G-SMT-1-P16-TR" device=""/>
<part name="SUPPLY117" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY118" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="IC7" library="PCF8574RGYR" library_urn="urn:adsk.wipprod:fs.file:vf.lcGkz4doQpyc2bgh-QTqqA" deviceset="PCF8574RGYR" device=""/>
<part name="SUPPLY111" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY112" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="IC1" library="BNO085" library_urn="urn:adsk.wipprod:fs.file:vf.KeicR6v6QYquMuzG2LVDPw" deviceset="BNO085" device=""/>
<part name="C17" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="SUPPLY113" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY114" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY115" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C18" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="SUPPLY116" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C20" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="22pF"/>
<part name="SUPPLY119" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C21" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="22pF"/>
<part name="SUPPLY120" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY121" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C19" library="830009706" library_urn="urn:adsk.wipprod:fs.file:vf.M16k7mWdQ5aB1VZZsRisGQ" deviceset="830009706" device=""/>
<part name="SUPPLY122" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY93" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="U$33" library="TFT_Library" library_urn="urn:adsk.wipprod:fs.file:vf.OMwaF8U3QfOV1ezvEUx29w" deviceset="1.47_IN_TFT_172_320_ST7789P3" device=""/>
<part name="S1" library="B3U-1000P" library_urn="urn:adsk.wipprod:fs.file:vf.XJbiwRhKSp-iOlNm4yOdNw" deviceset="B3U-1000P" device=""/>
<part name="S2" library="B3U-1000P" library_urn="urn:adsk.wipprod:fs.file:vf.XJbiwRhKSp-iOlNm4yOdNw" deviceset="B3U-1000P" device=""/>
<part name="S3" library="JS1300AQ" library_urn="urn:adsk.wipprod:fs.file:vf.CcEUDwFHTFK9mms8L6KdfA" deviceset="JS1300AQ" device=""/>
<part name="J7" library="F31L-1A7H1-11024" library_urn="urn:adsk.wipprod:fs.file:vf.R1_jZztcQ9au8PnQwM-Qyw" deviceset="F31L-1A7H1-11024" device=""/>
<part name="SUPPLY124" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="RN1" library="CAY16-103J4LF" library_urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g" deviceset="CAY16-103J4LF" device=""/>
<part name="IC10" library="STM32G071C8U6TR" library_urn="urn:adsk.wipprod:fs.file:vf.njSnwR1zRQ-aCaWkX6R64g" deviceset="STM32G071C8U6TR" device=""/>
<part name="SUPPLY127" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY5" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C3" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C-US" device="CHIP-0805(2012-METRIC)" package3d_urn="urn:adsk.eagle:package:16290897/5" technology="_" value="15pF"/>
<part name="SUPPLY8" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C5" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="SUPPLY38" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="R1" library="Resistor" library_urn="urn:adsk.eagle:library:16378527" deviceset="R" device="CHIP-0603(1608-METRIC)" package3d_urn="urn:adsk.eagle:package:16378565/5" technology="_" value="1K"/>
<part name="SUPPLY39" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY68" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY75" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY77" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C11" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-1210(3225-METRIC)" package3d_urn="urn:adsk.eagle:package:16290903/5" technology="_" value="100uF"/>
<part name="C15" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="4.7uF"/>
<part name="SUPPLY78" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY79" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="JP2" library="Connector" library_urn="urn:adsk.eagle:library:16378166" deviceset="PINHD-1X4" device="" package3d_urn="urn:adsk.eagle:package:22407/2" value="PINHD-1X4"/>
<part name="SUPPLY83" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="RN2" library="CAY16-103J4LF" library_urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g" deviceset="CAY16-103J4LF" device=""/>
<part name="RN3" library="CAY16-103J4LF" library_urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g" deviceset="CAY16-103J4LF" device=""/>
<part name="RN4" library="CAY16-103J4LF" library_urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g" deviceset="CAY16-103J4LF" device=""/>
<part name="RN5" library="CAY16-103J4LF" library_urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g" deviceset="CAY16-103J4LF" device=""/>
<part name="SUPPLY85" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY86" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="IC3" library="CAM-M8Q-0" library_urn="urn:adsk.wipprod:fs.file:vf.0LPKsAaDRqKDEJUuXZtcBg" deviceset="CAM-M8Q-0" device=""/>
<part name="SUPPLY88" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY89" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY92" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="RN6" library="CAY16-103J4LF" library_urn="urn:adsk.wipprod:fs.file:vf.24Bfikl0QmaiAX6ewm5__g" deviceset="CAY16-103J4LF" device=""/>
<part name="IC2" library="MAX98357AETE+T" library_urn="urn:adsk.wipprod:fs.file:vf._VMllKDRSi61WhmqObQNgQ" deviceset="MAX98357AETE+T" device=""/>
<part name="J4" library="S4B-PH-SM4-TB" library_urn="urn:adsk.wipprod:fs.file:vf.LdgZlENWRX-5uo8bxX-GBQ" deviceset="S4B-PH-SM4-TB" device=""/>
<part name="SUPPLY97" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C16" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="C22" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="SUPPLY99" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY100" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY102" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C23" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="220pF"/>
<part name="C24" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="220pF"/>
<part name="R2" library="Resistor" library_urn="urn:adsk.eagle:library:16378527" deviceset="R-US" device="CHIP-0603(1608-METRIC)" package3d_urn="urn:adsk.eagle:package:16378565/5" technology="_" value="370K"/>
<part name="SUPPLY104" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY105" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="FB1" library="Filter" library_urn="urn:adsk.eagle:library:16378195" deviceset="FB_" device="_0603(1608)" package3d_urn="urn:adsk.eagle:package:16378199/1" technology="BLM18AG601SN1D" value="LM18AG601"/>
<part name="FB2" library="Filter" library_urn="urn:adsk.eagle:library:16378195" deviceset="FB_" device="_0603(1608)" package3d_urn="urn:adsk.eagle:package:16378199/1" technology="BLM18AG601SN1D" value="LM18AG601"/>
<part name="IC8" library="MAX98357AETE+T" library_urn="urn:adsk.wipprod:fs.file:vf._VMllKDRSi61WhmqObQNgQ" deviceset="MAX98357AETE+T" device=""/>
<part name="SUPPLY106" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C25" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="C26" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value="10uF"/>
<part name="SUPPLY107" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY108" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY109" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C27" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="220pF"/>
<part name="C28" library="Capacitor" library_urn="urn:adsk.eagle:library:16290819" deviceset="C" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16290895/5" technology="_" value="220pF"/>
<part name="SUPPLY123" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY125" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="FB3" library="Filter" library_urn="urn:adsk.eagle:library:16378195" deviceset="FB_" device="_0603(1608)" package3d_urn="urn:adsk.eagle:package:16378199/1" technology="BLM18AG601SN1D" value="LM18AG601"/>
<part name="FB4" library="Filter" library_urn="urn:adsk.eagle:library:16378195" deviceset="FB_" device="_0603(1608)" package3d_urn="urn:adsk.eagle:package:16378199/1" technology="BLM18AG601SN1D" value="LM18AG601"/>
<part name="SUPPLY110" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="MK1" library="DMM-4026-B-I2S-R" library_urn="urn:adsk.wipprod:fs.file:vf.YdAovc1lTsGKKiX495LWbQ" deviceset="DMM-4026-B-I2S-R" device=""/>
<part name="SUPPLY126" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="C29" library="Tinkercad" library_urn="urn:adsk.eagle:library:30890021" deviceset="CAPACITOR" device="CHIP-0504(1310-METRIC)" package3d_urn="urn:adsk.eagle:package:16290904/5" technology="_" value=".1uF"/>
<part name="SUPPLY103" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="R3" library="Resistor" library_urn="urn:adsk.eagle:library:16378527" deviceset="R" device="CHIP-0402(1005-METRIC)" package3d_urn="urn:adsk.eagle:package:16378568/5" technology="_" value="100K"/>
<part name="SUPPLY128" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="SUPPLY96" library="Power_Symbols" library_urn="urn:adsk.eagle:library:16502351" deviceset="GND-BAR" device="" value="GND"/>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:42976481" deviceset="FRAME_B_L" device="">
<attribute name="32_SERVO_CONTROLLER" value="1"/>
<attribute name="ENDURANCE_RC_LLC" value="ENDURANCE R/C LLC"/>
</part>
</parts>
<sheets>
<sheet>
<plain>
<text x="393.7" y="93.98" size="2.54" layer="97" align="center" grouprefs="TFT_DISPLAY">ST7789P3
172 x 320 SPI TFT</text>
<text x="22.86" y="12.7" size="2.54" layer="97" align="center" grouprefs="MICRO_SD">MICRO SD</text>
<text x="58.42" y="60.96" size="2.54" layer="97" grouprefs="BUTTONS">I2C Address: 0x21</text>
<text x="165.1" y="71.12" size="2.54" layer="97" grouprefs="CONNECTORS">NOTE: QWIIC/STEMMA expansion
boards require crossover cables.</text>
<text x="68.58" y="-236.22" size="2.54" layer="97" rot="R180" grouprefs="GNSS">I2C Address: 0x42</text>
<text x="152.4" y="-264.16" size="2.54" layer="97" grouprefs="SERVO_DRIVER">I2C Address: 0x30</text>
<text x="383.54" y="-25.4" size="1.778" layer="97" grouprefs="RESISTORS">10K</text>
<text x="383.54" y="-40.64" size="1.778" layer="97" grouprefs="RESISTORS">10K</text>
<text x="383.54" y="-55.88" size="1.778" layer="97" grouprefs="RESISTORS">10K</text>
<text x="383.54" y="-71.12" size="1.778" layer="97" grouprefs="RESISTORS">10K</text>
<text x="383.54" y="-86.36" size="1.778" layer="97" grouprefs="RESISTORS">10K</text>
<text x="383.54" y="-101.6" size="1.778" layer="97" grouprefs="RESISTORS">5.1K</text>
<text x="134.62" y="-91.44" size="1.778" layer="97" grouprefs="AMP_SOUND">RIGHT AMP</text>
<text x="223.52" y="-91.44" size="1.778" layer="97" grouprefs="AMP_SOUND">LEFT AMP</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="71.12" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="76.2" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$2" gate="G$1" x="83.82" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="88.9" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$3" gate="G$1" x="96.52" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="101.6" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$4" gate="G$1" x="7.62" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="12.7" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$5" gate="G$1" x="20.32" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="25.4" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$6" gate="G$1" x="33.02" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="38.1" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$7" gate="G$1" x="45.72" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="50.8" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$8" gate="G$1" x="58.42" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="63.5" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$9" gate="G$1" x="71.12" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="76.2" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$11" gate="G$1" x="45.72" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="50.8" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$12" gate="G$1" x="58.42" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="63.5" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$13" gate="G$1" x="7.62" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="12.7" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$15" gate="G$1" x="20.32" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="25.4" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$16" gate="G$1" x="96.52" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="101.6" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$17" gate="G$1" x="7.62" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="12.7" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$18" gate="G$1" x="20.32" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="25.4" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$19" gate="G$1" x="33.02" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="38.1" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$20" gate="G$1" x="58.42" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="63.5" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$21" gate="G$1" x="45.72" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="50.8" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$22" gate="G$1" x="71.12" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="76.2" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$23" gate="G$1" x="83.82" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="88.9" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$24" gate="G$1" x="96.52" y="-88.9" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="101.6" y="-81.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$25" gate="G$1" x="7.62" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="12.7" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY7" gate="G$1" x="5.08" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="5.08" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY12" gate="G$1" x="55.88" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="55.88" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY13" gate="G$1" x="43.18" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="43.18" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY14" gate="G$1" x="30.48" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="30.48" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY15" gate="G$1" x="17.78" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="17.78" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY16" gate="G$1" x="5.08" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="2.54" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY17" gate="G$1" x="93.98" y="-96.52" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="93.98" y="-98.425" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY18" gate="G$1" x="81.28" y="-96.52" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="81.28" y="-98.425" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY19" gate="G$1" x="68.58" y="-96.52" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="68.58" y="-98.425" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY20" gate="G$1" x="43.18" y="-99.06" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="43.18" y="-100.965" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY21" gate="G$1" x="30.48" y="-99.06" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="30.48" y="-100.965" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY22" gate="G$1" x="17.78" y="-99.06" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="17.78" y="-100.965" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY23" gate="G$1" x="5.08" y="-99.06" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="5.08" y="-100.965" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY24" gate="G$1" x="93.98" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="93.98" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY25" gate="G$1" x="55.88" y="-96.52" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="55.88" y="-98.425" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY26" gate="G$1" x="81.28" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="81.28" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY27" gate="G$1" x="68.58" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="68.58" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY28" gate="G$1" x="55.88" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="55.88" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY29" gate="G$1" x="43.18" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="43.18" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY30" gate="G$1" x="30.48" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="30.48" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY31" gate="G$1" x="17.78" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="17.78" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY32" gate="G$1" x="5.08" y="-68.58" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="5.08" y="-70.485" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY33" gate="G$1" x="93.98" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="93.98" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY34" gate="G$1" x="81.28" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="81.28" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY35" gate="G$1" x="68.58" y="-38.1" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="68.58" y="-40.005" size="1.778" layer="96" align="center"/>
</instance>
<instance part="U$14" gate="G$1" x="33.02" y="-27.94" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="38.1" y="-20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$10" gate="G$1" x="83.82" y="-58.42" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="88.9" y="-50.8" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY4" gate="G$1" x="7.62" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="7.747" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY6" gate="G$1" x="20.32" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="20.447" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY9" gate="G$1" x="33.02" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="33.147" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY10" gate="G$1" x="45.72" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="45.847" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY47" gate="G$1" x="58.42" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="58.547" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY48" gate="G$1" x="71.12" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="71.247" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY49" gate="G$1" x="83.82" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="83.947" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY50" gate="G$1" x="96.52" y="-43.18" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="96.647" y="-46.355" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY51" gate="G$1" x="7.62" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="7.747" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY52" gate="G$1" x="20.32" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="20.447" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY53" gate="G$1" x="33.02" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="33.147" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY54" gate="G$1" x="45.72" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="45.847" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY55" gate="G$1" x="58.42" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="58.547" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY56" gate="G$1" x="71.12" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="71.247" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY57" gate="G$1" x="83.82" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="83.947" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY59" gate="G$1" x="7.62" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="7.747" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY60" gate="G$1" x="20.32" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="20.447" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY61" gate="G$1" x="33.02" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="33.147" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY62" gate="G$1" x="45.72" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="45.847" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY63" gate="G$1" x="58.42" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="58.547" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY64" gate="G$1" x="71.12" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="71.247" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY65" gate="G$1" x="83.82" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="83.947" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY66" gate="G$1" x="96.52" y="-104.14" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="96.647" y="-107.315" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY67" gate="G$1" x="7.62" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="7.747" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY58" gate="G$1" x="96.52" y="-73.66" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="96.647" y="-76.835" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="J1" gate="G$1" x="213.36" y="106.68" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="218.694" y="109.22" size="1.778" layer="96" rot="R90" align="top-center"/>
<attribute name="NAME" x="213.36" y="112.014" size="1.778" layer="95" align="bottom-center"/>
</instance>
<instance part="SUPPLY11" gate="G$1" x="208.28" y="101.6" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="208.28" y="99.695" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY3" gate="G$1" x="208.28" y="116.84" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="208.153" y="120.015" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY1" gate="G$1" x="238.76" y="101.6" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="VALUE" x="236.855" y="101.6" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="SUPPLY36" gate="G$1" x="154.94" y="55.88" smashed="yes" rot="R180" grouprefs="ESP32">
<attribute name="VALUE" x="154.94" y="57.785" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY37" gate="G$1" x="200.66" y="-7.62" smashed="yes" rot="R90" grouprefs="ESP32">
<attribute name="VALUE" x="202.565" y="-7.62" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="U$26" gate="G$1" x="20.32" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="25.4" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$27" gate="G$1" x="33.02" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="38.1" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$28" gate="G$1" x="45.72" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="50.8" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$29" gate="G$1" x="58.42" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="63.5" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$30" gate="G$1" x="71.12" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="76.2" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$31" gate="G$1" x="83.82" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="88.9" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$32" gate="G$1" x="96.52" y="-119.38" smashed="yes" rot="R90" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="101.6" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY40" gate="G$1" x="17.78" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="17.78" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY41" gate="G$1" x="20.32" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="20.447" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY42" gate="G$1" x="30.48" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="30.48" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY43" gate="G$1" x="43.18" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="43.18" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY44" gate="G$1" x="55.88" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="55.88" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY45" gate="G$1" x="68.58" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="68.58" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY46" gate="G$1" x="81.28" y="-127" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="81.28" y="-128.905" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY69" gate="G$1" x="93.98" y="-129.54" smashed="yes" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="93.98" y="-131.445" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY70" gate="G$1" x="33.02" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="33.147" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY71" gate="G$1" x="45.72" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="45.847" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY72" gate="G$1" x="58.42" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="58.547" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY73" gate="G$1" x="71.12" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="71.247" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY74" gate="G$1" x="83.82" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="83.947" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY76" gate="G$1" x="96.52" y="-134.62" smashed="yes" rot="R180" grouprefs="SERVO_CONNECTORS">
<attribute name="VALUE" x="96.647" y="-137.795" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY90" gate="G$1" x="35.56" y="91.44" smashed="yes" rot="R90" grouprefs="BUTTONS">
<attribute name="VALUE" x="37.465" y="91.44" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY98" gate="G$1" x="147.32" y="81.28" smashed="yes" rot="R90" grouprefs="CONNECTORS">
<attribute name="VALUE" x="149.225" y="81.28" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C7" gate="G$1" x="251.46" y="96.52" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="248.92" y="99.06" size="1.778" layer="95"/>
<attribute name="VALUE" x="246.38" y="92.456" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY2" gate="G$1" x="35.56" y="73.66" smashed="yes" rot="R90" grouprefs="BUTTONS">
<attribute name="VALUE" x="37.465" y="73.66" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C1" gate="G$1" x="251.46" y="106.68" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="248.92" y="109.22" size="1.778" layer="95"/>
<attribute name="VALUE" x="246.38" y="102.616" size="1.778" layer="96"/>
</instance>
<instance part="C2" gate="G$1" x="251.46" y="86.36" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="248.92" y="88.9" size="1.778" layer="95"/>
<attribute name="VALUE" x="246.38" y="82.296" size="1.778" layer="96"/>
</instance>
<instance part="C4" gate="G$1" x="251.46" y="116.84" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="248.92" y="119.38" size="1.778" layer="95"/>
<attribute name="VALUE" x="246.38" y="112.776" size="1.778" layer="96"/>
</instance>
<instance part="PS1" gate="G$1" x="254" y="104.14" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="267.97" y="111.76" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="260.35" y="109.22" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="IC4" gate="G$1" x="320.04" y="111.76" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="331.47" y="119.38" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="323.85" y="116.84" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="C6" gate="G$1" x="302.26" y="109.22" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="NAME" x="304.8" y="111.76" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="298.196" y="111.76" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="C8" gate="G$1" x="312.42" y="109.22" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="NAME" x="314.96" y="111.76" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="308.356" y="114.3" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="SUPPLY81" gate="G$1" x="294.64" y="114.3" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="VALUE" x="292.735" y="114.3" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="SUPPLY82" gate="G$1" x="294.64" y="96.52" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="VALUE" x="292.735" y="96.52" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="C9" gate="G$1" x="312.42" y="91.44" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="NAME" x="314.96" y="93.98" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="308.356" y="96.52" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="C10" gate="G$1" x="302.26" y="91.44" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="NAME" x="304.8" y="93.98" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="298.196" y="93.98" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="IC6" gate="G$1" x="320.04" y="93.98" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="331.47" y="83.82" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="323.85" y="86.36" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY84" gate="G$1" x="335.28" y="101.6" smashed="yes" rot="R270" grouprefs="POWER">
<attribute name="VALUE" x="333.375" y="101.6" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="C13" gate="G$1" x="345.44" y="101.6" smashed="yes" grouprefs="POWER">
<attribute name="NAME" x="342.9" y="104.14" size="1.778" layer="95"/>
<attribute name="VALUE" x="340.36" y="97.536" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY87" gate="G$1" x="393.7" y="12.7" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="VALUE" x="395.605" y="12.7" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C14" gate="G$1" x="381" y="12.7" smashed="yes" rot="R180" grouprefs="CAMERA">
<attribute name="NAME" x="388.62" y="15.24" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="388.62" y="11.684" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="IC5" gate="G$1" x="162.56" y="50.8" smashed="yes" grouprefs="ESP32">
<attribute name="NAME" x="176.53" y="58.42" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="163.83" y="55.88" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="FRAME2" gate="G$1" x="-7.62" y="-144.78" smashed="yes"/>
<instance part="FRAME2" gate="G$2" x="317.5" y="-144.78" smashed="yes">
<attribute name="LAST_DATE_TIME" x="330.2" y="-143.51" size="2.54" layer="94"/>
<attribute name="SHEET" x="403.86" y="-143.51" size="2.54" layer="94"/>
<attribute name="32_SERVO_CONTROLLER" x="332.74" y="-127" size="1.778" layer="90" display="name"/>
<attribute name="ENDURANCE_RC_LLC" x="342.9" y="-116.84" size="3.81" layer="90"/>
</instance>
<instance part="JP1" gate="G$1" x="198.12" y="106.68" smashed="yes" grouprefs="CONNECTORS">
<attribute name="NAME" x="191.77" y="112.395" size="1.778" layer="95"/>
<attribute name="VALUE" x="203.2" y="102.87" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY91" gate="G$1" x="195.58" y="116.84" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="195.453" y="120.015" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="J3" gate="G$1" x="162.56" y="114.3" smashed="yes" grouprefs="CONNECTORS">
<attribute name="NAME" x="171.45" y="121.92" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="166.37" y="119.38" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="J5" gate="A" x="172.72" y="93.98" smashed="yes" grouprefs="CONNECTORS">
<attribute name="NAME" x="176.8846" y="99.2886" size="2.083" layer="95" ratio="6"/>
</instance>
<instance part="C12" gate="G$1" x="60.96" y="30.48" smashed="yes" rot="R90" grouprefs="MICRO_SD">
<attribute name="NAME" x="58.42" y="27.94" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="65.024" y="27.94" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY80" gate="G$1" x="60.96" y="20.32" smashed="yes" grouprefs="MICRO_SD">
<attribute name="VALUE" x="60.96" y="18.415" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY94" gate="G$1" x="284.48" y="99.06" smashed="yes" grouprefs="POWER">
<attribute name="VALUE" x="284.48" y="97.155" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY95" gate="G$1" x="368.3" y="99.06" smashed="yes" grouprefs="TFT_DISPLAY">
<attribute name="VALUE" x="368.3" y="97.155" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY101" gate="G$1" x="17.78" y="101.6" smashed="yes" grouprefs="BUTTONS">
<attribute name="VALUE" x="17.78" y="99.695" size="1.778" layer="96" align="center"/>
</instance>
<instance part="J6" gate="G$1" x="5.08" y="40.64" smashed="yes" grouprefs="MICRO_SD">
<attribute name="NAME" x="21.59" y="48.26" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="11.43" y="45.72" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="J2" gate="G$1" x="127" y="96.52" smashed="yes" grouprefs="CONNECTORS">
<attribute name="NAME" x="127" y="120.142" size="1.778" layer="95"/>
<attribute name="VALUE" x="119.38" y="72.898" size="1.778" layer="96" align="top-left"/>
</instance>
<instance part="SUPPLY117" gate="G$1" x="106.68" y="91.44" smashed="yes" rot="R90" grouprefs="BUTTONS">
<attribute name="VALUE" x="108.585" y="91.44" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY118" gate="G$1" x="53.34" y="81.28" smashed="yes" grouprefs="BUTTONS">
<attribute name="VALUE" x="53.34" y="79.375" size="1.778" layer="96" align="center"/>
</instance>
<instance part="IC7" gate="G$1" x="55.88" y="101.6" smashed="yes" grouprefs="BUTTONS">
<attribute name="NAME" x="69.85" y="121.92" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="62.23" y="119.38" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY111" gate="G$1" x="162.56" y="106.68" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="162.56" y="104.775" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY112" gate="G$1" x="182.88" y="106.68" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="182.88" y="104.775" size="1.778" layer="96" align="center"/>
</instance>
<instance part="IC1" gate="G$1" x="236.22" y="30.48" smashed="yes" grouprefs="IMU">
<attribute name="NAME" x="278.13" y="48.26" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="275.59" y="45.72" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="C17" gate="G$1" x="228.6" y="27.94" smashed="yes" rot="R270" grouprefs="IMU">
<attribute name="NAME" x="231.14" y="30.48" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="224.536" y="30.48" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="SUPPLY113" gate="G$1" x="228.6" y="40.64" smashed="yes" rot="R180" grouprefs="IMU">
<attribute name="VALUE" x="228.6" y="42.545" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY114" gate="G$1" x="269.24" y="48.26" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="VALUE" x="271.145" y="48.26" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY115" gate="G$1" x="294.64" y="17.78" smashed="yes" grouprefs="IMU">
<attribute name="VALUE" x="294.64" y="15.875" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C18" gate="G$1" x="292.1" y="53.34" smashed="yes" rot="R180" grouprefs="IMU">
<attribute name="NAME" x="294.64" y="50.8" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="294.64" y="57.404" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY116" gate="G$1" x="302.26" y="53.34" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="VALUE" x="304.165" y="53.34" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C20" gate="G$1" x="302.26" y="22.86" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="NAME" x="302.26" y="15.24" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="307.34" y="15.24" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY119" gate="G$1" x="312.42" y="22.86" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="VALUE" x="314.325" y="22.86" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C21" gate="G$1" x="302.26" y="35.56" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="NAME" x="302.26" y="38.1" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="307.34" y="38.1" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY120" gate="G$1" x="312.42" y="35.56" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="VALUE" x="314.325" y="35.56" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY121" gate="G$1" x="226.06" y="20.32" smashed="yes" rot="R270" grouprefs="IMU">
<attribute name="VALUE" x="224.155" y="20.32" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="C19" gate="G$1" x="297.18" y="22.86" smashed="yes" rot="R90" grouprefs="IMU">
<attribute name="NAME" x="293.37" y="26.67" size="1.778" layer="95" rot="R90" align="center-left"/>
<attribute name="VALUE" x="300.99" y="29.21" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY122" gate="G$1" x="248.92" y="48.26" smashed="yes" rot="R270" grouprefs="IMU">
<attribute name="VALUE" x="247.015" y="48.26" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="SUPPLY93" gate="G$1" x="5.08" y="12.7" smashed="yes" grouprefs="MICRO_SD">
<attribute name="VALUE" x="5.08" y="10.795" size="1.778" layer="96" align="center"/>
</instance>
<instance part="U$33" gate="G$1" x="393.7" y="104.14" smashed="yes" grouprefs="TFT_DISPLAY"/>
<instance part="S1" gate="G$1" x="22.86" y="88.9" smashed="yes" rot="R180" grouprefs="BUTTONS">
<attribute name="NAME" x="13.97" y="81.28" size="1.778" layer="95" rot="R180" align="center-left"/>
<attribute name="VALUE" x="19.05" y="83.82" size="1.778" layer="96" rot="R180" align="center-left"/>
</instance>
<instance part="S2" gate="G$1" x="22.86" y="71.12" smashed="yes" rot="R180" grouprefs="BUTTONS">
<attribute name="NAME" x="13.97" y="63.5" size="1.778" layer="95" rot="R180" align="center-left"/>
<attribute name="VALUE" x="19.05" y="66.04" size="1.778" layer="96" rot="R180" align="center-left"/>
</instance>
<instance part="S3" gate="G$1" x="20.32" y="116.84" smashed="yes" grouprefs="BUTTONS">
<attribute name="NAME" x="29.21" y="121.92" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="24.13" y="101.6" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="J7" gate="G$1" x="337.82" y="63.5" smashed="yes" grouprefs="CAMERA">
<attribute name="NAME" x="349.25" y="71.12" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="341.63" y="68.58" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY124" gate="G$1" x="335.28" y="55.88" smashed="yes" grouprefs="CAMERA">
<attribute name="VALUE" x="335.28" y="53.975" size="1.778" layer="96" align="center"/>
</instance>
<instance part="RN1" gate="G$1" x="375.92" y="-17.78" smashed="yes" grouprefs="RESISTORS">
<attribute name="NAME" x="382.27" y="-20.32" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="377.19" y="-12.7" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="IC10" gate="G$1" x="139.7" y="-208.28" smashed="yes" grouprefs="SERVO_DRIVER">
<attribute name="NAME" x="148.59" y="-182.88" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="161.29" y="-182.88" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY127" gate="G$1" x="43.18" y="101.6" smashed="yes" grouprefs="BUTTONS">
<attribute name="VALUE" x="43.18" y="99.695" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY5" gate="G$1" x="401.32" y="45.72" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="VALUE" x="403.225" y="45.72" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C3" gate="G$1" x="391.16" y="45.72" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="NAME" x="390.525" y="46.736" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="395.351" y="46.736" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY8" gate="G$1" x="401.32" y="40.64" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="VALUE" x="403.225" y="40.64" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="C5" gate="G$1" x="391.16" y="30.48" smashed="yes" rot="R180" grouprefs="CAMERA">
<attribute name="NAME" x="393.7" y="27.94" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="393.7" y="34.544" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY38" gate="G$1" x="401.32" y="30.48" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="VALUE" x="403.225" y="30.48" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="R1" gate="G$1" x="391.16" y="22.86" smashed="yes" grouprefs="CAMERA">
<attribute name="NAME" x="388.62" y="20.32" size="1.778" layer="95" align="center"/>
<attribute name="VALUE" x="393.7" y="20.32" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY39" gate="G$1" x="401.32" y="22.86" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="VALUE" x="403.225" y="22.86" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY68" gate="G$1" x="401.32" y="7.62" smashed="yes" rot="R90" grouprefs="CAMERA">
<attribute name="VALUE" x="403.225" y="7.62" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY75" gate="G$1" x="114.3" y="-218.44" smashed="yes" rot="R270" grouprefs="SERVO_DRIVER">
<attribute name="VALUE" x="112.395" y="-218.44" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="SUPPLY77" gate="G$1" x="129.54" y="-228.6" smashed="yes" grouprefs="SERVO_DRIVER">
<attribute name="VALUE" x="129.54" y="-230.505" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C11" gate="G$1" x="127" y="-223.52" smashed="yes" rot="R90" grouprefs="SERVO_DRIVER">
<attribute name="NAME" x="119.38" y="-226.06" size="1.778" layer="95"/>
<attribute name="VALUE" x="119.38" y="-227.584" size="1.778" layer="96"/>
</instance>
<instance part="C15" gate="G$1" x="127" y="-210.82" smashed="yes" rot="R180" grouprefs="SERVO_DRIVER">
<attribute name="NAME" x="124.46" y="-210.82" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="124.46" y="-205.74" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY78" gate="G$1" x="127" y="-236.22" smashed="yes" grouprefs="SERVO_DRIVER">
<attribute name="VALUE" x="127" y="-238.125" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY79" gate="G$1" x="127" y="-200.66" smashed="yes" rot="R180" grouprefs="SERVO_DRIVER">
<attribute name="VALUE" x="127" y="-198.755" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="JP2" gate="A" x="139.7" y="-193.04" smashed="yes" grouprefs="SERVO_DRIVER">
<attribute name="NAME" x="133.35" y="-184.785" size="1.778" layer="95"/>
</instance>
<instance part="SUPPLY83" gate="G$1" x="119.38" y="-195.58" smashed="yes" rot="R270" grouprefs="SERVO_DRIVER">
<attribute name="VALUE" x="117.475" y="-195.58" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="RN2" gate="G$1" x="375.92" y="-33.02" smashed="yes" grouprefs="RESISTORS">
<attribute name="NAME" x="382.27" y="-35.56" size="1.778" layer="95" align="center-left"/>
</instance>
<instance part="RN3" gate="G$1" x="375.92" y="-48.26" smashed="yes" grouprefs="RESISTORS">
<attribute name="NAME" x="382.27" y="-50.8" size="1.778" layer="95" align="center-left"/>
</instance>
<instance part="RN4" gate="G$1" x="375.92" y="-63.5" smashed="yes" grouprefs="RESISTORS">
<attribute name="NAME" x="382.27" y="-66.04" size="1.778" layer="95" align="center-left"/>
</instance>
<instance part="RN5" gate="G$1" x="375.92" y="-78.74" smashed="yes" grouprefs="RESISTORS">
<attribute name="NAME" x="382.27" y="-81.28" size="1.778" layer="95" align="center-left"/>
</instance>
<instance part="SUPPLY85" gate="G$1" x="411.48" y="-68.58" smashed="yes" rot="R90" grouprefs="RESISTORS">
<attribute name="VALUE" x="413.385" y="-68.58" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY86" gate="G$1" x="170.18" y="81.28" smashed="yes" grouprefs="CONNECTORS">
<attribute name="VALUE" x="170.18" y="79.375" size="1.778" layer="96" align="center"/>
</instance>
<instance part="IC3" gate="G$1" x="27.94" y="-190.5" smashed="yes" grouprefs="GNSS">
<attribute name="NAME" x="54.61" y="-182.88" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="49.53" y="-185.42" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY88" gate="G$1" x="17.78" y="-200.66" smashed="yes" rot="R270" grouprefs="GNSS">
<attribute name="VALUE" x="15.875" y="-200.66" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="SUPPLY89" gate="G$1" x="17.78" y="-218.44" smashed="yes" rot="R270" grouprefs="GNSS">
<attribute name="VALUE" x="15.875" y="-218.44" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="SUPPLY92" gate="G$1" x="91.44" y="-226.06" smashed="yes" rot="R90" grouprefs="GNSS">
<attribute name="VALUE" x="93.345" y="-226.06" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="RN6" gate="G$1" x="375.92" y="-93.98" smashed="yes" grouprefs="RESISTORS">
<attribute name="NAME" x="382.27" y="-96.52" size="1.778" layer="95" align="center-left"/>
</instance>
<instance part="IC2" gate="G$1" x="119.38" y="-96.52" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="138.43" y="-58.42" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="130.81" y="-60.96" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="J4" gate="G$1" x="218.44" y="88.9" smashed="yes" grouprefs="CONNECTORS">
<attribute name="NAME" x="214.63" y="95.25" size="1.778" layer="95"/>
<attribute name="VALUE" x="204.216" y="78.486" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY97" gate="G$1" x="114.3" y="-101.6" smashed="yes" rot="R270" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="112.395" y="-101.6" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="C16" gate="G$1" x="157.48" y="-127" smashed="yes" rot="R90" grouprefs="AMP_SOUND">
<attribute name="NAME" x="154.94" y="-129.54" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="161.544" y="-132.08" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="C22" gate="G$1" x="147.32" y="-127" smashed="yes" rot="R90" grouprefs="AMP_SOUND">
<attribute name="NAME" x="144.78" y="-129.54" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="151.384" y="-132.08" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY99" gate="G$1" x="139.7" y="-66.04" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="139.7" y="-64.135" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY100" gate="G$1" x="162.56" y="-91.44" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="162.56" y="-89.535" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY102" gate="G$1" x="147.32" y="-137.16" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="147.32" y="-139.065" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C23" gate="G$1" x="175.26" y="-109.22" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="180.34" y="-106.68" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="182.88" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="C24" gate="G$1" x="175.26" y="-93.98" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="NAME" x="170.18" y="-91.44" size="1.778" layer="95"/>
<attribute name="VALUE" x="167.64" y="-96.52" size="1.778" layer="96"/>
</instance>
<instance part="R2" gate="G$1" x="116.84" y="-114.3" smashed="yes" rot="R90" grouprefs="AMP_SOUND">
<attribute name="NAME" x="114.0714" y="-114.3" size="1.778" layer="95" rot="R90" align="center"/>
<attribute name="VALUE" x="120.142" y="-114.3" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY104" gate="G$1" x="175.26" y="-83.82" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="175.26" y="-81.915" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY105" gate="G$1" x="175.26" y="-119.38" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="175.26" y="-121.285" size="1.778" layer="96" align="center"/>
</instance>
<instance part="FB1" gate="G$1" x="167.64" y="-101.6" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="167.64" y="-98.8314" size="1.778" layer="95" align="center"/>
</instance>
<instance part="FB2" gate="G$1" x="167.64" y="-104.14" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="167.64" y="-106.4514" size="1.778" layer="95" align="center"/>
</instance>
<instance part="IC8" gate="G$1" x="208.28" y="-96.52" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="227.33" y="-58.42" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="219.71" y="-60.96" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="SUPPLY106" gate="G$1" x="203.2" y="-101.6" smashed="yes" rot="R270" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="201.295" y="-101.6" size="1.778" layer="96" rot="R270" align="center"/>
</instance>
<instance part="C25" gate="G$1" x="246.38" y="-127" smashed="yes" rot="R90" grouprefs="AMP_SOUND">
<attribute name="NAME" x="243.84" y="-129.54" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="250.444" y="-132.08" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="C26" gate="G$1" x="236.22" y="-127" smashed="yes" rot="R90" grouprefs="AMP_SOUND">
<attribute name="NAME" x="233.68" y="-129.54" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="240.284" y="-132.08" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY107" gate="G$1" x="228.6" y="-66.04" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="228.6" y="-64.135" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY108" gate="G$1" x="251.46" y="-91.44" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="251.46" y="-89.535" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY109" gate="G$1" x="236.22" y="-137.16" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="236.22" y="-139.065" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C27" gate="G$1" x="264.16" y="-109.22" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="269.24" y="-106.68" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="271.78" y="-111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="C28" gate="G$1" x="264.16" y="-93.98" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="NAME" x="259.08" y="-91.44" size="1.778" layer="95"/>
<attribute name="VALUE" x="256.54" y="-96.52" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY123" gate="G$1" x="264.16" y="-83.82" smashed="yes" rot="R180" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="264.16" y="-81.915" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="SUPPLY125" gate="G$1" x="264.16" y="-119.38" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="VALUE" x="264.16" y="-121.285" size="1.778" layer="96" align="center"/>
</instance>
<instance part="FB3" gate="G$1" x="256.54" y="-101.6" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="256.54" y="-98.8314" size="1.778" layer="95" align="center"/>
</instance>
<instance part="FB4" gate="G$1" x="256.54" y="-104.14" smashed="yes" grouprefs="AMP_SOUND">
<attribute name="NAME" x="256.54" y="-106.4514" size="1.778" layer="95" align="center"/>
</instance>
<instance part="SUPPLY110" gate="G$1" x="116.84" y="15.24" smashed="yes" rot="R90" grouprefs="MIC">
<attribute name="VALUE" x="118.745" y="15.24" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="MK1" gate="G$1" x="93.98" y="22.86" smashed="yes" grouprefs="MIC">
<attribute name="NAME" x="81.28" y="34.29" size="1.778" layer="95"/>
<attribute name="VALUE" x="81.28" y="11.43" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="SUPPLY126" gate="G$1" x="76.2" y="17.78" smashed="yes" grouprefs="MIC">
<attribute name="VALUE" x="76.2" y="15.875" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C29" gate="G$1" x="114.3" y="35.56" smashed="yes" rot="R270" grouprefs="MIC">
<attribute name="NAME" x="116.84" y="38.1" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="110.236" y="38.1" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="SUPPLY103" gate="G$1" x="114.3" y="45.72" smashed="yes" rot="R180" grouprefs="MIC">
<attribute name="VALUE" x="114.3" y="47.625" size="1.778" layer="96" rot="R180" align="center"/>
</instance>
<instance part="R3" gate="G$1" x="127" y="15.24" smashed="yes" rot="R90" grouprefs="MIC">
<attribute name="NAME" x="124.46" y="15.24" size="1.778" layer="95" rot="R90" align="center"/>
<attribute name="VALUE" x="129.54" y="15.24" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="SUPPLY128" gate="G$1" x="127" y="5.08" smashed="yes" grouprefs="MIC">
<attribute name="VALUE" x="127" y="3.175" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY96" gate="G$1" x="401.32" y="-96.52" smashed="yes" rot="R90">
<attribute name="VALUE" x="403.225" y="-96.52" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="FRAME1" gate="G$1" x="-7.62" y="-444.5" smashed="yes"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="U$15" gate="G$1" pin="1"/>
<wire x1="17.78" y1="-30.48" x2="17.78" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY15" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="30.48" y1="-30.48" x2="30.48" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY14" gate="G$1" pin="GND"/>
<pinref part="U$14" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="U$11" gate="G$1" pin="1"/>
<wire x1="43.18" y1="-30.48" x2="43.18" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY13" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$12" gate="G$1" pin="1"/>
<wire x1="55.88" y1="-30.48" x2="55.88" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY12" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$13" gate="G$1" pin="1"/>
<wire x1="5.08" y1="-30.48" x2="5.08" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY7" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="1"/>
<wire x1="68.58" y1="-30.48" x2="68.58" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY35" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="1"/>
<wire x1="81.28" y1="-30.48" x2="81.28" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY34" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="1"/>
<wire x1="93.98" y1="-30.48" x2="93.98" y2="-35.56" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY33" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="1"/>
<wire x1="5.08" y1="-60.96" x2="5.08" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY32" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$5" gate="G$1" pin="1"/>
<wire x1="17.78" y1="-60.96" x2="17.78" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY31" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$6" gate="G$1" pin="1"/>
<wire x1="30.48" y1="-60.96" x2="30.48" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY30" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY29" gate="G$1" pin="GND"/>
<wire x1="43.18" y1="-66.04" x2="43.18" y2="-60.96" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$7" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="1"/>
<wire x1="55.88" y1="-60.96" x2="55.88" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY28" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY27" gate="G$1" pin="GND"/>
<wire x1="68.58" y1="-66.04" x2="68.58" y2="-60.96" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$9" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY26" gate="G$1" pin="GND"/>
<wire x1="81.28" y1="-66.04" x2="81.28" y2="-60.96" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$10" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY24" gate="G$1" pin="GND"/>
<wire x1="93.98" y1="-66.04" x2="93.98" y2="-60.96" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$16" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY23" gate="G$1" pin="GND"/>
<wire x1="5.08" y1="-96.52" x2="5.08" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$17" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY22" gate="G$1" pin="GND"/>
<wire x1="17.78" y1="-96.52" x2="17.78" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$18" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY21" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-96.52" x2="30.48" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$19" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY20" gate="G$1" pin="GND"/>
<wire x1="43.18" y1="-96.52" x2="43.18" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$21" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="U$20" gate="G$1" pin="1"/>
<wire x1="55.88" y1="-91.44" x2="55.88" y2="-93.98" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY25" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY19" gate="G$1" pin="GND"/>
<wire x1="68.58" y1="-93.98" x2="68.58" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$22" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY18" gate="G$1" pin="GND"/>
<wire x1="81.28" y1="-93.98" x2="81.28" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$23" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY17" gate="G$1" pin="GND"/>
<wire x1="93.98" y1="-93.98" x2="93.98" y2="-91.44" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$24" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY16" gate="G$1" pin="GND"/>
<wire x1="5.08" y1="-124.46" x2="5.08" y2="-121.92" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$25" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="208.28" y1="104.14" x2="208.28" y2="106.68" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J1" gate="G$1" pin="2"/>
<pinref part="SUPPLY11" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="241.3" y1="101.6" x2="243.84" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="SUPPLY1" gate="G$1" pin="GND"/>
<pinref part="C7" gate="G$1" pin="2"/>
<wire x1="246.38" y1="96.52" x2="243.84" y2="96.52" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="243.84" y1="86.36" x2="243.84" y2="96.52" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="243.84" y1="96.52" x2="243.84" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="246.38" y1="106.68" x2="243.84" y2="106.68" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="243.84" y1="106.68" x2="243.84" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C1" gate="G$1" pin="2"/>
<wire x1="243.84" y1="86.36" x2="246.38" y2="86.36" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C2" gate="G$1" pin="2"/>
<wire x1="243.84" y1="106.68" x2="243.84" y2="116.84" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="243.84" y1="116.84" x2="246.38" y2="116.84" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C4" gate="G$1" pin="2"/>
<wire x1="243.84" y1="101.6" x2="254" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="PS1" gate="G$1" pin="GND_1"/>
<junction x="243.84" y="101.6" grouprefs="POWER"/>
<junction x="243.84" y="96.52" grouprefs="POWER"/>
<junction x="243.84" y="106.68" grouprefs="POWER"/>
</segment>
<segment>
<pinref part="SUPPLY36" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="50.8" x2="154.94" y2="50.8" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="154.94" y1="50.8" x2="154.94" y2="53.34" width="0.1524" layer="91" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_1"/>
</segment>
<segment>
<pinref part="SUPPLY37" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-7.62" x2="195.58" y2="-7.62" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="-7.62" x2="195.58" y2="-5.08" width="0.1524" layer="91" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_2"/>
<pinref part="IC5" gate="G$1" pin="GND_3"/>
<wire x1="195.58" y1="-5.08" x2="195.58" y2="-2.54" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="-2.54" x2="195.58" y2="0" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="0" x2="195.58" y2="2.54" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="2.54" x2="195.58" y2="5.08" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="5.08" x2="195.58" y2="7.62" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="7.62" x2="195.58" y2="10.16" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="10.16" x2="195.58" y2="12.7" width="0.1524" layer="91" grouprefs="ESP32"/>
<wire x1="195.58" y1="12.7" x2="195.58" y2="15.24" width="0.1524" layer="91" grouprefs="ESP32"/>
<junction x="195.58" y="12.7" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_4"/>
<junction x="195.58" y="10.16" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_5"/>
<junction x="195.58" y="7.62" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_6"/>
<junction x="195.58" y="5.08" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_7"/>
<junction x="195.58" y="2.54" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_8"/>
<junction x="195.58" y="0" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_9"/>
<junction x="195.58" y="-2.54" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_10"/>
<junction x="195.58" y="-5.08" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="GND_11"/>
<junction x="195.58" y="-7.62" grouprefs="ESP32"/>
</segment>
<segment>
<pinref part="U$26" gate="G$1" pin="1"/>
<wire x1="17.78" y1="-121.92" x2="17.78" y2="-124.46" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY40" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$27" gate="G$1" pin="1"/>
<wire x1="30.48" y1="-121.92" x2="30.48" y2="-124.46" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY42" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$28" gate="G$1" pin="1"/>
<wire x1="43.18" y1="-121.92" x2="43.18" y2="-124.46" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY43" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$29" gate="G$1" pin="1"/>
<wire x1="55.88" y1="-121.92" x2="55.88" y2="-124.46" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY44" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$30" gate="G$1" pin="1"/>
<wire x1="68.58" y1="-121.92" x2="68.58" y2="-124.46" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY45" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$31" gate="G$1" pin="1"/>
<wire x1="81.28" y1="-121.92" x2="81.28" y2="-124.46" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY46" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="U$32" gate="G$1" pin="1"/>
<wire x1="93.98" y1="-121.92" x2="93.98" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY69" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC4" gate="G$1" pin="VSS"/>
<wire x1="320.04" y1="111.76" x2="320.04" y2="114.3" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="320.04" y1="114.3" x2="312.42" y2="114.3" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="312.42" y1="114.3" x2="302.26" y2="114.3" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="302.26" y1="114.3" x2="297.18" y2="114.3" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="SUPPLY81" gate="G$1" pin="GND"/>
<pinref part="C6" gate="G$1" pin="2"/>
<pinref part="C8" gate="G$1" pin="2"/>
<junction x="312.42" y="114.3"/>
<junction x="302.26" y="114.3"/>
</segment>
<segment>
<wire x1="320.04" y1="93.98" x2="320.04" y2="96.52" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="320.04" y1="96.52" x2="312.42" y2="96.52" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="SUPPLY82" gate="G$1" pin="GND"/>
<pinref part="IC6" gate="G$1" pin="VSS"/>
<pinref part="C9" gate="G$1" pin="2"/>
<wire x1="312.42" y1="96.52" x2="302.26" y2="96.52" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C10" gate="G$1" pin="2"/>
<wire x1="302.26" y1="96.52" x2="297.18" y2="96.52" width="0.1524" layer="91" grouprefs="POWER"/>
<junction x="312.42" y="96.52"/>
<junction x="302.26" y="96.52"/>
</segment>
<segment>
<pinref part="SUPPLY84" gate="G$1" pin="GND"/>
<wire x1="337.82" y1="101.6" x2="340.36" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C13" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="SUPPLY87" gate="G$1" pin="GND"/>
<wire x1="391.16" y1="12.7" x2="386.08" y2="12.7" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="C14" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="PS1" gate="G$1" pin="GND_2"/>
<wire x1="284.48" y1="104.14" x2="284.48" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="SUPPLY94" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="378.46" y1="101.6" x2="368.3" y2="101.6" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<pinref part="SUPPLY95" gate="G$1" pin="GND"/>
<pinref part="U$33" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="86.36" y1="91.44" x2="104.14" y2="91.44" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="SUPPLY117" gate="G$1" pin="GND"/>
<pinref part="IC7" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="55.88" y1="83.82" x2="53.34" y2="83.82" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="SUPPLY118" gate="G$1" pin="GND"/>
<wire x1="55.88" y1="88.9" x2="53.34" y2="88.9" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="53.34" y1="88.9" x2="53.34" y2="83.82" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="A1"/>
<pinref part="IC7" gate="G$1" pin="A2"/>
<junction x="53.34" y="83.82" grouprefs="BUTTONS"/>
</segment>
<segment>
<pinref part="SUPPLY111" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="109.22" x2="162.56" y2="111.76" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J3" gate="G$1" pin="3"/>
<wire x1="162.56" y1="111.76" x2="162.56" y2="114.3" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J3" gate="G$1" pin="2"/>
<junction x="162.56" y="111.76" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="SUPPLY112" gate="G$1" pin="GND"/>
<wire x1="182.88" y1="109.22" x2="182.88" y2="111.76" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J3" gate="G$1" pin="5"/>
<wire x1="182.88" y1="111.76" x2="182.88" y2="114.3" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<junction x="182.88" y="111.76" grouprefs="CONNECTORS"/>
<pinref part="J3" gate="G$1" pin="4"/>
</segment>
<segment>
<wire x1="40.64" y1="27.94" x2="55.88" y2="27.94" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<wire x1="55.88" y1="27.94" x2="55.88" y2="25.4" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<pinref part="J6" gate="G$1" pin="VSS"/>
<wire x1="55.88" y1="25.4" x2="60.96" y2="25.4" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<pinref part="C12" gate="G$1" pin="2"/>
<wire x1="60.96" y1="25.4" x2="60.96" y2="22.86" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<pinref part="SUPPLY80" gate="G$1" pin="GND"/>
<junction x="60.96" y="25.4"/>
</segment>
<segment>
<pinref part="SUPPLY113" gate="G$1" pin="GND"/>
<wire x1="228.6" y1="38.1" x2="228.6" y2="33.02" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="C17" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="GND_1"/>
<wire x1="264.16" y1="48.26" x2="266.7" y2="48.26" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="SUPPLY114" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="GND_2"/>
<wire x1="287.02" y1="20.32" x2="294.64" y2="20.32" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="SUPPLY115" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY116" gate="G$1" pin="GND"/>
<wire x1="299.72" y1="53.34" x2="297.18" y2="53.34" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="C18" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="C21" gate="G$1" pin="2"/>
<wire x1="307.34" y1="35.56" x2="309.88" y2="35.56" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="SUPPLY120" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="C20" gate="G$1" pin="2"/>
<wire x1="307.34" y1="22.86" x2="309.88" y2="22.86" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="SUPPLY119" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY121" gate="G$1" pin="GND"/>
<wire x1="228.6" y1="20.32" x2="236.22" y2="20.32" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="IC1" gate="G$1" pin="CLKSEL0"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="PS1"/>
<wire x1="256.54" y1="48.26" x2="251.46" y2="48.26" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="SUPPLY122" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY93" gate="G$1" pin="GND"/>
<pinref part="J6" gate="G$1" pin="GND_2"/>
<wire x1="5.08" y1="38.1" x2="5.08" y2="35.56" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="GND_4"/>
<wire x1="5.08" y1="35.56" x2="5.08" y2="33.02" width="0.1524" layer="91"/>
<wire x1="5.08" y1="33.02" x2="5.08" y2="30.48" width="0.1524" layer="91"/>
<wire x1="5.08" y1="30.48" x2="5.08" y2="27.94" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="GND_6"/>
<wire x1="5.08" y1="27.94" x2="5.08" y2="25.4" width="0.1524" layer="91"/>
<wire x1="5.08" y1="25.4" x2="5.08" y2="22.86" width="0.1524" layer="91"/>
<wire x1="5.08" y1="22.86" x2="5.08" y2="20.32" width="0.1524" layer="91"/>
<wire x1="5.08" y1="20.32" x2="5.08" y2="17.78" width="0.1524" layer="91"/>
<wire x1="5.08" y1="17.78" x2="5.08" y2="15.24" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="GND_8"/>
<pinref part="J6" gate="G$1" pin="GND_7"/>
<pinref part="J6" gate="G$1" pin="GND_5"/>
<pinref part="J6" gate="G$1" pin="GND_9"/>
<pinref part="J6" gate="G$1" pin="GND_3"/>
<wire x1="5.08" y1="38.1" x2="5.08" y2="40.64" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="GND_1"/>
<pinref part="J6" gate="G$1" pin="GND_10"/>
<junction x="5.08" y="38.1"/>
<junction x="5.08" y="35.56"/>
<junction x="5.08" y="33.02"/>
<junction x="5.08" y="30.48"/>
<junction x="5.08" y="27.94"/>
<junction x="5.08" y="25.4"/>
<junction x="5.08" y="22.86"/>
<junction x="5.08" y="20.32"/>
<junction x="5.08" y="17.78"/>
</segment>
<segment>
<wire x1="22.86" y1="91.44" x2="33.02" y2="91.44" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="SUPPLY90" gate="G$1" pin="GND"/>
<pinref part="S1" gate="G$1" pin="K"/>
</segment>
<segment>
<pinref part="SUPPLY2" gate="G$1" pin="GND"/>
<wire x1="22.86" y1="73.66" x2="33.02" y2="73.66" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="S2" gate="G$1" pin="K"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="MP2"/>
<wire x1="337.82" y1="60.96" x2="335.28" y2="60.96" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="335.28" y1="60.96" x2="335.28" y2="63.5" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="335.28" y1="63.5" x2="337.82" y2="63.5" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="J7" gate="G$1" pin="MP1"/>
<wire x1="335.28" y1="60.96" x2="335.28" y2="58.42" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="SUPPLY124" gate="G$1" pin="GND"/>
<junction x="335.28" y="60.96"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="E"/>
<wire x1="20.32" y1="106.68" x2="17.78" y2="106.68" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="17.78" y1="106.68" x2="17.78" y2="104.14" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="SUPPLY101" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="K"/>
<wire x1="40.64" y1="106.68" x2="43.18" y2="106.68" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="SUPPLY127" gate="G$1" pin="GND"/>
<pinref part="S3" gate="G$1" pin="G"/>
<wire x1="40.64" y1="111.76" x2="43.18" y2="111.76" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="40.64" y1="114.3" x2="43.18" y2="114.3" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="43.18" y1="114.3" x2="43.18" y2="109.22" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="S3" gate="G$1" pin="H"/>
<wire x1="43.18" y1="109.22" x2="43.18" y2="106.68" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="43.18" y1="106.68" x2="43.18" y2="104.14" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<pinref part="S3" gate="G$1" pin="J"/>
<wire x1="40.64" y1="109.22" x2="43.18" y2="109.22" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<junction x="43.18" y="106.68"/>
<junction x="43.18" y="109.22"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="10"/>
<wire x1="363.22" y1="40.64" x2="398.78" y2="40.64" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="SUPPLY8" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="396.24" y1="30.48" x2="398.78" y2="30.48" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="C5" gate="G$1" pin="2"/>
<pinref part="SUPPLY38" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="396.24" y1="22.86" x2="398.78" y2="22.86" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="SUPPLY39" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY68" gate="G$1" pin="GND"/>
<wire x1="398.78" y1="7.62" x2="363.22" y2="7.62" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="J7" gate="G$1" pin="23"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="VREF+"/>
<wire x1="139.7" y1="-218.44" x2="116.84" y2="-218.44" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<pinref part="SUPPLY75" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="VSS/VSSA"/>
<wire x1="139.7" y1="-223.52" x2="129.54" y2="-223.52" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<wire x1="129.54" y1="-223.52" x2="129.54" y2="-226.06" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<pinref part="SUPPLY77" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="C11" gate="G$1" pin="2"/>
<wire x1="127" y1="-228.6" x2="127" y2="-233.68" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<pinref part="SUPPLY78" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="C15" gate="G$1" pin="2"/>
<pinref part="SUPPLY79" gate="G$1" pin="GND"/>
<wire x1="127" y1="-205.74" x2="127" y2="-203.2" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
</segment>
<segment>
<pinref part="SUPPLY83" gate="G$1" pin="GND"/>
<wire x1="137.16" y1="-195.58" x2="121.92" y2="-195.58" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<pinref part="JP2" gate="A" pin="4"/>
</segment>
<segment>
<pinref part="J5" gate="A" pin="4"/>
<wire x1="172.72" y1="86.36" x2="170.18" y2="86.36" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<wire x1="170.18" y1="86.36" x2="170.18" y2="83.82" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="SUPPLY86" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="GND_2"/>
<wire x1="27.94" y1="-200.66" x2="25.4" y2="-200.66" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="SUPPLY88" gate="G$1" pin="GND"/>
<pinref part="IC3" gate="G$1" pin="GND_1"/>
<wire x1="25.4" y1="-200.66" x2="20.32" y2="-200.66" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="27.94" y1="-198.12" x2="25.4" y2="-198.12" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-198.12" x2="25.4" y2="-200.66" width="0.1524" layer="91" grouprefs="GNSS"/>
<junction x="25.4" y="-200.66"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="GND_8"/>
<wire x1="27.94" y1="-226.06" x2="25.4" y2="-226.06" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-226.06" x2="25.4" y2="-223.52" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_7"/>
<wire x1="27.94" y1="-223.52" x2="25.4" y2="-223.52" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-223.52" x2="25.4" y2="-220.98" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_6"/>
<wire x1="27.94" y1="-220.98" x2="25.4" y2="-220.98" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-220.98" x2="25.4" y2="-218.44" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_5"/>
<wire x1="27.94" y1="-218.44" x2="25.4" y2="-218.44" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-218.44" x2="25.4" y2="-215.9" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_4"/>
<wire x1="27.94" y1="-215.9" x2="25.4" y2="-215.9" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-215.9" x2="25.4" y2="-213.36" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_3"/>
<wire x1="27.94" y1="-213.36" x2="25.4" y2="-213.36" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-218.44" x2="20.32" y2="-218.44" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="SUPPLY89" gate="G$1" pin="GND"/>
<junction x="25.4" y="-223.52"/>
<junction x="25.4" y="-220.98"/>
<junction x="25.4" y="-218.44"/>
<junction x="25.4" y="-215.9"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="GND_9"/>
<wire x1="81.28" y1="-193.04" x2="83.82" y2="-193.04" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="83.82" y1="-193.04" x2="83.82" y2="-195.58" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_10"/>
<wire x1="81.28" y1="-195.58" x2="83.82" y2="-195.58" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="83.82" y1="-195.58" x2="83.82" y2="-200.66" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_11"/>
<wire x1="81.28" y1="-200.66" x2="83.82" y2="-200.66" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="83.82" y1="-200.66" x2="83.82" y2="-203.2" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_12"/>
<wire x1="81.28" y1="-203.2" x2="83.82" y2="-203.2" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="83.82" y1="-203.2" x2="83.82" y2="-215.9" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_13"/>
<wire x1="81.28" y1="-215.9" x2="83.82" y2="-215.9" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="83.82" y1="-215.9" x2="83.82" y2="-226.06" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="GND_14"/>
<wire x1="81.28" y1="-226.06" x2="83.82" y2="-226.06" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="83.82" y1="-226.06" x2="88.9" y2="-226.06" width="0.1524" layer="91" grouprefs="GNSS"/>
<pinref part="SUPPLY92" gate="G$1" pin="GND"/>
<junction x="83.82" y="-195.58"/>
<junction x="83.82" y="-200.66"/>
<junction x="83.82" y="-203.2"/>
<junction x="83.82" y="-215.9"/>
<junction x="83.82" y="-226.06"/>
</segment>
<segment>
<pinref part="SUPPLY98" gate="G$1" pin="GND"/>
<pinref part="J2" gate="G$1" pin="GND"/>
<pinref part="J2" gate="G$1" pin="SHIELD"/>
<wire x1="144.78" y1="81.28" x2="139.7" y2="81.28" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<wire x1="139.7" y1="76.2" x2="144.78" y2="76.2" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<wire x1="144.78" y1="76.2" x2="144.78" y2="81.28" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<junction x="144.78" y="81.28"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="GND_2"/>
<wire x1="160.02" y1="-99.06" x2="162.56" y2="-99.06" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="162.56" y1="-99.06" x2="162.56" y2="-93.98" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY100" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="GND_3"/>
<wire x1="139.7" y1="-71.12" x2="139.7" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY99" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="GND_1"/>
<wire x1="119.38" y1="-101.6" x2="116.84" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY97" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY102" gate="G$1" pin="GND"/>
<wire x1="147.32" y1="-134.62" x2="147.32" y2="-132.08" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C22" gate="G$1" pin="2"/>
<wire x1="147.32" y1="-132.08" x2="157.48" y2="-132.08" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="147.32" y="-132.08" grouprefs="AMP_SOUND"/>
<pinref part="C16" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="C24" gate="G$1" pin="2"/>
<wire x1="175.26" y1="-88.9" x2="175.26" y2="-86.36" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY104" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY105" gate="G$1" pin="GND"/>
<wire x1="175.26" y1="-116.84" x2="175.26" y2="-114.3" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C23" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="GND_2"/>
<wire x1="248.92" y1="-99.06" x2="251.46" y2="-99.06" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="251.46" y1="-99.06" x2="251.46" y2="-93.98" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY108" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="GND_3"/>
<wire x1="228.6" y1="-71.12" x2="228.6" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY107" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="GND_1"/>
<wire x1="208.28" y1="-101.6" x2="205.74" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY106" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY109" gate="G$1" pin="GND"/>
<wire x1="236.22" y1="-134.62" x2="236.22" y2="-132.08" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C26" gate="G$1" pin="2"/>
<wire x1="236.22" y1="-132.08" x2="246.38" y2="-132.08" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="236.22" y="-132.08" grouprefs="AMP_SOUND"/>
<pinref part="C25" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="C28" gate="G$1" pin="2"/>
<wire x1="264.16" y1="-88.9" x2="264.16" y2="-86.36" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="SUPPLY123" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY125" gate="G$1" pin="GND"/>
<wire x1="264.16" y1="-116.84" x2="264.16" y2="-114.3" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C27" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="SUPPLY110" gate="G$1" pin="GND"/>
<wire x1="114.3" y1="15.24" x2="111.76" y2="15.24" width="0.1524" layer="91" grouprefs="MIC"/>
<pinref part="MK1" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="MK1" gate="G$1" pin="LR"/>
<wire x1="76.2" y1="25.4" x2="76.2" y2="20.32" width="0.1524" layer="91" grouprefs="MIC"/>
<pinref part="SUPPLY126" gate="G$1" pin="GND"/>
<pinref part="MK1" gate="G$1" pin="CONFIG"/>
<junction x="76.2" y="20.32"/>
</segment>
<segment>
<pinref part="C29" gate="G$1" pin="2"/>
<wire x1="114.3" y1="40.64" x2="114.3" y2="43.18" width="0.1524" layer="91" grouprefs="MIC"/>
<pinref part="SUPPLY103" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY128" gate="G$1" pin="GND"/>
<wire x1="127" y1="7.62" x2="127" y2="10.16" width="0.1524" layer="91" grouprefs="MIC"/>
<pinref part="R3" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="398.78" y1="45.72" x2="396.24" y2="45.72" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="SUPPLY5" gate="G$1" pin="GND"/>
<pinref part="C3" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="SUPPLY85" gate="G$1" pin="GND"/>
<wire x1="408.94" y1="-68.58" x2="396.24" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="RN4" gate="G$1" pin="6"/>
</segment>
<segment>
<pinref part="RN6" gate="G$1" pin="7"/>
<wire x1="398.78" y1="-96.52" x2="396.24" y2="-96.52" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<wire x1="398.78" y1="-96.52" x2="398.78" y2="-99.06" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<pinref part="RN6" gate="G$1" pin="6"/>
<wire x1="396.24" y1="-99.06" x2="398.78" y2="-99.06" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<pinref part="SUPPLY96" gate="G$1" pin="GND"/>
<junction x="398.78" y="-96.52"/>
</segment>
</net>
<net name="S9" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="3"/>
<wire x1="10.16" y1="-60.96" x2="10.16" y2="-68.58" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="10.16" y="-68.58" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA15"/>
<wire x1="180.34" y1="-193.04" x2="180.34" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="180.34" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S10" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="3"/>
<wire x1="22.86" y1="-60.96" x2="22.86" y2="-68.58" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="22.86" y="-68.58" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PD0"/>
<wire x1="177.8" y1="-193.04" x2="177.8" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="177.8" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S11" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="3"/>
<wire x1="35.56" y1="-60.96" x2="35.56" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="35.56" y="-66.04" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PD1"/>
<wire x1="175.26" y1="-193.04" x2="175.26" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="175.26" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S8" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="3"/>
<wire x1="99.06" y1="-30.48" x2="99.06" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="99.06" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA10"/>
<wire x1="190.5" y1="-218.44" x2="193.04" y2="-218.44" width="0.1524" layer="91"/>
<label x="193.04" y="-218.44" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S12" class="0">
<segment>
<pinref part="U$7" gate="G$1" pin="3"/>
<wire x1="48.26" y1="-60.96" x2="48.26" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="48.26" y="-66.04" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PD2"/>
<wire x1="172.72" y1="-193.04" x2="172.72" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="172.72" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S13" class="0">
<segment>
<pinref part="U$8" gate="G$1" pin="3"/>
<wire x1="60.96" y1="-60.96" x2="60.96" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="60.96" y="-66.04" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PD3"/>
<wire x1="170.18" y1="-193.04" x2="170.18" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="170.18" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S14" class="0">
<segment>
<pinref part="U$9" gate="G$1" pin="3"/>
<wire x1="73.66" y1="-60.96" x2="73.66" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="73.66" y="-66.04" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB3"/>
<wire x1="167.64" y1="-193.04" x2="167.64" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="167.64" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S15" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="3"/>
<wire x1="86.36" y1="-60.96" x2="86.36" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="86.36" y="-66.04" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB4"/>
<wire x1="165.1" y1="-193.04" x2="165.1" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="165.1" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S16" class="0">
<segment>
<pinref part="U$16" gate="G$1" pin="3"/>
<wire x1="99.06" y1="-60.96" x2="99.06" y2="-66.04" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="99.06" y="-66.04" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB5"/>
<wire x1="162.56" y1="-193.04" x2="162.56" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="162.56" y="-190.5" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="S17" class="0">
<segment>
<pinref part="U$17" gate="G$1" pin="3"/>
<wire x1="10.16" y1="-91.44" x2="10.16" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="10.16" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PF0-OSC_IN"/>
<wire x1="139.7" y1="-226.06" x2="137.16" y2="-226.06" width="0.1524" layer="91"/>
<label x="137.16" y="-226.06" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="S4" class="0">
<segment>
<pinref part="U$11" gate="G$1" pin="3"/>
<wire x1="48.26" y1="-30.48" x2="48.26" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="48.26" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA8"/>
<wire x1="190.5" y1="-228.6" x2="193.04" y2="-228.6" width="0.1524" layer="91"/>
<label x="193.04" y="-228.6" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S3" class="0">
<segment>
<pinref part="U$14" gate="G$1" pin="3"/>
<wire x1="35.56" y1="-30.48" x2="35.56" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="35.56" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB15"/>
<wire x1="190.5" y1="-231.14" x2="193.04" y2="-231.14" width="0.1524" layer="91"/>
<label x="193.04" y="-231.14" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S2" class="0">
<segment>
<pinref part="U$15" gate="G$1" pin="3"/>
<wire x1="22.86" y1="-30.48" x2="22.86" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="22.86" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB14"/>
<wire x1="190.5" y1="-233.68" x2="193.04" y2="-233.68" width="0.1524" layer="91"/>
<label x="193.04" y="-233.68" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S1" class="0">
<segment>
<pinref part="U$13" gate="G$1" pin="3"/>
<wire x1="10.16" y1="-30.48" x2="10.16" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="10.16" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB13"/>
<wire x1="190.5" y1="-236.22" x2="193.04" y2="-236.22" width="0.1524" layer="91"/>
<label x="193.04" y="-236.22" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S23" class="0">
<segment>
<pinref part="U$23" gate="G$1" pin="3"/>
<wire x1="86.36" y1="-91.44" x2="86.36" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="86.36" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA4"/>
<wire x1="154.94" y1="-251.46" x2="154.94" y2="-254" width="0.1524" layer="91"/>
<label x="154.94" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S24" class="0">
<segment>
<pinref part="U$24" gate="G$1" pin="3"/>
<wire x1="99.06" y1="-91.44" x2="99.06" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="99.06" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA5"/>
<wire x1="157.48" y1="-251.46" x2="157.48" y2="-254" width="0.1524" layer="91"/>
<label x="157.48" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S25" class="0">
<segment>
<pinref part="U$25" gate="G$1" pin="3"/>
<wire x1="10.16" y1="-121.92" x2="10.16" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="10.16" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA6"/>
<wire x1="160.02" y1="-251.46" x2="160.02" y2="-254" width="0.1524" layer="91"/>
<label x="160.02" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S5" class="0">
<segment>
<pinref part="U$12" gate="G$1" pin="3"/>
<wire x1="60.96" y1="-30.48" x2="60.96" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="60.96" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA9"/>
<wire x1="190.5" y1="-226.06" x2="193.04" y2="-226.06" width="0.1524" layer="91"/>
<label x="193.04" y="-226.06" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S6" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="3"/>
<wire x1="73.66" y1="-30.48" x2="73.66" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="73.66" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PC6"/>
<wire x1="190.5" y1="-223.52" x2="193.04" y2="-223.52" width="0.1524" layer="91"/>
<label x="193.04" y="-223.52" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S7" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="3"/>
<wire x1="86.36" y1="-30.48" x2="86.36" y2="-38.1" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="86.36" y="-38.1" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PC7"/>
<wire x1="190.5" y1="-220.98" x2="193.04" y2="-220.98" width="0.1524" layer="91"/>
<label x="193.04" y="-220.98" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="S18" class="0">
<segment>
<pinref part="U$18" gate="G$1" pin="3"/>
<wire x1="22.86" y1="-91.44" x2="22.86" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="22.86" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PF1-OSC_OUT"/>
<wire x1="139.7" y1="-228.6" x2="137.16" y2="-228.6" width="0.1524" layer="91"/>
<label x="137.16" y="-228.6" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="S19" class="0">
<segment>
<pinref part="U$19" gate="G$1" pin="3"/>
<wire x1="35.56" y1="-91.44" x2="35.56" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="35.56" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA0"/>
<wire x1="139.7" y1="-233.68" x2="137.16" y2="-233.68" width="0.1524" layer="91"/>
<label x="137.16" y="-233.68" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="S20" class="0">
<segment>
<pinref part="U$21" gate="G$1" pin="3"/>
<wire x1="48.26" y1="-91.44" x2="48.26" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="48.26" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA1"/>
<wire x1="139.7" y1="-236.22" x2="137.16" y2="-236.22" width="0.1524" layer="91"/>
<label x="137.16" y="-236.22" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="S21" class="0">
<segment>
<pinref part="U$20" gate="G$1" pin="3"/>
<wire x1="60.96" y1="-91.44" x2="60.96" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="60.96" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA2"/>
<wire x1="149.86" y1="-251.46" x2="149.86" y2="-254" width="0.1524" layer="91"/>
<label x="149.86" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S22" class="0">
<segment>
<pinref part="U$22" gate="G$1" pin="3"/>
<wire x1="73.66" y1="-91.44" x2="73.66" y2="-96.52" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="73.66" y="-96.52" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA3"/>
<wire x1="152.4" y1="-251.46" x2="152.4" y2="-254" width="0.1524" layer="91"/>
<label x="152.4" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="U$13" gate="G$1" pin="2"/>
<wire x1="7.62" y1="-40.64" x2="7.62" y2="-30.48" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY4" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$15" gate="G$1" pin="2"/>
<wire x1="20.32" y1="-30.48" x2="20.32" y2="-40.64" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY6" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$14" gate="G$1" pin="2"/>
<wire x1="33.02" y1="-30.48" x2="33.02" y2="-40.64" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY9" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$11" gate="G$1" pin="2"/>
<wire x1="45.72" y1="-30.48" x2="45.72" y2="-40.64" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY10" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$12" gate="G$1" pin="2"/>
<wire x1="58.42" y1="-40.64" x2="58.42" y2="-30.48" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY47" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="SUPPLY48" gate="G$1" pin="VCC"/>
<wire x1="71.12" y1="-40.64" x2="71.12" y2="-30.48" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$1" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="SUPPLY49" gate="G$1" pin="VCC"/>
<wire x1="83.82" y1="-40.64" x2="83.82" y2="-30.48" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$2" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="2"/>
<wire x1="96.52" y1="-30.48" x2="96.52" y2="-40.64" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY50" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="2"/>
<wire x1="7.62" y1="-60.96" x2="7.62" y2="-71.12" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY51" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$5" gate="G$1" pin="2"/>
<wire x1="20.32" y1="-60.96" x2="20.32" y2="-71.12" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY52" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="SUPPLY53" gate="G$1" pin="VCC"/>
<wire x1="33.02" y1="-71.12" x2="33.02" y2="-60.96" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$6" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="U$7" gate="G$1" pin="2"/>
<wire x1="45.72" y1="-60.96" x2="45.72" y2="-71.12" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY54" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="2"/>
<wire x1="58.42" y1="-60.96" x2="58.42" y2="-71.12" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY55" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$9" gate="G$1" pin="2"/>
<wire x1="71.12" y1="-60.96" x2="71.12" y2="-71.12" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY56" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$10" gate="G$1" pin="2"/>
<wire x1="83.82" y1="-60.96" x2="83.82" y2="-71.12" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY57" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$17" gate="G$1" pin="2"/>
<wire x1="7.62" y1="-91.44" x2="7.62" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY59" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$18" gate="G$1" pin="2"/>
<wire x1="20.32" y1="-91.44" x2="20.32" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY60" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$19" gate="G$1" pin="2"/>
<wire x1="33.02" y1="-91.44" x2="33.02" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY61" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$21" gate="G$1" pin="2"/>
<wire x1="45.72" y1="-91.44" x2="45.72" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY62" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$20" gate="G$1" pin="2"/>
<wire x1="58.42" y1="-91.44" x2="58.42" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY63" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$22" gate="G$1" pin="2"/>
<wire x1="71.12" y1="-91.44" x2="71.12" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY64" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$23" gate="G$1" pin="2"/>
<wire x1="83.82" y1="-91.44" x2="83.82" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY65" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$24" gate="G$1" pin="2"/>
<wire x1="96.52" y1="-91.44" x2="96.52" y2="-101.6" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY66" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$25" gate="G$1" pin="2"/>
<wire x1="7.62" y1="-121.92" x2="7.62" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY67" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="SUPPLY58" gate="G$1" pin="VCC"/>
<wire x1="96.52" y1="-71.12" x2="96.52" y2="-60.96" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="U$16" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="SUPPLY3" gate="G$1" pin="VCC"/>
<wire x1="208.28" y1="114.3" x2="208.28" y2="109.22" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J1" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="U$26" gate="G$1" pin="2"/>
<wire x1="20.32" y1="-121.92" x2="20.32" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY41" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$27" gate="G$1" pin="2"/>
<wire x1="33.02" y1="-121.92" x2="33.02" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY70" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$28" gate="G$1" pin="2"/>
<wire x1="45.72" y1="-121.92" x2="45.72" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY71" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$29" gate="G$1" pin="2"/>
<wire x1="58.42" y1="-121.92" x2="58.42" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY72" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$30" gate="G$1" pin="2"/>
<wire x1="71.12" y1="-121.92" x2="71.12" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY73" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$31" gate="G$1" pin="2"/>
<wire x1="83.82" y1="-121.92" x2="83.82" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY74" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="U$32" gate="G$1" pin="2"/>
<wire x1="96.52" y1="-121.92" x2="96.52" y2="-132.08" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<pinref part="SUPPLY76" gate="G$1" pin="VCC"/>
</segment>
<segment>
<pinref part="JP1" gate="G$1" pin="1"/>
<wire x1="195.58" y1="109.22" x2="195.58" y2="114.3" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="SUPPLY91" gate="G$1" pin="VCC"/>
</segment>
</net>
<net name="D+" class="0">
<segment>
<label x="160.02" y="17.78" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
<segment>
<wire x1="162.56" y1="17.78" x2="160.02" y2="17.78" width="0.1524" layer="91" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO20"/>
</segment>
<segment>
<wire x1="139.7" y1="101.6" x2="142.24" y2="101.6" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="142.24" y="101.6" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="DP2"/>
</segment>
<segment>
<wire x1="139.7" y1="109.22" x2="142.24" y2="109.22" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="142.24" y="109.22" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="DP1"/>
</segment>
</net>
<net name="D-" class="0">
<segment>
<label x="160.02" y="20.32" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
<segment>
<wire x1="160.02" y1="20.32" x2="162.56" y2="20.32" width="0.1524" layer="91" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO19"/>
</segment>
<segment>
<wire x1="139.7" y1="111.76" x2="142.24" y2="111.76" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="142.24" y="111.76" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="DN1"/>
</segment>
<segment>
<wire x1="139.7" y1="104.14" x2="142.24" y2="104.14" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="142.24" y="104.14" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="DN2"/>
</segment>
</net>
<net name="VCC_5V" class="0">
<segment>
<label x="259.08" y="116.84" size="1.27" layer="95" xref="yes" grouprefs="POWER"/>
<pinref part="C1" gate="G$1" pin="1"/>
<wire x1="254" y1="106.68" x2="254" y2="116.84" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="254" y1="116.84" x2="259.08" y2="116.84" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="254" y1="106.68" x2="254" y2="104.14" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="PS1" gate="G$1" pin="IN"/>
<junction x="254" y="106.68" grouprefs="POWER"/>
<junction x="254" y="116.84" grouprefs="POWER"/>
</segment>
<segment>
<wire x1="139.7" y1="116.84" x2="142.24" y2="116.84" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="142.24" y="116.84" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="VBUS"/>
</segment>
<segment>
<pinref part="JP1" gate="G$1" pin="2"/>
<wire x1="195.58" y1="106.68" x2="195.58" y2="104.14" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="195.58" y="104.14" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="C16" gate="G$1" pin="1"/>
<wire x1="157.48" y1="-124.46" x2="147.32" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C22" gate="G$1" pin="1"/>
<wire x1="147.32" y1="-124.46" x2="142.24" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="147.32" y="-124.46" grouprefs="AMP_SOUND"/>
<pinref part="IC2" gate="G$1" pin="VDD_1"/>
<wire x1="139.7" y1="-121.92" x2="139.7" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="139.7" y1="-124.46" x2="142.24" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="142.24" y1="-124.46" x2="142.24" y2="-121.92" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="IC2" gate="G$1" pin="VDD_2"/>
<junction x="142.24" y="-124.46" grouprefs="AMP_SOUND"/>
<wire x1="157.48" y1="-124.46" x2="162.56" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="157.48" y="-124.46" grouprefs="AMP_SOUND"/>
<label x="162.56" y="-124.46" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="116.84" y1="-119.38" x2="116.84" y2="-121.92" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="116.84" y="-121.92" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="!SD_MODE"/>
<wire x1="208.28" y1="-104.14" x2="205.74" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="205.74" y1="-104.14" x2="205.74" y2="-109.22" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="205.74" y="-109.22" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="C25" gate="G$1" pin="1"/>
<wire x1="246.38" y1="-124.46" x2="236.22" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C26" gate="G$1" pin="1"/>
<wire x1="236.22" y1="-124.46" x2="231.14" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="236.22" y="-124.46" grouprefs="AMP_SOUND"/>
<pinref part="IC8" gate="G$1" pin="VDD_1"/>
<wire x1="228.6" y1="-121.92" x2="228.6" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="228.6" y1="-124.46" x2="231.14" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="231.14" y1="-124.46" x2="231.14" y2="-121.92" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="IC8" gate="G$1" pin="VDD_2"/>
<junction x="231.14" y="-124.46" grouprefs="AMP_SOUND"/>
<wire x1="246.38" y1="-124.46" x2="251.46" y2="-124.46" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="246.38" y="-124.46" grouprefs="AMP_SOUND"/>
<label x="251.46" y="-124.46" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="2"/>
<wire x1="375.92" y1="-20.32" x2="373.38" y2="-20.32" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-20.32" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="1"/>
<wire x1="375.92" y1="-17.78" x2="373.38" y2="-17.78" width="0.1524" layer="91"/>
<label x="373.38" y="-17.78" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="VCC_3.3V" class="0">
<segment>
<label x="259.08" y="86.36" size="1.27" layer="95" xref="yes" grouprefs="POWER"/>
<pinref part="C7" gate="G$1" pin="1"/>
<wire x1="254" y1="96.52" x2="254" y2="86.36" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="254" y1="86.36" x2="259.08" y2="86.36" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="254" y1="96.52" x2="254" y2="99.06" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="PS1" gate="G$1" pin="OUT"/>
<junction x="254" y="96.52" grouprefs="POWER"/>
<junction x="254" y="86.36" grouprefs="POWER"/>
</segment>
<segment>
<wire x1="162.56" y1="48.26" x2="160.02" y2="48.26" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="48.26" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="3V3"/>
</segment>
<segment>
<pinref part="IC6" gate="G$1" pin="VIN"/>
<pinref part="IC4" gate="G$1" pin="VIN"/>
<wire x1="347.98" y1="93.98" x2="347.98" y2="101.6" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="347.98" y1="101.6" x2="347.98" y2="111.76" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C13" gate="G$1" pin="1"/>
<label x="347.98" y="111.76" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="POWER"/>
<junction x="347.98" y="101.6"/>
</segment>
<segment>
<wire x1="40.64" y1="33.02" x2="60.96" y2="33.02" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<pinref part="C12" gate="G$1" pin="1"/>
<label x="60.96" y="35.56" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="MICRO_SD"/>
<pinref part="J6" gate="G$1" pin="VDD"/>
<wire x1="60.96" y1="33.02" x2="60.96" y2="35.56" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<junction x="60.96" y="33.02"/>
</segment>
<segment>
<wire x1="378.46" y1="104.14" x2="375.92" y2="104.14" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="104.14" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="VDD"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="VDD"/>
<wire x1="261.62" y1="48.26" x2="261.62" y2="53.34" width="0.1524" layer="91" grouprefs="IMU"/>
<wire x1="261.62" y1="53.34" x2="289.56" y2="53.34" width="0.1524" layer="91" grouprefs="IMU"/>
<wire x1="289.56" y1="53.34" x2="289.56" y2="27.94" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="IC1" gate="G$1" pin="VDDIO"/>
<wire x1="287.02" y1="27.94" x2="289.56" y2="27.94" width="0.1524" layer="91" grouprefs="IMU"/>
<label x="289.56" y="45.72" size="1.27" layer="95" xref="yes" grouprefs="IMU"/>
<pinref part="C18" gate="G$1" pin="1"/>
<junction x="289.56" y="53.34"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="PS0/WAKE"/>
<wire x1="236.22" y1="30.48" x2="233.68" y2="30.48" width="0.1524" layer="91" grouprefs="IMU"/>
<label x="233.68" y="30.48" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="IC7" gate="G$1" pin="VDD"/>
<wire x1="55.88" y1="93.98" x2="53.34" y2="93.98" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="53.34" y="91.44" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="A0"/>
<wire x1="55.88" y1="91.44" x2="53.34" y2="91.44" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="53.34" y1="91.44" x2="53.34" y2="93.98" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="VBAT"/>
<wire x1="139.7" y1="-215.9" x2="127" y2="-215.9" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="127" y="-215.9" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="SERVO_DRIVER"/>
<pinref part="C15" gate="G$1" pin="1"/>
<wire x1="127" y1="-213.36" x2="127" y2="-215.9" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="VDD/VDDA"/>
<wire x1="139.7" y1="-220.98" x2="127" y2="-220.98" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="127" y="-220.98" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="SERVO_DRIVER"/>
<pinref part="C11" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="JP2" gate="A" pin="3"/>
<wire x1="137.16" y1="-193.04" x2="132.08" y2="-193.04" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="132.08" y="-193.04" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="6"/>
<wire x1="396.24" y1="-22.86" x2="398.78" y2="-22.86" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-22.86" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="5"/>
<wire x1="396.24" y1="-25.4" x2="398.78" y2="-25.4" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-25.4" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="8"/>
<wire x1="396.24" y1="-33.02" x2="398.78" y2="-33.02" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-33.02" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="7"/>
<wire x1="396.24" y1="-35.56" x2="398.78" y2="-35.56" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-35.56" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="6"/>
<wire x1="396.24" y1="-38.1" x2="398.78" y2="-38.1" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-38.1" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="5"/>
<wire x1="396.24" y1="-40.64" x2="398.78" y2="-40.64" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-40.64" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN3" gate="G$1" pin="8"/>
<wire x1="396.24" y1="-48.26" x2="398.78" y2="-48.26" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-48.26" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN3" gate="G$1" pin="7"/>
<wire x1="396.24" y1="-50.8" x2="398.78" y2="-50.8" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-50.8" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="8"/>
<wire x1="396.24" y1="-63.5" x2="398.78" y2="-63.5" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-63.5" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="7"/>
<wire x1="396.24" y1="-66.04" x2="398.78" y2="-66.04" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-66.04" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="8"/>
<wire x1="396.24" y1="-78.74" x2="398.78" y2="-78.74" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-78.74" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="7"/>
<wire x1="396.24" y1="-81.28" x2="398.78" y2="-81.28" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-81.28" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
<segment>
<pinref part="J5" gate="A" pin="3"/>
<wire x1="172.72" y1="88.9" x2="170.18" y2="88.9" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="170.18" y="88.9" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="VCC_IO"/>
<wire x1="27.94" y1="-190.5" x2="25.4" y2="-190.5" width="0.1524" layer="91" grouprefs="GNSS"/>
<label x="25.4" y="-190.5" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="GNSS"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="VCC"/>
<wire x1="27.94" y1="-210.82" x2="25.4" y2="-210.82" width="0.1524" layer="91" grouprefs="GNSS"/>
<label x="25.4" y="-210.82" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="GNSS"/>
<pinref part="IC3" gate="G$1" pin="V_BCKP"/>
<wire x1="27.94" y1="-208.28" x2="25.4" y2="-208.28" width="0.1524" layer="91" grouprefs="GNSS"/>
<wire x1="25.4" y1="-208.28" x2="25.4" y2="-210.82" width="0.1524" layer="91" grouprefs="GNSS"/>
</segment>
<segment>
<pinref part="MK1" gate="G$1" pin="VDD"/>
<wire x1="111.76" y1="30.48" x2="114.3" y2="30.48" width="0.1524" layer="91" grouprefs="MIC"/>
<wire x1="114.3" y1="30.48" x2="114.3" y2="33.02" width="0.1524" layer="91" grouprefs="MIC"/>
<pinref part="C29" gate="G$1" pin="1"/>
<wire x1="114.3" y1="30.48" x2="116.84" y2="30.48" width="0.1524" layer="91" grouprefs="MIC"/>
<junction x="114.3" y="30.48" grouprefs="MIC"/>
<label x="116.84" y="30.48" size="1.27" layer="95" xref="yes" grouprefs="MIC"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="5"/>
<wire x1="396.24" y1="-71.12" x2="398.78" y2="-71.12" width="0.1524" layer="91"/>
<label x="398.78" y="-71.12" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="6"/>
<wire x1="396.24" y1="-83.82" x2="398.78" y2="-83.82" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-83.82" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="5"/>
<wire x1="396.24" y1="-86.36" x2="398.78" y2="-86.36" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-86.36" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="386.08" y1="30.48" x2="363.22" y2="30.48" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="386.08" y1="30.48" x2="388.62" y2="30.48" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="386.08" y="33.02" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CAMERA"/>
<wire x1="386.08" y1="33.02" x2="386.08" y2="30.48" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="C5" gate="G$1" pin="1"/>
<pinref part="J7" gate="G$1" pin="14"/>
<junction x="386.08" y="30.48"/>
</segment>
<segment>
<pinref part="RN6" gate="G$1" pin="5"/>
<wire x1="396.24" y1="-101.6" x2="398.78" y2="-101.6" width="0.1524" layer="91"/>
<label x="398.78" y="-101.6" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="RESET" class="0">
<segment>
<wire x1="162.56" y1="45.72" x2="160.02" y2="45.72" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="45.72" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="EN"/>
</segment>
<segment>
<wire x1="22.86" y1="71.12" x2="25.4" y2="71.12" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="25.4" y="71.12" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="S2" gate="G$1" pin="A"/>
</segment>
<segment>
<pinref part="RN6" gate="G$1" pin="4"/>
<wire x1="375.92" y1="-101.6" x2="373.38" y2="-101.6" width="0.1524" layer="91"/>
<label x="373.38" y="-101.6" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="BOOT" class="0">
<segment>
<wire x1="195.58" y1="48.26" x2="198.12" y2="48.26" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="198.12" y="48.26" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO0"/>
</segment>
<segment>
<wire x1="22.86" y1="88.9" x2="25.4" y2="88.9" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="25.4" y="88.9" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="S1" gate="G$1" pin="A"/>
</segment>
</net>
<net name="S26" class="0">
<segment>
<pinref part="U$26" gate="G$1" pin="3"/>
<wire x1="22.86" y1="-121.92" x2="22.86" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="22.86" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA7"/>
<wire x1="162.56" y1="-251.46" x2="162.56" y2="-254" width="0.1524" layer="91"/>
<label x="162.56" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S27" class="0">
<segment>
<pinref part="U$27" gate="G$1" pin="3"/>
<wire x1="35.56" y1="-121.92" x2="35.56" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="35.56" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB0"/>
<wire x1="165.1" y1="-251.46" x2="165.1" y2="-254" width="0.1524" layer="91"/>
<label x="165.1" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S28" class="0">
<segment>
<pinref part="U$28" gate="G$1" pin="3"/>
<wire x1="48.26" y1="-121.92" x2="48.26" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="48.26" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB1"/>
<wire x1="167.64" y1="-251.46" x2="167.64" y2="-254" width="0.1524" layer="91"/>
<label x="167.64" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S29" class="0">
<segment>
<pinref part="U$29" gate="G$1" pin="3"/>
<wire x1="60.96" y1="-121.92" x2="60.96" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="60.96" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB2"/>
<wire x1="170.18" y1="-251.46" x2="170.18" y2="-254" width="0.1524" layer="91"/>
<label x="170.18" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S31" class="0">
<segment>
<pinref part="U$31" gate="G$1" pin="3"/>
<wire x1="86.36" y1="-121.92" x2="86.36" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="86.36" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB11"/>
<wire x1="175.26" y1="-251.46" x2="175.26" y2="-254" width="0.1524" layer="91"/>
<label x="175.26" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S32" class="0">
<segment>
<pinref part="U$32" gate="G$1" pin="3"/>
<wire x1="99.06" y1="-121.92" x2="99.06" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="99.06" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB12"/>
<wire x1="177.8" y1="-251.46" x2="177.8" y2="-254" width="0.1524" layer="91"/>
<label x="177.8" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="S30" class="0">
<segment>
<pinref part="U$30" gate="G$1" pin="3"/>
<wire x1="73.66" y1="-121.92" x2="73.66" y2="-127" width="0.1524" layer="91" grouprefs="SERVO_CONNECTORS"/>
<label x="73.66" y="-127" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="SERVO_CONNECTORS"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PB10"/>
<wire x1="172.72" y1="-251.46" x2="172.72" y2="-254" width="0.1524" layer="91"/>
<label x="172.72" y="-254" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="SDA" class="0">
<segment>
<label x="198.12" y="17.78" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
<wire x1="195.58" y1="17.78" x2="198.12" y2="17.78" width="0.1524" layer="91" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO1"/>
</segment>
<segment>
<wire x1="55.88" y1="96.52" x2="53.34" y2="96.52" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="53.34" y="96.52" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="SDA"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA12_[PA10]"/>
<wire x1="190.5" y1="-213.36" x2="193.04" y2="-213.36" width="0.1524" layer="91"/>
<label x="193.04" y="-213.36" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J5" gate="A" pin="2"/>
<wire x1="172.72" y1="91.44" x2="170.18" y2="91.44" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="170.18" y="91.44" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="SDA_/_SPI_CS_N"/>
<wire x1="27.94" y1="-195.58" x2="25.4" y2="-195.58" width="0.1524" layer="91" grouprefs="GNSS"/>
<label x="25.4" y="-195.58" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="GNSS"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="7"/>
<wire x1="396.24" y1="-20.32" x2="398.78" y2="-20.32" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-20.32" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="SCL" class="0">
<segment>
<label x="198.12" y="20.32" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
<wire x1="195.58" y1="20.32" x2="198.12" y2="20.32" width="0.1524" layer="91" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO2"/>
</segment>
<segment>
<wire x1="55.88" y1="101.6" x2="53.34" y2="101.6" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="53.34" y="101.6" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="SCL"/>
</segment>
<segment>
<pinref part="IC10" gate="G$1" pin="PA11_[PA9]"/>
<wire x1="190.5" y1="-215.9" x2="193.04" y2="-215.9" width="0.1524" layer="91"/>
<label x="193.04" y="-215.9" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J5" gate="A" pin="1"/>
<wire x1="172.72" y1="93.98" x2="170.18" y2="93.98" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="170.18" y="93.98" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="SCL_/_SPI_CLK"/>
<wire x1="27.94" y1="-203.2" x2="25.4" y2="-203.2" width="0.1524" layer="91" grouprefs="GNSS"/>
<label x="25.4" y="-203.2" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="GNSS"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="8"/>
<wire x1="396.24" y1="-17.78" x2="398.78" y2="-17.78" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="398.78" y="-17.78" size="1.27" layer="95" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="CC1" class="0">
<segment>
<wire x1="139.7" y1="96.52" x2="142.24" y2="96.52" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="CC1"/>
<label x="142.24" y="96.52" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="RN6" gate="G$1" pin="2"/>
<wire x1="375.92" y1="-96.52" x2="373.38" y2="-96.52" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-96.52" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="CC2" class="0">
<segment>
<wire x1="139.7" y1="88.9" x2="142.24" y2="88.9" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<pinref part="J2" gate="G$1" pin="CC2"/>
<label x="142.24" y="88.9" size="1.27" layer="95" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="RN6" gate="G$1" pin="3"/>
<wire x1="375.92" y1="-99.06" x2="373.38" y2="-99.06" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-99.06" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="VCC_1.2V" class="0">
<segment>
<pinref part="IC4" gate="G$1" pin="VOUT"/>
<wire x1="320.04" y1="109.22" x2="320.04" y2="106.68" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="320.04" y1="106.68" x2="312.42" y2="106.68" width="0.1524" layer="91" grouprefs="POWER"/>
<label x="297.18" y="106.68" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="POWER"/>
<pinref part="C6" gate="G$1" pin="1"/>
<wire x1="312.42" y1="106.68" x2="302.26" y2="106.68" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="302.26" y1="106.68" x2="297.18" y2="106.68" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C8" gate="G$1" pin="1"/>
<junction x="312.42" y="106.68"/>
<junction x="302.26" y="106.68"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="15"/>
<wire x1="363.22" y1="27.94" x2="365.76" y2="27.94" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="27.94" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="VCC_2.8V" class="0">
<segment>
<wire x1="320.04" y1="91.44" x2="320.04" y2="88.9" width="0.1524" layer="91" grouprefs="POWER"/>
<wire x1="320.04" y1="88.9" x2="312.42" y2="88.9" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="IC6" gate="G$1" pin="VOUT"/>
<pinref part="C9" gate="G$1" pin="1"/>
<wire x1="312.42" y1="88.9" x2="302.26" y2="88.9" width="0.1524" layer="91" grouprefs="POWER"/>
<pinref part="C10" gate="G$1" pin="1"/>
<wire x1="302.26" y1="88.9" x2="297.18" y2="88.9" width="0.1524" layer="91" grouprefs="POWER"/>
<label x="297.18" y="88.9" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="POWER"/>
<junction x="312.42" y="88.9"/>
<junction x="302.26" y="88.9"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="21"/>
<wire x1="363.22" y1="12.7" x2="365.76" y2="12.7" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="12.7" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="CAM_SDA" class="0">
<segment>
<wire x1="162.56" y1="43.18" x2="160.02" y2="43.18" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="43.18" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO4"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="22"/>
<wire x1="363.22" y1="10.16" x2="365.76" y2="10.16" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="10.16" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="1"/>
<wire x1="375.92" y1="-33.02" x2="373.38" y2="-33.02" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-33.02" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="CAM_SCL" class="0">
<segment>
<wire x1="162.56" y1="40.64" x2="160.02" y2="40.64" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="40.64" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO5"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="20"/>
<wire x1="363.22" y1="15.24" x2="365.76" y2="15.24" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="15.24" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="4"/>
<wire x1="375.92" y1="-25.4" x2="373.38" y2="-25.4" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-25.4" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="CAM_RST" class="0">
<segment>
<pinref part="J7" gate="G$1" pin="19"/>
<label x="378.46" y="17.78" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
<pinref part="C14" gate="G$1" pin="1"/>
<wire x1="363.22" y1="17.78" x2="378.46" y2="17.78" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="378.46" y1="12.7" x2="378.46" y2="17.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="RN1" gate="G$1" pin="3"/>
<wire x1="375.92" y1="-22.86" x2="373.38" y2="-22.86" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-22.86" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="VSYNC" class="0">
<segment>
<wire x1="162.56" y1="38.1" x2="160.02" y2="38.1" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="38.1" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO6"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="18"/>
<wire x1="363.22" y1="20.32" x2="365.76" y2="20.32" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="20.32" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="HREF" class="0">
<segment>
<wire x1="162.56" y1="35.56" x2="160.02" y2="35.56" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="35.56" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO7"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="16"/>
<wire x1="363.22" y1="25.4" x2="365.76" y2="25.4" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="25.4" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA9" class="0">
<segment>
<wire x1="162.56" y1="30.48" x2="160.02" y2="30.48" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="30.48" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO16"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="13"/>
<wire x1="363.22" y1="33.02" x2="365.76" y2="33.02" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="33.02" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="XCLK" class="0">
<segment>
<wire x1="162.56" y1="33.02" x2="160.02" y2="33.02" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="33.02" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO15"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="12"/>
<wire x1="363.22" y1="35.56" x2="365.76" y2="35.56" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="35.56" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA8" class="0">
<segment>
<wire x1="162.56" y1="27.94" x2="160.02" y2="27.94" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="27.94" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO17"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="11"/>
<wire x1="363.22" y1="38.1" x2="365.76" y2="38.1" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="38.1" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA7" class="0">
<segment>
<wire x1="162.56" y1="25.4" x2="160.02" y2="25.4" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="25.4" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO18"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="9"/>
<wire x1="363.22" y1="43.18" x2="365.76" y2="43.18" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="43.18" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="PCLK" class="0">
<segment>
<wire x1="162.56" y1="0" x2="160.02" y2="0" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="0" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO13"/>
</segment>
<segment>
<label x="386.08" y="48.26" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CAMERA"/>
<wire x1="388.62" y1="45.72" x2="386.08" y2="45.72" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="386.08" y1="45.72" x2="363.22" y2="45.72" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="386.08" y1="45.72" x2="386.08" y2="48.26" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="C3" gate="G$1" pin="1"/>
<pinref part="J7" gate="G$1" pin="8"/>
<junction x="386.08" y="45.72"/>
</segment>
</net>
<net name="DATA4" class="0">
<segment>
<wire x1="162.56" y1="22.86" x2="160.02" y2="22.86" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="22.86" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO8"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="3"/>
<wire x1="363.22" y1="58.42" x2="365.76" y2="58.42" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="58.42" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA3" class="0">
<segment>
<wire x1="162.56" y1="10.16" x2="160.02" y2="10.16" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="10.16" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO9"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="4"/>
<wire x1="363.22" y1="55.88" x2="365.76" y2="55.88" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="55.88" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA5" class="0">
<segment>
<wire x1="162.56" y1="7.62" x2="160.02" y2="7.62" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="7.62" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO10"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="5"/>
<wire x1="363.22" y1="53.34" x2="365.76" y2="53.34" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="53.34" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA2" class="0">
<segment>
<wire x1="162.56" y1="5.08" x2="160.02" y2="5.08" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="5.08" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO11"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="6"/>
<wire x1="363.22" y1="50.8" x2="365.76" y2="50.8" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="50.8" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="DATA6" class="0">
<segment>
<wire x1="162.56" y1="2.54" x2="160.02" y2="2.54" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="2.54" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
<pinref part="IC5" gate="G$1" pin="IO12"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="7"/>
<wire x1="363.22" y1="48.26" x2="365.76" y2="48.26" width="0.1524" layer="91" grouprefs="CAMERA"/>
<label x="365.76" y="48.26" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
</segment>
</net>
<net name="SD_MISO" class="0">
<segment>
<label x="43.18" y="25.4" size="1.27" layer="95" xref="yes" grouprefs="MICRO_SD"/>
<wire x1="40.64" y1="25.4" x2="43.18" y2="25.4" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<pinref part="J6" gate="G$1" pin="DAT0"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO40"/>
<wire x1="195.58" y1="33.02" x2="198.12" y2="33.02" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="198.12" y="33.02" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
<segment>
<pinref part="RN3" gate="G$1" pin="1"/>
<wire x1="375.92" y1="-48.26" x2="373.38" y2="-48.26" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-48.26" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="SD_SCK" class="0">
<segment>
<wire x1="40.64" y1="30.48" x2="43.18" y2="30.48" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<label x="43.18" y="30.48" size="1.27" layer="95" xref="yes" grouprefs="MICRO_SD"/>
<pinref part="J6" gate="G$1" pin="CLK"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO39"/>
<wire x1="195.58" y1="35.56" x2="198.12" y2="35.56" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="198.12" y="35.56" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="SD_MOSI" class="0">
<segment>
<label x="43.18" y="35.56" size="1.27" layer="95" xref="yes" grouprefs="MICRO_SD"/>
<wire x1="40.64" y1="35.56" x2="43.18" y2="35.56" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<pinref part="J6" gate="G$1" pin="CMD"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO38"/>
<wire x1="195.58" y1="38.1" x2="198.12" y2="38.1" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="198.12" y="38.1" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="4"/>
<wire x1="375.92" y1="-40.64" x2="373.38" y2="-40.64" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-40.64" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="TFT_SCK" class="0">
<segment>
<wire x1="378.46" y1="106.68" x2="375.92" y2="106.68" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="106.68" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="SCL"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO47"/>
<wire x1="162.56" y1="-7.62" x2="160.02" y2="-7.62" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="-7.62" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="TFT_MOSI" class="0">
<segment>
<wire x1="378.46" y1="109.22" x2="375.92" y2="109.22" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="109.22" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="SDA"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO21"/>
<wire x1="162.56" y1="-5.08" x2="160.02" y2="-5.08" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="-5.08" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="TFT_RES" class="0">
<segment>
<wire x1="378.46" y1="111.76" x2="375.92" y2="111.76" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="111.76" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="RES"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO48"/>
<wire x1="162.56" y1="-10.16" x2="160.02" y2="-10.16" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="-10.16" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="TFT_DC" class="0">
<segment>
<wire x1="378.46" y1="114.3" x2="375.92" y2="114.3" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="114.3" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="DC"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO42"/>
<wire x1="195.58" y1="27.94" x2="198.12" y2="27.94" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="198.12" y="27.94" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="TFT_CS" class="0">
<segment>
<wire x1="378.46" y1="116.84" x2="375.92" y2="116.84" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="116.84" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="CS"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO41"/>
<wire x1="195.58" y1="30.48" x2="198.12" y2="30.48" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="198.12" y="30.48" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="UP_BUTTON" class="0">
<segment>
<wire x1="68.58" y1="71.12" x2="68.58" y2="66.04" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<wire x1="68.58" y1="66.04" x2="73.66" y2="66.04" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="73.66" y="66.04" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="P0"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="D"/>
<wire x1="20.32" y1="109.22" x2="17.78" y2="109.22" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="17.78" y="109.22" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
</segment>
</net>
<net name="RIGHT_BUTTON" class="0">
<segment>
<wire x1="86.36" y1="93.98" x2="88.9" y2="93.98" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="88.9" y="93.98" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="P4"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="C"/>
<wire x1="20.32" y1="111.76" x2="17.78" y2="111.76" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="17.78" y="111.76" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
</segment>
</net>
<net name="LEFT_BUTTON" class="0">
<segment>
<wire x1="71.12" y1="71.12" x2="73.66" y2="71.12" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="73.66" y="71.12" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="P1"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="A"/>
<wire x1="20.32" y1="116.84" x2="17.78" y2="116.84" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="17.78" y="116.84" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
</segment>
</net>
<net name="ENTER_BUTTON" class="0">
<segment>
<wire x1="86.36" y1="88.9" x2="88.9" y2="88.9" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="88.9" y="88.9" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="P3"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="F"/>
<wire x1="40.64" y1="116.84" x2="43.18" y2="116.84" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="43.18" y="116.84" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
</segment>
</net>
<net name="DOWN_BUTTON" class="0">
<segment>
<wire x1="86.36" y1="83.82" x2="88.9" y2="83.82" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="88.9" y="83.82" size="1.27" layer="95" xref="yes" grouprefs="BUTTONS"/>
<pinref part="IC7" gate="G$1" pin="P2"/>
</segment>
<segment>
<pinref part="S3" gate="G$1" pin="B"/>
<wire x1="20.32" y1="114.3" x2="17.78" y2="114.3" width="0.1524" layer="91" grouprefs="BUTTONS"/>
<label x="17.78" y="114.3" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="BUTTONS"/>
</segment>
</net>
<net name="BNO085_RX" class="0">
<segment>
<pinref part="IC5" gate="G$1" pin="IO14"/>
<wire x1="162.56" y1="-2.54" x2="160.02" y2="-2.54" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="-2.54" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="H_SDA/H_MISO/TX_"/>
<label x="289.56" y="7.62" size="1.27" layer="95" xref="yes" grouprefs="IMU"/>
<wire x1="289.56" y1="7.62" x2="287.02" y2="7.62" width="0.1524" layer="91" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="4"/>
<wire x1="375.92" y1="-86.36" x2="373.38" y2="-86.36" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-86.36" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="TFT_BL" class="0">
<segment>
<wire x1="378.46" y1="119.38" x2="375.92" y2="119.38" width="0.1524" layer="91" grouprefs="TFT_DISPLAY"/>
<label x="375.92" y="119.38" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="TFT_DISPLAY"/>
<pinref part="U$33" gate="G$1" pin="BL"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO46"/>
<wire x1="162.56" y1="12.7" x2="160.02" y2="12.7" width="0.1524" layer="91" grouprefs="ESP32"/>
<label x="160.02" y="12.7" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="SD_DAT2" class="0">
<segment>
<pinref part="J6" gate="G$1" pin="DAT2"/>
<wire x1="40.64" y1="40.64" x2="43.18" y2="40.64" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<label x="43.18" y="40.64" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="2"/>
<wire x1="375.92" y1="-35.56" x2="373.38" y2="-35.56" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-35.56" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="SD_DAT3" class="0">
<segment>
<pinref part="J6" gate="G$1" pin="CD/DAT3"/>
<wire x1="40.64" y1="38.1" x2="43.18" y2="38.1" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<label x="43.18" y="38.1" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="RN2" gate="G$1" pin="3"/>
<wire x1="375.92" y1="-38.1" x2="373.38" y2="-38.1" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-38.1" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="SD_DAT1" class="0">
<segment>
<pinref part="J6" gate="G$1" pin="DAT1"/>
<wire x1="40.64" y1="22.86" x2="43.18" y2="22.86" width="0.1524" layer="91" grouprefs="MICRO_SD"/>
<label x="43.18" y="22.86" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="RN3" gate="G$1" pin="2"/>
<wire x1="375.92" y1="-50.8" x2="373.38" y2="-50.8" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-50.8" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="C17" gate="G$1" pin="1"/>
<wire x1="228.6" y1="25.4" x2="228.6" y2="22.86" width="0.1524" layer="91" grouprefs="IMU"/>
<wire x1="228.6" y1="22.86" x2="236.22" y2="22.86" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="IC1" gate="G$1" pin="CAP"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="XOUT32/CLKSEL1"/>
<wire x1="287.02" y1="22.86" x2="297.18" y2="22.86" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="C20" gate="G$1" pin="1"/>
<pinref part="C19" gate="G$1" pin="1"/>
<wire x1="297.18" y1="22.86" x2="299.72" y2="22.86" width="0.1524" layer="91" grouprefs="IMU"/>
<junction x="297.18" y="22.86"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="XIN32"/>
<wire x1="287.02" y1="25.4" x2="292.1" y2="25.4" width="0.1524" layer="91" grouprefs="IMU"/>
<wire x1="292.1" y1="25.4" x2="292.1" y2="35.56" width="0.1524" layer="91" grouprefs="IMU"/>
<wire x1="292.1" y1="35.56" x2="297.18" y2="35.56" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="C21" gate="G$1" pin="1"/>
<pinref part="C19" gate="G$1" pin="2"/>
<wire x1="297.18" y1="35.56" x2="299.72" y2="35.56" width="0.1524" layer="91" grouprefs="IMU"/>
<junction x="297.18" y="35.56"/>
</segment>
</net>
<net name="H_SCL" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="H_SCL/SCK/RX"/>
<wire x1="264.16" y1="-17.78" x2="264.16" y2="-20.32" width="0.1524" layer="91" grouprefs="IMU"/>
<label x="264.16" y="-20.32" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="1"/>
<wire x1="375.92" y1="-63.5" x2="373.38" y2="-63.5" width="0.1524" layer="91"/>
<label x="373.38" y="-63.5" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="H_CSN" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="H_CSN"/>
<wire x1="261.62" y1="-17.78" x2="261.62" y2="-20.32" width="0.1524" layer="91" grouprefs="IMU"/>
<label x="261.62" y="-20.32" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="2"/>
<wire x1="375.92" y1="-66.04" x2="373.38" y2="-66.04" width="0.1524" layer="91"/>
<label x="373.38" y="-66.04" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="H_MOSI" class="0">
<segment>
<wire x1="259.08" y1="-20.32" x2="259.08" y2="-17.78" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="IC1" gate="G$1" pin="SA0/H_MOSI_"/>
<label x="259.08" y="-20.32" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="3"/>
<wire x1="375.92" y1="-68.58" x2="373.38" y2="-68.58" width="0.1524" layer="91"/>
<label x="373.38" y="-68.58" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="BOOTN" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="BOOTN"/>
<wire x1="259.08" y1="48.26" x2="259.08" y2="50.8" width="0.1524" layer="91" grouprefs="IMU"/>
<label x="259.08" y="50.8" size="1.27" layer="95" rot="R90" xref="yes" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="3"/>
<wire x1="375.92" y1="-83.82" x2="373.38" y2="-83.82" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-83.82" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="NRST" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="NRST"/>
<wire x1="236.22" y1="17.78" x2="233.68" y2="17.78" width="0.1524" layer="91" grouprefs="IMU"/>
<label x="233.68" y="17.78" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="2"/>
<wire x1="375.92" y1="-81.28" x2="373.38" y2="-81.28" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-81.28" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="ENV_SDA" class="0">
<segment>
<wire x1="256.54" y1="-20.32" x2="256.54" y2="-17.78" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="IC1" gate="G$1" pin="ENV_SDA"/>
<label x="256.54" y="-20.32" size="1.27" layer="95" rot="R270" xref="yes" grouprefs="IMU"/>
</segment>
<segment>
<pinref part="RN4" gate="G$1" pin="4"/>
<wire x1="375.92" y1="-71.12" x2="373.38" y2="-71.12" width="0.1524" layer="91"/>
<label x="373.38" y="-71.12" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="ENV_SCL" class="0">
<segment>
<wire x1="233.68" y1="7.62" x2="236.22" y2="7.62" width="0.1524" layer="91" grouprefs="IMU"/>
<pinref part="IC1" gate="G$1" pin="ENV_SCL_"/>
<label x="233.68" y="7.62" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="RN5" gate="G$1" pin="1"/>
<wire x1="375.92" y1="-78.74" x2="373.38" y2="-78.74" width="0.1524" layer="91" grouprefs="RESISTORS"/>
<label x="373.38" y="-78.74" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="RESISTORS"/>
</segment>
</net>
<net name="CAM_PWDN" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="1"/>
<label x="375.92" y="25.4" size="1.27" layer="95" xref="yes" grouprefs="CAMERA"/>
<wire x1="375.92" y1="22.86" x2="375.92" y2="25.4" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="386.08" y1="22.86" x2="375.92" y2="22.86" width="0.1524" layer="91" grouprefs="CAMERA"/>
<wire x1="375.92" y1="22.86" x2="363.22" y2="22.86" width="0.1524" layer="91" grouprefs="CAMERA"/>
<pinref part="J7" gate="G$1" pin="17"/>
<junction x="375.92" y="22.86"/>
</segment>
</net>
<net name="SWDIO" class="0">
<segment>
<pinref part="IC10" gate="G$1" pin="PA13"/>
<wire x1="190.5" y1="-210.82" x2="193.04" y2="-210.82" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="193.04" y="-210.82" size="1.27" layer="95" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
<segment>
<pinref part="JP2" gate="A" pin="2"/>
<wire x1="137.16" y1="-190.5" x2="132.08" y2="-190.5" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="132.08" y="-190.5" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="SWCLK" class="0">
<segment>
<pinref part="IC10" gate="G$1" pin="PA14-BOOT0"/>
<wire x1="190.5" y1="-208.28" x2="193.04" y2="-208.28" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="193.04" y="-208.28" size="1.27" layer="95" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
<segment>
<pinref part="JP2" gate="A" pin="1"/>
<wire x1="137.16" y1="-187.96" x2="132.08" y2="-187.96" width="0.1524" layer="91" grouprefs="SERVO_DRIVER"/>
<label x="132.08" y="-187.96" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="SERVO_DRIVER"/>
</segment>
</net>
<net name="RF_CON" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="RF_IN"/>
<wire x1="81.28" y1="-190.5" x2="83.82" y2="-190.5" width="0.1524" layer="91" grouprefs="GNSS"/>
<label x="83.82" y="-190.5" size="1.27" layer="95" xref="yes" grouprefs="GNSS"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="RF_OUT"/>
<wire x1="27.94" y1="-228.6" x2="25.4" y2="-228.6" width="0.1524" layer="91" grouprefs="GNSS"/>
<label x="25.4" y="-228.6" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="GNSS"/>
</segment>
</net>
<net name="LEFT_AMP_OUT_P" class="0">
<segment>
<pinref part="J4" gate="G$1" pin="1"/>
<wire x1="210.82" y1="91.44" x2="208.28" y2="91.44" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="208.28" y="91.44" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="FB4" gate="G$1" pin="2"/>
<wire x1="261.62" y1="-104.14" x2="264.16" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C27" gate="G$1" pin="1"/>
<wire x1="264.16" y1="-104.14" x2="266.7" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="264.16" y1="-106.68" x2="264.16" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="264.16" y="-104.14" grouprefs="AMP_SOUND"/>
<label x="266.7" y="-104.14" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
</net>
<net name="LEFT_AMP_OUT_N" class="0">
<segment>
<pinref part="J4" gate="G$1" pin="2"/>
<wire x1="210.82" y1="88.9" x2="208.28" y2="88.9" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="208.28" y="88.9" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
<segment>
<pinref part="FB3" gate="G$1" pin="2"/>
<wire x1="261.62" y1="-101.6" x2="264.16" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C28" gate="G$1" pin="1"/>
<wire x1="264.16" y1="-101.6" x2="266.7" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="264.16" y1="-96.52" x2="264.16" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="264.16" y="-101.6" grouprefs="AMP_SOUND"/>
<label x="266.7" y="-101.6" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="!SD_MODE"/>
<wire x1="119.38" y1="-104.14" x2="116.84" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="116.84" y1="-104.14" x2="116.84" y2="-109.22" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="R2" gate="G$1" pin="2"/>
</segment>
</net>
<net name="DIN" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DIN"/>
<wire x1="119.38" y1="-96.52" x2="116.84" y2="-96.52" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="116.84" y="-96.52" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="DIN"/>
<wire x1="208.28" y1="-96.52" x2="205.74" y2="-96.52" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="205.74" y="-96.52" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO45"/>
<wire x1="195.58" y1="50.8" x2="198.12" y2="50.8" width="0.1524" layer="91"/>
<label x="198.12" y="50.8" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="LRCLK" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="LRCLK"/>
<wire x1="142.24" y1="-71.12" x2="142.24" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="142.24" y1="-68.58" x2="144.78" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="144.78" y="-68.58" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="LRCLK"/>
<wire x1="231.14" y1="-71.12" x2="231.14" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="231.14" y1="-68.58" x2="233.68" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="233.68" y="-68.58" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="MK1" gate="G$1" pin="WS"/>
<wire x1="111.76" y1="25.4" x2="114.3" y2="25.4" width="0.1524" layer="91" grouprefs="MIC"/>
<label x="114.3" y="25.4" size="1.27" layer="95" xref="yes" grouprefs="MIC"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="IO3"/>
<wire x1="162.56" y1="15.24" x2="160.02" y2="15.24" width="0.1524" layer="91"/>
<label x="160.02" y="15.24" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="BCLK" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="BCLK"/>
<wire x1="137.16" y1="-71.12" x2="137.16" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="137.16" y1="-68.58" x2="134.62" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="134.62" y="-68.58" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="IC8" gate="G$1" pin="BCLK"/>
<wire x1="226.06" y1="-71.12" x2="226.06" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="226.06" y1="-68.58" x2="223.52" y2="-68.58" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<label x="223.52" y="-68.58" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="MK1" gate="G$1" pin="SCK"/>
<wire x1="111.76" y1="20.32" x2="114.3" y2="20.32" width="0.1524" layer="91" grouprefs="MIC"/>
<label x="114.3" y="20.32" size="1.27" layer="95" xref="yes" grouprefs="MIC"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="RXD0"/>
<wire x1="195.58" y1="25.4" x2="198.12" y2="25.4" width="0.1524" layer="91"/>
<label x="198.12" y="25.4" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="OUTN"/>
<wire x1="160.02" y1="-101.6" x2="162.56" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="FB1" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="OUTP"/>
<wire x1="160.02" y1="-104.14" x2="162.56" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="FB2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="RIGHT_AMP_OUT_N" class="0">
<segment>
<pinref part="FB1" gate="G$1" pin="2"/>
<wire x1="172.72" y1="-101.6" x2="175.26" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C24" gate="G$1" pin="1"/>
<wire x1="175.26" y1="-101.6" x2="177.8" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="175.26" y1="-96.52" x2="175.26" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="175.26" y="-101.6" grouprefs="AMP_SOUND"/>
<label x="177.8" y="-101.6" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="3"/>
<wire x1="210.82" y1="86.36" x2="208.28" y2="86.36" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="208.28" y="86.36" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
</net>
<net name="RIGHT_AMP_OUT_P" class="0">
<segment>
<pinref part="FB2" gate="G$1" pin="2"/>
<wire x1="172.72" y1="-104.14" x2="175.26" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="C23" gate="G$1" pin="1"/>
<wire x1="175.26" y1="-104.14" x2="177.8" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<wire x1="175.26" y1="-106.68" x2="175.26" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<junction x="175.26" y="-104.14" grouprefs="AMP_SOUND"/>
<label x="177.8" y="-104.14" size="1.27" layer="95" xref="yes" grouprefs="AMP_SOUND"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="4"/>
<wire x1="210.82" y1="83.82" x2="208.28" y2="83.82" width="0.1524" layer="91" grouprefs="CONNECTORS"/>
<label x="208.28" y="83.82" size="1.27" layer="95" rot="R180" xref="yes" grouprefs="CONNECTORS"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="IC8" gate="G$1" pin="OUTN"/>
<wire x1="248.92" y1="-101.6" x2="251.46" y2="-101.6" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="FB3" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="IC8" gate="G$1" pin="OUTP"/>
<wire x1="248.92" y1="-104.14" x2="251.46" y2="-104.14" width="0.1524" layer="91" grouprefs="AMP_SOUND"/>
<pinref part="FB4" gate="G$1" pin="1"/>
</segment>
</net>
<net name="MIC_SD" class="0">
<segment>
<pinref part="MK1" gate="G$1" pin="SD"/>
<wire x1="111.76" y1="22.86" x2="127" y2="22.86" width="0.1524" layer="91" grouprefs="MIC"/>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="127" y1="22.86" x2="129.54" y2="22.86" width="0.1524" layer="91" grouprefs="MIC"/>
<wire x1="127" y1="20.32" x2="127" y2="22.86" width="0.1524" layer="91" grouprefs="MIC"/>
<junction x="127" y="22.86" grouprefs="MIC"/>
<label x="129.54" y="22.86" size="1.27" layer="95" xref="yes" grouprefs="MIC"/>
</segment>
<segment>
<pinref part="IC5" gate="G$1" pin="TXD0"/>
<wire x1="195.58" y1="22.86" x2="198.12" y2="22.86" width="0.1524" layer="91"/>
<label x="198.12" y="22.86" size="1.27" layer="95" xref="yes" grouprefs="ESP32"/>
</segment>
</net>
<net name="GND1" class="0">
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S33" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S34" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S35" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S36" class="0">
<segment>
</segment>
</net>
<net name="S37" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S38" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S39" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S40" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S41" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="S42" class="0">
<segment>
</segment>
</net>
<net name="S43" class="0">
<segment>
</segment>
</net>
<net name="S44" class="0">
<segment>
</segment>
</net>
<net name="S45" class="0">
<segment>
</segment>
</net>
<net name="S46" class="0">
<segment>
</segment>
</net>
<net name="S47" class="0">
<segment>
</segment>
</net>
<net name="S48" class="0">
<segment>
</segment>
</net>
<net name="S49" class="0">
<segment>
</segment>
</net>
<net name="S50" class="0">
<segment>
</segment>
</net>
<net name="S51" class="0">
<segment>
</segment>
</net>
<net name="S52" class="0">
<segment>
</segment>
</net>
<net name="S53" class="0">
<segment>
</segment>
</net>
<net name="S54" class="0">
<segment>
</segment>
</net>
<net name="S55" class="0">
<segment>
</segment>
</net>
<net name="S56" class="0">
<segment>
</segment>
</net>
<net name="S57" class="0">
<segment>
</segment>
</net>
<net name="VCC1" class="0">
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
</net>
<net name="D+1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="D-1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="VCC_5V1" class="0">
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
</net>
<net name="VCC_3.3V1" class="0">
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
</net>
<net name="RESET1" class="0">
<segment>
</segment>
</net>
<net name="BOOT1" class="0">
<segment>
</segment>
</net>
<net name="S58" class="0">
<segment>
</segment>
</net>
<net name="S59" class="0">
<segment>
</segment>
</net>
<net name="S60" class="0">
<segment>
</segment>
</net>
<net name="S61" class="0">
<segment>
</segment>
</net>
<net name="S62" class="0">
<segment>
</segment>
</net>
<net name="S63" class="0">
<segment>
</segment>
</net>
<net name="S64" class="0">
<segment>
</segment>
</net>
<net name="SDA1" class="0">
<segment>
</segment>
</net>
<net name="SCL1" class="0">
<segment>
</segment>
</net>
<net name="VCC_1.2V1" class="0">
<segment>
</segment>
</net>
<net name="VCC_2.8V1" class="0">
<segment>
</segment>
</net>
<net name="CAM_SDA1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="CAM_SCL1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="CAM_RST1" class="0">
<segment>
</segment>
</net>
<net name="VSYNC1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="HREF1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="XCLK1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA10" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA11" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="PCLK1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA12" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA13" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA14" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA15" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="DATA16" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="SD_MISO1" class="0">
<segment>
</segment>
</net>
<net name="SD_SCK1" class="0">
<segment>
</segment>
</net>
<net name="SD_MOSI1" class="0">
<segment>
</segment>
</net>
<net name="TFT_SCK1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="TFT_MOSI1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="TFT_RES1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="TFT_DC1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="TFT_CS1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="BNO085_RX1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="TFT_BL1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="N$1" class="0">
<segment>
</segment>
</net>
<net name="N$4" class="0">
<segment>
</segment>
</net>
<net name="N$6" class="0">
<segment>
</segment>
</net>
<net name="H_SCL1" class="0">
<segment>
</segment>
</net>
<net name="H_CSN1" class="0">
<segment>
</segment>
</net>
<net name="H_MOSI1" class="0">
<segment>
</segment>
</net>
<net name="BOOTN1" class="0">
<segment>
</segment>
</net>
<net name="NRST1" class="0">
<segment>
</segment>
</net>
<net name="ENV_SDA1" class="0">
<segment>
</segment>
</net>
<net name="ENV_SCL1" class="0">
<segment>
</segment>
</net>
<net name="CAM_PWDN1" class="0">
<segment>
</segment>
</net>
<net name="SWDIO1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="SWCLK1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="LEFT_AMP_OUT_P1" class="0">
<segment>
</segment>
</net>
<net name="LEFT_AMP_OUT_N1" class="0">
<segment>
</segment>
</net>
<net name="N$9" class="0">
<segment>
</segment>
</net>
<net name="DIN1" class="0">
<segment>
</segment>
<segment>
</segment>
</net>
<net name="LRCLK1" class="0">
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
</net>
<net name="BCLK1" class="0">
<segment>
</segment>
<segment>
</segment>
<segment>
</segment>
</net>
<net name="N$10" class="0">
<segment>
</segment>
</net>
<net name="N$11" class="0">
<segment>
</segment>
</net>
<net name="RIGHT_AMP_OUT_N1" class="0">
<segment>
</segment>
</net>
<net name="RIGHT_AMP_OUT_P1" class="0">
<segment>
</segment>
</net>
<net name="N$15" class="0">
<segment>
</segment>
</net>
<net name="N$16" class="0">
<segment>
</segment>
</net>
<net name="MIC_SD1" class="0">
<segment>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
<note version="9.5" severity="warning">
Since Version 9.5, EAGLE supports persistent groups with
schematics, and board files. Those persistent groups
will not be understood (or retained) with this version.
</note>
<note version="8.4" severity="warning">
Since Version 8.4, EAGLE supports properties for SPICE simulation. 
Probes in schematics and SPICE mapping objects found in parts and library devices
will not be understood with this version. Update EAGLE to the latest version
for full support of SPICE simulation. 
</note>
</compatibility>
</eagle>

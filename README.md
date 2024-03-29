# Antenna Switch Control via Browser
Remote antenna switch controller using ESP8266 for a 4-port switch.  This is the software logic for a controller for a switch consisting of relays, board and connectors. A hardware kit for the switch itself is sourced from eBay.  The better ones are from the Czech Republic.

Most likely, the switch kit will operate on 12 volts, i.e. it will have 12v relays and require 12v signals to activate the relays.  You will need a driver board to convert the 3v logic of the ESP8266 to drive 12v signals required by the switch.  The easiest way to do this is to use a DC motor driver board commonly used in robots (see components list below).

The controller is a lightweight web server, hence the user interface is accessed via web browser.  The controller web server supports one simultaneous user.

<br>

***
<br>

## Antenna Selector Web Interface
<br>
The web page is shown below with a Flag Pole Antenna selected.  Antenna labels can be easily changed in the code.  Selecting one antenna will disable all others to prevent multiple antenna activation.  However, antennas can be indivdually deactivated so that all antennas can be disconnected.
<br><br>

![Antenna Selector UI](images/Antenna%20Selector.jpg)

<br>

***
<br>

## Switch Components

<br>

- Qty1 - Switch enclosure - https://www.amazon.com/gp/product/B07KYDVH4T/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
- Qty 1 set of 5 - SO-239 connectors - https://www.amazon.com/dp/B08JCCLK4C/ref=sspa_dk_detail_4?psc=1&pd_rd_i=B08JCCLK4C&pd_rd_w=xDNhf&pf_rd_p=0c758152-61cd-452f-97a6-17f070f654b8&pd_rd_wg=yPvdV&pf_rd_r=S8AN87KDCN369QPEGA8J&pd_rd_r=c6ed74ab-e185-4db9-b44c-d51286797beb&s=industrial&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyUUZZUktRUVBLUVlWJmVuY3J5cHRlZElkPUEwMjQ3MzAzMkM2SElSNFQ1TFpDTCZlbmNyeXB0ZWRBZElkPUEwMjE3ODcyMzVZM01CSjZTVzdBVyZ3aWRnZXROYW1lPXNwX2RldGFpbCZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=
- Qty 1 - 4:1 switch kit shown - available on eBay. Links to eBay items change too quickly for me to provide one. I can't vouch for every kit sold on eBay, but I've had no problems with the kit matching th picture shown below.  
<br><br>

![Switch Kit](images/Switch%20Kit.jpg)


<br>

***
<br>

## Controller Components

<br>

- Qty1 - WeMos D1 Mini ESP8266 board - https://smile.amazon.com/HiLetgo-NodeMcu-Development-ESP8266-Compatiable/dp/B073CQVFLK?ref_=ast_sto_dp
- Qty1 - 12v to 5v Buck Converter (adjust to 5v output) - https://smile.amazon.com/HiLetgo-LM2596S-ADJ-Module-Regulator-Adjustable/dp/B00LTSC564?ref_=ast_sto_dp
- Qty 1 - Relay voltage conversion & PNP output driver board - https://smile.amazon.com/dp/B07TCW947L?ref=ppx_yo2ov_dt_b_product_details&th=1
- Qty 1 - 12VDC 3A power supply
- Connectors needed for 12v power
- Connectors for interconnection of controller and switch assemblies
- 3D printing files for enclosure in 3D_Printed_Enclosure directory
<br><br>

![Controller in Enclosure](images/Controller%20in%20enclosure.jpg)

<br>

Note pull down resistor assembly at upper right.  All resistors are 10K ohm.

<br>

***
<br>

## The Finished Project

<br>

![Completed Project](images/Finished%20Project.jpg)

<br>

Picture shows my previous generation controller that had a smaller electronics enclosure, but you get the idea.

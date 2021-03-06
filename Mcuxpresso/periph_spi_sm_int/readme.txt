LPC5411x SPI master and slave example using spim (master) and spis (slave) drivers
==================================================================================

Example description
-------------------
This example shows how to use the SPI master and slave drivers in a non-DMA interrupt
driven configuration. The master will send and recceive data back from the slave. Both
the SPI master (spim) and slave (spis) are used simultaneoulsy with this example on
different SPI controllers.

The example sends and receive data between the 2 SPI controllers on the device. After
the data is transferred, it is displayed.

Make sure JP-6 is fitted to use the PMOD SPI port.

The interrupt functions are slow considering the speed of the SPI port.
If more than a FIFO of data is transferred, the demo will overflow the RX FIFO.
This is because both SPI ports are on the same device.

Special connection requirements
-------------------------------
SPI0 - FC5								SPI1 - FC3
SSEL  (J1-15) P1_1 / FC5 SSEL2		SSEL (J4-1) P0_14 / FC3 SSELN0
MOSI  (J1-13) P0_20 / FC5 MOSI		MOSI (J4-2) P0_12 / FC3 MOSI
MISO  (J1-11) P0_18 / FC5 MISO		MISO (J4-3) P0_13 / FC3 MISO
SCK   (J1-9)  P0_19 / FC5 SCK		SCK  (J4-4) P0_11 / FC3 SCK

Build procedures:
-----------------
Visit the at 'LPCOpen quickstart guides' [http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides]
to get started building LPCOpen projects.

Optionally, you can enable loopback mode to wrap master TX data back to master RX
and slave TX data back to slave RX. This won't work unless you connect the master
slave controller's SSEL and clock lines.

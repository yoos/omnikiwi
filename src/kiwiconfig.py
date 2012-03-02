#!/usr/bin/env python
# -*- coding: utf-8 -*-

# =============================================================================
# Communication
# =============================================================================

# General
#serialPort = "/dev/ttyUSB0"   # Uncomment to specify serial port. Otherwise, will connect to first available port.
baudRate = 57600

# TX
dataSendInterval = 0.040   # 40 ms interval = 25 hz. NOTE: This frequency should be LOWER than the microcontroller's communications loop frequency!
dogFeedInterval = 0.1
serHeader = chr(255)
dogBone = chr(254)

# RX
newlineSerTag  = '\xde\xad\xbe\xef'
fieldSerTag    = '\xff\xff'
sensorSerTag   = '\xfb'
rotationSerTag = '\xfc'
motorSerTag    = '\xfd'
pidSerTag      = '\xfe'


# Joystick axis sign flips.
axisSigns = [-1, 1, 1, 1, -1, 1]

# Joystick axis indices.
axisX = 0
axisY = 1
axisT = 2
axisZ = 3


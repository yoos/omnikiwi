#!/usr/bin/env python

# =============================================================================
# serialmon.py
# =============================================================================

import serial
import string
from time import sleep
import threading
from threading import Timer, Thread
from signal import signal, SIGINT

# ROS stuff
import roslib; roslib.load_manifest("tricopter")
import rospy
from omnikiwi.msg import Telemetry

import kiwiconfig as cfg   # Import config.

# =============================================================================
# Telemetry data
# =============================================================================

# Initial DCM values.
ledReadings = [0.0] * 6

# Target rotation values
targetRot = [0.0] * 3

# Motor/servo values (MT, MR, ML)
motorVal = [0.0] * 3

# PID data
pidData = [0.0] * 3


class telemetryThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.running = True
    def run(self):
        global ledReadings, targetRot, motorVal, pidData
        sensorDataIndex = 0       # Do I see IMU data?
        rotationDataIndex = 0       # Do I see rotation data?
        motorDataIndex = 0     # Do I see motor data?
        pidDataIndex = 0     # Do I see PID data?
        serBuffer = ''
        serLines = ''

        while self.running and not rospy.is_shutdown():
            try:
                if ser.inWaiting() > 0:
                    # =========================================================
                    # Update buffer, adding onto incomplete line if necessary.
                    # =========================================================
                    serBuffer = serBuffer + ser.read(ser.inWaiting())

                    # =========================================================
                    # Check for separator tag and split one entry off buffer.
                    # =========================================================
                    if cfg.newlineSerTag in serBuffer:
                        serLines = serBuffer.split(cfg.newlineSerTag)

                        # Parse fields separated by 0xf0f0.
                        fields = serLines[-2].split(cfg.fieldSerTag)

                        # Save second to last line and discard rest.
                        serBuffer = serLines[-1]

                    # =========================================================
                    # Scan for data field headers.
                    # TODO: Move this someplace else so it's run only once.
                    # =========================================================
                    for i in range(1, len(fields)):
                        if not sensorDataIndex and fields[i][0] == cfg.sensorSerTag:
                            sensorDataIndex = i
                        elif not rotationDataIndex and fields[i][0] == cfg.rotationSerTag:
                            rotationDataIndex = i
                        elif not motorDataIndex and fields[i][0] == cfg.motorSerTag:
                            motorDataIndex = i
                        elif not pidDataIndex and fields[i][0] == cfg.pidSerTag:
                            pidDataIndex = i

                    # =========================================================
                    # Check if we're receiving sensor data.
                    # =========================================================
                    if sensorDataIndex:
                        try:
                            for i in range(6):
                                ledReadings[i] = float(int(fields[sensorDataIndex][i+1:i+2].encode('hex'), 16)*1024.0)/250.0
                        except Exception, e:
                            print "SEN:", str(e)

                    # =========================================================
                    # Check if we're receiving target rotation data.
                    # =========================================================
                    if rotationDataIndex:
                        try:
                            for i in range(3):
                                targetRot[i] = float(int(fields[rotationDataIndex][i+1:i+2].encode('hex'), 16)-1)/250*2*pi-pi
                                #targetRot[i] = struct.unpack('f', fields[rotationDataIndex][3+i*4:3+i*4+4])[0]
                        except Exception, e:
                            print "ROT:", str(e)

                    # =========================================================
                    # Check if we're receiving motor/servo output data.
                    # =========================================================
                    if motorDataIndex:
                        try:
                            for i in range(3):
                                motorVal[i] = int(fields[motorDataIndex][i+1:i+2].encode('hex'), 16)
                                #motorVal[i] = struct.unpack('f', fields[motorDataIndex][3+i*4:3+(i+1)*4])[0]
                        except Exception, e:
                            print "MTR:", str(e)


                    # =========================================================
                    # Check if we're receiving PID gains and values.
                    # =========================================================
                    if pidDataIndex:
                        try:
                            for i in range(3):
                                pidData[i] = int(fields[pidDataIndex][i+1:i+2].encode('hex'), 16)
                        except Exception, e:
                            print "PID:", str(e)

                    # =========================================================
                    # Printout
                    # =========================================================
                    #print fields
                    #print [dcm, fields[-1]]
                    print "Move counter:", int(fields[0].encode('hex'), 16)
                    print "Motors:      ", motorVal
                    print "LED readings:", ledReadings
                    print "Loop time:   ", fields[-1]
                    print "\n--\n"

                    pub.publish(Telemetry(ledReadings[0],
                                          ledReadings[1],
                                          ledReadings[2],
                                          ledReadings[3],
                                          ledReadings[4],
                                          ledReadings[5],
                                          motorVal[0],
                                          motorVal[1],
                                          motorVal[2],
                                          pidData[0],
                                          pidData[1],
                                          pidData[2]))

            except:
                pass
            rospy.sleep(0.005)


###############################################################################

if __name__ == "__main__":
    # Initialize ROS node.
    rospy.init_node("tricopter_receiver", anonymous=False)
    pub = rospy.Publisher("telemetry", Telemetry)

    # =========================================================================
    # Try to initialize a serial connection. If serialPort is defined, try
    # opening that. If it is not defined, loop through a range of integers
    # starting from 0 and try to connect to /dev/ttyUSBX where X is the
    # integer. In either case, process dies if serial port cannot be opened.
    #
    # TODO: This needs to be made more concise.
    # =========================================================================
    try:
        ser = serial.Serial(cfg.serialPort, cfg.baudRate, timeout=0)
    except serial.SerialException:
        rospy.logerr("[SM] Unable to open specified serial port! Exiting...")
        exit(1)
    except AttributeError:
        for i in range(4):
            try:
                ser = serial.Serial("/dev/ttyUSB"+str(i), cfg.baudRate, timeout=0)
                rospy.loginfo("[SM] Opened serial port at /dev/ttyUSB%d.", i)
                break
            except serial.SerialException:
                rospy.logerr("[SM] No serial at /dev/ttyUSB%d.", i)
                if i == 3:
                    rospy.logerr("[SM] No serial found. Giving up!")
                    exit(1)

    try:
        telemetry = telemetryThread()
        telemetry.start()
        raw_input("Hit <enter> to quit.")

        # Stop the loops.
        telemetry.running = False

        # Wait for threads to finish jobs.
        telemetry.join()

    except rospy.ROSInterruptException:
        pass


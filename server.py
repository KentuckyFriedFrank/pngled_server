#bin/python
import argparse
parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('--fn', dest='filename',action="store", type=str, help="filename")
parser.add_argument('--baud', dest='baud',action="store",default='115200', type=int, help="baud")
args = parser.parse_args()

import numpy
import serial
from serial.tools import list_ports
import time
from PIL import Image
from twisted.internet import reactor

class Player(object):
        def __init__(self, imagePath, frameOutClosure):
                self.imagePath = imagePath
                self.out = frameOutClosure
                self.fps = 30
                self.reloadImage()

        def reloadImage(self):
                print "reloading %s" % self.imagePath
                i = Image.open(self.imagePath).convert('RGB')
                self.image = numpy.asarray(i)
                print self.image.shape

        def step(self):
                now = time.time()
                frameNum = int ((now * self.fps) % self.image.shape[1])
                frame = self.image[::-1,frameNum,:]
                self.out(frame)

if __name__ == "__main__":
        filename = args.filename
        ports = [port[0] for port in list_ports.comports()]
        print "Using serial port %s; found %s" % (ports[-1], ports)
        port = serial = serial.Serial(ports[-1],baudrate=args.baud, timeout=0, writeTimeout=1)

        def frameOut(colors):
                foo = colors.copy(order='C')
                port.write(str.encode('*'))
                print('* ', len(foo))
                print(foo)
                port.write(foo)
        player = Player(filename, frameOut)

        def loop():
                player.step()
                reactor.callLater(0.01, loop)
				
        loop()
        reactor.run()

import Image
import sys
import math
import struct

Bits = 3


def fileToPng(source, target):
    data = open(source, "rb").read()
    fileSize = len(data)
    data += "\0\0\0"

    # Keep Ratio 4:3
    width = int(math.sqrt(float(fileSize) / Bits * 4 / 3)) + 1
    height = int((fileSize/Bits) / width) + 1
    if width * height * Bits < fileSize:
        raise Exception("File too large")
    if width == 0 or height == 0:
        raise Exception("File too small.")

    im = Image.new("RGB", (width, height))
    pngData = tuple(tuple(map(ord, [y for y in data[x: x+Bits]]))
                    for x in xrange(0, fileSize, Bits))
    im.putdata(pngData)
    im.save(target, "PNG", transparency=struct.unpack(
        "B"*Bits, struct.pack("I", fileSize)[:Bits]), compression=9)

    del im, pngData


def pngToFile(source, target):
    im = Image.open(source)
    fileSize = struct.unpack("I",
                             struct.pack("B"*Bits, *im.info["transparency"]) + "\0"*(4-Bits))[0]
    # "".join(["".join(map(chr, x)) for x in im.getdata()])
    data = im.tostring()[:fileSize]
    open(target, "wb").write(data)
    del data, im


if __name__ == "__main__":
    if sys.argv[1] == "c":
        fileToPng(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == "x":
        pngToFile(sys.argv[2], sys.argv[3])
    else:
        print "file2png [c|x] file1 file2"

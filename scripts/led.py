import minimalmodbus
import sys

instr = minimalmodbus.Instrument(sys.argv[1], 5)
instr.serial.baudrate = 9600  # Baud
instr.serial.bytesize = 8
instr.serial.parity   = 'E'
instr.serial.stopbits = 1
instr.serial.timeout = 0.2
print(instr)
instr.write_register(int(sys.argv[2]), int(sys.argv[3]))

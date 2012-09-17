#!/usr/bin/env python


import socket, struct




s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 9123))

try:
	while True:
		line = raw_input( ">" )
		parts = line.split()
		if parts[0] == "SET":
			if parts[1] == "A":
				value = int( parts[2] )
				s.send( struct.pack( "<BBBBB", 0, value, 0, 0, 0 ) )
			if parts[1] == "B":
				value = int( parts[2] )
				s.send( struct.pack( "<BBBBB", 1, value, 0, 0, 0 ) )

		if parts[0] == "GET":
			if parts[1] == "A":
				s.send( struct.pack( "<BBBBB", 2, 0, 0, 0, 0 ) )
				data = s.recv( 5 )
				print struct.unpack( "<BBBBB", data )
			if parts[1] == "B":
				s.send( struct.pack( "<BBBBB", 3, 0, 0, 0, 0 ) )
				data = s.recv( 5 )
				print struct.unpack( "<BBBBB", data )
				
except KeyboardInterrupt:
	pass

s.close()

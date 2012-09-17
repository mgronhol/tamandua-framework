#!/usr/bin/env python


import sys


class Feed( object ):
	def __init__( self, entries ):
		self.entries = entries
		self.pos = 0
	
	def peek( self ):
		return self.entries[self.pos]
	
	def skip( self ):
		self.pos += 1
	
	def next( self ):
		out = self.entries[self.pos]
		self.pos += 1
		return out
	
	def add( self, entry ):
		self.entries.append( entry )

	def empty( self ):
		return not ( self.pos < len( self.entries ) )

def EventsParser( feed ):
	events_feed = Feed([])
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	entry = feed.next()
	while entry != "}":
		events_feed.add( entry )
		entry = feed.next()
	out = {}
	while not events_feed.empty():
		event_name = events_feed.next()
		arrow = events_feed.next()
		func = events_feed.next()
		if arrow != "->":
			raise SyntaxError
		if not func.endswith(";"):
			if events_feed.peek() != ';':
				raise SyntaxError
			else:
				events_feed.skip()
		func = func.replace( ";", "" )
		out[event_name] = func
	#print out
	
	return out

def ConditionParser( feed ):
	cond_feed = Feed([])
	name = feed.next()
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	entry = feed.next()
	while entry != "}":
		cond_feed.add( entry )
		entry = feed.next()
	out = {}
	while not cond_feed.empty():
		addr = cond_feed.next()
		state = cond_feed.next()
		if not state.endswith( ";" ):
			if cond_feed.peek() != ";":
				raise SyntaxError
			else:
				cond_feed.skip()
		state = state.replace( ";", "" )
		(port, pin) = addr.split( ":" )
		if port not in out:
			out[port] = {}
		if state not in out[port]:
			out[port][state] = set()

		out[port][state].add( pin )
	return (name, out)
	
def OnEmitParser( feed ):
	name = feed.next()
	emit = feed.next()
	if emit != "emit":
		raise SyntaxError
	
	events = set()
	event = feed.next()
	events.add( event.replace( ";", "" ) )
	#print "event", event
	if not event.endswith( ";" ):
		event = feed.next()
		#print "event", event
		if event != ";":
			events.add( event.replace( ";", "" ) )
	
	return (name, events)

def WorkflowParser( feed ):
	out = []
	name = feed.next()
	wf_feed = Feed([])
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	entry = feed.next()
	while entry != "}":
		wf_feed.add( entry )
		entry = feed.next()
	
	while not wf_feed.empty():
		step = wf_feed.next()
		if step == ";":
			break
		elif step.endswith( ";" ):
			if not wf_feed.empty():
				raise SyntaxError
			out.append( step.replace( ";", "" ) )
			break
		out.append( step.replace( ";", "" ) )
		arrow = wf_feed.next()
		if arrow != "->":
			raise SyntaxError
		else:
			continue
		

	return (name, out)

def InputConfigParser( feed ):
	out = {}
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	while True:
		entry = feed.next()
		if entry == "}":
			break
		if not entry.endswith( ";" ):
			if entry.peek() != ";":
				raise SyntaxError
			else:
				feed.skip()
		(port, pin) = entry.split(":")
		if port not in out:
			out[port] = set()
		out[port].add( pin.replace( ";", "" ) )
		
	return out

def OutputConfigParser( feed ):
	out = {}
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	while True:
		entry = feed.next()
		if entry == "}":
			break
		if not entry.endswith( ";" ):
			if feed.peek() != ";":
				raise SyntaxError
			feed.skip()
		(port, pin) = entry.split(":")
		if port not in out:
			out[port] = set()
		out[port].add( pin.replace( ";", "") )
		
	return out

def PeripheralsConfigParser( feed ):
	out = {}
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	while True:
		entry = feed.next()
		if entry == "}":
			break
		value = feed.next()
		if not value.endswith( ";" ):
			if feed.peek() != ";":
				raise SyntaxError
			else:
				feed.skip()
		out[entry] = value.replace( ";", "" ) == "on"
		
	return out

def ConfigureParser( feed ):
	out = {}
	c_feed = Feed([])
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	cnt = 1
	while cnt > 0:
		entry = feed.next()
		if entry == "{":
			cnt += 1
		if entry == "}":
			cnt -= 1
		if cnt > 0:
			c_feed.add( entry )

	while not c_feed.empty():
		section = c_feed.next()
		if section == "input":
			out['input'] = InputConfigParser( c_feed )
		elif section == "output":
			out['output'] = OutputConfigParser( c_feed )
		elif section == "peripherals":
			out['peripherals'] = PeripheralsConfigParser( c_feed )
		else:
			raise SyntaxError
	return out


def RunParser( feed ):
	out = []
	entry = feed.next()
	if entry != "{":
		raise SyntaxError
	entry = feed.next()
	while entry != "}":
		out.append( entry.replace( ";", "" ) )
		entry = feed.next()
	return out



lines = []

tokens = []

for line in open( sys.argv[1] ):
	if "//" in line:
		line = line[:line.find("//")]
	
	line = line.strip()
	if len( line ) < 1:
		continue
	#print line
	lines.append( line )
	tokens.extend( line.split() )


#print tokens
feed = Feed( tokens )

out = {}
while not feed.empty():
	entry = feed.next()
	print "main", entry
	if entry == "events":
		out['events'] = EventsParser( feed )
	elif entry == "condition":
		if 'conditions' not in out:
			out['conditions'] = {}
		(key, cond) = ConditionParser( feed )
		out['conditions'][key] = cond
	elif entry == "on":
		if 'emissions' not in out:
			out['emissions'] = {}

		(key, events) = OnEmitParser( feed )
		if key not in out['emissions']:
			out['emissions'][key] = []
		out['emissions'][key].append( events )
	elif entry == "workflow":
		if "workflows" not in out:
			out['workflows'] = {}
		(key, flow) = WorkflowParser( feed )
		out['workflows'][key] = flow
	elif entry == "configure":
		out['configuration'] = ConfigureParser( feed )
	elif entry == "run":
		out['main_loop'] = RunParser( feed )
	else:
		break

import pprint


pprint.pprint( out )

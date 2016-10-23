from OSC import OSCServer,OSCClient, OSCMessage
import sys
from time import sleep
import types
sys.path.insert(0, '/usr/lib/python2.7/bridge/') # make sure python can see the tcp module

from tcp import TCPJSONClient

# use this to get the ip of the current wlan interface
from tools import get_ip
										 
#set up the json client and the osc client and server. The server should have the ip of your Yun. 
#The client.connect should have the ip address of you phone. 
json = TCPJSONClient('127.0.0.1', 5700)
server = OSCServer( (get_ip("wlan0"), 8000) )
client = OSCClient()

#waits for data
def handle_timeout(self):
	print ("Awaiting data...")

server.handle_timeout = types.MethodType(handle_timeout, server)

# Adding functionality for the "light" fader:
def faderLight_callback(path, tags, args, source):
	global faderLightFeedback
	if path=="/self/light":
		#extract parameter:
		faderLightFeedback = int(args[0])
		#put parameter to the bridge:
		json.send({'command':'put', 'key':'light', 'value':'%i' % (faderLightFeedback)})		
		print "received: " +repr(source)+ " " + str(path) + " " + str(faderLightFeedback)
		#create feedback for faders label:
		msg = OSCMessage("/self/label_light")		
		msg.insert(0, faderLightFeedback)
		client.connect( (source[0], 9000) )
		client.send(msg)
server.addMsgHandler( "/self/light",faderLight_callback) #register function for handling "fader" control

# Adding functionality for the "sequential_value" fader:
def faderSequential_callback(path, tags, args, source):
	global faderSequentialFeedback
	if path=="/self/sequential_value":
		#extract parameter:
		faderSequentialFeedback = int(args[0])	
		#put parameter to the bridge:	
		json.send({'command':'put', 'key':'sequential_value', 'value':'%i' % (faderSequentialFeedback)})	
		#create feedback for faders label:	
		msg = OSCMessage("/self/label_Sequential")
		msg.insert(0, faderSequentialFeedback)
		client.connect( (source[0], 9000) )
		client.send(msg)
		print "received: " +repr(source)+ " " + str(path) + " " + str(faderSequentialFeedback)
server.addMsgHandler( "/self/sequential_value",faderSequential_callback)

# Adding functionality for the "sequential_toggle" button:
def toggleSequential_callback(path, tags, args, source):
	global toggleSequentialFeedback
	if path=="/self/sequential_toggle":
		#extract parameter:
		toggleSequentialFeedback = int(args[0])	
		#put parameter to the bridge:	
		json.send({'command':'put', 'key':'sequential_toggle', 'value':'%i' % (toggleSequentialFeedback)})	
		print "received: " +repr(source)+ " " + str(path) + " " + str(toggleSequentialFeedback)
server.addMsgHandler( "/self/sequential_toggle",toggleSequential_callback)


# Adding functionality for the "bpmfade_value" fader:
def faderbpmfade_callback(path, tags, args, source):
	global faderbpmfadeFeedback
	if path=="/self/bpmfade_value":
		#extract parameter:
		faderbpmfadeFeedback = int(args[0])	
		#put parameter to the bridge:	
		json.send({'command':'put', 'key':'bpmfade_value', 'value':'%i' % (faderbpmfadeFeedback)})	
		#create feedback for faders label:	
		msg = OSCMessage("/self/label_bpmfade")
		msg.insert(0, faderbpmfadeFeedback)
		client.connect( (source[0], 9000) )
		client.send(msg)
		print "received: " +repr(source)+ " " + str(path) + " " + str(faderbpmfadeFeedback)
server.addMsgHandler( "/self/bpmfade_value",faderbpmfade_callback)

# Adding functionality for the "bpmfade_toggle" button:
def togglebpmfade_callback(path, tags, args, source):
	global togglebpmfadeFeedback
	if path=="/self/bpmfade_toggle":
		#extract parameter:
		togglebpmfadeFeedback = int(args[0])	
		#put parameter to the bridge:	
		json.send({'command':'put', 'key':'bpmfade_toggle', 'value':'%i' % (togglebpmfadeFeedback)})	
		print "received: " +repr(source)+ " " + str(path) + " " + str(togglebpmfadeFeedback)
server.addMsgHandler( "/self/bpmfade_toggle",togglebpmfade_callback)

def bing1_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source)
	json.send({'command':'put', 'key':'bing1', 'value':'255' })
server.addMsgHandler("/self/bing/1/1", bing1_callback)

def bing2_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source)
	json.send({'command':'put', 'key':'bing2', 'value':'255' })
server.addMsgHandler("/self/bing/2/1", bing2_callback)

def bing1_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source)
	json.send({'command':'put', 'key':'bing3', 'value':'255' })
server.addMsgHandler("/self/bing/3/1", bing1_callback)

############################################################################
# Mode1 and palette1
def multiselectMode1_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source) 
	split = path.split("/")
	state = split.pop()
	state = split.pop()
	if args[0]==1:
		#requests.get("http://192.168.1.104/arduino/state/"+str(int(state)-1))
		json.send({'command':'put', 'key':'mode1', 'value':'%i' % int(int(state))})
		msg = OSCMessage(path)
		msg.insert(0, 1)
		client.connect( (source[0], 9000) )
		client.send(msg)
for x in range(0,20):
	server.addMsgHandler("/self/mode1/"+str(x)+"/1", multiselectMode1_callback)

def multiselectPalette1_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source)
	split = path.split("/")
	Palette = split.pop()
	Palette = split.pop()
	if args[0]==1:
		#requests.get("http://192.168.1.104/arduino/state/"+str(int(state)-1))
		json.send({'command':'put', 'key':'palette1', 'value':'%i' % int(int(Palette))})
		msg = OSCMessage(path)
		msg.insert(0, 1)
		client.connect( (source[0], 9000) )
		client.send(msg)
for x in range(0,20):
	server.addMsgHandler("/self/palette1/"+str(x)+"/1", multiselectPalette1_callback)





############################################################################
# Mode2 and palette2
def multiselectMode2_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source) 
	split = path.split("/")
	state = split.pop()
	state = split.pop()
	if args[0]==1:
		#requests.get("http://192.168.1.104/arduino/state/"+str(int(state)-1))
		json.send({'command':'put', 'key':'mode2', 'value':'%i' % int(int(state))})
		msg = OSCMessage(path)
		msg.insert(0, 1)
		client.connect( (source[0], 9000) )
		client.send(msg)
for x in range(0,20):
	server.addMsgHandler("/self/mode2/"+str(x)+"/1", multiselectMode2_callback)

def multiselectPalette2_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source)
	split = path.split("/")
	Palette = split.pop()
	Palette = split.pop()
	if args[0]==1:
		#requests.get("http://192.168.1.104/arduino/state/"+str(int(state)-1))
		json.send({'command':'put', 'key':'palette2', 'value':'%i' % int(int(Palette))})
		msg = OSCMessage(path)
		msg.insert(0, 1)
		client.connect( (source[0], 9000) )
		client.send(msg)
for x in range(0,20):
	server.addMsgHandler("/self/palette2/"+str(x)+"/1", multiselectPalette2_callback)






############################################################################
# Mode3 and palette3
def multiselectMode3_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source) 
	split = path.split("/")
	state = split.pop()
	state = split.pop()
	if args[0]==1:
		#requests.get("http://192.168.1.104/arduino/state/"+str(int(state)-1))
		json.send({'command':'put', 'key':'mode3', 'value':'%i' % int(int(state))})
		msg = OSCMessage(path)
		msg.insert(0, 1)
		client.connect( (source[0], 9000) )
		client.send(msg)
for x in range(0,20):
	server.addMsgHandler("/self/mode3/"+str(x)+"/1", multiselectMode3_callback)

def multiselectPalette3_callback(path, tags, args, source):
	print "received: " +repr(source)+ " " + str(path) + " " + str(args) + " " + str(source)
	split = path.split("/")
	Palette = split.pop()
	Palette = split.pop()
	if args[0]==1:
		#requests.get("http://192.168.1.104/arduino/state/"+str(int(state)-1))
		json.send({'command':'put', 'key':'palette3', 'value':'%i' % int(int(Palette))})
		msg = OSCMessage(path)
		msg.insert(0, 1)
		client.connect( (source[0], 9000) )
		client.send(msg)
for x in range(0,20):
	server.addMsgHandler("/self/palette3/"+str(x)+"/1", multiselectPalette3_callback)

while True:
	server.handle_request()

server.close()
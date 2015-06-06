@@[Home](Home.md) -> [Specs](Specs.md) -> [ActiveSockets](ActiveSockets.md)

---


## Overview ##

This feature allows to have unlimited set of connections initiated from aiengine server to external servers.

## Implementation Details ##

  * aiengine creates all active sockets on startup
  * active socket is available via AIMedia interface
  * active socket is available via IO channels if configured
  * inbound stream can be forwarded to configured IO channel
  * stream from specific IO channel can be forwarded to outbound
  * active socket supports protocol configuring - see [Protocols](MediaProtocols.md)
  * if forwarding inbound stream - creates thread to read from socket and automatically reconnects if connection was broken

Planned but implemented:
  * to have non-persisting connections - to use active connection only after request from server, do not restore connection automatically
  * timeout for reconnection

## Configuration ##

  * sample configuration for google active socket in media.xml
```
		<channel name="google" run="true">
			<property name="protocol" value="http"/>
			<property name="protocol.showmessages" value="false"/>
			<property name="protocol.showpackets" value="false"/>
			<property name="msgtype" value="text"/>
			<property name="permanent" value="true"/>
			<property name="host" value="www.google.com"/> 
			<property name="port" value="80"/> 
			<property name="redirect-in" value="true"/>
			<property name="redirect-out" value="true"/> 
			<property name="topic-in" value="http.response"/> 
			<property name="topic-out" value="http.request"/> 
		</channel>
```

  * **host** - host to connect to - now IP-addresses are not supported
  * **port** - port to connect to
  * **redirect-in** - if "true" then messages are forwarded from socket to IO channel
  * **redirect-out** - if "true" then messages are forwarded from IO channel to socket
  * **topic-in** - channel to write messages received from socket
  * **topic-out** - messages from this channel are sent to socket - see [Protocols](MediaProtocols.md)
  * **reconnectionTimeout** - if unable to connect to socket, then next attempt is performed only after reconnectionTimeout seconds

## How to Test ##

  * use google active socket and test to read some page:
```
INFO: AI console
INFO: connected to 87.228.126.111:20001
REQUEST:
<xmlcall name="TestDirectChannels-Google" class="TestDirectChannels" method="testRequestPage" requestId="REQ-1">
    <parameters>
        <property name="page" value="http://code.google.com" />
    </parameters>
</xmlcall>

output:
RESPONSE:
<xmlcallresult requestId="REQ-1" name="TestDirectChannels-Google" status="OK">
    <page>http://code.google.com</page>
    <body>&lt;!DOCTYPE html... (omitted)
</xmlcallresult>

INFO: disconnected
```
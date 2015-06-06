@@[Home](Home.md) -> [Specs](Specs.md) -> [MediaProtocols](MediaProtocols.md)

---


## Overview ##

Listeners and active sockets are used for communication between aiengine and external world. When connection is established, SocketProtocol class allows to receive and send messages, if any, disregarding of network packets.

## Implementation Details ##

  * based on TCP/IP and Windows Sockets 2.2
  * supports protocols: HTTP 1.1 (client side), delimited messages, xml messages, text stream
  * unified configuring (see configuration section below)
  * supports different protocols for inbound and outbound streams of the same connection, if applicable
  * stores part of socket stream that was read from network but not used for last message
  * allows reading fixed size messages
  * allows non-blocking mode, returning false until complete message is available
  * for text stream reads message as much as available without wait until configurable max size reached
  * for HTTP supports single packet message and chunked messages
  * for HTTP write message is treated as address for the page to read
  * for xml messages it returns text message containing one xml
  * message delimiter can be any C++ literal string with special characters - like \r or \1

Planned but still not implemented - binary stream or binary messages

## Configuration ##

  * sample configuration for listener in media.xml - debug messages, delimited by one character with ASCII code 1:
```
		<listener name="debug" run="true">
			<property name="protocol" value="text-messages"/>
			<property name="protocol.delimiter" value="\1"/>
		</listener>
```
  * reading any page from web
```
		<channel name="google" run="true">
			<property name="protocol" value="http"/>
			<property name="protocol.showmessages" value="false"/>
			<property name="protocol.showpackets" value="false"/>
		</channel>
```
  * all configuration parameters:
    * **max-packet-size** - in bytes, for text stream defines max size of single message, default 1000000
    * **max-read-size** - max bytes read from socket in one recv call, default 4096
    * **wait-time-sec** - in blocking mode, number of seconds to wait maximum, default 30
    * **protocol** - can be "asymmetric", "http" , "text-messages", "xml-messages"; if "asymetric", then below properties are configured using prefix "protocol-inbound" or "protocol-outbound"
    * **protocol.showmessages** - each in/out message is logged
    * **protocol.showpackets** - each in/out network packet is logged
    * **protocol.delimiter** - message delimiter, empty by default - for xml and text messages

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
  * set protocol.showpackets to "true" to see exact network traffic
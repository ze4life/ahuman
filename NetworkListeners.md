@@[Home](Home.md) -> [Specs](Specs.md) -> [NetworkListeners](NetworkListeners.md)

---


## Overview ##

This feature allows to have unlimited set of listening ports in aiengine by means of configuring only. Some external client can initiate connection to the server on each listening port and establish separate communication session.

## Implementation Details ##

  * aiengine creates separate communication thread for each incoming connection
  * server can handle unlimited number of connections running in parallel on the same port
  * each running connection is associated with separate IO session
  * client-to-server stream is split into messages according to protocol - see [Protocols](MediaProtocols.md)
  * components inside server communicate to listeners using IO and configured channels
  * incoming messages are forwarded from client socket to one IO channel, outgoing messages are forwarded to client socket from another IO channel
  * when listener connection sends message to channel, it sends it using separate session
  * channels are shared across all connections related to the same port and because of this listener subscriber connection uses its own session to filter out messages from other sessions (it is performed by IO)

## Configuration ##

  * sample configuration for listener in media.xml
```
	<listeners>
    
		<listener name="debug" run="true">
			<property name="direction" value="duplex"/> 
			<property name="protocol" value="text-messages"/>
			<property name="protocol.delimiter" value="\1"/>
			<property name="auth" value="false"/>
			<property name="port" value="20001"/> 
			<property name="msgtype" value="xmlcall"/> 
			<property name="topic-in" value="debug.commands.in"/> 
			<property name="topic-out" value="debug.commands.out"/> 
		</listener>
```

  * **direction** - controls whether topic-in and topic-out are used, can be "duplex", "in", "out"
  * **protocol** and protocol.`*` properties - control in/out messages, details are in [Protocols](MediaProtocols.md)
  * **auth** - not implemented fully now, but intended to have authorised sessions; if "true" then first message should contain auth props and no other messages will be sent to channels until authorisation completed
  * **port** - port where listener is started - use it to connect to server
  * **msgtype** - parse message to specific request type supported by IO before sending message to IO channel; possible values are "text" , "xml" , "xmlcall"; probably have to be migrated to protocol code
  * **topic-in** - channel to write client-to-server messages
  * **topic-out** - channel to write server-to-client messages

## How to Test ##

  * first listener created for the server is one for debug purposes - to make any testing from outside of server in runtime - debug
  * it requires aiconsole.exe - see human\aiconsole project
  * run human\deploy\xml-threaddump.xml to trigger debug listener - see:

```
start aiconsole.exe -s 87.228.126.111:20001 -i xml-threaddump.xml

INFO: ---------------------------
INFO: AI console
INFO: connected to 87.228.126.111:20001
REQUEST:
<xmlcall name="ThreadDump" class="TestEngineThreads" method="testThreadDump" requestId="REQ-1">
    <parameters>
        <property name="showStack" value="true" />
    </parameters>
</xmlcall>

RESPONSE:
<xmlcallresult requestId="REQ-1" name="ThreadDump" status="OK" />

INFO: disconnected
```
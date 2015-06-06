@@[Home](Home.md) -> [TestFramework](TestFramework.md)

![http://ahuman.googlecode.com/svn/images/wiki/test/mindtest.jpg](http://ahuman.googlecode.com/svn/images/wiki/test/mindtest.jpg)

---


## Test Strategy ##

In the early stages testing is not the important area as proof-of-the-concept is more critical. In the same time to force aHuman working even somehow requires running quite complex set of functions in multi-thread environment. So debugging is quite tricky.

To reduce overhead from bugfixing, below approaches are applied in aHuman project, specifically for the testing purposes:

  * Logging
  * Automated Testing
  * Thread Dumps

## Logging ##

Logging is implemented based on log4j ideas:

  * each class derived from Object, has protected member "logger"
  * each logger has name, by default equal to class name for simple objects, otherwise it could be equal to "class instance" name or to "service"
  * there are log levels: DEBUG/INFO/ERROR - with usual meaning
  * there are log controls, defined in main.xml:

```

	<logging level="INFO">
		<property name="syncMode" value="false"/>
		<property name="filename" value="log\main.log"/>
		<property name="format" value="log: %"/>
		
		<objectLogLevel level="DEBUG">
			<class name="NNFinderFactory" level="DEBUG"/>
			<class name="NNFinder" level="DEBUG"/>
			<class name="NNStrategyBackPropagation" level="DEBUG">
				<instance name="NNFinderFactory::P1S" level="ERROR"/>
			</class>
		</objectLogLevel>

		<serviceLogLevel level="DEBUG">
		</serviceLogLevel>

		<customLogLevel level="DEBUG">
			<class name="SocketServer::debug" level="ERROR"/>
			<class name="SocketServer::chat" level="ERROR"/>
			<class name="SocketConnection" level="ERROR"/>
			<class name="HtmLibDebug" level="INFO">
				<exclude string="showAcceptActions"/>
			</class>
			<class name="HtmLayer" level="DEBUG">
				<property name="showAcceptActions" value="3,4"/>
			</class>
		</customLogLevel>
	</logging>

```

  * "syncMode" feature defines whether logging is produces by async thread or in the same thread as caller; async thread is started after server startup sequence

## Automated Testing ##

Until project is mature, test codebase alignments looks to me not efficient. That's why all the test code is collected in the only test module, with below coding approach:

  * partly implementation is inspired by JUnit
  * test code consists of test service and test units
  * test unit has pre-defined interface and implements set of test cases, where each test case is identified and can be run independently from others
  * test units are part of aiengine running process and can be called externally by pre-defined interface using xml function call like:

```
<xmlcall name="nnlib::testFinderPlay">
	<parameters>
		<property name="statCount" value="10"/>
		<property name="maxIterations" value="100"/>
		<property name="maxRestarts" value="10"/>
<!-- network -->
		<property name="algorithm" value="1"/>
		<property name="hiddenLayerSize" value="3"/>
		<property name="errorFunctionLinear" value="false"/>
		<property name="calculateHiddenInputRanges" value="false"/>
<!-- core -->
		<property name="stopBitsPrecision" value="0.1"/>
		<property name="gradientRate" value="0.7"/>
		<property name="momentum" value="0"/>
		<property name="steepness" value="1"/>
<!-- weights -->
		<property name="initWeights" value="N"/>
		<property name="wMin" value="-1500"/>
		<property name="wMax" value="1500"/>
		<property name="wRandomMin" value="-0.5"/>
		<property name="wRandomMax" value="0.5"/>
<!-- RPROP -->
		<property name="increaseFactorRPROP" value="1.2"/>
		<property name="decreaseFactorRPROP" value="0.5"/>
		<property name="deltaMinRPROP" value="0"/>
		<property name="deltaMaxRPROP" value="50"/>
		<property name="deltaZeroRPROP" value="0.1"/>
		<property name="deltaZeroMinRPROP" value="0.0001"/>
<!-- QuickProp -->
		<property name="quickPropDecay" value="-0.0001"/>
		<property name="quickPropMu" value="1.75"/>
		<property name="quickPropMinStep" value="0.001"/>
	</parameters>
</xmlcall>

```

  * call can be done by tools.exe utility:

```
start tools.exe console -s localhost:20001 -i %1 -o %1.out
```

  * after the call, test case can either form response xml, or throw any exception; the last will be combined within pre-defined standard xml response

```
INFO: ---------------------------
INFO: AI console
INFO: connected to localhost:20001
REQUEST:
<xmlcall name="expert::createbysamples" requestId="REQ-1">
    <parameters />
</xmlcall>

RESPONSE:
<xmlcallresult requestId="REQ-1" name="expert::createbysamples" 
status="Exception">C++ Exception: assertion failed (false) (file=nnfinderfactory.cpp,
line=62)&#x0A;&#x09;...skipped...&#x0A;&#x09;
NNFinderFactory::create (aiengine, 0x41f017)&#x0A;&#x09;
AIExpertDebug::testCreateBySamples (aiengine,0x414363)&#x0A;&#x09;
AIExpertDebug::onMessage (aiengine, 0x414141)&#x0A;&#x09;
Channel::subscribeEvent (aiengine, 0x4080ff)&#x0A;&#x09;
Channel::publish (aiengine, 0x40789f)&#x0A;&#x09;
PublisherImpl::publish (aiengine, 0x40b3ab)&#x0A;&#x09;
SocketConnection::processMessage (aiengine, 0x411790)&#x0A;&#x09;
SocketConnection::processData (aiengine, 0x41148f)&#x0A;&#x09;
SocketConnection::performRead (aiengine, 0x41129b)&#x0A;&#x09;
SocketConnection::readMessages (aiengine, 0x410fde)&#x0A;&#x09;
SocketConnection::startConnection (aiengine, 0x410f39)&#x0A;&#x09;
::__beginthreadex (aiengine, 0x49b973)&#x0A;&#x09;
:: (unknown, 0x7c80b683)</xmlcallresult>

Exception: C++ Exception: assertion failed (false) (file=nnfinderfactory.cpp, line=62)
	...skipped...
	NNFinderFactory::create (aiengine, 0x41f017)
	AIExpertDebug::testCreateBySamples (aiengine, 0x414363)
	AIExpertDebug::onMessage (aiengine, 0x414141)
	Channel::subscribeEvent (aiengine, 0x4080ff)
	Channel::publish (aiengine, 0x40789f)
	PublisherImpl::publish (aiengine, 0x40b3ab)
	SocketConnection::processMessage (aiengine, 0x411790)
	SocketConnection::processData (aiengine, 0x41148f)
	SocketConnection::performRead (aiengine, 0x41129b)
	SocketConnection::readMessages (aiengine, 0x410fde)
	SocketConnection::startConnection (aiengine, 0x410f39)
	::__beginthreadex (aiengine, 0x49b973)
	:: (unknown, 0x7c80b683)
INFO: disconnected
```

## Thread Dumps ##

Multi-thread application is hard to debug without understanding what happens in different threads in the same time. Framework contains special functions to print threads and their stack trace.

Also test unit created to allow calling these functions from outside of engine process. Threads are suspended for the time of capturing stack trace.

  * each thread has unique name, if started via AIEngine call; framework-based threads are started with well-defined names

```
	virtual RFC_HND runThread( String name , Object *object , ObjectThreadFunction function , void *p_arg ) = 0;
```

  * threads and stack trace are logged to main log after calls to AIEngine methods:

```
	virtual void threadDumpAll( bool showStackTrace ) = 0;
	virtual void threadDumpByName( String name , bool showStackTrace ) = 0;
```

  * test unit call to show all thread, optionally printing stack trace for each:

```
<xmlcall name="ThreadDump" class="TestEngineThreads" method="testThreadDump">
	<parameters>
		<property name="showStack" value="false"/>
	</parameters>
</xmlcall>

results in output:

------------
thread index=0, name=SensesTracker, threadId=0x17fc
thread index=1, name=chat.in, threadId=0x161c
thread index=2, name=chat.out, threadId=0x1798
thread index=3, name=debug, threadId=0xb90
thread index=4, name=debug.1, threadId=0xfbc
thread index=5, name=debug.commands.in, threadId=0x874
thread index=6, name=debug.commands.out, threadId=0xc60
thread index=7, name=imagekbcmd, threadId=0xcc8
thread index=8, name=imagekbrsp, threadId=0x11c4
thread index=9, name=main, threadId=0x14ac
thread index=10, name=sensordata, threadId=0x107c
------------
```

  * test unit call to show specific thread by its name, optionally with printing its stack trace:

```
<xmlcall name="ThreadDump" class="TestEngineThreads" method="testShowThread">
	<parameters>
		<property name="threadName" value="main"/>
		<property name="showStack" value="true"/>
	</parameters>
</xmlcall>

results in log output:

00:00:29,593 [INFO, 0x1660] - THREAD DUMP: thread name=main, threadId=0x1634: [.]
00:00:41,401 [INFO, 0x1660] - CALL STACK:
	::_rfc_hnd_waitevent (aiengine.vc, 0x5aeaec)
	AIEngineImpl::waitExitSignal (aiengine.vc, 0x4aaed6)
	AIEngineImpl::runInternal (aiengine.vc, 0x4a8491)
	AIEngine::run (aiengine.vc, 0x4a78a4)
	::_main (aiengine.vc, 0x56999f)
	...skipped...
```
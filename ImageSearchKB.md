@@[Home](Home.md) -> [Specs](Specs.md) -> [ImageSearchKB](ImageSearchKB.md)

# Introduction #

Here is the current development status and the way to test the Image knowledge base module.

# Development Strategy #
  * The Image search server is implemented using JAVA and the search API from bing are used to search for a particular image
  * Two channels are used by module for communication with other modules, one for taking the query command which uses the format "query;width;height;no\_samples\n" and the other one to post the results to.

# Testing #
  * Run the image knowledge base server from path 'deploy\Image Knowledge Base\StartServer.bat'
  * Start aHuman engine.
  * Run test case using 'deploy\run-test-image-kb.bat' file.
  * Test case will post query to command channel and the results can be obtained by subscribing to the response channel.

# Pending Items #
  * Interface this module with the sensor 'eye'
  * Make this interfacing a dynamic operation so that when aHuman wants any visual information about anything it can switch to knowledge base and can present on results.
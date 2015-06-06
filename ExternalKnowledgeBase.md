# Introduction #

This page will highlight various external processes and application that will interact with aHuman to provide the knowledge and sensor data.


# Bing Search API to feed vision data to aHuman #

Add your content here.  Format your content with:
  * A image search server is created that will interact with aHuman using socket interface.
  * aHuman presently can interact with server and can ask for images of anything using a particular format of request "query;sizeX;sizeY;samples"
  * Image server will return the pixel data of the images to the aHuman interface which can then be fed to cortex.
  * Image server uses port 9000 to listen for connections.
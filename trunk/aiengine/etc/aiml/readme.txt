genoaiml.zip is a collection of FlashChat compatible aiml files that are all under 3.0K in size.

I created these from the stock programE files that came with FlashChat 4.x.x and from some newer
Dr. Wallace files I found. I also wrote a humor.aiml file and included it as well. The humor file
will respond to user input such as "Tell me a joke" "tell a joke" "are you funny" and more. You may
add short jokes to the humor file by placing the joke in the file under the RANDOM tag and enclosed
in <li> your joke text here </li>. Just follow the format of the other jokes. Remember, you have to
reload you ENTIRE aiml set for this to work. So if you want to add some jokes, do it now, before you
load the bot tables.

I split the larger .aiml files into smaller ones (under 3.0K) for users of FlashChat that have
timeout problems with their host.

FlashChat Installation
=======================
1. 	Delete all stock aiml files in your flashchat/bot/programe/aiml/ folder. Do NOT delete the startup.xml
	file that is there.
2. 	Upload the enclosed aiml files using an ftp program in binary mode to your flashchat/bot/programe/aiml/ folder.
3. 	Now you have to reload these files to you MySQL database tables. This can be done in -1- of 2 ways:

	(A). Using PhpMyAdmin, Empty all bot related tables. 
	_bot
	_bots
	_conversationlog
	_dstore
	_gmcache
	_gossip
	_patterns
	_templates
	_thatindex
	_thatstack
	Once the bot related tables above are emptied you can run the flashchat/bot/programe/src/botinst/botloader.php
	script, or the flashchat/bot/programe/src/botinst/botloaderinc.php script to reload your bots. Use botloaderinc
	if you still have timeout problems.

	-or- (B). Download a copy of my script called "botupdate" from the TuFat.com Code Depot area, install it, and run it.
	     botupdate will do everything for you.

Contact Information
===================

My name is Gene Wells
Email me at:  gwells@frognet.net
I can be contacted by PM on the Tufat.com forums. My nick is Geno
FlashChat is the property of Darrren Gates and can be gotten at http://www.tufat.com. An Awesome Flash/php/MySql chat script!

That's it.

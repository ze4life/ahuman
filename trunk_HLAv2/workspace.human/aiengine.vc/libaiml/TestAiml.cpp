#include <rebecca/network_all.h>
using namespace rebecca;

#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* args[]) 
{
	try
	{		
		NetworkAimlFacade aiml(argc, args);
		NetworkGraphBuilder &builder =    aiml.getNetworkGraphBuilder();
		cout << "[Type /exit to exit]"   << endl << endl << endl;
		string botName =   builder.getBotPredicate("name").c_str();
		StringPimpl response =   builder.getResponse("connect");		

		//Send the initial opening line of the bot
		cout << botName << " says: " << response.c_str() << endl;

		while(true) 
		{
			string input;
			cout << "You say> ";
			//Get input from the user from the keyboard
			getline(cin, input); 

			if(input == "/exit")
			{	
				break;
			}
			else //The user gave an input to the bot
			{
				StringPimpl response = 
					builder.getResponse(input.c_str());
				cout << "=====================" 
					<< endl << endl;
				//Print out what Rebecca says.
				cout << botName << " says: " 
					<< response.c_str() << endl;
			}
		} //end of while
	} //end of try
	catch(NetworkException &e)
	{
		cout << "[NetworkException Found Terminating]" 
			<< endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(Exception &e)
	{
		cout << "[An uknown exception occured, "
			"Terminating program]" << endl;
		cout << "[" << e.what() << "]";
		return 1;
	}
	//Everything smooth.  Exit normally.
	return 0;
}
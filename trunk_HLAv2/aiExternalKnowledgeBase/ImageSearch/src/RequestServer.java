import java.io.FileInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;


public class RequestServer {
	ServerSocket server = null;
	String protocol = null;
	String appID = null;
	String query = null;
	Properties prop = null;

	public RequestServer() {
		try{
			parseConfigFile();
			server = new ServerSocket(Integer.parseInt(prop.getProperty("SERVER_PORT")));
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	void parseConfigFile(){
		try{
			prop = new Properties();
			prop.load(new FileInputStream("config.properties"));
			protocol = prop.getProperty("PROTOCOL");
			System.out.println("********** Booting Image Knowledge Base ***********");
			System.out.println("[+] Using protocol: " + protocol);
			appID = prop.getProperty("APP_ID");
			System.out.println("[+] Using App ID: " + appID);
			System.out.println("************* Image Knowledge Base Up **************");
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	public void processRequests() {
		while(true){
			try{
				Socket client = server.accept();
				Thread worker = new Thread(new RequestProcessor(client, appID, protocol));
				worker.start();
			}catch(Exception e){
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		RequestServer obj = new RequestServer();
		obj.processRequests();
	}
}

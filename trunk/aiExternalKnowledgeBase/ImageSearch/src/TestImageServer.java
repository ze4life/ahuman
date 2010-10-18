import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;


public class TestImageServer {

	public static void main(String args[]){
		try{
			Socket sock = new Socket("127.0.0.1", 9000);
			InputStreamReader ir = new InputStreamReader(sock.getInputStream());
			BufferedReader bin = new BufferedReader(ir);
			OutputStreamWriter or = new OutputStreamWriter(sock.getOutputStream());
			BufferedWriter br = new BufferedWriter(or);
			br.write("chair;200;200;2\n",0,"chair;200;200;2\n".length());
			br.flush();
			for(int i = 0; i < 2; i++){
				System.out.println("Image Data: "+ i);
				for(int j = 0; j < 200; j ++){
					for(int  k = 0; k < 200;k++){
						System.out.print(bin.read()+",");
						System.out.flush();
					}
					System.out.println("");
				}
			}
			sock.close();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}

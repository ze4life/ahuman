import java.awt.image.BufferedImage;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.URL;

import javax.imageio.ImageIO;

import com.google.code.bing.search.schema.SearchResponse;
import com.google.code.bing.search.schema.multimedia.ImageResult;


public class RequestProcessor implements Runnable {

	String sizeX, sizeY;
	String query;
	Socket client = null;
	String protocol = null;
	String appID = null;
	String samples;
	/**
	 * The protocol to get data from server will be "<query>;<sizex>;<sizey>;<samplesize>"
	 * @param client
	 * @param protocol 
	 * @param appID 
	 */
	public RequestProcessor(Socket client, String appID, String protocol) {
		System.out.println("[+] Got connection from:"+ client.getRemoteSocketAddress());
		this.client = client;
		this.appID = appID;
		this.protocol = protocol;
	}

	private void processResponse(SearchResponse response) {
		System.out.println("[+] Results for query: " + response.getQuery().getSearchTerms());
		for (ImageResult result : response.getImage().getResults().getImageResultList()) {
			System.out.println("\t - Media URL ["+result.getWidth()+","+result.getHeight()+"]:"+result.getMediaUrl());
			try{
				URL url = new URL(result.getMediaUrl()); 
				BufferedImage bImage = ImageIO.read(url);
				int w = result.getWidth().intValue();
				int h = (int)result.getHeight().intValue();
				int rgbs[] = new int[w*h];
				bImage.getRGB(0, 0, w, h, rgbs, 0, w);
				BufferedOutputStream out = new BufferedOutputStream(client.getOutputStream());
				for(int i = 0; i < w*h; i++){
					out.write(rgbs[i]);
				}
				out.flush();
			}catch(Exception e){
				e.printStackTrace();
			}
			System.out.println("\t\t -- Image data sent to client for training");
		}
	}

	@Override
	public void run() {
		try{
			InputStreamReader ir = new InputStreamReader(client.getInputStream());
			BufferedReader bin = new BufferedReader(ir);
			String data = bin.readLine();
			String commands[] = data.split(";");
			/* Apply protocol logic */
			query = commands[0];
			sizeX = commands[1];
			sizeY = commands[2];
			samples = commands[3];
			/* Get the data from the internet about the query requested */
			PerformSearch search = new PerformSearch();
			search.setAppID(appID);
			search.setProtocol(protocol);
			search.setQuery(query);
			search.setSizeX(sizeX);
			search.setSizeY(sizeY);
			search.setSamples(samples);
			System.out.println("\t - Client query :" + query);
			SearchResponse response = search.search();
			processResponse(response);
			client.close();
			System.out.println("\t - Client request successfully processed");
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}

}

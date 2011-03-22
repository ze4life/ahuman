import com.google.code.bing.search.client.BingSearchClient;
import com.google.code.bing.search.client.BingSearchServiceClientFactory;
import com.google.code.bing.search.client.BingSearchClient.SearchRequestBuilder;
import com.google.code.bing.search.client.enumeration.ApiProtocol;
import com.google.code.bing.search.schema.AdultOption;
import com.google.code.bing.search.schema.SearchRequest;
import com.google.code.bing.search.schema.SearchResponse;
import com.google.code.bing.search.schema.SourceType;

public class PerformSearch {

	String protocol = null;
	String appID = null;
	String sizeX, sizeY;
	String query = null;
	String samples;
	public SearchResponse search() {
		BingSearchServiceClientFactory factory = BingSearchServiceClientFactory.newInstance();
		BingSearchClient client = factory.createBingSearchClient(ApiProtocol.fromValue(protocol));
		SearchResponse response = client.search(createSearchRequest(client));
		return response;
	}

	private SearchRequest createSearchRequest(BingSearchClient client) {
		SearchRequestBuilder builder = client.newSearchRequestBuilder();
		builder.withAppId(appID);
		builder.withQuery(query);
		builder.withSourceType(SourceType.IMAGE);
		builder.withVersion("2.0");
		builder.withAdultOption(AdultOption.OFF);
		builder.withImageRequestCount(Long.parseLong(samples));
		builder.withImageRequestOffset(0L);
		builder.withImageRequestFilter("Size:Width:"+sizeX);
		builder.withImageRequestFilter("Size:Height:"+sizeY);
		return builder.getResult();
	}

	public String getProtocol() {
		return protocol;
	}

	public String getAppID() {
		return appID;
	}

	public String getSizeX() {
		return sizeX;
	}

	public String getSizeY() {
		return sizeY;
	}

	public String getQuery() {
		return query;
	}

	public void setProtocol(String protocol) {
		this.protocol = protocol;
	}

	public void setAppID(String appID) {
		this.appID = appID;
	}

	public void setSizeX(String sizeX) {
		this.sizeX = sizeX;
	}

	public void setSizeY(String sizeY) {
		this.sizeY = sizeY;
	}

	public void setQuery(String query) {
		this.query = query;
	}

	public String getSamples() {
		return samples;
	}

	public void setSamples(String samples) {
		this.samples = samples;
	}
}


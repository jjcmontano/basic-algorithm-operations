package com.bao.lc.client;

import java.io.IOException;
import java.net.URI;
import java.util.Map;

import org.apache.http.HttpHost;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.params.CookiePolicy;
import org.apache.http.client.params.HttpClientParams;
import org.apache.http.conn.ClientConnectionManager;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.impl.conn.tsccm.ThreadSafeClientConnManager;
import org.apache.http.params.HttpParams;
import org.apache.http.params.HttpProtocolParams;
import org.apache.http.protocol.BasicHttpProcessor;

import com.bao.lc.util.CommonUtil;
import com.bao.lc.util.HttpClientUtil;

public class BrowserClient extends DefaultHttpClient
{
	public static final String AGENT_IE7 = "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; TEN)";
	public static final String AGENT_CHROME = "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.2 (KHTML, like Gecko) Chrome/15.0.874.106 Safari/535.2";
	public static final String AGENT_FIREFOX = "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6 (.NET CLR 3.5.30729)";

	/**
	 * Creates a new HTTP client from parameters and a connection manager.
	 * 
	 * @param params
	 *            the parameters
	 * @param conman
	 *            the connection manager
	 */
	public BrowserClient(final ClientConnectionManager conman, final HttpParams params)
	{
		super(conman, params);
	}

	/**
	 * @since 4.1
	 */
	public BrowserClient(final ClientConnectionManager conman)
	{
		super(conman, null);
	}

	public BrowserClient(final HttpParams params)
	{
		super(null, params);
	}

	public BrowserClient()
	{
		super(null, null);
	}

	protected ClientConnectionManager createClientConnectionManager()
	{
		return new ThreadSafeClientConnManager();
	}

	protected HttpParams createHttpParams()
	{
		HttpParams params = super.createHttpParams();

		HttpProtocolParams.setUserAgent(params, AGENT_IE7);
		HttpClientParams.setCookiePolicy(params, CookiePolicy.BROWSER_COMPATIBILITY);
		return params;
	}

	public void addReferer(String referer)
	{
		getParams().setParameter(RequestReferer.REFERER_INTERNAL, referer);
	}

	protected BasicHttpProcessor createHttpProcessor()
	{
		BasicHttpProcessor httpproc = super.createHttpProcessor();
		httpproc.addInterceptor(new RequestReferer());

		return httpproc;
	}

	public HttpResponse get(URI uri, Map<String, String> headers, Map<String, String> params,
		HttpHost targetHost) throws ClientProtocolException, IOException
	{
		uri = CommonUtil.getAbsoluteURI(uri, targetHost);

		HttpGet hp = HttpClientUtil.createHttpGet(uri, params, headers);

		HttpResponse rsp = null;
		if(targetHost != null)
		{
			rsp = execute(targetHost, hp);
		}
		else
		{
			rsp = execute(hp);
		}

		addReferer(uri.toString());

		return rsp;
	}

	public HttpResponse get(String url, Map<String, String> headers, Map<String, String> params,
		HttpHost targetHost) throws ClientProtocolException, IOException
	{
		return get(URI.create(url), headers, params, targetHost);
	}

	public HttpResponse get(String url) throws ClientProtocolException, IOException
	{
		return get(URI.create(url), null, null, null);
	}

	public HttpResponse post(URI uri, Map<String, String> headers, Map<String, String> params,
		String encoding, HttpHost targetHost) throws ClientProtocolException, IOException
	{
		uri = CommonUtil.getAbsoluteURI(uri, targetHost);

		HttpPost post = HttpClientUtil.createHttpPost(uri, params, encoding, headers);

		HttpResponse rsp = null;
		if(targetHost != null)
		{
			rsp = execute(targetHost, post);
		}
		else
		{
			rsp = execute(post);
		}

		addReferer(uri.toString());

		return rsp;
	}

	public HttpResponse post(String url, Map<String, String> headers, Map<String, String> params,
		String encoding, HttpHost targetHost) throws ClientProtocolException, IOException
	{
		return post(URI.create(url), headers, params, encoding, targetHost);
	}

	public HttpResponse post(String url, Map<String, String> params, String encoding)
		throws ClientProtocolException, IOException
	{
		return post(URI.create(url), null, params, encoding, null);
	}
}
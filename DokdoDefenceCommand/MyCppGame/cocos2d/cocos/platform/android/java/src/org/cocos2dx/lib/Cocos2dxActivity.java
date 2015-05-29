/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.ViewGroup;
import android.util.Log;
import android.widget.FrameLayout;
import android.preference.PreferenceManager.OnActivityResultListener;

import com.google.android.gms.ads.*;
/*import net.daum.adam.publisher.AdInterstitial;
import net.daum.adam.publisher.AdView.OnAdClosedListener;
import net.daum.adam.publisher.AdView.OnAdFailedListener;
import net.daum.adam.publisher.AdView.OnAdLoadedListener;
import net.daum.adam.publisher.impl.AdError;*/

public abstract class Cocos2dxActivity extends Activity implements Cocos2dxHelperListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private final static String TAG = Cocos2dxActivity.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================
	
	private Cocos2dxGLSurfaceView mGLSurfaceView;
	private Cocos2dxHandler mHandler;	
	private static Cocos2dxActivity sContext = null;
	private Cocos2dxVideoHelper mVideoHelper = null;
	
	// ===========================================================
	// AdMob & Ad@m : Adam 전면광고는 현재 전면 제공중이지 않으므로 빼고 간다.
	// ===========================================================
	private static final int MSG_AD_REQUEST = 1000;
	private static final int MSG_SHOWAD = 1001;
	private static Handler mAdHandler = new Handler(){
		public void handleMessage(Message msg) {
			switch(msg.what)
			{
			case MSG_AD_REQUEST:
				requestAdMob();
				break;
			case MSG_SHOWAD:
				if(admobInterstitial.isLoaded() == true)
				{
					admobInterstitial.show();
				}
				break;
			}
		}
	};
	
	private static InterstitialAd admobInterstitial = null;
	private final static String ADMOB_AD_UNIT_ID = "ca-app-pub-9183016001148429/6063131597";
	
	/*private AdInterstitial adamInterstitial = null;
	private final static String ADAM_CLIENT_ID = "9991Z0MT147f6e37b8f";*/
	
	
	public static Context getContext() {
		return sContext;
	}
	
	protected void onLoadNativeLibraries() {
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
			Bundle bundle = ai.metaData;
			String libName = bundle.getString("android.app.lib_name");
    		System.loadLibrary(libName);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	// ===========================================================
	// Constructors
	// ===========================================================
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		onLoadNativeLibraries();

		sContext = this;
    	this.mHandler = new Cocos2dxHandler(this);
    	
    	Cocos2dxHelper.init(this);
    	
    	this.init();
    	if (mVideoHelper == null) {
    		mVideoHelper = new Cocos2dxVideoHelper(this, mFrameLayout);
		}
    	
    	// Create Adam Interstitial
    	/*adamInterstitial = new AdInterstitial(this);
    	adamInterstitial.setClientId(ADAM_CLIENT_ID);
    	adamInterstitial.setOnAdLoadedListener(new OnAdLoadedListener(){
			@Override
			public void OnAdLoaded() {
				Log.i("jrkim", "Adam.OnAdLoaded");
			}
    	});
    	adamInterstitial.setOnAdClosedListener(new OnAdClosedListener(){
			@Override
			public void OnAdClosed() {
				Log.i("jrkim", "Adam.OnAdClosed");
			}
    	});
    	adamInterstitial.setOnAdFailedListener(new OnAdFailedListener(){
			@Override
			public void OnAdFailed(AdError arg0, String arg1) {	
				Log.i("jrkim", "Adam.OnAdFailedListener");
			}
    	});*/
    	
    	// Create AdMob Interstitial
    	admobInterstitial = new InterstitialAd(this);
    	admobInterstitial.setAdUnitId(ADMOB_AD_UNIT_ID);
    	
    	admobInterstitial.setAdListener(new AdListener() {
    		@Override
    		public void onAdLoaded() {
    		}
    		
    		@Override
    		public void onAdFailedToLoad(int errorCode){
    			// 30초 후에 다시 광고 Request 시도
    			mAdHandler.sendEmptyMessageDelayed(MSG_AD_REQUEST, 30000);
    		}
    		
    		@Override
    		public void onAdClosed()
    		{
    	    	requestAdMob();
    		}
    	});
   
    	requestAdMob();
	}
	
	private static void requestAdMob()
	{
		AdRequest adRequest = new AdRequest.Builder()/*.addTestDevice("5A14E85D513F16D9BCC74FC8E09BBEA3")*/.build();
    	admobInterstitial.loadAd(adRequest);
	}
	
	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	@Override
	protected void onResume() {
		super.onResume();

		Cocos2dxHelper.onResume();
		this.mGLSurfaceView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		
		Cocos2dxHelper.onPause();
		this.mGLSurfaceView.onPause();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		
		/*if(adamInterstitial != null)
			adamInterstitial = null;*/
		
		if(admobInterstitial != null)
			admobInterstitial = null;
			
	}

	@Override
	public void showDialog(final String pTitle, final String pMessage) {
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_DIALOG;
		msg.obj = new Cocos2dxHandler.DialogMessage(pTitle, pMessage);
		this.mHandler.sendMessage(msg);
	}

	@Override
	public void showEditTextDialog(final String pTitle, final String pContent, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) { 
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_EDITBOX_DIALOG;
		msg.obj = new Cocos2dxHandler.EditBoxMessage(pTitle, pContent, pInputMode, pInputFlag, pReturnType, pMaxLength);
		this.mHandler.sendMessage(msg);
	}
	
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurfaceView.queueEvent(pRunnable);
	}
	
	@Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        for (OnActivityResultListener listener : Cocos2dxHelper.getOnActivityResultListeners()) {
            listener.onActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }


	protected FrameLayout mFrameLayout = null;
	// ===========================================================
	// Methods
	// ===========================================================
	public void init() {
		
    	// FrameLayout
        ViewGroup.LayoutParams framelayout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.MATCH_PARENT);
        mFrameLayout = new FrameLayout(this);
        mFrameLayout.setLayoutParams(framelayout_params);

        // Cocos2dxEditText layout
        ViewGroup.LayoutParams edittext_layout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.WRAP_CONTENT);
        Cocos2dxEditText edittext = new Cocos2dxEditText(this);
        edittext.setLayoutParams(edittext_layout_params);

        // ...add to FrameLayout
        mFrameLayout.addView(edittext);

        // Cocos2dxGLSurfaceView
        this.mGLSurfaceView = this.onCreateView();

        // ...add to FrameLayout
        mFrameLayout.addView(this.mGLSurfaceView);

        // Switch to supported OpenGL (ARGB888) mode on emulator
        if (isAndroidEmulator())
           this.mGLSurfaceView.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);

        this.mGLSurfaceView.setCocos2dxRenderer(new Cocos2dxRenderer());
        this.mGLSurfaceView.setCocos2dxEditText(edittext);

        // Set framelayout as the content view
		setContentView(mFrameLayout);
	}
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	return new Cocos2dxGLSurfaceView(this);
    }

   private final static boolean isAndroidEmulator() {
      String model = Build.MODEL;
      Log.d(TAG, "model=" + model);
      String product = Build.PRODUCT;
      Log.d(TAG, "product=" + product);
      boolean isEmulator = false;
      if (product != null) {
         isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
      }
      Log.d(TAG, "isEmulator=" + isEmulator);
      return isEmulator;
   }

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
   public static void openURL(String url)
   {
	   Intent i = new Intent(Intent.ACTION_VIEW);
	   i.setData(Uri.parse(url));
	   sContext.startActivity(i);
   }
   
	public static boolean showAd() {
		if(admobInterstitial != null && mAdHandler != null )
		{
			mAdHandler.sendEmptyMessage(MSG_SHOWAD);
			return true;
		}
		return false;
	}
}

package com.Horizon.Brick;

/**
 * Created by GwapoSiZob on 30/08/2017.
 */
 
import android.util.Log;
import android.widget.Switch;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.share.model.GameRequestContent;
import com.facebook.share.model.ShareOpenGraphAction;
import com.facebook.share.model.ShareOpenGraphContent;
import com.facebook.share.model.ShareOpenGraphObject;
import com.facebook.share.widget.GameRequestDialog;
import com.facebook.share.widget.MessageDialog;
import com.facebook.share.widget.ShareDialog;

import java.util.Map;

import com.epicgames.ue4.GameActivity;
import com.epicgames.ue4.Logger;

import org.json.JSONException;
import org.json.JSONObject;

public class FacebookShare {

    /**
     * Static representation of action types used for OpenGraph Stories
     */
    public static final int ACTION_PLAYS = 0;
    public static final int ACTION_CELEBRATE = 1;
    public static final int ACTION_SAVES = 2;
    public static final int ACTION_ACHIEVES = 3;

    /**
     * Responses supported by this class
     */
    public static final int FACEBOOK_RESPONSE_OK = 0;
    public static final int FACEBOOK_RESPONSE_CANCELED = 1;
    public static final int FACEBOOK_RESPONSE_PENDING = 2;
    public static final int FACEBOOK_RESPONSE_ERROR = 3;

    private GameActivity activity;

    /** Logging property. Used to out put log messages*/
    private Logger FBLog;

    /** Manages GameRequest's callbacks*/
    private CallbackManager callbackManager;

	private String objectLink;
	private String appID;

    public FacebookShare(GameActivity activity, String appID, String objectLink)
    {
        this.activity = activity;
		
		this.appID = appID; // "1375368315904124";
		this.objectLink = objectLink; // "http://play.google.com/store/apps/details?id=com.Horizon.Brick";

        FBLog = new Logger("UE4-FB");
    }

    public void Init()
    {
        callbackManager = CallbackManager.Factory.create();
    }

    /**
     * Exposed to be able to call onActivityResult
     *
     * @return the instance of the CallBackManagerImpl
     */
    public CallbackManager getCallbackManager() { return callbackManager; }


    /**
     * Called by GameActivity for sharing with the ShareDialog
     *
     * @param contentTitle Title of the Post to be published. This is where challenge quotes are
     *                     advised to be included
     * @param contentDescription Description of the post to be published. This is where scores are
     *                           advised to be included
     * @param imageLink Link to the image to be included with the post. Should be 600x600px for
     *                  small-format images or at least 1200px wide and with a ratio of at least
     *                  1.91:1 for large-format images
     * @param actionType Indicates whether the action_type for the OpenGraph is game.plays, games.saves,
     *                   games.celebrate of games.achieves
     */
    public void shareDialog(String contentTitle, String contentDescription,
                               String imageLink, int actionType)
    {
        FBLog.debug("FacebookShare: shareHighScore: started sharing to facebook");

        ShareDialog.show(this.activity, createOpenGraphContent(contentTitle, contentDescription,
                imageLink, actionType));
    }


    /**
     * Called by GameActivity for sharing to friends with the MessageDialog
     *
     * @param contentTitle Title of the Post to be published. This is where challenge quotes are
     *                     advised to be included
     * @param contentDescription Description of the post to be published. This is where scores are
     *                           advised to be included
     * @param imageLink Link to the image to be included with the post. Should be 600x600px for
     *                  small-format images or at least 1200px wide and with a ratio of at least
     *                  1.91:1 for large-format images
     * @param actionType Indicates whether the action_type for the OpenGraph is game.plays, games.saves,
     *                   games.celebrate of games.achieves
     */
    public void messageDialog(String contentTitle, String contentDescription,
                                 String imageLink, int actionType, String link)
    {
        FBLog.debug("FacebookShare: shareHighScore: started messaging to facebook");

        MessageDialog.show(this.activity, createOpenGraphContent(contentTitle, contentDescription,
                imageLink, actionType, link));
    }


    /**
     * Called by internal functions to create a content to be shared via ShareDialog or MessageDialog
     *
     * @param contentTitle Title of the Post to be published. This is where challenge quotes are
     *                     advised to be included
     * @param contentDescription Description of the post to be published. This is where scores are
     *                           advised to be included
     * @param imageLink Link to the image to be included with the post. Should be 600x600px for
     *                  small-format images or at least 1200px wide and with a ratio of at least
     *                  1.91:1 for large-format images
     * @param actionType Indicates whether the action_type for the OpenGraph is game.plays, games.saves,
     *                   games.celebrate of games.achieves
     *
     * @return ShareOpenGraphContent content The content created.
     */
    private ShareOpenGraphContent createOpenGraphContent(String contentTitle, String contentDescription,
                                                         String imageLink, int actionType)
    {
        // initializes the variables to be used for creating the object and action
        String objectType; // object type used for ShareOpenGraphObject property og:type
        String objectName; // used to reference the object from the action
        String actionName; // action  type used in creating the content

        switch (actionType)
        {
            case 0: // ACTION_PLAYS
                actionName = "games.plays";
                objectType = "games.victory";
                objectName = "game";
                    break;
            case 1: // ACTION_CELEBRATE
                actionName = "games.celebrate";
                objectType = "games.victory";
                objectName = "victory";
                    break;
            case 2: // ACTION_SAVES
                actionName = "games.saves";
                objectType = "games.victory";
                objectName = "game";
                    break;
            case 3: // ACTION_ACHIEVES
                actionName = "games.achieves";
                objectType = "game.achievement";
                objectName = "achievement";
                    break;
            default:
                actionName = "games.plays";
                objectType = "games.victory";
                objectName = "game";
                    break;

        } // End of switch-case actionType

        // Builds the object within the class ShareOpenGraphObject.Builder
        ShareOpenGraphObject.Builder objectBuilder = new ShareOpenGraphObject.Builder()
                .putString("fb:app_id", appID)
                .putString("og:type", objectType)
                .putString("og:title", contentTitle)
                .putString("og:description", contentDescription)
                .putString("og:image", imageLink);

		if (objectLink != null || !objectLink.isEmpty())
		{
			objectBuilder.putString("og:url", objectLink);
		}

        /** 
		 * Adding additional properties for the object.
         * Used for game:achievement's game:points or game:secret
		 * or adding additional OpenGraphProperties like og:video, og:determiner or many more.
		 * 
		 * Properties include but are not limited to what's on this list:
		 * https://developers.facebook.com/docs/sharing/opengraph/object-properties
		 */
//        for ( int i = 0; i < objectParams.length; i++) {
//          objectBuilder.putString(objectParams.getKey, objectParams.getValue);
//        }

        // Creates the object
        ShareOpenGraphObject object = objectBuilder.build();

        // Builds the action
        ShareOpenGraphAction.Builder actionBuilder = new ShareOpenGraphAction.Builder()
                .setActionType(actionName)
                .putObject(objectName, object);

//        /**
//		   * Adding additional properties for the object.
//         * Used for save's source token or story_type or achieve's importance.
//		   */
//        for ( int i = 0; i < actionParams.length; i++) {
//          actionBuilder.putString(actionParams.getKey, actionParams.getValue);
//        }

		// Create an action
		ShareOpenGraphAction action = actionBuilder.build();

        // Create the openGraphContent
        ShareOpenGraphContent openGraphContent = new ShareOpenGraphContent.Builder()
                .setPreviewPropertyName(objectName)
                .setAction(action)
                .build();

        return openGraphContent;
    }

	private ShareOpenGraphContent createOpenGraphContent(String contentTitle, String contentDescription,
                                                         String imageLink, int actionType, String link)
    {
        // initializes the variables to be used for creating the object and action
        String objectType; // object type used for ShareOpenGraphObject property og:type
        String objectName; // used to reference the object from the action
        String actionName; // action  type used in creating the content

        switch (actionType)
        {
            case 0: // ACTION_PLAYS
                actionName = "games.plays";
                objectType = "games.victory";
                objectName = "game";
                    break;
            case 1: // ACTION_CELEBRATE
                actionName = "games.celebrate";
                objectType = "games.victory";
                objectName = "victory";
                    break;
            case 2: // ACTION_SAVES
                actionName = "games.saves";
                objectType = "games.victory";
                objectName = "game";
                    break;
            case 3: // ACTION_ACHIEVES
                actionName = "games.achieves";
                objectType = "game.achievement";
                objectName = "achievement";
                    break;
            default:
                actionName = "games.plays";
                objectType = "games.victory";
                objectName = "game";
                    break;

        } // End of switch-case actionType

        // Builds the object within the class ShareOpenGraphObject.Builder
        ShareOpenGraphObject.Builder objectBuilder = new ShareOpenGraphObject.Builder()
                .putString("fb:app_id", appID)
				.putString("og:url", link)
                .putString("og:type", "website")
                .putString("og:title", contentTitle)
                .putString("og:description", contentDescription)
                .putString("og:image", imageLink);

        /** 
		 * Adding additional properties for the object.
         * Used for game:achievement's game:points or game:secret
		 * or adding additional OpenGraphProperties like og:video, og:determiner or many more.
		 * 
		 * Properties include but are not limited to what's on this list:
		 * https://developers.facebook.com/docs/sharing/opengraph/object-properties
		 */
//        for ( int i = 0; i < objectParams.length; i++) {
//          objectBuilder.putString(objectParams.getKey, objectParams.getValue);
//        }

        // Creates the object
        ShareOpenGraphObject object = objectBuilder.build();

		// Creates the privacy parameter object
		JSONObject privacy = new JSONObject();

		try {
		   privacy.put("value", "ALL_FRIENDS");
		} catch (JSONException e) {
		   e.printStackTrace();
		}

        // Builds the action
        ShareOpenGraphAction.Builder actionBuilder = new ShareOpenGraphAction.Builder()
                .setActionType(actionName)
                .putObject(objectName, object)
				.putString("privacy", privacy.toString());

//        /**
//		   * Adding additional properties for the object.
//         * Used for save's source token or story_type or achieve's importance.
//		   */
//        for ( int i = 0; i < actionParams.length; i++) {
//          actionBuilder.putString(actionParams.getKey, actionParams.getValue);
//        }

		// Create an action
		ShareOpenGraphAction action = actionBuilder.build();

        // Create the openGraphContent
        ShareOpenGraphContent openGraphContent = new ShareOpenGraphContent.Builder()
                .setPreviewPropertyName(objectName)
                .setAction(action)
                .build();
				
        return openGraphContent;
    }

    /**
     * Call when you want to publish a story or post for the user.
     * This needs the permissions "publish_actions" to use
     *
     * @param GraphPath the path to execute the OpenGraph Story to
     * @param peopleIds userId of facebook friends to tag this post with
     * @param openGraphParams Key-Value pairs. Properties of the given GraphPath
     */
    private void createOpenGraphStory(String GraphPath, String peopleIds[], Map[] openGraphParams)
    {
//        Bundle params = new Bundle();
//        for (int i = 0; i < openGraphParams.length; i++ )
//        {
//            params.putString(openGraphParams[i].getKey, openGraphParams[i].getValue);
//        }
//
//        GraphRequest request = new GraphRequest(AccessToken.getCurrentAccessToken(),
//                GraphPath, // "/me/games.celebrate",
//                params,
//                HttpMethod.POST,
//                new GraphRequest.Callback() {
//                    @Override
//                    public void onCompleted(GraphResponse response) {
//
//                    }
//                });
//        request.executeAsync();
    }

    /**
     * Called by GameActivity for sending Game Requests to facebook friends using
     * the GameRequestDialog
     *
     * @param message text to be added with the game request or challenge
     */
    public void GameRequest(String message)
    {
        GameRequestDialog requestDialog = new GameRequestDialog(activity);
        requestDialog.registerCallback(callbackManager, GameRequestCallBack());

        GameRequestContent content = new GameRequestContent.Builder()
                .setMessage(message)
                .build();

        requestDialog.show(content);
    }

    /**
     * Callback for GameRequestDialog
     *
     * @return the result of the callback
     */
    private FacebookCallback<GameRequestDialog.Result> GameRequestCallBack()
    {
        return new FacebookCallback<GameRequestDialog.Result>()
        {
            @Override
            public void onSuccess(GameRequestDialog.Result result)
            {
                // TODO: insert onGameRequestComplete features
                // or call nativeGameRequestComplete(FACEBOOK_RESPONSE_OK)
                // could be adding in-game credits for every invite
            }

            @Override
            public void onCancel()
            {

            }

            @Override
            public void onError(FacebookException error)
            {
                // TODO:insert onGameRequestComplete features
                // or call nativeGameRequestComplete(FACEBOOK_RESPONSE_ERROR)
            }
        };
    }
}
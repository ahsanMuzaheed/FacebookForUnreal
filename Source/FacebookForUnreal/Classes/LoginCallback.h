// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FacebookIdentityInterface.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FacebookForUnrealBPLibrary.h"
#include "LoginCallback.generated.h"

/**
 * 
 */

class FFacebookIdentityCommon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFacebookLogin, FString, AccessToken);

typedef TSharedPtr<class IOnlineIdentity, ESPMode::ThreadSafe> IOnlineIdentityPtr;

UCLASS()
class FACEBOOKFORUNREAL_API ULoginCallback : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	ULoginCallback();
	~ULoginCallback();

	IOnlineIdentityPtr IdentityPtr;

	//Delegate instance
	UPROPERTY(BlueprintAssignable)
		FOnFacebookLogin OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FOnFacebookLogin OnFailure;
	
	/**
	* Logs Facebook in to the user logged in on the Facebook App installed on device.
	* If there is no Facebook App or is Logged out, a login dialog will appear.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FacebookLogin", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Facebook")
		static ULoginCallback* FacebookLogin();

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	// End of UBlueprintAsyncActionBase interface

private:

	FDelegateHandle OnLoginCompleteDelegatehandle;

	virtual void ReturnAccessToken(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

};

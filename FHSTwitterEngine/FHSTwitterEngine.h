//
//  FHSTwitterEngine.h
//  FHSTwitterEngine
//
//  Created by Nathaniel Symer on 8/22/12.
//  Copyright (C) 2012 Nathaniel Symer.

//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//


//
// FHSTwitterEngine
// The synchronous Twitter engine that doesn’t suck!!
//


// FHSTwitterEngine is Synchronous
// That means you will have to thread. Boo Hoo.

// Setup
// Just add the FHSTwitterEngine folder to you project.

// USAGE
// See README.markdown

// Return Codes:
// (These apply to any method that returns an int)
// (You can look them up using the lookupErrorCode: method)
// 0 - Success
// 1 - API Error (Params are invalid - missing params here are my fault)
// 2 - Insufficient input (missing a parameter, your fault)
// 3 - Image too large (bigger than 700KB)
// 4 - User unauthorized 
// 304 to 504 - HTTP/Twitter response code. Look these up here. (My favorite is Error 420 - Enhance Your Calm)

//
// NOTE TO CONTRIBUTORS
// There is an excellent JSON parser INCLUDED in the iOS SDK called NSJSONSerialization. Please use it for the sake of my (our) users.
//


#import <Foundation/Foundation.h>

// These are for the dispatch_async() calls that you use to get around the synchronous-ness
#define GCDBackgroundThread dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
#define GCDMainThread dispatch_get_main_queue()

@interface FHSTwitterEngine : NSObject <UIWebViewDelegate>

//
// REST API
//

// Custom REST API methods
// friends/ids & users/lookup OR followers/ids & users/lookup
// (The second being called once for every 99 id's) - can be expensive CACHE CACHE CACHE

- (NSArray *)getFollowers;
- (NSArray *)getFriends;

// statuses/update
- (int)postTweet:(NSString *)tweetString inReplyTo:(NSString *)inReplyToString;
- (int)postTweet:(NSString *)tweetString;

// statuses/home_timeline
- (id)getHomeTimelineSinceID:(NSString *)sinceID startingAtPage:(int)pageNum count:(int)count;

// help/test
- (BOOL)testService;

// blocks/create
- (int)block:(NSString *)username;

// blocks/destroy
- (int)unblock:(NSString *)username;

// users/lookup
- (id)getUserInformationForUsers:(NSArray *)users areUsers:(BOOL)flag;

// notifications/follow & notifications/leave
- (int)disableNotificationsForID:(NSString *)identifier;
- (int)disableNotificationsForUsername:(NSString *)username;
- (int)enableNotificationsForID:(NSString *)identifier;
- (int)enableNotificationsForUsername:(NSString *)identifier;

// account/totals
- (NSDictionary *)getTotals;

// account/update_profile_image
- (int)setProfileImageWithImageAtPath:(NSString *)file;

// account/settings POST & GET
// See FHSTwitterEngine.m for details
- (int)updateSettingsWithDictionary:(NSDictionary *)settings;
- (NSDictionary *)getUserSettings;

// account/update_profile
// See FHSTwitterEngine.m for details
- (int)updateUserProfileWithDictionary:(NSDictionary *)settings;

// account/update_profile_background_image
- (int)setProfileBackgroundImageWithImageAtPath:(NSString *)file tiled:(BOOL)flag;
- (int)setUseProfileImage:(BOOL)shouldUseProfileImage;

// account/update_profile_colors
// See FHSTwitterEngine.m for details
// If the dictionary is nil, FHSTwitterEngine resets the values
- (int)updateProfileColorsWithDictionary:(NSDictionary *)dictionary;

// account/rate_limit_status
- (id)getRateLimitStatus;

// favorites/create, favorites/destroy
- (int)markTweet:(NSString *)tweetID asFavorite:(BOOL)flag;

// account/verify_credentials
- (id)verifyCredentials;



//
// Login and Auth
//

// XAuth login
- (int)getXAuthAccessTokenForUsername:(NSString *)username password:(NSString *)password;

// OAuth login
- (UIViewController *)OAuthLoginWindow; // You want to use it with something other than presentModalViewController:animated:
- (void)showOAuthLoginControllerFromViewController:(UIViewController *)sender; // just one less line of code

// Access Token Mangement
- (void)clearAccessToken;
- (void)loadAccessToken;
- (BOOL)isAuthorized;


//
// Misc Methods
//

// Date parser
- (NSDate *)getDateFromTwitterCreatedAt:(NSString *)twitterDate;

// Error code lookup
// (so you don't have to)
// Keys:
// message - (its the error message)
// title - (its the error code and title)
- (NSDictionary *)lookupErrorCode:(int)errorCode;

// init method
- (id)initWithConsumerKey:(NSString *)consumerKey andSecret:(NSString *)consumerSecret;

// Logged in user's username
@property (nonatomic, strong) NSString *loggedInUsername;

@end
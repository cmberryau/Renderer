//
//  main.m
//  Renderer-iOS
//
//  Created by Christopher Berry on 14/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

#import <MediaPlayer/MPNowPlayingInfoCenter.h>

int main(int argc, char * argv[]) {
    //NSMutableDictionary *playInfo = [NSMutableDictionary dictionaryWithDictionary:[MPNowPlayingInfoCenter defaultCenter].nowPlayingInfo];
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

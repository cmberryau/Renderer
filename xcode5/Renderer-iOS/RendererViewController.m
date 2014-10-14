//
//  ViewController.m
//  Renderer-iOS
//
//  Created by Christopher Berry on 14/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "RendererViewController.h"

@interface RendererViewController ()

@end

@implementation RendererViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // Create an OpenGL ES context and assign it to the view loaded from storyboard
    GLKView *view = (GLKView *)self.view;
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    // Set animation frame rate
    self.preferredFramesPerSecond = 60;
}

- (void)update
{
    
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

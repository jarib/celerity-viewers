#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface AppController : NSObject {
	
    IBOutlet id webView;
    NSSocketPort* socketPort;
    NSFileHandle* fileHandle;
    NSNotificationCenter* nc;
}

-(void)awakeFromNib;
-(void)setupWebView;
-(void)setupSocket;
-(void)handleConnection:(NSNotification *)notification;
-(void)updateWithData:(NSData*)data;

@end

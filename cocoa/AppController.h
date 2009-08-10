#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface AppController : NSObject {

    IBOutlet id webView;
    IBOutlet id window;

    NSSocketPort* socketPort;
    NSFileHandle* fileHandle;
}

-(void)awakeFromNib;
-(void)applicationWillTerminate;
-(void)setupWebView;
-(void)setupSocket;
-(void)handleConnection:(NSNotification *)notification;
-(void)processFileHandle:(NSFileHandle *)fh;
-(void)updateWithData:(NSData*)data;
-(void)alert:(NSString*)message;
-(void)save;
@end

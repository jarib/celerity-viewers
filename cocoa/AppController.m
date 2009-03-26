#import "AppController.h"

@implementation AppController

-(void)awakeFromNib 
{
	[self setupWebView];
	[self setupSocket];
}

- (void)setupWebView
{
	[[NSUserDefaults standardUserDefaults] setObject:@"YES" forKey:@"WebKitDeveloperExtras"];
	[[webView preferences] setShouldPrintBackgrounds: YES];
}

- (void)setupSocket
{
	socketPort = [[NSSocketPort alloc] initWithTCPPort:6429];
	NSLog(@"socketPort: %@", socketPort);
	fileHandle = [[NSFileHandle alloc] initWithFileDescriptor:[socketPort socket]
											   closeOnDealloc:YES];
	
	nc = [NSNotificationCenter defaultCenter];
	[nc addObserver:self
		   selector:@selector(handleConnection:)
			   name:NSFileHandleConnectionAcceptedNotification
			 object:nil];
	
	[fileHandle acceptConnectionInBackgroundAndNotify];	
}

- (void)handleConnection:(NSNotification *)notification
{
	NSDictionary* userInfo = [notification userInfo];
	NSFileHandle* remoteFileHandle = [userInfo objectForKey:
									  NSFileHandleNotificationFileHandleItem];
	
	NSNumber* errorNo = [userInfo objectForKey:@"NSFileHandleError"];
	if(errorNo) 
	{
		NSLog(@"NSFileHandle Error: %s", strerror([errorNo intValue]));
		return;
	}
	
	[fileHandle acceptConnectionInBackgroundAndNotify];
	if(remoteFileHandle) 
		[self updateWithData:[remoteFileHandle readDataToEndOfFile]]; 
}


- (void)updateWithData:(NSData*)data
{
	if([data length] == 0) {
		NSLog(@"connection closed");
	} else {
		NSString* html = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		[[webView mainFrame] loadHTMLString:html baseURL:nil];
	}	
}

- (void)dealloc
{
    [nc removeObserver:self];
	[fileHandle release];
    [socketPort release];
    [super dealloc];
}
@end
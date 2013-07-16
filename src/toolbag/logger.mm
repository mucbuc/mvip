#import <Cocoa/Cocoa.h>
#include "logger.h"

#if 0 
void PostMessageToLocalHost(const char * message)
{
	NSURL *url = [NSURL URLWithString: @"http://localhost:8081"];
	NSMutableURLRequest* urlRequest = [[NSMutableURLRequest alloc] initWithURL:url];
	[urlRequest setHTTPMethod:@"POST"];
    
    NSString * body = [ [ NSString alloc ] initWithString:@"message=" ];
    body = [ body stringByAppendingString: [ NSString stringWithUTF8String:message ] ];
  	[urlRequest setHTTPBody:[ body dataUsingEncoding:NSUTF8StringEncoding ] ];   
	[NSURLConnection connectionWithRequest:urlRequest delegate:nil];
}
#endif 

begin
require 'rubygems'
rescue LoadError
end
require 'osx/cocoa'
require 'pathname'

include OSX
require_framework 'WebKit'


def log(*args)
	args.each do |m|
    NSLog m.inspect
	end
end

def _(key)
	NSLocalizedString(key, '').to_s
end

path = Pathname.new NSBundle.mainBundle.resourcePath.fileSystemRepresentation
Pathname.glob(path + '*.rb') do |file|
	next if file.to_s == __FILE__
	require(file)
end

# require "ruby-debug"
# Debugger.wait_connection = true
# Debugger.start_server

NSApplication.sharedApplication
NSApplicationMain(0, nil)



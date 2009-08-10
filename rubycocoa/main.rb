
begin
require 'rubygems'
rescue LoadError
end

require 'osx/cocoa'
require 'pathname'
include OSX
require_framework 'WebKit'


def log(*args)
  File.open("/tmp/cvlog.txt", "a") do |f|
  	args.each { |m| f.puts m.inspect }
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

Thread.abort_on_exception = true

NSApplication.sharedApplication
NSApplicationMain(0, nil)



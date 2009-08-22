require "rubygems"
require "sinatra/base"
require "json"


class HtmlSnapService < Sinatra::Base
  set :environment, :production

  get "/" do
    "please POST some html"
  end

  post "/" do
    send 'html' => request.body.read
    read['image']
  end

  private

  def send(msg)
    json = msg.to_json
    socket.write "Content-Length: #{json.size}\n\n#{json}"
    socket.flush

    nil
  end

  def read
    buf = ''
    until buf =~ /\n\n\z/ || socket.eof? || socket.closed?
      buf << socket.read(1).to_s
    end

    return if buf.empty?

    length = buf[/Content-Length: (\d+)/, 1].to_i
    JSON.parse socket.read(length)
  end

  def socket
    @socket ||= TCPSocket.new("localhost", 6429)
  end
end

if __FILE__ == $0
  if ARGV.size == 1
    HtmlSnapService.set :port, Integer(ARGV.shift)
  end

  fork { exec "#{File.dirname(__FILE__)}/htmlsnap" }
  HtmlSnapService.run!
end


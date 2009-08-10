require "socket"

module CelerityServer
  def start_server
    server = TCPServer.new("0.0.0.0", 6429)

    loop {
      s = server.accept
      Thread.new(s) do |socket|
        begin
          handle_socket socket
        rescue => e
          log e
        end
      end
    }
  end

  def handle_socket(socket)
    log(:accepted => socket)

    until socket.closed?
      data = read_from socket

      case data['method']
      when 'render_html'
        render_html data['html'], data['url']
      when 'save'
        save data['path']
      end
    end
  end

  def read_from(socket)
    buf = ''
    until buf =~ /\n\n\z/
      buf << socket.read(1).to_s
    end

    log :buf => buf if $DEBUG
    length = buf[/Content-Length: (\d+)/, 1].to_i
    log :length => length if $DEBUG

    JSON.parse(socket.read(length))
  end
end

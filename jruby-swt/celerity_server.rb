require "socket"

module CelerityServer
  def start_server
    server = TCPServer.new("0.0.0.0", 6429)

    loop {
      s = server.accept
      Thread.new(s) do |socket|
        begin
          handle_socket socket
        rescue
          $stderr.puts $!, $@
        end
      end
    }
  end

  def handle_socket(socket)
    $stderr.puts "accepted => #{socket.inspect}"

    until socket.closed?
      data = read_from socket
      return if data.nil?

      case data['method']
      when 'page_changed'
        render_html data['html'], data['url']
      when 'save'
        save data['path']
      end
    end
  end

  def read_from(socket)
    buf = ''
    until buf =~ /\n\n\z/ || socket.eof? || socket.closed?
      buf << socket.read(1).to_s
    end

    return if buf.empty?

    length = buf[/Content-Length: (\d+)/, 1].to_i
    JSON.parse socket.read(length)
  end
end

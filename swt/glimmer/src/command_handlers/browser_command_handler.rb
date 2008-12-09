class BrowserWidget < RWidget
  def initialize(parent, style = nil &block)
    super("browser", parent, style, &block)
  end
end

class BrowserCommandHandler
  include CommandHandler

  def can_handle?(parent, command_symbol, *args, &block)
    command_symbol.to_s == "browser"
  end

  def do_handle(parent, command_symbol, *args, &block)
    p :args => args
    BrowserWidget.new(parent, args.shift, &block)
  end
end


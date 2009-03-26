require "drb"
require "drb/acl"
require "uri"
require "fileutils"

DRb.install_acl(ACL.new(%w[deny all allow 127.0.0.1]))


class MainController < NSObject
  ib_outlets :web_view, :text_field, :status_label, :window

  def awakeFromNib
    @window.delegate = self # for windowWillClose
    setup_webview
    setup_counters
    setup_panel
    load_url
    start_drb
    # start_tcp_server
  rescue
    log $!
    raise $!
  end

  def setup_panel
    @window.floatingPanel = false
  end

  def setup_webview
    NSUserDefaults.standardUserDefaults.setObject_forKey('YES', 'WebKitDeveloperExtras')
    @web_view.preferences.setShouldPrintBackgrounds(true)
    @web_view.frameLoadDelegate = self
  end

  def setup_counters
    @save_count = 0
    @update_count = 0
    @status_label.stringValue = "Updated: #{@update_count} times."
  end

  def start_drb
    DRb.start_service("druby://127.0.0.1:6429", self)
  end
  
  def start_tcp_server
    server = TCPServer.open("localhost", 6429)
    Thread.new do
      loop do
        sock = server.accept
        render_html(sock.read)
        sock.close
      end
    end
  end

  def load_url(sender = @text_field)
    str = sender.stringValue
    url = str.to_ruby =~ /^https?/ ? str : "http://#{str}"
    @web_view.setMainFrameURL(url)
  end

  def bump_count
    @update_count += 1
    @status_label.stringValue = "Updated: #{@update_count} times."
  end

  def alert(message, title = "Error")
    alert = NSAlert.alloc.init
    alert.setMessageText(message)
    alert.setInformativeText(title)
    alert.setAlertStyle(NSCriticalAlertStyle)
    alert.beginSheetModalForWindow_modalDelegate_didEndSelector_contextInfo(@window, self, nil, nil)
  end

  def render_html(html, url = nil)
    if url
      uri = URI.parse(url)
      base_url = "#{uri.scheme}://#{uri.host}"
      @text_field.stringValue = url
      url = NSURL.URLWithString(base_url)
    end
    @web_view.mainFrame.loadHTMLString_baseURL(html, url)
    bump_count
  rescue => e
    log(e)
  end

  def save(path = nil)
    @save_count += 1
    return @web_view.print(nil) unless path

    viewport        = @web_view.mainFrame.frameView.documentView
    viewport_bounds = viewport.bounds
    image_rep       = viewport.bitmapImageRepForCachingDisplayInRect(viewport_bounds)
    FileUtils.mkdir_p File.dirname(path)

    viewport.cacheDisplayInRect_toBitmapImageRep(viewport_bounds, image_rep)

    return unless image_rep

    image_rep.representationUsingType_properties(NSPNGFileType, nil).writeToFile_atomically(path, true)
    log("Wrote screenshot to #{path}")

    @save_count
  rescue => e
    log($!, $@)
    raise e
  end

  #
  # delegate methods
  #

  def windowWillClose(sender)
    NSApplication.sharedApplication.terminate(0)
  end

  def webView_didStartProvisionalLoadForFrame(view, frame)
    @text_field.stringValue = view.mainFrameURL
  end

  # for debugging
  # def respond_to?(*args)
  #   retval = super
  #   p :respond_to => args, :retval => retval
  #   retval
  # end
end

require "rubygems"
require "uri"

missing_gems = []

begin
  require "json"
rescue LoadError
  missing_gems << "json-jruby"
end

begin 
  require "facets" # glimmer dep.
rescue LoadError
  missing_gems << "facets"
end

unless missing_gems.empty?
  $stderr.puts "You need to run `jruby -S gem install #{missing_gems.join ' '}`"
  exit 1
end

begin
  require "swt.jar"
rescue LoadError => e
  puts e.message + " (inside jar?)"
end

require "glimmer/src/swt"
require "celerity_server"

class CelerityViewer
  include CelerityServer
  include_package 'org.eclipse.swt'
  include_package 'org.eclipse.swt.layout'

  include Glimmer

  INSPECTORS = {
    "v1" => "javascript:void(z=document.body.appendChild(document.createElement('script')));void(z.language='javascript');void(z.type='text/javascript');void(z.src='http://slayeroffice.com/tools/modi/modi.js');void(z.id='modi');",
    "v2" => "javascript:prefFile='';void(z=document.body.appendChild(document.createElement('script')));void(z.language='javascript');void(z.type='text/javascript');void(z.src='http://slayeroffice.com/tools/modi/v2.0/modi_v2.0.js');void(z.id='modi');"
  }

  attr_accessor :inspector, :inspector_options

  def initialize
    Thread.new { start_server }
    @style = ENV['SWT_MOZILLA'] ? SWT::MOZILLA : SWT::NONE

    @inspector_options = INSPECTORS.keys
    @inspector = "v2"
  end

  def launch
    shell do
      text         "CelerityViewer"
      minimum_size 300, 400
      location     100, 50

      composite do
        @browser = browser(@style) do
          layoutData GridData.new(fill, fill, true, true)
        end

        composite do
          layout GridLayout.new(3, false)
          button do
            text "Inspector"
            on_widget_selected { show_inspector }
          end

          combo(SWT::READ_ONLY) do
            selection bind(self, :inspector)
          end

          button do
            text "Reset"
            on_widget_selected { reset }
          end
        end
      end

    end.open
    exit(0)
  end

  def render_html(string, base_url = nil)
    if base_url
      uri = URI.parse(base_url)
      string = %Q{<base href="#{uri.scheme}://#{uri.host}">\n#{string}}
    end

    @html = string
    runnable = lambda { @browser.widget.setText(@html) }
    @browser.widget.getDisplay.asyncExec(runnable)
  rescue
    puts $!, $@
  end

  def save(path = nil)
    # does nothing
  end

  def show_inspector
    @browser.widget.execute(INSPECTORS[@inspector])
  end

  def reset
    render_html(@html)
  end

end

CelerityViewer.new.launch



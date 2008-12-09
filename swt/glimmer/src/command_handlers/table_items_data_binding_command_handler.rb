################################################################################
# Copyright (c) 2008 Annas Al Maleh.
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html
#
# Contributors:
#    Annas Al Maleh - initial API and implementation
################################################################################ 

require "glimmer/src/command_handler"
require "glimmer/src/command_handlers" + "/models/r_widget"
require "glimmer/src/command_handlers" + "/models/table_items_updater"

class TableItemsDataBindingCommandHandler
  include CommandHandler
  
  include_package 'org.eclipse.swt.widgets'

  def can_handle?(parent, command_symbol, *args, &block)
    parent.is_a?(RWidget) and
    parent.widget.is_a?(Table) and
    command_symbol.to_s == "items" and
    args.size == 2 and
    args[0].is_a?(ModelObserver) and
    args[0].evaluate_property.is_a?(Array) and
    args[1].is_a?(Array) and
    block == nil
  end
  
  def do_handle(parent, command_symbol, *args, &block)
    model_observer = args[0]
    column_properties = args[1]
    TableItemsUpdater.new(parent, model_observer, column_properties)
  end

end
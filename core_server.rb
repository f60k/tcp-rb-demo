#
#  core_server.rb
#  TestTcp
#
#  Created by 柳 大介 on 08/05/10.
#  Copyright (c) 2008 __MyCompanyName__. All rights reserved.
#

class CoreServer

	attr_accessor :delegate, :port
	attr_reader

	def initialize
		@sock = TcpServer.alloc.init
		@sock.delegate = self
	end
	
	def open
		return unless @sock
		@sock.open
	end
	
	def tcpserver_on_accept(sender, c)
		p "s_accept"
		@delegate.
	end
	
	def tcpserver_on_connect(sender, c)
		p "s_connect"
		@items=[["dave",122],["mark",123]]
		@table.reloadData
	end
	
	def tcpserver_on_error(sender, c, err)
		p "s_error"
	end
	
	def tcpserver_on_disconnect(sender, c)
		p "s_disconnect"
	end
	
	def tcpserver_on_read(sender, c)
		p "s_read >", c.read
	end
	
	def tcpserver_on_write(sender, c)
		p "s_write"
	end

end

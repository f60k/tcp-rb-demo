#
#  AppController.rb
#  TestTcp
#
#  Created by 柳 大介 on 08/05/09.
#  Copyright (c) 2008 __MyCompanyName__. All rights reserved.
#
require 'pathname'
require 'osx/cocoa'
class AppController < OSX::NSObject
	
	include OSX
	
	ib_outlet :table
	ib_action :onBrowse
	
	def initialize
	
	@myaddress="127.0.0.1"
	@items=[]
	
	end
	
	def awakeFromNib
		
		
		@sock = TcpServer.alloc.init
		@sock.delegate = self
		@sock.port = 12341
		@sock.open
		
		@rsock= TcpClient.alloc.init
		@rsock.port = 12341
		@rsock.delegate = self
		@rsock.host = 'localhost'
		@rsock.open
		

		
		end
	
	def detect_myaddress_from_nic
    addr = Socket.getaddrinfo(Socket.gethostname, nil)
    addr = addr.find {|i| !(/\.local$/ =~ i[2])}
    Resolver.resolve(self, addr[2]) if addr
  rescue
    @myaddress = nil
  end
  
	def tcpclient_on_connect(sender)
		p "c_connect"
		#p @sock.clients
		
		#@rsock.close
		#		p detect_myaddress_from_nic
		
		end
	
	def tcpclient_on_disconnect(sender)
		p "c_disconnect"
		end
	
	def tcpclient_on_error(sender, err)
		p "c_error"
		end
	
	def tcpclient_on_read(sender)
		p "c_read"
		end
	
	def tcpclient_on_write(sender)
		p "c_write"
		end
	
	def tcpserver_on_accept(sender, c)
		
		p "s_accept"
		
		end
	
	def tcpserver_on_connect(sender, c)
		p "s_connect"
		@items=[["dave",122],["mark",123]]
		@table.reloadData
		
		c.write("client wrote")
		
		end
	
	def tcpserver_on_error(sender, c, err)
		p "s_error"
		end
	
	def tcpserver_on_disconnect(sender, c)
		p "s_disconnect"
		end
	
	def tcpserver_on_read(sender, c)
		p "s_read"
		
		p c.read
	end
	
	def tcpserver_on_write(sender, c)
		p "s_write"
		p c.read
		
		end
	
def onBrowse(sender)
    @send.cancel(nil) if @send
    
    @send = NSOpenPanel.openPanel	#open dialog on OSX
    @send.setCanChooseFiles(true)
    @send.setCanChooseDirectories(false)
    @send.setResolvesAliases(true)
    @send.setAllowsMultipleSelection(true)
    @send.beginForDirectory_file_types_modelessDelegate_didEndSelector_contextInfo('~/Desktop', nil, nil, self, 'sendFilePanelDidEnd:returnCode:contextInfo:', nil)
  end
  
def sendFilePanelDidEnd_returnCode_contextInfo(panel, code, info)

    @send = nil
    return if code != NSOKButton

    files = panel.filenames.to_a
    files = files.map {|i| i.to_s}
	
	
	#targets.each do |t|
      files.each {|f| sendFile(f) }
	  #files.each {|f| add_sender(f)}
    #end
  end
  
  def sendFile(f)
	setfilename(f)
	open_file
	send_file(nil, @port, @full_filename, @size)
  end
  
  def open_file
    close_file if @file
    begin
      @file = @full_filename.open('rb')
	  p "open",@file
	  
	  
	  
    rescue
		p "err"
		p @full_filename
    
    end
  end
  
  def send_file(nick, port, fname, size)
    morph_fname = nil#fname.gsub(/ /, '_')
    if /\A(\d+)\.(\d+)\.(\d+)\.(\d+)\z/ =~ @myaddress
      w, x, y, z = $1.to_i, $2.to_i, $3.to_i, $4.to_i
      addr = w; addr <<= 8
      addr |= x; addr <<= 8
      addr |= y; addr <<= 8
      addr |= z
    else
      addr = @myaddress
    end
    send_ctcp_query(nick, 'DCC SEND', "#{morph_fname} #{addr} #{port} #{size} 2 :#{fname}")
    #print_both(self, :dcc_send_send, "Trying file transfer to #{nick}, #{fname} (#{size.grouped_by_comma} bytes) #{@myaddress}:#{port}")
 
  
   
	 end
  
  def send_ctcp_query(target, cmd, body=nil)
    cmd = cmd.to_s.upcase
    s = "\x01#{cmd}"
    s << " #{body}" if body && !body.empty?
    s << "\x01"
    #send(:privmsg, target, s)
	
	@rsock.write(s)
	
  end
  
  
  
  
def close_file
    return unless @file
    @file.close
    @file = nil
  end

    #setter
  def setfilename(v)
  
  p "ffff"
  
    @full_filename = Pathname.new(v)
    @size = @full_filename.size?
    @filename = @full_filename.basename.to_s
    ext = @full_filename.extname
    ext[0] = '' if ext[0..0] == '.'
    @icon = NSWorkspace.sharedWorkspace.iconForFileType(ext)
	
  end
  
  #getter
  def filename
    @full_filename.to_s
  end
# NSTableView dataSource

  def numberOfRowsInTableView(sender)
    @items.length
  end

  def tableView_objectValueForTableColumn_row(sender, col, row)
    if col.identifier.to_s == "user_col"
      @items[row][0]
    else
      @items[row][1]
    end
  end

  
end

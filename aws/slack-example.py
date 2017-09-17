from slackclient import SlackClient

# Don't prefix the #
channel_name = 'apitest'

# Your API key is actually found at https://api.slack.com/web
token = 'your API key'
sc = SlackClient(token)
sc.rtm_connect()

# Example from README.md doesn't work, raises exception. 
# sc.rtm_send_message('#apitest', 'DISAPPOINTED') 

# rtm_send_message() is a proxy for server.channels.find(channel).send_message(message)
# find() doesn't do what you expect, it takes a channel ID, not a name. You need to:
try:
	channel = next(channel for channel in sc.server.channels if channel.name==channel_name)
except StopIteration:
	raise Exception('Could not find channel: #%s' % channel_name)
	
channel.send_message('My favorite video: https://www.youtube.com/watch?v=_O1hM-k3aUY')

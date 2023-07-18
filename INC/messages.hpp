#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# define JOIN(source, channel, nick) ":" + source + " JOIN :" + channel + " :" + nick
# define PRIV(source, channel, msg) ":" + source + " PRIVMSG " + channel + " " + msg
# define KICK(source, channel, nick, reason) ":" + source + " KICK " + channel + " " + nick + " :" + reason
# define NOTICE(source, dest, msg) ":" + source + " NOTICE " + dest + " " + msg
# define PING(source, nick) ":" + source + " PONG :" + nick
# define NICK(source, nick) ":" + source + " NICK " + nick
# define TOPIC(source, channel, topic) ":" + source + " TOPIC " + channel + " " + topic


#endif // !MESSAGE_HPP
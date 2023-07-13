#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# define JOIN(source, channel, nick) ":" + source + " JOIN :" + channel + " :" + nick
# define PRIV(source, channel, msg) ":" + source + " PRIVMSG " + channel + " :" + msg + ":"

#endif // !MESSAGE_HPP
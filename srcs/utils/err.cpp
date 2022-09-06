#include "../utils/libs.hpp"

std::string getErr(const std::string &function, std::string socketFd, const std::string &msg)
{
	return (red("Fatal error " + function + (socketFd != "" ? " at socket " + const_cast<const std::string &>(socketFd) : "") +": " + msg));
}

std::string errnoMgmt(const std::string &function, std::string socketFd, int err)
{
	if (function == "recv")
	{
		switch (err)
		{
			case EAGAIN:
				return (getErr(function, socketFd, "The socket is marked nonblocking and the receive operation would block, or a receive timeout had been set and the timeout expired before data was received"));
			case EBADF:
				return (getErr(function, socketFd, "The argument sockfd is an invalid file descriptor"));
			case ECONNREFUSED:
				return (getErr(function, socketFd, "A remote host refused to allow the network connection"));
			case EFAULT:
				return (getErr(function, socketFd, "The receive buffer pointer(s) point outside the process's address space"));
			case EINTR:
				return (getErr(function, socketFd, "The receive was interrupted by delivery of a signal before any data was available"));
			case EINVAL:
				return (getErr(function, socketFd, "Invalid argument passed."));
			case ENOMEM:
				return (getErr(function, socketFd, "Could not allocate memory for recvmsg"));
			case ENOTCONN:
				return (getErr(function, socketFd, "The socket is associated with a connection-oriented protocol and has not been connected"));
			case ENOTSOCK:
			    	return (getErr(function, socketFd, "The file descriptor sockfd does not refer to a socket"));
			default:
				return (getErr(function, socketFd, "Couldn't read"));
		}
	}
	
	else if (function == "accept")
	{
		switch (err)
		{
			case EAGAIN:
				return (getErr(function, socketFd, "The socket is marked nonblocking and no connections are present to be accepted"));
			case EBADF:
				return (getErr(function, socketFd, "sockfd is not an open file descriptor."));
			case ECONNABORTED:
				return (getErr(function, socketFd, "A connection has been aborted"));
			case EFAULT:
				return (getErr(function, socketFd, "The addr argument is not in a writable part of the use address space."));
			case EINTR:
				return (getErr(function, socketFd, "The system call was interrupted by a signal that was caught before a valid connection arrived"));
			case EINVAL:
				return (getErr(function, socketFd, "Socket is not listening for connections, or addrlen is invalid"));
			case EMFILE:
				return (getErr(function, socketFd, "The per-process limit on the number of open file descriptors has been reached."));
			case ENFILE:
				return (getErr(function, socketFd, "The system-wide limit on the total number of open files has been reached."));
			case ENOBUFS:
				return (getErr(function, socketFd, "Not enough free memory"));
			case ENOMEM:
				return (getErr(function, socketFd, "Not enough free memory"));
			case ENOTSOCK:
				return (getErr(function, socketFd, "The file descriptor sockfd does not refer to a socket"));
			case EOPNOTSUPP:
				return (getErr(function, socketFd, "The referenced socket is not of type SOCK_STREAM"));
			case EPERM:
				return (getErr(function, socketFd, "Firewall rules forbid connection"));
			case EPROTO:
				return (getErr(function, socketFd, "Protocol error"));
			default:
				return (getErr(function, socketFd, "Couldn't accept"));
		}
	}
	else if (function == "send")
	{
		switch (err)
		{
			case EACCES:
				 return (getErr(function, socketFd, "Write permission is denied on the destination socket file, or search permission is denied for one of the directories the path prefix"));
			case EAGAIN:
				return (getErr(function, socketFd, "The socket is marked nonblocking and the requested operation would block"));
			case EALREADY:
				return (getErr(function, socketFd, "Another Fast Open is in progress"));
			case EBADF:
				return (getErr(function, socketFd, "sockfd is not a valid file descriptor."));
			case ECONNRESET:
				return (getErr(function, socketFd, "Connection reset by peer"));
			case EFAULT:
				return (getErr(function, socketFd, "An invalid user space address was specified for an argument"));
			case EINTR:
				return (getErr(function, socketFd, "A signal occurred before any data was transmitted"));
			case EINVAL:
				return (getErr(function, socketFd, "Invalid argument passed"));
			case EISCONN:
              			return (getErr(function, socketFd, "The connection-mode socket was connected already but a recipient was specified"));
			case EMSGSIZE:
              			return (getErr(function, socketFd, "The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible"));
			case ENOBUFS:
				return (getErr(function, socketFd, "The output queue for a network interface was full"));
			case ENOMEM:
				return (getErr(function, socketFd, "Not enough free memory"));
			case ENOTSOCK:
				return (getErr(function, socketFd, "The file descriptor sockfd does not refer to a socket"));
			case EOPNOTSUPP:
				return (getErr(function, socketFd, "Some bit in the flags argument is inappropriate for the socket type"));
			default:
				return (getErr(function, socketFd, "Coundn't send"));
		}	
	}
	else if (function == "poll")
	{
		switch (err)
		{
			case EFAULT:
				return (getErr(function, "", "fds points outside the process's accessible address space"));
			case EINTR:
				return (getErr(function, "", "A signal occurred before any requested event"));
       			case EINVAL:
				return (getErr(function, "", "The nfds value exceeds the RLIMIT_NOFILE value"));
       			case ENOMEM:
				return (getErr(function, "", "Unable to allocate memory for kernel data structures"));
			default:
				return (getErr(function, "", "failed to execute"));
		}
	}
	else
		return (getErr(function, "", "failed to execute"));
}

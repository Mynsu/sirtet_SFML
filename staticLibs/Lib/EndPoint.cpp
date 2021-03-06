#pragma hdrstop
#include "EndPoint.h"
#include <Ws2tcpip.h> // inet_pton(...)

EndPoint EndPoint::Any;

EndPoint::EndPoint( )
{
	ZeroMemory( &mIPv4EP, sizeof(mIPv4EP) );
	mIPv4EP.sin_family = AF_INET;
}

EndPoint::EndPoint( const char* const ipAddress, const uint16_t port )
{
	ZeroMemory( &mIPv4EP, sizeof(mIPv4EP) );
	mIPv4EP.sin_family = AF_INET;
	if ( nullptr != ipAddress )
	{
		inet_pton( AF_INET, ipAddress, &mIPv4EP.sin_addr );
	}
	mIPv4EP.sin_port = ::htons(port);
}
#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "CEvent.h"

CEvent Inet(bool* flag1, SOCKET* sock, SOCKET* listener);
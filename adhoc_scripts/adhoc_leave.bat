SET WIRELESS_DEVICE="%1"

netsh wlan disconnect
netsh interface ipv4 set address %WIRELESS_DEVICE% dhcp

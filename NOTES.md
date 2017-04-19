# MacOS Notes

### Compiling with Cryptopp on MacOS

I had to install cryptopp on Mac with a prefix of the extern_libs directory.
Since I use brew, and brew doesn't support custom installation paths, you need to install it within extern_libs, because [the prefix is wherever you extract the tarball.](https://github.com/Homebrew/brew/blob/664d0c67d5947605c914c4c56ebcfaa80cb6eca0/docs/Installation.md#multiple-installations)

Therefore, it is possible to do the following in order to include and link to the library on MacOS:
```bash
# cd to this repo directory
cd extern_libs

# Download and extract the latest brew here...
curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1

# Install cryptopp with this prefix:
./bin/brew install cryptopp

```


Now, it should be able to link to cryptopp without changing the *.pro* file.


### Connecting to the adhoc network
The adhoc setup scripts use the network manager, which doens't exist on MacOS. In order to connect, you need a linux device which creates the network.
Then, connect to it just as you would on a Wifi network.

Afterwards, go to Network Preferences, click on your Wifi connection, click on Advanced->TCP/IP.
Change the IPv4 configuration from DHCP to manual and set the IP address to 192.168.5.x (where x is your computer ID in the chat system).
*(optional)* Set the subnet mask to 255.255.255.0.

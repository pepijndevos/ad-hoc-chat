# Ad-hoc chat

This is an Ad-hoc chat built for the project of the Network Systems module at Utwente.


#### Features:
- [Protobufs](https://developers.google.com/protocol-buffers/) to structure and serialize our data.
- Qt5 for GUI, networking and inter-communication of different layers.
- [Raft](https://raft.github.io/) for node synchronisation. *(Which doesn't work yet)*
- Everything is sent over UDP Multicast.
- Symmetric AES Encryption at the packet level, using [cryptopp](https://www.cryptopp.com/).


#### MacOS Notes:
If using MacOS, read the [NOTES.md](NOTES.md) for connecting to the Adhoc network and installing cryptopp using brew.

# Client and Server on TCP and UDP


## Overview


TCP (Transmission Control Protocol) is the most commonly used protocol on the Internet. The reason for this is because TCP offers error correction.

When the TCP protocol is used there is a "guaranteed delivery."

This is due largely in part to a method called "flow control."

Flow control determines when data needs to be re-sent, and stops the flow of data until previous packets are successfully transferred.

This works because if a packet of data is sent, a collision may occur.

When this happens, the client re-requests the packet from the server until the whole packet is complete and is identical to its original. 


UDP (User Datagram Protocol) is anther commonly used protocol on the Internet. 

However, UDP is never used to send important data such as webpages, database information, etc; UDP is commonly used for streaming audio and video. 

Streaming media such as Windows Media audio files (.WMA) , Real Player (.RM), and others use UDP because it offers speed! 

The reason UDP is faster than TCP is because there is no form of flow control or error correction. 

The data sent over the Internet is affected by collisions, and errors will be present. 

Remember that UDP is only concerned with speed. This is the main reason why streaming media is not high quality.

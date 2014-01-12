APKEncryption
=============

a cryptography method based on pre-shared key. The key is 4 bytes (three bytes + null byte). Each include a 3 bit long number (000 to 111). The data packet is 8 bytes and each byte of data is a combination of 5 bits of data and three bytes of encryption key of the next packet.

# Changelog

This file documents all notable changes to **WINCS02** and **RNWF02** firmware.

## [v3.3.0] — October 2026

### New Features
- Periodic scanning and beacon transmission (WSCNP, WBCN) for asset tracking and similar beacon-based applications
- Vendor-specific information elements (IEs) in beacon, probe request and probe response frames, for transmit and receive
- Large MQTT messages (up to 16KB): fragmented publish and buffered subscribe
- Hotspot: MAC address blocklist

### Enhancements
- SSID prefix matching in the scan filter list
- Hotspot: ability to disconnect an associated STA
- IPv6: option to disable SLAAC
- OTA: HTTP status errors (e.g. 401, 404) are reported immediately in +OTAERR
- MQTT: oversized messages are rejected and reported
- Reduced XDS sleep current and cold boot current consumption
- **WINCS02 only:** Extended error API in the driver, giving more detail about driver failures

### Fixes
- Security: fixes for vulnerabilities in the Wi-Fi firmware and the network controller application (see [SECURITY.md](./SECURITY.md))
- Wi-Fi: WSTAC BSSID configuration now limits the AP connected to; connection state is cleared after a failed connect; Hotspot no longer loses STA connections after scanning
- MQTT: fixed byte array publish payloads, publish failures within specified limits, empty topic names and corrupted or partial multi-chunk received messages, and recovery from oversized received messages
- Power save: fixed crash when XDS is enabled with the secondary oscillator selected but no crystal fitted
- Bypass mode: fixed crash on receiving a 14-byte Ethernet frame
- **WINCS02 only:** Driver fixes for Berkeley socket locking and UDP buffer leak, crash on SDIO bus failure, missing scan completion when all results are filtered, power save configuration, and resource clean-up when initialisation fails

## [v3.2.0] — March 2026

> **Note:** Firmware binary filenames changed in this release.
> `*.bootable.bin` → `*_wholeflash.bin` and `*_dfu.bootable.bin` → `*_dfu_high.bin`.
> See the release notes for your version for the correct filenames.

### New Features
- WPA Enterprise support (EAP-TLS, EAP-TTLS, EAP-PEAP)
- HTTP Client API
- Platform Power Save (PPS) with EXtreme Deep Sleep (XDS) mode
- TLS session caching and certificate pinning
- Boot-time configuration of system variables
- **RNWF02 only:** Persistent baud rate configuration

### Enhancements
- DNS client: MDNS, TCP and TLS support; additional record types (CNAME, SOA, PTR, TXT, DS, NSEC, DNSKEY); fallback DNS
- Additional TLS contexts for WPA-Enterprise, DNS over TLS, MQTT, and TLS sockets
- TCP socket hand-off to protocol handlers (e.g. HTTP client)
- Optimised memory use for Block-Ack handles and improved buffer handling under load
- Ability to reset configuration commands to default values
- **RNWF02 only:** Serial interface format control
- Improved scan filter documentation and file handling
- OTA: increased maximum URL length to 1024 characters

### Fixes
- WLAN and Hotspot stability: fixed several crashes in Hotspot mode, Block-Ack session handling, DHCP server locking, and Wi-Fi QoS parameter processing
- TCP/IP and socket handling: improved TCP window management and corrected socket read/write behaviour for UDP and TCP
- TLS and security: fixed random number generator reseeding after prolonged operation and improved TLS alert handling
- MQTT connectivity: fixed connection and initialisation issues, including dual-stack broker resolution and QoS message acknowledgement
- IPv6: fixed crash when sending IPv6 ping using hostname
- **WINCS02 only:** Berkeley sockets: fixed poll skipping of invalid file descriptors, dual-stack listening socket matching, setsockopt validation on pending sockets, connect rejection after failure, getaddrinfo result population, and dual-stack TCP server socket port conflicts
- General: various fixes for file system handle management, NVM data handling, and command parameter validation

## [v3.1.0] — September 2025

### New Features
- Anti-rollback counter API (query and increment)
- DFU image modification API (secure DFU support)
- Arbitrary flash file read/write API

### Enhancements
- Upgraded TLS stack to WolfSSL v5.7.4 from v4.7.0
- TX A-MPDU performance improvements (buffer handling, ack handling, TX/RX decoupling)
- Removed expired Baltimore CyberTrust Root certificate from release package
- Strengthened cryptographic elements used in WPA2/WPA3 (NIST-standard RNG)
- Refined CCA levels for adaptivity test compliance
- Improved TLS error reporting and detection of incorrect TLS configurations
- Removed limit on connections per server socket (up to 10 total TCP connections)
- Increased Hotspot mode STA connections from 8 to 10
- Prevented flash partition modification when current partition image is invalidated

### Security Fixes
- Fixed CVE-2009-3555 (TLS renegotiation)
- Fixed CVE-2017-13079 and CVE-2017-13081 (Wi-Fi IGTK reinstallation)

### Fixes
- Block-Ack stability: fixed TX stalls, lost frames, stuck recovery, and memory leaks when Block-Ack is active
- AP/Hotspot: fixed de-authentication crashes and fragmented frame MIC check failures in AP mode
- TLS: fixed watchdog when exceeding connection limit and improved interoperability with renegotiation
- MQTT: fixed subscription read flushing all messages and corrected debug output for protected management frames
- TCP: fixed fast re-transmit detection being reset by data packets between duplicate ACKs
- General: fixed MAC event manager stalls, A-MPDU crash on de-auth, and AP cipher detection

### Certification
- WFA Flextrack and Quicktrack STA mode certification (Quicktrack v2.2)

## [v3.0.0] — October 2024

### New Features
- Layer 2 bypass mode (send/receive raw packets with unicast/broadcast/multicast filtering)
- TLS v1.2 Server mode
- Over-the-Air (OTA) firmware upgrade via internal HTTP/HTTPS and host-controlled flash writing
- Persistent configuration storage and retrieval (RAM and flash)
- TX A-MPDU support in STA mode
- Roaming enable/disable control

### Enhancements
- Enhanced system throughput across multiple layers
- DNS client support for IPv6 servers and AAAA record filtering
- MQTT: topic aliases, IPv6 server hostname resolution, clear all TX properties
- Socket: asynchronous receive modes, TOS on unconnected UDP
- TLS: certificate chain support (2+ certificates during handshake)
- SNTP configuration changeable while connected
- Integer representation expanded to binary and octal formats

### Fixes
- Wi-Fi stability: fixed idle disconnections, WMM crashes, powersave QoS handling, and coexistence failures
- SoftAP: fixed HT/WMM IE extraction and multi-cycle disconnect/connect/reset reliability
- TCP/IP: fixed IPv6 socket crashes, enabled fast retransmission, and corrected broadcast QoS framing
- MQTT: fixed IPv6 connection failures, publish after ping, and property formatting
- TLS: enabled SHA224 for handshakes and fixed crash on excessively long commands
- Roaming: fixed disconnect/auth-fail state sync and probe request channel correctness
